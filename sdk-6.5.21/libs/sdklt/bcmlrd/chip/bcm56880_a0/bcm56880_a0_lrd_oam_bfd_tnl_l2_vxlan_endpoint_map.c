/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/oam/bcm56880_a0/bcm56880_a0_OAM_BFD_TNL_L2_VXLAN_ENDPOINT.map.ltl for
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
/* OAM_BFD_TNL_L2_VXLAN_ENDPOINT field init */
static const bcmlrd_field_data_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_field_data_mmd[] = {
    { /* 0 OAM_BFD_TNL_L2_VXLAN_ENDPOINT_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x7ff,
      .depth = 0,
      .width = 11,
      .edata = NULL,
    },
    { /* 1 ROLE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x1,
      .depth = 0,
      .width = 1,
      .edata = BCMLTD_COMMON_OAM_BFD_ENDPOINT_SESSION_INIT_ROLE_T_DATA,
    },
    { /* 2 IP_ENCAP_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x3,
      .depth = 0,
      .width = 2,
      .edata = BCMLTD_COMMON_OAM_BFD_TNL_L2_VXLAN_ENDPOINT_IP_ENCAP_TYPE_T_DATA,
    },
    { /* 3 MODE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x1,
      .depth = 0,
      .width = 1,
      .edata = BCMLTD_COMMON_OAM_BFD_ENDPOINT_MODE_T_DATA,
    },
    { /* 4 LOCAL_DISCRIMINATOR */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 5 REMOTE_DISCRIMINATOR */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 6 DIAG_CODE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x9,
      .depth = 0,
      .width = 4,
      .edata = BCMLTD_COMMON_OAM_BFD_DIAG_CODE_T_DATA,
    },
    { /* 7 MIN_TX_INTERVAL_USECS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0xce4,
      .def = &bcm56880_a0_lrd_ifd_u32_0xf4240,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 8 MIN_RX_INTERVAL_USECS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0xf4240,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 9 DETECT_MULTIPLIER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x1,
      .def = &bcm56880_a0_lrd_ifd_u8_0x3,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 10 AUTH_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x3,
      .depth = 0,
      .width = 2,
      .edata = BCMLTD_COMMON_OAM_BFD_AUTH_TYPE_T_DATA,
    },
    { /* 11 OAM_BFD_AUTH_SIMPLE_PASSWORD_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 12 OAM_BFD_AUTH_SHA1_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 13 INITIAL_SHA1_SEQ_NUM */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 14 SHA1_SEQ_NUM_INCREMENT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 15 POLL_SEQUENCE */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_is_true_0x0,
      .def = &bcm56880_a0_lrd_ifd_is_true_0x0,
      .max = &bcm56880_a0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 16 RX_LOOKUP_VLAN_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 17 PORT_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0x9f,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 18 COS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 19 UNDERLAY_DST_MAC */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffff,
      .depth = 0,
      .width = 48,
      .edata = NULL,
    },
    { /* 20 UNDERLAY_SRC_MAC */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffff,
      .depth = 0,
      .width = 48,
      .edata = NULL,
    },
    { /* 21 UNDERLAY_TAG_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x1,
      .max = &bcm56880_a0_lrd_ifd_u32_0x2,
      .depth = 0,
      .width = 2,
      .edata = BCM56880_A0_LRD_VLAN_TAG_TYPE_T_DATA,
    },
    { /* 22 UNDERLAY_VLAN_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 23 UNDERLAY_VLAN_PRI */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 24 UNDERLAY_TPID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 25 UNDERLAY_INNER_VLAN_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 26 UNDERLAY_INNER_VLAN_PRI */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 27 UNDERLAY_INNER_TPID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 28 UNDERLAY_SRC_IPV6_UPPER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 29 UNDERLAY_SRC_IPV6_LOWER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 30 UNDERLAY_DST_IPV6_UPPER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 31 UNDERLAY_DST_IPV6_LOWER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 32 UNDERLAY_TRAFFIC_CLASS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 33 UNDERLAY_HOP_LIMIT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 34 UNDERLAY_SRC_IPV4 */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 35 UNDERLAY_DST_IPV4 */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 36 UNDERLAY_TOS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 37 UNDERLAY_TTL */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 38 UNDERLAY_UDP_SRC_PORT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 39 UNDERLAY_UDP_DST_PORT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 40 VNID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffff,
      .depth = 0,
      .width = 24,
      .edata = NULL,
    },
    { /* 41 OVERLAY_DST_MAC */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffff,
      .depth = 0,
      .width = 48,
      .edata = NULL,
    },
    { /* 42 OVERLAY_SRC_MAC */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffff,
      .depth = 0,
      .width = 48,
      .edata = NULL,
    },
    { /* 43 OVERLAY_TAG_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x1,
      .max = &bcm56880_a0_lrd_ifd_u32_0x2,
      .depth = 0,
      .width = 2,
      .edata = BCM56880_A0_LRD_VLAN_TAG_TYPE_T_DATA,
    },
    { /* 44 OVERLAY_VLAN_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 45 OVERLAY_VLAN_PRI */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 46 OVERLAY_TPID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 47 OVERLAY_INNER_VLAN_ID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 48 OVERLAY_INNER_VLAN_PRI */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0x7,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 49 OVERLAY_INNER_TPID */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0x0,
      .def = &bcm56880_a0_lrd_ifd_u16_0x0,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 50 OVERLAY_SRC_IPV6_UPPER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 51 OVERLAY_SRC_IPV6_LOWER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 52 OVERLAY_DST_IPV6_UPPER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 53 OVERLAY_DST_IPV6_LOWER */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u64_0x0,
      .def = &bcm56880_a0_lrd_ifd_u64_0x0,
      .max = &bcm56880_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 54 OVERLAY_TRAFFIC_CLASS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 55 OVERLAY_SRC_IPV4 */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 56 OVERLAY_DST_IPV4 */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 57 OVERLAY_TOS */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 58 OVERLAY_UDP_SRC_PORT */
      .flags = 0,
      .min = &bcm56880_a0_lrd_ifd_u16_0xc000,
      .def = &bcm56880_a0_lrd_ifd_u16_0xc000,
      .max = &bcm56880_a0_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 59 TX_MODE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x2,
      .depth = 0,
      .width = 2,
      .edata = BCMLTD_COMMON_OAM_BFD_ENDPOINT_TX_MODE_T_DATA,
    },
    { /* 60 OPERATIONAL_STATE */
      .flags = BCMLRD_FIELD_F_READ_ONLY | BCMLTD_FIELD_F_ENUM,
      .min = &bcm56880_a0_lrd_ifd_u32_0x0,
      .def = &bcm56880_a0_lrd_ifd_u32_0x0,
      .max = &bcm56880_a0_lrd_ifd_u32_0x3,
      .depth = 0,
      .width = 2,
      .edata = BCMLTD_COMMON_OAM_BFD_ENDPOINT_STATE_T_DATA,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_field_data = {
    .fields = 61,
    .field = bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpointt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 2048,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = TRUE,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpointt_attr_group = {
    .attributes = 2,
    .attr = bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpointt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56880_a0_lrd_bcmimm_oam_bfd_tnl_l2_vxlan_endpoint_entry[] = {
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
            /* handler: bcm56880_a0_lta_bcmimm_oam_bfd_tnl_l2_vxlan_endpoint_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56880_A0_LTA_BCMIMM_OAM_BFD_TNL_L2_VXLAN_ENDPOINT_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_entry_t
bcm56880_a0_lrd_bcmltx_oam_bfd_tnl_l2_vxlan_endpoint_validate_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_VALUE_FIELD_VALIDATION,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            /* handler: bcm56880_a0_lta_bcmltx_oam_bfd_tnl_l2_vxlan_endpoint_std_val_fv_handler */
            .handler_id = BCMLTD_VALIDATE_BCM56880_A0_LTA_BCMLTX_OAM_BFD_TNL_L2_VXLAN_ENDPOINT_STD_VAL_FV_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56880_a0_lrd_bcmimm_oam_bfd_tnl_l2_vxlan_endpoint_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_VALIDATION,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56880_a0_lrd_bcmltx_oam_bfd_tnl_l2_vxlan_endpoint_validate_entry
    },
};
const bcmlrd_map_t bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map = {
    .src_id = OAM_BFD_TNL_L2_VXLAN_ENDPOINTt,
    .field_data = &bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_field_data,
    .groups = 2,
    .group  = bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpoint_map_group,
    .table_attr = &bcm56880_a0_lrd_oam_bfd_tnl_l2_vxlan_endpointt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
