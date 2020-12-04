/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 * File:    alpm_128.c
 * Purpose: Tomahawk Primitives for LPM management in ALPM - Mode for IPv6-128.
 * Requires:
 */

#include <shared/bsl.h>

#include <soc/mem.h>
#include <soc/drv.h>
#include <soc/debug.h>
#include <soc/error.h>
#include <soc/lpm.h>
#include <soc/trident2.h>
#include <soc/tomahawk.h>

#ifdef ALPM_ENABLE
#if defined(BCM_TOMAHAWK_SUPPORT) || defined(BCM_APACHE_SUPPORT)

#include <shared/util.h>
#include <shared/l3.h>
#include <soc/alpm.h>
#include <soc/esw/alpm_int.h>
#include <soc/esw/trie.h>


#define SHR_SHIFT_LEFT(val, count) \
    (((count) == 32) ? 0 : (val) << (count))

#define SHR_SHIFT_RIGHT(val, count) \
    (((count) == 32) ? 0 : (val) >> (count))

/* Add support for Extended based on Flex Counter support type */
#define SOC_ALPM_TABLE_MEM_128(_u_, _v6_, _mem_)             \
            _mem_ = L3_DEFIP_ALPM_IPV6_128m

/* Add suport for Extended */
#define SOC_ALPM_ENTRY_BUF_128(_v6_, _mem_, _buf_, _v4ent_, _v6ent_)  \
            _buf_ = ((uint32 *) &(_v6ent_))

/* this is a left shift of the prefix by 32/64 - length  and convert to
   brcm order of ip words */
#define ALPM_TRIE_TO_NORMAL_IP_128(prefix, length, v6) \
    _soc_th_alpm_128_trie_to_normal_ip((prefix), (length), (v6))

/* used for moving either 2 v4 entries or 1 v6 entry. */
#define SOC_ALPM_MOVE_PIVOT_FULL_128(u, src, dst)\
    do {\
        int _src = soc_th_alpm_physical_idx((u), L3_DEFIP_PAIR_128m, (src), 1);\
        int _dst = soc_th_alpm_physical_idx((u), L3_DEFIP_PAIR_128m, (dst), 1);\
        int tcam = SOC_ALPM_128_ADDR_LWR((u), (_dst)) << 1;\
        /* Track full-entry move */\
        ALPM_TCAM_PIVOT((u), tcam) = \
                ALPM_TCAM_PIVOT((u), SOC_ALPM_128_ADDR_LWR((u), (_src)) << 1);\
        if (ALPM_TCAM_PIVOT((u), tcam)) {\
            PIVOT_TCAM_INDEX(ALPM_TCAM_PIVOT((u), tcam)) = tcam;\
            SOC_ALPM_BU_PIVOT_IDX_UPDATE(u, tcam); \
        }\
        ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR((u), (_src)) << 1) = NULL;\
    } while (0)

/***********************************************************************
 ***********************************************************************
 *              TCAM Management and ALPM Memory Mangement              *
 */
void soc_th_alpm_128_lpm_state_dump(int u);
static int soc_th_alpm_128_lpm_insert(int u, void *entry_data, int *index, int bpm_len,
                                      int src_default, int src_discard);
static int soc_th_alpm_128_lpm_delete(int u, void *key_data);
static int _soc_th_alpm_128_fill_aux_entry_for_op(int u,
               void *key_data,
               int ipv6,    /* Entry is ipv6. */
               int db_type, /* database type */
               int ent_type,
               int replace_len, /* used for DElete propagate */
               defip_aux_scratch_entry_t *aux_entry);
static int
_soc_th_alpm_128_lpm_match(int u,
               void *key_data,
               void *e,         /* return entry data if found */
               int *index_ptr,  /* return key location */
               int *pfx_len,    /* Key prefix length. vrf+32+pfx len for v6*/
               int *ipv6,       /* Entry is ipv6. */
               int *vrf_id,     /* (OUT) */
               int *vrf);        /* (OUT) */

static int soc_th_alpm_128_lpm_match(int u,
               void *key_data,
               void *e,         /* return entry data if found */
               int *index_ptr);  /* return key location */
static int _soc_th_alpm_128_mem_ent_init(int unit, void *lpm_entry,
                       void *alpm_entry, void *alpm_sip_entry, soc_mem_t mem,
                       uint32 src_flags, uint32 *default_route, int bucket_id);
static int
_soc_th_alpm_128_lpm_ent_init(int unit, void *alpm_entry, soc_mem_t mem,
                              int ipv6, int vrf_id, int bucket, int index,
                              void *lpm_entry, int flex);
static int
_soc_th_alpm_128_lpm_ent_key_init(int unit, uint32 *key, int len, int vrf, int ipv6,
                             defip_pair_128_entry_t *lpm_entry, int init);

static int soc_th_alpm_128_vrf_delete(int u, int vrf, int v6);


/* Extern */
extern int soc_th_get_alpm_banks(int unit);
extern int _soc_th_alpm_rollback_bkt_move(int u, int v6, void *key_data,
                        soc_mem_t mem, alpm_pivot_t *old_pivot_pyld,
                        alpm_pivot_t *new_pivot_pyld,
                        alpm_mem_prefix_array_t *p_pfxarr,
                        int *new_index, int new_insert);
extern int soc_th_alpm_lpm_delete(int u, void *key_data);

/* Lpm State */
#define FB_LPM_128_HASH_SUPPORT 1

typedef struct soc_th_alpm_128_lpm_state_s {
    int start;  /* start index for this prefix length */
    int end;    /* End index for this prefix length */
    int prev;   /* Previous (Lo to Hi) prefix length with non zero entry count*/
    int next;   /* Next (Hi to Lo) prefix length with non zero entry count */
    int vent;   /* valid entries */
    int fent;   /* free entries */
} soc_th_alpm_128_lpm_state_t, *soc_th_alpm_128_lpm_state_p;

#define SOC_MEM_128_COMPARE_RETURN(a, b) {          \
        if ((a) < (b)) { return -1; }           \
        if ((a) > (b)) { return  1; }           \
}

/* Can move to SOC Control structures */
static soc_th_alpm_128_lpm_state_p soc_th_alpm_128_lpm_state[SOC_MAX_NUM_DEVICES];

#define IPV6_128_PFX_ZERO                0
#define MAX_PFX_ENTRIES_128              (3 * (128 + 2 + 1))
#define MAX_PFX_INDEX_128                (MAX_PFX_ENTRIES_128 - 1)
#define MAX_VRF_PFX_INDEX_128            ((MAX_PFX_ENTRIES_128/3) - 1)
#define SOC_ALPM_128_LPM_INIT_CHECK(u)    (soc_th_alpm_128_lpm_state[(u)] != NULL)
#define SOC_ALPM_128_LPM_STATE(u)             (soc_th_alpm_128_lpm_state[(u)])
#define SOC_ALPM_128_LPM_STATE_START(u, pfx)  \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].start)
#define SOC_ALPM_128_LPM_STATE_END(u, pfx)    \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].end)
#define SOC_ALPM_128_LPM_STATE_PREV(u, pfx)  \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].prev)
#define SOC_ALPM_128_LPM_STATE_NEXT(u, pfx)  \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].next)
#define SOC_ALPM_128_LPM_STATE_VENT(u, pfx)  \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].vent)
#define SOC_ALPM_128_LPM_STATE_FENT(u, pfx)  \
    (soc_th_alpm_128_lpm_state[(u)][(pfx)].fent)

#define SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(m, f) soc_field_info_t * m##f
#define SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(m_u, s, m, f) \
                (s)->m##f = soc_mem_fieldinfo_get(m_u, m, f)

typedef struct soc_lpm_128_field_cache_s {
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, CLASS_IDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, DST_DISCARDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, SRC_DISCARDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ECMPf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ECMP_COUNTf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ECMP_PTRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, GLOBAL_ROUTEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, RPA_IDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, EXPECTED_L3_IIFf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IPMC_EXPECTED_L3_IIF_MISMATCH_TOCPUf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IPMC_EXPECTED_L3_IIF_MISMATCH_DROPf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, L3MC_INDEXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, HITf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR_MASK0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR_MASK1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR_MASK0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, IP_ADDR_MASK1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, NEXT_HOP_INDEXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, PRIf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, RPEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VALID0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VALID1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VALID0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VALID1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_MASK0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_MASK1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_MASK0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, VRF_ID_MASK1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, GLOBAL_HIGHf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ALG_HIT_IDXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ALG_BKT_PTRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ALG_SUB_BKT_PTRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, DEFAULT_MISSf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, FLEX_CTR_BASE_COUNTER_IDXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, FLEX_CTR_OFFSET_MODEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, FLEX_CTR_POOL_NUMBERf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, DESTINATIONf);
    SOC_ALPM_128_LPM_CACHE_FIELD_CREATE(L3_DEFIP_PAIR_128m, ENTRY_VIEWf);
} soc_lpm_128_field_cache_t, *soc_lpm_128_field_cache_p;

static soc_lpm_128_field_cache_p
                        soc_lpm_128_field_cache_state[SOC_MAX_NUM_DEVICES];

#define SOC_MEM_OPT_F32_GET_128(m_unit, m_mem, m_entry_data, m_field) \
        soc_meminfo_fieldinfo_field32_get((&SOC_MEM_INFO(m_unit, m_mem)), \
            (m_entry_data), (soc_lpm_128_field_cache_state[(m_unit)]->m_mem##m_field))

#define SOC_MEM_OPT_F32_SET_128(m_unit, m_mem, m_entry_data, m_field, m_val) \
        soc_meminfo_fieldinfo_field32_set((&SOC_MEM_INFO(m_unit, m_mem)), \
            (m_entry_data), (soc_lpm_128_field_cache_state[(m_unit)]->m_mem##m_field), (m_val))


#define SOC_MEM_OPT_FIELD_VALID_128(m_unit, m_mem, m_field) \
        ((soc_lpm_128_field_cache_state[(m_unit)]->m_mem##m_field) != NULL)

#ifdef FB_LPM_128_HASH_SUPPORT
typedef struct _soc_th_alpm_128_lpm_hash_s {
    int         unit;
    int         entry_count;    /* Number entries in hash table */
    int         index_count;    /* Hash index max value + 1 */
    uint16      *table;         /* Hash table with 16 bit index */
    uint16      *link_table;    /* To handle collisions */
} _soc_th_alpm_128_lpm_hash_t;

typedef uint32 _soc_th_alpm_128_lpm_hash_entry_t[9];
typedef int (*_soc_th_alpm_128_lpm_hash_compare_fn)
     (_soc_th_alpm_128_lpm_hash_entry_t key1, _soc_th_alpm_128_lpm_hash_entry_t key2);
static _soc_th_alpm_128_lpm_hash_t *_fb_lpm_128_hash_tab[SOC_MAX_NUM_DEVICES];

#define SOC_ALPM_128_LPM_STATE_HASH(u)           (_fb_lpm_128_hash_tab[(u)])

#define FB_LPM_128_HASH_INDEX_NULL  (0xFFFF)
#define FB_LPM_128_HASH_INDEX_MASK  (0x3FFF)
#define FB_LPM_128_HASH_IPV6_MASK   (0x8000)

#define SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, entry_data, odata) \
    odata[0] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR0_LWRf);\
    odata[1] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR0_UPRf);\
    odata[2] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR_MASK0_LWRf);\
    odata[3] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR_MASK0_UPRf);\
    odata[4] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR1_LWRf);\
    odata[5] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR1_UPRf);\
    odata[6] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR_MASK1_LWRf);\
    odata[7] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data, \
               IP_ADDR_MASK1_UPRf);\
    if ( (!(SOC_IS_HURRICANE(u))) &&   \
        (SOC_MEM_OPT_FIELD_VALID_128(u, L3_DEFIP_PAIR_128m, VRF_ID_0_LWRf))) { \
        int m_vrf;\
        (void) soc_th_alpm_128_lpm_vrf_get(u, entry_data, (int *)&odata[8], &m_vrf); \
    } else {                                                                 \
        odata[8] = 0;                                                        \
    }

#define SOC_FB_LPM_128_HASH_ENTRY_GET _soc_th_alpm_128_lpm_hash_entry_get

static void
_soc_th_alpm_128_lpm_hash_entry_get(int u, void *e,
                             int index, _soc_th_alpm_128_lpm_hash_entry_t r_entry,
                             int *v);
static uint16
_soc_th_alpm_128_lpm_hash_compute(uint8 *data, int data_nbits);
static int
_soc_th_alpm_128_lpm_hash_create(int unit, int entry_count, int index_count,
                            _soc_th_alpm_128_lpm_hash_t **fb_lpm_hash_ptr);
static int
_soc_th_alpm_128_lpm_hash_destroy(_soc_th_alpm_128_lpm_hash_t *fb_lpm_hash);
static int
_soc_th_alpm_128_lpm_hash_lookup(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t    entry,
                            int pfx, uint16 *key_index);
static int
_soc_th_alpm_128_lpm_hash_insert(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int pfx, uint16 old_index, uint16 new_index,
                            uint32 *rvt_index);
static
int _soc_th_alpm_128_lpm_hash_revert(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            uint16 new_index,
                            uint32 rvt_index);
static int
_soc_th_alpm_128_lpm_hash_delete(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int pfx, uint16 delete_index);
static int
_soc_th_alpm_128_lpm_hash_verify(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int pfx, uint16 verify_index);

static int
_soc_th_alpm_128_lpm_prefix_length_get(int, void *, int *, int *, int *);

STATIC int
_soc_th_alpm_128_ip6_mask_len_get(int u, const void *entry, int *pfx)
{
    int     i, rv;
    int     field[4] = {IP_ADDR_MASK0_LWRf, IP_ADDR_MASK1_LWRf,
                        IP_ADDR_MASK0_UPRf, IP_ADDR_MASK1_UPRf};
    uint32  ipv4a;
    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, entry, field[0]);
    if ((rv = _ipmask2pfx(ipv4a, pfx)) < 0) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                          "_ipmask2pfx fails mask0 0x%x pfx %d\n"),
                          ipv4a, *pfx));
        return(rv);
    }
    for (i = 1; i < 4; i++) {
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, entry, field[i]);
        if (*pfx) {
            if (ipv4a != 0xffffffff)  {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                                  "ip6_mask_len_get fails i %d mask 0x%x pfx %d\n"),
                                  i, ipv4a, *pfx));
                return(SOC_E_PARAM);
            }
            *pfx += 32;
        } else {
            if ((rv = _ipmask2pfx(ipv4a, pfx)) < 0) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                                  "_ipmask2pfx fails mask%d 0x%x pfx %d\n"),
                                  i, ipv4a, *pfx));
                return(rv);
            }
        }
    }
    return SOC_E_NONE;
}

static void
_soc_th_alpm_128_trie_to_normal_ip(uint32 *result, int length, int v6)
{
    uint32 pfx_shift, tmp, start, prefix[6];
    int i;

    sal_memcpy(prefix, result, sizeof(uint32) * BITS2WORDS(_MAX_KEY_LEN_144_));
    sal_memset(result, 0, sizeof(uint32) * BITS2WORDS(_MAX_KEY_LEN_144_));

    /* shift entire prefix left to add trailing 0s in prefix */
    pfx_shift = 128 - length;
    start = (pfx_shift + 31) / 32;
    /* fix corner case: */
    if ((pfx_shift % 32) == 0) {
        start++;
    }
    pfx_shift = pfx_shift % 32;
    for (i = start; i <= 4; i++) {
        prefix[i] <<= pfx_shift;
        tmp = prefix[i+1] & ~(0xffffffff >> pfx_shift);
        tmp = SHR_SHIFT_RIGHT(tmp, 32 - pfx_shift);
        if (i < 4) {
            prefix[i] |= tmp;
        }
    }
    /* make shift left justified and reversed, i.e, lsw goes to index 0 */
    for (i = start; i <= 4; i++) {
        result[3 - (i - start)] = prefix[i];
    }
}

static void
_soc_th_alpm_128_pfx_len_to_mask(int unit, void *lpm_entry, int pfx_len)
{
    int i;
    soc_field_t mask_field[4] = {IP_ADDR_MASK0_LWRf, IP_ADDR_MASK1_LWRf,
                                 IP_ADDR_MASK0_UPRf, IP_ADDR_MASK1_UPRf};
    /* initialize mask field to 0, in case same entry is first being filled with
     * associated data first and then key later
     */
    for (i = 0; i < 4; i++) {
        soc_mem_field32_set(unit, L3_DEFIP_PAIR_128m, lpm_entry, mask_field[i],
                            0);
    }
    for (i = 0; i < 4; i++) {
        if (pfx_len <= 32) break;
        soc_mem_field32_set(unit, L3_DEFIP_PAIR_128m, lpm_entry,
                            mask_field[3-i], 0xffffffff);
        pfx_len -= 32;
    }
    soc_mem_field32_set(unit, L3_DEFIP_PAIR_128m, lpm_entry, mask_field[3-i],
                        ~SHR_SHIFT_RIGHT(0xffffffff, pfx_len));
}

/* Create Prefix */
/* Prefix is created based on the trie key packing expectations */
/* Prefix[0] will have higher order Word, Prefix[1] will have lower order word
 * in case of IPV6. For IPV4 prefix[0] will contain the prefix
 */
int
_soc_th_alpm_128_prefix_create(int u, void *entry, uint32 *result, uint32 *pfx_len,
                               int *default_route)
{
    int i;
    int pfx = 0, start;
    int rv = SOC_E_NONE;
    uint32 pfx_shift, tmp;
    uint32  prefix[5];

    sal_memset(result, 0, sizeof(uint32) * BITS2WORDS(_MAX_KEY_LEN_144_));
    sal_memset(prefix, 0, sizeof(uint32) * BITS2WORDS(_MAX_KEY_LEN_144_));

    /* Form Prefix based on the entry */
    prefix[0] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry, IP_ADDR0_LWRf);
    prefix[1] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry, IP_ADDR1_LWRf);
    prefix[2] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry, IP_ADDR0_UPRf);
    prefix[3] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry, IP_ADDR1_UPRf);
    /* Obtain prefix length */
    rv = _soc_th_alpm_128_ip6_mask_len_get(u, entry, &pfx);
    if (SOC_FAILURE(rv)) {
        return rv;
    }

    /* shift entire prefix right to remove trailing 0s in prefix */
    /* to simplify, words which are all 0s are ignored to begin with, so
     * a right shift of say 46 is a right shift of 46-32 = 14, but starting
     * from word 1. Once all shifting is done, shift all words to right by 1
     */
    pfx_shift = 128 - pfx;
    start = pfx_shift / 32;
    pfx_shift = pfx_shift % 32;
    for (i = start; i < 4; i++) {
        prefix[i] >>= pfx_shift;
        tmp = prefix[i+1] & ((1 << pfx_shift) - 1);
        tmp = SHR_SHIFT_LEFT(tmp, 32 - pfx_shift);
        prefix[i] |= tmp;
    }
    /* make shift right justified and also reverse order for trie.
     * Also, note trie sees key only in words 1 to 4
     */
    for (i = start; i < 4; i++) {
        result[4 - (i - start)] = prefix[i];
    }
    *pfx_len = pfx;
    if (default_route != NULL) {
        *default_route = (prefix[0] == 0) && (prefix[1] == 0) &&
                         (prefix[2] == 0) && (prefix[3] == 0) && (pfx == 0);
    }

    return SOC_E_NONE;
}

int _soc_th_alpm_128_sw_pivot_find(int u, uint32 *prefix, uint32 length, int ipv6,
                                   int vrf, int *hit, int *tcam_index,
                                   int *log_bkt)
{
    int rv = SOC_E_NONE;
    trie_t  *pivot_trie;
    trie_node_t *lpmp = NULL;
    alpm_pivot_t *pivot_pyld;

    pivot_trie = VRF_PIVOT_TRIE_IPV6_128(u, vrf);
    rv = trie_find_lpm(pivot_trie, prefix, length, &lpmp);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "Pivot find failed\n")));
        return rv;
    }
    pivot_pyld = (alpm_pivot_t *)lpmp;

    *hit = 1;
    *tcam_index = PIVOT_TCAM_INDEX(pivot_pyld);
    *log_bkt = PIVOT_BUCKET_INDEX(pivot_pyld);

    return SOC_E_NONE;
}

int
_soc_th_alpm_128_sw_prefix_check(int u,
                                 soc_mem_t mem,      /* Mem type for ALPM */
                                 int v6,
                                 void *key_data,     /* TCAM entry data */
                                 int vrf_id,
                                 int vrf)
{
    int         rv = SOC_E_NONE;
    uint32 prefix[5], length;
    int default_route = 0;
    trie_t  *pivot_trie, *bkt_trie;
    trie_node_t *lpmp = NULL;
    alpm_pivot_t *pivot_node;
    if (vrf_id == 0) {
        if (ALPM_CTRL(u).gp_zoned) {
            /* cannot have 0 as a VRF in parallel mode */
            return SOC_E_PARAM;
        }
    }
    if (!(ALPM_PREFIX_IN_TCAM(u, vrf_id))) {
        rv = _soc_th_alpm_128_prefix_create(u, key_data, prefix, &length,
                                            &default_route);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "_soc_th_alpm_128_sw_prefix_check: prefix create failed\n")));
            return rv;
        }

        pivot_trie = VRF_PIVOT_TRIE_IPV6_128(u, vrf);

        rv = trie_find_lpm(pivot_trie, prefix, length, &lpmp);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "_soc_th_alpm_128_sw_prefix_check: Pivot find failed\n")));
            return rv;
        }
        pivot_node = (alpm_pivot_t *)lpmp;
        bkt_trie = pivot_node->bucket->bucket_trie;
        if (bkt_trie != NULL) {
            rv = trie_search(bkt_trie, prefix, length,
                             (trie_node_t **)&bkt_trie);
            if (SOC_FAILURE(rv)){
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                                      "_soc_th_alpm_128_sw_prefix_check: prefix find failed\n")));
            }
        } else {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "_soc_th_alpm_128_sw_prefix_check: bkt trie doesn't exist\n")));
        }
    }
    return rv;
}

/*
 * Find and read the match in the database.
 * Returns SOC_E_NONE, if found.
 * SOC_E_NOT_FOUND if not found
 * SOC_E_FAIL, if lookup failed.
 */
static int
_soc_th_alpm_128_find(int u,
               soc_mem_t mem,      /* Mem type for ALPM */
               void *key_data,     /* TCAM entry data */
               int vrf_id,
               int vrf,
               void *alpm_data,    /* Alpm data if match */
               int *tcam_index,    /* TCAM INDEX */
               int *log_bkt,       /* return Bucket ID */
               int *index_ptr,     /* return key location */
               int sw_find)
{
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    int         v6;
    int         key_index ;
    uint32      db_type, ent_type, bank_disable;
    int         rv = SOC_E_NONE;
    int         hit = 0;

    v6 = L3_DEFIP_MODE_128;

    if (vrf_id == 0) {
        if (ALPM_CTRL(u).gp_zoned) {
            /* cannot have 0 as a VRF in parallel mode */
            return SOC_E_PARAM;
        }
    }
    bank_disable = ALPM_CTRL(u).bank_disable_bmp[vrf != SOC_VRF_MAX(u) + 1];
    soc_alpm_db_ent_type_encoding(u, vrf, &db_type, &ent_type);
    /* For VRF_OVERRIDE (Global High) entries, software needs to maintain the
     * index */
    /* Prefix resides in TCAM directly */
    if (!(ALPM_PREFIX_IN_TCAM(u, vrf_id))) {
        if (sw_find) {
            uint32 prefix[5], length;
            int default_route = 0;

            /* Create Prefix */
            rv = _soc_th_alpm_128_prefix_create(u, key_data, prefix, &length,
                                                &default_route);
            if (SOC_FAILURE(rv)) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                           "_soc_alpm_insert: prefix create failed\n")));
                return rv;
            }

            rv = _soc_th_alpm_128_sw_pivot_find(u, prefix, length, v6, vrf, &hit,
                                                tcam_index, log_bkt);
            SOC_IF_ERROR_RETURN(rv);
        } else {
            defip_aux_scratch_entry_t aux_entry;
            /* Fill in AUX Scratch and perform Lookup Operation */
            sal_memset(&aux_entry, 0, sizeof(defip_aux_scratch_entry_t));
            SOC_IF_ERROR_RETURN(
                _soc_th_alpm_128_fill_aux_entry_for_op(u, key_data, v6, db_type,
                            ent_type, 0, &aux_entry));
            SOC_IF_ERROR_RETURN(
                _soc_th_alpm_aux_op(u, PREFIX_LOOKUP, &aux_entry, TRUE, &hit,
                                    tcam_index, log_bkt, 0));
        }

        if (hit) { /* Entry is found in the log_bkt */
            /* Fill entry for lookup */
            _soc_th_alpm_128_mem_ent_init(u, key_data, e, 0, mem, 0, 0, *log_bkt);
            /* Perform lookup */
            rv = _soc_th_alpm_find_in_bkt(u, mem, *log_bkt, bank_disable,
                                          e, alpm_data, &key_index, v6);
            if (SOC_SUCCESS(rv)) {
                *index_ptr = key_index;
            }
        } else {
            rv = SOC_E_NOT_FOUND;
        }
    }
    return rv;
}

/*
 * Find and update the match in the database.
 * Returns SOC_E_NONE, if found and updated.
 * SOC_E_NOT_FOUND if not found
 * SOC_E_FAIL, if update failed.
 */
static int
_soc_th_alpm_128_find_and_update(int u,
                              void *key_data,  /* TCAM entry data */
                              void *alpm_data, /* Alpm data to be updated with */
                              void *alpm_sip_data,
                              soc_mem_t mem,   /* Mem view for ALPM data */
                              int key_index)  /* key location */
{
    defip_aux_scratch_entry_t aux_entry;
    int         vrf_id, v6, vrf;
    int         log_bkt;
    uint32      db_type, ent_type;
    int         rv = SOC_E_NONE;
    int         hit = 0, tmp = 0;
    int         tcam_index, index;
    int         aux_flags = 0;
    uint32      alpm_ent[SOC_MAX_MEM_FIELD_WORDS];

    v6 = L3_DEFIP_MODE_128;
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, key_data, &vrf_id, &vrf));
    soc_alpm_db_ent_type_encoding(u, vrf, &db_type, &ent_type);
    /* For VRF_OVERRIDE (Global High) entries */
    if (!(ALPM_PREFIX_IN_TCAM(u, vrf_id))) {
        /* Fill in AUX Scratch and perform Lookup Operation */
        sal_memset(&aux_entry, 0, sizeof(defip_aux_scratch_entry_t));
        SOC_IF_ERROR_RETURN(
           _soc_th_alpm_128_fill_aux_entry_for_op(u, key_data, v6, db_type,
                            ent_type, 0, &aux_entry));

        /* Perform lookup */
        SOC_ALPM_LPM_LOCK(u);
        /* Find and update the entry */
        rv = _soc_th_alpm_128_find(u, mem, key_data, vrf_id, vrf, alpm_ent,
                                   &tcam_index, &log_bkt, &index, TRUE);
        SOC_ALPM_LPM_UNLOCK(u);
        SOC_IF_ERROR_RETURN(rv);
        if (ALPM_CTRL(u).bkt_sharing) {
            soc_mem_field32_set(u, mem, alpm_data, SUB_BKT_PTRf,
                                ALPM_SUB_BKT(u, log_bkt));
        }

        /* Update the entry */
        SOC_IF_ERROR_RETURN(
            soc_mem_write(u, mem, MEM_BLOCK_ANY, ALPM_ENT_INDEX(key_index),
                          alpm_data));

        if (SOC_URPF_STATUS_GET(u)) {
            if (ALPM_CTRL(u).bkt_sharing) {
                soc_mem_field32_set(u, mem, alpm_sip_data, SUB_BKT_PTRf,
                                    ALPM_SUB_BKT(u, log_bkt));
            }
            /* Update the sip entry */
            SOC_IF_ERROR_RETURN(soc_mem_write(u, mem, MEM_BLOCK_ANY,
                                _soc_th_alpm_rpf_entry(u, ALPM_ENT_INDEX(key_index)),
                                alpm_sip_data));
        }
        /* set REPLACE_LEN field to correct value */
        tmp = soc_mem_field32_get(u, L3_DEFIP_AUX_SCRATCHm,
                                 &aux_entry, IP_LENGTHf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                            REPLACE_LENf, tmp);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry, ALG_HIT_IDXf,
                            ALPM_ENT_INDEX(key_index));

        /* We used DELETE_PROPAGATE before because in TD2, INSERT Propagate
         * doesn't handle '==' case, so we need DELETE instead.
         * but DELETE can't be used against software trie-tree for non-delete
         * purpose.
         *
         * So need to bring INSERT back.
         *
         * *** For Trident2, don't turn on TCAM cache. ***
         */
        if (SOC_URPF_STATUS_GET(u)) {
            if (soc_mem_field32_get(u, mem, alpm_sip_data, DEFAULTROUTEf)) {
                aux_flags |= SOC_ALPM_AUX_DEF_ROUTE;
            }
            if (soc_mem_field32_get(u, mem, alpm_sip_data, SRC_DISCARDf)) {
                aux_flags |= SOC_ALPM_AUX_SRC_DISCARD;
            }
        }
        SOC_IF_ERROR_RETURN(_soc_th_alpm_aux_op(u,
            SOC_IS_TRIDENT2(u) ? DELETE_PROPAGATE : INSERT_PROPAGATE,
            &aux_entry, TRUE, &hit, &tcam_index, &log_bkt, aux_flags));

        if (0) {
            /* propagate SIP too */
            /* Check default route */
            soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                RPEf, tmp == 0 ? 1 : 0);
            soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                DB_TYPEf, db_type + 1);
            tmp = soc_mem_field32_get(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                      ALG_HIT_IDXf);
            if (tmp > 0) {
                soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                    ALG_HIT_IDXf, _soc_th_alpm_rpf_entry(u, tmp));
            }
            SOC_IF_ERROR_RETURN(_soc_th_alpm_aux_op(u,
                SOC_IS_TRIDENT2(u) ? DELETE_PROPAGATE : INSERT_PROPAGATE,
                &aux_entry, TRUE, &hit, &tcam_index, &log_bkt, 0));
        }
    }
    return rv;
}

/* Update bucket/hit index of tcam entry if urpf is enabled */
STATIC void
_soc_th_alpm_128_urpf_tcam_info_update(int u, void *entry)
{
    uint32    value = 0;

    value = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, entry, ALG_BKT_PTRf);
    /* modify only valid bucket pointer */
    if (value) {
        value += SOC_TH_ALPM_BUCKET_COUNT(u);
        soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, entry, ALG_BKT_PTRf, value);
    }
    if (ALPM_CTRL(u).bkt_sharing) {
        value = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, entry, ALG_SUB_BKT_PTRf);
        /* modify only valid bucket pointer */
        if (value) {
            soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, entry, ALG_SUB_BKT_PTRf, value);
        }
    }
    /* modify only valid hit index */
    value = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, entry, ALG_HIT_IDXf);
    if (value) {
        value = _soc_th_alpm_rpf_entry(u, value);
        soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, entry, ALG_HIT_IDXf, value);
    }

    return;
}

/* create shadow entry copy of primary tcam entry at index */
static int
_soc_th_alpm_128_tcam_shadow_ent_init(int u, int r_index, void *entry,
                                      defip_aux_table_entry_t *shadow,
                                      int w_index, int bpm_len)
{
    uint32 tmp, db_type, ent_type, urpf = 0;
    soc_mem_t mem = L3_DEFIP_PAIR_128m;
    soc_mem_t s_mem = L3_DEFIP_AUX_TABLEm;
    int rv = SOC_E_NONE, pfx, vrf_id, vrf;
    int is_ipmc = 0;
    void *s1, *s2;

    s1 = (void *) shadow;
    s2 = (void *) (shadow + 1);

    SOC_IF_ERROR_RETURN(soc_mem_read(u, s_mem, MEM_BLOCK_ANY,
                        SOC_ALPM_128_ADDR_LWR(u, r_index), shadow));
    SOC_IF_ERROR_RETURN(soc_mem_read(u, s_mem, MEM_BLOCK_ANY,
                        SOC_ALPM_128_ADDR_UPR(u, r_index), shadow + 1));

    if (bpm_len == INVALID_BPM_LEN) {
        /* Clean dirty data */
        if (soc_mem_field32_get(u, s_mem, s1, VALID0f) == 0) {
            soc_mem_field32_set(u, s_mem, s1, BPM_LENGTH0f, 0);
        }

        if (soc_mem_field32_get(u, s_mem, s1, VALID1f) == 0) {
            soc_mem_field32_set(u, s_mem, s1, BPM_LENGTH1f, 0);
        }

        if (soc_mem_field32_get(u, s_mem, s2, VALID0f) == 0) {
            soc_mem_field32_set(u, s_mem, s2, BPM_LENGTH0f, 0);
        }

        if (soc_mem_field32_get(u, s_mem, s2, VALID1f) == 0) {
            soc_mem_field32_set(u, s_mem, s2, BPM_LENGTH1f, 0);
        }
    } else {
        soc_mem_field32_set(u, L3_DEFIP_AUX_TABLEm, s1, BPM_LENGTH0f, bpm_len);
        soc_mem_field32_set(u, L3_DEFIP_AUX_TABLEm, s1, BPM_LENGTH1f, bpm_len);
        soc_mem_field32_set(u, L3_DEFIP_AUX_TABLEm, s2, BPM_LENGTH0f, bpm_len);
        soc_mem_field32_set(u, L3_DEFIP_AUX_TABLEm, s2, BPM_LENGTH1f, bpm_len);
    }

    tmp = soc_mem_field32_get(u, mem, entry, VRF_ID_0_LWRf);
    soc_mem_field32_set(u, s_mem, s1, VRF0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, VRF_ID_1_LWRf);
    soc_mem_field32_set(u, s_mem, s1, VRF1f, tmp);

    tmp = soc_mem_field32_get(u, mem, entry, VRF_ID_0_UPRf);
    soc_mem_field32_set(u, s_mem, s2, VRF0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, VRF_ID_1_UPRf);
    soc_mem_field32_set(u, s_mem, s2, VRF1f, tmp);

    tmp = soc_mem_field32_get(u, mem, entry, MODE0_LWR_f(u));
    soc_mem_field32_set(u, s_mem, s1, MODE0_f(u), tmp);
    tmp = soc_mem_field32_get(u, mem, entry, MODE1_LWR_f(u));
    soc_mem_field32_set(u, s_mem, s1, MODE1_f(u), tmp);

    tmp = soc_mem_field32_get(u, mem, entry, MODE0_UPR_f(u));
    soc_mem_field32_set(u, s_mem, s2, MODE0_f(u), tmp);
    tmp = soc_mem_field32_get(u, mem, entry, MODE1_UPR_f(u));
    soc_mem_field32_set(u, s_mem, s2, MODE1_f(u), tmp);

    /* for now simply copy all fields. Let caller decide which half to use */
    tmp = soc_mem_field32_get(u, mem, entry, VALID0_LWRf);
    soc_mem_field32_set(u, s_mem, s1, VALID0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, VALID1_LWRf);
    soc_mem_field32_set(u, s_mem, s1, VALID1f, tmp);

    tmp = soc_mem_field32_get(u, mem, entry, VALID0_UPRf);
    soc_mem_field32_set(u, s_mem, s2, VALID0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, VALID1_UPRf);
    soc_mem_field32_set(u, s_mem, s2, VALID1f, tmp);


    /* IP_LENGTH */
    rv = _soc_th_alpm_128_ip6_mask_len_get(u, entry, &pfx);
    SOC_IF_ERROR_RETURN(rv);

    soc_mem_field32_set(u, s_mem, s1, IP_LENGTH0f, pfx);
    soc_mem_field32_set(u, s_mem, s1, IP_LENGTH1f, pfx);
    soc_mem_field32_set(u, s_mem, s2, IP_LENGTH0f, pfx);
    soc_mem_field32_set(u, s_mem, s2, IP_LENGTH1f, pfx);

    /* IP_ADDR */
    tmp = soc_mem_field32_get(u, mem, entry, IP_ADDR0_LWRf);
    soc_mem_field32_set(u, s_mem, s1, IP_ADDR0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, IP_ADDR1_LWRf);
    soc_mem_field32_set(u, s_mem, s1, IP_ADDR1f, tmp);

    tmp = soc_mem_field32_get(u, mem, entry, IP_ADDR0_UPRf);
    soc_mem_field32_set(u, s_mem, s2, IP_ADDR0f, tmp);
    tmp = soc_mem_field32_get(u, mem, entry, IP_ADDR1_UPRf);
    soc_mem_field32_set(u, s_mem, s2, IP_ADDR1f, tmp);

    /* DB_TYPE */
    /* for v4 need to be careful */
    rv = soc_th_alpm_128_lpm_vrf_get(u, entry, &vrf_id, &vrf);
    SOC_IF_ERROR_RETURN(rv);

    if (SOC_URPF_STATUS_GET(u)) {
        if (w_index >= (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1)) {
            urpf = 1;
        }
    }

    soc_alpm_db_ent_type_encoding(u, vrf, &db_type, &ent_type);

    if (soc_feature(u, soc_feature_ipmc_defip)) {
        if (soc_mem_field_valid(u, mem, MULTICAST_ROUTEf)) {
            is_ipmc = soc_mem_field32_get(u, mem, entry, MULTICAST_ROUTEf);
        } else if (soc_mem_field_valid(u, mem, DATA_TYPEf)) {
            if (soc_mem_field32_get(u, mem, entry, DATA_TYPEf) == 2) {
                is_ipmc = 1;
            } else {
                is_ipmc = 0;
            }
        }
    }

    if (ALPM_PREFIX_IN_TCAM(u, vrf_id) || is_ipmc) {
        soc_mem_field32_set(u, s_mem, s1, VALID0f, 0);
        soc_mem_field32_set(u, s_mem, s1, VALID1f, 0);
        soc_mem_field32_set(u, s_mem, s2, VALID0f, 0);
        soc_mem_field32_set(u, s_mem, s2, VALID1f, 0);
        db_type = 0; /* don't care */
    } else {
        if (urpf) {
            db_type ++;
        }
    }

    soc_mem_field32_set(u, s_mem, s1, DB_TYPE0f, db_type);
    soc_mem_field32_set(u, s_mem, s1, DB_TYPE1f, db_type);
    soc_mem_field32_set(u, s_mem, s2, DB_TYPE0f, db_type);
    soc_mem_field32_set(u, s_mem, s2, DB_TYPE1f, db_type);

    /* ENTRY_TYPE */
    tmp = soc_mem_field32_get(u, mem, entry, ENTRY_TYPE0_LWR_f(u));
    soc_mem_field32_set(u, s_mem, s1, ENTRY_TYPE0_f(u), tmp | ent_type);
    tmp = soc_mem_field32_get(u, mem, entry, ENTRY_TYPE1_LWR_f(u));
    soc_mem_field32_set(u, s_mem, s1, ENTRY_TYPE1_f(u), tmp | ent_type);

    tmp = soc_mem_field32_get(u, mem, entry, ENTRY_TYPE0_UPR_f(u));
    soc_mem_field32_set(u, s_mem, s2, ENTRY_TYPE0_f(u), tmp | ent_type);
    tmp = soc_mem_field32_get(u, mem, entry, ENTRY_TYPE1_UPR_f(u));
    soc_mem_field32_set(u, s_mem, s2, ENTRY_TYPE1_f(u), tmp | ent_type);

    /* modify bucket index if urpf is enabled */
    if (urpf) {
       _soc_th_alpm_128_urpf_tcam_info_update(u, entry);
    }

    /* BPM_LENGTH */
    /* don't modify, preserve existing values */
    return SOC_E_NONE;
}

