/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm/cosq.h>
#include <bcm_int/control.h>

#include <bcm_int/ltsw/mbcm/mod.h>
#include <bcm_int/ltsw/dev.h>
#include <bcm_int/ltsw/lt_intf.h>
#include <bcm_int/ltsw/cosq.h>
#include <bcm_int/ltsw/cosq_int.h>
#include <bcm_int/ltsw/ha.h>

#include <shr/shr_bitop.h>
#include <sal/sal_types.h>
#include <shr/shr_debug.h>
#include <bcmltd/chip/bcmltd_str.h>
#include <bcmlt/bcmlt.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_COSQ

/*!
 * \brief Cosq mirror-on-drop config structure.
 */
typedef struct cosq_mod_config_s {

    /*! Profile used bitmap. */
    SHR_BITDCL *profile_bmp;

    /*! Profile number. */
    uint32_t profile_num;

} cosq_mod_config_t;

/******************************************************************************
 * Private functions
 */


/* Cosq mod config global structure. */
static cosq_mod_config_t cosq_mod_cfg[BCM_MAX_NUM_UNITS];

/* Cosq mod config. */
#define MOD_CFG(uint) (&cosq_mod_cfg[unit])

/* Cosq mod profile number. */
#define MOD_PROFILE_NUM(unit) \
            (MOD_CFG(unit)->profile_num)

/* Cosq mod profile used bitmap. */
#define MOD_PROF_BMP(unit) \
            (MOD_CFG(unit)->profile_bmp)

/* Set Cosq mod profile used bitmap. */
#define MOD_PROF_BMP_USED_SET(unit, id) \
            (SHR_BITSET(MOD_PROF_BMP(unit), id))

/* Get Cosq mod profile used bitmap. */
#define MOD_PROF_BMP_USED_GET(unit, id) \
            (SHR_BITGET(MOD_PROF_BMP(unit), id))

/* Clear Cosq mod profile used bitmap. */
#define MOD_PROF_BMP_USED_CLR(unit, id) \
            (SHR_BITCLR(MOD_PROF_BMP(unit), id))

