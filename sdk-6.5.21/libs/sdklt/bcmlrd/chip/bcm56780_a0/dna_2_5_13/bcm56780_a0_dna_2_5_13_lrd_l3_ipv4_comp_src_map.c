/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/npl/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_L3_IPV4_COMP_SRC.map.ltl for
 *      bcm56780_a0 variant dna_2_5_13
 *
 * Tool: $SDK/INTERNAL/fltg/bin/fltg
 *
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
#include <bcmlrd/bcmlrd_internal.h>
#include <bcmlrd/chip/bcmlrd_id.h>
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_field_data.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "../bcm56780_a0_lrd_enumpool.h"
#include "bcm56780_a0_dna_2_5_13_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* L3_IPV4_COMP_SRC field init */
static const bcmlrd_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_field_data_mmd[] = {
    { /* 0 L4_PORT */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 1 L4_PORT_MASK */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 2 IPV4 */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 3 IPV4_MASK */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 4 CLASS_ID */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_field_data = {
    .fields = 5,
    .field = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_SIZE,
        .value = 2621440,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TCAM_ORDERING,
        .value = LPM,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_attr_group = {
    .attributes = 3,
    .attr = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_attr_entry,
};


const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_src_field_desc_s0[4] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4_MASKf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 1,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4_MASKf,
        .field_idx = 0,
        .minbit    = 2,
        .maxbit    = 23,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4_MASKf,
        .field_idx = 0,
        .minbit    = 24,
        .maxbit    = 29,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4_MASKf,
        .field_idx = 0,
        .minbit    = 30,
        .maxbit    = 31,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_dst_field_desc[4] = {
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 150,
        .maxbit    = 151,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 156,
        .maxbit    = 177,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 178,
        .maxbit    = 183,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 184,
        .maxbit    = 185,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_src_field_desc_s0[4] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4f,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 1,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4f,
        .field_idx = 0,
        .minbit    = 2,
        .maxbit    = 23,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4f,
        .field_idx = 0,
        .minbit    = 24,
        .maxbit    = 29,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_IPV4f,
        .field_idx = 0,
        .minbit    = 30,
        .maxbit    = 31,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_dst_field_desc[4] = {
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 50,
        .maxbit    = 51,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 56,
        .maxbit    = 77,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 78,
        .maxbit    = 83,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 84,
        .maxbit    = 85,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_src_field_desc_s0[3] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORT_MASKf,
        .field_idx = 0,
        .minbit    = 10,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORT_MASKf,
        .field_idx = 0,
        .minbit    = 4,
        .maxbit    = 9,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORT_MASKf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 3,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_dst_field_desc[3] = {
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 196,
        .maxbit    = 201,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 190,
        .maxbit    = 195,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = MASKf,
        .field_idx = 0,
        .minbit    = 186,
        .maxbit    = 189,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_src_field_desc_s0[3] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORTf,
        .field_idx = 0,
        .minbit    = 10,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORTf,
        .field_idx = 0,
        .minbit    = 4,
        .maxbit    = 9,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_L4_PORTf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 3,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_dst_field_desc[3] = {
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 96,
        .maxbit    = 101,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 90,
        .maxbit    = 95,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = KEYf,
        .field_idx = 0,
        .minbit    = 86,
        .maxbit    = 89,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_IPV4_MASKF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_src_field_desc_s0,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_IPV4_MASKF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_dst_field_desc,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_IPV4F_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_src_field_desc_s0,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_IPV4F_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_dst_field_desc,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_ipv4f_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_L4_PORT_MASKF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 3,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_src_field_desc_s0,
    .dst_fields = 3,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_L4_PORT_MASKF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 3,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_dst_field_desc,
    .dst_fields = 3,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_L4_PORTF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 3,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_src_field_desc_s0,
    .dst_fields = 3,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_COMP_SRCT_L4_PORTF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 3,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_dst_field_desc,
    .dst_fields = 3,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_comp_srct_l4_portf_0_src_field_desc_s0,
};


static const bcmlrd_map_entry_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_memdb_tcam_ifta80_mem0_1_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLYf,
            .field_idx = 0,
            .minbit    = 210,
            .maxbit    = 225,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt_CLASS_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 15,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = VALIDf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 1,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 3,
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = KEYf,
            .field_idx = 0,
            .minbit    = 4,
            .maxbit    = 5,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 0,
            }
        },
    },
    { /* 3 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = MASKf,
            .field_idx = 0,
            .minbit    = 104,
            .maxbit    = 105,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 3,
            }
        },
    },
    { /* 4 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = KEYf,
            .field_idx = 0,
            .minbit    = 2,
            .maxbit    = 3,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 0,
            }
        },
    },
    { /* 5 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = MASKf,
            .field_idx = 0,
            .minbit    = 102,
            .maxbit    = 103,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 3,
            }
        },
    },
    { /* 6 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = DATA_ONLYf,
            .field_idx = 0,
            .minbit    = 359,
            .maxbit    = 360,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 2,
            }
        },
    },
    { /* 7 */
        .entry_type = BCMLRD_MAP_ENTRY_FWD_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 8 */
        .entry_type = BCMLRD_MAP_ENTRY_REV_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4_maskf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 9 */
        .entry_type = BCMLRD_MAP_ENTRY_FWD_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 10 */
        .entry_type = BCMLRD_MAP_ENTRY_REV_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_ipv4f_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 11 */
        .entry_type = BCMLRD_MAP_ENTRY_FWD_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 12 */
        .entry_type = BCMLRD_MAP_ENTRY_REV_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_port_maskf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 13 */
        .entry_type = BCMLRD_MAP_ENTRY_FWD_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 14 */
        .entry_type = BCMLRD_MAP_ENTRY_REV_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_comp_srct_l4_portf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
};
static const bcmlrd_map_group_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = MEMDB_TCAM_IFTA80_MEM0_1m,
        },
        .entries = 15,
        .entry = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_memdb_tcam_ifta80_mem0_1_map_entry
    },
};
const bcmlrd_map_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map = {
    .src_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_COMP_SRCt,
    .field_data = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_field_data,
    .groups = 1,
    .group  = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_src_map_group,
    .table_attr = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_comp_srct_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
