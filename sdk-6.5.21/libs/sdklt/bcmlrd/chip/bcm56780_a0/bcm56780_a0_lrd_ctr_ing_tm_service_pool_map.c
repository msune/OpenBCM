/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/ctr/bcm56780_a0/bcm56780_a0_CTR_ING_TM_SERVICE_POOL.map.ltl for
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
/* CTR_ING_TM_SERVICE_POOL field init */
static const bcmlrd_field_data_t bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_field_data_mmd[] = {
    { /* 0 BUFFER_POOL */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0x0,
      .depth = 0,
      .width = 1,
      .edata = NULL,
    },
    { /* 1 TM_ING_SERVICE_POOL_ID */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_lrd_ifd_u8_0x3,
      .depth = 0,
      .width = 2,
      .edata = NULL,
    },
    { /* 2 TOTAL_USAGE_CELLS */
      .flags = BCMLRD_FIELD_F_READ_ONLY,
      .min = &bcm56780_a0_lrd_ifd_u64_0x0,
      .def = &bcm56780_a0_lrd_ifd_u64_0x0,
      .max = &bcm56780_a0_lrd_ifd_u64_0x7ffff,
      .depth = 0,
      .width = 19,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_field_data = {
    .fields = 3,
    .field = bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_lrd_ctr_ing_tm_service_poolt_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MAX_INDEX,
        .value = 0,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INSTANCE_MIN_INDEX,
        .value = 0,
    },
    { /* 2 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = true,
    },
    { /* 3 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_PREPOPULATE,
        .value = true,
    },
    { /* 4 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MAX_INDEX,
        .value = 3,
    },
    { /* 5 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_MIN_INDEX,
        .value = 0,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_lrd_ctr_ing_tm_service_poolt_attr_group = {
    .attributes = 6,
    .attr = bcm56780_a0_lrd_ctr_ing_tm_service_poolt_attr_entry,
};

static const bcmlrd_map_entry_t bcm56780_a0_lrd_ctr_ing_tm_service_poolt_mmu_thdi_pool_shared_count_sp_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INDEX,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 1,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_TM_SERVICE_POOLt_TM_ING_SERVICE_POOL_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 1,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_INSTANCE,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_TM_SERVICE_POOLt_BUFFER_POOLf,
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
            .field_id  = TOTAL_BUFFER_COUNTf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 18,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = CTR_ING_TM_SERVICE_POOLt_TOTAL_USAGE_CELLSf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 18,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
};
static const bcmlrd_map_group_t bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = MMU_THDI_POOL_SHARED_COUNT_SPr,
        },
        .entries = 3,
        .entry = bcm56780_a0_lrd_ctr_ing_tm_service_poolt_mmu_thdi_pool_shared_count_sp_map_entry
    },
};
const bcmlrd_map_t bcm56780_a0_lrd_ctr_ing_tm_service_pool_map = {
    .src_id = CTR_ING_TM_SERVICE_POOLt,
    .field_data = &bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_field_data,
    .groups = 1,
    .group  = bcm56780_a0_lrd_ctr_ing_tm_service_pool_map_group,
    .table_attr = &bcm56780_a0_lrd_ctr_ing_tm_service_poolt_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE
};
