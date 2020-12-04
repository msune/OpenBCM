/** \file dnx/swstate/auto_generated/diagnostic/algo_trunk_commandline.h
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

#ifndef __ALGO_TRUNK_COMMANDLINE_H__
#define __ALGO_TRUNK_COMMANDLINE_H__

#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_utils.h>
#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/types/algo_trunk_types.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr_internal.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
#include <bcm_int/dnx/algo/trunk/algo_trunk.h>
#include <include/soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
shr_error_e sh_dnx_swstate_algo_trunk_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_dump_man;
shr_error_e sh_dnx_swstate_algo_trunk_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_size_get_man;
shr_error_e sh_dnx_swstate_algo_trunk_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_diagnostic_operation_counters_man;
extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_man;
extern const char cmd_dnx_swstate_algo_trunk_desc[];

extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_egress_trunk_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_egress_trunk_man;
extern const char cmd_dnx_swstate_algo_trunk_egress_trunk_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_egress_trunk_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_egress_trunk_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_egress_trunk_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_egress_trunk_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_egress_trunk_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_egress_trunk_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_egress_trunk_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_egress_trunk_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_egress_trunk_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_pools_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_man;
extern const char cmd_dnx_swstate_algo_trunk_pools_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_pools_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_pools_groups_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_man;
extern const char cmd_dnx_swstate_algo_trunk_pools_groups_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_pools_groups_spa_id_manager_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_man;
extern const char cmd_dnx_swstate_algo_trunk_pools_groups_spa_id_manager_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_spa_id_manager_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_spa_id_manager_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_spa_id_manager_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_spa_id_manager_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_pools_groups_tm_index_manager_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_man;
extern const char cmd_dnx_swstate_algo_trunk_pools_groups_tm_index_manager_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_tm_index_manager_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_tm_index_manager_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_pools_groups_tm_index_manager_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_pools_groups_tm_index_manager_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_algo_trunk_psc_profiles_cmds[];
extern sh_sand_man_t dnx_swstate_algo_trunk_psc_profiles_man;
extern const char cmd_dnx_swstate_algo_trunk_psc_profiles_desc[];
shr_error_e sh_dnx_swstate_algo_trunk_psc_profiles_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_psc_profiles_dump_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_psc_profiles_dump_man;


shr_error_e sh_dnx_swstate_algo_trunk_psc_profiles_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_psc_profiles_size_get_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_psc_profiles_size_get_man;


shr_error_e sh_dnx_swstate_algo_trunk_psc_profiles_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_algo_trunk_psc_profiles_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_algo_trunk_psc_profiles_diagnostic_operation_counters_man;


#endif /* DNX_SW_STATE_DIAGNOSTIC */

#endif /* __ALGO_TRUNK_COMMANDLINE_H__ */
