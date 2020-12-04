/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/sec/bcm56780_a0/bcm56780_a0_SEC_DECRYPT_IPSEC_SA_POLICY.map.ltl for
 *      bcm56780_a0
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
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_field_data.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "bcm56780_a0_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* SEC_DECRYPT_IPSEC_SA_POLICY field init */
static const bcmlrd_field_data_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_field_data_mmd[] = {
    { /* 0 SEC_BLOCK_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0x5,
      .depth = 0,
      .width = 3,
      .edata = NULL,
    },
    { /* 1 SEC_DECRYPT_IPSEC_SA_POLICY_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0x7ff,
      .depth = 0,
      .width = 11,
      .edata = NULL,
    },
    { /* 2 STATE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0x1,
      .depth = 0,
      .width = 1,
      .edata = BCMLTD_COMMON_SA_STATE_CONTROL_T_DATA,
    },
    { /* 3 INITIAL_PKT_NUMBER */
      .flags = 0,
      .min = &bcm56780_a0_lrd_ifd_u64_0x0,
      .def = &bcm56780_a0_lrd_ifd_u64_0x0,
      .max = &bcm56780_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 4 XPN_SALT */
      .flags = 0,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0xff,
      .depth = 12,
      .width = 8,
      .edata = NULL,
    },
    { /* 5 KEY */
      .flags = 0,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0xff,
      .depth = 32,
      .width = 8,
      .edata = NULL,
    },
    { /* 6 NEXT_PKT_NUMBER */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56780_a0_lrd_ifd_u64_0x0,
      .def = &bcm56780_a0_lrd_ifd_u64_0x0,
      .max = &bcm56780_a0_lrd_ifd_u64_0xffffffffffffffff,
      .depth = 0,
      .width = 64,
      .edata = NULL,
    },
    { /* 7 IN_USE */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56780_a0_lrd_ifd_is_true_0x0,
      .def = &bcm56780_a0_lrd_ifd_is_true_0x0,
      .max = &bcm56780_a0_lrd_ifd_is_true_0x1,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 8 IN_USE_START_TIME */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 9 IN_USE_STOP_TIME */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56780_a0_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_field_data = {
    .fields = 10,
    .field = bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policyt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_ENTRY_LIMIT,
        .value = 12288,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = true,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policyt_attr_group = {
    .attributes = 2,
    .attr = bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policyt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56780_a0_lrd_bcmimm_sec_decrypt_ipsec_sa_policy_entry[] = {
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
            /* handler: bcm56780_a0_lta_bcmimm_sec_decrypt_ipsec_sa_policy_cth_handler */
            .handler_id = BCMLTD_TABLE_BCM56780_A0_LTA_BCMIMM_SEC_DECRYPT_IPSEC_SA_POLICY_CTH_HANDLER_ID
        }
    },
};
static const bcmlrd_map_entry_t
bcm56780_a0_lrd_bcmltx_sec_decrypt_ipsec_sa_policy_validate_entry[] = {
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
            /* handler: bcm56780_a0_lta_bcmltx_sec_decrypt_ipsec_sa_policy_std_val_fv_handler */
            .handler_id = BCMLTD_VALIDATE_BCM56780_A0_LTA_BCMLTX_SEC_DECRYPT_IPSEC_SA_POLICY_STD_VAL_FV_HANDLER_ID
        }
    },
};
static const bcmlrd_map_entry_t
bcm56780_a0_lrd_bcmltx_sec_decrypt_ipsec_sa_policy_table_entry_limit_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_TABLE_ENTRY_LIMIT_HANDLER,
        .desc = {
            .field_id  = 0,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            /* handler: bcm56780_a0_lta_bcmltx_sec_decrypt_ipsec_sa_policy_sec_valid_table_entry_limit_handler */
            .handler_id = BCMLTD_TABLE_ENTRY_LIMIT_BCM56780_A0_LTA_BCMLTX_SEC_DECRYPT_IPSEC_SA_POLICY_SEC_VALID_TABLE_ENTRY_LIMIT_HANDLER_ID
        }
    },
};
static const bcmlrd_map_group_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_CUSTOM,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56780_a0_lrd_bcmimm_sec_decrypt_ipsec_sa_policy_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_VALIDATION,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56780_a0_lrd_bcmltx_sec_decrypt_ipsec_sa_policy_validate_entry
    },
    {
        .dest = {
            .kind = BCMLRD_MAP_TABLE_ENTRY_LIMIT,
            .id = 0,
        },
        .entries = 1,
        .entry = bcm56780_a0_lrd_bcmltx_sec_decrypt_ipsec_sa_policy_table_entry_limit_entry
    },
};
const bcmlrd_map_t bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map = {
    .src_id = SEC_DECRYPT_IPSEC_SA_POLICYt,
    .field_data = &bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_field_data,
    .groups = 3,
    .group  = bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policy_map_group,
    .table_attr = &bcm56780_a0_lrd_sec_decrypt_ipsec_sa_policyt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
