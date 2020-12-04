/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/fp/bcm56990_b0/bcm56990_b0_FP_EM_PRESEL_TEMPLATE_PARTITION_INFO.map.ltl for
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
/* FP_EM_PRESEL_TEMPLATE_PARTITION_INFO field init */
static const bcmlrd_field_data_t bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_field_data_mmd[] = {
    { /* 0 NUM_QUAL_IP_TYPE_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 1 QUAL_IP_TYPE_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 2 QUAL_IP_TYPE_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 3 QUAL_IP_TYPE_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 4 NUM_QUAL_L4_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 5 QUAL_L4_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 6 QUAL_L4_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 7 QUAL_L4_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 8 NUM_QUAL_TNL_TYPE_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 9 QUAL_TNL_TYPE_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 10 QUAL_TNL_TYPE_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 11 QUAL_TNL_TYPE_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 12 NUM_QUAL_LOOPBACK_TYPE_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 13 QUAL_LOOPBACK_TYPE_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 14 QUAL_LOOPBACK_TYPE_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 15 QUAL_LOOPBACK_TYPE_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 16 NUM_QUAL_MYSTATIONTCAM_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 17 QUAL_MYSTATIONTCAM_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 18 QUAL_MYSTATIONTCAM_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 19 QUAL_MYSTATIONTCAM_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 20 NUM_QUAL_MYSTATIONTCAM_2_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 21 QUAL_MYSTATIONTCAM_2_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 22 QUAL_MYSTATIONTCAM_2_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 23 QUAL_MYSTATIONTCAM_2_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 24 NUM_QUAL_SRC_VP_VALID_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 25 QUAL_SRC_VP_VALID_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 26 QUAL_SRC_VP_VALID_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 27 QUAL_SRC_VP_VALID_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 28 NUM_QUAL_MPLS_BOS_TERMINATED_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 29 QUAL_MPLS_BOS_TERMINATED_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 30 QUAL_MPLS_BOS_TERMINATED_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 31 QUAL_MPLS_BOS_TERMINATED_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 32 NUM_QUAL_MPLSENTRY_FIRSTLOOKUP_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 33 QUAL_MPLSENTRY_FIRSTLOOKUP_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 34 QUAL_MPLSENTRY_FIRSTLOOKUP_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 35 QUAL_MPLSENTRY_FIRSTLOOKUP_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 36 NUM_QUAL_MPLSENTRY_SECONDLOOKUP_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 37 QUAL_MPLSENTRY_SECONDLOOKUP_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 38 QUAL_MPLSENTRY_SECONDLOOKUP_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 39 QUAL_MPLSENTRY_SECONDLOOKUP_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 40 NUM_QUAL_L3_TNL_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 41 QUAL_L3_TNL_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 42 QUAL_L3_TNL_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 43 QUAL_L3_TNL_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 44 NUM_QUAL_DOSATTACK_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 45 QUAL_DOSATTACK_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 46 QUAL_DOSATTACK_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 47 QUAL_DOSATTACK_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 48 NUM_QUAL_L3_DST_LPM_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 49 QUAL_L3_DST_LPM_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 50 QUAL_L3_DST_LPM_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 51 QUAL_L3_DST_LPM_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 52 NUM_QUAL_L3_DST_HOST_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 53 QUAL_L3_DST_HOST_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 54 QUAL_L3_DST_HOST_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 55 QUAL_L3_DST_HOST_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 56 NUM_QUAL_L3_SRC_HOST_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 57 QUAL_L3_SRC_HOST_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 58 QUAL_L3_SRC_HOST_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 59 QUAL_L3_SRC_HOST_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 60 NUM_QUAL_L2CACHE_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 61 QUAL_L2CACHE_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 62 QUAL_L2CACHE_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 63 QUAL_L2CACHE_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 64 NUM_QUAL_L2_DST_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 65 QUAL_L2_DST_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 66 QUAL_L2_DST_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 67 QUAL_L2_DST_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 68 NUM_QUAL_L2_SRC_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 69 QUAL_L2_SRC_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 70 QUAL_L2_SRC_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 71 QUAL_L2_SRC_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 72 NUM_QUAL_L2_SRC_STATIC_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 73 QUAL_L2_SRC_STATIC_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 74 QUAL_L2_SRC_STATIC_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 75 QUAL_L2_SRC_STATIC_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 76 NUM_QUAL_ING_STP_STATE_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 77 QUAL_ING_STP_STATE_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 78 QUAL_ING_STP_STATE_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 79 QUAL_ING_STP_STATE_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 80 NUM_QUAL_FWD_VLAN_VALID_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 81 QUAL_FWD_VLAN_VALID_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 82 QUAL_FWD_VLAN_VALID_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 83 QUAL_FWD_VLAN_VALID_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 84 NUM_QUAL_VXLT_LOOKUP_HIT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 85 QUAL_VXLT_LOOKUP_HIT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 86 QUAL_VXLT_LOOKUP_HIT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 87 QUAL_VXLT_LOOKUP_HIT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 88 NUM_QUAL_FWD_TYPE_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 89 QUAL_FWD_TYPE_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 90 QUAL_FWD_TYPE_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 91 QUAL_FWD_TYPE_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 92 NUM_QUAL_DROP_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 93 QUAL_DROP_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 94 QUAL_DROP_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 95 QUAL_DROP_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
    { /* 96 NUM_QUAL_HIGIG_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 97 QUAL_HIGIG_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 98 QUAL_HIGIG_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 99 QUAL_HIGIG_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 100 NUM_QUAL_MIRROR_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 101 QUAL_MIRROR_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 102 QUAL_MIRROR_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 103 QUAL_MIRROR_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 104 NUM_QUAL_VISIBILITY_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 105 QUAL_VISIBILITY_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 106 QUAL_VISIBILITY_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 107 QUAL_VISIBILITY_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 108 NUM_QUAL_HIGIGLOOKUP_PKT_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 109 QUAL_HIGIGLOOKUP_PKT_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 110 QUAL_HIGIGLOOKUP_PKT_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 111 QUAL_HIGIGLOOKUP_PKT_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 112 NUM_QUAL_MIXED_SRC_CLASS_INFO */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 113 QUAL_MIXED_SRC_CLASS_OFFSET */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 114 QUAL_MIXED_SRC_CLASS_WIDTH */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xffff,
      .depth = 33,
      .width = 16,
      .edata = NULL,
    },
    { /* 115 QUAL_MIXED_SRC_CLASS_ORDER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 33,
      .width = 8,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_field_data = {
    .fields = 116,
    .field = bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_b0_lrd_fp_em_presel_template_partition_infot_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 1,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56990_b0_lrd_fp_em_presel_template_partition_infot_attr_group = {
    .attributes = 2,
    .attr = bcm56990_b0_lrd_fp_em_presel_template_partition_infot_attr_entry,
};

static const bcmlrd_map_entry_t bcm56990_b0_lrd_bcmfp_fp_em_presel_template_partition_info_entry[] = {
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
            /* handler: bcm56990_b0_lta_bcmfp_fp_em_presel_template_partition_info_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56990_B0_LTA_BCMFP_FP_EM_PRESEL_TEMPLATE_PARTITION_INFO_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56990_b0_lrd_bcmfp_fp_em_presel_template_partition_info_entry
    },
};
const bcmlrd_map_t bcm56990_b0_lrd_fp_em_presel_template_partition_info_map = {
    .src_id = FP_EM_PRESEL_TEMPLATE_PARTITION_INFOt,
    .field_data = &bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_field_data,
    .groups = 1,
    .group  = bcm56990_b0_lrd_fp_em_presel_template_partition_info_map_group,
    .table_attr = &bcm56990_b0_lrd_fp_em_presel_template_partition_infot_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE
};
