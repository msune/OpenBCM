/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/tnl/bcm56990_b0/bcm56990_b0_TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EM.map.ltl for
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
/* TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EM field init */
static const bcmlrd_field_data_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_field_data_mmd[] = {
    { /* 0 OVID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 1 OUTER_DST_IPV6_UPPER */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u64_0x0,
      .def = &bcm56990_b0_lrd_ifd_u64_0x0,
      .max = &bcm56990_b0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 2 OUTER_DST_IPV6_LOWER */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u64_0x0,
      .def = &bcm56990_b0_lrd_ifd_u64_0x0,
      .max = &bcm56990_b0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 3 IPV6_PAYLOAD */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 4 IPV4_PAYLOAD */
      .flags = BCMLRD_FIELD_F_UNMAPPED,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .depth = 0,
      .width = 0,
      .edata = NULL,
    },
    { /* 5 USE_TNL_HDR_TTL */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 6 KEEP_PAYLOAD_DSCP */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 7 L3_IIF_ID */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0x1fff,
      .depth = 0,
      .width = 13,
      .edata = NULL,
    },
    { /* 8 CLASS_ID */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xfff,
      .depth = 0,
      .width = 12,
      .edata = NULL,
    },
    { /* 9 BFD */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 10 TNL_DECAP_PORT_PROFILE_ID */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 11 CTR_ING_EFLEX_OBJECT */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x1fff,
      .depth = 0,
      .width = 13,
      .edata = NULL,
    },
    { /* 12 CTR_ING_EFLEX_ACTION */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x1f,
      .depth = 0,
      .width = 5,
      .edata = NULL,
    },
    { /* 13 IGNORE_UDP_CHKSUM */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .def = &bcm56990_b0_lrd_ifd_is_true_0x0,
      .max = &bcm56990_b0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 14 TNL_HDR_FOR_PHB */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56990_b0_lrd_ifd_u32_0x0,
      .def = &bcm56990_b0_lrd_ifd_u32_0x0,
      .max = &bcm56990_b0_lrd_ifd_u32_0x2,
      .depth = 0,
      .width = 2,
      .edata = BCM56990_B0_LRD_VXLAN_TNL_HDR_FOR_PHB_T_DATA,
    },
};
const bcmlrd_map_field_data_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_field_data = {
    .fields = 15,
    .field = bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_SIZE,
        .value = 8192,
    },
};

static const bcmlrd_map_attr_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_attr_group = {
    .attributes = 2,
    .attr = bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_attr_entry,
};


const bcmltd_field_desc_t
bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_src_field_desc_s0[2] = {
    {
        .field_id  = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_OUTER_DST_IPV6u_UPPERf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 25,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_OUTER_DST_IPV6u_UPPERf,
        .field_idx = 0,
        .minbit    = 26,
        .maxbit    = 63,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_dst_field_desc[2] = {
    {
        .field_id  = VXLAN_DIP_V6v_O_DIP_LWRf,
        .field_idx = 0,
        .minbit    = 82,
        .maxbit    = 107,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = VXLAN_DIP_V6v_O_DIP_UPRf,
        .field_idx = 0,
        .minbit    = 123,
        .maxbit    = 160,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmlrd_field_xfrm_desc_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56990_B0_LTA_BCMLTX_FIELD_DEMUX_TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMT_OUTER_DST_IPV6U_UPPERF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_src_field_desc_s0,
    .dst_fields = 2,
    .dst = bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56990_B0_LTA_BCMLTX_FIELD_DEMUX_TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMT_OUTER_DST_IPV6U_UPPERF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_dst_field_desc,
    .dst_fields = 2,
    .dst = bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_src_field_desc_s0,
};


static const bcmlrd_map_entry_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_l3_tunnel_double_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = BASE_VALID_0f,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 2,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 1,
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = BASE_VALID_1f,
            .field_idx = 0,
            .minbit    = 120,
            .maxbit    = 122,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 2,
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = KEY_TYPEf,
            .field_idx = 0,
            .minbit    = 3,
            .maxbit    = 5,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 5,
            }
        },
    },
    { /* 3 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_OVIDf,
            .field_idx = 0,
            .minbit    = 6,
            .maxbit    = 17,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_OVIDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 11,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 4 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_O_DIP_LWRf,
            .field_idx = 0,
            .minbit    = 18,
            .maxbit    = 81,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_OUTER_DST_IPV6u_LOWERf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 63,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 5 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_USE_OUTER_HDR_PHBf,
            .field_idx = 0,
            .minbit    = 206,
            .maxbit    = 207,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_TNL_HDR_FOR_PHBf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 1,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 6 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_USE_OUTER_HDR_TTLf,
            .field_idx = 0,
            .minbit    = 208,
            .maxbit    = 208,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_USE_TNL_HDR_TTLf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 0,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 7 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_DONOT_CHANGE_INNER_HDR_DSCPf,
            .field_idx = 0,
            .minbit    = 209,
            .maxbit    = 209,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_KEEP_PAYLOAD_DSCPf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 0,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 8 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_L3_IIFf,
            .field_idx = 0,
            .minbit    = 210,
            .maxbit    = 222,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_L3_IIF_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 12,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 9 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_TUNNEL_CLASS_IDf,
            .field_idx = 0,
            .minbit    = 223,
            .maxbit    = 234,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_CLASS_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 11,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 10 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_BFD_ENABLEf,
            .field_idx = 0,
            .minbit    = 235,
            .maxbit    = 235,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_BFDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 0,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 11 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_ALLOWED_PORT_BITMAP_PROFILE_PTRf,
            .field_idx = 0,
            .minbit    = 236,
            .maxbit    = 239,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_TNL_DECAP_PORT_PROFILE_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 12 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_FLEX_CTR_OBJECTf,
            .field_idx = 0,
            .minbit    = 186,
            .maxbit    = 198,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_CTR_ING_EFLEX_OBJECTf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 12,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 13 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_FLEX_CTR_ACTIONf,
            .field_idx = 0,
            .minbit    = 199,
            .maxbit    = 203,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_CTR_ING_EFLEX_ACTIONf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 4,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 14 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = VXLAN_DIP_V6v_IGNORE_UDP_CHECKSUMf,
            .field_idx = 0,
            .minbit    = 185,
            .maxbit    = 185,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt_IGNORE_UDP_CHKSUMf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 0,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 15 */
        .entry_type = BCMLRD_MAP_ENTRY_FWD_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 16 */
        .entry_type = BCMLRD_MAP_ENTRY_REV_KEY_FIELD_XFRM_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .xfrm = {
                /* handler: bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_outer_dst_ipv6u_upperf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
};
static const bcmlrd_map_group_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = L3_TUNNEL_DOUBLEm,
        },
        .entries = 17,
        .entry = bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_l3_tunnel_double_map_entry
    },
};
const bcmlrd_map_t bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map = {
    .src_id = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt,
    .field_data = &bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_field_data,
    .groups = 1,
    .group  = bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_map_group,
    .table_attr = &bcm56990_b0_lrd_tnl_l2_vxlan_decap_ovid_dst_ipv6_emt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
