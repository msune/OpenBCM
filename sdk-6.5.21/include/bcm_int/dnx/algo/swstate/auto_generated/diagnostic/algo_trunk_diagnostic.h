/** \file algo/swstate/auto_generated/diagnostic/algo_trunk_diagnostic.h
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

#ifndef __ALGO_TRUNK_DIAGNOSTIC_H__
#define __ALGO_TRUNK_DIAGNOSTIC_H__

#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include <soc/dnxc/swstate/dnx_sw_state_size.h>
#include <soc/dnxc/swstate/dnx_sw_state_diagnostic_operation_counters.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/types/algo_trunk_types.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr_internal.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
#include <bcm_int/dnx/algo/trunk/algo_trunk.h>
#include <include/soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
typedef enum {
    ALGO_TRUNK_DB_INFO,
    ALGO_TRUNK_DB_EGRESS_TRUNK_INFO,
    ALGO_TRUNK_DB_POOLS_INFO,
    ALGO_TRUNK_DB_POOLS_GROUPS_INFO,
    ALGO_TRUNK_DB_POOLS_GROUPS_SPA_ID_MANAGER_INFO,
    ALGO_TRUNK_DB_POOLS_GROUPS_TM_INDEX_MANAGER_INFO,
    ALGO_TRUNK_DB_PSC_PROFILES_INFO,
    ALGO_TRUNK_DB_INFO_NOF_ENTRIES
} sw_state_algo_trunk_db_layout_e;


extern dnx_sw_state_diagnostic_info_t algo_trunk_db_info[SOC_MAX_NUM_DEVICES][ALGO_TRUNK_DB_INFO_NOF_ENTRIES];

extern const char* algo_trunk_db_layout_str[ALGO_TRUNK_DB_INFO_NOF_ENTRIES];
int algo_trunk_db_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_egress_trunk_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_pools_dump(
    int unit, int pools_idx_0, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_pools_groups_dump(
    int unit, int pools_idx_0, int groups_idx_0, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_pools_groups_spa_id_manager_dump(
    int unit, int pools_idx_0, int groups_idx_0, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_pools_groups_tm_index_manager_dump(
    int unit, int pools_idx_0, int groups_idx_0, dnx_sw_state_dump_filters_t filters);

int algo_trunk_db_psc_profiles_dump(
    int unit, dnx_sw_state_dump_filters_t filters);

#endif /* DNX_SW_STATE_DIAGNOSTIC */

#endif /* __ALGO_TRUNK_DIAGNOSTIC_H__ */
