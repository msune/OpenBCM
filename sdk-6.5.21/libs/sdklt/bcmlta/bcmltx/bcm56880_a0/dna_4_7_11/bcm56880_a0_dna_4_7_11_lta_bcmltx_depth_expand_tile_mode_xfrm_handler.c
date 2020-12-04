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
/* Handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/general/bcmltx_depth_expand_tile_mode.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_xfrm_field_desc.h>

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0[1] = {
    16384,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg1[1] = {
    4096,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg2[1] = {
    1024,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg3[1] = {
    2048,
};

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s1[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s2[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s3[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s4[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s5[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s6[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s7[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s8[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s9[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_dst_field_desc_d1[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_dst_field_desc_d1[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_dst_field_desc_d1[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_dst_field_desc_d1[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_dst_field_desc_d0[];

extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_dst_field_desc_d0[];

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s0 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s0
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s1 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s1
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s2 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s2
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s3 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s3
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s4 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s4
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s5 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s5
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s6 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s6
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s7 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s7
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s8 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s8
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s9 = {
    .field_num = 1,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_src_field_desc_s9
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_dst_list_d1 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_dst_field_desc_d1
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_dst_list_d1 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_dst_field_desc_d1
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_dst_list_d1 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_dst_field_desc_d1
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_dst_list_d1 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_dst_field_desc_d1
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_dst_field_desc_d0
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_dst_field_desc_d0
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s0[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_L3_NEXT_HOP_1t_L3_NEXT_HOP_1f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s1[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_L3_NEXT_HOP_2t_L3_NEXT_HOP_2f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s2[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_L3_OIF_2t_L3_OIF_2f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s3[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_L3_TUNNEL_0t_EGR_L3_TUNNEL_IDX_0f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s4[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_L3_TUNNEL_1t_EGR_L3_TUNNEL_IDX_0f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s5[1] = {
    BCM56880_A0_DNA_4_7_11_EGR_MPLS_VPNt_MPLS_VPN_OR_INT_INDEXf,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s6[1] = {
    BCM56880_A0_DNA_4_7_11_ING_IPMC_REMAP_TABLEt_IPMC_INDEXf,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s7[1] = {
    BCM56880_A0_DNA_4_7_11_ING_L3_NEXT_HOP_1_TABLEt_NHOP_INDEX_1f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s8[1] = {
    BCM56880_A0_DNA_4_7_11_ING_L3_NEXT_HOP_2_TABLEt_NHOP_INDEX_2f,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s9[1] = {
    BCM56880_A0_DNA_4_7_11_ING_L3_SRC_NEXT_HOP_TABLEt_L3_SRC_NHOP_INDEXf,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_transform_dst_d1[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_transform_dst_d1[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_transform_dst_d1[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_transform_dst_d1[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_transform_dst_d0[2] = {
    BCMLRD_FIELD_INDEX,
    BCMLRD_FIELD_TABLE_SEL,
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_L3_NEXT_HOP_1t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data1 = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_L3_NEXT_HOP_2t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data2 = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_L3_OIF_2t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data3 = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_L3_TUNNEL_0t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data4 = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_L3_TUNNEL_1t,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data5 = {
    .sid       = BCM56880_A0_DNA_4_7_11_EGR_MPLS_VPNt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data6 = {
    .sid       = BCM56880_A0_DNA_4_7_11_ING_IPMC_REMAP_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data7 = {
    .sid       = BCM56880_A0_DNA_4_7_11_ING_L3_NEXT_HOP_1_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data8 = {
    .sid       = BCM56880_A0_DNA_4_7_11_ING_L3_NEXT_HOP_2_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data9 = {
    .sid       = BCM56880_A0_DNA_4_7_11_ING_L3_SRC_NEXT_HOP_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s0_d0_x0_t0 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t0,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s0,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s0_d0_x0_t0 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t0,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_1_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s1_d0_x0_t1 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t1,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s1,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s1,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data1
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s1_d0_x0_t1 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t1,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_next_hop_2_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s1,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s1,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data1
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s2_d1_x1_t2 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg1,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t2,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s2,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s2,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_transform_dst_d1,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_dst_list_d1,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data2
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s2_d1_x1_t2 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg1,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t2,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_transform_dst_d1,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_oif_2_dst_list_d1,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s2,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s2,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data2
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s3_d1_x2_t3 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg2,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t3,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s3,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s3,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_transform_dst_d1,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_dst_list_d1,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data3
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s3_d1_x2_t3 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg2,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t3,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_transform_dst_d1,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_0_dst_list_d1,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s3,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s3,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data3
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s4_d1_x3_t4 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg3,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t4,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s4,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s4,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_transform_dst_d1,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_dst_list_d1,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data4
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s4_d1_x3_t4 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg3,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t4,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_transform_dst_d1,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_l3_tunnel_1_dst_list_d1,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s4,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s4,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data4
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s5_d1_x1_t5 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg1,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t5,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s5,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s5,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_transform_dst_d1,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_dst_list_d1,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data5
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s5_d1_x1_t5 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg1,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t5,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_transform_dst_d1,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_egr_mpls_vpn_dst_list_d1,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s5,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s5,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data5
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s6_d0_x0_t6 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t6,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s6,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s6,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data6
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s6_d0_x0_t6 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t6,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_ipmc_remap_table_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s6,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s6,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data6
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s7_d0_x0_t7 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t7,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s7,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s7,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data7
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s7_d0_x0_t7 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t7,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_1_table_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s7,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s7,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data7
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s8_d0_x0_t8 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t8,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s8,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s8,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data8
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s8_d0_x0_t8 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 2,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t8,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_next_hop_2_table_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s8,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s8,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data8
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s9_d0_x0_t9 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t9,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s9,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s9,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data9
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s9_d0_x0_t9 = {
    .values      = 1,
    .value       = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_arg0,
    .tables      = 4,
    .table       = bcm56880_a0_dna_4_7_11_lrd_depth_expand_tile_mode_transform_tbl_t9,
    .fields      = 2,
    .field       = bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_transform_dst_d0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lrd_bcmltx_depth_expand_tile_mode_ing_l3_src_next_hop_table_dst_list_d0,
    .rfields     = 1,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_transform_src_s9,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_src_list_s9,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_comp_data9
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s0_d0_x0_t0 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s0_d0_x0_t0
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s1_d0_x0_t1 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s1_d0_x0_t1
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s2_d1_x1_t2 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s2_d1_x1_t2
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s3_d1_x2_t3 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s3_d1_x2_t3
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s4_d1_x3_t4 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s4_d1_x3_t4
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s5_d1_x1_t5 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s5_d1_x1_t5
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s6_d0_x0_t6 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s6_d0_x0_t6
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s7_d0_x0_t7 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s7_d0_x0_t7
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s8_d0_x0_t8 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s8_d0_x0_t8
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_s9_d0_x0_t9 = {
    .transform     = bcmltx_depth_expand_tile_mode_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_fwd_arg_s9_d0_x0_t9
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s0_d0_x0_t0 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s0_d0_x0_t0
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s1_d0_x0_t1 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s1_d0_x0_t1
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s2_d1_x1_t2 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s2_d1_x1_t2
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s3_d1_x2_t3 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s3_d1_x2_t3
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s4_d1_x3_t4 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s4_d1_x3_t4
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s5_d1_x1_t5 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s5_d1_x1_t5
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s6_d0_x0_t6 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s6_d0_x0_t6
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s7_d0_x0_t7 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s7_d0_x0_t7
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s8_d0_x0_t8 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s8_d0_x0_t8
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_s9_d0_x0_t9 = {
    .transform     = bcmltx_depth_expand_tile_mode_rev_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_depth_expand_tile_mode_xfrm_handler_rev_arg_s9_d0_x0_t9
};


