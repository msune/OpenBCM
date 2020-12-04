/** \file algo/swstate/auto_generated/diagnostic/dnx_mirror_diagnostic.c
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

#include <bcm_int/dnx/algo/swstate/auto_generated/diagnostic/dnx_mirror_diagnostic.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
/*
 * Global Variables
 */

extern dnx_mirror_db_t * dnx_mirror_db_data[SOC_MAX_NUM_DEVICES];
/*
 * FUNCTIONs
 */

/*
 *
 * dump function for the variable dnx_mirror_db
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;
    SHR_IF_ERR_EXIT(dnx_mirror_db_channel_to_egress_if_dump(unit, -1, -1, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_egress_mirror_priority_dump(unit, -1, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_snif_ingress_profiles_mirror_dump(unit, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_snif_ingress_profiles_snoop_dump(unit, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_snif_ingress_profiles_stat_sampling_dump(unit, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_snif_egress_vlan_profiles_mirror_dump(unit, -1, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_snif_ingress_vlan_profiles_mirror_dump(unit, -1, filters));
    SHR_IF_ERR_EXIT(dnx_mirror_db_mirror_on_drop_profile_dump(unit, -1, filters));
    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable channel_to_egress_if
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_channel_to_egress_if_dump(int  unit,  int  channel_to_egress_if_idx_0,  int  channel_to_egress_if_idx_1,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = channel_to_egress_if_idx_0, I0 = channel_to_egress_if_idx_0 + 1;
    int i1 = channel_to_egress_if_idx_1, I1 = channel_to_egress_if_idx_1 + 1, org_i1 = channel_to_egress_if_idx_1;
    char *s0 = "", *s1 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "int") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror channel_to_egress_if") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror channel_to_egress_if\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/channel_to_egress_if.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","channel_to_egress_if[][]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_DATA_MAX_DEVICE_GENERAL_NOF_CORES;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->channel_to_egress_if
                , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->channel_to_egress_if), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_DATA_MAX_DEVICE_GENERAL_NOF_CORES)
        {
            LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->channel_to_egress_if[][]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_DATA_MAX_DEVICE_GENERAL_NOF_CORES == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            if (i1 == -1) {
                I1 = DNX_DATA_MAX_PORT_GENERAL_MAX_NOF_CHANNELS;
                i1 = dnx_sw_state_dump_check_all_the_same(unit,
                    ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->channel_to_egress_if[i0]
                    , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->channel_to_egress_if[i0]), I1, &s1) ? I1 - 1 : 0;
            }

            if(i1 >= DNX_DATA_MAX_PORT_GENERAL_MAX_NOF_CHANNELS)
            {
                LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->channel_to_egress_if[][]: ")));
                LOG_CLI((BSL_META("Invalid index: %d \n"),i1));
                SHR_EXIT();
            }

            if(DNX_DATA_MAX_PORT_GENERAL_MAX_NOF_CHANNELS == 0)
            {
                SHR_EXIT();
            }

            for(; i1 < I1; i1++) {
                dnx_sw_state_dump_update_current_idx(unit, i1);
                DNX_SW_STATE_PRINT_MONITOR(
                    unit,
                    "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","channel_to_egress_if[%s%d][%s%d]: ", s0, i0, s1, i1);

                DNX_SW_STATE_PRINT_FILE(
                    unit,
                    "[%s%d][%s%d]: ", s0, i0, s1, i1);

                dnx_sw_state_print_int(
                    unit,
                    &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->channel_to_egress_if[i0][i1]);

            }
            i1 = org_i1;
            dnx_sw_state_dump_end_of_stride(unit);
        }
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable egress_mirror_priority
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_egress_mirror_priority_dump(int  unit,  int  egress_mirror_priority_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = egress_mirror_priority_idx_0, I0 = egress_mirror_priority_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "bcm_pbmp_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror egress_mirror_priority") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror egress_mirror_priority\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/egress_mirror_priority.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","egress_mirror_priority[]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        if (i0 == -1) {
            I0 = DNX_MIRROR_RCY_PRIORITY_NOF;
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->egress_mirror_priority
                , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->egress_mirror_priority), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= DNX_MIRROR_RCY_PRIORITY_NOF)
        {
            LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->egress_mirror_priority[]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(DNX_MIRROR_RCY_PRIORITY_NOF == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_OPAQUE_MONITOR(
                unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->egress_mirror_priority[i0],
                "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","egress_mirror_priority[%s%d]: ", s0, i0);

            DNX_SW_STATE_PRINT_OPAQUE_FILE(
                unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->egress_mirror_priority[i0],
                    "[%s%d]: ", s0, i0);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable snif_ingress_profiles_mirror
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_snif_ingress_profiles_mirror_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror snif_ingress_profiles_mirror") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror snif_ingress_profiles_mirror\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/snif_ingress_profiles_mirror.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_mirror: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_mirror: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_RES_MNGR_PRINT(
            unit,
            DNX_MIRROR_MODULE_ID,
            &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_profiles_mirror);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable snif_ingress_profiles_snoop
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_snif_ingress_profiles_snoop_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror snif_ingress_profiles_snoop") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror snif_ingress_profiles_snoop\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/snif_ingress_profiles_snoop.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_snoop: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_snoop: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_RES_MNGR_PRINT(
            unit,
            DNX_MIRROR_MODULE_ID,
            &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_profiles_snoop);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable snif_ingress_profiles_stat_sampling
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_snif_ingress_profiles_stat_sampling_dump(int  unit,  dnx_sw_state_dump_filters_t  filters)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_res_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror snif_ingress_profiles_stat_sampling") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror snif_ingress_profiles_stat_sampling\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/snif_ingress_profiles_stat_sampling.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_stat_sampling: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_PRINT_MONITOR(
            unit,
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_profiles_stat_sampling: ");

        DNX_SW_STATE_PRINT_FILE(
            unit,
            " ");

        DNX_ALGO_RES_MNGR_PRINT(
            unit,
            DNX_MIRROR_MODULE_ID,
            &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_profiles_stat_sampling);

        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable snif_egress_vlan_profiles_mirror
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_snif_egress_vlan_profiles_mirror_dump(int  unit,  int  snif_egress_vlan_profiles_mirror_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = snif_egress_vlan_profiles_mirror_idx_0, I0 = snif_egress_vlan_profiles_mirror_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror snif_egress_vlan_profiles_mirror") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror snif_egress_vlan_profiles_mirror\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/snif_egress_vlan_profiles_mirror.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_egress_vlan_profiles_mirror[]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror);

        if (i0 == -1) {
            I0 = dnx_sw_state_get_nof_elements(unit,
                DNX_MIRROR_MODULE_ID,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror);
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror
                , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror))
        {
            LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror[]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror) == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_egress_vlan_profiles_mirror[%s%d]: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            DNX_ALGO_TEMP_MNGR_PRINT(
                unit,
                DNX_MIRROR_MODULE_ID,
                &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_egress_vlan_profiles_mirror[i0],
                dnx_mirror_vlan_profile_print_cb);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable snif_ingress_vlan_profiles_mirror
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_snif_ingress_vlan_profiles_mirror_dump(int  unit,  int  snif_ingress_vlan_profiles_mirror_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = snif_ingress_vlan_profiles_mirror_idx_0, I0 = snif_ingress_vlan_profiles_mirror_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "dnx_algo_template_t") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror snif_ingress_vlan_profiles_mirror") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror snif_ingress_vlan_profiles_mirror\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/snif_ingress_vlan_profiles_mirror.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_vlan_profiles_mirror[]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror);

        if (i0 == -1) {
            I0 = dnx_sw_state_get_nof_elements(unit,
                DNX_MIRROR_MODULE_ID,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror);
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror
                , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror))
        {
            LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror[]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror) == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","snif_ingress_vlan_profiles_mirror[%s%d]: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            DNX_ALGO_TEMP_MNGR_PRINT(
                unit,
                DNX_MIRROR_MODULE_ID,
                &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->snif_ingress_vlan_profiles_mirror[i0],
                dnx_mirror_vlan_profile_print_cb);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 *
 * dump function for the variable mirror_on_drop_profile
 * AUTO-GENERATED - DO NOT MODIFY
 */
