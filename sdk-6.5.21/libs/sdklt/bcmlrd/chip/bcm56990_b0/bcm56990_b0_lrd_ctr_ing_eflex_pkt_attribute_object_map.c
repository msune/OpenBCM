/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/ctr/bcm56990_b0/bcm56990_b0_CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECT.map.ltl for
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
/* CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECT field init */
static const bcmlrd_field_data_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_field_data_mmd[] = {
    { /* 0 PIPE */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0x3,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 1 CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECT_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0x2,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 2 PKT_ATTRIBUTE_OBJECT_INSTANCE_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56990_b0_lrd_ifd_u16_0x0,
      .def = &bcm56990_b0_lrd_ifd_u16_0x0,
      .max = &bcm56990_b0_lrd_ifd_u16_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
    { /* 3 CTR_ING_EFLEX_OBJECT */
      .flags = 0,
      .min = &bcm56990_b0_lrd_ifd_u8_0x0,
      .def = &bcm56990_b0_lrd_ifd_u8_0x0,
      .max = &bcm56990_b0_lrd_ifd_u8_0xff,
      .depth = 0,
      .width = 8,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_field_data = {
    .fields = 4,
    .field = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MAX_INDEX,
        .value = 3,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MIN_INDEX,
        .value = 0,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = TRUE,
    },
    { /* 3 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 255,
    },
    { /* 4 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 0,
    },
};

static const bcmlrd_map_attr_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_attr_group = {
    .attributes = 5,
    .attr = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_attr_entry,
};


const bcmltd_field_desc_t
bcm56990_b0_lrd_bcmltx_copy_field_src_field_desc_s4[1] = {
    {
        .field_id  = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECT_IDf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
};

const bcmltd_field_desc_t
bcm56990_b0_lrd_bcmltx_copy_field_ctr_ing_eflex_pkt_attribute_object_dst_field_desc_d1[1] = {
    {
        .field_id  = BCMLRD_FIELD_TABLE_SEL,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 7,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const uint32_t
bcm56990_b0_lrd_copy_field_transform_tbl_t2[3] = {
    ING_FLEX_CTR_OFFSET_TABLE_0_INST0m,
    ING_FLEX_CTR_OFFSET_TABLE_1_INST0m,
    ING_FLEX_CTR_OFFSET_TABLE_2_INST0m,
};

const uint32_t
bcm56990_b0_lrd_copy_field_transform_tbl_t3[3] = {
    ING_FLEX_CTR_OFFSET_TABLE_0_INST1m,
    ING_FLEX_CTR_OFFSET_TABLE_1_INST1m,
    ING_FLEX_CTR_OFFSET_TABLE_2_INST1m,
};

const bcmlrd_field_xfrm_desc_t
bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t2_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56990_B0_LTA_BCMLTX_COPY_FIELD_XFRM_HANDLER_FWD_S4_D1_T2_ID,
    .src_fields = 1,
    .src = bcm56990_b0_lrd_bcmltx_copy_field_src_field_desc_s4,
    .dst_fields = 1,
    .dst = bcm56990_b0_lrd_bcmltx_copy_field_ctr_ing_eflex_pkt_attribute_object_dst_field_desc_d1,
    .tables = 3,
    .tbl = bcm56990_b0_lrd_copy_field_transform_tbl_t2,
};

const bcmlrd_field_xfrm_desc_t
bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_rev_s4_d1_t2_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56990_B0_LTA_BCMLTX_COPY_FIELD_XFRM_HANDLER_REV_S4_D1_T2_ID,
    .src_fields = 1,
    .src = bcm56990_b0_lrd_bcmltx_copy_field_ctr_ing_eflex_pkt_attribute_object_dst_field_desc_d1,
    .dst_fields = 1,
    .dst = bcm56990_b0_lrd_bcmltx_copy_field_src_field_desc_s4,
    .tables = 3,
    .tbl = bcm56990_b0_lrd_copy_field_transform_tbl_t2,
};

const bcmlrd_field_xfrm_desc_t
bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t3_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56990_B0_LTA_BCMLTX_COPY_FIELD_XFRM_HANDLER_FWD_S4_D1_T3_ID,
    .src_fields = 1,
    .src = bcm56990_b0_lrd_bcmltx_copy_field_src_field_desc_s4,
    .dst_fields = 1,
    .dst = bcm56990_b0_lrd_bcmltx_copy_field_ctr_ing_eflex_pkt_attribute_object_dst_field_desc_d1,
    .tables = 3,
    .tbl = bcm56990_b0_lrd_copy_field_transform_tbl_t3,
};


static const bcmlrd_map_entry_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_ing_flex_ctr_offset_table_0_inst0_map_entry[] = {
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
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_PKT_ATTRIBUTE_OBJECT_INSTANCE_IDf,
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
            .field_id  = OFFSETf,
            .field_idx = 0,
            .minbit    = 1,
            .maxbit    = 8,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_CTR_ING_EFLEX_OBJECTf,
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
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INSTANCE,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 1,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_PIPEf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 1,
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
                /* handler: bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t2 */
                .desc = &bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t2_desc,
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
                /* handler: bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_rev_s4_d1_t2 */
                .desc = &bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_rev_s4_d1_t2_desc,
            },
        },
    },
};
static const bcmlrd_map_entry_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_ing_flex_ctr_offset_table_0_inst1_map_entry[] = {
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
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_PKT_ATTRIBUTE_OBJECT_INSTANCE_IDf,
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
            .field_id  = OFFSETf,
            .field_idx = 0,
            .minbit    = 1,
            .maxbit    = 8,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_CTR_ING_EFLEX_OBJECTf,
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
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INSTANCE,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 1,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_PIPEf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 1,
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
                /* handler: bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t3 */
                .desc = &bcm56990_b0_lta_bcmltx_copy_field_xfrm_handler_fwd_s4_d1_t3_desc,
            },
        },
    },
};
static const bcmlrd_map_entry_t
bcm56990_b0_lrd_bcmltx_ctr_ing_eflex_pkt_attribute_object_validate_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_KEY_FIELD_VALIDATION,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            /* handler: bcm56990_b0_lta_bcmltx_ctr_ing_eflex_pkt_attribute_object_pipe_fv_handler_v0 */
            .handler_id = BCMLTD_VALIDATE_BCM56990_B0_LTA_BCMLTX_CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECT_PIPE_FV_HANDLER_V0_ID
        }
    },
};
/* Map conditions */
static const uint32_t
bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_edit[] = {
    2, /* Number of groups. */
    0, /* Group ID. */
    1, /* Number of entries. */
    2, /* Entry ID. */
    1, /* Group ID. */
    1, /* Number of entries. */
    2, /* Entry ID. */
    0, /* Number of multi-entry transforms. */
};