static INLINE int
_soc_th_alpm_128_write_pivot_with_bpm_aux(int u, int copyno, int index, int s_index,
                                      void *entry, int bpm_len)
{
    defip_aux_table_entry_t shadow[2];

    if (SOC_IS_TRIDENT3(u) && SOC_URPF_STATUS_GET(u) &&
        (index >= (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1))) {
        soc_mem_t mem = L3_DEFIP_PAIR_128m;
        soc_mem_field32_set(u, mem, entry, FLEX_CTR_BASE_COUNTER_IDXf, 0);
    }

    if (!ALPM_CTRL(u).aux_enable) {
        if (SOC_URPF_STATUS_GET(u) &&
            (index >= (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1))) {
            _soc_th_alpm_128_urpf_tcam_info_update(u, entry);
        }

        SOC_IF_ERROR_RETURN(
            WRITE_L3_DEFIP_PAIR_128m(u, MEM_BLOCK_ANY, index, entry));
    } else {
        s_index = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, s_index, 1);
        SOC_IF_ERROR_RETURN(
            _soc_th_alpm_128_tcam_shadow_ent_init(u, s_index, entry,
                                                  &shadow[0], index, bpm_len));
        SOC_IF_ERROR_RETURN(
            WRITE_L3_DEFIP_PAIR_128m(u, MEM_BLOCK_ANY, index, entry));

        index = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, index, 1);

        SOC_IF_ERROR_RETURN(WRITE_L3_DEFIP_AUX_TABLEm(u, MEM_BLOCK_ANY,
                            SOC_ALPM_128_ADDR_LWR(u, index), shadow));
        SOC_IF_ERROR_RETURN(WRITE_L3_DEFIP_AUX_TABLEm(u, MEM_BLOCK_ANY,
                            SOC_ALPM_128_ADDR_UPR(u, index), shadow + 1));
    }

    return SOC_E_NONE;
}

/*
 *      Replicate entry to the second half of the tcam if URPF check is ON.
 */
static INLINE
int _lpm_128_fb_urpf_entry_replicate_with_bpm(int u, int index, uint32 *e, int bpm_len,
                                              int src_default, int src_discard)
{
    int src_tcam_offset;  /* Defip memory size/2 urpf source lookup offset */
    uint32 mask0, mask2, mask3;   /* Mask field values.                    */
    uint32 mask1;         /* Mask 1 field value.                           */
    int def_gw_flag;      /* Entry is default gateway.                     */

    if(!SOC_URPF_STATUS_GET(u)) {
        return (SOC_E_NONE);
    }
    src_default = src_default ? 1 : 0;
    src_discard = src_discard ? 1 : 0;

    if (soc_feature(u, soc_feature_l3_defip_hole)) {
         src_tcam_offset = (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1);
    } else if (SOC_IS_APOLLO(u)) {
         src_tcam_offset = (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1) + 0x0400;
    } else {
         src_tcam_offset = (soc_mem_index_count(u, L3_DEFIP_PAIR_128m) >> 1);
    }

    /* Reset destination discard bit. */
    if (SOC_MEM_OPT_FIELD_VALID_128(u, L3_DEFIP_PAIR_128m, DST_DISCARDf)) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, e, DST_DISCARDf, 0);
    }

    /* Set/Reset default gateway flag based on ip mask value. */
    mask0 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e,
                                    IP_ADDR_MASK0_LWRf);
    mask1 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e,
                                    IP_ADDR_MASK1_LWRf);
    mask2 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e,
                                    IP_ADDR_MASK0_UPRf);
    mask3 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e,
                                    IP_ADDR_MASK1_UPRf);

    
    def_gw_flag = ((!mask0) &&  (!mask1) && (!mask2) && (!mask3)) ? 1 : 0;
    mask0 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID0_LWRf);
    mask1 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID0_UPRf);
    mask2 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID1_UPRf);
    mask3 = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID1_UPRf);
    if (mask0 && mask1 && mask2 && mask3) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, e, RPEf,
                                def_gw_flag | src_default);
        if (SOC_MEM_OPT_FIELD_VALID_128(u, L3_DEFIP_PAIR_128m, DST_DISCARDf)) {
            SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, e, DST_DISCARDf,
                                    src_discard);
        }
        if (SOC_IS_TRIDENT3X(u)) {
            soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, e, DATA_TYPEf, 1);
        }
    }

    /* Write entry to the second half of the tcam. */
    return _soc_th_alpm_128_write_pivot_with_bpm_aux(u, MEM_BLOCK_ANY, index + src_tcam_offset,
                                                 index, e, bpm_len);
}

/*
 *      Replicate entry to the second half of the tcam if URPF check is ON.
 */
static
int _lpm_128_fb_urpf_entry_replicate(int u, int index, uint32 *e, int src_default,
                                     int src_discard)
{
    return _lpm_128_fb_urpf_entry_replicate_with_bpm(u, index, e, INVALID_BPM_LEN,
                                                     src_default, src_discard);
}

static int
_soc_th_alpm_128_write_pivot(int u, int copyno, int index, int s_index,
                             void *entry, int bpm_len, int src_default,
                             int src_discard)
{
    int rv;
    rv = _soc_th_alpm_128_write_pivot_with_bpm_aux
        (u, copyno, index, s_index, entry, bpm_len);

    if (rv >= 0) {
        if (bpm_len == INVALID_BPM_LEN) {
            rv = _lpm_128_fb_urpf_entry_replicate(u, index, entry,
                    src_default, src_discard);
        } else {
            rv = _lpm_128_fb_urpf_entry_replicate_with_bpm(u, index, entry,
                    bpm_len,
                    src_default, src_discard);
        }
    }
    return rv;
}

/* Connect TCAM entry to a bucket ID */
static int
_soc_th_alpm_128_bucket_link(int u, int v6, int pivot_index, int log_bkt)
{
    int             rv = SOC_E_NONE;
    int             lpm_index;
    soc_mem_t       lpm_mem = L3_DEFIP_PAIR_128m;
    defip_pair_128_entry_t   lpm_entry;
     int             phy_bkt, sub_bkt;

    phy_bkt = ALPM_PHY_BKT(u, log_bkt);
    sub_bkt = ALPM_SUB_BKT(u, log_bkt);

    /* Connect TCAM entry to new bucket */
    lpm_index = soc_th_alpm_logical_idx(u, lpm_mem,
                    SOC_ALPM_128_DEFIP_TO_PAIR(u, pivot_index >> 1), 1);

    rv = _soc_mem_alpm_read(u, lpm_mem, MEM_BLOCK_ANY, lpm_index, &lpm_entry);
    SOC_IF_ERROR_RETURN(rv);
    soc_mem_field32_set(u, lpm_mem, &lpm_entry, ALG_BKT_PTRf, phy_bkt);
    if (ALPM_CTRL(u).bkt_sharing) {
        soc_mem_field32_set(u, lpm_mem, &lpm_entry, ALG_SUB_BKT_PTRf, sub_bkt);
    }
    rv = soc_mem_write(u, lpm_mem, MEM_BLOCK_ANY, lpm_index, &lpm_entry);
    SOC_IF_ERROR_RETURN(rv);

    if (SOC_URPF_STATUS_GET(u)) {
        int _urpf_index = (soc_mem_index_count(u, lpm_mem) >> 1) +
                            soc_th_alpm_logical_idx(u, lpm_mem,
                            SOC_ALPM_128_DEFIP_TO_PAIR(u, pivot_index >> 1), 1);
        rv = _soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m,
                                MEM_BLOCK_ANY, _urpf_index, &lpm_entry);
        SOC_IF_ERROR_RETURN(rv);

        soc_mem_field32_set(u, lpm_mem, &lpm_entry, ALG_BKT_PTRf,
                            phy_bkt + SOC_TH_ALPM_BUCKET_COUNT(u));
        if (ALPM_CTRL(u).bkt_sharing) {
            soc_mem_field32_set(u, lpm_mem, &lpm_entry, ALG_SUB_BKT_PTRf, sub_bkt);
        }
        rv = WRITE_L3_DEFIP_PAIR_128m(u, MEM_BLOCK_ANY, _urpf_index, &lpm_entry);
        SOC_IF_ERROR_RETURN(rv);
    }

    return rv;
}


static void
_soc_th_alpm_128_bucket_prepare_undo(int u,
                                     alpm_mem_prefix_array_t **alloc_pfx_array,
                                     void **alloc_bufp,
                                     void **alloc_sip_bufp,
                                     int  **alloc_new_index)
{
    if (*alloc_pfx_array) {
        sal_free(*alloc_pfx_array);
        *alloc_pfx_array = NULL;
    }
    if (*alloc_bufp) {
        sal_free(*alloc_bufp);
        *alloc_bufp = NULL;
    }
    if (*alloc_sip_bufp) {
        sal_free(*alloc_sip_bufp);
        *alloc_sip_bufp = NULL;
    }
    if (*alloc_new_index) {
        sal_free(*alloc_new_index);
        *alloc_new_index = NULL;
    }
}


static int
_soc_th_alpm_128_bucket_prepare(int u, soc_mem_t mem,
                                trie_t *bkt_trie,
                                alpm_mem_prefix_array_t **alloc_pfx_array,
                                void **alloc_bufp,
                                void **alloc_sip_bufp,
                                int  **alloc_new_index)
{
    int i, rv = SOC_E_NONE;
    int entry_size;
    int alloc_size;
    /* allocation pointers all set to NULL */
    void *bufp = NULL, *sip_bufp = NULL;
    int  *index_array = NULL;
    alpm_mem_prefix_array_t *pfx_array = NULL;

    *alloc_bufp      = NULL;
    *alloc_sip_bufp  = NULL;
    *alloc_new_index = NULL;
    *alloc_pfx_array = NULL;

    /* Alloc prefix array */
    alloc_size = sizeof(alpm_mem_prefix_array_t);
    pfx_array = sal_alloc(alloc_size, "prefix array");
    if (pfx_array == NULL) {
        goto cleanup;
    }

    /* Fill prefix array */
    sal_memset(pfx_array, 0, sizeof(alpm_mem_prefix_array_t));
    rv = trie_traverse(bkt_trie, _soc_th_alpm_mem_prefix_array_cb,
                       pfx_array, _TRIE_INORDER_TRAVERSE);
    if (SOC_FAILURE(rv)) {
        goto cleanup;
    }

    /* Alloc index array */
    alloc_size = sizeof(int) * pfx_array->count;
    index_array = sal_alloc(alloc_size, "index_array");
    if (index_array == NULL) {
        goto cleanup;
    }
    sal_memset(index_array, -1, alloc_size);

    /* Alloc bufp & sip_bufp */
    entry_size = sizeof(defip_alpm_ipv6_128_entry_t);

    alloc_size = entry_size * pfx_array->count;
    bufp = sal_alloc(alloc_size, "alloc_bufp");
    if (bufp == NULL) {
        goto cleanup;
    }
    if (SOC_URPF_STATUS_GET(u)) {
        sip_bufp  = sal_alloc(alloc_size, "alloc_sip_bufp");
        if (sip_bufp == NULL) {
            goto cleanup;
        }
    }

    /* Fill bufp & sip bufp */
    for (i = 0; i < pfx_array->count; i++) {
        payload_t *prefix = pfx_array->prefix[i];

        if (prefix->index > 0) { /* old prefix */
            rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY, prefix->index,
                              (uint8 *)bufp + i * entry_size);

            if (SOC_FAILURE(rv)) {
                break;
            }

            if (SOC_URPF_STATUS_GET(u)) {
                rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY,
                        _soc_th_alpm_rpf_entry(u, prefix->index),
                        (uint8 *)sip_bufp + i * entry_size);
                if (SOC_FAILURE(rv)) {
                    break;
                }
            }
        }
    }
    if (SOC_FAILURE(rv)) {
        goto cleanup;
    }

    *alloc_bufp      = bufp;
    *alloc_sip_bufp  = sip_bufp;
    *alloc_new_index = index_array;
    *alloc_pfx_array = pfx_array;

    return rv;

cleanup:
    if (bufp) {
        sal_free(bufp);
    }
    if (sip_bufp) {
        sal_free(sip_bufp);
    }
    if (index_array) {
        sal_free(index_array);
    }
    if (pfx_array) {
        sal_free(pfx_array);
    }
    return rv;
}

static void
_soc_th_alpm_128_bucket_inval_undo(int u, soc_mem_t mem,
                               alpm_mem_prefix_array_t *pfx_array,
                               void *old_bufp, void *old_sip_bufp)
{
    int i;
    int entry_size = sizeof(defip_alpm_ipv6_128_entry_t);

    for (i = 0; i < pfx_array->count; i++) {
        payload_t *prefix = pfx_array->prefix[i];

        if (prefix->index > 0) {
            soc_mem_write(u, mem, MEM_BLOCK_ALL, prefix->index,
                          (uint8 *)old_bufp + i * entry_size);

            if (SOC_URPF_STATUS_GET(u)) {
                /* UPRF entry */
                soc_mem_write(u, mem, MEM_BLOCK_ALL,
                              _soc_th_alpm_rpf_entry(u, prefix->index),
                              (uint8 *)old_sip_bufp + i * entry_size);
            }
        }
    }
    return;
}


static int
_soc_th_alpm_128_bucket_inval(int u, soc_mem_t mem,
                              alpm_mem_prefix_array_t *pfx_array,
                              void *old_bufp, void *old_sip_bufp)
{
    int i, rv = SOC_E_NONE;

    /* Invalidation process
     * 1. Erase old copied entries
     * 2. Re-validate those entries if invalidation fails
     */

    for (i = 0; i < pfx_array->count; i++) {
        payload_t *prefix = pfx_array->prefix[i];

        if (prefix->index >= 0) {
            /* zero out old entries now that split is done */
            rv = soc_mem_write(u, mem, MEM_BLOCK_ALL, prefix->index,
                               soc_mem_entry_null(u, mem));
            if (SOC_FAILURE(rv)) {
                break;
            }

            if (SOC_URPF_STATUS_GET(u)) {
                rv = soc_mem_write(u, mem, MEM_BLOCK_ANY,
                                   _soc_th_alpm_rpf_entry(u, prefix->index),
                                   soc_mem_entry_null(u, mem));
                if (SOC_FAILURE(rv)) {
                    break;
                }
            }
        }
    }

    /* re-validate old bucket entries */
    if (SOC_FAILURE(rv)) {
        _soc_th_alpm_128_bucket_inval_undo(u, mem, pfx_array, old_bufp, old_sip_bufp);
    }

    return rv;
}

STATIC int
_soc_th_alpm_128_split_lpm_init(int                     u,
                                int                     pivot_idx_from,
                                int                     vrf,
                                int                     log_bkt,
                                void                    *alpm_data,
                                void                    *alpm_sip_data,
                                uint32                  *pivot,
                                int                     length,
                                defip_pair_128_entry_t  *lpm_entry,
                                uint32                  *bpm_len,
                                uint32                  *bpm,
                                uint32                  *src_discard,
                                uint32                  *src_default)
{
    int                             rv = SOC_E_NONE, v6;
    trie_node_t                     *lpm = NULL;
    payload_t                       *bkt_lpm = NULL;
    trie_t                          *pfx_trie;
    defip_alpm_ipv6_128_entry_t     alpmv6_entry, alpmv6_sip_entry;
    uint32                          tmp_pivot[5] = {0};

    v6 = L3_DEFIP_MODE_128;

    /* prefix trie */
    pfx_trie = VRF_PREFIX_TRIE_IPV6_128(u, vrf);

    /* find longest prefix that covers pivot */
    lpm = NULL;
    rv = trie_find_lpm(pfx_trie, pivot, length, &lpm);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "unit %d Unable to find lpm for pivot: "
                              "0x%08x 0x%08x\n 0x%08x 0x%08x 0x%08x length: %d\n"),
                   u, pivot[0], pivot[1], pivot[2], pivot[3], pivot[4],
                   length));

        return rv;
    }
    bkt_lpm = ((payload_t *)lpm)->bkt_ptr;

    /* Initialize the lpm entry to insert */
    if (bkt_lpm) {
        int             index, vrf_id;
        void            *bufp, *sip_bufp;
        soc_mem_t       mem;

        /* Get table memory. */
        SOC_ALPM_TABLE_MEM_128(u, v6, mem);
        SOC_ALPM_ENTRY_BUF_128(v6, mem, bufp, 0, alpmv6_entry);
        SOC_ALPM_ENTRY_BUF_128(v6, mem, sip_bufp, 0, alpmv6_sip_entry);
        /* this means this bucket default route is an actual route */
        /* initialize new pivot's associated data with data of lpm match */
        index = bkt_lpm->index;
        if (index == -1) {
            /* this means the new route is the bucket's default */
            if (alpm_data == NULL || alpm_sip_data == NULL) {
                return SOC_E_PARAM;
            }
            sal_memcpy(bufp, alpm_data, sizeof(defip_alpm_ipv6_128_entry_t));
            if (SOC_URPF_STATUS_GET(u)) {
                *src_default = soc_mem_field32_get(u, mem, alpm_sip_data,
                                                   DEFAULTROUTEf);
                *src_discard = soc_mem_field32_get(u, mem, alpm_sip_data,
                                                    SRC_DISCARDf);
            }
        } else {
            rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY, index, bufp);
            if (SOC_FAILURE(rv)) {
                return rv;
            }
            if (SOC_URPF_STATUS_GET(u)) {
                rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY,
                                        _soc_th_alpm_rpf_entry(u, index),
                                        sip_bufp);
                *src_default = soc_mem_field32_get(u, mem, sip_bufp,
                                                   DEFAULTROUTEf);
                *src_discard = soc_mem_field32_get(u, mem, sip_bufp,
                                                   SRC_DISCARDf);
            }
        }
        if (SOC_FAILURE(rv)) {
            return rv;
        }

        vrf_id = vrf;
        if (vrf == (SOC_VRF_MAX(u) + 1)) {
            vrf_id = SOC_L3_VRF_GLOBAL;
        }
        rv = _soc_th_alpm_128_lpm_ent_init(u, bufp, mem, v6, vrf_id, log_bkt,
                                           index, lpm_entry,
                                           VRF_FLEX_IS_SET(u, vrf_id, vrf, v6, 1));
        if (SOC_FAILURE(rv)) {
            return rv;
        }
        /* remember the bpm_len of this pivot. Need to put in shadow */
        *bpm_len = bkt_lpm->len;
        if (ALPM_CTRL(u).trie_propagate) {
            (void)trie_bpm_mask_get(pfx_trie, bkt_lpm->key, *bpm_len, bpm);
        }
    } else {
        /* read default data of current pivot */
        /* This case is for those route without default route 0.0.0.0/0,
         * e.g. Parallel mode / (Combined mode + global low)
         * An internal assiciated data is used.
         */
        rv = _soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m, MEM_BLOCK_ANY,
                          soc_th_alpm_logical_idx(u, L3_DEFIP_PAIR_128m,
                          SOC_ALPM_128_DEFIP_TO_PAIR(u, pivot_idx_from >> 1), 1),
                          lpm_entry);
        if (SOC_FAILURE(rv)) {
            return rv;
        }
        /* Need to reset ALG_HIT_IDX to 0. */
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_HIT_IDXf, 0);

        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_BKT_PTRf,
                                ALPM_PHY_BKT(u, log_bkt));
        if (ALPM_CTRL(u).bkt_sharing) {
            SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_SUB_BKT_PTRf,
                                    ALPM_SUB_BKT(u, log_bkt));
        }
    }

    /* Convert is a self-modified op, thus use tmp one */
    sal_memcpy(tmp_pivot, pivot, sizeof(tmp_pivot));

    /* Convert from trie format to h/w format */
    ALPM_TRIE_TO_NORMAL_IP_128(tmp_pivot, length, v6);
    _soc_th_alpm_128_lpm_ent_key_init(u, tmp_pivot, length, vrf, v6,
                                      lpm_entry, 0);

    return rv;
}


static int
_soc_th_alpm_128_split_pivot_create_undo(int u, int v6, int vrf, uint32 *pivot,
                                         uint32 length, alpm_pivot_t *alpm_pivot,
                                         int clear)
{
    int                         rv = SOC_E_NONE, pivot_index;
    alpm_bucket_handle_t        *bucket_handle;
    trie_t                      *pivot_trie = NULL;
    trie_node_t                 *delp = NULL;

    pivot_trie = VRF_PIVOT_TRIE_IPV6_128(u, vrf);

    if (alpm_pivot == NULL) {
        rv = trie_delete(pivot_trie, pivot, length, &delp);
        alpm_pivot = (alpm_pivot_t *) delp;
    }
    if (SOC_SUCCESS(rv)) {
        bucket_handle   = alpm_pivot->bucket;
        pivot_index     = PIVOT_TCAM_INDEX(alpm_pivot);

        trie_destroy(PIVOT_BUCKET_TRIE(alpm_pivot));
        sal_free(alpm_pivot);
        sal_free(bucket_handle);

        /* For normal destroy (other than rollback) when the entry is deleted
         * from lpm. The pivot_index is already replaced to another index.
         */
        if (clear) {
            ALPM_TCAM_PIVOT(u, pivot_index) = NULL;
        }
    }

    return rv;
}



static int
_soc_th_alpm_128_split_pivot_create(int u, int v6, int vrf, int log_bkt_to,
                                    trie_node_t     *split_trie_root,
                                    uint32          *pivot,
                                    uint32          length,
                                    uint32          bpm_len,
                                    uint32          *bpm,
                                    alpm_pivot_t    **new_pivot)
{
    int                             rv = SOC_E_NONE;
    alpm_pivot_t                    *pivot_pyld_new;
    alpm_bucket_handle_t            *bucket_handle;
    trie_t                          *pivot_trie = NULL;

    pivot_trie = VRF_PIVOT_TRIE_IPV6_128(u, vrf);


    /* Add New Pivot to the pivot trie */
    bucket_handle = sal_alloc(sizeof(alpm_bucket_handle_t),
                             "ALPM Bucket Handle");
    if (bucket_handle == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Unable to allocate memory "
                              "for PIVOT trie node \n")));
        return SOC_E_MEMORY;
    }
    sal_memset(bucket_handle, 0, sizeof(*bucket_handle));
    pivot_pyld_new = sal_alloc(sizeof(alpm_pivot_t),
                            "Payload for new Pivot");
    if (pivot_pyld_new == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Unable to allocate memory "
                              "for PIVOT trie node \n")));
        sal_free(bucket_handle);
        return SOC_E_MEMORY;
    }
    sal_memset(pivot_pyld_new, 0, sizeof(*pivot_pyld_new));
    PIVOT_BUCKET_HANDLE(pivot_pyld_new) = bucket_handle;
    (void) trie_init(_MAX_KEY_LEN_144_, &PIVOT_BUCKET_TRIE(pivot_pyld_new));
    PIVOT_BUCKET_TRIE(pivot_pyld_new)->trie  = split_trie_root;
    PIVOT_BUCKET_INDEX(pivot_pyld_new)       = log_bkt_to;
    PIVOT_BUCKET_VRF(pivot_pyld_new)         = vrf;
    PIVOT_BUCKET_IPV6(pivot_pyld_new)        = v6;
    PIVOT_BUCKET_DEF(pivot_pyld_new)         = FALSE;
    PIVOT_TCAM_BPMLEN(pivot_pyld_new)        = bpm_len;

    (pivot_pyld_new)->key[0] = pivot[0];
    (pivot_pyld_new)->key[1] = pivot[1];
    (pivot_pyld_new)->key[2] = pivot[2];
    (pivot_pyld_new)->key[3] = pivot[3];
    (pivot_pyld_new)->key[4] = pivot[4];
    (pivot_pyld_new)->len    = length;

    rv = trie_insert(pivot_trie, pivot,
                     ALPM_CTRL(u).trie_propagate ? bpm : NULL,
                     length, (trie_node_t *)pivot_pyld_new);

    if (SOC_SUCCESS(rv)) {
        if (new_pivot) {
            *new_pivot = pivot_pyld_new;
        }
     } else {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "could not initialize pivot")));
        _soc_th_alpm_128_split_pivot_create_undo(u, v6, vrf, pivot,
                                                 length, pivot_pyld_new, 1);
    }

    return rv;
}


static void
_soc_th_alpm_128_bucket_copy_undo(int u, soc_mem_t mem, int count, int *new_index)
{
    int i;
    for (i = 0; i < count; i++) {
        if (new_index[i] < 0) {
            continue;
        }
        soc_mem_write(u, mem, MEM_BLOCK_ANY, new_index[i],
                      soc_mem_entry_null(u, mem));
        if (SOC_URPF_STATUS_GET(u)) {
            soc_mem_write(u, mem, MEM_BLOCK_ANY,
                          _soc_th_alpm_rpf_entry(u, new_index[i]),
                          soc_mem_entry_null(u, mem));
        }
    }
}


/* Populate entries in pfx array to logical bucket */
static int
_soc_th_alpm_128_bucket_copy(int u, soc_mem_t mem, int vrf,
                             alpm_mem_prefix_array_t *pfx_array,
                             int log_bkt_to,
                             void *old_bufp,
                             void *old_sip_bufp,
                             void *new_bufp,
                             void *new_sip_bufp,
                             int *new_index,
                             int *new_index_pos)
{
    int                             rv = SOC_E_NONE;
    defip_alpm_ipv6_128_entry_t     alpmv6_entry, alpmv6_sip_entry;
    void                            *bufp, *sip_bufp;
    int                             sub_bkt_to;
    int                             entsz, key_index;
    uint32                          bank_disable = 0;
    int                             v6, i;
    uint32                          e[SOC_MAX_MEM_FIELD_WORDS];

    sub_bkt_to    = ALPM_SUB_BKT(u, log_bkt_to);

    bank_disable = ALPM_CTRL(u).bank_disable_bmp[vrf != SOC_VRF_MAX(u) + 1];

    v6 = L3_DEFIP_MODE_128;
    SOC_ALPM_ENTRY_BUF_128(v6, mem, bufp, 0, alpmv6_entry);
    SOC_ALPM_ENTRY_BUF_128(v6, mem, sip_bufp, 0, alpmv6_sip_entry);

    entsz = sizeof(alpmv6_entry);

    for (i = 0; i < pfx_array->count; i++) {
        if (pfx_array->prefix[i]->index > 0) { /* old prefix */
            sal_memcpy(bufp, (uint8 *)old_bufp + i * entsz, entsz);
            if (ALPM_CTRL(u).bkt_sharing) {
                soc_mem_field32_set(u, mem, bufp, SUB_BKT_PTRf, sub_bkt_to);
            }

            if (SOC_URPF_STATUS_GET(u)) {
                sal_memcpy(sip_bufp, (uint8 *)old_sip_bufp + i * entsz, entsz);
            }
            /* entry shouldn't exist, insert the entry into the RAM */
            rv = _soc_th_alpm_insert_in_bkt(u, mem, log_bkt_to,
                                            bank_disable, bufp, sip_bufp, e,
                                            &key_index, v6);

        } else { /* for split case only */
            if (!new_bufp || !new_index_pos) {
                rv = SOC_E_PARAM;
                goto _rollback;
            }
            *new_index_pos = i;
            if (ALPM_CTRL(u).bkt_sharing) {
                soc_mem_field32_set(u, mem, new_bufp, SUB_BKT_PTRf, sub_bkt_to);
            }
            rv = _soc_th_alpm_insert_in_bkt(u, mem, log_bkt_to,
                                            bank_disable, new_bufp, new_sip_bufp, e,
                                            &key_index, v6);
        }
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "Failed to insert prefix "
                                  "0x%08x 0x%08x 0x%08x 0x%08x to bucket %d\n"),
                       pfx_array->prefix[i]->key[1],
                       pfx_array->prefix[i]->key[2],
                       pfx_array->prefix[i]->key[3],
                       pfx_array->prefix[i]->key[4], log_bkt_to));

            goto _rollback;
        }
        new_index[i] = key_index;
    }

_rollback:
    if (SOC_FAILURE(rv)) {
        /* Delete entries in new bucket */
        _soc_th_alpm_128_bucket_copy_undo(u, mem, pfx_array->count, new_index);
    }

    return rv;
}


/* Merge entries from one logical bucket to another */
int
_soc_th_alpm_128_bucket_merge(int u, soc_mem_t mem, int log_bkt_from,
                              int log_bkt_to, soc_alpm_merge_type_t merge_dir,
                              int *shuffled)
{
    int                     *new_index = NULL;
    int                     rv = SOC_E_NONE;
    int                     pivot_idx_from, pivot_idx_to;
    int                     v6, i;
    int                     vrf = 0;
    int                     phy_bkt_from, sub_bkt_from, phy_bkt_to, sub_bkt_to;
    void                    *bufp = NULL, *sip_bufp = NULL;
    alpm_mem_prefix_array_t *pfx_array = NULL;
    defip_pair_128_entry_t  lpm_entry;
    alpm_pivot_t            *from_pivot;
    alpm_pivot_t            *parent_pivot = NULL, *child_pivot = NULL;
    enum {
        _MERGE_NONE,
        _MERGE_PREPARE,
        _MERGE_COPY,
        _MERGE_LPM_LINK,
        _MERGE_INVALIDATE,
        _MERGE_CHILD_TRIE_MERGED,
        _MERGE_CHILD_LPM_DELETED,
        _MERGE_CHILD_PIVOT_DESTROYED
    } doing = _MERGE_NONE, done = _MERGE_NONE;

    phy_bkt_from  = ALPM_PHY_BKT(u, log_bkt_from);
    sub_bkt_from  = ALPM_SUB_BKT(u, log_bkt_from);
    phy_bkt_to    = ALPM_PHY_BKT(u, log_bkt_to);
    sub_bkt_to    = ALPM_SUB_BKT(u, log_bkt_to);

    v6 = L3_DEFIP_MODE_128;

    pivot_idx_from = SOC_ALPM_BU_PIVOT_IDX(u, phy_bkt_from, sub_bkt_from);
    pivot_idx_to = SOC_ALPM_BU_PIVOT_IDX(u, phy_bkt_to, sub_bkt_to);

    from_pivot = ALPM_TCAM_PIVOT(u, pivot_idx_from);

    vrf = PIVOT_BUCKET_VRF(from_pivot);

    /**
     * Invalidate need to happen only after all the entries are
     * written to the new pivot and the new pivot is valid. Otherwise
     * there is a chance of MISS.
     *
     * hitless move:
     * - Copy entries to new bucket.
     * - activate new pivot
     * - delete entries from old bucket
     */

    doing = _MERGE_PREPARE;
    rv = _soc_th_alpm_128_bucket_prepare(u, mem, PIVOT_BUCKET_TRIE(from_pivot),
                                         &pfx_array, &bufp, &sip_bufp, &new_index);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _MERGE_COPY;
    rv = _soc_th_alpm_128_bucket_copy(u, mem, vrf, pfx_array,
                                      log_bkt_to, bufp, sip_bufp,
                                      NULL, NULL, new_index, NULL);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* Connect TCAM entry to new bucket */
    doing = _MERGE_LPM_LINK;
    rv = _soc_th_alpm_128_bucket_link(u, v6, pivot_idx_from, log_bkt_to);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* Invalide old entries */
    doing = _MERGE_INVALIDATE;
    rv = _soc_th_alpm_128_bucket_inval(u, mem, pfx_array, bufp, sip_bufp);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    if (merge_dir != MERGE_PHY) {
        uint32          hw_key[5] = {0};
        int             child_vrf;

        if (merge_dir == MERGE_LOG_PARENT_TO_CHILD) {
            parent_pivot = ALPM_TCAM_PIVOT(u, pivot_idx_from);
            child_pivot  = ALPM_TCAM_PIVOT(u, pivot_idx_to);
        } else if (merge_dir == MERGE_LOG_CHILD_TO_PARENT) {
            child_pivot  = ALPM_TCAM_PIVOT(u, pivot_idx_from);
            parent_pivot = ALPM_TCAM_PIVOT(u, pivot_idx_to);
        }

        /* SW bucket merge: not expect to fail */
        doing = _MERGE_CHILD_TRIE_MERGED;
        rv = trie_merge(PIVOT_BUCKET_TRIE(parent_pivot),
                        PIVOT_BUCKET_TRIE(child_pivot)->trie,
                        child_pivot->key,
                        child_pivot->len);
        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

        sal_memcpy(hw_key, child_pivot->key, sizeof(hw_key));
        ALPM_TRIE_TO_NORMAL_IP_128(hw_key, child_pivot->len, v6);

        child_vrf = PIVOT_BUCKET_VRF(child_pivot);

        (void) _soc_th_alpm_128_lpm_ent_key_init(u, hw_key, child_pivot->len,
                                      child_vrf, v6, &lpm_entry, 1);

        /* Delete child lpm entry from TCAM */
        doing = _MERGE_CHILD_LPM_DELETED;
        rv = soc_th_alpm_128_lpm_delete(u, &lpm_entry);
        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);
        if (shuffled) {
            *shuffled = 1;
        }

        /* Destroy child pivot from trie */
        doing = _MERGE_CHILD_PIVOT_DESTROYED;
        rv = _soc_th_alpm_128_split_pivot_create_undo
                    (u, v6, child_vrf, child_pivot->key, child_pivot->len, NULL, 0);

        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);
    }

    /* Update hit bits */
    rv = soc_th_alpm_hit_bits_update(u, pfx_array, new_index, v6, vrf);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "update_hit_bits failed, count %d\n"),
                              pfx_array->count));
        rv = SOC_E_NONE;
    }

    /* Update TCAM mgmt info: set new logical bucket */
    if (merge_dir != MERGE_LOG_CHILD_TO_PARENT && ALPM_TCAM_PIVOT(u, pivot_idx_from)) {
        PIVOT_BUCKET_INDEX(ALPM_TCAM_PIVOT(u, pivot_idx_from)) = log_bkt_to;
    }

    soc_th_alpm_bucket_usage_decr(u, log_bkt_from, TRUE, vrf, mem, pfx_array->count, log_bkt_to);
    soc_th_alpm_bucket_usage_incr(u, log_bkt_to,
                                  (merge_dir == MERGE_LOG_CHILD_TO_PARENT) ?
                                  pivot_idx_to : pivot_idx_from,
                                  vrf, mem, pfx_array->count);

    /* Update new index */
    for (i = 0; i < pfx_array->count; i++) {
        pfx_array->prefix[i]->index = new_index[i];
    }

    _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);
    return rv;

