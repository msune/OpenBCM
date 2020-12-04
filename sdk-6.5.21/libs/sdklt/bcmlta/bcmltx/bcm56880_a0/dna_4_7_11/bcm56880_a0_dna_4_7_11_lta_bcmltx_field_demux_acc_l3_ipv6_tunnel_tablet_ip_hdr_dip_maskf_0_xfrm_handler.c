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
/* Handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmltx_field_demux_acc.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_xfrm_field_desc.h>


extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_src_field_desc_s0[];

static const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_dst_field_desc[1] = {
    {
        .field_id  = BCMLTD_INTERNAL_FIELD_BASE + 132,
        .field_idx = 0,
        .minbit    = 190,
        .maxbit    = 241,
        .entry_idx = 0,
        .sym       = "MEMDB_TCAM_IFTA40_MEM0_2_ONLYm.MASKf.ENTRY0[79:28]",
        .reserved  = 0
    },
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_src_list_s0 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_src_field_desc_s0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_dst_list_d0 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_dst_field_desc
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_src_s0[1] = {
    BCM56880_A0_DNA_4_7_11_L3_IPV6_TUNNEL_TABLEt_IP_HDR_DIP_MASKf,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_dst_d0[1] = {
    BCMLTD_INTERNAL_FIELD_BASE + 132,
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_comp_data = {
    .sid       = BCM56880_A0_DNA_4_7_11_L3_IPV6_TUNNEL_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};


static uint64_t bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_val[2];
static uint32_t bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_count;
extern const bcmltd_rev_subfield_transform_info_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_info;
const bcmltd_rev_subfield_transform_info_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_info = {
    .magic = BCMLTD_REV_SUBFIELD_TRANSFORM_INFO_MAGIC,
    .num = 4,
    .count = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_count,
    .values = 2,
    .value = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_val
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_comp_data1 = {
    .sid       = BCM56880_A0_DNA_4_7_11_L3_IPV6_TUNNEL_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = (void *)&bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_info
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_fwd_arg_s0_d0 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_src_s0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_src_list_s0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_comp_data
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_rev_arg_s0_d0_c1 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_transform_src_s0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_src_list_s0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_comp_data1
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_fwd_s0_d0 = {
    .transform     = bcmltx_field_demux_acc_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_fwd_arg_s0_d0
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_rev_s0_d0_c1 = {
    .transform     = bcmltx_field_mux_acc_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_acc_l3_ipv6_tunnel_tablet_ip_hdr_dip_maskf_0_xfrm_handler_rev_arg_s0_d0_c1
};


