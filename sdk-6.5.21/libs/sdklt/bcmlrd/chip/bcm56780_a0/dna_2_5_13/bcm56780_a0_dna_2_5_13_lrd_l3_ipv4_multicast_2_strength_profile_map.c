/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/npl/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_L3_IPV4_MULTICAST_2_STRENGTH_PROFILE.map.ltl for
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
/* L3_IPV4_MULTICAST_2_STRENGTH_PROFILE field init */
static const bcmlrd_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_field_data_mmd[] = {
    { /* 0 L3_IPV4_MULTICAST_2_STRENGTH_PROFILE_INDEX */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 1 L3_DST_DESTINATION_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 2 L3_DST_DESTINATION_TYPE_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 3 L3_DST_CLASS_ID_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 4 L3_DST_MISC_CTRL_0_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 5 L3_DST_MISC_CTRL_1_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 6 MTU_PROFILE_PTR_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 7 EXPECTED_L3_IIF_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 8 RPA_ID_STRENGTH */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_field_data = {
    .fields = 9,
    .field = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profilet_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 16,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_RESOURCE_INFO,
        .value = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_2_STRENGTH_PROFILE_RESOURCE_INFOt,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profilet_attr_group = {
    .attributes = 3,
    .attr = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profilet_attr_entry,
};

static const bcmlrd_map_entry_t bcm56780_a0_dna_2_5_13_lrd_bcmimm_l3_ipv4_multicast_2_strength_profile_entry[] = {
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
            /* handler: bcm56780_a0_dna_2_5_13_lta_bcmimm_l3_ipv4_multicast_2_strength_profile_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56780_A0_DNA_2_5_13_LTA_BCMIMM_L3_IPV4_MULTICAST_2_STRENGTH_PROFILE_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56780_a0_dna_2_5_13_lrd_bcmimm_l3_ipv4_multicast_2_strength_profile_entry
    },
};
const bcmlrd_map_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map = {
    .src_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_2_STRENGTH_PROFILEt,
    .field_data = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_field_data,
    .groups = 1,
    .group  = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profile_map_group,
    .table_attr = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_2_strength_profilet_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