_rollback:

    /* fall through on all cases */
    switch (done)  {
    case _MERGE_CHILD_LPM_DELETED:
        if (merge_dir != MERGE_PHY) {
            /* not expecting any failure after lpm deleted */
        }

    case _MERGE_CHILD_TRIE_MERGED:
        if (merge_dir != MERGE_PHY) {
            uint32      pivot[5], length;
            trie_split2(PIVOT_BUCKET_TRIE(parent_pivot),
                        child_pivot->key,
                        child_pivot->len,
                        pivot, &length,
                        &(PIVOT_BUCKET_TRIE(child_pivot)->trie),
                        PIVOT_BUCKET_COUNT(child_pivot), 1);
        }

    case _MERGE_INVALIDATE:
        _soc_th_alpm_128_bucket_inval_undo(u, mem, pfx_array, bufp, sip_bufp);

    case _MERGE_LPM_LINK:
        /* Connect TCAM back to original bucket */
        _soc_th_alpm_128_bucket_link(u, v6, pivot_idx_from, log_bkt_from);

    case _MERGE_COPY:
        /* Delete entries in new bucket */
        _soc_th_alpm_128_bucket_copy_undo(u, mem, pfx_array->count, new_index);

    case _MERGE_PREPARE:
        _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);

    case _MERGE_NONE:
    default:
        break;
    }

    /* Error dump */
    switch (doing)  {
    case _MERGE_LPM_LINK:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "_soc_th_alpm_128_bucket_link failed, pivot %d log_bkt %d\n"),
                              pivot_idx_from, log_bkt_to));
        break;

    case _MERGE_INVALIDATE:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "_soc_th_alpm_128_bucket_inval failed\n")));
        break;
    case _MERGE_CHILD_TRIE_MERGED:
        break;

    case _MERGE_CHILD_PIVOT_DESTROYED:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Pivot destroy fail, something not expected\n")));

    default:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Merge fails at step %d\n"), doing));
        break;
    }

    return rv;
}


int
_soc_th_alpm_128_lpm_free_entries(int u, int vrf)
{
    int curr_pfx, min_pfx;
    int total_fent = 0;

    curr_pfx = MAX_PFX_INDEX_128;
    min_pfx  = 0;
    if (ALPM_CTRL(u).gp_zoned) {
        if (vrf == (SOC_VRF_MAX(u) + 1)) { /* Global VRF */
            min_pfx  = MAX_VRF_PFX_INDEX_128 + 1;
        } else {
            curr_pfx = MAX_VRF_PFX_INDEX_128;
        }
    }
    while (curr_pfx >= min_pfx) {
        total_fent += SOC_ALPM_128_LPM_STATE_FENT(u, curr_pfx);
        curr_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx);
    }

    return total_fent;
}


/* Move partial entries from one logical bucket to another */
int
_soc_th_alpm_128_bucket_repartition(int u, soc_mem_t mem, int log_bkt_from,
                                    int log_bkt_to, int max_count,
                                    trie_node_t **new_trie,
                                    int *shuffled)
{
    trie_node_t             *split_trie_root = NULL;
    uint32                  length, bpm_len = 0;
    uint32                  pivot[5];
    uint32                  bpm[5] = {0};
    uint32                  src_discard, src_default;
    defip_pair_128_entry_t  lpm_entry;
    alpm_mem_prefix_array_t *pfx_array = NULL;
    int                     *new_index = NULL;
    int                     rv = SOC_E_NONE, i;
    int                     tcam_index, pivot_index;
    int                     pivot_idx_from, pivot_idx_to;
    int                     vrf = 0;
    void                    *bufp = NULL, *sip_bufp = NULL;
    int                     phy_bkt_from, sub_bkt_from, phy_bkt_to, sub_bkt_to;
    int                     max_split_count;
    alpm_pivot_t            *new_pivot, *parent_pivot, *child_pivot;
    int                     v6 = L3_DEFIP_MODE_128;
    enum {
        _REPART_TRIE_NONE,
        _REPART_TRIE_SPLIT,
        _REPART_LPM_INIT,
        _REPART_PIVOT_CREATE,
        _REPART_PREPARE,
        _REPART_COPY,
        _REPART_LPM_INSERT,
        _REPART_INVALIDATE,
        _REPART_CHILD_TRIE_MERGED,
        _REPART_CHILD_LPM_DELETED,
        _REPART_CHILD_PIVOT_DESTROYED
    } doing = _REPART_TRIE_NONE, done = _REPART_TRIE_NONE;

    phy_bkt_from  = ALPM_PHY_BKT(u, log_bkt_from);
    sub_bkt_from  = ALPM_SUB_BKT(u, log_bkt_from);
    phy_bkt_to    = ALPM_PHY_BKT(u, log_bkt_to);
    sub_bkt_to    = ALPM_SUB_BKT(u, log_bkt_to);

    pivot_idx_from = SOC_ALPM_BU_PIVOT_IDX(u, phy_bkt_from, sub_bkt_from);
    pivot_idx_to   = SOC_ALPM_BU_PIVOT_IDX(u, phy_bkt_to, sub_bkt_to);

    parent_pivot = ALPM_TCAM_PIVOT(u, pivot_idx_from);
    child_pivot  = ALPM_TCAM_PIVOT(u, pivot_idx_to);

    max_split_count = max_count - SOC_ALPM_BU_COUNT(u, phy_bkt_to);
    if (max_split_count == 0) {
        return SOC_E_NONE;
    }

    doing = _REPART_TRIE_SPLIT;
    rv = trie_split2(PIVOT_BUCKET_TRIE(parent_pivot),
                     child_pivot->key,
                     child_pivot->len,
                     pivot, &length,
                     &split_trie_root,
                     max_split_count, 0);
    if (SOC_FAILURE(rv)) {
        /* Non repartable is nothing fatal, just return and keep searching */
        if (rv == SOC_E_NOT_FOUND) {
            rv = SOC_E_NONE;
        }
        /* Must return */
        return rv;
    }
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    vrf = PIVOT_BUCKET_VRF(ALPM_TCAM_PIVOT(u, pivot_idx_from));
    doing = _REPART_LPM_INIT;
    rv = _soc_th_alpm_128_split_lpm_init(u, pivot_idx_from,
                                         vrf, log_bkt_to, NULL, NULL,
                                         pivot, length, &lpm_entry, &bpm_len, bpm,
                                         &src_discard, &src_default);

    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);


    doing = _REPART_PIVOT_CREATE;
    rv = _soc_th_alpm_128_split_pivot_create(u, v6, vrf, log_bkt_to,
                                             split_trie_root, pivot, length,
                                             bpm_len, bpm, &new_pivot);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _REPART_PREPARE;
    rv = _soc_th_alpm_128_bucket_prepare(u, mem, PIVOT_BUCKET_TRIE(new_pivot),
                                         &pfx_array, &bufp, &sip_bufp, &new_index);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _REPART_COPY;
    rv = _soc_th_alpm_128_bucket_copy(u, mem, vrf, pfx_array,
                                      log_bkt_to, bufp, sip_bufp,
                                      NULL, NULL, new_index, NULL);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _REPART_LPM_INSERT;
    rv = soc_th_alpm_128_lpm_insert(u, &lpm_entry, &tcam_index, bpm_len,
                                    src_default, src_discard);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);
    if (shuffled) {
        *shuffled = 1;
    }

    /* TCAM index from lpm code is logical.  Convert to global idx */
    tcam_index = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, tcam_index, v6);

    pivot_index = SOC_ALPM_128_ADDR_LWR(u, tcam_index) << 1;;
    PIVOT_TCAM_INDEX(new_pivot)         = pivot_index;
    ALPM_TCAM_PIVOT(u, pivot_index)     = new_pivot;

    /* Invalide old entries */
    doing = _REPART_INVALIDATE;
    rv = _soc_th_alpm_128_bucket_inval(u, mem, pfx_array, bufp, sip_bufp);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* Delete old lpm entry */
    {
        uint32          hw_key[5] = {0};
        int             child_vrf;

        /* SW bucket merge: not expect to fail */
        doing = _REPART_CHILD_TRIE_MERGED;
        rv = trie_merge(PIVOT_BUCKET_TRIE(new_pivot),
                        PIVOT_BUCKET_TRIE(child_pivot)->trie,
                        child_pivot->key,
                        child_pivot->len);
        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

        sal_memcpy(hw_key, child_pivot->key, sizeof(hw_key));
        ALPM_TRIE_TO_NORMAL_IP_128(hw_key, child_pivot->len, v6);

        child_vrf = PIVOT_BUCKET_VRF(child_pivot);

        (void) _soc_th_alpm_128_lpm_ent_key_init(u, hw_key, child_pivot->len,
                                      child_vrf, v6, &lpm_entry, 1);

        doing = _REPART_CHILD_LPM_DELETED;
        rv = soc_th_alpm_128_lpm_delete(u, &lpm_entry);
        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

        pivot_index = PIVOT_TCAM_INDEX(new_pivot);

        /* Destroy child pivot */
        doing = _REPART_CHILD_PIVOT_DESTROYED;
        rv = _soc_th_alpm_128_split_pivot_create_undo
                    (u, v6, child_vrf, child_pivot->key, child_pivot->len, NULL, 0);

        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);
    }

    /* Update hit bits */
    rv = soc_th_alpm_hit_bits_update(u, pfx_array, new_index, v6, vrf);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "update_hit_bits failed, count %d\n"),
                              pfx_array->count));
        rv = SOC_E_NONE;
    }
    soc_th_alpm_bucket_usage_decr(u, log_bkt_from, FALSE, vrf, mem, pfx_array->count, log_bkt_to);
    soc_th_alpm_bucket_usage_incr(u, log_bkt_to, pivot_index, vrf, mem, pfx_array->count);

    /* Update new index */
    for (i = 0; i < pfx_array->count; i++) {
        pfx_array->prefix[i]->index = new_index[i];
    }

    _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);
    *new_trie = (trie_node_t *) new_pivot;

    return rv;

_rollback:
    /* fall through on all cases */
    switch (done)  {
    case _REPART_CHILD_LPM_DELETED:
        /* Not expect any failure after trie_merge */

    case _REPART_CHILD_TRIE_MERGED: {
            uint32      pivot2[5], length2;
            trie_split2(PIVOT_BUCKET_TRIE(parent_pivot),
                        child_pivot->key,
                        child_pivot->len,
                        pivot2, &length2,
                        &(PIVOT_BUCKET_TRIE(child_pivot)->trie),
                        PIVOT_BUCKET_COUNT(child_pivot), 1);
        }

    case _REPART_INVALIDATE:
        _soc_th_alpm_128_bucket_inval_undo(u, mem, pfx_array, bufp, sip_bufp);

    case _REPART_LPM_INSERT:
        soc_th_alpm_128_lpm_delete(u, &lpm_entry);

    case _REPART_COPY:
        /* Delete entries in new bucket */
        _soc_th_alpm_128_bucket_copy_undo(u, mem, pfx_array->count, new_index);

    case _REPART_PREPARE:
        _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);

    case _REPART_PIVOT_CREATE:
        _soc_th_alpm_128_split_pivot_create_undo(u, v6, vrf, pivot, length, NULL, 0);


    case _REPART_LPM_INIT:
        /* nothing to undo */

    case _REPART_TRIE_SPLIT:
        trie_merge(PIVOT_BUCKET_TRIE(parent_pivot), split_trie_root, pivot, length);
    default:
        break;
    }

    LOG_ERROR(BSL_LS_SOC_ALPM,
              (BSL_META_U(u,
                          "Repartition fails at step %d\n"), doing));

    return rv;
}

static int
_soc_th_alpm_128_bucket_split(int u, alpm_pfx_info_t *pfx_info, int *index_ptr)
{
    trie_node_t             *split_trie_root;
    uint32                  e[SOC_MAX_MEM_FIELD_WORDS];
    uint32                  length, bpm_len = 0;
    uint32                  bank_disable = 0;
    uint32                  pivot[5] = {0};
    uint32                  bpm[5] = {0};
    uint32                  src_discard, src_default;
    int                     key_index, i;
    trie_t                  *bkt_trie;
    defip_pair_128_entry_t  lpm_entry;
    alpm_mem_prefix_array_t *pfx_array = NULL;
    int                     *new_index = NULL;
    int                     rv = SOC_E_NONE, new_index_pos = -1;
    int                     tcam_index, pivot_index;
    void                    *bufp = NULL, *sip_bufp = NULL;
    int                     max_split_count;
    alpm_pivot_t            *new_pivot = NULL;
    int                     v6 = L3_DEFIP_MODE_128;
    int                     max_split_length = 128 - 1;

    enum {
        _SPLIT_TRIE_NONE,
        _SPLIT_TRIE_SPLIT,
        _SPLIT_LPM_INIT,
        _SPLIT_PIVOT_CREATE,
        _SPLIT_PREPARE,
        _SPLIT_COPY,
        _SPLIT_LPM_INSERT,
        _SPLIT_INVALIDATE
    } doing = _SPLIT_TRIE_NONE, done = _SPLIT_TRIE_NONE;

    bkt_trie = PIVOT_BUCKET_TRIE(ALPM_TCAM_PIVOT(u, pfx_info->pivot_idx_from));

    /* If free space is less than a single bucket capacity (start
     * using sub bucket 1..., )
     * We need to limit the split_trie_root payload count
     */
    max_split_count = _soc_th_alpm_bkt_entry_cnt(u, pfx_info->mem) -
                      SOC_ALPM_BU_COUNT(u, ALPM_PHY_BKT(u, pfx_info->log_bkt_to));

    doing = _SPLIT_TRIE_SPLIT;
    rv = trie_split(bkt_trie, max_split_length, FALSE,
                    pivot, &length, &split_trie_root, NULL, FALSE, max_split_count);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    if (length > max_split_length) {
        rv = SOC_E_FULL;
        _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);
    }

    doing = _SPLIT_LPM_INIT;
    rv = _soc_th_alpm_128_split_lpm_init(u,
                                         pfx_info->pivot_idx_from,
                                         pfx_info->vrf,
                                         pfx_info->log_bkt_to,
                                         pfx_info->alpm_data,
                                         pfx_info->alpm_sip_data,
                                         pivot, length,
                                         &lpm_entry, &bpm_len, bpm,
                                         &src_discard, &src_default);

    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* this must be after lpm_init , because it needs the bpm */
    doing = _SPLIT_PIVOT_CREATE;
    rv = _soc_th_alpm_128_split_pivot_create(u, v6, pfx_info->vrf, pfx_info->log_bkt_to,
                                             split_trie_root, pivot, length, bpm_len, bpm, &new_pivot);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _SPLIT_PREPARE;
    rv = _soc_th_alpm_128_bucket_prepare(u, pfx_info->mem, PIVOT_BUCKET_TRIE(new_pivot),
                                          &pfx_array, &bufp, &sip_bufp, &new_index);

    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _SPLIT_COPY;
    rv = _soc_th_alpm_128_bucket_copy(u, pfx_info->mem, pfx_info->vrf, pfx_array, pfx_info->log_bkt_to,
                                       bufp, sip_bufp, pfx_info->alpm_data,
                                       pfx_info->alpm_sip_data, new_index, &new_index_pos);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    doing = _SPLIT_LPM_INSERT;
    rv = soc_th_alpm_128_lpm_insert(u, &lpm_entry, &tcam_index, bpm_len,
                                   src_default, src_discard);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* TCAM index from lpm code is logical.  Convert to global idx */
    tcam_index = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, tcam_index, v6);

    pivot_index = SOC_ALPM_128_ADDR_LWR(u, tcam_index) << 1;;
    PIVOT_TCAM_INDEX(new_pivot)         = pivot_index;
    ALPM_TCAM_PIVOT(u, pivot_index)     = new_pivot;

    doing = _SPLIT_INVALIDATE;
    rv = _soc_th_alpm_128_bucket_inval(u, pfx_info->mem, pfx_array, bufp, sip_bufp);
    _ALPM_IF_ERROR_GOTO(rv, _rollback, done, doing);

    /* Don't try rollback from here on, since split is successful. */
    rv = soc_th_alpm_hit_bits_update(u, pfx_array, new_index, v6, pfx_info->vrf);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "update_hit_bits failed, count %d\n"),
                              pfx_array->count));
        rv = SOC_E_NONE;
    }

    if (new_index_pos != -1) { /* New prefix goes to new split bucket */
        *index_ptr = new_index[new_index_pos];
    } else { /* To old parent bucket, do actual insert */
        /* Add Entry to old bucket RAM */
        if (ALPM_CTRL(u).bkt_sharing) {
            soc_mem_field32_set(u, pfx_info->mem, pfx_info->alpm_data, SUB_BKT_PTRf,
                                ALPM_SUB_BKT(u, pfx_info->log_bkt_from));
        }
        /* entry shouldn't exist, insert the entry into the RAM */
        bank_disable =
            ALPM_CTRL(u).bank_disable_bmp[pfx_info->vrf != SOC_VRF_MAX(u) + 1];
        rv = _soc_th_alpm_insert_in_bkt(u, pfx_info->mem, pfx_info->log_bkt_from,
                                        bank_disable, pfx_info->alpm_data, pfx_info->alpm_sip_data,
                                        e, &key_index, v6);

        if (SOC_FAILURE(rv)) {
            /* recover by matching trie state to h/w state */
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u, "Could not insert new "
                                  "prefix into trie after split\n")));
            /* since split was successful, leave split state as-is */
            pfx_info->log_bkt_to = -1;
            return rv;
        }

        *index_ptr = key_index;
    }

    /* Update old bucket usage */
    soc_th_alpm_bucket_usage_decr(u, pfx_info->log_bkt_from, FALSE, pfx_info->vrf, pfx_info->mem, pfx_array->count - 1, pfx_info->log_bkt_to);
    /* Update new bucket usage */
    soc_th_alpm_bucket_usage_incr(u, pfx_info->log_bkt_to, pivot_index, pfx_info->vrf, pfx_info->mem, pfx_array->count);

    PIVOT_BUCKET_ENT_CNT_UPDATE(new_pivot);
    VRF_BUCKET_SPLIT_INC(u, pfx_info->vrf, v6);

    /* Update new index */
    for (i = 0; i < pfx_array->count; i++) {
        pfx_array->prefix[i]->index = new_index[i];
    }

    _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);
    return rv;

_rollback:
    /* fall through on all cases */
    switch (done)  {
    case _SPLIT_LPM_INSERT:
        soc_th_alpm_128_lpm_delete(u, &lpm_entry);

    case _SPLIT_COPY:
        /* Delete entries in new bucket */
        _soc_th_alpm_128_bucket_copy_undo(u, pfx_info->mem, pfx_array->count, new_index);

    case _SPLIT_PREPARE:
        _soc_th_alpm_128_bucket_prepare_undo(u, &pfx_array, &bufp, &sip_bufp, &new_index);

    case _SPLIT_PIVOT_CREATE:
        _soc_th_alpm_128_split_pivot_create_undo(u, v6, pfx_info->vrf, pivot, length, NULL, 0);

    case _SPLIT_LPM_INIT:
        /* nothing to undo */
    case _SPLIT_TRIE_SPLIT:
        trie_merge(bkt_trie, split_trie_root, pivot, length);

    case _SPLIT_TRIE_NONE:
    default:
        /* nothing to rollback for first step */
        break;
    }

    switch (doing) {
    case _SPLIT_TRIE_SPLIT:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Could not split bucket")));
        break;

    case _SPLIT_PIVOT_CREATE:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u, "failed to insert into pivot bkt_trie\n")));
        break;

    case _SPLIT_LPM_INSERT:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Unable to add new pivot to tcam\n")));

        if (rv == SOC_E_FULL) {
            VRF_PIVOT_FULL_INC(u, pfx_info->vrf, v6);
        }
        break;
    default:
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "Split fails at step %d\n"), doing));
        break;
    }

    return rv;
}


/*
 * Insert entry into ALPM database.
 * Returns SOC_E_NONE, if found and updated.
 * SOC_E_FAIL, if insert failed.
 */
static int
_soc_th_alpm_128_insert(int u,
                        void *key_data,  /* TCAM entry data */
                        soc_mem_t mem,   /* Mem view for ALPM data */
                        void *alpm_data, /* Alpm data to be updated with */
                        void *alpm_sip_data,
                        int *index_ptr,
                        int log_bkt,
                        int tcam_index)  /* return key location */
{
    alpm_pivot_t *old_pivot;
    defip_aux_scratch_entry_t aux_entry;
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    uint32      prefix[5], length;
    int         v6, vrf, vrf_id;
    int         key_index;
    int         rv = SOC_E_NONE;
    uint32      db_type, ent_type, bank_disable;
    int         hit = 0;
    int         free_count, old_count;
    int         split = 0;
    trie_t      *bkt_trie = NULL , *pfx_trie = NULL;
    trie_node_t *lpmp = NULL, *lpmp2 = NULL;
    payload_t   *bkt_payload = NULL, *pfx_payload = NULL, *tmp_pyld;
    int default_route = 0;
    /* Search Result buffers */
    alpm_pfx_info_t pfx_info;
    int         new_log_bkt = -1;
    int         bkt_trie_inserted = 0, pfx_trie_inserted = 0;
    int         shuffled = 0, aux_flags = 0;

    v6 = L3_DEFIP_MODE_128;
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, key_data, &vrf_id, &vrf));
    bank_disable = ALPM_CTRL(u).bank_disable_bmp[vrf != SOC_VRF_MAX(u) + 1];
    soc_alpm_db_ent_type_encoding(u, vrf, &db_type, &ent_type);

    /* Get table memory. */
    SOC_ALPM_TABLE_MEM_128(u, v6, mem);

    /* Insert the prefix into the bucket trie, whether the insert was
     * successul or resulted in Split. Spliting the trie after insertion
     * yeilds better pivot and better split.
     */
    /* Create Prefix */
    rv = _soc_th_alpm_128_prefix_create(u, key_data, prefix, &length,
                                        &default_route);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(u, "_soc_th_alpm_128_insert: prefix create failed\n")));
        return rv;
    }
    /* Fill in AUX Scratch and perform PREFIX Operation */
    sal_memset(&aux_entry, 0, sizeof(defip_aux_scratch_entry_t));
    SOC_IF_ERROR_RETURN(
       _soc_th_alpm_128_fill_aux_entry_for_op(u, key_data, v6, db_type,
                    ent_type, 0, &aux_entry));
    /* we need to do sw pivot find again, or we may miss sub_bkt info */
    if (log_bkt == 0) {
        if (ALPM_CTRL(u).sw_prefix_lkup) {
            rv = _soc_th_alpm_128_sw_pivot_find(u, prefix, length, v6, vrf, &hit,
                                            &tcam_index, &log_bkt);
        } else {
            rv = _soc_th_alpm_aux_op(u, PREFIX_LOOKUP, &aux_entry, TRUE, &hit,
                                     &tcam_index, &log_bkt, 0);
        }
        SOC_IF_ERROR_RETURN(rv);
        if (ALPM_CTRL(u).bkt_sharing) {
            soc_mem_field32_set(u, mem, alpm_data, SUB_BKT_PTRf,
                                ALPM_SUB_BKT(u, log_bkt));
        }
    }

    /* entry shouldn't exist, insert the entry into the RAM */
    rv = _soc_th_alpm_insert_in_bkt(u, mem, log_bkt,
                                    bank_disable, alpm_data, alpm_sip_data,
                                    e, &key_index, v6);

    old_pivot = ALPM_TCAM_PIVOT(u, tcam_index);

    if (rv == SOC_E_NONE) {
        *index_ptr = key_index;
    } else if (rv == SOC_E_FULL) {
        old_count = PIVOT_BUCKET_COUNT(old_pivot);
        rv = soc_th_alpm_assign(u, vrf, mem, &new_log_bkt,
                                &shuffled, &free_count);
        SOC_IF_ERROR_RETURN(rv);

        if (shuffled) {
            if (ALPM_CTRL(u).sw_prefix_lkup) {
                rv = _soc_th_alpm_128_sw_pivot_find(u, prefix, length, v6, vrf, &hit,
                                                &tcam_index, &log_bkt);
            } else {
                rv = _soc_th_alpm_aux_op(u, PREFIX_LOOKUP, &aux_entry, TRUE, &hit,
                                         &tcam_index, &log_bkt, 0);
            }
            SOC_IF_ERROR_RETURN(rv);
            if (ALPM_CTRL(u).bkt_sharing) {
                soc_mem_field32_set(u, mem, alpm_data, SUB_BKT_PTRf,
                                    ALPM_SUB_BKT(u, log_bkt));
            }

            old_pivot = ALPM_TCAM_PIVOT(u, tcam_index);
            old_count = PIVOT_BUCKET_COUNT(old_pivot);
        }

        if (PIVOT_BUCKET_TRIE(old_pivot)->trie == NULL ||
            ((old_count + 1) <= free_count &&
             _soc_th_alpm_128_lpm_free_entries(u, vrf) == 0)) { /* find a new home*/

            rv = _soc_th_alpm_128_bucket_merge(u, mem, log_bkt, new_log_bkt, MERGE_PHY, NULL);
            if (SOC_FAILURE(rv)) {
                soc_th_alpm_bucket_release(u, new_log_bkt, vrf, v6);
                return rv;
            }
            log_bkt = new_log_bkt;
            if (ALPM_CTRL(u).bkt_sharing) {
                soc_mem_field32_set(u, mem, alpm_data, SUB_BKT_PTRf,
                                    ALPM_SUB_BKT(u, log_bkt));
            }
            /* entry shouldn't exist, insert the entry into the RAM */
            rv = _soc_th_alpm_insert_in_bkt(u, mem, log_bkt,
                                            bank_disable, alpm_data, alpm_sip_data,
                                            e, &key_index, v6);
            if (SOC_SUCCESS(rv)) {
                *index_ptr = key_index;
                /* if necessary insert SRC entry */
            } else {
                return rv;
            }
        } else {
            split = 1;
            /* this indicates a new route, which will be used to decide
             * if the new route happens to be new pivot.
             */
            key_index = -1;
        }
    } else {
        return rv;
    }

    /* Allocate Payload */
    bkt_payload = sal_alloc(sizeof(payload_t), "Payload for 128b Key");
    if (bkt_payload == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(u,
                 "Unable to allocate memory for "
                  "bkt_trie node \n")));
        rv = SOC_E_MEMORY;
        goto _rollback;
    }
    pfx_payload = sal_alloc(sizeof(payload_t), "Payload for pfx trie 128b key");
    if (pfx_payload == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                   "Unable to allocate memory for "
                  "pfx trie node \n")));
        rv = SOC_E_MEMORY;
        goto _rollback;
    }
    sal_memset(bkt_payload, 0, sizeof(*bkt_payload));
    sal_memset(pfx_payload, 0, sizeof(*pfx_payload));
    sal_memcpy(bkt_payload->key, prefix, sizeof(prefix));
    bkt_payload->len    = length;
    /* Needs update for split case, updated below */
    bkt_payload->index  = key_index;
    /* create duplicate for prefix bkt_trie */
    sal_memcpy(pfx_payload, bkt_payload, sizeof(*bkt_payload));
    pfx_payload->bkt_ptr = bkt_payload;

    /* Insert the prefix */
    /* bucket trie insert */
    bkt_trie = PIVOT_BUCKET_TRIE(old_pivot);
    rv = trie_insert(bkt_trie, prefix, NULL, length, (trie_node_t *)bkt_payload);
    if (SOC_SUCCESS(rv)) {
        bkt_trie_inserted = 1;
    } else {
        goto _rollback;
    }

    /* prefix trie insert */
    pfx_trie = VRF_PREFIX_TRIE_IPV6_128(u, vrf);
    if (!default_route) {
        uint32 bpm[5] = {0};
        _soc_th_alpm_mask_prefix_create(u, v6, length, bpm);
        /* default route already in trie */
        rv = trie_insert(pfx_trie, prefix,
                         ALPM_CTRL(u).trie_propagate ? bpm : NULL,
                         length, (trie_node_t *)pfx_payload);
        if (SOC_SUCCESS(rv)) {
            pfx_trie_inserted = 1;
        }
    } else {
        /* update the default route */
        lpmp = NULL;
        rv = trie_find_lpm(pfx_trie, 0, 0, &lpmp);
        tmp_pyld = (payload_t *) lpmp;
        if (SOC_SUCCESS(rv)) {
            tmp_pyld->bkt_ptr = bkt_payload;
        }
    }
    if (SOC_FAILURE(rv)) {
        goto _rollback;
    }

    /* Performs lazy splitting */
    if (split) {
        pfx_info.pivot_idx_from   = tcam_index;
        pfx_info.alpm_data        = alpm_data;
        pfx_info.alpm_sip_data    = alpm_sip_data;
        pfx_info.log_bkt_from     = log_bkt;
        pfx_info.log_bkt_to       = new_log_bkt;
        pfx_info.vrf              = vrf;
        pfx_info.mem              = mem;
        rv = _soc_th_alpm_128_bucket_split(u, &pfx_info, index_ptr);
        if (rv != SOC_E_NONE) {
            new_log_bkt = pfx_info.log_bkt_to;
            goto _rollback;
        }
        bkt_payload->index  = *index_ptr;
        /* New Pivot */
        _alpm_dbg_cntr[u].bkt_split++;
    } else {
        /* Insert successfully, update bkt usage */
        soc_th_alpm_bucket_usage_incr(u, log_bkt, tcam_index, vrf, mem, 1);
    }

    /* from here on, we don't expect any failure */

    /* propagate the insertion */
    if (default_route) {
        /* also free unused pfx_payload pointer */
        sal_free(pfx_payload);
    }
    /* do insert propagation to update existing default datas */
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry, ALG_HIT_IDXf,
                        *index_ptr);
    if (SOC_URPF_STATUS_GET(u)) {
        if (soc_mem_field32_get(u, mem, alpm_sip_data, DEFAULTROUTEf)) {
            aux_flags |= SOC_ALPM_AUX_DEF_ROUTE;
        }
        if (soc_mem_field32_get(u, mem, alpm_sip_data, SRC_DISCARDf)) {
            aux_flags |= SOC_ALPM_AUX_SRC_DISCARD;
        }
    }

   SOC_IF_ERROR_RETURN(_soc_th_alpm_aux_op(u, INSERT_PROPAGATE, &aux_entry,
                            TRUE, &hit, &tcam_index, &log_bkt, aux_flags));

    /* For debug, update the old pivot's counter */
    PIVOT_BUCKET_ENT_CNT_UPDATE(old_pivot);
    return rv;

_rollback:
    if (!default_route && pfx_trie_inserted) {
        (void)trie_delete(pfx_trie, prefix, length, &lpmp);
    }

    if (bkt_trie_inserted) {
        (void)trie_delete(bkt_trie, prefix, length, &lpmp2);
    }

    if (pfx_payload) {
        sal_free(pfx_payload);
    }

    if (bkt_payload) {
        sal_free(bkt_payload);
    }

    if (split && new_log_bkt != -1) {
        /* for non-split case, the new logical bucket is taking effect and thus
         * should not be released
         */
         (void)soc_th_alpm_bucket_release(u, new_log_bkt, vrf, v6);
    }
    return rv;
}

/* Build an LPM entry, from a key */
/* Mostly used for the match */
static int
_soc_th_alpm_128_lpm_ent_key_init(int u, uint32 *addr, int len, int vrf, int ipv6,
                                    defip_pair_128_entry_t *lpm_entry, int init)
{
    uint32 tmp;

    /* Zero buffers. */
    if (init) {
        sal_memset(lpm_entry, 0, sizeof(defip_pair_128_entry_t));
    }

    if (SOC_MEM_FIELD_VALID(u, L3_DEFIP_PAIR_128m, DWf)) {
        soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, DWf, 1);
    }

    /* and with mask to ensure global vrf gets set to 0 */
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VRF_ID_0_LWRf,
                            vrf & SOC_VRF_MAX(u));
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VRF_ID_1_LWRf,
                            vrf & SOC_VRF_MAX(u));
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VRF_ID_0_UPRf,
                            vrf & SOC_VRF_MAX(u));
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VRF_ID_1_UPRf,
                            vrf & SOC_VRF_MAX(u));

    if (vrf == (SOC_VRF_MAX(u) + 1)) {
        tmp = 0;
        /* for global routes */
    } else {
        tmp = SOC_VRF_MAX(u);
    }
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK0_LWRf, tmp);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK1_LWRf, tmp);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK0_UPRf, tmp);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK1_UPRf, tmp);

    /* Set address to the buffer. */
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            IP_ADDR0_LWRf, addr[0]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            IP_ADDR1_LWRf, addr[1]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            IP_ADDR0_UPRf, addr[2]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            IP_ADDR1_UPRf, addr[3]);

    /* Set mode to ipv6-128 */
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE0_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE1_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE0_UPR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE1_UPR_f(u), 3);

    _soc_th_alpm_128_pfx_len_to_mask(u, (void *)lpm_entry, len);

    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VALID0_LWRf, 1);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VALID1_LWRf, 1);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VALID0_UPRf, 1);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VALID1_UPRf, 1);

    /* Set Mode Masks */
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE_MASK0_LWR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        MODE_MASK0_LWR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE_MASK1_LWR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        MODE_MASK1_LWR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE_MASK0_UPR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        MODE_MASK0_UPR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE_MASK1_UPR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        MODE_MASK1_UPR_f(u))) - 1);

    /* Set Entry Type Masks */
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK0_LWR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        ENTRY_TYPE_MASK0_LWR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK1_LWR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        ENTRY_TYPE_MASK1_LWR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK0_UPR_f(u),
                       (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        ENTRY_TYPE_MASK0_UPR_f(u))) - 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK1_UPR_f(u),
                        (1 << soc_mem_field_length(u, L3_DEFIP_PAIR_128m,
                        ENTRY_TYPE_MASK1_UPR_f(u))) - 1);
    return (SOC_E_NONE);
}


