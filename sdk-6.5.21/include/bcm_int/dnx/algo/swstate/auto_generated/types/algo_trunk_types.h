/** \file algo/swstate/auto_generated/types/algo_trunk_types.h
 *
 * sw state types (structs/enums/typedefs)
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

#ifndef __ALGO_TRUNK_TYPES_H__
#define __ALGO_TRUNK_TYPES_H__

#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr_internal.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
#include <bcm_int/dnx/algo/trunk/algo_trunk.h>
#include <include/soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
/*
 * STRUCTs
 */

/**
 * group info in algo trunk module
 */
typedef struct {
    /**
     * resource manager for SPA member ids per group
     */
    dnx_algo_res_t spa_id_manager;
    /**
     * resource manager for tm indexes per group
     */
    dnx_algo_res_t tm_index_manager;
} algo_trunk_group_info_t;

/**
 * pool info in algo trunk module
 */
typedef struct {
    /**
     * groups in trunk pool
     */
    algo_trunk_group_info_t* groups;
} algo_trunk_pool_info_t;

/**
 * Trunk related sw state
 */
typedef struct {
    /**
     * Egress Trunk
     */
    dnx_algo_template_t egress_trunk;
    /**
     * pools in algo trunk module
     */
    algo_trunk_pool_info_t* pools;
    /**
     * psc profiles
     */
    dnx_algo_template_t psc_profiles;
} algo_trunk_sw_state_t;


#endif /* __ALGO_TRUNK_TYPES_H__ */
