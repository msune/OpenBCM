/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/table/common/common_TABLE_FIELD_INFO.map.ltl for
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
#include <bcmltd/id/bcmltd_common_id.h> /* LTID_T */
/* TABLE_FIELD_INFO field init */
static const bcmlrd_field_data_t bcm56990_b0_lrd_table_field_info_map_field_data_mmd[] = {
    { /* 0 TABLE_ID */
      .flags = BCMLTD_FIELD_F_KEY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = BCM56990_B0_LRD_LTID_T_DATA,
    },
    { /* 1 FIELD_ID */
      .flags = BCMLTD_FIELD_F_KEY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = BCM56990_B0_LRD_LFID_T_DATA,
    },
    { /* 2 SYMBOL */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 3 MIN_LIMIT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u64_0x0,
      .def = &bcm56990_b0_lrd_ifd_u64_0x0,
      .max = &bcm56990_b0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 4 MAX_LIMIT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u64_0x0,
      .def = &bcm56990_b0_lrd_ifd_u64_0x0,
      .max = &bcm56990_b0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 5 DEFAULT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u64_0x0,
      .def = &bcm56990_b0_lrd_ifd_u64_0x0,
      .max = &bcm56990_b0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 6 SYMBOL_DEFAULT */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = BCM56990_B0_LRD_ENUM_NAME_T_DATA,
    },
    { /* 7 KEY */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 8 INDEX_ALLOC_KEY_FIELD */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 9 READ_ONLY */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 10 ARRAY_DEPTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 11 ELEMENTS */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 12 FIELD_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 13 SELECTOR */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 14 NUM_GROUP */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56990_b0_lrd_table_field_info_map_field_data = {
    .fields = 15,
    .field = bcm56990_b0_lrd_table_field_info_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_b0_lrd_table_field_infot_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56990_b0_lrd_table_field_infot_attr_group = {
    .attributes = 1,
    .attr = bcm56990_b0_lrd_table_field_infot_attr_entry,
};

const bcmlrd_field_selector_t bcm56990_b0_lrd_table_field_info_map_select[] = {
    { /* Node:0, Type:ROOT, SYMBOL */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = TABLE_FIELD_INFOt_SYMBOLf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:1, Type:FIELD, SYMBOL_DEFAULT */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = TABLE_FIELD_INFOt_SYMBOL_DEFAULTf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = TABLE_FIELD_INFOt_SYMBOLf,
        .selector_value = TRUE
    },
    { /* Node:2, Type:FIELD, DEFAULT */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = TABLE_FIELD_INFOt_DEFAULTf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = TABLE_FIELD_INFOt_SYMBOLf,
        .selector_value = FALSE
    },
};

const bcmlrd_field_selector_data_t bcm56990_b0_lrd_table_field_info_map_select_data = {
    .num_field_selector = 3,
    .field_selector = bcm56990_b0_lrd_table_field_info_map_select,
};

static const bcmlrd_map_group_t bcm56990_b0_lrd_table_field_info_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_LTM,
            .id = 0,
        },
        .entries = 0,
        .entry = NULL
    },
};
const bcmlrd_map_t bcm56990_b0_lrd_table_field_info_map = {
    .src_id = TABLE_FIELD_INFOt,
    .field_data = &bcm56990_b0_lrd_table_field_info_map_field_data,
    .groups = 1,
    .group  = bcm56990_b0_lrd_table_field_info_map_group,
    .table_attr = &bcm56990_b0_lrd_table_field_infot_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE,
    .sel = &bcm56990_b0_lrd_table_field_info_map_select_data,
};