#ifdef CHECK_CLEAN_BKT
static int
_soc_th_alpm_128_bkt_count(int u, soc_mem_t mem, int is_log_bkt, int bkt, int vrf, void *bufp)
{
    int bank_num;
    int entry_num;
    int bank_count;
    int bank_bits;
    int alpm_bkt_bits = ALPM_CTRL(u).bkt_bits;
    int bkt_count;
    int phy_bkt;
    int sub_bkt;
    int addr;
    int rv;
    int entry_count = 2;
    uint32 bank_disable;
    int count = 0;

    if (is_log_bkt) {
        phy_bkt = ALPM_PHY_BKT(u, bkt);
        sub_bkt = ALPM_SUB_BKT(u, bkt);
    } else {
        phy_bkt = bkt;
        sub_bkt = -1;
    }

    bank_disable = ALPM_CTRL(u).bank_disable_bmp_8b[vrf != SOC_VRF_MAX(u) + 1];
    bank_count  = soc_alpm_cmn_banks_get(u);
    bank_bits   = (bank_count + 1) / 2;

    ALPM_FIRST_AVAIL_BANK(bank_num, bank_count, bank_disable);


    bkt_count   = _soc_th_alpm_bkt_entry_cnt(u, mem);
    entry_num   = 0;
    while (bkt_count--) {
        addr = (entry_num << (bank_bits + alpm_bkt_bits)) |
               (phy_bkt << bank_bits) |
               (bank_num & ((1U << bank_bits) - 1));
        entry_num++;
        if (entry_num == entry_count) {
            entry_num = 0;
            ALPM_NEXT_AVAIL_BANK(bank_num, bank_count, bank_disable);
            if (bank_num == bank_count) {
                ALPM_FIRST_AVAIL_BANK(bank_num, bank_count, bank_disable);
                phy_bkt ++;
            }
        }

        rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY, addr, bufp);
        SOC_IF_ERROR_RETURN(rv); /* If fail, the rv < 0, and check also fails */

        if (sub_bkt != -1 && sub_bkt !=
            soc_mem_field32_get(u, mem, bufp, SUB_BKT_PTRf)) {
            continue;
        }

        if (soc_mem_field32_get(u, mem, bufp, VALIDf)) {
            LOG_CLI(("mem %s bkt %d vrf %d bank_disable %d bkt_count %d "
                     "entry_num %d, bank_num %d, addr %d\n",
                     SOC_MEM_NAME(u, mem), bkt, vrf, bank_disable, bkt_count,
                     entry_num, bank_num, addr));
            count++;
        }
    }

    return count;
}
#endif /* CHECK_CLEAN_BKT */

/*
 * Delete entry from ALPM database.
 * Returns SOC_E_NONE, if found and updated.
 * SOC_E_FAIL, if insert failed.
 * If default route replace with internal default
 */
static int
_soc_th_alpm_128_delete(int u,
                    void *key_data, int vrf_id, int vrf, int log_bkt,
                    int tcam_index, int key_index)  /* TCAM entry data */
{
    alpm_pivot_t *pivot_pyld;
    /* Search Result buffer */
    defip_alpm_ipv6_128_entry_t alpmv6_entry, alpmv62, alpmv6_sip_entry;
    defip_aux_scratch_entry_t aux_entry;
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    soc_mem_t mem;
    void      *bufp, *bufp2, *sip_bufp = NULL;
    int       rv = SOC_E_NONE, rv2 = SOC_E_NONE;
    uint32    prop_pfx[5], prefix[5], bpm[5];
    int       v6;
    uint32    length;
    int       delete_log_bkt, delete_phy_bkt;
    uint32    db_type, ent_type, bank_disable;
    int       hit, default_route = 0;
    trie_t    *trie, *pfx_trie;
    uint32    bpm_pfx_len;
    defip_pair_128_entry_t lpm_entry, *lpm_key;
    payload_t *payload = NULL, *pfx_pyld = NULL, *tmp_pyld = NULL;
    trie_node_t *delp = NULL, *lpmp = NULL;
    trie_t    *pivot_trie = NULL;
    int       empty_bucket, aux_flags = 0;

    v6 = L3_DEFIP_MODE_128;

    /* For VRF_OVERRIDE (Global High) entries, software needs to maintain the
     * index, Prefix resides in TCAM directly. Handling of these functions are
     * taken care by main insert */
    if (!(ALPM_PREFIX_IN_TCAM(u, vrf_id))) {
        bank_disable = ALPM_CTRL(u).bank_disable_bmp[vrf != SOC_VRF_MAX(u) + 1];
        soc_alpm_db_ent_type_encoding(u, vrf, &db_type, &ent_type);
        /* Create Prefix */
        rv = _soc_th_alpm_128_prefix_create(u, key_data, prefix, &length,
                                            &default_route);

        if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                  "_soc_alpm_128_delete: prefix create failed\n")));
            return rv;
        }
        if (ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_COMBINED) {
            if (vrf_id != SOC_L3_VRF_GLOBAL) {
                /* allow default deletion only at end */
                if (VRF_TRIE_ROUTES_CNT(u, vrf_id, vrf, v6) > 1) {
                    if (default_route) {
                        LOG_ERROR(BSL_LS_SOC_ALPM,
                                  (BSL_META_U(u,
                                        "VRF %d: Cannot v6-128 delete "
                                        "default route if other routes are present "
                                        "in this mode\n"), vrf));
                        return SOC_E_PARAM;
                    }
                }
            }
        }

        /* Get table memory. */
        SOC_ALPM_TABLE_MEM_128(u, v6, mem);

        /* Assign entry buf based on table being used */
        SOC_ALPM_ENTRY_BUF_128(v6, mem, bufp, alpmv4_entry, alpmv6_entry);

        SOC_ALPM_LPM_LOCK(u);

        if (log_bkt == 0) {
            /* Search the entry */
            rv = _soc_th_alpm_128_find(u, mem, key_data, vrf_id, vrf, bufp,
                                       &tcam_index, &log_bkt, &key_index, TRUE);
        } else {
            rv = _soc_th_alpm_128_mem_ent_init(u, key_data, bufp, 0, mem, 0, 0,
                                               log_bkt);
        }

        /* save results as they are lost later */
        sal_memcpy(&alpmv62, bufp, sizeof(alpmv62));
        
        bufp2 = &alpmv62;

        if (SOC_FAILURE(rv)) {
            SOC_ALPM_LPM_UNLOCK(u);
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_alpm_128_delete: Unable to find "
                          "prefix for delete\n")));
            return rv;
        }

        /* Entry found
         * 1> Delete entry from trie
         * 2> Find Best Prefix Match
         * 3> Update bpm using replacement prefix op
         * 4> Invalidate Entry in the ALPM database
         */
        /* Delete the prefix from trie*/
        /* Store index to invalidate the prefix */
        delete_log_bkt = log_bkt;

        pivot_pyld = ALPM_TCAM_PIVOT(u, tcam_index);
        trie = PIVOT_BUCKET_TRIE(pivot_pyld);

        rv = trie_delete(trie, prefix, length,  &delp);
        payload = (payload_t *) delp;
        if (rv != SOC_E_NONE) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_alpm_128_delete: Error prefix not "
                          "present in trie \n")));
            SOC_ALPM_LPM_UNLOCK(u);
            return rv;
        }

        /* prefix trie delete */
        pfx_trie = VRF_PREFIX_TRIE_IPV6_128(u, vrf);
        pivot_trie = VRF_PIVOT_TRIE_IPV6_128(u, vrf);

        if (!default_route) {
            rv = trie_delete(pfx_trie, prefix, length, &delp);
            pfx_pyld = (payload_t *) delp;

            if (SOC_FAILURE(rv)) {
                /* continue anyway to minimize state mismatch */
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_th_alpm_128_delete: Prefix not present "
                          "in pfx trie: 0x%08x 0x%08x 0x%08x 0x%08x\n"),
                           prefix[1], prefix[2], prefix[3], prefix[4]));
                goto recover_bkt_trie;
            }

            /* Find Best prefix match for the prefix */
            lpmp = NULL;
            rv = trie_find_lpm(pfx_trie, prefix, length, &lpmp);
            tmp_pyld = (payload_t *) lpmp;
            if (SOC_SUCCESS(rv)) {
                payload_t *t = (payload_t *)(tmp_pyld->bkt_ptr);
                if (t != NULL) {
                    /* this means a real default route exists */
                    bpm_pfx_len = t->len;
                } else {
                    /* only internal default route exists */
                    /* this should happen only if the lpm is a default route */
                    bpm_pfx_len = 0;
                }
            } else {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                            "_soc_th_alpm_128_delete: Could not find"
                            " replacement bpm for prefix: 0x%08x 0x%08x "
                            "0x%08x 0x%08x\n"), prefix[1], prefix[2],
                            prefix[3], prefix[4]));
                goto recover_pfx_trie;
            }

            /* Initialize an lpm enty to perform a match */
            /* not expected to fail */
            sal_memcpy(prop_pfx, prefix, sizeof(prefix));
            ALPM_TRIE_TO_NORMAL_IP_128(prop_pfx, length, v6);
            rv = _soc_th_alpm_128_lpm_ent_key_init(u, prop_pfx, bpm_pfx_len, vrf, v6,
                                                     &lpm_entry, 1);

            /* Find Associated data for the bpm */
            rv2 = _soc_th_alpm_128_find(u, mem, &lpm_entry, vrf_id, vrf, bufp,
                                        &tcam_index, &log_bkt, &key_index, TRUE);
            if (rv2 < 0) {
                if (vrf_id != SOC_L3_VRF_GLOBAL &&
                    ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_COMBINED) {
                    LOG_ERROR(BSL_LS_SOC_ALPM,
                            (BSL_META_U(u,
                            "Find128 associated data for next bpm failed."
                            "prefix: 0x%08x 0x%08x 0x%08x 0x%08x, length %d\n"),
                            prop_pfx[0], prop_pfx[1], prop_pfx[2], prop_pfx[3],
                            bpm_pfx_len));
                } else {
                    key_index = 0;
                }
            }

            /* convert associated data to lpm entry format */
            (void) _soc_th_alpm_128_lpm_ent_init(u, bufp, mem, v6, vrf_id,
                                                 log_bkt, 0, &lpm_entry, 0);

            /* set key to the prefix being deleted */
            (void) _soc_th_alpm_128_lpm_ent_key_init(u, prop_pfx, length, vrf, v6,
                                                &lpm_entry, 0);

            if (SOC_URPF_STATUS_GET(u)) {
                SOC_ALPM_ENTRY_BUF_128(v6, mem, sip_bufp, 0,
                        alpmv6_sip_entry);
                rv = _soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY,
                        _soc_alpm_rpf_entry(u, key_index), sip_bufp);
                if (soc_mem_field32_get(u, mem, sip_bufp, DEFAULTROUTEf)) {
                    aux_flags |= SOC_ALPM_AUX_DEF_ROUTE;
                }
                if (soc_mem_field32_get(u, mem, sip_bufp, SRC_DISCARDf)) {
                    aux_flags |= SOC_ALPM_AUX_SRC_DISCARD;
                }
            }

           if ((bpm_pfx_len == 0)  && SOC_FAILURE(rv2)) {
                /* could not find a default route. Use internal default */
                /* default route's associated data */
                lpm_key = VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf);
                sal_memcpy(&lpm_entry, lpm_key, sizeof(lpm_entry));
                /* copy key info over again */
                rv = _soc_th_alpm_128_lpm_ent_key_init(u, prop_pfx, length,
                                                       vrf, v6, &lpm_entry, 0);
            }
            if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                           "_soc_th_alpm_128_delete: Could not find "
                           "replacement prefix for prefix: 0x%08x 0x%08x 0x%08x "
                           "0x%08x\n"), prefix[1], prefix[2], prefix[3], prefix[4]));
                goto recover_pfx_trie;
            }

            lpm_key = &lpm_entry;
        } else { /* !default_route */
            /* remove the real default route reference if any */
            lpmp = NULL;
            rv = trie_find_lpm(pfx_trie, prefix, length, &lpmp);
            tmp_pyld = (payload_t *)lpmp;
            if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_th_alpm_128_delete: Could not find "
                          "default route in the trie for vrf %d\n"), vrf));
                goto recover_bkt_trie;
            }
            tmp_pyld->bkt_ptr = 0;
            bpm_pfx_len = 0;
            key_index = 0;
            lpm_key = VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf);
        }
        sal_memset(&aux_entry, 0, sizeof(defip_aux_scratch_entry_t));
        rv = _soc_th_alpm_128_fill_aux_entry_for_op(u, lpm_key, v6, db_type,
                                ent_type, bpm_pfx_len, &aux_entry);
        if (SOC_FAILURE(rv)) {
            goto recover_pfx_trie;
        }

        /* Perform Delete propagate */
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry, ALG_HIT_IDXf,
                            ALPM_ENT_INDEX(key_index));
        rv = _soc_th_alpm_aux_op(u, DELETE_PROPAGATE, &aux_entry, TRUE, &hit,
                                 &tcam_index, &log_bkt, aux_flags);

        if (SOC_FAILURE(rv)) {
            goto recover_pfx_trie;
        }

        /* perform SIP delete propagate */
        if (0) {
            uint32 tmp;
            /* only SRC bits are different from DIP entry. Copy them over if
               internal default is not being used */
            soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                DB_TYPEf, db_type + 1);
            soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                ALG_HIT_IDXf, _soc_th_alpm_rpf_entry(u,
                                ALPM_ENT_INDEX(key_index)));
            tmp = soc_mem_field32_get(u, L3_DEFIP_AUX_SCRATCHm, &aux_entry,
                                      IP_LENGTHf);
            soc_mem_field32_set(u, mem, &aux_entry, DEFAULTROUTEf,
                                tmp == 0 ? 1 : 0);

            rv = _soc_th_alpm_aux_op(u, DELETE_PROPAGATE, &aux_entry, TRUE,
                                     &hit, &tcam_index, &log_bkt, 0);
            if (SOC_FAILURE(rv)) {
                goto recover_pfx_trie;
            }
        }

        /* From here on don't try to recover trie state */
        sal_free(payload);
        if (!default_route) {
            sal_free(pfx_pyld);
        }

        /* For debug, update the pivot's counter */
        PIVOT_BUCKET_ENT_CNT_UPDATE(pivot_pyld);

        empty_bucket = (pivot_pyld->len != 0) && (trie->trie == NULL);
        if (empty_bucket) { /* Empty bucket */
            uint32 hw_key[5];
            sal_memcpy(hw_key, pivot_pyld->key, sizeof(hw_key));
            ALPM_TRIE_TO_NORMAL_IP_128(hw_key, pivot_pyld->len, v6);

            /* Initialize an lpm entry to perform a match */
            _soc_th_alpm_128_lpm_ent_key_init(u, hw_key, pivot_pyld->len, vrf, v6,
                                         &lpm_entry, 1);

            /* delete entry from TCAM */
            rv = soc_th_alpm_128_lpm_delete(u, &lpm_entry);
            if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                           "_soc_th_alpm_128_delete: Unable to "
                           "delete pivot 0x%08x 0x%08x 0x%08x 0x%08x \n"),
                           pivot_pyld->key[1], pivot_pyld->key[2],
                           pivot_pyld->key[3], pivot_pyld->key[4]));
                /* continue to clean up still */
            }
        }

        /* Invalidate the route */
        delete_phy_bkt = ALPM_PHY_BKT(u, delete_log_bkt);
        rv = _soc_th_alpm_delete_in_bkt(u, mem, delete_phy_bkt, bank_disable,
                                        bufp2, e, &key_index, v6);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "_soc_th_alpm_128_delete_in_bkt: Unable to "
                                  "delete phy bkt 0x%08x \n"), delete_phy_bkt));
            SOC_ALPM_LPM_UNLOCK(u);
            return rv;
        }

        /* delete corresponding RPF entry if it exists */
        if (SOC_URPF_STATUS_GET(u)) {
            /* hit is an unused variable */
            delete_phy_bkt = SOC_TH_ALPM_RPF_BKT_IDX(u, delete_phy_bkt);
            rv = _soc_th_alpm_delete_in_bkt(u, mem, delete_phy_bkt, bank_disable,
                                            bufp2, e, &hit, v6);
            if (SOC_FAILURE(rv)) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                                      "_soc_th_alpm_128_delete_in_bkt: Unable to "
                                      "delete phy bkt 0x%08x \n"), delete_phy_bkt));
                SOC_ALPM_LPM_UNLOCK(u);
                return rv;
            }
        }

        /* Update bucket sharing bookeeping info */
        soc_th_alpm_bucket_usage_decr(u, PIVOT_BUCKET_INDEX(pivot_pyld), empty_bucket, vrf, mem, 1, 0);
        if (empty_bucket) { /* Empty bucket */

            /* remove pivot from pivot trie */
            rv = trie_delete(pivot_trie, pivot_pyld->key, pivot_pyld->len, &delp);
            if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "could not delete pivot from pivot trie\n")));
            }

            /* Free up Bucket trie */
            trie_destroy(PIVOT_BUCKET_TRIE(pivot_pyld));

            /* Free up Bucket handle */
            sal_free(PIVOT_BUCKET_HANDLE(pivot_pyld));

            /* free Pivot structure */
            sal_free(pivot_pyld);

#ifdef CHECK_CLEAN_BKT
            assert(_soc_th_alpm_128_bkt_count(u, mem, 1, delete_log_bkt, vrf, bufp)
                                                                    == 0);
#endif /* CHECK_CLEAN_BKT */
        }
    }
    VRF_TRIE_ROUTES_DEC(u, vrf_id, vrf, v6);
    if (VRF_TRIE_ROUTES_CNT(u, vrf_id, vrf, v6) == 0) {
        /* vrf is empty. Release resources */
        rv = soc_th_alpm_128_vrf_delete(u, vrf, v6);
    }
    SOC_ALPM_LPM_UNLOCK(u);
    return rv;

/* Recovery from error: */
    /* add back pivot bucket trie entry */
    /* add back prefix trie entry */
recover_pfx_trie:
    _soc_th_alpm_mask_prefix_create(u, v6, length, bpm);
    rv2 = trie_insert(pfx_trie, prefix,
                      ALPM_CTRL(u).trie_propagate ? bpm : NULL,
                      length, (trie_node_t *)pfx_pyld);
    if (SOC_FAILURE(rv2)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_th_alpm_128_delete: Unable to reinsert"
                          "prefix 0x%08x 0x%08x 0x%08x 0x%08x into pfx trie\n"),
                          prefix[1], prefix[2], prefix[3], prefix[4]));
    }
recover_bkt_trie:
    rv2 = trie_insert(trie, prefix, NULL, length,  (trie_node_t *) payload);
    if (SOC_FAILURE(rv2)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "_soc_th_alpm_128_delete: Unable to reinsert"
                          "prefix 0x%08x 0x%08x 0x%08x 0x%08x into pfx trie\n"),
                           prefix[1], prefix[2], prefix[3], prefix[4]));
    }

    SOC_ALPM_LPM_UNLOCK(u);
    return rv;
}

/* Initialize ALPM Subsytem */
int
soc_th_alpm_128_init(int u)
{
    int rv = SOC_E_NONE;

    /* Initialize TCAM Memory management */
    rv = soc_th_alpm_128_lpm_init(u);
    SOC_IF_ERROR_RETURN(rv);

    return rv;
}


/* clear only v6-128 alpm related internal state. Don't clean up common
 * containing structures here. Allow v4/v6-64 clear code to do that
 */
int soc_th_alpm_128_state_clear(int u)
{
    int i, rv;

    /* clear all pivot state */
    /* done in common code */

    /* clear all prefix tries */
    for (i = 0; i <= SOC_VRF_MAX(u) + 1; i++) {
        rv = trie_traverse(VRF_PREFIX_TRIE_IPV6_128(u, i), alpm_delete_node_cb,
                           NULL, _TRIE_INORDER_TRAVERSE);
        if (SOC_SUCCESS(rv)) {
            trie_destroy(VRF_PREFIX_TRIE_IPV6_128(u, i));
        } else {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "unit: %d Unable to clear v6_128 pfx trie for "
                          "vrf %d\n"), u, i));
            return rv;
        }
        if (VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, i) != NULL) {
            sal_free(VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, i));
        }
    }
    return SOC_E_NONE;
}

/* De-Init ALPM Subsytem */
int
soc_th_alpm_128_deinit(int u)
{
    soc_th_alpm_128_lpm_deinit(u);

    SOC_IF_ERROR_RETURN(soc_th_alpm_128_state_clear(u));
    return SOC_E_NONE;
}


/*
 * soc_th_alpm_128_vrf_add
 * Add a VRF default route when a L3 VRF is added
 * Adds a 0.0 entry into VRF
 */
static int
soc_th_alpm_128_vrf_add(int u, int vrf, int v6)
{
    defip_pair_128_entry_t *lpm_entry = NULL, tmp_lpm;
    int log_bkt = 0;
    int index;
    int rv = SOC_E_NONE;
    uint32 key[5] = {0};
    uint32 length;
    alpm_bucket_handle_t *bucket_handle = NULL;
    alpm_pivot_t *pivot_pyld = NULL;
    payload_t   *pfx_pyld = NULL;
    trie_t  *root;

    trie_t *pivot_root = NULL;
    trie_init(_MAX_KEY_LEN_144_, &VRF_PIVOT_TRIE_IPV6_128(u, vrf));
    pivot_root = VRF_PIVOT_TRIE_IPV6_128(u, vrf);

    trie_init(_MAX_KEY_LEN_144_, &VRF_PREFIX_TRIE_IPV6_128(u, vrf));
    root = VRF_PREFIX_TRIE_IPV6_128(u, vrf);

    lpm_entry = sal_alloc(sizeof(*lpm_entry), "Default 128 LPM entry");
    if (lpm_entry == NULL) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_vrf_add: unable to allocate memory "
                          "for IPv6-128 LPM entry\n")));
        return SOC_E_MEMORY;
    }

    /* Initialize an lpm entry to perform a match */
    _soc_th_alpm_128_lpm_ent_key_init(u, key, 0, vrf, v6, lpm_entry, 1);

    VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf) = lpm_entry;

    /* for global VRF */
    if (vrf == SOC_VRF_MAX(u) + 1) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, GLOBAL_ROUTEf, 1);
    } else {
        /* Set default miss to global route only for non global routes */
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, DEFAULT_MISSf, 1);
    }
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ENTRY_VIEWf,
        _soc_th_alpm_lpm_entry_view_get(u, v6, VRF_FLEX_IS_SET(u, vrf, vrf, v6, 1)));

    rv = soc_th_alpm_assign(u, vrf, L3_DEFIP_ALPM_IPV6_128m,
                            &log_bkt, NULL, NULL);
    if (SOC_FAILURE(rv)) {
        goto _err_exit;
    }
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_BKT_PTRf,
                            ALPM_PHY_BKT(u, log_bkt));
    if (ALPM_CTRL(u).bkt_sharing) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_SUB_BKT_PTRf,
                                ALPM_SUB_BKT(u, log_bkt));
    }

    /* add Entry into tcam as default routes for the VRF */
    sal_memcpy(&tmp_lpm, lpm_entry, sizeof(tmp_lpm));
    rv = soc_th_alpm_128_lpm_insert(u, &tmp_lpm, &index, 0, 0, 0);
    if (SOC_FAILURE(rv)) {
        goto _err_exit;
    }
    /* Insert Pivot into the pivot tries */
    bucket_handle = sal_alloc(sizeof(alpm_bucket_handle_t),
                              "ALPM Bucket Handle");
    if (bucket_handle == NULL) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_vrf_add: Unable to allocate memory "
                          "for bucket handle \n")));
        rv = SOC_E_MEMORY;
        goto _err_exit;
    }
    sal_memset(bucket_handle, 0, sizeof(*bucket_handle));

    /* Allocate PIVOT Payload */
    pivot_pyld = sal_alloc(sizeof(alpm_pivot_t), "Payload for Pivot");
    if (pivot_pyld == NULL) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_vrf_add: Unable to allocate memory "
                          "for PIVOT trie node \n")));
        rv = SOC_E_MEMORY;
        goto _err_exit;
    }

    pfx_pyld = sal_alloc(sizeof(payload_t), "Payload for pfx trie key");
    if (pfx_pyld == NULL) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_vrf_add: Unable to allocate memory "
                          "for pfx trie node \n")));
        rv = SOC_E_MEMORY;
        goto _err_exit;
    }
    sal_memset(pivot_pyld, 0, sizeof(*pivot_pyld));
    sal_memset(pfx_pyld, 0, sizeof(*pfx_pyld));

    /* 0 for default * route */
    length = 0;
    PIVOT_BUCKET_HANDLE(pivot_pyld) = bucket_handle;
    trie_init(_MAX_KEY_LEN_144_, &PIVOT_BUCKET_TRIE(pivot_pyld));
    PIVOT_BUCKET_INDEX(pivot_pyld) = log_bkt;
    PIVOT_BUCKET_VRF(pivot_pyld) = vrf;
    PIVOT_BUCKET_IPV6(pivot_pyld) = v6;
    PIVOT_BUCKET_DEF(pivot_pyld) = TRUE;

    pivot_pyld->key[0] = pfx_pyld->key[0] = key[0];
    pivot_pyld->key[1] = pfx_pyld->key[1] = key[1];
    pivot_pyld->key[2] = pfx_pyld->key[2] = key[2];
    pivot_pyld->key[3] = pfx_pyld->key[3] = key[3];
    pivot_pyld->key[4] = pfx_pyld->key[4] = key[4];
    pivot_pyld->len = pfx_pyld->len    = length;
    rv = trie_insert(root, key, ALPM_CTRL(u).trie_propagate ? key : NULL,
                     length, &(pfx_pyld->node));

    /* no internal default in bucket trie */
    if (SOC_FAILURE(rv)) {
        goto _err_exit;
    }

    /* insert into trie of pivots */
    rv = trie_insert(pivot_root, key, ALPM_CTRL(u).trie_propagate ? key : NULL,
                     length, (trie_node_t *)pivot_pyld);
    if (SOC_FAILURE(rv)) {
        trie_node_t *delp = NULL;
        (void) trie_delete(root, key, length, &delp);
        goto _err_exit;
    }

    index = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, index, v6);
    ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, index) << 1) = pivot_pyld;
    PIVOT_TCAM_INDEX(pivot_pyld) = SOC_ALPM_128_ADDR_LWR(u, index) << 1;
    PIVOT_TCAM_BPMLEN(pivot_pyld) = length;

    VRF_TRIE_INIT_DONE(u, vrf, v6, 1);
    return rv;

_err_exit:
    if (pfx_pyld != NULL) {
        sal_free(pfx_pyld);
    }
    if (pivot_pyld != NULL) {
        sal_free(pivot_pyld);
    }
    if (bucket_handle != NULL) {
        sal_free(bucket_handle);
    }
    if (lpm_entry != NULL) {
        sal_free(lpm_entry);
    }
    VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf) = NULL;

    return rv;
}

/*
 * soc_th_alpm_vrf_delete
 * Delete the VRF default route when a L3 VRF is destroyed
 */
static int
soc_th_alpm_128_vrf_delete(int u, int vrf, int v6)
{
    defip_pair_128_entry_t *lpm_entry;
    int idx, vrf_id, _vrf;
    int rv = SOC_E_NONE;
    uint32 key[2] = {0, 0}, result[SOC_MAX_MEM_FIELD_WORDS];
    payload_t *payload;
    alpm_pivot_t *pivot_pyld1;
    trie_node_t *delp;
    trie_t  *root;
    trie_t *pivot_root = NULL;

    soc_mem_t mem;
    int tcam_index, log_bkt, index;
    uint32 alpm_ent[SOC_MAX_MEM_FIELD_WORDS];

    lpm_entry = VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf);
    mem = L3_DEFIP_ALPM_IPV6_128m;

    /* Find and update the entry */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, lpm_entry, &vrf_id, &_vrf));
    rv = _soc_th_alpm_128_find(u, mem, lpm_entry, vrf_id, _vrf, alpm_ent,
                               &tcam_index, &log_bkt, &index, TRUE);

    /* find bucket pointers and release them */
    rv = soc_th_alpm_bucket_release(u, log_bkt, vrf, v6);
    if (SOC_FAILURE(rv)) {
         LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                  "soc_th_alpm_bucket_release: unable to free bucket %d"
                  " vrf %d/%d\n"), log_bkt, vrf, v6));
    }

    /* add Entry into tcam as default routes for the VRF */
    rv = soc_th_alpm_128_lpm_match(u, lpm_entry, (void *) result, &idx);
    if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_vrf_delete: unable to get internal"
                          " pivot idx for vrf %d/%d\n"), vrf, v6));
        idx = -1;
    }

    idx = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, idx, v6);
    pivot_pyld1 = ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, idx) << 1);

    rv = soc_th_alpm_128_lpm_delete(u, lpm_entry);
    if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_vrf_delete: unable to delete lpm "
                          "entry for internal default for vrf %d/%d\n"), vrf, v6));
    }

    sal_free(lpm_entry);

    VRF_TRIE_DEFAULT_ROUTE_IPV6_128(u, vrf)  = NULL;
    root = VRF_PREFIX_TRIE_IPV6_128(u, vrf);
    VRF_PREFIX_TRIE_IPV6_128(u, vrf) = NULL;
    VRF_TRIE_INIT_DONE(u, vrf, v6, 0);

    rv = trie_delete(root, key, 0, &delp);
    payload = (payload_t *) delp;
    if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "Unable to delete internal default for 128b vrf "
                          " %d/%d\n"), vrf, v6));
    }
    sal_free(payload);
    (void) trie_destroy(root);

    pivot_root = VRF_PIVOT_TRIE_IPV6_128(u, vrf);
    VRF_PIVOT_TRIE_IPV6_128(u, vrf) = NULL;

    delp = NULL;
    rv = trie_delete(pivot_root, key, 0, &delp);
    if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "Unable to delete internal pivot node for vrf"
                          " %d/%d\n"), vrf, v6));
    }
    (void) trie_destroy(pivot_root);

    (void) trie_destroy(PIVOT_BUCKET_TRIE(pivot_pyld1));
    sal_free(PIVOT_BUCKET_HANDLE(pivot_pyld1));
    sal_free(pivot_pyld1);

    return rv;
}

/*
 * soc_th_alpm_128_insert
 * Moving multiple entries around in h/w vs doing a linear search in s/w
 */
int
soc_th_alpm_128_insert(int u, void *entry_data, uint32 flags, int ent_index,
                    int pivot_info)
{
    /* Search Result buffer */
    defip_alpm_ipv6_128_entry_t alpmv6_entry, alpmv6_sip_entry;
    soc_mem_t mem;
    void      *bufp, *bufp2;
    int       vrf_id, vrf;
    int       index;
    int       ipv6;
    int       rv = SOC_E_NONE;
    uint32    default_route;
    int       log_bkt = 0, phy_bkt = 0;
    int       ipmc_route = 0;

    ipv6 = L3_DEFIP_MODE_128;

    /* Get table memory. */
    SOC_ALPM_TABLE_MEM_128(u, ipv6, mem);

    /* Assign entry buf based on table being used */
    SOC_ALPM_ENTRY_BUF_128(ipv6, mem, bufp, 0, alpmv6_entry);
    SOC_ALPM_ENTRY_BUF_128(ipv6, mem, bufp2, 0, alpmv6_sip_entry);

    if (ent_index != -1) {
        log_bkt = SOC_TH_ALPM_AIDX_TO_LOG_BKT(u, ent_index);
    }

    SOC_IF_ERROR_RETURN(
        _soc_th_alpm_128_mem_ent_init(u, entry_data, bufp, bufp2, mem, flags,
                                      &default_route, log_bkt));

    /* If the entry is override, then insert into TCAM directly */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, entry_data, &vrf_id, &vrf));

    if (VRF_FLEX_COMPLETED(u, vrf_id, vrf, ipv6)) {
        if (VRF_FLEX_IS_SET(u, vrf_id, vrf, ipv6, 1) != !!(flags & SOC_ALPM_STAT_FLEX)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "soc_alpm_128_insert:Flex flag conflict\n"
                                  )));
            return SOC_E_PARAM;
        }
    } else {
        VRF_FLEX_SET(u, vrf_id, vrf, ipv6, flags & SOC_ALPM_STAT_FLEX);
    }

    if (soc_feature(u, soc_feature_ipmc_defip)) {
        if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf)) {
            ipmc_route = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                             entry_data, MULTICAST_ROUTEf);
        } else if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, DATA_TYPEf)) {
            if (soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                    entry_data, DATA_TYPEf) == 2) {
                ipmc_route = 1;
            } else {
                ipmc_route = 0;
            }
        }
    }

    /* For VRF_OVERRIDE (Global High) entries, software needs to maintain the
     * index */
    /* Prefix resides in TCAM directly */
    /* Global High and Global Low Prefixes reside in TCAM directly, in TCAM / ALPM mode */
    /* Global High Prefixes reside in TCAM directly, in Parallel mode */
     if (ALPM_PREFIX_IN_TCAM(u, vrf_id) || ipmc_route) { /* Insert into TCAM directly and return */
        /* search in the hash table */
        rv = soc_th_alpm_128_lpm_insert(u, entry_data, &index, INVALID_BPM_LEN, 0,
                                        flags & SOC_ALPM_RPF_SRC_DISCARD);
        if (SOC_SUCCESS(rv) && !(pivot_info & SOC_ALPM_LPM_LOOKUP_HIT)) {
            VRF_TRIE_ROUTES_INC(u, vrf_id, vrf, ipv6);
        }

        if (rv == SOC_E_FULL) {
            if (vrf_id == SOC_L3_VRF_OVERRIDE) {
                VRF_PIVOT_FULL_INC(u, MAX_VRF_ID, ipv6);
            } else {
                VRF_PIVOT_FULL_INC(u, vrf, ipv6);
            }
        }
        return(rv);
    } else if (vrf == 0) {
        if (ALPM_CTRL(u).gp_zoned) {
            /* cannot have 0 as a VRF in parallel mode */
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                  "VRF=0 cannot be added in current mode\n")));
            return SOC_E_PARAM;
        }
    }

    /* combined search mode protection */
    if (vrf_id != SOC_L3_VRF_GLOBAL) {
        if (ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_COMBINED) {
            /* for emtpy DB allow insert only if route is default */
            if (VRF_TRIE_ROUTES_CNT(u, vrf_id, vrf, ipv6) == 0) {
                /* check if route is default, else throw error */
                if (!default_route) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "VRF %d: First route in a VRF has to "
                          " be a default route in this mode\n"), vrf_id));
                    return SOC_E_PARAM;
                }
            }
        }
    }

    /* non override entries, goes into ALPM memory */
    if (!VRF_TRIE_INIT_COMPLETED(u, vrf, ipv6)) {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u,
                    "soc_th_alpm_128_insert:VRF %d is not "
                    "initialized\n"), vrf));
        rv = soc_th_alpm_128_vrf_add(u, vrf, ipv6);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                  "soc_th_alpm_128_insert:VRF %d/%d trie init \n"
                          "failed\n"), vrf, ipv6));
            return rv;
        }
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
              (BSL_META_U(u,
              "soc_th_alpm_128_insert:VRF %d/%d trie init "
              "completed\n"), vrf, ipv6));
    }

    /* Find and update the entry */
    if (pivot_info & SOC_ALPM_LOOKUP_HIT) {
        rv = _soc_th_alpm_128_find_and_update(u, entry_data, bufp, bufp2, mem,
                                              ent_index);
    } else {
        /* entry is not found in database */
        /* Insert the entry into the database, if FULL, split the bucket */
        /* Insert prefix into trie */
        /* Split trie : Insertion into trie results into Split */
        /* Allocate a TCAM entry for PIVOT and bucket and move entries */
        if (ent_index == -1) {
            /* internally 0 is invalid bucket index */
            ent_index = 0;
        }
        phy_bkt = SOC_TH_ALPM_AIDX_TO_PHY_BKT(u, ent_index);
        /* In double wide mode, the ent_index could come from second
         * bucket, need to adjust to first bucket */
        if ((ALPM_CTRL(u).double_wide[ipv6]) && (phy_bkt & 0x1)) {
            phy_bkt &= ~0x1;
        }
        log_bkt = ALPM_LOG_BKT(phy_bkt, SOC_TH_ALPM_AIDX_TO_SUB_BKT(u, ent_index));
        rv = _soc_th_alpm_128_insert(u, entry_data, mem, bufp, bufp2, &index,
                                     log_bkt, pivot_info);
        if (SOC_SUCCESS(rv)) {
            VRF_TRIE_ROUTES_INC(u, vrf_id, vrf, ipv6);
        }
    }

    if (rv == SOC_E_FULL) {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
              (BSL_META_U(u,
              "unit %d :soc_th_alpm_128_insert: "
              "Route Insertion Failed :%s\n"),
              u, soc_errmsg(rv)));
    } else if (rv != SOC_E_NONE) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
              (BSL_META_U(u,
              "unit %d :soc_th_alpm_128_insert: "
              "Route Insertion Failed :%s\n"),
              u, soc_errmsg(rv)));
    }
    return(rv);
}