static const bcmlrd_condition_t
bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_condition[] = {
    {
        .op    = BCMLRD_CONDITION_AND,
        .table = CTR_EFLEX_CONFIGt,
        .field = CTR_EFLEX_CONFIGt_CTR_ING_EFLEX_OPERMODE_PIPEUNIQUEf,
        .value = 1
    },
};

static const bcmlrd_cond_expr_t
bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_expr[] = {
    {
        .num_cond = 1,
        .cond     = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_condition + 0,
    },
};

static const bcmlrd_cond_field_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_field[] = {
    {
        .field = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt_PIPEf,
        .expr  = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_expr + 0,
        .edit  = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_edit + 0,
    },
};
static const bcmlrd_cond_data_t
bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond = {
    .num_field_cond = 1,
    .field_cond = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond_field
};
static const bcmlrd_map_group_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = ING_FLEX_CTR_OFFSET_TABLE_0_INST0m,
        },
        .entries = 5,
        .entry = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_ing_flex_ctr_offset_table_0_inst0_map_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = ING_FLEX_CTR_OFFSET_TABLE_0_INST1m,
        },
        .entries = 4,
        .entry = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_ing_flex_ctr_offset_table_0_inst1_map_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_VALIDATION,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56990_b0_lrd_bcmltx_ctr_ing_eflex_pkt_attribute_object_validate_entry
    },
};
const bcmlrd_map_t bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map = {
    .src_id = CTR_ING_EFLEX_PKT_ATTRIBUTE_OBJECTt,
    .field_data = &bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_field_data,
    .groups = 3,
    .group  = bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_group,
    .table_attr = &bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_objectt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE,
    .cond = &bcm56990_b0_lrd_ctr_ing_eflex_pkt_attribute_object_map_cond,
};
