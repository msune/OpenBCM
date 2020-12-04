/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/port/bcm56880_a0/bcm56880_a0_PORT.map.ltl for
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
/* PORT field init */
static const bcmlrd_field_data_t bcm56880_a0_dna_4_7_11_lrd_port_map_field_data_mmd[] = {
    { /* 0 PORT_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x9f,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 1 MY_MODID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 2 PORT_TYPE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = BCM56880_A0_DNA_4_7_11_LRD_PORT_TYPE_T_DATA,
    },
    { /* 3 V6L3 */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 4 V6IPMC */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 5 V4L3 */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 6 V4IPMC */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 7 OPERATING_MODE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 8 URPF_MODE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 9 URPF_DEFAULT_ROUTE_CHECK */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 10 PORT_PKT_CONTROL_ID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 11 MPLS */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 12 IPMC_USE_L3_IIF */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 13 IEEE_802_1AS */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 14 USE_IVID_AS_OVID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 15 VLAN_ING_TAG_ACTION_PROFILE_ID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 16 ING_OVID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 17 ING_OPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 18 ING_OCFI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 19 ING_IVID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 20 ING_IPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 21 ING_ICFI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 22 CTR_ING_FLEX_POOL_NUMBER */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 23 CTR_ING_FLEX_BASE_INDEX */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 24 CTR_ING_FLEX_OFFSET_MODE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 25 EGR_OVID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 26 EGR_ASSIGN_OPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 27 EGR_OPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 28 EGR_OCFI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 29 EGR_IVID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 30 EGR_ASSIGN_IPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 31 EGR_IPRI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 32 EGR_ICFI */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 33 VLAN_EGR_TAG_ACTION_PROFILE_ID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 34 CTR_EGR_FLEX_POOL_NUMBER */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 35 CTR_EGR_FLEX_BASE_INDEX */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 36 CTR_EGR_FLEX_OFFSET_MODE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 37 PRESERVE_CPU_TAG */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 38 CNTAG_DELETE_ON_PRI_MATCH */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 39 VLAN_ASSIGNMENT_BASED_IPV4 */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 40 VLAN_ASSIGNMENT_BASED_MAC */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 41 VLAN_ASSIGNMENT_PROTOCOL_ID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 42 VLAN_PRECEDENCE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 43 INBAND_TELEMETRY_IFA */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 44 INBAND_TELEMETRY_IOAM */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 45 INBAND_TELEMETRY_DATAPLANE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 46 INPORT_BITMAP_INDEX */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 47 L2_EIF_ID */
      .flags = 0,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 48 ING_SYSTEM_PORT_TABLE_ID */
      .flags = 0,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 49 MTU_CHECK */
      .flags = 0,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 50 MTU */
      .flags = 0,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x3fff,
      .depth = 0,
      .width = 14,
      .edata = NULL,
    },
    { /* 51 VFI_EGR_ADAPT_PORT_GRP */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 52 EGR_OPAQUE_TAG */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u32_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 53 CTR_ING_EFLEX_ACTION */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 54 CTR_EGR_EFLEX_ACTION */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 55 PIPE */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 56 VFI_EGR_ADAPT_PORT_GRP_LOOKUP */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 57 VFI_EGR_ADAPT_PORT_GRP_LOOKUP_MISS_DROP */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 58 VXLAN_VFI_EGR_ADAPT_PORT_GRP_LOOKUP */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 59 VXLAN_VFI_EGR_ADAPT_PORT_GRP_LOOKUP_MISS_DROP */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 60 NTP_TC */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 61 DEVICE_TS_PTP_MSG_CONTROL_PROFILE_ID */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 62 PORT_CONTEXT */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_dna_4_7_11_lrd_port_map_field_data = {
    .fields = 63,
    .field = bcm56880_a0_dna_4_7_11_lrd_port_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_dna_4_7_11_lrd_portt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 159,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 0,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_dna_4_7_11_lrd_portt_attr_group = {
    .attributes = 3,
    .attr = bcm56880_a0_dna_4_7_11_lrd_portt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_portt_epost_egr_mtu_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INDEX,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 7,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_PORT_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 7,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = MTU_ENABLEf,
            .field_idx = 0,
            .minbit    = 14,
            .maxbit    = 14,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_MTU_CHECKf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 0,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = MTU_SIZEf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 13,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_MTUf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 13,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
};
static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_portt_epre_edev_config_device_port_table_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INDEX,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 7,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_PORT_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 7,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = L2_OIFf,
            .field_idx = 0,
            .minbit    = 4,
            .maxbit    = 19,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_L2_EIF_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 15,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
};
static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_portt_idev_config_table_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INDEX,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 7,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_PORT_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 7,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DEVICE_PORTf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 7,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_PORT_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 7,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = ING_PP_PORTf,
            .field_idx = 0,
            .minbit    = 8,
            .maxbit    = 15,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_PORT_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 7,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 3 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = SYSTEM_PORTf,
            .field_idx = 0,
            .minbit    = 19,
            .maxbit    = 34,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = PORTt_ING_SYSTEM_PORT_TABLE_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 15,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
};
static const bcmlrd_map_group_t bcm56880_a0_dna_4_7_11_lrd_port_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = EPOST_EGR_MTUm,
        },
        .entries = 3,
        .entry = bcm56880_a0_dna_4_7_11_lrd_portt_epost_egr_mtu_map_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = EPRE_EDEV_CONFIG_DEVICE_PORT_TABLEm,
        },
        .entries = 2,
        .entry = bcm56880_a0_dna_4_7_11_lrd_portt_epre_edev_config_device_port_table_map_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = IDEV_CONFIG_TABLEm,
        },
        .entries = 4,
        .entry = bcm56880_a0_dna_4_7_11_lrd_portt_idev_config_table_map_entry
    },
};
const bcmlrd_map_t bcm56880_a0_dna_4_7_11_lrd_port_map = {
    .src_id = PORTt,
    .field_data = &bcm56880_a0_dna_4_7_11_lrd_port_map_field_data,
    .groups = 3,
    .group  = bcm56880_a0_dna_4_7_11_lrd_port_map_group,
    .table_attr = &bcm56880_a0_dna_4_7_11_lrd_portt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