/*
 * soc_th_alpm_128_lookup
 * For IPV4 assume only both IP_ADDR0 is valid
 * Moving multiple entries around in h/w vs  doing a linear search in s/w
 */
int
soc_th_alpm_128_lookup(int u,
                void *key_data,
                void *e,         /* return entry data if found */
                int *index_ptr,
                int *cookie)
{
    defip_alpm_ipv6_128_entry_t alpmv6_entry; /* Search Result buffer */
    soc_mem_t mem;
    int       log_bkt = 0;
    int       tcam_index = -1;
    void      *bufp;
    int       vrf_id, vrf;
    int       ipv6 = 2, pfx;
    int       rv = SOC_E_NONE;
    int       ipmc_route = 0;
    int       flex;

    /* First launch lookup directly into tcam. If hit comes from override
     * vrf just return it. Else launch lookup into alpm pivots
     */
    /* For VRF_OVERRIDE (Global High) entries, software needs to maintain the
     * index */
    /* Prefix resides in TCAM directly */

    /* search in the hash table */
    *index_ptr = 0;
    rv = _soc_th_alpm_128_lpm_match(u, key_data, e, index_ptr, &pfx,
                                    &ipv6, &vrf_id, &vrf);

    if (SOC_SUCCESS(rv)) {
        if (soc_feature(u, soc_feature_ipmc_defip)) {
            if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf)) {
                ipmc_route = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                                 e, MULTICAST_ROUTEf);
            } else if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, DATA_TYPEf)) {
                if (soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                        e, DATA_TYPEf) == 2) {
                    ipmc_route = 1;
                } else {
                    ipmc_route = 0;
                }
            }
        }
    }
    /*
     * If entry is ipv4 copy to the "zero" half of the,
     * buffer, "zero" half of lpm_entry if the  original entry
     * is in the "one" half.
     */
    if (ALPM_PREFIX_IN_TCAM(u, vrf_id) || (ipmc_route)) {
        *cookie = 0;
        if (SOC_SUCCESS(rv)) {
            *cookie |= SOC_ALPM_LPM_LOOKUP_HIT;
        }
        return rv;
    }

    /* either no hit in OVERRIDE or hit in pivot tcam */

    /* non override entries, go to into ALPM memory */
    if (!VRF_TRIE_INIT_COMPLETED(u, vrf, ipv6)) {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
              (BSL_META_U(u,
              "soc_th_alpm_128_lookup:VRF %d is not "
              "initialized\n"), vrf));
        *index_ptr = 0;
        *cookie = 0;
        return SOC_E_NOT_FOUND;
    }
    /* Get table memory. */
    SOC_ALPM_TABLE_MEM_128(u, ipv6, mem);

    /* Assign entry buf based on table being used */
    SOC_ALPM_ENTRY_BUF_128(ipv6, mem, bufp, 0, alpmv6_entry);

    SOC_ALPM_LPM_LOCK(u);
    /* Find and update the entry */
    rv = _soc_th_alpm_128_find(u, mem, key_data, vrf_id, vrf, bufp,
                               &tcam_index, &log_bkt, index_ptr, TRUE);
    SOC_ALPM_LPM_UNLOCK(u);
    if (SOC_FAILURE(rv)) {
        *cookie = tcam_index;
        *index_ptr = SOC_TH_ALPM_AIDX(u, ALPM_PHY_BKT(u, log_bkt),
                                      ALPM_SUB_BKT(u, log_bkt), 0, 0);
        return rv;
    }
    /* Copy ALPM memory to LPM entry */
    flex = VRF_FLEX_IS_SET(u, vrf_id, vrf, ipv6, 0);
    rv =  _soc_th_alpm_128_lpm_ent_init(u, bufp, mem, ipv6, vrf_id,
                                        log_bkt, *index_ptr, e, flex);
    *cookie = SOC_ALPM_LOOKUP_HIT | tcam_index;
    if (flex) {
        *cookie |= SOC_ALPM_COOKIE_FLEX;
    }
    *index_ptr = (ALPM_SUB_BKT(u, log_bkt) << ALPM_ENT_INDEX_BITS) | *index_ptr;

    return(rv);
}

/* Find a LPM Global low or VRF route in ALPM memory */
int
_soc_th_alpm_128_find_best_match(int u,
                                 void *key_data,
                                 void *e,      /* return entry data if found */
                                 int vrf_id,
                                 int *tcam_index,
                                 int *log_bkt,
                                 int *key_index,
                                 int do_urpf)
{
    int rv = SOC_E_NONE;
    int i, j, v6, hit = 0;
    uint32 db_type, ent_type, bank_disable;
    defip_aux_scratch_entry_t aux_entry;
    int global, mvrf, vrf;
    int index;
    soc_mem_t mem, lpm_mem;
    int hw_len, sw_len, ent_num;

    soc_field_t ip_addr_fld[4] = {
        IP_ADDR0_LWRf,
        IP_ADDR1_LWRf,
        IP_ADDR0_UPRf,
        IP_ADDR1_UPRf
    };

    /* Used for keeping Longest Matched entry in Bucket */
    uint32  alpm_bufp[SOC_MAX_MEM_FIELD_WORDS] = {0};
    int     alpm_len = -1;
    int     alpm_index = 0;

    v6 = L3_DEFIP_MODE_128;
    lpm_mem = L3_DEFIP_PAIR_128m;
    global = soc_mem_field32_get(u, lpm_mem, key_data, GLOBAL_ROUTEf);
    mvrf = soc_mem_field32_get(u, lpm_mem, key_data, VRF_ID_0_LWRf);
    vrf  = (vrf_id == SOC_L3_VRF_GLOBAL) ? (SOC_VRF_MAX(u) + 1) : mvrf;

    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                (BSL_META_U(u, "Prefare AUX Scratch for searching TCAM in "
                "%s region, Key data: v6 %d global %d vrf %d\n"),
                vrf_id == SOC_L3_VRF_GLOBAL ? "Global" : "VRF",
                v6, global, mvrf));

    bank_disable = ALPM_CTRL(u).bank_disable_bmp_8b[vrf != SOC_VRF_MAX(u) + 1];

    if (ALPM_CTRL(u).sw_prefix_lkup) {
        uint32 prefix[5] = {0};
        uint32 length = 0;
        int    default_route = 0;

        if (!VRF_TRIE_INIT_COMPLETED(u, vrf, v6)) {
            LOG_VERBOSE(BSL_LS_SOC_ALPM, (BSL_META_U(u,
                "_soc_th_alpm_128_find_best_match: VRF %d is not initialized\n"),
                vrf));
            return SOC_E_NOT_FOUND;
        }

        rv = _soc_th_alpm_128_prefix_create(u, key_data, prefix,
                                            &length, &default_route);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM, (BSL_META_U(u,
                "_soc_th_alpm_128_find_best_match: prefix create failed\n")));
            return rv;
        }

        SOC_IF_ERROR_RETURN(
            _soc_th_alpm_128_sw_pivot_find(u, prefix, length, v6, vrf, &hit,
                                           tcam_index, log_bkt));
    } else {
        soc_alpm_db_ent_type_encoding(u, vrf , &db_type, &ent_type);

        if (do_urpf) {
            db_type += 1;
        }
        if (vrf_id == SOC_L3_VRF_GLOBAL) {
            soc_mem_field32_set(u, lpm_mem, key_data, GLOBAL_ROUTEf, 1);
            soc_mem_field32_set(u, lpm_mem, key_data, VRF_ID_0_LWRf, 0);
        }

        sal_memset(&aux_entry, 0, sizeof(defip_aux_scratch_entry_t));
        SOC_IF_ERROR_RETURN(
            _soc_th_alpm_128_fill_aux_entry_for_op(u, key_data, v6, db_type,
                                                   ent_type, 0, &aux_entry));
        /* Recover to original value */
        if (vrf_id == SOC_L3_VRF_GLOBAL) {
            soc_mem_field32_set(u, lpm_mem, key_data, GLOBAL_ROUTEf, global);
            soc_mem_field32_set(u, lpm_mem, key_data, VRF_ID_0_LWRf, mvrf);
        }

        /* Start shadow table engine to search */
        SOC_IF_ERROR_RETURN(
            _soc_th_alpm_aux_op(u, PREFIX_LOOKUP, &aux_entry, TRUE,
                                &hit, tcam_index, log_bkt, 0));

    }

    if (hit == 0) {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Could not find bucket\n")));
        return SOC_E_NOT_FOUND;
    }

    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                (BSL_META_U(u, "Hit in memory %s, index %d, "
                "bucket [%d,%d]\n"), SOC_MEM_NAME(u, lpm_mem),
                soc_th_alpm_logical_idx(u, lpm_mem,
                    SOC_ALPM_128_DEFIP_TO_PAIR(u, (*tcam_index) >> 1), 1),
                ALPM_PHY_BKT(u, *log_bkt), ALPM_SUB_BKT(u, *log_bkt)));

    /* Found, check ALPM bucket */
    mem = L3_DEFIP_ALPM_IPV6_128m;
    rv = _soc_th_alpm_128_ip6_mask_len_get(u, key_data, &sw_len);
    if (SOC_FAILURE(rv)) {
        return rv;
    }
    ent_num = (ALPM_CTRL(u).double_wide[v6]) ? 16 : 8;

    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                (BSL_META_U(u, "Start searching mem %s bucket [%d,%d](count %d) "
                "for Length %d\n"),
                SOC_MEM_NAME(u, mem), ALPM_PHY_BKT(u, *log_bkt),
                ALPM_SUB_BKT(u, *log_bkt), ent_num, sw_len));

    for (i = 0; i < ent_num; i++) {
        uint32 bufp[SOC_MAX_MEM_FIELD_WORDS] = {0};
        uint32 mask[4] = {0};
        uint32 hkey[4] = {0};
        uint32 skey[4] = {0};
        int valid;

        rv = _soc_th_alpm_mem_index(u, mem, ALPM_PHY_BKT(u, *log_bkt),
                                    i, bank_disable, &index);
        if (rv == SOC_E_FULL) {
            continue;
        }

        SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, mem, MEM_BLOCK_ANY,
                                         index, (void *)&bufp));
        valid = soc_mem_field32_get(u, mem, &bufp, VALIDf);
        hw_len = soc_mem_field32_get(u, mem, &bufp, LENGTHf);

        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Bucket [%d,%d] index %6d: valid %d, length %d\n"),
                    ALPM_PHY_BKT(u, *log_bkt), ALPM_SUB_BKT(u, *log_bkt),
                    index, valid, hw_len));

        if (!valid || (hw_len > sw_len)) {
            continue;
        }

        /* Length in ALPM <= given length */
        SHR_BITSET_RANGE(mask, 128 - hw_len, hw_len);
        (void)soc_mem_field_get(u, mem, (uint32 *)&bufp, KEYf, (uint32 *)hkey);
        skey[3] = soc_mem_field32_get(u, lpm_mem, key_data, ip_addr_fld[3]);
        skey[2] = soc_mem_field32_get(u, lpm_mem, key_data, ip_addr_fld[2]);
        skey[1] = soc_mem_field32_get(u, lpm_mem, key_data, ip_addr_fld[1]);
        skey[0] = soc_mem_field32_get(u, lpm_mem, key_data, ip_addr_fld[0]);

        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u,
                    "\tmask %08x %08x %08x %08x \n"
                    "\t key %08x %08x %08x %08x \n"
                    "\thost %08x %08x %08x %08x \n"),
                    mask[3], mask[2], mask[1], mask[0],
                    hkey[3], hkey[2], hkey[1], hkey[0],
                    skey[3], skey[2], skey[1], skey[0]));

        for (j = 3; j >= 0; j--) {
            if ((skey[j] & mask[j]) != (hkey[j] & mask[j])) {
                break;
            }
        }

        /* Hardware key doesn't match to software key */
        if (j >= 0) {
            continue;
        }

        /* Matched, store and keep searching,
         * could be Longer prefix in following entries */
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Found a match in mem %s bucket [%d,%d], "
                    "index %d\n"), SOC_MEM_NAME(u, mem),
                    ALPM_PHY_BKT(u, *log_bkt), ALPM_SUB_BKT(u, *log_bkt),
                    index));

        /* Keep longest matched route */
        if (alpm_len == -1 || alpm_len < hw_len) {
            alpm_len = hw_len;
            alpm_index = index;
            sal_memcpy(alpm_bufp, bufp, sizeof(bufp));
        }
    }

    /* Found */
    if (alpm_len != -1) {
        rv = _soc_th_alpm_128_lpm_ent_init(u, &alpm_bufp, mem, v6, vrf_id,
                                           *log_bkt, alpm_index, e,
                                           VRF_FLEX_IS_SET(u, vrf_id, vrf, v6, 0));
        if (SOC_SUCCESS(rv)) {
            *key_index = alpm_index;
            if (bsl_check(bslLayerSoc, bslSourceAlpm, bslSeverityVerbose, u)) {
                LOG_VERBOSE(BSL_LS_SOC_ALPM,
                            (BSL_META_U(u, "Hit mem %s bucket [%d,%d], index %d\n"),
                            SOC_MEM_NAME(u, mem), ALPM_PHY_BKT(u, *log_bkt),
                            ALPM_SUB_BKT(u, *log_bkt), alpm_index));
            }
        }
        return rv;
    }

    /* Miss in bucket, use associate data */
    *key_index = soc_th_alpm_logical_idx(u, lpm_mem,
                    SOC_ALPM_128_DEFIP_TO_PAIR(u, (*tcam_index) >> 1), 1);
    SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, lpm_mem, MEM_BLOCK_ANY,
                                           *key_index, (void *)e));

    return SOC_E_NONE;
}

/*
 * soc_th_alpm_128_find_best_match
 *
 * It's an indenpendent routine, to simalute HW process for incoming packets.
 * Considering possible mismatch between SW and HW, we need to go through
 * hardware for lookup regardless of software state.
 */
int
soc_th_alpm_128_find_best_match(int u,
                                void *key_data,
                                void *e,   /* return entry data if found */
                                int *index_ptr,
                                int do_urpf)
{
    int rv = SOC_E_NONE;
    int i, j;
    int index_min, index_cnt;
    defip_pair_128_entry_t lpm128_ent;
    uint32 hmsk, hkey, skey;
    int hw_len, sw_len;
    int global_hi, global_rt;
    int vrf_id, vrf = 0;
    int tcam_index, bucket_index;
    soc_mem_t lpm_mem;

#define ALPM_128_KEY_FIELD_NUM  4
    soc_field_t msk_fld[ALPM_128_KEY_FIELD_NUM] = {
        IP_ADDR_MASK1_UPRf,
        IP_ADDR_MASK0_UPRf,
        IP_ADDR_MASK1_LWRf,
        IP_ADDR_MASK0_LWRf
    };
    soc_field_t val_fld[ALPM_128_KEY_FIELD_NUM] = {
        IP_ADDR1_UPRf,
        IP_ADDR0_UPRf,
        IP_ADDR1_LWRf,
        IP_ADDR0_LWRf
    };

    lpm_mem = L3_DEFIP_PAIR_128m;
    if (!SOC_URPF_STATUS_GET(u) && do_urpf) {
        return SOC_E_PARAM;
    }

    /* Since L3_DEFIP_* tables are not support for DMA,
     * we do PIO search instead */
    index_min = soc_mem_index_min(u, lpm_mem);
    index_cnt = soc_mem_index_count(u, lpm_mem);
    if (SOC_URPF_STATUS_GET(u)) {
        index_cnt >>= 1;
    }
    /* in Parallel mode search from second half */
    if (ALPM_CTRL(u).gp_zoned) {
        index_cnt >>= 1;
        index_min += index_cnt;
    }

    if (do_urpf) {
        index_min += soc_mem_index_count(u, lpm_mem) / 2;
    }

    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                (BSL_META_U(u, "Start LPM searchng from %d, count %d\n"),
                index_min, index_cnt));

    /* Searching for Global High routes */
    for (i = index_min; i < index_min + index_cnt; i++) {
        SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, lpm_mem, MEM_BLOCK_ANY, i,
                            (void *)&lpm128_ent));

        if (!soc_mem_field32_get(u, lpm_mem, &lpm128_ent, VALID0_LWRf)) {
            continue;
        }

        /* Found, all Key matched */
        global_hi = soc_mem_field32_get(u, lpm_mem, &lpm128_ent, GLOBAL_HIGHf);
        global_rt = soc_mem_field32_get(u, lpm_mem, &lpm128_ent, GLOBAL_ROUTEf);
        /* No need to compare key if not Global High route */
        if (!(ALPM_CTRL(u).alpm_mode != SOC_ALPM_MODE_TCAM_ALPM &&
              global_hi && global_rt) &&
            !(ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_TCAM_ALPM &&
              global_rt)) {
            continue;
        }

        rv = _soc_th_alpm_128_ip6_mask_len_get(u, key_data, &sw_len);
        rv = _soc_th_alpm_128_ip6_mask_len_get(u, &lpm128_ent, &hw_len);
        if (SOC_FAILURE(rv) || (hw_len > sw_len)) {
            continue;
        }

        for (j = 0; j < ALPM_128_KEY_FIELD_NUM; j++) {
            hmsk = soc_mem_field32_get(u, lpm_mem, &lpm128_ent, msk_fld[j]);
            hkey = soc_mem_field32_get(u, lpm_mem, &lpm128_ent, val_fld[j]);
            skey = soc_mem_field32_get(u, lpm_mem, key_data, val_fld[j]);
            if ((skey & hmsk) != (hkey & hmsk)) {
                break;
            }
        }

        /* Not match */
        if (j < ALPM_128_KEY_FIELD_NUM) {
            continue;
        }

        /* Found, all Key matched */
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Hit Global High route in index = %d\n"), j));
        sal_memcpy(e, &lpm128_ent, sizeof(lpm128_ent));
        *index_ptr = i;
        return SOC_E_NONE;
    }

    /* Global High lookup miss, use AUX to search Global Low and VRF route */
    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                (BSL_META_U(u, "Global high lookup miss, use AUX engine to "
                "search for Global Low and VRF routes\n")));

    /* Fill in AUX Scratch and perform PREFIX Operation */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, key_data, &vrf_id, &vrf));
    rv = _soc_th_alpm_128_find_best_match(u, key_data, e, vrf_id, &tcam_index,
                                          &bucket_index, index_ptr, do_urpf);
    if (rv == SOC_E_NOT_FOUND) {
        vrf = SOC_L3_VRF_GLOBAL;
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Not found in VRF region, try Global "
                    "region\n")));
        rv = _soc_th_alpm_128_find_best_match(u, key_data, e, vrf_id, &tcam_index,
                                              &bucket_index, index_ptr, do_urpf);
    }

    if (SOC_SUCCESS(rv)) {
        tcam_index = soc_th_alpm_logical_idx(u, lpm_mem,
                        SOC_ALPM_128_DEFIP_TO_PAIR(u, tcam_index >> 1), 1);
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Hit in %s region in TCAM index %d, "
                    "bucket [%d,%d]\n"),
                    vrf == SOC_L3_VRF_GLOBAL ? "Global Low" : "VRF",
                    tcam_index, ALPM_PHY_BKT(u, bucket_index),
                    ALPM_SUB_BKT(u, bucket_index)));
    } else {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "Search miss for given address\n")));
    }

    return(rv);
}

/*
 * soc_th_alpm_delete
 */
int
soc_th_alpm_128_delete(int u, void *key_data, int key_idx, int pivot_info)
{
    int       log_bkt, phy_bkt;
    int       vrf_id, vrf;
    int       ipv6;
    int       rv = SOC_E_NONE;
    int       ipmc_route = 0;

    ipv6 = L3_DEFIP_MODE_128;

    if (soc_feature(u, soc_feature_ipmc_defip)) {
        if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf)) {
            ipmc_route = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                             key_data, MULTICAST_ROUTEf);
        } else if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, DATA_TYPEf)) {
            if (soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                    key_data, DATA_TYPEf) == 2) {
                ipmc_route = 1;
            } else {
                ipmc_route = 0;
            }
        }
    }

    /* If the entry is override, then insert into TCAM directly */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, key_data, &vrf_id, &vrf));
    /* For VRF_OVERRIDE (Global High) entries, software needs to maintain the
     * index */
    /* Prefix resides in TCAM directly */
    if (ALPM_PREFIX_IN_TCAM(u, vrf_id) || (ipmc_route)) { /* TCAM Direct lookup */
        /* search in the hash table */
        rv = soc_th_alpm_128_lpm_delete(u, key_data);
        if (SOC_SUCCESS(rv)) {
            VRF_TRIE_ROUTES_DEC(u, vrf_id, vrf, ipv6);
        }
        return(rv);
    } else { /* non override entries, go to into ALPM memory */
        int tcam_index;
        if (!VRF_TRIE_INIT_COMPLETED(u, vrf, ipv6)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "soc_th_alpm_128_delete:VRF %d/%d is not "
                          "initialized\n"), vrf, ipv6));
            return SOC_E_NONE;
        }
        if (key_idx == -1) {
            /* internally 0 is invalid bucket index */
            key_idx = 0;
        }
        phy_bkt = SOC_TH_ALPM_AIDX_TO_PHY_BKT(u, key_idx);
        /* In double wide mode, the key_idx could come from second
         * bucket, need to adjust to first bucket */
        if (ALPM_CTRL(u).double_wide[ipv6] && (phy_bkt & 0x1)) {
            phy_bkt &= ~0x1;
        }

        log_bkt = ALPM_LOG_BKT(phy_bkt, SOC_TH_ALPM_AIDX_TO_SUB_BKT(u, key_idx));
        tcam_index = pivot_info & SOC_ALPM_TCAM_INDEX_MASK;
        rv = _soc_th_alpm_128_delete(u, key_data, vrf_id, vrf, log_bkt,
                                     tcam_index, key_idx);
    }
    return(rv);
}

/**********************************************
* TCAM Management functions *
 */

/*
 * TCAM based PIVOT implementation. Each table entry can hold two IPV4 PIVOTs or
 * one IPV6 PIVOT entry. VRF independent routes placed at the beginning or
 * at the end of table based on application provided entry vrf id
 * (SOC_L3_VRF_OVERRIDE/SOC_L3_VRF_GLOBAL).
 *
 *              ALPM_MAX_PFX_INDEX
 * lpm_prefix_index[98].begin ---> ===============================
 *                                 ==                           ==
 *                                 ==    0                      ==
 * lpm_prefix_index[98].end   ---> ===============================
 *
 * lpm_prefix_index[97].begin ---> ===============================
 *                                 ==                           ==
 *                                 ==    IPV6  Prefix Len = 64  ==
 * lpm_prefix_index[97].end   ---> ===============================
 *
 *
 *
 * lpm_prefix_index[x].begin --->  ===============================
 *                                 ==                           ==
 *                                 ==                           ==
 * lpm_prefix_index[x].end   --->  ===============================
 *
 *
 *              ALPM_IPV6_PFX_ZERO
 * lpm_prefix_index[33].begin ---> ===============================
 *                                 ==                           ==
 *                                 ==    IPV6  Prefix Len = 0   ==
 * lpm_prefix_index[33].end   ---> ===============================
 *
 *
 * lpm_prefix_index[32].begin ---> ===============================
 *                                 ==                           ==
 *                                 ==    IPV4  Prefix Len = 32  ==
 * lpm_prefix_index[32].end   ---> ===============================
 *
 *
 *
 * lpm_prefix_index[0].begin --->  ===============================
 *                                 ==                           ==
 *                                 ==    IPV4  Prefix Len = 0   ==
 * lpm_prefix_index[0].end   --->  ===============================
 */


/*
 *      Extract key data from an entry at the given index.
 */
static
void _soc_th_alpm_128_lpm_hash_entry_get(int u, void *e,
                             int index, _soc_th_alpm_128_lpm_hash_entry_t r_entry,
                             int *v)
{
    SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, e, r_entry);
    if (v) {
        *v = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID0_LWRf) &&
             SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID1_LWRf) &&
             SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID0_UPRf) &&
             SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, e, VALID1_UPRf);
    }
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_compare_key
 * Purpose:
 *      Comparison function for AVL shadow table operations.
 */
static
int _soc_th_alpm_128_lpm_hash_compare_key(_soc_th_alpm_128_lpm_hash_entry_t key1,
                                 _soc_th_alpm_128_lpm_hash_entry_t key2)
{
    int idx;

    for (idx = 0; idx < 9; idx++) {
        SOC_MEM_128_COMPARE_RETURN(key1[idx], key2[idx]);
    }
    return (0);
}

#ifdef FB_LPM_DEBUG
#define H_INDEX_MATCH_128(str, tab_index, match_index)      \
                 LOG_ERROR(BSL_LS_SOC_ALPM,\
                          (BSL_META_U(u, \
                          "%s index: H %d A %d\n"),   \
                           str, (int)tab_index, match_index))
#else
#define H_INDEX_MATCH_128(str, tab_index, match_index)
#endif

#define LPM_128_NO_MATCH_INDEX 0x4000
#define LPM_128_HASH_INSERT(u, entry_data, tab_index, rvt_index)       \
    soc_th_alpm_128_lpm_hash_insert(u, entry_data, tab_index, \
                            LPM_128_NO_MATCH_INDEX, 0, rvt_index)

#define LPM_128_HASH_REVERT(u, entry_data, tab_index, rvt_index)       \
    soc_th_alpm_128_lpm_hash_revert(u, entry_data, tab_index, rvt_index)

#define LPM_128_HASH_DELETE(u, key_data, tab_index)         \
    soc_th_alpm_128_lpm_hash_delete(u, key_data, tab_index)

#define LPM_128_HASH_LOOKUP(u, key_data, pfx, tab_index)    \
    soc_th_alpm_128_lpm_hash_lookup(u, key_data, pfx, tab_index)

#define LPM_128_HASH_VERIFY(u, key_data, tab_index)    \
    soc_th_alpm_128_lpm_hash_verify(u, key_data, tab_index)

#define INDEX_DELETE_128(hash, hash_idx, del_idx)                   \
    hash->table[hash_idx] =                                     \
        hash->link_table[del_idx & FB_LPM_128_HASH_INDEX_MASK];     \
    hash->link_table[del_idx & FB_LPM_128_HASH_INDEX_MASK] =        \
        FB_LPM_128_HASH_INDEX_NULL

#define INDEX_DELETE_LINK_128(hash, prev_idx, del_idx)              \
    hash->link_table[prev_idx & FB_LPM_128_HASH_INDEX_MASK] =       \
        hash->link_table[del_idx & FB_LPM_128_HASH_INDEX_MASK];     \
    hash->link_table[del_idx & FB_LPM_128_HASH_INDEX_MASK] =        \
        FB_LPM_128_HASH_INDEX_NULL

static
void soc_th_alpm_128_lpm_hash_insert(int u, void *entry_data, uint32 tab_index,
                            uint32 old_index, int pfx, uint32 *rvt_index)
{
    _soc_th_alpm_128_lpm_hash_entry_t    key_hash;

    /* IPV6 entry */
    if (SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID1_LWRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID0_LWRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID1_UPRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID0_UPRf)) {
        SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, entry_data, key_hash);
        _soc_th_alpm_128_lpm_hash_insert(
                    SOC_ALPM_128_LPM_STATE_HASH(u),
                    _soc_th_alpm_128_lpm_hash_compare_key,
                    key_hash,
                    pfx,
                    old_index,
                    tab_index,
                    rvt_index);
    }
}

static
void soc_th_alpm_128_lpm_hash_revert(int u, void *entry_data, uint32 tab_index,
                                  uint32 rvt_index)
{
    _soc_th_alpm_128_lpm_hash_entry_t    key_hash;

    /* IPV6 entry */
    if (SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID1_LWRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID0_LWRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID1_UPRf) &&
        SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, entry_data,
                                VALID0_UPRf)) {
        SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, entry_data, key_hash);
        _soc_th_alpm_128_lpm_hash_revert(
                    SOC_ALPM_128_LPM_STATE_HASH(u),
                    _soc_th_alpm_128_lpm_hash_compare_key,
                    key_hash,
                    tab_index,
                    rvt_index);
    }
}


static
void soc_th_alpm_128_lpm_hash_delete(int u, void *key_data, uint32 tab_index)
{
    _soc_th_alpm_128_lpm_hash_entry_t    key_hash;
    int                         pfx = -1;
    int                         rv;
    uint16                      index;

    SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, key_data, key_hash);
    index = tab_index;

    rv = _soc_th_alpm_128_lpm_hash_delete(SOC_ALPM_128_LPM_STATE_HASH(u),
                                 _soc_th_alpm_128_lpm_hash_compare_key,
                                 key_hash, pfx, index);
    if (SOC_FAILURE(rv)) {
                 LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                           "\ndel  index: H %d error %d\n"), index, rv));
    }
}

static
int soc_th_alpm_128_lpm_hash_lookup(int u, void *key_data, int pfx, int *key_index)
{
    _soc_th_alpm_128_lpm_hash_entry_t    key_hash;
    int rv;
    uint16  index = FB_LPM_128_HASH_INDEX_NULL;

    SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, key_data, key_hash);

    rv = _soc_th_alpm_128_lpm_hash_lookup(SOC_ALPM_128_LPM_STATE_HASH(u),
                                       _soc_th_alpm_128_lpm_hash_compare_key,
                                       key_hash, pfx, &index);
    if (SOC_FAILURE(rv)) {
        *key_index = 0xFFFFFFFF;
        return(rv);
    }

    *key_index = index;

    return(SOC_E_NONE);
}


static
int soc_th_alpm_128_lpm_hash_verify(int u, void *key_data, uint32 tab_index)
{
    _soc_th_alpm_128_lpm_hash_entry_t    key_hash;
    int                         pfx = -1;
    int                         rv;
    uint16                      index;

    SOC_FB_LPM_128_HASH_ENTRY_GET_IPV6(u, key_data, key_hash);
    index = tab_index;

    rv = _soc_th_alpm_128_lpm_hash_verify(SOC_ALPM_128_LPM_STATE_HASH(u),
                                 _soc_th_alpm_128_lpm_hash_compare_key,
                                 key_hash, pfx, index);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                              "\nveri index: H %d error %d\n"), index, rv));
    }
    return rv;
}
/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_compute
 * Purpose:
 *      Compute CRC hash for key data.
 * Parameters:
 *      data - Key data
 *      data_nbits - Number of data bits
 * Returns:
 *      Computed 16 bit hash
 */
static
uint16 _soc_th_alpm_128_lpm_hash_compute(uint8 *data, int data_nbits)
{
    return (_shr_crc16b(0, data, data_nbits));
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_create
 * Purpose:
 *      Create an empty hash table
 * Parameters:
 *      unit  - Device unit
 *      entry_count - Limit for number of entries in table
 *      index_count - Hash index max + 1. (index_count <= count)
 *      fb_lpm_hash_ptr - Return pointer (handle) to new Hash Table
 * Returns:
 *      SOC_E_NONE       Success
 *      SOC_E_MEMORY     Out of memory (system allocator)
 */

static
int _soc_th_alpm_128_lpm_hash_create(int unit,
                            int entry_count,
                            int index_count,
                            _soc_th_alpm_128_lpm_hash_t **fb_lpm_hash_ptr)
{
    _soc_th_alpm_128_lpm_hash_t  *hash;
    int                 index;

    if (index_count > entry_count) {
        return SOC_E_MEMORY;
    }
    hash = sal_alloc(sizeof (_soc_th_alpm_128_lpm_hash_t), "lpm_hash");
    if (hash == NULL) {
        return SOC_E_MEMORY;
    }

    sal_memset(hash, 0, sizeof (*hash));

    hash->unit = unit;
    hash->entry_count = entry_count;
    hash->index_count = index_count;

    /*
     * Pre-allocate the hash table storage.
     */
    hash->table = sal_alloc(hash->index_count * sizeof(*(hash->table)),
                            "hash_table");

    if (hash->table == NULL) {
        sal_free(hash);
        return SOC_E_MEMORY;
    }
    /*
     * In case where all the entries should hash into the same bucket
     * this will prevent the hash table overflow
     */
    hash->link_table = sal_alloc(
                            hash->entry_count * sizeof(*(hash->link_table)),
                            "link_table");
    if (hash->link_table == NULL) {
        sal_free(hash->table);
        sal_free(hash);
        return SOC_E_MEMORY;
    }

    /*
     * Set the entries in the hash table to FB_LPM_128_HASH_INDEX_NULL
     * Link the entries beyond hash->index_max for handling collisions
     */
    for(index = 0; index < hash->index_count; index++) {
        hash->table[index] = FB_LPM_128_HASH_INDEX_NULL;
    }
    for(index = 0; index < hash->entry_count; index++) {
        hash->link_table[index] = FB_LPM_128_HASH_INDEX_NULL;
    }
    *fb_lpm_hash_ptr = hash;
    return SOC_E_NONE;
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_destroy
 * Purpose:
 *      Destroy the hash table
 * Parameters:
 *      fb_lpm_hash - Pointer (handle) to Hash Table
 * Returns:
 *      SOC_E_NONE       Success
 */
static
int _soc_th_alpm_128_lpm_hash_destroy(_soc_th_alpm_128_lpm_hash_t *fb_lpm_hash)
{
    if (fb_lpm_hash != NULL) {
        sal_free(fb_lpm_hash->table);
        sal_free(fb_lpm_hash->link_table);
        sal_free(fb_lpm_hash);
    }

    return SOC_E_NONE;
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_lookup
 * Purpose:
 *      Look up a key in the hash table
 * Parameters:
 *      hash - Pointer (handle) to Hash Table
 *      key_cmp_fn - Compare function which should compare key
 *      entry   - The key to lookup
 *      pfx     - Prefix length for lookup acceleration.
 *      key_index - (OUT)       Index where the key was found.
 * Returns:
 *      SOC_E_NONE      Key found
 *      SOC_E_NOT_FOUND Key not found
 */

static
int _soc_th_alpm_128_lpm_hash_lookup(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry, int pfx,
                            uint16 *key_index)
{
    int u = hash->unit, v, i = 0;

    uint16 hash_val;
    uint16 index;

    hash_val = _soc_th_alpm_128_lpm_hash_compute((uint8 *)entry,
                                        (32 * 9)) % hash->index_count;
    index = hash->table[hash_val];
    H_INDEX_MATCH_128("lhash", entry[0], hash_val);
    H_INDEX_MATCH_128("lkup ", entry[0], index);
    while(index != FB_LPM_128_HASH_INDEX_NULL && i++ < hash->entry_count) {
        uint32  e[SOC_MAX_MEM_FIELD_WORDS];
        _soc_th_alpm_128_lpm_hash_entry_t  r_entry;
        int     rindex;

        rindex = index;
        /*
         * Check prefix length and skip index if not valid for given length
        if ((SOC_ALPM_LPM_STATE_START(u, pfx) <= rindex) &&
            (SOC_ALPM_LPM_STATE_END(u, pfx) >= rindex)) {
         */
        SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m,
                                               MEM_BLOCK_ANY, rindex, e));
        SOC_FB_LPM_128_HASH_ENTRY_GET(u, e, index, r_entry, &v);
        if (v == 0) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u,
                                "Empty entry[%d] in link_table. hash_val %d ridx %d \n"),
                                index, hash_val, rindex));
        }
        if ((*key_cmp_fn)(entry, r_entry) == 0) {
            *key_index = index;
            H_INDEX_MATCH_128("found", entry[0], index);
            return(SOC_E_NONE);
        }
        /*
        }
        */
        index = hash->link_table[index & FB_LPM_128_HASH_INDEX_MASK];
        H_INDEX_MATCH_128("lkup1", entry[0], index);
    }
    if (i > hash->entry_count) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                            "Hash loop\n")));
    }
    H_INDEX_MATCH_128("not_found", entry[0], index);
    return(SOC_E_NOT_FOUND);
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_insert
 * Purpose:
 *      Insert/Update a key index in the hash table
 * Parameters:
 *      hash - Pointer (handle) to Hash Table
 *      key_cmp_fn - Compare function which should compare key
 *      entry   - The key to lookup
 *      pfx     - Prefix length for lookup acceleration.
 *      old_index - Index where the key was moved from.
 *                  FB_LPM_128_HASH_INDEX_NULL if new entry.
 *      new_index - Index where the key was moved to.
 * Returns:
 *      SOC_E_NONE      Key found
 */
