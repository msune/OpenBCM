/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by c-struct-gen from PTRM data files.
 *
 * Tool: $SDK/INTERNAL/fltg/bin/c-struct-gen
 *
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
#include "bcm56990_b0_ptrm.h"
#include "bcm56990_b0_hash.ptrm.data.h"
#include "bcm56990_b0_tcam_pri.ptrm.data.h"
#include "bcm56990_b0_alpm.ptrm.data.h"
#include "bcm56990_b0_tcam_fp.ptrm.data.h"
#include "bcm56990_b0_ctr.ptrm.data.h"

const bcmptm_ptrm_table_data_t bcm56990_b0_ptrm_table_data;
static const bcmptm_ptrm_table_t bcm56990_b0_ptrm_table[65];

const bcmptm_ptrm_table_data_t bcm56990_b0_ptrm_table_data = {
    .table_data =     bcm56990_b0_ptrm_table,
    .table_data_count = 65,/* implicit length assignment */
};
static const bcmptm_ptrm_table_t bcm56990_b0_ptrm_table[65] = {
    {
        .handler = &th4_b0_l2_vfi_fdb_lt_mreq_info,
        .sid = L2_VFI_FDBt,
    },
    {
        .handler = &th4_b0_l2_vfi_fdb_cc_lt_mreq_info,
        .sid = L2_VFI_FDB_CCt,
    },
    {
        .handler = &th4_b0_tnl_mpls_decap_1_lt_mreq_info,
        .sid = TNL_MPLS_DECAP_1t,
    },
    {
        .handler = &th4_b0_tnl_mpls_decap_trunk_1_lt_mreq_info,
        .sid = TNL_MPLS_DECAP_TRUNK_1t,
    },
    {
        .handler = &th4_b0_tnl_mpls_decap_2_lt_mreq_info,
        .sid = TNL_MPLS_DECAP_2t,
    },
    {
        .handler = &th4_b0_tnl_mpls_decap_trunk_2_lt_mreq_info,
        .sid = TNL_MPLS_DECAP_TRUNK_2t,
    },
    {
        .handler = &th4_b0_tnl_ipv4_decap_em_lt_mreq_info,
        .sid = TNL_IPV4_DECAP_EMt,
    },
    {
        .handler = &th4_b0_tnl_ipv6_decap_em_lt_mreq_info,
        .sid = TNL_IPV6_DECAP_EMt,
    },
    {
        .handler = &th4_b0_fp_em_entry_lt_mreq_info,
        .sid = FP_EM_ENTRYt,
    },
    {
        .handler = &th4_b0_vfi_egr_adapt_port_grp_lt_mreq_info,
        .sid = VFI_EGR_ADAPT_PORT_GRPt,
    },
    {
        .handler = &th4_b0_vfi_ing_adapt_ovid_port_grp_lt_mreq_info,
        .sid = VFI_ING_ADAPT_OVID_PORT_GRPt,
    },
    {
        .handler = &th4_b0_port_svp_es_filtering_lt_mreq_info,
        .sid = PORT_SVP_ES_FILTERINGt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_adapt_vfi_lt_mreq_info,
        .sid = TNL_L2_VXLAN_ADAPT_VFIt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_adapt_vfi_dvp_grp_lt_mreq_info,
        .sid = TNL_L2_VXLAN_ADAPT_VFI_DVP_GRPt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_svp_assignment_ovid_src_ipv4_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_SVP_ASSIGNMENT_OVID_SRC_IPV4t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_svp_assignment_ovid_src_ipv6_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_SVP_ASSIGNMENT_OVID_SRC_IPV6t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_VFI_ASSIGNMENT_OVID_VNIDt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv4_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_VFI_ASSIGNMENT_OVID_VNID_SRC_IPV4t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_vfi_assignment_ovid_vnid_src_ipv6_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_VFI_ASSIGNMENT_OVID_VNID_SRC_IPV6t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_dst_ipv4_em_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_DST_IPV4_EMt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_dst_ipv6_em_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6_EMt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_ipv4_em_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_IPV4_EMt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_ipv6_em_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_IPV6_EMt,
    },
    {
        .handler = &th4_b0_l2_vfi_fdb_static_lt_mreq_info,
        .sid = L2_VFI_FDB_STATICt,
    },
    {
        .handler = &th4_b0_l2_vfi_underlay_my_station_tcam_lt_mreq_info,
        .sid = L2_VFI_UNDERLAY_MY_STATIONt,
    },
    {
        .handler = &th4_b0_l2_vfi_underlay_my_station_modport_tcam_lt_mreq_info,
        .sid = L2_VFI_UNDERLAY_MY_STATION_MODPORTt,
    },
    {
        .handler = &th4_b0_l2_vfi_underlay_my_station_trunk_tcam_lt_mreq_info,
        .sid = L2_VFI_UNDERLAY_MY_STATION_TRUNKt,
    },
    {
        .handler = &th4_b0_l2_vfi_my_station_tcam_lt_mreq_info,
        .sid = L2_VFI_MY_STATIONt,
    },
    {
        .handler = &th4_b0_l2_vfi_my_station_modport_tcam_lt_mreq_info,
        .sid = L2_VFI_MY_STATION_MODPORTt,
    },
    {
        .handler = &th4_b0_l2_vfi_my_station_trunk_tcam_lt_mreq_info,
        .sid = L2_VFI_MY_STATION_TRUNKt,
    },
    {
        .handler = &th4_b0_tm_cos_q_cpu_map_lt_mreq_info,
        .sid = TM_COS_Q_CPU_MAPt,
    },
    {
        .handler = &th4_b0_udf_lt_mreq_info,
        .sid = UDFt,
    },
    {
        .handler = &th4_b0_lb_hash_flex_fields_select_lt_mreq_info,
        .sid = LB_HASH_FLEX_FIELDS_SELECTIONt,
    },
    {
        .handler = &th4_b0_tnl_ipv4_decap_lt_mreq_info,
        .sid = TNL_IPV4_DECAPt,
    },
    {
        .handler = &th4_b0_tnl_ipv6_decap_lt_mreq_info,
        .sid = TNL_IPV6_DECAPt,
    },
    {
        .handler = &th4_b0_mirror_ing_event_profile_lt_mreq_info,
        .sid = MIRROR_ING_EVENT_PROFILEt,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_dst_ipv4_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_DST_IPV4t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_dst_ipv6_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_DST_IPV6t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_ipv4_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_IPV4t,
    },
    {
        .handler = &th4_b0_tnl_l2_vxlan_decap_ovid_ipv6_lt_mreq_info,
        .sid = TNL_L2_VXLAN_DECAP_OVID_IPV6t,
    },
    {
        .handler = &th4_b0_l3_ipv4_uc_route_lt_mreq_info,
        .sid = L3_IPV4_UC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_ipv4_uc_route_vrf_lt_mreq_info,
        .sid = L3_IPV4_UC_ROUTE_VRFt,
    },
    {
        .handler = &th4_b0_l3_ipv4_uc_route_override_lt_mreq_info,
        .sid = L3_IPV4_UC_ROUTE_OVERRIDEt,
    },
    {
        .handler = &th4_b0_l3_ipv4_mc_route_lt_mreq_info,
        .sid = L3_IPV4_MC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_ipv6_uc_route_lt_mreq_info,
        .sid = L3_IPV6_UC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_ipv6_uc_route_vrf_lt_mreq_info,
        .sid = L3_IPV6_UC_ROUTE_VRFt,
    },
    {
        .handler = &th4_b0_l3_ipv6_uc_route_override_lt_mreq_info,
        .sid = L3_IPV6_UC_ROUTE_OVERRIDEt,
    },
    {
        .handler = &th4_b0_l3_ipv6_mc_route_lt_mreq_info,
        .sid = L3_IPV6_MC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_src_ipv4_uc_route_lt_mreq_info,
        .sid = L3_SRC_IPV4_UC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_src_ipv4_uc_route_vrf_lt_mreq_info,
        .sid = L3_SRC_IPV4_UC_ROUTE_VRFt,
    },
    {
        .handler = &th4_b0_l3_src_ipv4_uc_route_override_lt_mreq_info,
        .sid = L3_SRC_IPV4_UC_ROUTE_OVERRIDEt,
    },
    {
        .handler = &th4_b0_l3_src_ipv6_uc_route_lt_mreq_info,
        .sid = L3_SRC_IPV6_UC_ROUTEt,
    },
    {
        .handler = &th4_b0_l3_src_ipv6_uc_route_vrf_lt_mreq_info,
        .sid = L3_SRC_IPV6_UC_ROUTE_VRFt,
    },
    {
        .handler = &th4_b0_l3_src_ipv6_uc_route_override_lt_mreq_info,
        .sid = L3_SRC_IPV6_UC_ROUTE_OVERRIDEt,
    },
    {
        .handler = &th4_b0_l3_ipv4_comp_dst_lt_mreq_info,
        .sid = L3_IPV4_COMP_DSTt,
    },
    {
        .handler = &th4_b0_l3_ipv4_comp_src_lt_mreq_info,
        .sid = L3_IPV4_COMP_SRCt,
    },
    {
        .handler = &th4_b0_l3_ipv6_comp_dst_lt_mreq_info,
        .sid = L3_IPV6_COMP_DSTt,
    },
    {
        .handler = &th4_b0_l3_ipv6_comp_src_lt_mreq_info,
        .sid = L3_IPV6_COMP_SRCt,
    },
    {
        .handler = &th4_b0_fp_ing_entry_lt_mreq_info,
        .sid = FP_ING_ENTRYt,
    },
    {
        .handler = &th4_b0_fp_ing_presel_entry_lt_mreq_info,
        .sid = FP_ING_PRESEL_ENTRY_TEMPLATEt,
    },
    {
        .handler = &th4_b0_fp_vlan_entry_lt_mreq_info,
        .sid = FP_VLAN_ENTRYt,
    },
    {
        .handler = &th4_b0_fp_egr_entry_lt_mreq_info,
        .sid = FP_EGR_ENTRYt,
    },
    {
        .handler = &th4_b0_fp_em_presel_entry_lt_mreq_info,
        .sid = FP_EM_PRESEL_ENTRY_TEMPLATEt,
    },
    {
        .handler = &th4_b0_mirror_ing_flex_sflow_lt_mreq_info,
        .sid = MIRROR_ING_FLEX_SFLOWt,
    },
    {
        .handler = &th4_b0_mirror_port_encap_sflow_lt_mreq_info,
        .sid = MIRROR_PORT_ENCAP_SFLOWt,
    },
};

