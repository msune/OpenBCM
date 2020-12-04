/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/table/common/common_TABLE_RESOURCE_INFO.map.ltl for
 *      bcm56780_a0
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
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_field_data.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "bcm56780_a0_lrd_enumpool.h"
#include <bcmltd/id/bcmltd_common_id.h> /* LTID_T */
/* TABLE_RESOURCE_INFO field init */
static const bcmlrd_field_data_t bcm56780_a0_lrd_table_resource_info_map_field_data_mmd[] = {
    { /* 0 TABLE_ID */
      .flags = BCMLTD_FIELD_F_KEY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = BCM56780_A0_LRD_LTID_T_DATA,
    },
    { /* 1 RESOURCE_INFO */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 2 RESOURCE_INFO_TABLE_ID */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = BCM56780_A0_LRD_LTID_T_DATA,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_lrd_table_resource_info_map_field_data = {
    .fields = 3,
    .field = bcm56780_a0_lrd_table_resource_info_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_lrd_table_resource_infot_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_lrd_table_resource_infot_attr_group = {
    .attributes = 1,
    .attr = bcm56780_a0_lrd_table_resource_infot_attr_entry,
};

static const bcmlrd_map_group_t bcm56780_a0_lrd_table_resource_info_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_LTM,
            .id = 0,
        },
        .entries = 0,
        .entry = NULL
    },
};
const bcmlrd_map_t bcm56780_a0_lrd_table_resource_info_map = {
    .src_id = TABLE_RESOURCE_INFOt,
    .field_data = &bcm56780_a0_lrd_table_resource_info_map_field_data,
    .groups = 1,
    .group  = bcm56780_a0_lrd_table_resource_info_map_group,
    .table_attr = &bcm56780_a0_lrd_table_resource_infot_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE
};