/*
 *      Should be caled before updating the LPM table so that the
 *      data in the hash table is consistent with the LPM table
 */
static
int _soc_th_alpm_128_lpm_hash_insert(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int    pfx,
                            uint16 old_index,
                            uint16 new_index,
                            uint32 *rvt_index)
{

#define INDEX_ADD_128(hash, hash_idx, new_idx)                      \
    hash->link_table[new_idx & FB_LPM_128_HASH_INDEX_MASK] =        \
        hash->table[hash_idx];                                  \
    hash->table[hash_idx] = new_idx

#define INDEX_ADD_LINK_128(hash, t_index, new_idx)                  \
    hash->link_table[new_idx & FB_LPM_128_HASH_INDEX_MASK] =        \
        hash->link_table[t_index & FB_LPM_128_HASH_INDEX_MASK];     \
    hash->link_table[t_index & FB_LPM_128_HASH_INDEX_MASK] = new_idx

#define INDEX_UPDATE_128(hash, hash_idx, old_idx, new_idx)          \
    hash->table[hash_idx] = new_idx;                            \
    hash->link_table[new_idx & FB_LPM_128_HASH_INDEX_MASK] =        \
        hash->link_table[old_idx & FB_LPM_128_HASH_INDEX_MASK];     \
    hash->link_table[old_idx & FB_LPM_128_HASH_INDEX_MASK] = FB_LPM_128_HASH_INDEX_NULL

#define INDEX_UPDATE_LINK_128(hash, prev_idx, old_idx, new_idx)             \
    hash->link_table[prev_idx & FB_LPM_128_HASH_INDEX_MASK] = new_idx;      \
    hash->link_table[new_idx & FB_LPM_128_HASH_INDEX_MASK] =                \
        hash->link_table[old_idx & FB_LPM_128_HASH_INDEX_MASK];             \
    hash->link_table[old_idx & FB_LPM_128_HASH_INDEX_MASK] = FB_LPM_128_HASH_INDEX_NULL


    int u = hash->unit, v, i = 0;

    uint16 hash_val;
    uint16 index;
    uint16 prev_index;

    if (rvt_index) {
        *rvt_index = FB_LPM_128_HASH_INDEX_NULL;
    }
    hash_val = _soc_th_alpm_128_lpm_hash_compute((uint8 *)entry,
                                        (32 * 9)) % hash->index_count;
    index = hash->table[hash_val];
    H_INDEX_MATCH_128("ihash", entry[0], hash_val);
    H_INDEX_MATCH_128("ins  ", entry[0], new_index);
    H_INDEX_MATCH_128("ins1 ", index, new_index);
    prev_index = FB_LPM_128_HASH_INDEX_NULL;
    if (old_index != FB_LPM_128_HASH_INDEX_NULL) {
        while(index != FB_LPM_128_HASH_INDEX_NULL && i++ < hash->entry_count) {
            uint32  e[SOC_MAX_MEM_FIELD_WORDS];
            _soc_th_alpm_128_lpm_hash_entry_t  r_entry;
            int     rindex;

            rindex = index;

            /*
             * Check prefix length and skip index if not valid for given length
            if ((SOC_ALPM_LPM_STATE_START(u, pfx) <= rindex) &&
                (SOC_ALPM_LPM_STATE_END(u, pfx) >= rindex)) {
             */
            SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m,
                                                   MEM_BLOCK_ANY, rindex, e));
            SOC_FB_LPM_128_HASH_ENTRY_GET(u, e, index, r_entry, &v);
            if (v == 0) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                                    "Empty entry[%d] in link_table. hash_val %d ridx %d nidx %d\n"),
                                    index, hash_val, rindex, new_index));
            }
            if (v && ((*key_cmp_fn)(entry, r_entry) == 0)) {
                /* assert(old_index == index);*/
                if (new_index != index) {
                    H_INDEX_MATCH_128("imove", prev_index, new_index);
                    if (prev_index == FB_LPM_128_HASH_INDEX_NULL) {
                        INDEX_UPDATE_128(hash, hash_val, index, new_index);
                    } else {
                        INDEX_UPDATE_LINK_128(hash, prev_index, index,
                                          new_index);
                    }
                }
                if (rvt_index) {
                    *rvt_index = index;
                }
                H_INDEX_MATCH_128("imtch", index, new_index);
                return(SOC_E_NONE);
            }
            /*
            }
            */
            prev_index = index;
            index = hash->link_table[index & FB_LPM_128_HASH_INDEX_MASK];
            H_INDEX_MATCH_128("ins2 ", index, new_index);
        }
    }
    if (i > hash->entry_count) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                            "Hash loop\n")));
        return SOC_E_INTERNAL;
    }
    INDEX_ADD_128(hash, hash_val, new_index);  /* new entry */
    return(SOC_E_NONE);
}

/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_revert
 * Purpose:
 *      Revert a key index in the hash table
 * Parameters:
 *      hash - Pointer (handle) to Hash Table
 *      key_cmp_fn - Compare function which should compare key
 *      entry   - The key to delete
 *      pfx     - Prefix length for lookup acceleration.
 *      delete_index - Index to delete.
 * Returns:
 *      SOC_E_NONE      Success
 *      SOC_E_NOT_FOUND Key index not found.
 */
static
int _soc_th_alpm_128_lpm_hash_revert(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            uint16 new_index,
                            uint32 rvt_index)
{
    int u = hash->unit, i = 0;
    uint16 hash_val;
    uint16 index;
    uint16 prev_index;

    hash_val = _soc_th_alpm_128_lpm_hash_compute((uint8 *)entry,
                                        (32 * 9)) % hash->index_count;
    index = hash->table[hash_val];
    H_INDEX_MATCH_128("rhash", entry[0], hash_val);
    H_INDEX_MATCH_128("rvt  ", entry[0], index);
    prev_index = FB_LPM_128_HASH_INDEX_NULL;
    while(index != FB_LPM_128_HASH_INDEX_NULL && i++ < hash->entry_count) {
        if (new_index == index) {
            H_INDEX_MATCH_128("dfoun", entry[0], index);
            if (rvt_index == FB_LPM_128_HASH_INDEX_NULL) {
                if (prev_index == FB_LPM_128_HASH_INDEX_NULL) {
                    INDEX_DELETE_128(hash, hash_val, new_index);
                } else {
                    INDEX_DELETE_LINK_128(hash, prev_index, new_index);
                }
            } else {
                if (prev_index == FB_LPM_128_HASH_INDEX_NULL) {
                    INDEX_UPDATE_128(hash, hash_val, new_index, rvt_index);
                } else {
                    INDEX_UPDATE_LINK_128(hash, prev_index, new_index,
                                      rvt_index);
                }
            }
            return(SOC_E_NONE);
        }
        prev_index = index;
        index = hash->link_table[index & FB_LPM_128_HASH_INDEX_MASK];
        H_INDEX_MATCH_128("rvt1 ", entry[0], index);
    }
    if (i > hash->entry_count) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                            "Hash loop\n")));
    }
    return(SOC_E_NOT_FOUND);
}


/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_delete
 * Purpose:
 *      Delete a key index in the hash table
 * Parameters:
 *      hash - Pointer (handle) to Hash Table
 *      key_cmp_fn - Compare function which should compare key
 *      entry   - The key to delete
 *      pfx     - Prefix length for lookup acceleration.
 *      delete_index - Index to delete.
 * Returns:
 *      SOC_E_NONE      Success
 *      SOC_E_NOT_FOUND Key index not found.
 */
static
int _soc_th_alpm_128_lpm_hash_delete(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int    pfx,
                            uint16 delete_index)
{
    int u = hash->unit, i = 0;
    uint16 hash_val;
    uint16 index;
    uint16 prev_index;

    hash_val = _soc_th_alpm_128_lpm_hash_compute((uint8 *)entry,
                                        (32 * 9)) % hash->index_count;
    index = hash->table[hash_val];
    H_INDEX_MATCH_128("dhash", entry[0], hash_val);
    H_INDEX_MATCH_128("del  ", entry[0], index);
    prev_index = FB_LPM_128_HASH_INDEX_NULL;
    while(index != FB_LPM_128_HASH_INDEX_NULL && i++ < hash->entry_count) {
        if (delete_index == index) {
            H_INDEX_MATCH_128("dfoun", entry[0], index);
            if (prev_index == FB_LPM_128_HASH_INDEX_NULL) {
                INDEX_DELETE_128(hash, hash_val, delete_index);
            } else {
                INDEX_DELETE_LINK_128(hash, prev_index, delete_index);
            }
            return(SOC_E_NONE);
        }
        prev_index = index;
        index = hash->link_table[index & FB_LPM_128_HASH_INDEX_MASK];
        H_INDEX_MATCH_128("del1 ", entry[0], index);
    }
    if (i > hash->entry_count) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                            "Hash loop\n")));
    }
    return(SOC_E_NOT_FOUND);
}


/*
 * Function:
 *      _soc_th_alpm_128_lpm_hash_verify
 * Purpose:
 *      Verify a key index in the hash table
 * Parameters:
 *      hash - Pointer (handle) to Hash Table
 *      key_cmp_fn - Compare function which should compare key
 *      entry   - The key to verify
 *      pfx     - Prefix length for lookup acceleration.
 *      verify_index   - Index to verify.
 * Returns:
 *      SOC_E_NONE      Success
 *      SOC_E_NOT_FOUND Key index not found.
 */
static
int _soc_th_alpm_128_lpm_hash_verify(_soc_th_alpm_128_lpm_hash_t *hash,
                            _soc_th_alpm_128_lpm_hash_compare_fn key_cmp_fn,
                            _soc_th_alpm_128_lpm_hash_entry_t entry,
                            int    pfx,
                            uint16 verify_index)
{
    int u = hash->unit, i = 0;
    uint16 hash_val;
    uint16 index;

    hash_val = _soc_th_alpm_128_lpm_hash_compute((uint8 *)entry,
                                        (32 * 9)) % hash->index_count;
    index = hash->table[hash_val];
    H_INDEX_MATCH_128("vhash", entry[0], hash_val);
    H_INDEX_MATCH_128("veri ", entry[0], index);
    while(index != FB_LPM_128_HASH_INDEX_NULL && i++ < hash->entry_count) {
        if (verify_index == index) {
            H_INDEX_MATCH_128("vfoun", entry[0], index);
            return(SOC_E_NONE);
        }
        index = hash->link_table[index & FB_LPM_128_HASH_INDEX_MASK];
        H_INDEX_MATCH_128("veri1", entry[0], index);
    }
    if (i > hash->entry_count) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                  (BSL_META_U(u,
                            "Hash loop\n")));
    }
    return(SOC_E_NOT_FOUND);
}

#else
#define LPM_128_HASH_INSERT(u, entry_data, tab_index, rvt_index)
#define LPM_128_HASH_REVERT(u, entry_data, tab_index, rvt_index)
#define LPM_128_HASH_DELETE(u, key_data, tab_index)
#define LPM_128_HASH_LOOKUP(u, key_data, pfx, tab_index)
#define LPM_128_HASH_VERIFY(u, key_data, tab_index)
#endif /* FB_LPM_128_HASH_SUPPORT */

void
soc_th_alpm_128_lpm_state_dump(int u)
{
    int i;
    int max_pfx_len;
    max_pfx_len = MAX_PFX_INDEX_128;

    if (!bsl_check(bslLayerSoc, bslSourceAlpm, bslSeverityVerbose, u)) {
        return;
    }
    for(i = max_pfx_len; i >= 0 ; i--) {
        if ((i != MAX_PFX_INDEX_128) && (SOC_ALPM_128_LPM_STATE_START(u, i) == -1)) {
            continue;
        }
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u,
                    "PFX = %d P = %d N = %d START = %d "
                    "END = %d VENT = %d FENT = %d\n"),
                    i,
                    SOC_ALPM_128_LPM_STATE_PREV(u, i),
                    SOC_ALPM_128_LPM_STATE_NEXT(u, i),
                    SOC_ALPM_128_LPM_STATE_START(u, i),
                    SOC_ALPM_128_LPM_STATE_END(u, i),
                    SOC_ALPM_128_LPM_STATE_VENT(u, i),
                    SOC_ALPM_128_LPM_STATE_FENT(u, i)));
    }
}

/*
 *      Create a slot for the new entry rippling the entries if required
 */
static
int _lpm_128_fb_entry_shift(int u, int from_ent, int to_ent)
{
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    uint32      rvt_index = 0;
    int         rv;

#ifdef FB_LPM_TABLE_CACHED
    SOC_IF_ERROR_RETURN(soc_mem_cache_invalidate(u, L3_DEFIP_PAIR_128m,
                                       MEM_BLOCK_ANY, from_ent));
#endif /* FB_LPM_TABLE_CACHED */

    SOC_IF_ERROR_RETURN(_soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m,
                                           MEM_BLOCK_ANY, from_ent, e));
    LPM_128_HASH_INSERT(u, e, to_ent, &rvt_index);
    rv = _soc_th_alpm_128_write_pivot(u, MEM_BLOCK_ANY, to_ent, from_ent, e,
                                      INVALID_BPM_LEN, 0, 0);
    if (rv < 0) {
        LPM_128_HASH_REVERT(u, e, to_ent, rvt_index);
        return rv;
    }

    SOC_ALPM_MOVE_PIVOT_FULL_128(u, from_ent, to_ent);

    return (SOC_E_NONE);
}


/*
 *      Shift prefix entries 1 entry UP, while preserving
 *      last half empty IPv4 entry if any.
 */
static
int _lpm_128_fb_shift_pfx_up(int u, int pfx, int ipv6)
{
    int         from_ent;
    int         to_ent;

    to_ent = SOC_ALPM_128_LPM_STATE_END(u, pfx) + 1;

    from_ent = SOC_ALPM_128_LPM_STATE_START(u, pfx);
    if (from_ent != to_ent) {
        SOC_IF_ERROR_RETURN(_lpm_128_fb_entry_shift(u, from_ent, to_ent));
        /* Store Shift counter in MAX_VRF_ID */
        VRF_PIVOT_SHIFT_INC(u, MAX_VRF_ID, ipv6);
    }
    SOC_ALPM_128_LPM_STATE_START(u, pfx) += 1;
    SOC_ALPM_128_LPM_STATE_END(u, pfx) += 1;
    return (SOC_E_NONE);
}

/*
 *      Shift prefix entries 1 entry DOWN, while preserving
 *      last half empty IPv4 entry if any.
 */
static
int _lpm_128_fb_shift_pfx_down(int u, int pfx, int ipv6)
{
    int         from_ent;
    int         to_ent;

    to_ent = SOC_ALPM_128_LPM_STATE_START(u, pfx) - 1;

    /* Don't move empty prefix . */
    if (SOC_ALPM_128_LPM_STATE_VENT(u, pfx) == 0) {
        SOC_ALPM_128_LPM_STATE_START(u, pfx) = to_ent;
        SOC_ALPM_128_LPM_STATE_END(u, pfx) = to_ent - 1;
        return (SOC_E_NONE);
    }

    from_ent = SOC_ALPM_128_LPM_STATE_END(u, pfx);
    SOC_IF_ERROR_RETURN(_lpm_128_fb_entry_shift(u, from_ent, to_ent));
    /* Store Shift counter in MAX_VRF_ID */
    VRF_PIVOT_SHIFT_INC(u, MAX_VRF_ID, ipv6);

    SOC_ALPM_128_LPM_STATE_START(u, pfx) -= 1;
    SOC_ALPM_128_LPM_STATE_END(u, pfx) -= 1;

    return (SOC_E_NONE);
}

/*
 *      Create a slot for the new entry rippling the entries if required
 */
static
int _lpm_128_free_slot_create(int u, int pfx, int ipv6, void *e, int *free_slot)
{
    int         prev_pfx;
    int         next_pfx;
    int         free_pfx;
    int         curr_pfx;


    if (SOC_ALPM_128_LPM_STATE_VENT(u, pfx) == 0) {
        /*
         * Find the  prefix position. Only prefix with valid
         * entries are in the list.
         * next -> high to low prefix. low to high index
         * prev -> low to high prefix. high to low index
         * Unused prefix length MAX_PFX_INDEX_128 is the head of the
         * list and is node corresponding to this is always
         * present.
         */
        curr_pfx = MAX_PFX_INDEX_128;
        if (ALPM_CTRL(u).gp_zoned) {
            if (pfx <= MAX_VRF_PFX_INDEX_128) {
                curr_pfx = MAX_VRF_PFX_INDEX_128;
            }
        }
        while (SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx) > pfx) {
            curr_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx);
        }
        /* Insert the new prefix */
        next_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx);
        if (next_pfx != -1) {
            SOC_ALPM_128_LPM_STATE_PREV(u, next_pfx) = pfx;
        }
        SOC_ALPM_128_LPM_STATE_NEXT(u, pfx) = SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx);
        SOC_ALPM_128_LPM_STATE_PREV(u, pfx) = curr_pfx;
        SOC_ALPM_128_LPM_STATE_NEXT(u, curr_pfx) = pfx;

        SOC_ALPM_128_LPM_STATE_FENT(u, pfx) =  (SOC_ALPM_128_LPM_STATE_FENT(u, curr_pfx) + 1) / 2;
        SOC_ALPM_128_LPM_STATE_FENT(u, curr_pfx) -= SOC_ALPM_128_LPM_STATE_FENT(u, pfx);
        SOC_ALPM_128_LPM_STATE_START(u, pfx) =  SOC_ALPM_128_LPM_STATE_END(u, curr_pfx) +
                                       SOC_ALPM_128_LPM_STATE_FENT(u, curr_pfx) + 1;
        SOC_ALPM_128_LPM_STATE_END(u, pfx) = SOC_ALPM_128_LPM_STATE_START(u, pfx) - 1;
        SOC_ALPM_128_LPM_STATE_VENT(u, pfx) = 0;
    }

    free_pfx = pfx;
    while(SOC_ALPM_128_LPM_STATE_FENT(u, free_pfx) == 0) {
        free_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, free_pfx);
        if (free_pfx == -1) {
            /* No free entries on this side try the other side */
            free_pfx = pfx;
            break;
        }
    }

    while(SOC_ALPM_128_LPM_STATE_FENT(u, free_pfx) == 0) {
        free_pfx = SOC_ALPM_128_LPM_STATE_PREV(u, free_pfx);
        if (free_pfx == -1) {
            if (SOC_ALPM_128_LPM_STATE_VENT(u, pfx) == 0) {
                /* We failed to allocate entries for a newly allocated prefix.*/
                prev_pfx = SOC_ALPM_128_LPM_STATE_PREV(u, pfx);
                next_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, pfx);
                if (-1 != prev_pfx) {
                    SOC_ALPM_128_LPM_STATE_NEXT(u, prev_pfx) = next_pfx;
                }
                if (-1 != next_pfx) {
                    SOC_ALPM_128_LPM_STATE_PREV(u, next_pfx) = prev_pfx;
                }
            }
            return(SOC_E_FULL);
        }
    }

    /*
     * Ripple entries to create free space
     */
    while (free_pfx > pfx) {
        next_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, free_pfx);
        SOC_IF_ERROR_RETURN(_lpm_128_fb_shift_pfx_down(u, next_pfx, ipv6));
        SOC_ALPM_128_LPM_STATE_FENT(u, free_pfx) -= 1;
        SOC_ALPM_128_LPM_STATE_FENT(u, next_pfx) += 1;
        free_pfx = next_pfx;
    }

    while (free_pfx < pfx) {
        SOC_IF_ERROR_RETURN(_lpm_128_fb_shift_pfx_up(u, free_pfx, ipv6));
        SOC_ALPM_128_LPM_STATE_FENT(u, free_pfx) -= 1;
        prev_pfx = SOC_ALPM_128_LPM_STATE_PREV(u, free_pfx);
        SOC_ALPM_128_LPM_STATE_FENT(u, prev_pfx) += 1;
        free_pfx = prev_pfx;
    }

    SOC_ALPM_128_LPM_STATE_VENT(u, pfx) += 1;
    SOC_ALPM_128_LPM_STATE_FENT(u, pfx) -= 1;
    SOC_ALPM_128_LPM_STATE_END(u, pfx) += 1;
    *free_slot = SOC_ALPM_128_LPM_STATE_END(u, pfx);
    sal_memcpy(e, soc_mem_entry_null(u, L3_DEFIP_PAIR_128m),
               soc_mem_entry_words(u,L3_DEFIP_PAIR_128m) * 4);

    return(SOC_E_NONE);
}

/*
 *      Delete a slot and adjust entry pointers if required.
 *      e - has the contents of entry at slot(useful for IPV4 only)
 */
static
int _lpm_128_free_slot_delete(int u, int pfx, int ipv6, void *e, int slot)
{
    int         prev_pfx;
    int         next_pfx;
    int         from_ent;
    int         to_ent;
    uint32      ef[SOC_MAX_MEM_FIELD_WORDS];
    int         rv;
    int         tmp;
    uint32      rvt_index = 0;

    from_ent = SOC_ALPM_128_LPM_STATE_END(u, pfx);
    to_ent = slot;
    SOC_ALPM_128_LPM_STATE_VENT(u, pfx) -= 1;
    SOC_ALPM_128_LPM_STATE_FENT(u, pfx) += 1;
    SOC_ALPM_128_LPM_STATE_END(u, pfx) -= 1;
    if (to_ent != from_ent) {
#ifdef FB_LPM_TABLE_CACHED
        if ((rv = soc_mem_cache_invalidate(u, L3_DEFIP_PAIR_128m,
                                           MEM_BLOCK_ANY, from_ent)) < 0) {
            return rv;
        }
#endif /* FB_LPM_TABLE_CACHED */
        if ((rv = _soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m,
                                     MEM_BLOCK_ANY, from_ent, ef)) < 0) {
            return rv;
        }
        LPM_128_HASH_INSERT(u, ef, to_ent, &rvt_index);
        /* coverity[copy_paste_error : FALSE] */
        if ((rv = _soc_th_alpm_128_write_pivot(u, MEM_BLOCK_ANY, to_ent, from_ent, ef,
                                               INVALID_BPM_LEN, 0, 0)) < 0)
        {
            LPM_128_HASH_REVERT(u, ef, to_ent, rvt_index);
            return rv;
        }
    }
    /* v6-128 indices are still raw in pivot tcam */
    tmp = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, to_ent, 1);
    slot = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, from_ent, 1);
    ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, tmp) << 1) =
                      ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, slot) << 1);
    if (ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, tmp) << 1)) {
        PIVOT_TCAM_INDEX(ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, tmp) << 1)) =
                         SOC_ALPM_128_ADDR_LWR(u, tmp) << 1;
        SOC_ALPM_BU_PIVOT_IDX_UPDATE(u, SOC_ALPM_128_ADDR_LWR(u, tmp) << 1);
    }
    ALPM_TCAM_PIVOT(u, SOC_ALPM_128_ADDR_LWR(u, slot) << 1) = NULL;

    sal_memcpy(ef, soc_mem_entry_null(u, L3_DEFIP_PAIR_128m),
               soc_mem_entry_words(u,L3_DEFIP_PAIR_128m) * 4);
    LPM_128_HASH_INSERT(u, ef, from_ent, &rvt_index);
    if ((rv = _soc_th_alpm_128_write_pivot(u, MEM_BLOCK_ANY, from_ent, from_ent,
                                           ef, INVALID_BPM_LEN, 0, 0)) < 0) {
        LPM_128_HASH_REVERT(u, ef, from_ent, rvt_index);
        return rv;
    }
    if (SOC_ALPM_128_LPM_STATE_VENT(u, pfx) == 0) {
        /* remove from the list */
        prev_pfx = SOC_ALPM_128_LPM_STATE_PREV(u, pfx); /* Always present */
        assert(prev_pfx != -1);
        next_pfx = SOC_ALPM_128_LPM_STATE_NEXT(u, pfx);
        SOC_ALPM_128_LPM_STATE_NEXT(u, prev_pfx) = next_pfx;
        SOC_ALPM_128_LPM_STATE_FENT(u, prev_pfx) +=
                                            SOC_ALPM_128_LPM_STATE_FENT(u, pfx);
        SOC_ALPM_128_LPM_STATE_FENT(u, pfx) = 0;
        if (next_pfx != -1) {
            SOC_ALPM_128_LPM_STATE_PREV(u, next_pfx) = prev_pfx;
        }
        SOC_ALPM_128_LPM_STATE_NEXT(u, pfx) = -1;
        SOC_ALPM_128_LPM_STATE_PREV(u, pfx) = -1;
        SOC_ALPM_128_LPM_STATE_START(u, pfx) = -1;
        SOC_ALPM_128_LPM_STATE_END(u, pfx) = -1;
    }

    return(rv);
}

/*
 * Function:
 *      soc_th_alpm_128_lpm_vrf_get
 * Purpose:
 *      Service routine used to translate hw specific vrf id to API format.
 * Parameters:
 *      unit      - (IN)SOC unit number.
 *      lpm_entry - (IN)Route info buffer from hw.
 *      vrf_id    - (OUT)Virtual router id.
 * Returns:
 *      BCM_E_XXX
 */
int
soc_th_alpm_128_lpm_vrf_get(int unit, void *lpm_entry, int *vrf_id, int *vrf)
{
    int mem_vrf;

    /* Get Virtual Router id if supported. */
    if (SOC_MEM_OPT_FIELD_VALID_128(unit, L3_DEFIP_PAIR_128m,
                                            VRF_ID_MASK0_LWRf)){
        mem_vrf = SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry,
                                         VRF_ID_0_LWRf);

        /* Special vrf_id's handling. */
        if (SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry,
                                    VRF_ID_MASK0_LWRf)) {
            *vrf_id = mem_vrf;
        } else if (!SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m,
                lpm_entry, GLOBAL_HIGHf)) {
            *vrf_id = SOC_L3_VRF_GLOBAL;
        } else {
            *vrf_id = SOC_L3_VRF_OVERRIDE;
        }
        if (vrf) {
            if (*vrf_id == SOC_L3_VRF_GLOBAL) {
                *vrf = SOC_VRF_MAX(unit) + 1;
            } else {
                *vrf = mem_vrf;
            }
        }
    } else {
        /* No vrf support on this device. */
        *vrf_id = SOC_L3_VRF_DEFAULT;
    }
    return (SOC_E_NONE);
}

/*
 * _soc_th_alpm_128_lpm_prefix_length_get (Extract vrf weighted  prefix lenght from the
 * hw entry based on ip, mask & vrf)
 */
static int
_soc_th_alpm_128_lpm_prefix_length_get(int u, void *entry, int *pfx_len,
                                       int *vrf_id,
                                       int *vrf)
{
    int         pfx=0;
    int         rv;
    int         vrfid;
    int         mode;

    rv = _soc_th_alpm_128_ip6_mask_len_get(u, entry, &pfx);
    if (rv < 0) {
        return rv;
    }
    pfx += IPV6_128_PFX_ZERO; /* Now only v6-128 */

    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(u, entry, &vrfid, &rv));
    if (vrf_id != NULL) {
        *vrf_id = vrfid;
    }
    if (vrf != NULL) {
        *vrf = rv;
    }

    /* In ALPM the arragnement of VRF is at he begining followed by VRF
     * override and global */
    mode = ALPM_CTRL(u).alpm_mode;
    switch (vrfid) {
      case SOC_L3_VRF_GLOBAL:
          if ((mode == SOC_ALPM_MODE_PARALLEL) ||
              (mode == SOC_ALPM_MODE_TCAM_ALPM)) {
            *pfx_len = pfx + (MAX_PFX_ENTRIES_128 / 3);
          } else {
            *pfx_len = pfx;
          }
          break;
      case SOC_L3_VRF_OVERRIDE:
            *pfx_len = pfx +  2 * (MAX_PFX_ENTRIES_128 / 3);
          break;
      default:
          if ((mode == SOC_ALPM_MODE_PARALLEL) ||
              (mode == SOC_ALPM_MODE_TCAM_ALPM)) {
            *pfx_len = pfx;
          } else {
            *pfx_len = pfx +  (MAX_PFX_ENTRIES_128 / 3);
          }
          break;
    }
    return (SOC_E_NONE);
}

/*
 * _soc_th_alpm_128_lpm_match (Exact match for the key.
 * Will match both IP address and mask)
 */
static int
_soc_th_alpm_128_lpm_match(int u,
               void *key_data,
               void *e,         /* return entry data if found */
               int *index_ptr,  /* return key location */
               int *pfx_len,    /* Key prefix length. vrf+32+pfx len for v6*/
               int *ipv6,       /* Entry is ipv6. */
               int *vrf_id,     /* (OUT) */
               int *vrf)        /* (OUT) */
{
    int         rv;
    int         key_index;
    int         pfx = 0;

    *ipv6 = L3_DEFIP_MODE_128;

    /* Calculate vrf weighted prefix lengh. */
    _soc_th_alpm_128_lpm_prefix_length_get(u, key_data, &pfx, vrf_id, vrf);
    *pfx_len = pfx;

#ifdef FB_LPM_128_HASH_SUPPORT
    if (LPM_128_HASH_LOOKUP(u, key_data, pfx, &key_index) == SOC_E_NONE) {
        *index_ptr = key_index;
        if ((rv = _soc_mem_alpm_read(u, L3_DEFIP_PAIR_128m, MEM_BLOCK_ANY,
                         (*ipv6) ? *index_ptr : (*index_ptr >> 1), e)) < 0) {
            return rv;
        }
#ifndef  FB_LPM_CHECKER_ENABLE
        return(SOC_E_NONE);
#endif
    } else {
#ifndef  FB_LPM_CHECKER_ENABLE
        return(SOC_E_NOT_FOUND);
#endif
    }
#endif /* FB_LPM_128_HASH_SUPPORT */
}

/*
 * Initialize the start/end tracking pointers for each prefix length
 */
int
soc_th_alpm_128_lpm_init(int u)
{
    int max_pfx_len;
    int i;
    int defip_table_size;
    int pfx_state_size;

    if (! soc_feature(u, soc_feature_lpm_tcam)) {
        return(SOC_E_UNAVAIL);
    }

    max_pfx_len = MAX_PFX_ENTRIES_128;

    pfx_state_size = sizeof(soc_th_alpm_128_lpm_state_t) * (max_pfx_len);

    if (SOC_ALPM_128_LPM_INIT_CHECK(u)) {
        /* this is a reinit. clean up old state */
        SOC_IF_ERROR_RETURN(soc_th_alpm_128_deinit(u));
    }
    soc_lpm_128_field_cache_state[u] =
           sal_alloc(sizeof(soc_lpm_128_field_cache_t), "lpm_128_field_state");
    if (NULL == soc_lpm_128_field_cache_state[u]) {
        return (SOC_E_MEMORY);
    }
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, CLASS_IDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, DST_DISCARDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, SRC_DISCARDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ECMPf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ECMP_COUNTf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ECMP_PTRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, GLOBAL_ROUTEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, RPA_IDf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, EXPECTED_L3_IIFf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IPMC_EXPECTED_L3_IIF_MISMATCH_TOCPUf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IPMC_EXPECTED_L3_IIF_MISMATCH_DROPf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, L3MC_INDEXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, HITf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR_MASK0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR_MASK0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR_MASK1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, IP_ADDR_MASK1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, NEXT_HOP_INDEXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, PRIf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, RPEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VALID0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VALID0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VALID1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VALID1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_MASK0_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_MASK0_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_MASK1_LWRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, VRF_ID_MASK1_UPRf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, GLOBAL_HIGHf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ALG_HIT_IDXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ALG_BKT_PTRf);
    if (ALPM_CTRL(u).bkt_sharing) {
        SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, ALG_SUB_BKT_PTRf);
    }
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, DEFAULT_MISSf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m,
                                    FLEX_CTR_BASE_COUNTER_IDXf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m,
                                    FLEX_CTR_OFFSET_MODEf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m,
                                    FLEX_CTR_POOL_NUMBERf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m, DESTINATIONf);
    SOC_ALPM_128_LPM_CACHE_FIELD_ASSIGN(u, soc_lpm_128_field_cache_state[u],
                                    L3_DEFIP_PAIR_128m,
                                    ENTRY_VIEWf);
    SOC_ALPM_128_LPM_STATE(u) = sal_alloc(pfx_state_size,
                                          "LPM 128 prefix info");
    if (NULL == SOC_ALPM_128_LPM_STATE(u)) {
        sal_free(soc_lpm_128_field_cache_state[u]);
        soc_lpm_128_field_cache_state[u] = NULL;
        return (SOC_E_MEMORY);
    }

#ifdef FB_LPM_TABLE_CACHED
    SOC_IF_ERROR_RETURN (soc_mem_cache_set(u, L3_DEFIP_PAIR_128m,
                                           MEM_BLOCK_ALL, TRUE));
#endif /* FB_LPM_TABLE_CACHED */
    SOC_ALPM_LPM_LOCK(u);

    sal_memset(SOC_ALPM_128_LPM_STATE(u), 0, pfx_state_size);
    for(i = 0; i < max_pfx_len; i++) {
        SOC_ALPM_128_LPM_STATE_START(u, i) = -1;
        SOC_ALPM_128_LPM_STATE_END(u, i) = -1;
        SOC_ALPM_128_LPM_STATE_PREV(u, i) = -1;
        SOC_ALPM_128_LPM_STATE_NEXT(u, i) = -1;
        SOC_ALPM_128_LPM_STATE_VENT(u, i) = 0;
        SOC_ALPM_128_LPM_STATE_FENT(u, i) = 0;
    }

    defip_table_size = soc_mem_index_count(u, L3_DEFIP_PAIR_128m);

    /* RPF supported, then the table is partitioned for DIP and SIP */
    if (SOC_URPF_STATUS_GET(u)) {
            defip_table_size >>= 1;
    }

    if (ALPM_CTRL(u).gp_zoned) {
        
        /* For Parallel search, the TCAM is hard paritioned.
        * First half are for VRF specific, the bottom half for override and
        * global. Start of Global entries start at the bottom half of TCAM
        */
        SOC_ALPM_128_LPM_STATE_END(u, MAX_PFX_INDEX_128) =
                                                    (defip_table_size>>1) - 1;

        /* Free entries for VRF */
        SOC_ALPM_128_LPM_STATE_FENT(u, (MAX_VRF_PFX_INDEX_128)) =
                                                    defip_table_size >> 1;

        /* Remaining entries are assigned to Global entries */
        SOC_ALPM_128_LPM_STATE_FENT(u, (MAX_PFX_INDEX_128)) =
          (defip_table_size - SOC_ALPM_128_LPM_STATE_FENT(u,
                                                     (MAX_VRF_PFX_INDEX_128)));
    } else {
        /* Remaining entries are assigned to Global entries */
        SOC_ALPM_128_LPM_STATE_FENT(u, (MAX_PFX_INDEX_128)) = defip_table_size;
    }

