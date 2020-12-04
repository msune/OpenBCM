/** \file dnx/swstate/auto_generated/diagnostic/dnx_algo_field_action_commandline.h
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

#ifndef __DNX_ALGO_FIELD_ACTION_COMMANDLINE_H__
#define __DNX_ALGO_FIELD_ACTION_COMMANDLINE_H__

#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_utils.h>
#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_algo_field_action_types.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_field_types.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_field_key_types.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/types/dnx_algo_field_types.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
shr_error_e sh_dnx_swstate_dnx_algo_field_action_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_dump_man;
shr_error_e sh_dnx_swstate_dnx_algo_field_action_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_size_get_man;
shr_error_e sh_dnx_swstate_dnx_algo_field_action_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_diagnostic_operation_counters_man;
extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_desc[];

extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_field_group_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_place_in_fg_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_fes_state_mask_is_alloc_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf2_context_state_priority_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_field_group_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_place_in_fg_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_fes_state_mask_is_alloc_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_ipmf3_context_state_priority_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_fes_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_field_group_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_place_in_fg_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_fes_state_mask_is_alloc_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_context_state_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_diagnostic_operation_counters_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_man;
extern const char cmd_dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_desc[];
shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_dump_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_size_get_man;


shr_error_e sh_dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_diagnostic_operation_counters_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_diagnostic_operation_counters_options[];
extern sh_sand_man_t dnx_swstate_dnx_algo_field_action_epmf_context_state_priority_diagnostic_operation_counters_man;


#endif /* DNX_SW_STATE_DIAGNOSTIC */

#endif /* __DNX_ALGO_FIELD_ACTION_COMMANDLINE_H__ */
