/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from
 *    INTERNAL/fltg/xgs/npl/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLE.map.ltl for
 *      bcm56780_a0 variant dna_2_5_13
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
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_field_data.h>
#include <bcmlrd/chip/bcm56780_a0/bcm56780_a0_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_ltm_intf.h>
#include <bcmlrd/chip/bcm56780_a0/dna_2_5_13/bcm56780_a0_dna_2_5_13_lrd_xfrm_field_desc.h>
#include <bcmdrd/chip/bcm56780_a0_enum.h>
#include "bcmltd/chip/bcmltd_common_enumpool.h"
#include "../bcm56780_a0_lrd_enumpool.h"
#include "bcm56780_a0_dna_2_5_13_lrd_enumpool.h"
#include <bcmltd/bcmltd_handler.h>
/* L3_IPV4_MULTICAST_DEFIP_TABLE field init */
static const bcmlrd_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_field_data_mmd[] = {
    { /* 0 IPV4_ADDR */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 1 VRF */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x3fff,
      .depth = 0,
      .width = 14,
      .edata = NULL,
    },
    { /* 2 IPV4_ADDR_MASK */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0xffffffff,
      .depth = 0,
      .width = 32,
      .edata = NULL,
    },
    { /* 3 VRF_MASK */
      .flags = BCMLTD_FIELD_F_KEY,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x3fff,
      .depth = 0,
      .width = 14,
      .edata = NULL,
    },
    { /* 4 FLEX_CTR_ACTION */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x3f,
      .depth = 0,
      .width = 6,
      .edata = NULL,
    },
    { /* 5 STRENGTH_PROFILE_INDEX */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x1f,
      .depth = 0,
      .width = 5,
      .edata = NULL,
    },
    { /* 6 DESTINATION */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 7 DESTINATION_TYPE */
      .flags = BCMLTD_FIELD_F_ENUM,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0xa,
      .depth = 0,
      .width = 4,
      .edata = BCM56780_A0_DNA_2_5_13_LRD_DESTINATION_TYPE_DATA,
    },
    { /* 8 CLASS_ID */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0xffff,
      .depth = 0,
      .width = 16,
      .edata = NULL,
    },
    { /* 9 MTU_PROFILE_PTR */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x3ff,
      .depth = 0,
      .width = 10,
      .edata = NULL,
    },
    { /* 10 RPA_ID */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 11 EXPECTED_L3_IIF */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u16_0x3fff,
      .depth = 0,
      .width = 14,
      .edata = NULL,
    },
    { /* 12 MISC_CTRL_0 */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 13 MISC_CTRL_1 */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u8_0xf,
      .depth = 0,
      .width = 4,
      .edata = NULL,
    },
    { /* 14 ENTRY_PRIORITY */
      .flags = 0,
      .min = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .def = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x0,
      .max = &bcm56780_a0_dna_2_5_13_lrd_ifd_u32_0x7fffffff,
      .depth = 0,
      .width = 31,
      .edata = NULL,
    },
};
const bcmlrd_map_field_data_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_field_data = {
    .fields = 15,
    .field = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_field_data_mmd
};

static const bcmlrd_map_table_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_attr_entry[] = {
    { /* 0 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_INTERACTIVE,
        .value = FALSE,
    },
    { /* 1 */
        .key   = BCMLRD_MAP_TABLE_ATTRIBUTE_TABLE_SIZE,
        .value = 16384,
    },
};

static const bcmlrd_map_attr_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_attr_group = {
    .attributes = 2,
    .attr = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_attr_entry,
};