#ifdef FB_LPM_128_HASH_SUPPORT
    if (SOC_ALPM_128_LPM_STATE_HASH(u) != NULL) {
        if (_soc_th_alpm_128_lpm_hash_destroy(SOC_ALPM_128_LPM_STATE_HASH(u)) < 0){
            SOC_ALPM_LPM_UNLOCK(u);
            return SOC_E_INTERNAL;
        }
        SOC_ALPM_128_LPM_STATE_HASH(u) = NULL;
    }

    if (_soc_th_alpm_128_lpm_hash_create(u, defip_table_size * 2, defip_table_size,
                                &SOC_ALPM_128_LPM_STATE_HASH(u)) < 0) {
        SOC_ALPM_LPM_UNLOCK(u);
        return SOC_E_MEMORY;
    }
#endif

    SOC_ALPM_LPM_UNLOCK(u);
    return(SOC_E_NONE);
}

/*
 * De-initialize the start/end tracking pointers for each prefix length
 */
int
soc_th_alpm_128_lpm_deinit(int u)
{
    if (!soc_feature(u, soc_feature_lpm_tcam)) {
        return(SOC_E_UNAVAIL);
    }

    SOC_ALPM_LPM_LOCK(u);

#ifdef FB_LPM_128_HASH_SUPPORT
    if (SOC_ALPM_128_LPM_STATE_HASH(u) != NULL) {
        _soc_th_alpm_128_lpm_hash_destroy(SOC_ALPM_128_LPM_STATE_HASH(u));
        SOC_ALPM_128_LPM_STATE_HASH(u) = NULL;
    }
#endif

    if (SOC_ALPM_128_LPM_INIT_CHECK(u)) {
        sal_free(soc_lpm_128_field_cache_state[u]);
        soc_lpm_128_field_cache_state[u] = NULL;
        sal_free(SOC_ALPM_128_LPM_STATE(u));
        SOC_ALPM_128_LPM_STATE(u) = NULL;
    }

    SOC_ALPM_LPM_UNLOCK(u);

    return(SOC_E_NONE);
}

/*
 * Implementation using soc_mem_read/write using entry rippling technique
 * Advantage: A completely sorted table is not required. Lookups can be slow
 * as it will perform a linear search on the entries for a given prefix length.
 * No device access necessary for the search if the table is cached. Auxiliary
 * hash table can be maintained to speed up search(Not implemented) instead of
 * performing a linear search.
 * Small number of entries need to be moved around (97 worst case)
 * for performing insert/update/delete. However CPU needs to do all
 * the work to move the entries.
 */

/*
 * soc_th_alpm_128_lpm_insert
 * Moving multiple entries around in h/w vs  doing a linear search in s/w
 */
static int
soc_th_alpm_128_lpm_insert(int u, void *entry_data, int *lpm_index, int bpm_len,
                           int src_default, int src_discard)
{
    int         pfx;
    int         index;
    int         ipv6;
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    int         rv = SOC_E_NONE;
    int         found = 0;
    uint32      rvt_index = 0;
    int         vrf, vrf_id;

    sal_memcpy(e, soc_mem_entry_null(u, L3_DEFIP_PAIR_128m),
               soc_mem_entry_words(u,L3_DEFIP_PAIR_128m) * 4);

    SOC_ALPM_LPM_LOCK(u);
    rv = _soc_th_alpm_128_lpm_match(u, entry_data, e, &index, &pfx, &ipv6, &vrf_id, &vrf);
    if (rv == SOC_E_NOT_FOUND) {
        rv = _lpm_128_free_slot_create(u, pfx, ipv6, e, &index);
        if (rv < 0) {
            SOC_ALPM_LPM_UNLOCK(u);
            return(rv);
        }
    } else {
        found = 1;
    }

    *lpm_index = index;

    if (rv == SOC_E_NONE) {
        /* Entry already present. Update the entry */
        soc_th_alpm_128_lpm_state_dump(u);
        LOG_INFO(BSL_LS_SOC_ALPM,
                 (BSL_META_U(u,
                 "soc_th_alpm_128_lpm_insert: %d %d\n"),
                  index, pfx));
        if (!found) {
            LPM_128_HASH_INSERT(u, entry_data, index, &rvt_index);
        }
        rv = _soc_th_alpm_128_write_pivot(u, MEM_BLOCK_ANY, index, index,
                                          entry_data, bpm_len, src_default,
                                          src_discard);
        if (!found) {
            if (SOC_SUCCESS(rv)) {
                VRF_PIVOT_REF_INC(u, vrf_id, vrf, ipv6);
            } else {
                LPM_128_HASH_REVERT(u, entry_data, index, rvt_index);
            }
        }
    }

    SOC_ALPM_LPM_UNLOCK(u);

    return(rv);
}

/*
 * soc_th_alpm_128_lpm_delete
 */
static int
soc_th_alpm_128_lpm_delete(int u, void *key_data)
{
    int         pfx;
    int         index;
    int         ipv6;
    uint32      e[SOC_MAX_MEM_FIELD_WORDS];
    int         rv = SOC_E_NONE;
    int         vrf, vrf_id;

    SOC_ALPM_LPM_LOCK(u);
    rv = _soc_th_alpm_128_lpm_match(u, key_data, e, &index, &pfx, &ipv6, &vrf_id, &vrf);
    if (rv == SOC_E_NONE) {
        LOG_INFO(BSL_LS_SOC_ALPM,
                 (BSL_META_U(u,
                 "soc_th_alpm_lpm_delete: %d %d\n"),
                 index, pfx));
        LPM_128_HASH_DELETE(u, key_data, index);
        rv = _lpm_128_free_slot_delete(u, pfx, ipv6, e, index);
    }
    if (SOC_SUCCESS(rv)) {
        VRF_PIVOT_REF_DEC(u, vrf_id, vrf, ipv6);
    }
    soc_th_alpm_128_lpm_state_dump(u);
    SOC_ALPM_LPM_UNLOCK(u);
    return(rv);
}

/*
 * soc_th_alpm_128_lpm_match (Exact match for the key. Will match both IP
 *                   address and mask)
 */
static int
soc_th_alpm_128_lpm_match(int u,
               void *key_data,
               void *e,         /* return entry data if found */
               int *index_ptr)  /* return key location */
{
    int        pfx;
    int        rv;
    int        ipv6;

    SOC_ALPM_LPM_LOCK(u);
    rv = _soc_th_alpm_128_lpm_match(u, key_data, e, index_ptr, &pfx, &ipv6, 0, 0);
    SOC_ALPM_LPM_UNLOCK(u);
    return(rv);
}

/* Fill Aux entry for operation */
static int
_soc_th_alpm_128_fill_aux_entry_for_op(int u,
               void *key_data,
               int ipv6,    /* Entry is ipv6. */
               int db_type, /* database type */
               int ent_type,
               int replace_len, /* used for DElete propagate */
               defip_aux_scratch_entry_t *aux_entry)
{
    uint32 ipv4a;
    uint32 ip6_word[4] = {0, 0, 0, 0};
    int    pfx = 0;
    int    rv = SOC_E_NONE;

    /* pick one of 4 valid bits */
    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                    VALID0_LWRf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, VALIDf, ipv4a);

    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data, MODE0_LWR_f(u));
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, MODE_f(u), ipv4a);

    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                                ENTRY_TYPE0_LWR_f(u));
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, ENTRY_TYPE_f(u), ent_type);

    if (SOC_IS_TRIDENT3X(u)) {
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data, DATA_TYPEf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, DATA_TYPEf, ipv4a);
    }

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                GLOBAL_ROUTEf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                        GLOBAL_ROUTEf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                    DEFAULT_MISSf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                        DEFAULT_MISSf, ipv4a);

    if (soc_feature(u, soc_feature_ipmc_defip)) {
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                EXPECTED_L3_IIFf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                EXPECTED_L3_IIFf, ipv4a);
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                RPA_IDf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                RPA_IDf, ipv4a);
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                IPMC_EXPECTED_L3_IIF_MISMATCH_TOCPUf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                IPMC_EXPECTED_L3_IIF_MISMATCH_TOCPUf, ipv4a);
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                IPMC_EXPECTED_L3_IIF_MISMATCH_DROPf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                IPMC_EXPECTED_L3_IIF_MISMATCH_DROPf, ipv4a);
        if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, L3MC_INDEXf)) {
            ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                    L3MC_INDEXf);
            soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                    L3MC_INDEXf, ipv4a);
        }
    }

    if (soc_feature(u, soc_feature_generic_dest)) {
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, key_data,
                                    DESTINATIONf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                            DESTINATIONf, ipv4a);
    } else {
        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, ECMPf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, ECMPf, ipv4a);

        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, ECMP_PTRf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, ECMP_PTRf, ipv4a);

        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                    NEXT_HOP_INDEXf);
        soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry,
                            NEXT_HOP_INDEXf, ipv4a);
    }

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, PRIf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, PRIf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, RPEf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, RPEf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                               VRF_ID_0_LWRf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, VRFf, ipv4a);

    /* Set Database type */
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, DB_TYPEf,
                        db_type);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                DST_DISCARDf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, DST_DISCARDf,
                        ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, CLASS_IDf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, CLASS_IDf,
                        ipv4a);


    /* Set IP Address and IP length */
    ip6_word[0] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                      IP_ADDR0_LWRf);
    ip6_word[1] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                      IP_ADDR1_LWRf);
    ip6_word[2] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                      IP_ADDR0_UPRf);
    ip6_word[3] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data,
                                      IP_ADDR1_UPRf);
    soc_mem_field_set(u, L3_DEFIP_AUX_SCRATCHm, (uint32*)aux_entry,
                      IP_ADDRf, (uint32*)ip6_word);

    rv = _soc_th_alpm_128_ip6_mask_len_get(u, key_data, &pfx);
    if (SOC_FAILURE(rv)) {
        return rv;
    }
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, IP_LENGTHf,pfx);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, REPLACE_LENf,
                        replace_len);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, FLEX_CTR_BASE_COUNTER_IDXf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, FLEX_CTR_BASE_COUNTER_IDXf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, FLEX_CTR_OFFSET_MODEf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, FLEX_CTR_OFFSET_MODEf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, key_data, FLEX_CTR_POOL_NUMBERf);
    soc_mem_field32_set(u, L3_DEFIP_AUX_SCRATCHm, aux_entry, FLEX_CTR_POOL_NUMBERf, ipv4a);

    return (SOC_E_NONE);
}


/* Initialize the ALPM memory from a TCAM entry */
static int
_soc_th_alpm_128_mem_ent_init(int u, void *lpm_entry,
                       void *alpm_entry, void *alpm_sip_entry, soc_mem_t mem,
                       uint32 src_flags, uint32 *is_default, int bucket_id)
{
    uint32 ipv4a;
    uint32 ip6_word[4];
    int    pfx = 0;
    int    rv = SOC_E_NONE;
    uint32 default_route = 0;

    /* Zero Buffer */
    sal_memset(alpm_entry, 0, soc_mem_entry_words(u, mem) * 4);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, HITf);
    soc_mem_field32_set(u, mem, alpm_entry, HITf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                    VALID0_LWRf);
    soc_mem_field32_set(u, mem, alpm_entry, VALIDf, ipv4a);

    if (soc_feature(u, soc_feature_generic_dest)) {
        ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                    DESTINATIONf);
        soc_mem_field32_set(u, mem, alpm_entry, DESTINATIONf, ipv4a);
    } else {
        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ECMPf);
        soc_mem_field32_set(u, mem, alpm_entry, ECMPf, ipv4a);

        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ECMP_PTRf);
        soc_mem_field32_set(u, mem, alpm_entry, ECMP_PTRf, ipv4a);

        ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                        NEXT_HOP_INDEXf);
        soc_mem_field32_set(u, mem, alpm_entry, NEXT_HOP_INDEXf, ipv4a);
    }

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, PRIf);
    soc_mem_field32_set(u, mem, alpm_entry, PRIf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, RPEf);
    soc_mem_field32_set(u, mem, alpm_entry, RPEf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                    DST_DISCARDf);
    soc_mem_field32_set(u, mem, alpm_entry, DST_DISCARDf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                    SRC_DISCARDf);
    soc_mem_field32_set(u, mem, alpm_entry, SRC_DISCARDf, ipv4a);

    ipv4a = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, CLASS_IDf);
    soc_mem_field32_set(u, mem, alpm_entry, CLASS_IDf, ipv4a);

    if (ALPM_CTRL(u).bkt_sharing) {
        soc_mem_field32_set(u, mem, alpm_entry, SUB_BKT_PTRf,
                            ALPM_SUB_BKT(u, bucket_id));
    }

    /* Set IP Address and IP length */
    ip6_word[0] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                          IP_ADDR0_LWRf);
    ip6_word[1] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                          IP_ADDR1_LWRf);
    ip6_word[2] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                          IP_ADDR0_UPRf);
    ip6_word[3] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                          IP_ADDR1_UPRf);
    soc_mem_field_set(u, mem, (uint32*)alpm_entry, KEYf, (uint32*)ip6_word);

    rv = _soc_th_alpm_128_ip6_mask_len_get(u, lpm_entry, &pfx);
    if (SOC_FAILURE(rv)) {
        return rv;
    }

    if ((pfx == 0) && (ip6_word[0] == 0) && (ip6_word[1] == 0) &&
        (ip6_word[2] == 0) && (ip6_word[3] == 0)) {
        default_route = 1;
    }
    if (is_default != NULL) {
        *is_default = default_route;
    }
    soc_mem_field32_set(u, mem, alpm_entry, LENGTHf, pfx);

    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_BASE_COUNTER_IDXf);
    soc_mem_field32_set(u, mem, alpm_entry, FLEX_CTR_BASE_COUNTER_IDXf, ipv4a);

    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_OFFSET_MODEf);
    soc_mem_field32_set(u, mem, alpm_entry, FLEX_CTR_OFFSET_MODEf, ipv4a);

    ipv4a = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_POOL_NUMBERf);
    soc_mem_field32_set(u, mem, alpm_entry, FLEX_CTR_POOL_NUMBERf, ipv4a);

    if (alpm_sip_entry == NULL) {
        return (SOC_E_NONE);
    }
    if (SOC_URPF_STATUS_GET(u)) {
        sal_memset(alpm_sip_entry, 0, soc_mem_entry_words(u, mem) * 4);
        sal_memcpy(alpm_sip_entry, alpm_entry, soc_mem_entry_words(u, mem) * 4);
        soc_mem_field32_set(u, mem, alpm_sip_entry, DST_DISCARDf, 0);
        soc_mem_field32_set(u, mem, alpm_sip_entry, RPEf, 0);

        soc_mem_field32_set(u, mem, alpm_sip_entry, SRC_DISCARDf,
                            src_flags & SOC_ALPM_RPF_SRC_DISCARD);
        soc_mem_field32_set(u, mem, alpm_sip_entry, DEFAULTROUTEf,
                            default_route);
#if defined(BCM_TRIDENT3_SUPPORT)
        if (SOC_IS_TRIDENT3X(u)) {
            if (SOC_MEM_FIELD_VALID(u, mem, FLEX_CTR_BASE_COUNTER_IDXf)) {
                soc_mem_field32_set(u, mem, alpm_sip_entry,
                    FLEX_CTR_BASE_COUNTER_IDXf, 0);
            }
            if (SOC_MEM_FIELD_VALID(u, mem, FLEX_CTR_BASE_COUNTER_IDX0f)) {
                soc_mem_field32_set(u, mem, alpm_sip_entry,
                    FLEX_CTR_BASE_COUNTER_IDX0f, 0);
            }
            if (SOC_MEM_FIELD_VALID(u, mem, FLEX_CTR_BASE_COUNTER_IDX1f)) {
                soc_mem_field32_set(u, mem, alpm_sip_entry,
                    FLEX_CTR_BASE_COUNTER_IDX1f, 0);
            }
        }
#endif
    }
    return (SOC_E_NONE);
}

/* Initialize the TCAM entry from ALPM memory */
static int
_soc_th_alpm_128_lpm_ent_init(int u, void *alpm_entry, soc_mem_t mem, int ipv6,
                              int vrf_id, int bucket, int index, void *lpm_entry,
                              int flex)
{
    uint32 ipv4a;
    uint32 ip6_word[4];
    uint32 mvrf, mvrf_mask;

    /* Zero Buffer */
    sal_memset(lpm_entry, 0, soc_mem_entry_words(u, L3_DEFIP_PAIR_128m) * 4);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, HITf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, HITf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, VALIDf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VALID0_LWRf, ipv4a);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VALID1_LWRf, ipv4a);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VALID0_UPRf, ipv4a);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VALID1_UPRf, ipv4a);

    if (soc_feature(u, soc_feature_generic_dest)) {
        ipv4a = soc_mem_field32_get(u, mem, alpm_entry, DESTINATIONf);
        soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            DESTINATIONf, ipv4a);
    } else {
        ipv4a = soc_mem_field32_get(u, mem, alpm_entry, ECMPf);
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ECMPf, ipv4a);

        ipv4a = soc_mem_field32_get(u, mem, alpm_entry, ECMP_PTRf);
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ECMP_PTRf, ipv4a);

        ipv4a = soc_mem_field32_get(u, mem, alpm_entry, NEXT_HOP_INDEXf);
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                NEXT_HOP_INDEXf, ipv4a);
    }

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, PRIf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, PRIf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, RPEf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, RPEf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, DST_DISCARDf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, DST_DISCARDf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, SRC_DISCARDf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, SRC_DISCARDf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, CLASS_IDf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, CLASS_IDf, ipv4a);

    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_BKT_PTRf,
                            ALPM_PHY_BKT(u, bucket));
    if (ALPM_CTRL(u).bkt_sharing) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_SUB_BKT_PTRf,
                                ALPM_SUB_BKT(u, bucket));
    }
    if (index > 0) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_HIT_IDXf,
                                index);
    }

    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        MODE_MASK0_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        MODE_MASK1_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        MODE_MASK0_UPR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        MODE_MASK1_UPR_f(u), 3);

    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK0_LWR_f(u), 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK1_LWR_f(u), 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK0_UPR_f(u), 1);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry,
                        ENTRY_TYPE_MASK1_UPR_f(u), 1);

    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE0_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE1_LWR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE0_UPR_f(u), 3);
    soc_mem_field32_set(u, L3_DEFIP_PAIR_128m, lpm_entry, MODE1_UPR_f(u), 3);

    /* Set IP Address and IP length */
    soc_mem_field_get(u, mem, alpm_entry, KEYf, ip6_word);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR0_LWRf,
                            ip6_word[0]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR1_LWRf,
                            ip6_word[1]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR0_UPRf,
                            ip6_word[2]);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR1_UPRf,
                            ip6_word[3]);

    ip6_word[0] = ip6_word[1] = ip6_word[2] = ip6_word[3] = 0;

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, LENGTHf);
    _soc_th_alpm_128_pfx_len_to_mask(u, lpm_entry, ipv4a);

    if (vrf_id == SOC_L3_VRF_OVERRIDE) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                GLOBAL_HIGHf, 1);
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                GLOBAL_ROUTEf, 1);
        mvrf = 0;
        mvrf_mask = 0;
    } else  if (vrf_id == SOC_L3_VRF_GLOBAL) {
        SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                GLOBAL_ROUTEf, 1);
        mvrf = 0;
        mvrf_mask = 0;
    } else {
        mvrf = vrf_id;
        mvrf_mask = SOC_VRF_MAX(u);
    }
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ENTRY_VIEWf,
        _soc_th_alpm_lpm_entry_view_get(u, ipv6, flex));

    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_0_LWRf, mvrf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_1_LWRf, mvrf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_0_UPRf, mvrf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_1_UPRf, mvrf);

    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK0_LWRf, mvrf_mask);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK1_LWRf, mvrf_mask);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK0_UPRf, mvrf_mask);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry,
                            VRF_ID_MASK1_UPRf, mvrf_mask);


    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, FLEX_CTR_BASE_COUNTER_IDXf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_BASE_COUNTER_IDXf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, FLEX_CTR_OFFSET_MODEf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_OFFSET_MODEf, ipv4a);

    ipv4a = soc_mem_field32_get(u, mem, alpm_entry, FLEX_CTR_POOL_NUMBERf);
    SOC_MEM_OPT_F32_SET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, FLEX_CTR_POOL_NUMBERf, ipv4a);

    return (SOC_E_NONE);
}

STATIC int
_soc_th_alpm_128_pivot_bmp_len_get(int unit, void *lpm_entry, uint32 *bpm_len)
{
    int         rv = SOC_E_NONE;
    int         vrf_id = 0, vrf = 0;
    uint32      length = 0;
    uint32      prefix[5] = {0};
    int         default_route = 0;
    trie_t      *pfx_root = NULL;
    trie_node_t *lpmp = NULL;
    payload_t   *tmp_pyld = NULL;

    *bpm_len = 0;

    SOC_IF_ERROR_RETURN(
        soc_th_alpm_128_lpm_vrf_get(unit, lpm_entry, &vrf_id, &vrf));

    if ((ALPM_PREFIX_IN_TCAM(unit, vrf_id))) {
        return rv;
    }

    SOC_IF_ERROR_RETURN(
        _soc_th_alpm_128_prefix_create(unit, lpm_entry, prefix, &length,
                                       &default_route));

    pfx_root = VRF_PREFIX_TRIE_IPV6_128(unit, vrf);

    /* find longest prefix that covers pivot */
    rv = trie_find_lpm(pfx_root, prefix, length, &lpmp);
    if (SOC_FAILURE(rv)) {
        return rv;
    }

    tmp_pyld = (payload_t *)lpmp;

    if (tmp_pyld->bkt_ptr) {
        *bpm_len = ((payload_t *)(tmp_pyld->bkt_ptr))->len;
    }

    return rv;

}

int
soc_th_alpm_128_warmboot_pivot_bmp_len_update(int unit, int ipv6,
                                          void *lpm_entry, int tcam_idx)
{
    int          rv = SOC_E_NONE;
    alpm_pivot_t *pivot = NULL;
    uint32       bpm_len = 0;

    SOC_IF_ERROR_RETURN(
        _soc_th_alpm_128_pivot_bmp_len_get(unit, lpm_entry, &bpm_len));

    tcam_idx = soc_th_alpm_physical_idx(unit, L3_DEFIP_PAIR_128m, tcam_idx, ipv6);

    pivot = ALPM_TCAM_PIVOT(unit, SOC_ALPM_128_ADDR_LWR(unit, tcam_idx) << 1);

    /* update bpm_len */
    PIVOT_TCAM_BPMLEN(pivot) = bpm_len;

    return rv;
}

int
soc_th_alpm_128_warmboot_pivot_add(int unit, int ipv6, void *lpm_entry,
                                   int tcam_idx, int log_bkt)
{
    int                  rv = SOC_E_NONE;
    uint32               key[4] = {0, 0, 0, 0};
    alpm_pivot_t         *pivot = NULL;
    alpm_bucket_handle_t *bucket_handle = NULL;
    int                  vrf_id = 0, vrf = 0;
    uint32               length2;
    trie_t               *pivot_root = NULL;
    uint32               prefix[5] = {0};
    uint32               bpm[5] = {0};
    int                  default_route = 0;

    rv = _soc_th_alpm_128_prefix_create(unit, lpm_entry, prefix, &length2,
                                        &default_route);
    SOC_IF_ERROR_RETURN(rv);

    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(unit, lpm_entry, &vrf_id, &vrf));
    tcam_idx = soc_th_alpm_physical_idx(unit, L3_DEFIP_PAIR_128m, tcam_idx, ipv6);

    /* Allocate bucket handle */
    bucket_handle = sal_alloc(sizeof(alpm_bucket_handle_t), "ALPM Bucket Handle");
    if (bucket_handle == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "Unable to allocate memory for PIVOT trie node \n")));
        return SOC_E_NONE;
    }
    sal_memset(bucket_handle, 0, sizeof(*bucket_handle));

    /* Allocate pivot Payload */
    pivot = sal_alloc(sizeof(alpm_pivot_t), "Payload for Pivot");
    if (pivot == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "Unable to allocate memory for PIVOT trie node \n")));
        sal_free(bucket_handle);
        return SOC_E_MEMORY;
    }
    sal_memset(pivot, 0, sizeof(*pivot));

    /* Save bucket_handle in pivot->bucket_trie */
    PIVOT_BUCKET_HANDLE(pivot) = bucket_handle;

    trie_init(_MAX_KEY_LEN_144_, &PIVOT_BUCKET_TRIE(pivot));

    /* Set address to the buffer. */
    key[0] = SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR0_LWRf);
    key[1] = SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR1_LWRf);
    key[2] = SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR0_UPRf);
    key[3] = SOC_MEM_OPT_F32_GET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, IP_ADDR1_UPRf);

    /* Save bucket index into pivot->bucket->bucket_index */
    PIVOT_BUCKET_INDEX(pivot) = log_bkt;

    /* Save tcam index into pivot->tcam_index */
    PIVOT_TCAM_INDEX(pivot) = SOC_ALPM_128_ADDR_LWR(unit, tcam_idx) << 1;

    if (!(ALPM_PREFIX_IN_TCAM(unit, vrf_id))) {
        pivot_root = VRF_PIVOT_TRIE_IPV6_128(unit, vrf);
        if (pivot_root == NULL) {
            trie_init(_MAX_KEY_LEN_144_, &VRF_PIVOT_TRIE_IPV6_128(unit, vrf));
            pivot_root = VRF_PIVOT_TRIE_IPV6_128(unit, vrf);
        }

        sal_memcpy(pivot->key, prefix, sizeof(prefix));
        pivot->len    = length2;

        rv = trie_insert(pivot_root, pivot->key,
                         ALPM_CTRL(unit).trie_propagate ? bpm : NULL,
                         pivot->len, (trie_node_t *)pivot);
        if (SOC_FAILURE(rv)) {
            sal_free(bucket_handle);
            sal_free(pivot);
            return rv;
        }
    }

    /* Insert pivot into global pivot array indexed by tcam_idx */
    ALPM_TCAM_PIVOT(unit, SOC_ALPM_128_ADDR_LWR(unit, tcam_idx) << 1) = pivot;

    PIVOT_BUCKET_VRF(pivot) = vrf;
    PIVOT_BUCKET_IPV6(pivot) = ipv6;
    PIVOT_BUCKET_ENT_CNT_UPDATE(pivot);
    if (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0) {
        PIVOT_BUCKET_DEF(pivot) = TRUE;
    }

    return rv;
}

static int
_soc_th_alpm_128_warmboot_insert(int unit,
                                 int ipv6,
                                 void *lpm_entry,
                                 void *alpm_entry, /* ALPM (SRAM) entry data */
                                 soc_mem_t mem,    /* Mem view for ALPM data */
                                 int tcam_idx,     /* TCAM index             */
                                 int log_bkt,        /* Bucket index           */
                                 int alpm_idx )    /* ALPM entry index       */
{
    int          vrf_id;   /* Internal API representation of VRF id           */
    int          vrf;      /* VRF in 0 to (MAX_VRF + 1) range;                */
                           /* VRF = (MAX_VRF + 1), software rep of GLOBAL VRF */
    int          rv = SOC_E_NONE;
    int          default_route = 0;
    uint32       prefix[5] = {0, 0, 0, 0, 0};
    uint32       length;
    defip_pair_128_entry_t temp_lpm_entry;
    trie_t       *bkt_trie = NULL;
    trie_t       *pfx_trie = NULL;
    trie_node_t  *delp = NULL;
    payload_t    *bkt_payload = NULL;
    payload_t    *pfx_payload = NULL;
    alpm_pivot_t *pivot_pyld = NULL;
    trie_node_t  *lpmp = NULL;
    payload_t    *tmp_pyld = NULL;

    /* Check function params */
    if ((NULL == lpm_entry) || (NULL == alpm_entry)) {
        return SOC_E_PARAM;
    }

    /* Get VRF */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(unit, lpm_entry, &vrf_id,
                                                    &vrf));

    /* Get ALPM table memory. */
    SOC_ALPM_TABLE_MEM_128(unit, ipv6, mem);

    /* Convert alpm_entry into lpm_entry to extract prefix */
    SOC_IF_ERROR_RETURN(_soc_th_alpm_128_lpm_ent_init(unit, alpm_entry, mem, ipv6,
                                                      vrf_id, log_bkt, tcam_idx,
                                                      &temp_lpm_entry, 0));

    /* Create Prefix */
    rv = _soc_th_alpm_128_prefix_create(unit, &temp_lpm_entry, prefix, &length,
                                        &default_route);
    if (SOC_FAILURE(rv)) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "prefix create failed\n")));
        return rv;
    }

    /* Get TCAM pivot */
    pivot_pyld = ALPM_TCAM_PIVOT(unit, tcam_idx);

    /* Get bucket trie from pivot */
    bkt_trie = PIVOT_BUCKET_TRIE(pivot_pyld);

    /* Allocate bucket payload */
    bkt_payload = sal_alloc(sizeof(payload_t), "Payload for Key");
    if (NULL == bkt_payload) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "Unable to allocate memory for trie node.\n")));
        return SOC_E_MEMORY;
    }

    /* Allocate prefix trie payload */
    pfx_payload = sal_alloc(sizeof(payload_t), "Payload for pfx trie key");
    if (NULL == pfx_payload) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "Unable to allocate memory for pfx trie node\n")));
        sal_free(bkt_payload);
        return SOC_E_MEMORY;
    }

    /* Clear allocated payloads */
    sal_memset(bkt_payload, 0, sizeof(*bkt_payload));
    sal_memset(pfx_payload, 0, sizeof(*pfx_payload));
    sal_memcpy(bkt_payload->key, prefix, sizeof(bkt_payload->key));
    bkt_payload->len    = length;
    bkt_payload->index  = alpm_idx;

    /* Create duplicate for prefix trie */
    sal_memcpy(pfx_payload, bkt_payload, sizeof(*bkt_payload));
    pfx_payload->bkt_ptr = bkt_payload;

    /* Insert prefix into bucket-trie */
    rv = trie_insert(bkt_trie, prefix, NULL, length,
                    (trie_node_t *)bkt_payload);
    if (SOC_FAILURE(rv)) {
        goto free_memory;
    }

    /* Insert prefix into prefix-trie */
    if (ipv6) {
        pfx_trie = VRF_PREFIX_TRIE_IPV6_128(unit, vrf);
    }

    if (!default_route) {
        uint32 bpm[5];
        /* Default route already in prefix trie */
        _soc_th_alpm_mask_prefix_create(unit, ipv6, length, bpm);
        rv = trie_insert(pfx_trie, prefix,
                         ALPM_CTRL(unit).trie_propagate ? bpm : NULL, length,
                         (trie_node_t *)pfx_payload);
        if (SOC_FAILURE(rv)) {
            goto delete_bkt_trie;
        }
    } else {
        /* update the default route */
        lpmp = NULL;
        rv = trie_find_lpm(pfx_trie, 0, 0, &lpmp);
        tmp_pyld = (payload_t *)lpmp;
        if (SOC_SUCCESS(rv)) {
            tmp_pyld->bkt_ptr = bkt_payload;
        } else {
            goto delete_bkt_trie;
        }
    }

    /* Return success */
    return rv;

delete_bkt_trie:
    (void) trie_delete(bkt_trie, prefix, length, &delp);
    bkt_payload = (payload_t *) delp;

free_memory:
    sal_free(bkt_payload);
    sal_free(pfx_payload);
    return rv;
}

/*
 * soc_th_alpm_warmboot_vrf_add
 */
static int
soc_th_alpm_128_warmboot_vrf_add(int unit, int v6, int vrf, int idx, int log_bkt)
{
    int           rv = SOC_E_NONE;
    uint32        length;
    uint32        key[5] = {0, 0, 0, 0, 0};
    trie_t        *pfx_root = NULL;
    payload_t     *pfx_pyld = NULL;
    defip_pair_128_entry_t *lpm_entry = NULL;

    /* Initialize VRF PIVOT IPV4 trie */
    lpm_entry = sal_alloc(sizeof(defip_pair_128_entry_t), "Default LPM entry");
    if (lpm_entry == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                  "unable to allocate memory for LPM entry\n")));
        return SOC_E_MEMORY;
    }

    /* Initialize an lpm entry to perform a match */
    _soc_th_alpm_128_lpm_ent_key_init(unit, key, 0, vrf, v6, lpm_entry, 1);

    /* for global VRF */
    if (vrf == SOC_VRF_MAX(unit) + 1) {
        SOC_MEM_OPT_F32_SET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, GLOBAL_ROUTEf, 1);
    } else {
        /* Set default miss to global route only for non global routes */
        SOC_MEM_OPT_F32_SET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, DEFAULT_MISSf, 1);
    }

    SOC_MEM_OPT_F32_SET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, ALG_BKT_PTRf,
                                       ALPM_PHY_BKT(unit, log_bkt));
    if (ALPM_CTRL(unit).bkt_sharing) {
        SOC_MEM_OPT_F32_SET_128(unit, L3_DEFIP_PAIR_128m, lpm_entry, ALG_SUB_BKT_PTRf,
                                ALPM_SUB_BKT(unit, log_bkt));
    }

    VRF_TRIE_DEFAULT_ROUTE_IPV6_128(unit, vrf) = lpm_entry;
    trie_init(_MAX_KEY_LEN_144_, &VRF_PREFIX_TRIE_IPV6_128(unit, vrf));
    pfx_root = VRF_PREFIX_TRIE_IPV6_128(unit, vrf);

    pfx_pyld = sal_alloc(sizeof(payload_t), "Payload for pfx trie key");
    if (pfx_pyld == NULL) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                 "Unable to allocate memory for pfx trie node \n")));
        return SOC_E_MEMORY;
    }

    sal_memset(pfx_pyld, 0, sizeof(*pfx_pyld));
    pfx_pyld->key[0] = key[0];
    pfx_pyld->key[1] = key[1];
    pfx_pyld->len    = length = 0;

    rv = trie_insert(pfx_root, key, ALPM_CTRL(unit).trie_propagate ? key : NULL,
                     length, &(pfx_pyld->node));
    if (SOC_FAILURE(rv)) {
        sal_free(pfx_pyld);
        return rv;
    }

    VRF_TRIE_INIT_DONE(unit, vrf, v6, 1);

    return rv;
}

/*
 * soc_th_alpm_128_warmboot_prefix_insert
 */
