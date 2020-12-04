/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/dlb/bcm56880_a0/bcm56880_a0_DLB_TRUNK.map.ltl for
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
/* DLB_TRUNK field init */
static const bcmlrd_field_data_t bcm56880_a0_lrd_dlb_trunk_map_field_data_mmd[] = {
    { /* 0 DLB_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_lrd_ifd_u8_0x1,
      .def = &bcm56880_a0_lrd_ifd_u8_0x1,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7f,
      .depth = 0,
      .width = 7,
      .edata = NULL,
    },
    { /* 1 INACTIVITY_TIME */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x10,
      .def = &bcm56880_a0_lrd_ifd_u16_0x10,
      .max = &bcm56880_a0_lrd_ifd_u16_0x7fff,
      .depth = 0,
      .width = 15,
      .edata = NULL,
    },
    { /* 2 ASSIGNMENT_MODE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x2,
      .depth = 0,
      .width = 2,
      .edata = BCM56880_A0_LRD_DLB_ASSIGNMENT_MODE_T_DATA,
    },
    { /* 3 FLOW_SET_SIZE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x8,
      .depth = 0,
      .width = 4,
      .edata = BCM56880_A0_LRD_DLB_FLOW_SET_SIZE_T_DATA,
    },
    { /* 4 NUM_PATHS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x40,
      .depth = 0,
      .width = 7,
      .edata = NULL,
    },
    { /* 5 PORT_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0x9f,
      .depth = 64,
      .width = 8,
      .edata = NULL,
    },
    { /* 6 PRIMARY_PATH_THRESHOLD */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 7 ALTERNATE_PATH_COST */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 8 ALTERNATE_PATH_BIAS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 9 ALTERNATE_NUM_PATHS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x40,
      .depth = 0,
      .width = 7,
      .edata = NULL,
    },
    { /* 10 ALTERNATE_PORT_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0x9f,
      .depth = 64,
      .width = 8,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_lrd_dlb_trunk_map_field_data = {
    .fields = 11,
    .field = bcm56880_a0_lrd_dlb_trunk_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_lrd_dlb_trunkt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 128,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_lrd_dlb_trunkt_attr_group = {
    .attributes = 2,
    .attr = bcm56880_a0_lrd_dlb_trunkt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56880_a0_lrd_bcmimm_dlb_trunk_entry[] = {
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
            /* handler: bcm56880_a0_lta_bcmimm_dlb_trunk_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56880_A0_LTA_BCMIMM_DLB_TRUNK_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56880_a0_lrd_dlb_trunk_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56880_a0_lrd_bcmimm_dlb_trunk_entry
    },
};
const bcmlrd_map_t bcm56880_a0_lrd_dlb_trunk_map = {
    .src_id = DLB_TRUNKt,
    .field_data = &bcm56880_a0_lrd_dlb_trunk_map_field_data,
    .groups = 1,
    .group  = bcm56880_a0_lrd_dlb_trunk_map_group,
    .table_attr = &bcm56880_a0_lrd_dlb_trunkt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
