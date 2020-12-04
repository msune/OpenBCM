/** \file algo/swstate/auto_generated/diagnostic/algo_lif_profile_diagnostic.c
 *
 * sw state functions definitions
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

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <bcm_int/dnx/algo/swstate/auto_generated/diagnostic/algo_lif_profile_diagnostic.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
/*
 * Global Variables
 */

extern algo_lif_profile_sw_state_t * algo_lif_profile_db_data[SOC_MAX_NUM_DEVICES];
/*
 * FUNCTIONs
 */

/*
 *
 * dump function for the variable algo_lif_profile_db
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(algo_lif_profile_db_in_lif_profile_l3_enablers_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_in_lif_lb_profile_enablers_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_in_lif_profile_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_eth_rif_profile_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_in_lif_da_not_found_destination_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_etpp_out_lif_profile_dump(unit, filters));
    SHR_IF_ERR_EXIT(algo_lif_profile_db_erpp_out_lif_profile_dump(unit, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable in_lif_profile_l3_enablers
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_in_lif_profile_l3_enablers_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile in_lif_profile_l3_enablers") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile in_lif_profile_l3_enablers\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/in_lif_profile_l3_enablers.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_profile_l3_enablers: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_profile_l3_enablers: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->in_lif_profile_l3_enablers,
            dnx_algo_in_lif_profile_l3_enablers_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable in_lif_lb_profile_enablers
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_in_lif_lb_profile_enablers_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile in_lif_lb_profile_enablers") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile in_lif_lb_profile_enablers\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/in_lif_lb_profile_enablers.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_lb_profile_enablers: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_lb_profile_enablers: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->in_lif_lb_profile_enablers,
            dnx_algo_in_lif_profile_in_lif_lb_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable in_lif_profile
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_in_lif_profile_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile in_lif_profile") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile in_lif_profile\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/in_lif_profile.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_profile: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_profile: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->in_lif_profile,
            dnx_algo_in_lif_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable eth_rif_profile
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_eth_rif_profile_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile eth_rif_profile") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile eth_rif_profile\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/eth_rif_profile.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","eth_rif_profile: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","eth_rif_profile: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->eth_rif_profile,
            dnx_algo_in_lif_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable in_lif_da_not_found_destination
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_in_lif_da_not_found_destination_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile in_lif_da_not_found_destination") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile in_lif_da_not_found_destination\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/in_lif_da_not_found_destination.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_da_not_found_destination: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","in_lif_da_not_found_destination: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->in_lif_da_not_found_destination,
            dnx_algo_in_lif_flood_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable etpp_out_lif_profile
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_etpp_out_lif_profile_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile etpp_out_lif_profile") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile etpp_out_lif_profile\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/etpp_out_lif_profile.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","etpp_out_lif_profile: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","etpp_out_lif_profile: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->etpp_out_lif_profile,
            dnx_algo_etpp_out_lif_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable erpp_out_lif_profile
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
algo_lif_profile_db_erpp_out_lif_profile_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "algo_lif_profile erpp_out_lif_profile") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate algo_lif_profile erpp_out_lif_profile\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "algo_lif_profile_db/erpp_out_lif_profile.txt",
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","erpp_out_lif_profile: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "algo_lif_profile_db[%d]->","((algo_lif_profile_sw_state_t*)sw_state_roots_array[%d][ALGO_LIF_PROFILE_MODULE_ID])->","erpp_out_lif_profile: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_TEMP_MNGR_PRINT(
            unit,
            ALGO_LIF_PROFILE_MODULE_ID,
            &((algo_lif_profile_sw_state_t*)sw_state_roots_array[unit][ALGO_LIF_PROFILE_MODULE_ID])->erpp_out_lif_profile,
            dnx_algo_erpp_out_lif_profile_print_entry_cb);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 * Global Variables
 */

dnx_sw_state_diagnostic_info_t algo_lif_profile_db_info[SOC_MAX_NUM_DEVICES][ALGO_LIF_PROFILE_DB_INFO_NOF_ENTRIES];
const char* algo_lif_profile_db_layout_str[ALGO_LIF_PROFILE_DB_INFO_NOF_ENTRIES] = {
    "ALGO_LIF_PROFILE_DB~",
    "ALGO_LIF_PROFILE_DB~IN_LIF_PROFILE_L3_ENABLERS~",
    "ALGO_LIF_PROFILE_DB~IN_LIF_LB_PROFILE_ENABLERS~",
    "ALGO_LIF_PROFILE_DB~IN_LIF_PROFILE~",
    "ALGO_LIF_PROFILE_DB~ETH_RIF_PROFILE~",
    "ALGO_LIF_PROFILE_DB~IN_LIF_DA_NOT_FOUND_DESTINATION~",
    "ALGO_LIF_PROFILE_DB~ETPP_OUT_LIF_PROFILE~",
    "ALGO_LIF_PROFILE_DB~ERPP_OUT_LIF_PROFILE~",
};
#endif /* DNX_SW_STATE_DIAGNOSTIC */
#undef BSL_LOG_MODULE
