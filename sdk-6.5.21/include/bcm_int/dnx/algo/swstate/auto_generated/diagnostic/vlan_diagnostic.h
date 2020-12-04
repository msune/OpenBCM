/** \file algo/swstate/auto_generated/diagnostic/vlan_diagnostic.h
 *
 * sw state functions declarations
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef __VLAN_DIAGNOSTIC_H__
#define __VLAN_DIAGNOSTIC_H__

#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include <soc/dnxc/swstate/dnx_sw_state_size.h>
#include <soc/dnxc/swstate/dnx_sw_state_diagnostic_operation_counters.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/types/vlan_types.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr_internal.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
#include <bcm_int/dnx/algo/vlan/algo_vlan.h>
#include <include/bcm/types.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
typedef enum {
    VLAN_DB_INFO,
    VLAN_DB_VLAN_INFO_INFO,
    VLAN_DB_VLAN_INFO_DEFAULT_VID_INFO,
    VLAN_DB_VSI_INFO,
    VLAN_DB_ACTION_ID_INGRESS_INFO,
    VLAN_DB_ACTION_ID_EGRESS_INFO,
    VLAN_DB_VLAN_PORT_INGRESS_VIRTUAL_GPORT_ID_INFO,
    VLAN_DB_VLAN_PORT_EGRESS_VIRTUAL_GPORT_ID_INFO,
    VLAN_DB_VLAN_RANGE_OUTER_PROFILE_INFO,
    VLAN_DB_VLAN_RANGE_INNER_PROFILE_INFO,
    VLAN_DB_INFO_NOF_ENTRIES
} sw_state_vlan_db_layout_e;


extern dnx_sw_state_diagnostic_info_t vlan_db_info[SOC_MAX_NUM_DEVICES][VLAN_DB_INFO_NOF_ENTRIES];

extern const char* vlan_db_layout_str[VLAN_DB_INFO_NOF_ENTRIES];
int vlan_db_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_info_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_info_default_vid_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vsi_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_action_id_ingress_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_action_id_egress_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_port_ingress_virtual_gport_id_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_port_egress_virtual_gport_id_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_range_outer_profile_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int vlan_db_vlan_range_inner_profile_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

#endif /* DNX_SW_STATE_DIAGNOSTIC */

#endif /* __VLAN_DIAGNOSTIC_H__ */