/*!
 * \brief Set mod control configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] config Cosq mod control configuration structure.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_control_set(int unit, bcm_cosq_mod_control_t *control)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MIRROR_ON_DROPs, 0, 0, {0}},
        /*1*/ {RESERVED_LIMIT_CELLSs, 0, 0, {0}},
        /*2*/ {OPERATIONAL_STATEs, 0, 0, {0}},
    };
    bcmi_ltsw_cosq_device_info_t info;
    uint32_t valid_flags;
    SHR_FUNC_ENTER(unit);

    /* No flags are set. */
    if (!(control->valid_flags & (BCM_COSQ_MOD_CONTROL_ENABLE_VALID |
          BCM_COSQ_MOD_CONTROL_POOL_LIMIT_VALID))) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    valid_flags = control->valid_flags & (~(BCM_COSQ_MOD_CONTROL_ENABLE_VALID |
                                BCM_COSQ_MOD_CONTROL_POOL_LIMIT_VALID));
    /* Invalid flag is set. */
    if (valid_flags != 0) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    /* Get MMU cell size. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_ltsw_cosq_device_info_get(unit, &info));

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    if (control->valid_flags & BCM_COSQ_MOD_CONTROL_ENABLE_VALID) {
        field[0].u.val = control->enable;
        field[0].flags = BCMI_LT_FIELD_F_SET;
    }
    if (control->valid_flags & BCM_COSQ_MOD_CONTROL_POOL_LIMIT_VALID) {
        field[1].u.val = (control->pool_limit + (info.mmu_cell_size - 1)) /
                          info.mmu_cell_size;
        field[1].flags = BCMI_LT_FIELD_F_SET;
    }

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_set(unit,
                           TM_MIRROR_ON_DROP_CONTROLs,
                           &lt_entry,
                           NULL));

    field[0].flags = 0;
    field[1].flags = 0;
    field[2].flags = BCMI_LT_FIELD_F_GET | BCMI_LT_FIELD_F_SYMBOL;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           TM_MIRROR_ON_DROP_CONTROLs,
                           &lt_entry,
                           NULL,
                           NULL));

    /* Incorrect cell limit. */
    if (sal_strcasecmp(field[2].u.sym_val,
                       INCORRECT_RESERVED_CELLS_LIMITs) == 0) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Get mod control configuration.
 *
 * \param [in] unit Unit Number.
 * \param [out] config Cosq mod control configuration structure.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_control_get(int unit, bcm_cosq_mod_control_t *control)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MIRROR_ON_DROPs, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*1*/ {RESERVED_LIMIT_CELLSs, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*2*/ {OPERATIONAL_STATEs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    bcmi_ltsw_cosq_device_info_t info;
    SHR_FUNC_ENTER(unit);

    /* Get MMU cell size. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_ltsw_cosq_device_info_get(unit, &info));

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[2].flags |= BCMI_LT_FIELD_F_SYMBOL;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           TM_MIRROR_ON_DROP_CONTROLs,
                           &lt_entry,
                           NULL,
                           NULL));

    /* Incorrect cell limit. */
    if (sal_strcasecmp(field[2].u.sym_val,
                       INCORRECT_RESERVED_CELLS_LIMITs) == 0) {
        SHR_ERR_EXIT(SHR_E_CONFIG);
    }

    control->enable = field[0].u.val;
    control->pool_limit = field[1].u.val * info.mmu_cell_size;
    control->valid_flags |= BCM_COSQ_MOD_CONTROL_ENABLE_VALID |
                      BCM_COSQ_MOD_CONTROL_POOL_LIMIT_VALID;

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Allocate a mod profile id.
 *
 * \param [in] unit Unit Number.
 * \param [out] id Profile id.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_profile_id_alloc(int unit, int *id)
{
    int i, size;
    cosq_mod_config_t *mod_cfg = MOD_CFG(unit);
    SHR_BITDCL *bitmap = NULL;
    SHR_FUNC_ENTER(unit);

    bitmap = mod_cfg->profile_bmp;
    size = MOD_PROFILE_NUM(unit);
    SHR_NULL_CHECK(bitmap, SHR_E_INIT);

    for (i = 0; i < size; i++) {
        if (!SHR_BITGET(bitmap, i)) {
            break;
        }
    }

    if (i >= size) {
        SHR_ERR_EXIT(SHR_E_RESOURCE);
    }
    *id = i;

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Hold a mod profile id.
 *
 * \param [in] unit Unit Number.
 * \param [in] id Profile id.
 */
static void
cosq_mod_profile_id_hold(int unit, int id)
{
    if (id >= MOD_PROFILE_NUM(unit)) {
        return;
    }
    MOD_PROF_BMP_USED_SET(unit, id);
    return;
}

/*!
 * \brief Free a mod profile id.
 *
 * \param [in] unit Unit Number.
 * \param [out] id Profile id.
 */
static void
cosq_mod_profile_id_free(int unit, int id)
{
    if (id >= MOD_PROFILE_NUM(unit)) {
        return;
    }
    MOD_PROF_BMP_USED_CLR(unit, id);
    return;
}

/*!
 * \brief Create a mod profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] options Options flags.
 * \param [out] profile_id Profile id.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_profile_create(int unit, uint32_t options, int *profile_id)
{
    int id;
    SHR_FUNC_ENTER(unit);

    if (options & BCM_COSQ_MOD_PROFILE_OPTIONS_WITH_ID) {
        id = *profile_id;
        if (id < 0 || id >= MOD_PROFILE_NUM(unit)) {
            SHR_ERR_EXIT(SHR_E_BADID);
        }

        if (MOD_PROF_BMP_USED_GET(unit, id)) {
            SHR_ERR_EXIT(SHR_E_EXISTS);
        }

        /* Mark profile id is used. */
        cosq_mod_profile_id_hold(unit, id);
    } else {
        /* Allocate mod profile id. */
        SHR_IF_ERR_VERBOSE_EXIT
            (cosq_mod_profile_id_alloc(unit, &id));

        /* Mark profile id is used. */
        cosq_mod_profile_id_hold(unit, id);
        *profile_id = id;
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Destroy a mod profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile id.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_profile_destroy(int unit, int profile_id)
{
    SHR_FUNC_ENTER(unit);

    if (profile_id < 0 || profile_id >= MOD_PROFILE_NUM(unit)) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    if (!MOD_PROF_BMP_USED_GET(unit, profile_id)) {
        SHR_ERR_EXIT(SHR_E_NOT_FOUND);
    }

    /* Free mod profile id. */
    cosq_mod_profile_id_free(unit, profile_id);

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Set a mod profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile id.
 * \param [in] profile Mod profile structure.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_profile_set(int unit, int profile_id, bcm_cosq_mod_profile_t *profile)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_PROFILE_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {PERCENTAGE_0_25s, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*2*/ {PERCENTAGE_25_50s, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*3*/ {PERCENTAGE_50_75s, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*4*/ {PERCENTAGE_75_100s, BCMI_LT_FIELD_F_SET, 0, {0}},
    };
    SHR_FUNC_ENTER(unit);

    if (profile_id < 0 || profile_id >= MOD_PROFILE_NUM(unit)) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    if (!MOD_PROF_BMP_USED_GET(unit, profile_id)) {
        SHR_ERR_EXIT(SHR_E_NOT_FOUND);
    }

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = profile_id;
    field[1].u.val = profile->percent_0_25;
    field[2].u.val = profile->percent_25_50;
    field[3].u.val = profile->percent_50_75;
    field[4].u.val = profile->percent_75_100;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_set(unit,
                           TM_MIRROR_ON_DROP_PROFILEs,
                           &lt_entry,
                           NULL));
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Get a mod profile for given profile id.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile id.
 * \param [out] profile Mod profile structure.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_profile_get(int unit, int profile_id, bcm_cosq_mod_profile_t *profile)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_PROFILE_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {PERCENTAGE_0_25s, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*2*/ {PERCENTAGE_25_50s, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*3*/ {PERCENTAGE_50_75s, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*4*/ {PERCENTAGE_75_100s, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    SHR_FUNC_ENTER(unit);

    if (profile_id < 0 || profile_id >= MOD_PROFILE_NUM(unit)) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    if (!MOD_PROF_BMP_USED_GET(unit, profile_id)) {
        SHR_ERR_EXIT(SHR_E_NOT_FOUND);
    }

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = profile_id;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           TM_MIRROR_ON_DROP_PROFILEs,
                           &lt_entry,
                           NULL,
                           NULL));

    profile->percent_0_25   = field[1].u.val;
    profile->percent_25_50  = field[2].u.val;
    profile->percent_50_75  = field[3].u.val;
    profile->percent_75_100 = field[4].u.val;

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Add mod destination.
 *
 * \param [in] unit Unit Number.
 * \param [in] mod_dest mod destination.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_dest_add(int unit, bcmi_ltsw_cosq_mod_dest_t *mod_dest)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_DESTINATION_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {PORT_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*2*/ {NULL, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*3*/ {UC_Qs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };
    bcmi_lt_field_t field1[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_ENCAP_PROFILE_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {MIRROR_ENCAP_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };
    bcmi_ltsw_cosq_port_map_info_t info;

    SHR_FUNC_ENTER(unit);

    /* Get UC/MC queue number. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_ltsw_cosq_port_map_info_get(unit, mod_dest->port, &info));

    /* The cosq exceeds the maximum queue number. */
    if (mod_dest->cosq >= (info.num_uc_q + info.num_mc_q)) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = 0;
    field[1].u.val = mod_dest->port;
    if (mod_dest->cosq >= info.num_uc_q) {
        field[2].fld_name = TM_MC_Q_IDs;
        field[2].u.val = mod_dest->cosq - info.num_uc_q;
    } else {
        field[2].fld_name = TM_UC_Q_IDs;
        field[2].u.val = mod_dest->cosq;
        field[3].u.val = true;
    }

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_set(unit,
                           TM_MIRROR_ON_DROP_DESTINATIONs,
                           &lt_entry,
                           NULL));

    lt_entry.fields = field1;
    lt_entry.nfields = sizeof(field1) / sizeof(field1[0]);
    lt_entry.attr = 0;

    /* TM_MIRROR_ON_DROP_ENCAP_PROFILE has only one entry(0). */
    field1[0].u.val = 0;
    field1[1].u.val = mod_dest->encap_id;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_set(unit,
                           TM_MIRROR_ON_DROP_ENCAP_PROFILEs,
                           &lt_entry,
                           NULL));
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Delete mod destination.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_dest_delete(int unit)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_DESTINATION_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };
    bcmi_lt_field_t field1[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_ENCAP_PROFILE_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = 0;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_delete(unit,
                              TM_MIRROR_ON_DROP_DESTINATIONs,
                              &lt_entry,
                              NULL));

    lt_entry.fields = field1;
    lt_entry.nfields = sizeof(field1) / sizeof(field1[0]);
    lt_entry.attr = 0;

    field1[0].u.val = 0;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_delete(unit,
                              TM_MIRROR_ON_DROP_ENCAP_PROFILEs,
                              &lt_entry,
                              NULL));
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Get mod destination.
 *
 * \param [in] unit Unit Number.
 * \param [out] mod_dest Mod destination.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_dest_get(int unit, bcmi_ltsw_cosq_mod_dest_t *mod_dest)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_DESTINATION_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {PORT_IDs, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*2*/ {TM_MC_Q_IDs, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*3*/ {TM_UC_Q_IDs, BCMI_LT_FIELD_F_GET, 0, {0}},
        /*4*/ {UC_Qs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    bcmi_lt_field_t field1[] =
    {
        /*0*/ {TM_MIRROR_ON_DROP_ENCAP_PROFILE_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {MIRROR_ENCAP_IDs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    int num_uc_queue, num_mc_queue;

    SHR_FUNC_ENTER(unit);

    /* Get UC/MC queue number. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_ltsw_cosq_num_queue_get(unit, &num_uc_queue, &num_mc_queue));

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = 0;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           TM_MIRROR_ON_DROP_DESTINATIONs,
                           &lt_entry,
                           NULL,
                           NULL));

    mod_dest->port = field[1].u.val;
    if (field[4].u.val) {
        mod_dest->cosq = field[3].u.val;
    } else {
        mod_dest->cosq = field[2].u.val + num_uc_queue;
    }

    lt_entry.fields = field1;
    lt_entry.nfields = sizeof(field1) / sizeof(field1[0]);
    lt_entry.attr = 0;

    field1[0].u.val = 0;

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           TM_MIRROR_ON_DROP_ENCAP_PROFILEs,
                           &lt_entry,
                           NULL,
                           NULL));
    mod_dest->encap_id = field1[1].u.val;

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Get mod statistics.
 *
 * \param [in] unit Unit Number.
 * \param [in] id Statistics object id.
 * \param [in] stat Cosq mod Statistics type.
 * \param [out] value Statistics value.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_stat_get(int unit, bcm_cosq_object_id_t *id, bcm_cosq_mod_stat_t stat,
                  uint64_t *value)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {BUFFER_POOLs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {NULL, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    bcmi_ltsw_cosq_device_info_t info;

    SHR_FUNC_ENTER(unit);

    /* Get MMU cell size. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_ltsw_cosq_device_info_get(unit, &info));

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = id->buffer;

    if (stat == bcmCosqModStatPoolBytesCurrent) {
        field[1].fld_name = CELL_USAGEs;
    } else if (stat == bcmCosqModStatDroppedPackets) {
        field[1].fld_name = DROP_PKTs;
    } else if (stat == bcmCosqModStatEnqueuedPackets) {
        field[1].fld_name = QUEUE_PKTs;
    } else {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_get(unit,
                           CTR_TM_MIRROR_ON_DROP_BUFFER_POOLs,
                           &lt_entry,
                           NULL, NULL));

    if(stat == bcmCosqModStatPoolBytesCurrent) {
        *value = field[1].u.val * info.mmu_cell_size;
    } else {
        *value = field[1].u.val;
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Set mod statistics counter.
 *
 * \param [in] unit Unit Number.
 * \param [in] id Statistics object id.
 * \param [in] stat Cosq mod Statistics type
 * \param [in] value Statistics value.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_stat_set(int unit, bcm_cosq_object_id_t *id, bcm_cosq_mod_stat_t stat,
                  uint64_t value)
{

    /*
     * The following fields of CTR_TM_MIRROR_ON_DROP_BUFFER_POOL
     * are read-only, so not able to set.
     * 1.CELL_USAGE
     * 2.DROP_PKT
     * 3.QUEUE_PKT
     */
    return SHR_E_PARAM;
}

/*!
 * \brief Init mod statistics counter.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_stat_init(int unit)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {BUFFER_POOLs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field) / sizeof(field[0]);
    lt_entry.attr = 0;

    /* Counter for ITM0. */
    field[0].u.val = 0;
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_entry_insert(unit,
                              CTR_TM_MIRROR_ON_DROP_BUFFER_POOLs,
                              &lt_entry,
                              NULL));
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Init Cosq mod sub-module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE on success and error code otherwise.
 */
static int
cosq_mod_init(int unit)
{
    int warm = bcmi_warmboot_get(unit);
    cosq_mod_config_t *mod_cfg;
    void *ptr = NULL;
    uint32_t alloc_size, req_size;
    uint64_t min = 0;
    uint64_t max = 0;
    SHR_FUNC_ENTER(unit);

    mod_cfg = &cosq_mod_cfg[unit];

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmi_lt_field_value_range_get(unit,
                                       TM_MIRROR_ON_DROP_PROFILEs,
                                       TM_MIRROR_ON_DROP_PROFILE_IDs,
                                       &min,
                                       &max));
    mod_cfg->profile_num = (uint32_t)max + 1;

    /* Allocate HA memory for mod profile. */
    req_size = SHR_BITALLOCSIZE(mod_cfg->profile_num);
    alloc_size = req_size;
    ptr = bcmi_ltsw_ha_mem_alloc(unit,
                                 BCMI_HA_COMP_ID_COSQ,
                                 BCMINT_COSQ_MOD_PROFILE_BMP_SUB_COMP_ID,
                                 "bcmCosqModProfBmp",
                                 &alloc_size);
    SHR_NULL_CHECK(ptr, SHR_E_MEMORY);
    SHR_IF_ERR_VERBOSE_EXIT
        ((alloc_size < req_size) ? SHR_E_MEMORY : SHR_E_NONE);
    if (!warm) {
        sal_memset(ptr, 0, alloc_size);
    }
    mod_cfg->profile_bmp = ptr;

    if (!warm) {
        /* Clean up MOD statistics counter. */
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmi_lt_clear(unit, CTR_TM_MIRROR_ON_DROP_BUFFER_POOLs));

        /* Insert MOD statistics counter. */
        SHR_IF_ERR_VERBOSE_EXIT
            (cosq_mod_stat_init(unit));
    }

exit:
    if (SHR_FUNC_ERR()) {
        if (!warm) {
            if (ptr != NULL) {
                (void)bcmi_ltsw_ha_mem_free(unit, mod_cfg->profile_bmp);
                mod_cfg->profile_bmp = NULL;
            }
        }
    }
    SHR_FUNC_EXIT();
}


static int
bcm56780_a0_ltsw_cosq_mod_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_init(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_detach(int unit)
{
    return SHR_E_NONE;
}

static int
bcm56780_a0_ltsw_cosq_mod_control_set(
    int unit,
    bcm_cosq_mod_control_t *control)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_control_set(unit, control));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_control_get(
    int unit,
    bcm_cosq_mod_control_t *control)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_control_get(unit, control));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_profile_create(
    int unit,
    uint32_t options,
    int *profile_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_profile_create(unit, options, profile_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_profile_destroy(
    int unit,
    int profile_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_profile_destroy(unit, profile_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_profile_set(
    int unit,
    int profile_id,
    bcm_cosq_mod_profile_t *profile)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_profile_set(unit, profile_id, profile));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_profile_get(
    int unit,
    int profile_id,
    bcm_cosq_mod_profile_t *profile)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_profile_get(unit, profile_id, profile));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_dest_add(
    int unit,
    bcmi_ltsw_cosq_mod_dest_t *mod_dest)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_dest_add(unit, mod_dest));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_dest_delete(
    int unit,
    bcmi_ltsw_cosq_mod_dest_t *mod_dest)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_dest_delete(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_dest_get(
    int unit,
    bcmi_ltsw_cosq_mod_dest_t *mod_dest)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_dest_get(unit, mod_dest));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_instance_id_get(
    int unit,
    int *instance_id)
{
    return SHR_E_UNAVAIL;
}

static int
bcm56780_a0_ltsw_cosq_mod_stat_get(
    int unit,
    bcm_cosq_object_id_t *id,
    bcm_cosq_mod_stat_t stat,
    uint64_t *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_stat_get(unit, id, stat, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_cosq_mod_stat_set(
    int unit,
    bcm_cosq_object_id_t *id,
    bcm_cosq_mod_stat_t stat,
    uint64_t value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (cosq_mod_stat_set(unit, id, stat, value));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Cosq_mod driver function variable for bcm56780_a0 device.
 */
static mbcm_ltsw_cosq_mod_drv_t bcm56780_a0_ltsw_cosq_mod_drv = {
    .cosq_mod_init = bcm56780_a0_ltsw_cosq_mod_init,
    .cosq_mod_detach = bcm56780_a0_ltsw_cosq_mod_detach,
    .cosq_mod_control_set = bcm56780_a0_ltsw_cosq_mod_control_set,
    .cosq_mod_control_get = bcm56780_a0_ltsw_cosq_mod_control_get,
    .cosq_mod_profile_create = bcm56780_a0_ltsw_cosq_mod_profile_create,
    .cosq_mod_profile_destroy = bcm56780_a0_ltsw_cosq_mod_profile_destroy,
    .cosq_mod_profile_set = bcm56780_a0_ltsw_cosq_mod_profile_set,
    .cosq_mod_profile_get = bcm56780_a0_ltsw_cosq_mod_profile_get,
    .cosq_mod_dest_add = bcm56780_a0_ltsw_cosq_mod_dest_add,
    .cosq_mod_dest_delete = bcm56780_a0_ltsw_cosq_mod_dest_delete,
    .cosq_mod_dest_get = bcm56780_a0_ltsw_cosq_mod_dest_get,
    .cosq_mod_instance_id_get = bcm56780_a0_ltsw_cosq_mod_instance_id_get,
    .cosq_mod_stat_get = bcm56780_a0_ltsw_cosq_mod_stat_get,
    .cosq_mod_stat_set = bcm56780_a0_ltsw_cosq_mod_stat_set
};

/******************************************************************************
 * Public functions
 */

int
bcm56780_a0_ltsw_cosq_mod_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_cosq_mod_drv_set(unit, &bcm56780_a0_ltsw_cosq_mod_drv));

exit:
    SHR_FUNC_EXIT();
}

