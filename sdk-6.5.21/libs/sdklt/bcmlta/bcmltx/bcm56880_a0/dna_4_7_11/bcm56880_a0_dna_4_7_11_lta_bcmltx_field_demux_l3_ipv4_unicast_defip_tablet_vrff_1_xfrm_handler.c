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
/* Handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmltx_field_demux.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include <bcmlrd/chip/bcm56880_a0/dna_4_7_11/bcm56880_a0_dna_4_7_11_lrd_xfrm_field_desc.h>


extern const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lrd_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_src_field_desc_s1[];

static const bcmltd_field_desc_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_dst_field_desc[2] = {
    {
        .field_id  = BCMLTD_INTERNAL_FIELD_BASE + 64,
        .field_idx = 0,
        .minbit    = 12,
        .maxbit    = 23,
        .entry_idx = 1,
        .sym       = "MEMDB_TCAM_IFTA80_MEM2_0_ONLYm.KEYf.ENTRY1[21:10]",
        .reserved  = 0
    },
    {
        .field_id  = BCMLTD_INTERNAL_FIELD_BASE + 65,
        .field_idx = 0,
        .minbit    = 8,
        .maxbit    = 9,
        .entry_idx = 1,
        .sym       = "MEMDB_TCAM_IFTA80_MEM2_0_ONLYm.KEYf.ENTRY1[7:6]",
        .reserved  = 0
    },
};

static const
bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_src_list_s0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lrd_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_src_field_desc_s1
};

static const bcmltd_field_list_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_dst_list_d0 = {
    .field_num = 2,
    .field_array = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_dst_field_desc
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_transform_src_s0[1] = {
    BCM56880_A0_DNA_4_7_11_L3_IPV4_UNICAST_DEFIP_TABLEt_VRFf,
};

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_transform_dst_d0[2] = {
    BCMLTD_INTERNAL_FIELD_BASE + 64,
    BCMLTD_INTERNAL_FIELD_BASE + 65,
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_comp_data = {
    .sid       = BCM56880_A0_DNA_4_7_11_L3_IPV4_UNICAST_DEFIP_TABLEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_xfrm_handler_fwd_arg_s0_d0 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_transform_src_s0,
    .field_list  = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_src_list_s0,
    .rfields     = 2,
    .rfield      = bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_transform_dst_d0,
    .rfield_list = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_dst_list_d0,
    .comp_data   = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_comp_data
};

const bcmltd_xfrm_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_xfrm_handler_fwd_s0_d0 = {
    .transform     = bcmltx_field_demux_transform,
    .arg           = &bcm56880_a0_dna_4_7_11_lta_bcmltx_field_demux_l3_ipv4_unicast_defip_tablet_vrff_1_xfrm_handler_fwd_arg_s0_d0
};


