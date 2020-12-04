/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/npl/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_R_VLAN_XLATE_MISS_POLICY.map.ltl for
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
/* R_VLAN_XLATE_MISS_POLICY field init */
static const bcmlrd_field_data_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_field_data_mmd[] = {
    { /* 0 OPAQUE_CTRL_ID */
      .flags = 0,
      .min = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .def = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0x0,
      .max = &bcm56880_a0_dna_4_7_11_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_field_data = {
    .fields = 1,
    .field = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
};

static const bcmlrd_map_attr_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_attr_group = {
    .attributes = 1,
    .attr = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_attr_entry,
};


const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d0[2] = {
    {
        .field_id  = BCMLRD_FIELD_SELECTOR,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 31,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = BCMLRD_FIELD_INDEX,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 4,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d1[2] = {
    {
        .field_id  = BCMLRD_FIELD_SELECTOR,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 31,
        .entry_idx = 1,
        .reserved  = 0,
    },
    {
        .field_id  = BCMLRD_FIELD_INDEX,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 4,
        .entry_idx = 1,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d2[2] = {
    {
        .field_id  = BCMLRD_FIELD_SELECTOR,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 31,
        .entry_idx = 2,
        .reserved  = 0,
    },
    {
        .field_id  = BCMLRD_FIELD_INDEX,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 4,
        .entry_idx = 2,
        .reserved  = 0,
    },
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x4_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_FWD_S0_D0_X4_ID,
    .src_fields = 0,
    .src = NULL,
    .dst_fields = 2,
    .dst = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d0,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x4_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_REV_S0_D0_X4_ID,
    .src_fields = 2,
    .src = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d0,
    .dst_fields = 0,
    .dst = NULL,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d1_x5_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_FWD_S0_D1_X5_ID,
    .src_fields = 0,
    .src = NULL,
    .dst_fields = 2,
    .dst = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d1,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d1_x5_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_REV_S0_D1_X5_ID,
    .src_fields = 2,
    .src = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d1,
    .dst_fields = 0,
    .dst = NULL,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d2_x6_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_FWD_S0_D2_X6_ID,
    .src_fields = 0,
    .src = NULL,
    .dst_fields = 2,
    .dst = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d2,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d2_x6_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_REV_S0_D2_X6_ID,
    .src_fields = 2,
    .src = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d2,
    .dst_fields = 0,
    .dst = NULL,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x7_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_FWD_S0_D0_X7_ID,
    .src_fields = 0,
    .src = NULL,
    .dst_fields = 2,
    .dst = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d0,
};

const bcmlrd_field_xfrm_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x7_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56880_A0_DNA_4_7_11_LTA_BCMLTX_SELECT_TILE_MODE_XFRM_HANDLER_REV_S0_D0_X7_ID,
    .src_fields = 2,
    .src = bcm56880_a0_dna_4_7_11_lrd_bcmltx_select_tile_mode_r_vlan_xlate_miss_policy_dst_field_desc_d0,
    .dst_fields = 0,
    .dst = NULL,
};


static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_ifta40_e2t_00_array_miss_policy_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATAf,
            .field_idx = 0,
            .minbit    = 176,
            .maxbit    = 179,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATAf,
            .field_idx = 0,
            .minbit    = 176,
            .maxbit    = 179,
            .entry_idx = 1,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATAf,
            .field_idx = 0,
            .minbit    = 176,
            .maxbit    = 179,
            .entry_idx = 2,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 3 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x4 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x4_desc,
            },
        },
    },
    { /* 4 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x4 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x4_desc,
            },
        },
    },
    { /* 5 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d1_x5 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d1_x5_desc,
            },
        },
    },
    { /* 6 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d1_x5 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d1_x5_desc,
            },
        },
    },
    { /* 7 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d2_x6 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d2_x6_desc,
            },
        },
    },
    { /* 8 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d2_x6 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d2_x6_desc,
            },
        },
    },
};
static const bcmlrd_map_entry_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_ifta40_e2t_01_array_miss_policy_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATAf,
            .field_idx = 0,
            .minbit    = 176,
            .maxbit    = 179,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x7 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_fwd_s0_d0_x7_desc,
            },
        },
    },
    { /* 2 */
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
                /* handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x7 */
                .desc = &bcm56880_a0_dna_4_7_11_lta_bcmltx_select_tile_mode_xfrm_handler_rev_s0_d0_x7_desc,
            },
        },
    },
};
const bcmlrd_field_selector_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_select[] = {
    { /* Node:0, Type:ROOT, IFTA40_E2T_00_ARRAY_MISS_POLICY.__SELECTOR.ENTRY0 */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = BCMLRD_FIELD_SELECTOR,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:1, Type:Directmap, OPAQUE_CTRL_ID:IFTA40_E2T_00_ARRAY_MISS_POLICY.DATA */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_MAP_ENTRY,
        .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
        .group_index = 0,
        .entry_index = 0,
        .selection_parent = 0,
        .group = 0,
        .selector_id = BCMLRD_FIELD_SELECTOR,
        .selector_value = 31 /* IFTA40_E2T_00_MODE0 */
    },
    { /* Node:2, Type:ROOT, IFTA40_E2T_00_ARRAY_MISS_POLICY.__SELECTOR.ENTRY1 */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = BCMLRD_FIELD_SELECTOR,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:3, Type:Directmap, OPAQUE_CTRL_ID:IFTA40_E2T_00_ARRAY_MISS_POLICY.DATA */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_MAP_ENTRY,
        .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
        .group_index = 0,
        .entry_index = 1,
        .selection_parent = 2,
        .group = 1,
        .selector_id = BCMLRD_FIELD_SELECTOR,
        .selector_value = 31 /* IFTA40_E2T_00_MODE0 */
    },
    { /* Node:4, Type:ROOT, IFTA40_E2T_00_ARRAY_MISS_POLICY.__SELECTOR.ENTRY2 */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = BCMLRD_FIELD_SELECTOR,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:5, Type:Directmap, OPAQUE_CTRL_ID:IFTA40_E2T_00_ARRAY_MISS_POLICY.DATA */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_MAP_ENTRY,
        .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
        .group_index = 0,
        .entry_index = 2,
        .selection_parent = 4,
        .group = 2,
        .selector_id = BCMLRD_FIELD_SELECTOR,
        .selector_value = 32 /* IFTA40_E2T_00_MODE1 */
    },
    { /* Node:6, Type:ROOT, IFTA40_E2T_01_ARRAY_MISS_POLICY.__SELECTOR.ENTRY0 */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_ROOT,
        .field_id = BCMLRD_FIELD_SELECTOR,
        .group_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .entry_index = BCMLRD_INVALID_SELECTOR_INDEX,
        .selection_parent = BCMLRD_INVALID_SELECTOR_INDEX,
        .group = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_id = BCMLRD_INVALID_SELECTOR_INDEX,
        .selector_value = BCMLRD_INVALID_SELECTOR_INDEX
    },
    { /* Node:7, Type:Directmap, OPAQUE_CTRL_ID:IFTA40_E2T_01_ARRAY_MISS_POLICY.DATA */
        .selector_type = BCMLRD_FIELD_SELECTOR_TYPE_MAP_ENTRY,
        .field_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt_OPAQUE_CTRL_IDf,
        .group_index = 1,
        .entry_index = 0,
        .selection_parent = 6,
        .group = 3,
        .selector_id = BCMLRD_FIELD_SELECTOR,
        .selector_value = 33 /* IFTA40_E2T_01_MODE0 */
    },
};

const bcmlrd_field_selector_data_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_select_data = {
    .num_field_selector = 8,
    .field_selector = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_select,
};

static const bcmlrd_map_group_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = IFTA40_E2T_00_ARRAY_MISS_POLICYm,
        },
        .entries = 9,
        .entry = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_ifta40_e2t_00_array_miss_policy_map_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = IFTA40_E2T_01_ARRAY_MISS_POLICYm,
        },
        .entries = 3,
        .entry = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_ifta40_e2t_01_array_miss_policy_map_entry
    },
};
const bcmlrd_map_t bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map = {
    .src_id = BCM56880_A0_DNA_4_7_11_R_VLAN_XLATE_MISS_POLICYt,
    .field_data = &bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_field_data,
    .groups = 2,
    .group  = bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_group,
    .table_attr = &bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policyt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE,
    .sel = &bcm56880_a0_dna_4_7_11_lrd_r_vlan_xlate_miss_policy_map_select_data,
};
