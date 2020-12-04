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
/* Handler: bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_fv_handler */
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmdrd/chip/bcm56990_b0_enum.h>
#include <bcmltx/general/bcmltx_pipe_validate.h>

static const uint32_t
bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_validate_arg0[1] = {
    LPORT_TABm,
};

static const uint32_t
bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_validate_src[1] = {
    PORT_SYSTEM_PVLAN_PROFILEt_PIPEf,
};

static const bcmltd_generic_arg_t
bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_comp_data = {
    .sid       = PORT_SYSTEM_PVLAN_PROFILEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

const bcmltd_field_val_arg_t
bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_fv_handler_arg_v0 = {
    .values = 1,
    .value = bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_validate_arg0,
    .fields = 1,
    .field = bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_validate_src,
    .comp_data = &bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_comp_data
};

const bcmltd_field_val_handler_t
bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_fv_handler_v0 = {
    .validate = bcmltx_pipe_validate,
    .arg      = &bcm56990_b0_lta_bcmltx_port_system_pvlan_profile_pipe_fv_handler_arg_v0
};


