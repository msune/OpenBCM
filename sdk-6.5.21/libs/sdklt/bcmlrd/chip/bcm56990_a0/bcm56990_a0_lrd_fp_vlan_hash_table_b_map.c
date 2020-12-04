/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/fp/bcm56990_a0/bcm56990_a0_FP_VLAN_HASH_TABLE_B.map.ltl for
 *      bcm56990_a0
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
#include <bcmlrd/chip/bcm56990_a0/bcm56990_a0_lrd_field_data.h>
#include <bcmlrd/chip/bcm56990_a0/bcm56990_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56990_a0/bcm56990_a0_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56990_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "bcm56990_a0_lrd_enumpool.h"
/* FP_VLAN_HASH_TABLE_B field init */
static const bcmlrd_field_data_t bcm56990_a0_lrd_fp_vlan_hash_table_b_map_field_data_mmd[] = {
    { /* 0 FP_VLAN_HASH_TABLE_B_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_a0_lrd_ifd_u8_0x0,
      .def = &bcm56990_a0_lrd_ifd_u8_0x0,
      .max = &bcm56990_a0_lrd_ifd_u8_0xe,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 1 HASH_BUCKET_BITMAP */
      .flags = 0,
      .min = &bcm56990_a0_lrd_ifd_u16_0x0,
      .def = &bcm56990_a0_lrd_ifd_u16_0x0,
      .max = &bcm56990_a0_lrd_ifd_u16_0x1fff,
      .depth = 0,
      .width = 13,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56990_a0_lrd_fp_vlan_hash_table_b_map_field_data = {
    .fields = 2,
    .field = bcm56990_a0_lrd_fp_vlan_hash_table_b_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_a0_lrd_fp_vlan_hash_table_bt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = false,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 14,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 0,
    },
};

static const bcmlrd_map_attr_t bcm56990_a0_lrd_fp_vlan_hash_table_bt_attr_group = {
    .attributes = 3,
    .attr = bcm56990_a0_lrd_fp_vlan_hash_table_bt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56990_a0_lrd_fp_vlan_hash_table_bt_vfp_hash_field_bmap_table_b_map_entry[] = {
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
                    .field_id = FP_VLAN_HASH_TABLE_Bt_FP_VLAN_HASH_TABLE_B_IDf,
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
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = BITMAPf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 12,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = FP_VLAN_HASH_TABLE_Bt_HASH_BUCKET_BITMAPf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 12,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
};
static const bcmlrd_map_group_t bcm56990_a0_lrd_fp_vlan_hash_table_b_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = VFP_HASH_FIELD_BMAP_TABLE_Bm,
        },
        .entries = 2,
        .entry = bcm56990_a0_lrd_fp_vlan_hash_table_bt_vfp_hash_field_bmap_table_b_map_entry
    },
};
const bcmlrd_map_t bcm56990_a0_lrd_fp_vlan_hash_table_b_map = {
    .src_id = FP_VLAN_HASH_TABLE_Bt,
    .field_data = &bcm56990_a0_lrd_fp_vlan_hash_table_b_map_field_data,
    .groups = 1,
    .group  = bcm56990_a0_lrd_fp_vlan_hash_table_b_map_group,
    .table_attr = &bcm56990_a0_lrd_fp_vlan_hash_table_bt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
