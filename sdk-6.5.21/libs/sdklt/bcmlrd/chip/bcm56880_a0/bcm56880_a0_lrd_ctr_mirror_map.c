/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/ctr/bcm56880_a0/bcm56880_a0_CTR_MIRROR.map.ltl for
 *      bcm56880_a0
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
#include <bcmlrd/chip/bcm56880_a0/bcm56880_a0_lrd_field_data.h>
#include <bcmlrd/chip/bcm56880_a0/bcm56880_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56880_a0/bcm56880_a0_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "bcm56880_a0_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* CTR_MIRROR field init */
static const bcmlrd_field_data_t bcm56880_a0_lrd_ctr_mirror_map_field_data_mmd[] = {
    { /* 0 MIRROR_INSTANCE_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 1 MIRROR_SESSION_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 2 PIPE */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x3,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 3 MIRROR_PKT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_lrd_ctr_mirror_map_field_data = {
    .fields = 4,
    .field = bcm56880_a0_lrd_ctr_mirror_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_lrd_ctr_mirrort_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MAX_INDEX,
        .value = 3,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MIN_INDEX,
        .value = 0,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = TRUE,
    },
    { /* 3 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 15,
    },
    { /* 4 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 0,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_lrd_ctr_mirrort_attr_group = {
    .attributes = 5,
    .attr = bcm56880_a0_lrd_ctr_mirrort_attr_entry,
};


const bcmltd_field_desc_t
bcm56880_a0_lrd_bcmltx_id_to_table_sel_src_field_desc_s0[1] = {
    {
        .field_id  = CTR_MIRRORt_MIRROR_SESSION_IDf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 3,
        .entry_idx = 0,
        .reserved  = 0
    },
};

const bcmltd_field_desc_t
bcm56880_a0_lrd_bcmltx_id_to_table_sel_ctr_mirror_dst_field_desc_d0[1] = {
    {
        .field_id  = BCMLRD_FIELD_TABLE_SEL,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 7,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const uint32_t
bcm56880_a0_lrd_id_to_table_sel_transform_tbl_t0[8] = {
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_0m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_1m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_2m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_3m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_4m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_5m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_6m,
    IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_7m,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_fwd_s0_d0_t0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_LTA_BCMLTX_ID_TO_TABLE_SEL_XFRM_HANDLER_FWD_S0_D0_T0_ID,
    .src_fields = 1,
    .src = bcm56880_a0_lrd_bcmltx_id_to_table_sel_src_field_desc_s0,
    .dst_fields = 1,
    .dst = bcm56880_a0_lrd_bcmltx_id_to_table_sel_ctr_mirror_dst_field_desc_d0,
    .tables = 8,
    .tbl = bcm56880_a0_lrd_id_to_table_sel_transform_tbl_t0,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_rev_s0_d0_t0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_LTA_BCMLTX_ID_TO_TABLE_SEL_XFRM_HANDLER_REV_S0_D0_T0_ID,
    .src_fields = 1,
    .src = bcm56880_a0_lrd_bcmltx_id_to_table_sel_ctr_mirror_dst_field_desc_d0,
    .dst_fields = 1,
    .dst = bcm56880_a0_lrd_bcmltx_id_to_table_sel_src_field_desc_s0,
    .tables = 8,
    .tbl = bcm56880_a0_lrd_id_to_table_sel_transform_tbl_t0,
};


static const bcmlrd_map_entry_t bcm56880_a0_lrd_ctr_mirrort_ipost_mirror_sampler_mirror_session_counter_0_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INDEX,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 3,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_MIRRORt_MIRROR_INSTANCE_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INSTANCE,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 1,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_MIRRORt_PIPEf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 1,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = MTP_COUNTf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 63,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_MIRRORt_MIRROR_PKTf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 63,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 3 */
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
                /* handler: bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_fwd_s0_d0_t0 */
                .desc = &bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_fwd_s0_d0_t0_desc,
            },
        },
    },
    { /* 4 */
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
                /* handler: bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_rev_s0_d0_t0 */
                .desc = &bcm56880_a0_lta_bcmltx_id_to_table_sel_xfrm_handler_rev_s0_d0_t0_desc,
            },
        },
    },
};
static const bcmlrd_map_group_t bcm56880_a0_lrd_ctr_mirror_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = IPOST_MIRROR_SAMPLER_MIRROR_SESSION_COUNTER_0m,
        },
        .entries = 5,
        .entry = bcm56880_a0_lrd_ctr_mirrort_ipost_mirror_sampler_mirror_session_counter_0_map_entry
    },
};
const bcmlrd_map_t bcm56880_a0_lrd_ctr_mirror_map = {
    .src_id = CTR_MIRRORt,
    .field_data = &bcm56880_a0_lrd_ctr_mirror_map_field_data,
    .groups = 1,
    .group  = bcm56880_a0_lrd_ctr_mirror_map_group,
    .table_attr = &bcm56880_a0_lrd_ctr_mirrort_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
