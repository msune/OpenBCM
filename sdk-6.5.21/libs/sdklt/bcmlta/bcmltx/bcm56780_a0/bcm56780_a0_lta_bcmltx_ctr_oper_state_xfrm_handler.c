/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from Logical Table mapping files.
 *
 * Tool: $SDK/INTERNAL/fltg/bin/fltg
 *
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
/* Logical Table Adaptor for component bcmltx */
/* Handler: bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmctr/bcmltx_ctr_oper_state.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_xfrm_field_desc.h>

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_arg0[1] = {
    1,
};

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s0[];

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s1[];

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s2[];

static const bcmltd_field_desc_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k0[1] = {
    {
        .field_id  = CTR_ING_PFCt_PORT_IDf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k1[1] = {
    {
        .field_id  = CTR_MACt_PORT_IDf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k2[1] = {
    {
        .field_id  = CTR_MAC_ERRt_PORT_IDf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
};


static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s0 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s0
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s1 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s1
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s2 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lrd_bcmltx_ctr_oper_state_src_field_desc_s2
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k0 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k0
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k1 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k1
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k2 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lta_bcmltx_ctr_oper_state_src_field_desc_k2
};

static const bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_dst_list_d0 = {
    .field_num = 0,
    .field_array = NULL
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s0[1] = {
    CTR_ING_PFCt_OPERATIONAL_STATEf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s1[1] = {
    CTR_MACt_OPERATIONAL_STATEf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s2[1] = {
    CTR_MAC_ERRt_OPERATIONAL_STATEf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k0[1] = {
    CTR_ING_PFCt_PORT_IDf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k1[1] = {
    CTR_MACt_PORT_IDf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k2[1] = {
    CTR_MAC_ERRt_PORT_IDf,
};


static const bcmltd_generic_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data = {
    .sid       = CTR_ING_PFCt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data1 = {
    .sid       = CTR_MACt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data2 = {
    .sid       = CTR_MAC_ERRt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s0_k0_d0_x0 = {
    .values      = 1,
    .value       = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_arg0,
    .tables      = 0,
    .table       = NULL,
    .fields      = 0,
    .field       = NULL,
    .field_list  = &bcm56780_a0_lta_bcmltx_ctr_oper_state_dst_list_d0,
    .kfields     = 1,
    .kfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k0,
    .kfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k0,
    .rfields     = 1,
    .rfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s0,
    .rfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s0,
    .comp_data   = &bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s1_k1_d0_x0 = {
    .values      = 1,
    .value       = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_arg0,
    .tables      = 0,
    .table       = NULL,
    .fields      = 0,
    .field       = NULL,
    .field_list  = &bcm56780_a0_lta_bcmltx_ctr_oper_state_dst_list_d0,
    .kfields     = 1,
    .kfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k1,
    .kfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k1,
    .rfields     = 1,
    .rfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s1,
    .rfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s1,
    .comp_data   = &bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data1
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s2_k2_d0_x0 = {
    .values      = 1,
    .value       = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_arg0,
    .tables      = 0,
    .table       = NULL,
    .fields      = 0,
    .field       = NULL,
    .field_list  = &bcm56780_a0_lta_bcmltx_ctr_oper_state_dst_list_d0,
    .kfields     = 1,
    .kfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_k2,
    .kfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_k2,
    .rfields     = 1,
    .rfield      = bcm56780_a0_lta_bcmltx_ctr_oper_state_transform_src_s2,
    .rfield_list = &bcm56780_a0_lta_bcmltx_ctr_oper_state_src_list_s2,
    .comp_data   = &bcm56780_a0_lta_bcmltx_ctr_oper_state_comp_data2
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_s0_k0_d0_x0 = {
    .ext_transform = bcmltx_ctr_oper_state_rev_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s0_k0_d0_x0
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_s1_k1_d0_x0 = {
    .ext_transform = bcmltx_ctr_oper_state_rev_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s1_k1_d0_x0
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_s2_k2_d0_x0 = {
    .ext_transform = bcmltx_ctr_oper_state_rev_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_ctr_oper_state_xfrm_handler_rev_arg_s2_k2_d0_x0
};


