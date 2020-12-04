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
/* Handler: bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmsec/bcmltx_array_fld_sel.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_xfrm_field_desc.h>

static const uint32_t
bcm56780_a0_lta_bcmltx_array_fld_sel_transform_arg0[1] = {
    0,
};

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_src_field_desc_s0[];

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_src_field_desc_s1[];

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_field_desc_d1[];

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s0 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lrd_bcmltx_array_fld_sel_src_field_desc_s0
};

static const
bcmltd_field_list_t
bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s1 = {
    .field_num = 1,
    .field_array = bcm56780_a0_lrd_bcmltx_array_fld_sel_src_field_desc_s1
};

static const bcmltd_field_list_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d0 = {
    .field_num = 4,
    .field_array = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d1 = {
    .field_num = 4,
    .field_array = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_field_desc_d1
};

static const uint32_t
bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s0[1] = {
    SEC_DECRYPT_PROTOCOLt_TPIDf,
};

static const uint32_t
bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s1[1] = {
    SEC_DECRYPT_PROTOCOLt_MPLS_ETHERTYPEf,
};

static const uint32_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d0[4] = {
    TPID0f,
    TPID1f,
    TPID2f,
    TPID3f,
};

static const uint32_t
bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d1[4] = {
    ETYPE0f,
    ETYPE1f,
    ETYPE2f,
    ETYPE3f,
};

static const bcmltd_generic_arg_t
bcm56780_a0_lta_bcmltx_array_fld_sel_comp_data = {
    .sid       = SEC_DECRYPT_PROTOCOLt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_arg_s0_d0_x0 = {
    .values      = 1,
    .value       = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_arg0,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s0,
    .field_list  = &bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s0,
    .rfields     = 4,
    .rfield      = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d0,
    .rfield_list = &bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d0,
    .comp_data   = &bcm56780_a0_lta_bcmltx_array_fld_sel_comp_data
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_arg_s0_d0_x0 = {
    .values      = 1,
    .value       = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_arg0,
    .tables      = 0,
    .table       = NULL,
    .fields      = 4,
    .field       = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d0,
    .field_list  = &bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s0,
    .rfield_list = &bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s0,
    .comp_data   = &bcm56780_a0_lta_bcmltx_array_fld_sel_comp_data
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_arg_s1_d1 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s1,
    .field_list  = &bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s1,
    .rfields     = 4,
    .rfield      = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d1,
    .rfield_list = &bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d1,
    .comp_data   = &bcm56780_a0_lta_bcmltx_array_fld_sel_comp_data
};

static const bcmltd_transform_arg_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_arg_s1_d1 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 4,
    .field       = bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_transform_dst_d1,
    .field_list  = &bcm56780_a0_lrd_bcmltx_array_fld_sel_sec_decrypt_protocol_dst_list_d1,
    .rfields     = 1,
    .rfield      = bcm56780_a0_lta_bcmltx_array_fld_sel_transform_src_s1,
    .rfield_list = &bcm56780_a0_lta_bcmltx_array_fld_sel_src_list_s1,
    .comp_data   = &bcm56780_a0_lta_bcmltx_array_fld_sel_comp_data
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_s0_d0_x0 = {
    .transform     = bcmltx_array_fld_sel_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_arg_s0_d0_x0
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_s1_d1 = {
    .transform     = bcmltx_array_fld_sel_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_fwd_arg_s1_d1
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_s0_d0_x0 = {
    .transform     = bcmltx_array_fld_sel_rev_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_arg_s0_d0_x0
};

const bcmltd_xfrm_handler_t
bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_s1_d1 = {
    .transform     = bcmltx_array_fld_sel_rev_transform,
    .arg           = &bcm56780_a0_lta_bcmltx_array_fld_sel_xfrm_handler_rev_arg_s1_d1
};