const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_src_field_desc_s0[4] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDR_MASKf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDR_MASKf,
        .field_idx = 0,
        .minbit    = 16,
        .maxbit    = 27,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDR_MASKf,
        .field_idx = 0,
        .minbit    = 28,
        .maxbit    = 29,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDR_MASKf,
        .field_idx = 0,
        .minbit    = 30,
        .maxbit    = 31,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_dst_field_desc[4] = {
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 136,
        .maxbit    = 151,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 124,
        .maxbit    = 135,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 110,
        .maxbit    = 111,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 106,
        .maxbit    = 107,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_src_field_desc_s0[4] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDRf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 15,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDRf,
        .field_idx = 0,
        .minbit    = 16,
        .maxbit    = 27,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDRf,
        .field_idx = 0,
        .minbit    = 28,
        .maxbit    = 29,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_IPV4_ADDRf,
        .field_idx = 0,
        .minbit    = 30,
        .maxbit    = 31,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_dst_field_desc[4] = {
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 36,
        .maxbit    = 51,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 24,
        .maxbit    = 35,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 10,
        .maxbit    = 11,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 6,
        .maxbit    = 7,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_src_field_desc_s0[2] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_VRF_MASKf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 11,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_VRF_MASKf,
        .field_idx = 0,
        .minbit    = 12,
        .maxbit    = 13,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_dst_field_desc[2] = {
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 112,
        .maxbit    = 123,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 108,
        .maxbit    = 109,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_src_field_desc_s0[2] = {
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_VRFf,
        .field_idx = 0,
        .minbit    = 0,
        .maxbit    = 11,
        .entry_idx = 0,
        .reserved  = 0
    },
    {
        .field_id  = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_VRFf,
        .field_idx = 0,
        .minbit    = 12,
        .maxbit    = 13,
        .entry_idx = 0,
        .reserved  = 0
    },
};

static const bcmltd_field_desc_t
bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_dst_field_desc[2] = {
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 12,
        .maxbit    = 23,
        .entry_idx = 0,
        .reserved  = 0,
    },
    {
        .field_id  = TCAM_ONLYf,
        .field_idx = 0,
        .minbit    = 8,
        .maxbit    = 9,
        .entry_idx = 0,
        .reserved  = 0,
    },
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_IPV4_ADDR_MASKF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_src_field_desc_s0,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_IPV4_ADDR_MASKF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_dst_field_desc,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_IPV4_ADDRF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_src_field_desc_s0,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_IPV4_ADDRF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 4,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_dst_field_desc,
    .dst_fields = 4,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_VRF_MASKF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_src_field_desc_s0,
    .dst_fields = 2,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_VRF_MASKF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_dst_field_desc,
    .dst_fields = 2,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_src_field_desc_s0,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_fwd_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_VRFF_0_XFRM_HANDLER_FWD_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_src_field_desc_s0,
    .dst_fields = 2,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_dst_field_desc,
};

const bcmlrd_field_xfrm_desc_t
bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_rev_s0_d0_desc = {
    .handler_id = BCMLTD_TRANSFORM_BCM56780_A0_DNA_2_5_13_LTA_BCMLTX_FIELD_DEMUX_L3_IPV4_MULTICAST_DEFIP_TABLET_VRFF_0_XFRM_HANDLER_REV_S0_D0_ID,
    .src_fields = 2,
    .src = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_dst_field_desc,
    .dst_fields = 2,
    .dst = bcm56780_a0_dna_2_5_13_lrd_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_src_field_desc_s0,
};


static const bcmlrd_map_entry_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_memdb_tcam_ifta80_mem0_0_map_entry[] = {
    { /* 0 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 360,
            .maxbit    = 364,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_STRENGTH_PROFILE_INDEXf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 4,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 1 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 354,
            .maxbit    = 359,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_FLEX_CTR_ACTIONf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 5,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 2 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 210,
            .maxbit    = 213,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_DESTINATION_TYPEf,
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
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 274,
            .maxbit    = 289,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_DESTINATIONf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 15,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 4 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 258,
            .maxbit    = 273,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_CLASS_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 15,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 5 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 348,
            .maxbit    = 351,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_MISC_CTRL_0f,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 6 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 218,
            .maxbit    = 221,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_MISC_CTRL_1f,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 7 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 226,
            .maxbit    = 235,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_MTU_PROFILE_PTRf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 9,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 8 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 214,
            .maxbit    = 217,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_RPA_IDf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 3,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 9 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_VALUE,
        .desc = {
            .field_id  = DATA_ONLY_0f,
            .field_idx = 0,
            .minbit    = 242,
            .maxbit    = 255,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_EXPECTED_L3_IIFf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 13,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 10 */
        .entry_type = BCMLRD_MAP_ENTRY_MAPPED_KEY,
        .desc = {
            .field_id  = BCMLRD_FIELD_ENTRY_PRIORITY,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 30,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .mapped = {
                .src = {
                    .field_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt_ENTRY_PRIORITYf,
                    .field_idx = 0,
                    .minbit    = 0,
                    .maxbit    = 30,
                    .entry_idx = 0,
                    .reserved  = 0
                }
            }
        },
    },
    { /* 11 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = TCAM_ONLYf,
            .field_idx = 0,
            .minbit    = 0,
            .maxbit    = 0,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 1,
            }
        },
    },
    { /* 12 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = TCAM_ONLYf,
            .field_idx = 0,
            .minbit    = 2,
            .maxbit    = 5,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 2,
            }
        },
    },
    { /* 13 */
        .entry_type = BCMLRD_MAP_ENTRY_FIXED_KEY,
        .desc = {
            .field_id  = TCAM_ONLYf,
            .field_idx = 0,
            .minbit    = 102,
            .maxbit    = 105,
            .entry_idx = 0,
            .reserved  = 0
        },
        .u = {
            .fixed = {
                .value = 15,
            }
        },
    },
    { /* 14 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 15 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addr_maskf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 16 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 17 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_ipv4_addrf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 18 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 19 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrf_maskf_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
    { /* 20 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_fwd_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_fwd_s0_d0_desc,
            },
        },
    },
    { /* 21 */
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
                /* handler: bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_rev_s0_d0 */
                .desc = &bcm56780_a0_dna_2_5_13_lta_bcmltx_field_demux_l3_ipv4_multicast_defip_tablet_vrff_0_xfrm_handler_rev_s0_d0_desc,
            },
        },
    },
};
static const bcmlrd_map_group_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_group[] = {
    {
        .dest = {
            .kind = BCMLRD_MAP_PHYSICAL,
            .id = MEMDB_TCAM_IFTA80_MEM0_0m,
        },
        .entries = 22,
        .entry = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_memdb_tcam_ifta80_mem0_0_map_entry
    },
};
const bcmlrd_map_t bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map = {
    .src_id = BCM56780_A0_DNA_2_5_13_L3_IPV4_MULTICAST_DEFIP_TABLEt,
    .field_data = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_field_data,
    .groups = 1,
    .group  = bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_table_map_group,
    .table_attr = &bcm56780_a0_dna_2_5_13_lrd_l3_ipv4_multicast_defip_tablet_attr_group,
    .entry_ops = BCMLRD_MAP_TABLE_ENTRY_OPERATION_LOOKUP | BCMLRD_MAP_TABLE_ENTRY_OPERATION_TRAVERSE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_INSERT | BCMLRD_MAP_TABLE_ENTRY_OPERATION_UPDATE | BCMLRD_MAP_TABLE_ENTRY_OPERATION_DELETE
};