int
dnx_mirror_db_mirror_on_drop_profile_dump(int  unit,  int  mirror_on_drop_profile_idx_0,  dnx_sw_state_dump_filters_t  filters)
{
    int i0 = mirror_on_drop_profile_idx_0, I0 = mirror_on_drop_profile_idx_0 + 1;
    char *s0 = "";
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    if (dnx_sw_state_compare(filters.typefilter, "int") != TRUE)
    {
         SHR_EXIT();
    }

    if (dnx_sw_state_compare(filters.namefilter, "dnx_mirror mirror_on_drop_profile") != TRUE)
    {
         SHR_EXIT();
    }

    if (filters.nocontent)
    {
         DNX_SW_STATE_PRINT(unit, "swstate dnx_mirror mirror_on_drop_profile\n");
    }
    else
    {
        dnx_sw_state_dump_attach_file(
            unit,
            "dnx_mirror_db/mirror_on_drop_profile.txt",
            "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","mirror_on_drop_profile[]: ");

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID]));

        DNX_SW_STATE_DUMP_PTR_NULL_CHECK(
            unit,
            ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile);

        if (i0 == -1) {
            I0 = dnx_sw_state_get_nof_elements(unit,
                DNX_MIRROR_MODULE_ID,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile);
            i0 = dnx_sw_state_dump_check_all_the_same(unit,
                ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile
                , sizeof(*((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile), I0, &s0) ? I0 - 1 : 0;
        }

        if(i0 >= dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile))
        {
            LOG_CLI((BSL_META("dnx_mirror_db[]->((dnx_mirror_db_t*)sw_state_roots_array[][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile[]: ")));
            LOG_CLI((BSL_META("Invalid index: %d \n"),i0));
            SHR_EXIT();
        }

        if(dnx_sw_state_get_nof_elements(unit, DNX_MIRROR_MODULE_ID, ((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile) == 0)
        {
            SHR_EXIT();
        }

        for(; i0 < I0; i0++) {
            dnx_sw_state_dump_update_current_idx(unit, i0);
            DNX_SW_STATE_PRINT_MONITOR(
                unit,
                "dnx_mirror_db[%d]->","((dnx_mirror_db_t*)sw_state_roots_array[%d][DNX_MIRROR_MODULE_ID])->","mirror_on_drop_profile[%s%d]: ", s0, i0);

            DNX_SW_STATE_PRINT_FILE(
                unit,
                "[%s%d]: ", s0, i0);

            dnx_sw_state_print_int(
                unit,
                &((dnx_mirror_db_t*)sw_state_roots_array[unit][DNX_MIRROR_MODULE_ID])->mirror_on_drop_profile[i0]);

        }
        dnx_sw_state_dump_end_of_stride(unit);
        dnx_sw_state_dump_detach_file(
            unit);

    }

    DNXC_SW_STATE_FUNC_RETURN;
}



/*
 * Global Variables
 */

dnx_sw_state_diagnostic_info_t dnx_mirror_db_info[SOC_MAX_NUM_DEVICES][DNX_MIRROR_DB_INFO_NOF_ENTRIES];
const char* dnx_mirror_db_layout_str[DNX_MIRROR_DB_INFO_NOF_ENTRIES] = {
    "DNX_MIRROR_DB~",
    "DNX_MIRROR_DB~CHANNEL_TO_EGRESS_IF~",
    "DNX_MIRROR_DB~EGRESS_MIRROR_PRIORITY~",
    "DNX_MIRROR_DB~SNIF_INGRESS_PROFILES_MIRROR~",
    "DNX_MIRROR_DB~SNIF_INGRESS_PROFILES_SNOOP~",
    "DNX_MIRROR_DB~SNIF_INGRESS_PROFILES_STAT_SAMPLING~",
    "DNX_MIRROR_DB~SNIF_EGRESS_VLAN_PROFILES_MIRROR~",
    "DNX_MIRROR_DB~SNIF_INGRESS_VLAN_PROFILES_MIRROR~",
    "DNX_MIRROR_DB~MIRROR_ON_DROP_PROFILE~",
};
#endif /* DNX_SW_STATE_DIAGNOSTIC */
#undef BSL_LOG_MODULE