int
soc_th_alpm_128_warmboot_prefix_insert(int unit,
                                int  ipv6,
                                void *lpm_entry,
                                void *alpm_entry,
                                int tcam_idx,
                                int log_bkt,
                                int alpm_idx)
{
    int       vrf_id;   /* API representation of VRF id */
    int       vrf;      /* VRF in (0 - (MAX_VRF + 1)) range */
    int       rv = SOC_E_NONE;
    soc_mem_t mem;

    tcam_idx = soc_th_alpm_physical_idx(unit, L3_DEFIP_PAIR_128m, tcam_idx, ipv6);
    tcam_idx = SOC_ALPM_128_ADDR_LWR(unit, tcam_idx) << 1;

    /* Get ALPM table memory. */
    SOC_ALPM_TABLE_MEM_128(unit, ipv6, mem);

    /* Get VRF */
    SOC_IF_ERROR_RETURN(soc_th_alpm_128_lpm_vrf_get(unit, lpm_entry, &vrf_id, &vrf));

    /* For VRF_OVERRIDE (Global High) entries,  Prefix resides in TCAM directly */
    if (ALPM_PREFIX_IN_TCAM(unit, vrf_id)) {
        return(rv);
    }

    /* Non override entries, goes into ALPM memory */
    if (!VRF_TRIE_INIT_COMPLETED(unit, vrf, ipv6)) {
        LOG_VERBOSE(BSL_LS_SOC_ALPM,
                    (BSL_META_U(unit,
                                "VRF %d is not initialized\n"), vrf));
        rv = soc_th_alpm_128_warmboot_vrf_add(unit, ipv6, vrf, tcam_idx, log_bkt);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                     (BSL_META_U(unit,
                                 "VRF %d/%d trie init \n"
                                 "failed\n"), vrf, ipv6));
            return rv;
        }

    }

    rv = _soc_th_alpm_128_warmboot_insert(unit, ipv6, lpm_entry, alpm_entry, mem,
                                          tcam_idx, log_bkt, alpm_idx);
    if (rv != SOC_E_NONE) {
        LOG_WARN(BSL_LS_SOC_ALPM,
                 (BSL_META_U(unit,
                             "unit %d : "
                             "Route Insertion Failed :%s\n"),
                              unit, soc_errmsg(rv)));

        return(rv);
    }

    soc_th_alpm_bucket_usage_incr(unit, log_bkt, tcam_idx, vrf, mem, 1);
    VRF_TRIE_ROUTES_INC(unit, vrf_id, vrf, ipv6);
    return(rv);
}

/*
 * alpm_warmboot_bucket_bitmap_set
 * This function will set bit position in bucket bitmap
 */
int
soc_th_alpm_128_warmboot_bucket_bitmap_set(int u,       /* Unit         */
                                           int vrf,     /* VRF          */
                                           int v6,      /* Flag v4/v6   */
                                           int bkt_idx) /* Bucket index */
{
    int step_count = 1;
    uint8 ipv = !!v6;
    SHR_BITDCL *bkt_bmap = SOC_TH_ALPM_VRF_BUCKET_BMAP(u, ipv);

    if (vrf == SOC_VRF_MAX(u) + 1) {
        bkt_bmap = SOC_TH_ALPM_GLB_BUCKET_BMAP(u, ipv);
    }
    /*
     * In combined search mode, with urpf disabled, need to allocate even and
     * odd bucket pointers
     */
    if (ALPM_CTRL(u).double_wide[v6]) {
        step_count = 2;
    }

    /* Set bit position */
    SHR_BITSET_RANGE(bkt_bmap, bkt_idx, step_count);

    return SOC_E_NONE;
}

int
soc_th_alpm_128_warmboot_lpm_reinit_done(int unit)
{
    int idx;
    int prev_idx = MAX_PFX_INDEX_128;

    int defip_table_size = soc_mem_index_count(unit, L3_DEFIP_PAIR_128m);

    if (SOC_URPF_STATUS_GET(unit)) {
        defip_table_size >>= 1;
    }

    /* returns 0 for combined search mode and 1 for parallel search mode */
    if (ALPM_CTRL(unit).alpm_mode == SOC_ALPM_MODE_COMBINED) {
        /* Combined search mode */
        SOC_ALPM_128_LPM_STATE_PREV(unit, MAX_PFX_INDEX_128) = -1;

        for (idx = MAX_PFX_INDEX_128; idx > -1; idx--) {
            if (-1 == SOC_ALPM_128_LPM_STATE_START(unit, idx)) {
                continue;
            }

            SOC_ALPM_128_LPM_STATE_PREV(unit, idx) = prev_idx;
            SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = idx;

            SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                    \
                              SOC_ALPM_128_LPM_STATE_START(unit, idx) -      \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;
            prev_idx = idx;

        }

        SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = -1;
        SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                       \
                              defip_table_size -                   \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;
    } else {
        /* Parallel search mode
         *
         *    Configured VRF Range
         *    {0 - (MAX_PFX_INDEX_128/3)}
         *    Global VRF Range
         *    {((MAX_PFX_INDEX_128/1) + 1) - (MAX_PFX_INDEX_128/2) }
         *    Override VRF Range
         *    {((MAX_PFX_INDEX_128/2) + 1) - (MAX_PFX_INDEX_128) }
         */

        /*
         * Global and Overide VRF range are treated as single block and
         * both blocks will be linked
         */

        SOC_ALPM_128_LPM_STATE_PREV(unit, MAX_PFX_INDEX_128) = -1;
        for (idx = MAX_PFX_INDEX_128; idx > (MAX_PFX_INDEX_128/3) ; idx--) {
            if (-1 == SOC_ALPM_128_LPM_STATE_START(unit, idx)) {
                continue;
            }

            SOC_ALPM_128_LPM_STATE_PREV(unit, idx) = prev_idx;
            SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = idx;

            SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                    \
                              SOC_ALPM_128_LPM_STATE_START(unit, idx) -      \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;

            prev_idx = idx;
        }
        SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = -1;
        SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                       \
                              defip_table_size -                        \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;

        /* Configured VRF range */
        prev_idx = (MAX_PFX_INDEX_128/3);
        SOC_ALPM_128_LPM_STATE_PREV(unit, (MAX_PFX_INDEX_128/3)) = -1;
        for (idx = ((MAX_PFX_INDEX_128/3)-1); idx > -1; idx--) {
            if (-1 == SOC_ALPM_128_LPM_STATE_START(unit, idx)) {
                continue;
            }

            SOC_ALPM_128_LPM_STATE_PREV(unit, idx) = prev_idx;
            SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = idx;

            SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                    \
                              SOC_ALPM_128_LPM_STATE_START(unit, idx) -      \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;
            prev_idx = idx;
        }
        SOC_ALPM_128_LPM_STATE_NEXT(unit, prev_idx) = -1;
        SOC_ALPM_128_LPM_STATE_FENT(unit, prev_idx) =                         \
                              (defip_table_size >> 1) -                   \
                              SOC_ALPM_128_LPM_STATE_END(unit, prev_idx) - 1;
    }

    return (SOC_E_NONE);
}

int
soc_th_alpm_128_warmboot_lpm_reinit(int unit,
                             int ipv6,
                             int idx,
                             void *lpm_entry)
{
    int pfx_len;
    int flex;
    int vrf, vrf_id;

    LPM_128_HASH_INSERT(unit, lpm_entry, idx, NULL);

    SOC_IF_ERROR_RETURN
        (_soc_th_alpm_128_lpm_prefix_length_get(unit, lpm_entry, &pfx_len, &vrf_id, &vrf));

    if (!VRF_FLEX_COMPLETED(unit, vrf_id, vrf, ipv6)) {
        flex = _soc_th_alpm_lpm_flex_get(unit, ipv6,
                    soc_mem_field32_get(unit, L3_DEFIP_PAIR_128m,
                    lpm_entry, ENTRY_VIEWf));
        VRF_FLEX_SET(unit, vrf_id, vrf, ipv6, flex);
    }

    VRF_PIVOT_REF_INC(unit, vrf_id, vrf, ipv6);

    if (SOC_ALPM_128_LPM_STATE_VENT(unit, pfx_len) == 0) {
        SOC_ALPM_128_LPM_STATE_START(unit, pfx_len) = idx;
        SOC_ALPM_128_LPM_STATE_END(unit, pfx_len) = idx;
    } else {
        SOC_ALPM_128_LPM_STATE_END(unit, pfx_len) = idx;
    }

    SOC_ALPM_128_LPM_STATE_VENT(unit, pfx_len)++;

    return (SOC_E_NONE);
}

#ifdef ALPM_WARM_BOOT_DEBUG

/*
 * Function:
 *     soc_th_alpm_128_warmboot_lpm_sw_dump
 * Purpose:
 *     Displays FB LPM information maintained by software.
 * Parameters:
 *     unit - Device unit number
 * Returns:
 *     None
 */
void
soc_th_alpm_128_warmboot_lpm_sw_dump(int unit)
{
    int i;
    _soc_th_alpm_128_lpm_hash_t *hash128;
    soc_th_alpm_128_lpm_state_p lpm_state_128;

    /* Dump v6-128 lpm state */
    bsl_verbose(BSL_SOC_ALPM, unit,
                        "V6-128 LPM STATE DUMP.\n");
    lpm_state_128 = soc_th_alpm_128_lpm_state[unit];

    if (lpm_state_128 != NULL) {
        for (i = 0; i < MAX_PFX_ENTRIES_128; i++) {
            if (lpm_state_128[i].vent != 0 ) {
                LOG_CLI((BSL_META_U(unit,
                                    "Prefix %d\n"), i));
                LOG_CLI((BSL_META_U(unit,
                                    "  Start : %d\n"), lpm_state_128[i].start));
                LOG_CLI((BSL_META_U(unit,
                                    "  End   : %d\n"), lpm_state_128[i].end));
                LOG_CLI((BSL_META_U(unit,
                                    "  Prev  : %d\n"), lpm_state_128[i].prev));
                LOG_CLI((BSL_META_U(unit,
                                    "  Next  : %d\n"), lpm_state_128[i].next));
                LOG_CLI((BSL_META_U(unit,
                                    "  Valid : %d\n"), lpm_state_128[i].vent));
                LOG_CLI((BSL_META_U(unit,
                                    "  Free  : %d\n"), lpm_state_128[i].fent));
            }
        }
    }
    LOG_CLI((BSL_META_U(unit,
                        "V6-128 LPM STATE DUMP DONE.\n\n")));

    /* Dump LPM HASH 128 table */
    LOG_CLI((BSL_META_U(unit,
                        "LPM HASH 128 TABLE DUMP.\n")));
    hash128 = _fb_lpm_128_hash_tab[unit];
    for(i = 0; i < hash128->index_count; i++) {
        if (hash128->table[i] != FB_LPM_128_HASH_INDEX_NULL) {
            LOG_CLI((BSL_META_U(unit,
                                "hash_indx_128 = 0x%x Data = 0x%x\n"),
                     i,  hash128->table[i]));
        }
    }
    LOG_CLI((BSL_META_U(unit,
                        "LPM HASH 128 TABLE DUMP DONE.\n\n")));

    return;
}
#endif




/*
 * Function:
 *      _soc_th_alpm_128_sanity_check
 * Purpose:
 *      Sanity check for ALPM with L3_DEFIP
 * Parameters:
 *      u           - Device unit
 *      min         - Min index of L3_DEFIP
 *      max         - Max index of L3_DEFIP
 *      check_sw    - Check software
 *      bkt_ptr_arr - bucket ptr array
 * Returns:
 *      SOC_E_XXX defined in error.h
 */
int
_soc_th_alpm_128_sanity_check(int u, int min, int max, int check_sw,
                              int *bkt_ptr_arr, alpm_bkt_usg_t  *bkt_usg)
{
    int             rv = SOC_E_NONE;
    int             lpm_idx, lpm_idx2, fd_lpm_idx2, alpm_idx;
    int             j, ipv6;
    int             vrf_id, vrf;
    int             fd_lpm_idx, fd_bkt_ptr, fd_alpm_idx;
    int             ent, ent_num, bkt_ptr, sub_bkt_ptr;
    int             error1 = 0, error2 = 0, error = 0, success = 0;
    int             used;
    int             bpm_len, ip_len;
    int             trie_bpm_len, default_route;
    int             alloc_size;
    uint32          bank_disable = 0;
    uint32          e[SOC_MAX_MEM_FIELD_WORDS] = {0};
    uint32          shadow[SOC_MAX_MEM_FIELD_WORDS] = {0};
    uint32          prefix[5], length;
    trie_t          *pfx_trie  = NULL;
    trie_node_t     *lpmp      = NULL;
    payload_t       *tmp_pyld  = NULL;
    uint32          data0[10] = {0};
    uint32          data1[10] = {0};
    char            *buffer = NULL;
    defip_pair_128_entry_t   *lpm_entry, lpm_entry2, lpm_bmp;
    soc_mem_t       bkt_mem_type;
    soc_mem_t       alpm_mem = L3_DEFIP_ALPM_IPV6_128m;
    int             bpm_check = 0;

    /* Calculate table size. */
    alloc_size = sizeof(defip_pair_128_entry_t) * (max - min + 1);

    /* Allocate memory buffer. */
    buffer = soc_cm_salloc(u, alloc_size, "lpm_tbl");
    if (buffer == NULL) {
        return (SOC_E_MEMORY);
    }

    /* Reset allocated buffer. */
    sal_memset(buffer, 0, alloc_size);

    SOC_ALPM_LPM_LOCK(u);

    /* Read table to the buffer. */
    if (soc_mem_read_range(u, L3_DEFIP_PAIR_128m, MEM_BLOCK_ANY,
                           min, max, buffer) < 0) {
        soc_cm_sfree(u, buffer);
        SOC_ALPM_LPM_UNLOCK(u);
        return (SOC_E_INTERNAL);
    }

    ipv6 = L3_DEFIP_MODE_128;
    ent_num = _soc_th_alpm_bkt_entry_cnt(u, alpm_mem);

    for (lpm_idx = min; lpm_idx <= max; lpm_idx++) {
        int is_ipmc = 0;
        if (error1) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u,
                     "\tL3_DEFIP_PAIR_128 index:%d check failed. error count %d\n"),
                     lpm_idx - 1, error1));
            error = 1;
        } else if (success) {
            LOG_INFO(BSL_LS_SOC_ALPM,(BSL_META_U(u,
                     "\tL3_DEFIP_PAIR_128 index:%d check passed. success count %d\n"),
                     lpm_idx - 1, success));
        }
        error1 = error2 = success = 0;
        lpm_entry = soc_mem_table_idx_to_pointer(u, L3_DEFIP_PAIR_128m,
                                 defip_pair_128_entry_t *, buffer, lpm_idx - min);

        bkt_ptr = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_BKT_PTRf);
        if (!SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, VALID0_LWRf)) {
            continue;
        } else {
            /* cache coherency check */
            defip_pair_128_entry_t hw_ent, sw_ent;
            soc_mem_t cmem = L3_DEFIP_PAIR_128m;
            sal_memset(&hw_ent, 0, sizeof(hw_ent));
            sal_memset(&sw_ent, 0, sizeof(sw_ent));
            rv = _soc_mem_alpm_read_cache(u, cmem, SOC_BLOCK_ANY,
                                          lpm_idx, &sw_ent);
            if (SOC_SUCCESS(rv)) {
                rv = soc_mem_read_no_cache(u, 0, cmem, 0, SOC_BLOCK_ANY,
                                           lpm_idx, &hw_ent);
                if (SOC_SUCCESS(rv)) {
                    soc_mem_parity_field_clear(
                        u, cmem, (void *)&hw_ent, (void *)&sw_ent);
                    if (sal_memcmp(&sw_ent, &hw_ent,
                                   soc_mem_entry_bytes(u, cmem)) != 0) {
                        LOG_ERROR(BSL_LS_SOC_ALPM,
                            (BSL_META_U(u, "\t%s index:[%d], ipv6(%d)"
                            " cache mismatch\n"), SOC_MEM_NAME(u, cmem),
                            lpm_idx, ipv6));
                        error1 ++;
                    }
                }
            }

            /* We can just use defip_pair_128_entry_t because it's always
             * longer than aux_entry_t */
            cmem = L3_DEFIP_AUX_TABLEm;
            sal_memset(&hw_ent, 0, sizeof(hw_ent));
            sal_memset(&sw_ent, 0, sizeof(sw_ent));
            lpm_idx2 = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, lpm_idx, 1);
            rv = _soc_mem_alpm_read_cache(u, cmem, SOC_BLOCK_ANY,
                    SOC_ALPM_128_ADDR_LWR(u, lpm_idx2), &sw_ent);
            if (SOC_SUCCESS(rv)) {
                rv = soc_mem_read_no_cache(u, 0, cmem, 0, SOC_BLOCK_ANY,
                        SOC_ALPM_128_ADDR_LWR(u, lpm_idx2), &hw_ent);
                if (SOC_SUCCESS(rv)) {
                    soc_mem_parity_field_clear(
                        u, cmem, (void *)&hw_ent, (void *)&sw_ent);
                    if (sal_memcmp(&sw_ent, &hw_ent,
                                   soc_mem_entry_bytes(u, cmem)) != 0) {
                        LOG_ERROR(BSL_LS_SOC_ALPM,
                            (BSL_META_U(u, "\t%s index:[%d], ipv6(%d)"
                            " cache mismatch\n"), SOC_MEM_NAME(u, cmem),
                            SOC_ALPM_128_ADDR_LWR(u, lpm_idx2), ipv6));
                        error1 ++;
                    }
                }
            }
            sal_memset(&hw_ent, 0, sizeof(hw_ent));
            sal_memset(&sw_ent, 0, sizeof(sw_ent));
            rv = _soc_mem_alpm_read_cache(u, cmem, SOC_BLOCK_ANY,
                    SOC_ALPM_128_ADDR_UPR(u, lpm_idx2), &sw_ent);
            if (SOC_SUCCESS(rv)) {
                rv = soc_mem_read_no_cache(u, 0, cmem, 0, SOC_BLOCK_ANY,
                        SOC_ALPM_128_ADDR_UPR(u, lpm_idx2), &hw_ent);
                if (SOC_SUCCESS(rv)) {
                    soc_mem_parity_field_clear(
                        u, cmem, (void *)&hw_ent, (void *)&sw_ent);
                    if (sal_memcmp(&sw_ent, &hw_ent,
                                   soc_mem_entry_bytes(u, cmem)) != 0) {
                        LOG_ERROR(BSL_LS_SOC_ALPM,
                            (BSL_META_U(u, "\t%s index:[%d], ipv6(%d)"
                            " cache mismatch\n"), SOC_MEM_NAME(u, cmem),
                            SOC_ALPM_128_ADDR_UPR(u, lpm_idx2), ipv6));
                        error1 ++;
                    }
                }
            }
        }

        is_ipmc = 0;
        if (soc_feature(u, soc_feature_ipmc_defip)) {
            if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, MULTICAST_ROUTEf)) {
                is_ipmc = soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                              lpm_entry, MULTICAST_ROUTEf);
            } else if (soc_mem_field_valid(u, L3_DEFIP_PAIR_128m, DATA_TYPEf)) {
                if (soc_mem_field32_get(u, L3_DEFIP_PAIR_128m,
                                        lpm_entry, DATA_TYPEf) == 2) {
                    is_ipmc = 1;
                } else {
                    is_ipmc = 0;
                }
            }
        }

        if (SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, GLOBAL_HIGHf) ||
            is_ipmc ||
            (SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, GLOBAL_ROUTEf) &&
             ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_TCAM_ALPM)) {
            if (bkt_ptr != 0) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u, "\tWrong bkt_ptr %d\n"),
                          bkt_ptr));
                error1 ++;
            }
            continue;
        }
        if (bkt_ptr == 0) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u, "\tWrong bkt_ptr2 %d\n"),
                      bkt_ptr));
            error1 ++;
        }

        j = 0;
        if (soc_feature(u, soc_feature_generic_dest)) {
            uint32 val, dest_type = SOC_MEM_FIF_DEST_NEXTHOP;
            val = soc_mem_field32_dest_get(u, L3_DEFIP_PAIR_128m, lpm_entry,
                                           DESTINATIONf, &dest_type);
            if (dest_type == SOC_MEM_FIF_DEST_ECMP) {
                data0[j++] = 1;
            } else {
                data0[j++] = 0;
            }
            data0[j++] = val;
            data0[j++] = val;
        } else {
            data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m,
                                                 lpm_entry, ECMPf);
            data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m,
                                                 lpm_entry, ECMP_PTRf);
            data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m,
                                                 lpm_entry, NEXT_HOP_INDEXf);
        }
        data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, PRIf);
        data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, RPEf);
        data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, DST_DISCARDf);
        data0[j++] = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, CLASS_IDf);

        /* Check if bucket pointer duplicated */
        if (ALPM_CTRL(u).bkt_sharing) {
            sub_bkt_ptr = SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m, lpm_entry, ALG_SUB_BKT_PTRf);
        } else {
            sub_bkt_ptr = 0;
        }
        if (bkt_ptr_arr) {
            if (bkt_ptr_arr[bkt_ptr * SOC_TH_MAX_SUB_BUCKETS + sub_bkt_ptr] == -1) {
                bkt_ptr_arr[bkt_ptr * SOC_TH_MAX_SUB_BUCKETS + sub_bkt_ptr] = lpm_idx;
                if (ALPM_CTRL(u).double_wide[ipv6]) {
                    bkt_ptr_arr[(bkt_ptr + 1) * SOC_TH_MAX_SUB_BUCKETS + sub_bkt_ptr] = lpm_idx;
                }
                success ++;
            } else {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u, "\tConflict bucket pointer [%d,%d]: "
                          "was %d now %d\n"), bkt_ptr, sub_bkt_ptr,
                          bkt_ptr_arr[bkt_ptr * SOC_TH_MAX_SUB_BUCKETS + sub_bkt_ptr],
                          lpm_idx));
                error1 ++;
            }
        }

        (void) soc_th_alpm_128_lpm_vrf_get(u, lpm_entry, &vrf_id, &vrf);

        /* read shadow table for bpm length */
        lpm_idx2 = soc_th_alpm_physical_idx(u, L3_DEFIP_PAIR_128m, lpm_idx, 1);

        if (bkt_usg) {
            if (bkt_usg[bkt_ptr].sub_bkts == 0) {
                bkt_usg[bkt_ptr].global = (vrf == SOC_VRF_MAX(u) + 1);
            }
            bkt_usg[bkt_ptr].sub_bkts |= 1U << sub_bkt_ptr;
            bkt_usg[bkt_ptr].pivots[sub_bkt_ptr] =
                (SOC_ALPM_128_ADDR_LWR(u, lpm_idx2) << 1);
        }

        bpm_len = -1;
        bpm_check = 0;

        if (!ALPM_CTRL(u).aux_enable) {
            rv = _soc_th_alpm_128_pivot_bmp_len_get(u, lpm_entry,
                                                    (uint32 *)&bpm_len);
            if (SOC_SUCCESS(rv)) {
                bpm_check = 1;
            }
        } else {
            rv = soc_mem_read(u, L3_DEFIP_AUX_TABLEm, MEM_BLOCK_ANY,
                              SOC_ALPM_128_ADDR_LWR(u, lpm_idx2), shadow);

            if (SOC_SUCCESS(rv)) {
                bpm_len = soc_mem_field32_get(u, L3_DEFIP_AUX_TABLEm,
                                              shadow, BPM_LENGTH0f);
                ip_len  = soc_mem_field32_get(u, L3_DEFIP_AUX_TABLEm,
                                              shadow, IP_LENGTH0f);

                if (bpm_len > ip_len) {
                    LOG_ERROR(BSL_LS_SOC_ALPM,
                              (BSL_META_U(u, "\tAUX Table corrupted\n")));
                    error1 ++;
                } else {
                    success ++;
                }
                bpm_check = 1;

            }
        }

        if ((bpm_check == 1) && (bpm_len == 0) &&
            SOC_MEM_OPT_F32_GET_128(u, L3_DEFIP_PAIR_128m,
                                    lpm_entry, DEFAULT_MISSf)) {
            if (ALPM_CTRL(u).alpm_mode == SOC_ALPM_MODE_COMBINED) {
                error1 ++;
            } else {
                bpm_check = 0;
            }
        }

        if (bpm_check) {
            sal_memcpy(&lpm_bmp, lpm_entry, sizeof(defip_pair_128_entry_t));
            _soc_th_alpm_128_pfx_len_to_mask(u, &lpm_bmp, bpm_len);

            fd_lpm_idx = fd_bkt_ptr = fd_alpm_idx = -1;
            rv = _soc_th_alpm_128_find(
                     u, alpm_mem, &lpm_bmp, vrf_id, vrf, e,
                     &fd_lpm_idx, &fd_bkt_ptr, &fd_alpm_idx,
                     (SOC_IS_TRIDENT3X(u) ? TRUE :
                     (ALPM_CTRL(u).aux_enable ? FALSE : TRUE)));
            if (fd_lpm_idx > 0) {
                fd_lpm_idx = soc_th_alpm_logical_idx(u, L3_DEFIP_PAIR_128m,
                                SOC_ALPM_128_DEFIP_TO_PAIR(u, fd_lpm_idx >> 1), 1);
            }
            if (SOC_SUCCESS(rv)) {
                j = 0;
                if (soc_feature(u, soc_feature_generic_dest)) {
                    uint32 val, dest_type = SOC_MEM_FIF_DEST_NEXTHOP;
                    val = soc_mem_field32_dest_get(u, alpm_mem, e,
                                                   DESTINATIONf, &dest_type);
                    if (dest_type == SOC_MEM_FIF_DEST_ECMP) {
                        data1[j++] = 1;
                    } else {
                        data1[j++] = 0;
                    }
                    data1[j++] = val;
                    data1[j++] = val;
                } else {
                    data1[j++] = soc_mem_field32_get(u, alpm_mem, e, ECMPf);
                    data1[j++] = soc_mem_field32_get(u, alpm_mem, e, ECMP_PTRf);
                    data1[j++] = soc_mem_field32_get(u, alpm_mem, e, NEXT_HOP_INDEXf);
                }
                data1[j++] = soc_mem_field32_get(u, alpm_mem, e, PRIf);
                data1[j++] = soc_mem_field32_get(u, alpm_mem, e, RPEf);
                data1[j++] = soc_mem_field32_get(u, alpm_mem, e, DST_DISCARDf);
                data1[j++] = soc_mem_field32_get(u, alpm_mem, e, CLASS_IDf);

                if (sal_memcmp(data0, data1, sizeof(data0)) != 0) {
                    LOG_ERROR(BSL_LS_SOC_ALPM,
                              (BSL_META_U(u,
                              "\tData mismatch: "
                              "lpm_idx %d find_lpm_idx %d "
                              "find_alpm_idx %d find_bkt_ptr %d\n"),
                              lpm_idx, fd_lpm_idx,
                              fd_alpm_idx, fd_bkt_ptr));
                    error1 ++;
                } else {
                    success ++;
                }
            } else {
                if (rv == SOC_E_NOT_FOUND &&
                    (vrf_id == SOC_L3_VRF_GLOBAL || ALPM_CTRL(u).gp_zoned)) {
                    LOG_VERBOSE(BSL_LS_SOC_ALPM,
                              (BSL_META_U(u,
                              "\t_soc_th_alpm_128_find rv=%d: "
                              "lpm_idx %d find_lpm_idx %d "
                              "find_alpm_idx %d find_bkt_ptr %d,"
                              "(Possible: global route or !combined "
                              "without default)\n"),
                              rv, lpm_idx, fd_lpm_idx,
                              fd_alpm_idx, fd_bkt_ptr));
                } else {
                    LOG_ERROR(BSL_LS_SOC_ALPM,
                              (BSL_META_U(u,
                              "\t_soc_th_alpm_128_find rv=%d: "
                              "lpm_idx %d find_lpm_idx %d "
                              "find_alpm_idx %d find_bkt_ptr %d\n"),
                              rv, lpm_idx, fd_lpm_idx,
                              fd_alpm_idx, fd_bkt_ptr));
                    error1 ++;
                }
            }
        }

        bank_disable = ALPM_CTRL(u).bank_disable_bmp_8b[vrf != SOC_VRF_MAX(u) + 1];
        /* Traverse bucket */
        for (ent = 0; ent < ent_num; ent++) {
            rv = _soc_th_alpm_mem_index(u, alpm_mem, bkt_ptr, ent, bank_disable,
                                          &alpm_idx);
            if (SOC_FAILURE(rv)) {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u, "\tALPM mem index get failure: rv %d "
                          "bkt_ptr %d, ent %d, bank_dis %d\n"),
                          rv, bkt_ptr, ent, bank_disable));
                error1 ++;
                error2 ++;
            }

            rv = _soc_mem_alpm_read(u, alpm_mem, MEM_BLOCK_ANY, alpm_idx, e);
            if (SOC_FAILURE(rv)) {
                continue;
            }

            if (!soc_mem_field32_get(u, alpm_mem, e, VALIDf)) {
                continue;
            }

            if (ALPM_CTRL(u).bkt_sharing && sub_bkt_ptr !=
                soc_mem_field32_get(u, alpm_mem, e, SUB_BKT_PTRf)) {
                continue;
            }

            if (bkt_usg) {
                bkt_usg[bkt_ptr].count++;
            }

            (void) _soc_th_alpm_128_lpm_ent_init(u, e, alpm_mem, ipv6, vrf_id,
                                                 ALPM_LOG_BKT(bkt_ptr, sub_bkt_ptr),
                                                 0, &lpm_entry2, 0);

            if (check_sw) {
                rv = _soc_th_alpm_128_sw_prefix_check(u, alpm_mem, ipv6, &lpm_entry2, vrf_id, vrf);
                if (SOC_FAILURE(rv)) {
                    error1 ++;
                    error2 ++;
                    LOG_ERROR(BSL_LS_SOC_ALPM,
                              (BSL_META_U(u,
                              "_soc_th_alpm_128_sw_prefix_check rv=%d: v6 = %d, vrf_id = %d, vrf = %d\n"),
                               rv, ipv6, vrf_id, vrf));
                }
            }

            fd_lpm_idx2 = fd_lpm_idx = fd_bkt_ptr = fd_alpm_idx = -1;
            rv = _soc_th_alpm_128_find(
                     u, alpm_mem, &lpm_entry2, vrf_id, vrf,
                     e, &fd_lpm_idx, &fd_bkt_ptr, &fd_alpm_idx,
                     (SOC_IS_TRIDENT3X(u) ? TRUE :
                     (ALPM_CTRL(u).aux_enable ? FALSE : TRUE)));

            if (SOC_SUCCESS(rv)) {
                fd_lpm_idx2 = soc_th_alpm_logical_idx(u, L3_DEFIP_PAIR_128m,
                                SOC_ALPM_128_DEFIP_TO_PAIR(u, fd_lpm_idx >> 1), 1);
            }
            if (SOC_FAILURE(rv) ||
                fd_bkt_ptr  != ALPM_LOG_BKT(bkt_ptr, sub_bkt_ptr) ||
                fd_lpm_idx2 != lpm_idx ||
                SOC_ALPM_128_DEFIP_TO_PAIR(u, fd_lpm_idx >> 1) != lpm_idx2 ||
                fd_alpm_idx != alpm_idx) {

                error1 ++;
                error2 ++;
                LOG_ERROR(BSL_LS_SOC_ALPM,
                          (BSL_META_U(u,
                          "\t_soc_th_alpm_128_find2 rv=%d: "
                          "fl [%d,%d] fa %d fb [%d,%d] "
                          "l [%d,%d] a %d b [%d,%d]\n"),
                          rv,
                          SOC_ALPM_128_DEFIP_TO_PAIR(u, fd_lpm_idx >> 1),
                          fd_lpm_idx2, fd_alpm_idx,
                          ALPM_PHY_BKT(u, fd_bkt_ptr), ALPM_SUB_BKT(u, fd_bkt_ptr),
                          lpm_idx2, lpm_idx, alpm_idx, bkt_ptr, sub_bkt_ptr));
            }
        }
        if (error2 == 0) {
            success ++;
        }

        if (!check_sw) {
            continue;
        }

        /*
         * Check hardware table above.
         * Check software table below.
 */

        /* lpm hash */

#ifdef FB_LPM_128_HASH_SUPPORT
        rv = LPM_128_HASH_VERIFY(u, lpm_entry, lpm_idx);
        if (SOC_FAILURE(rv)) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u, "\tLPM Hash check failed: rv %d "
                                  "lpm_idx %d\n"), rv, lpm_idx));
            error1 ++;
        } else {
            success ++;
        }
#endif

        /* bucket bitmap */
        rv = soc_th_alpm_bucket_is_assigned(u,  ALPM_LOG_BKT(bkt_ptr, sub_bkt_ptr),
                                            vrf, ipv6, &used);
        if (SOC_FAILURE(rv) || sub_bkt_ptr >= SOC_TH_MAX_SUB_BUCKETS) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u, "\tInvalid bucket pointer [%d,%d] "
                      "detected, in memory %s index %d\n"), bkt_ptr, sub_bkt_ptr,
                      SOC_MEM_NAME(u, L3_DEFIP_PAIR_128m), lpm_idx));
            error1 ++;
        } else if (used == 0) {
            /* If bucket was already freed */
            LOG_ERROR(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "\tFreed bucket pointer %d "
                     "detected, in memory %s index %d\n"), bkt_ptr,
                     SOC_MEM_NAME(u, L3_DEFIP_PAIR_128m), lpm_idx));
            error1 ++;
        } else {
            success ++;
        }

        /* bucket view map */
        bkt_mem_type = soc_alpm_cmn_bkt_view_get(u,
            SOC_TH_ALPM_AIDX(u, bkt_ptr, 0, 0, 0));

        if (alpm_mem != bkt_mem_type) {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                      (BSL_META_U(u, "\tMismatched alpm view "
                      "in bucket %d, expected %s, was %s\n"), bkt_ptr,
                      SOC_MEM_NAME(u, alpm_mem),
                      SOC_MEM_NAME(u, bkt_mem_type)));
            error1 ++;
        } else {
            success ++;
        }

        /* Check bpm len information */
        rv = _soc_th_alpm_128_prefix_create(u, lpm_entry, prefix,
                                             &length, &default_route);

        if (SOC_SUCCESS(rv)) {
            pfx_trie = VRF_PREFIX_TRIE_IPV6_128(u, vrf);
            lpmp = NULL;
            if (pfx_trie) {
                rv = trie_find_lpm(pfx_trie, prefix, length, &lpmp);
            }
            if (SOC_SUCCESS(rv) && lpmp){
                tmp_pyld = (payload_t *) lpmp;
                if (tmp_pyld->bkt_ptr != NULL) {
                    trie_bpm_len = ((payload_t *)(tmp_pyld->bkt_ptr))->len;
                    if (trie_bpm_len != bpm_len) {
                        LOG_ERROR(BSL_LS_SOC_ALPM,
                                (BSL_META_U(u, "\tBPM len mismatch: lpm_idx %d"
                                 " alpm_idx %d bpm_len %d trie_bpm_len %d\n"),
                                 lpm_idx, alpm_idx, bpm_len, trie_bpm_len));
                        error1 ++;
                    } else {
                        success ++;
                    }
                } else {
                    success ++;
                }
            } else {
                LOG_ERROR(BSL_LS_SOC_ALPM,
                        (BSL_META_U(u, "\ttrie_find_lpm failed: "
                                    "lpm_idx %d alpm_idx %d lpmp %p\n"),
                         lpm_idx, alpm_idx, lpmp));
                error1 ++;
            }
        } else {
            LOG_ERROR(BSL_LS_SOC_ALPM,
                    (BSL_META_U(u, "\tPrefix creating failed: "
                                "lpm_idx %d alpm_idx %d\n" ), lpm_idx, alpm_idx));
            error1 ++;
        }
    }
    if (error1) {
        LOG_ERROR(BSL_LS_SOC_ALPM,
                (BSL_META_U(u,
                 "\tL3_DEFIP_PAIR_128 index:%d check failed. error count %d\n"),
                 lpm_idx - 1, error1));
        error = 1;
    } else if (success) {
        LOG_INFO(BSL_LS_SOC_ALPM,(BSL_META_U(u,
                 "\tL3_DEFIP_PAIR_128 index:%d check passed. success count %d\n"),
                 lpm_idx - 1, success));
    }

    SOC_ALPM_LPM_UNLOCK(u);
    soc_cm_sfree(u, buffer);

    return (error ? SOC_E_FAIL: SOC_E_NONE);
}






#endif /* TOMAHAWK APACHE */
#endif /* ALPM_ENABLE */
