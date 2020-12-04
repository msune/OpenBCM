/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/device/bcm56990_b0/bcm56990_b0_DEVICE_EM_GROUP.map.ltl for
 *      bcm56990_b0
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
#include <bcmlrd/chip/bcm56990_b0/bcm56990_b0_lrd_field_data.h>
#include <bcmlrd/chip/bcm56990_b0/bcm56990_b0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56990_b0/bcm56990_b0_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56990_b0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "bcm56990_b0_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* DEVICE_EM_GROUP field init */
static const bcmlrd_field_data_t bcm56990_b0_lrd_device_em_group_map_field_data_mmd[] = {
    { /* 0 DEVICE_EM_GROUP_ID */
      .flags = BCMLTD_FIELD_F_KEY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x1,
      .def = &bcm56990_b0_lrd_ifd_u32_0x1,
      .max = &bcm56990_b0_lrd_ifd_u32_0x8,
      .depth = 0,
      .width = 4,
      .edata = BCM56990_B0_LRD_DEVICE_EM_GROUP_ID_KEY_T_DATA,
    },
    { /* 1 ROBUST */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 2 SEED */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0xfffffd,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 3 VECTOR_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x6,
      .def = &bcm56990_b0_lrd_ifd_u32_0x6,
      .max = &bcm56990_b0_lrd_ifd_u32_0x6,
      .depth = 0,
      .width = 3,
      .edata = BCM56990_B0_LRD_DEVICE_HASH_VECTOR_T_DATA,
    },
    { /* 4 DEVICE_EM_BANK_ID */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0x1a,
      .depth = 16,
      .width = 5,
      .edata = BCM56990_B0_LRD_DEVICE_EM_BANK_ID_VALUE_T_DATA,
    },
    { /* 5 NUM_BANKS */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x8,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56990_b0_lrd_device_em_group_map_field_data = {
    .fields = 6,
    .field = bcm56990_b0_lrd_device_em_group_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_b0_lrd_device_em_groupt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 20,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 8,
    },
    { /* 3 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 1,
    },
};

static const bcmlrd_map_attr_t bcm56990_b0_lrd_device_em_groupt_attr_group = {
    .attributes = 4,
    .attr = bcm56990_b0_lrd_device_em_groupt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56990_b0_lrd_bcmimm_device_em_group_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_TABLE_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            /* handler: bcm56990_b0_lta_bcmimm_device_em_group_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56990_B0_LTA_BCMIMM_DEVICE_EM_GROUP_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56990_b0_lrd_device_em_group_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56990_b0_lrd_bcmimm_device_em_group_entry
    },
};
const bcmlrd_map_t bcm56990_b0_lrd_device_em_group_map = {
    .src_id = DEVICE_EM_GROUPt,
    .field_data = &bcm56990_b0_lrd_device_em_group_map_field_data,
    .groups = 1,
    .group  = bcm56990_b0_lrd_device_em_group_map_group,
    .table_attr = &bcm56990_b0_lrd_device_em_groupt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE
};
