/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/npl/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_FP_EGR_SLICE_INFO.map.ltl for
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
/* FP_EGR_SLICE_INFO field init */
static const bcmlrd_field_data_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_field_data_mmd[] = {
    { /* 0 FP_EGR_SLICE_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x3,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 1 PIPE */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x3,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 2 ENTRY_INUSE_CNT */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 3 ENTRY_MAXIMUM */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_field_data = {
    .fields = 4,
    .field = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_infot_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 4,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_infot_attr_group = {
    .attributes = 2,
    .attr = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_infot_attr_entry,
};

static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_bcmfp_fp_egr_slice_info_entry[] = {
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
            /* handler: bcm56880_a0_dna_4_7_11_lta_bcmfp_fp_egr_slice_info_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56880_A0_DNA_4_7_11_LTA_BCMFP_FP_EGR_SLICE_INFO_CTH_HANDLER_ID
        }
    },
};
/* Map conditions */
static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_edit[] = {
    0, /* Number of groups. */
    0, /* Number of multi-entry transforms. */
};

static const bcmlrd_condition_t
bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_condition[] = {
    {
        .op    = BCMLRD_CONDITION_AND,
        .table = FP_CONFIGt,
        .field = FP_CONFIGt_FP_EGR_OPERMODE_PIPEUNIQUEf,
        .value = 1
    },
};

static const bcmlrd_cond_expr_t
bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_expr[] = {
    {
        .num_cond = 1,
        .cond     = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_condition + 0,
    },
};

static const bcmlrd_cond_field_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_field[] = {
    {
        .field = FP_EGR_SLICE_INFOt_PIPEf,
        .expr  = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_expr + 0,
        .edit  = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_edit + 0,
    },
};
static const bcmlrd_cond_data_t
bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond = {
    .num_field_cond = 1,
    .field_cond = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond_field
};
static const bcmlrd_map_group_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56880_a0_dna_4_7_11_lrd_bcmfp_fp_egr_slice_info_entry
    },
};
const bcmlrd_map_t bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map = {
    .src_id = FP_EGR_SLICE_INFOt,
    .field_data = &bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_field_data,
    .groups = 1,
    .group  = bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_group,
    .table_attr = &bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_infot_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE,
    .cond = &bcm56880_a0_dna_4_7_11_lrd_fp_egr_slice_info_map_cond,
};
