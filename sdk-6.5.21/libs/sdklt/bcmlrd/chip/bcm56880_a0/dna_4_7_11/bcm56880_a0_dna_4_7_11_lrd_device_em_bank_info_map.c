/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/device/bcm56880_a0/bcm56880_a0_DEVICE_EM_BANK_INFO.map.ltl for
 *      bcm56880_a0 variant dna_4_7_11
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
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_field_data.h>
#include <bcmlrd/chip/bcm56880_a0/bcm56880_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "../bcm56880_a0_lrd_enumpool.h"
#include "bcm56880_a0_dna_4_7_11_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* DEVICE_EM_BANK_INFO field init */
static const bcmlrd_field_data_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_field_data_mmd[] = {
    { /* 0 DEVICE_EM_BANK_ID */
      .flags = BCMLTD_FIELD_F_KEY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x6a,
      .depth = 0,
      .width = 7,
      .edata = BCM56880_A0_DNA_4_7_11_LRD_DEVICE_EM_BANK_ID_KEY_T_DATA,
    },
    { /* 1 TYPE */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x3,
      .depth = 0,
      .width = 2,
      .edata = BCM56880_A0_LRD_DEVICE_EM_BANK_TYPE_T_DATA,
    },
    { /* 2 LOOKUP_CNT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 3 GROUP_CNT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 4 DEVICE_EM_GROUP_ID */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x128,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x128,
      .depth = 512,
      .width = 9,
      .edata = BCM56880_A0_DNA_4_7_11_LRD_DEVICE_EM_GROUP_ID_VALUE_T_DATA,
    },
    { /* 5 BASE_ENTRY_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 6 BASE_BUCKET_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 7 NUM_BASE_BUCKETS */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 8 NUM_BASE_ENTRIES */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_field_data = {
    .fields = 9,
    .field = bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_infot_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 107,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_infot_attr_group = {
    .attributes = 2,
    .attr = bcm56880_a0_dna_4_7_11_lrd_device_em_bank_infot_attr_entry,
};

static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_bcmimm_device_em_bank_info_entry[] = {
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
            /* handler: bcm56880_a0_dna_4_7_11_lta_bcmimm_device_em_bank_info_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56880_A0_DNA_4_7_11_LTA_BCMIMM_DEVICE_EM_BANK_INFO_CTH_HANDLER_ID
        }
    },
};
const bcmlrd_field_selector_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_select[] = {
    { /* Node:0, Type:ROOT, TYPE */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = DEVICE_EM_BANK_INFOt_TYPEf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:1, Type:FIELD, BASE_ENTRY_WIDTH */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = DEVICE_EM_BANK_INFOt_BASE_ENTRY_WIDTHf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = DEVICE_EM_BANK_INFOt_TYPEf,
        .selector_value = 0 /* HASH */
    },
    { /* Node:2, Type:FIELD, BASE_BUCKET_WIDTH */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = DEVICE_EM_BANK_INFOt_BASE_BUCKET_WIDTHf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = DEVICE_EM_BANK_INFOt_TYPEf,
        .selector_value = 0 /* HASH */
    },
    { /* Node:3, Type:FIELD, NUM_BASE_BUCKETS */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = DEVICE_EM_BANK_INFOt_NUM_BASE_BUCKETSf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = DEVICE_EM_BANK_INFOt_TYPEf,
        .selector_value = 0 /* HASH */
    },
    { /* Node:4, Type:FIELD, NUM_BASE_ENTRIES */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_FIELD,
        .field_id = DEVICE_EM_BANK_INFOt_NUM_BASE_ENTRIESf,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = 0,
        .group = 0,
        .selector_id = DEVICE_EM_BANK_INFOt_TYPEf,
        .selector_value = 0 /* HASH */
    },
};

const bcmlrd_field_selector_data_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_select_data = {
    .num_field_selector = 5,
    .field_selector = bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_select,
};

static const bcmlrd_map_group_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56880_a0_dna_4_7_11_lrd_bcmimm_device_em_bank_info_entry
    },
};
const bcmlrd_map_t bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map = {
    .src_id = DEVICE_EM_BANK_INFOt,
    .field_data = &bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_field_data,
    .groups = 1,
    .group  = bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_group,
    .table_attr = &bcm56880_a0_dna_4_7_11_lrd_device_em_bank_infot_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE,
    .sel = &bcm56880_a0_dna_4_7_11_lrd_device_em_bank_info_map_select_data,
};
