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
/* Handler: bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmltx_field_demux.h>
#include <bcmdrd/chip/bcm56990_b0_enum.h>
#include <bcmlrd/chip/bcm56990_b0/bcm56990_b0_lrd_xfrm_field_desc.h>


extern const bcmltd_field_desc_t
bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_src_field_desc_s0[];

static const bcmltd_field_desc_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_dst_field_desc[2] = {
    {
        .field_id  = BCMLTD_INTERNAL_FIELD_BASE + 82,
        .field_idx = 0,
        .minbit    = 107,
        .maxbit    = 117,
        .entry_idx = 0,
        .sym       = "MPLS_ENTRY_DOUBLEm.VXLAN_SIP_V6_VNID::O_SIP_LWRf[74:64]",
        .reserved  = 0
    },
    {
        .field_id  = VXLAN_SIP_V6_VNIDv_O_SIP_UPRf,
        .field_idx = 0,
        .minbit    = 123,
        .maxbit    = 175,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const
bcmltd_field_list_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_src_list_s0 = {
    .field_num = 2,
    .field_array = bcm56990_b0_lrd_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_src_field_desc_s0
};

static const bcmltd_field_list_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_dst_field_desc
};

static const uint32_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_src_s0[1] = {
    TNL_L2_VXLAN_DECAP_VFI_ASSIGNMENT_OVID_VNID_SRC_IPV6t_OUTER_SRC_IPV6u_UPPERf,
};

static const uint32_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_dst_d0[2] = {
    BCMLTD_INTERNAL_FIELD_BASE + 82,
    VXLAN_SIP_V6_VNIDv_O_SIP_UPRf,
};

static const bcmltd_generic_arg_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_comp_data = {
    .sid       = TNL_L2_VXLAN_DECAP_VFI_ASSIGNMENT_OVID_VNID_SRC_IPV6t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_fwd_arg_s0_d0 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_src_s0,
    .field_list  = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_src_list_s0,
    .rfields     = 2,
    .rfield      = bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_dst_d0,
    .rfield_list = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_dst_list_d0,
    .comp_data   = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_comp_data
};

static const bcmltd_transform_arg_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_rev_arg_s0_d0 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 2,
    .field       = bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_dst_d0,
    .field_list  = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_transform_src_s0,
    .rfield_list = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_src_list_s0,
    .comp_data   = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_comp_data
};

const bcmltd_xfrm_handler_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_fwd_s0_d0 = {
    .transform     = bcmltx_field_demux_transform,
    .arg           = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_fwd_arg_s0_d0
};

const bcmltd_xfrm_handler_t
bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_rev_s0_d0 = {
    .transform     = bcmltx_field_mux_transform,
    .arg           = &bcm56990_b0_lta_bcmltx_field_demux_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6t_outer_src_ipv6u_upperf_0_xfrm_handler_rev_arg_s0_d0
};


