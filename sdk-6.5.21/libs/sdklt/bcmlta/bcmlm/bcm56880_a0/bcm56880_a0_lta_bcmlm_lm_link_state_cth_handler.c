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
/* Logical Table Adaptor for component bcmlm */
/* Handler: bcm56880_a0_lta_bcmlm_lm_link_state_cth_handler */
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmlm/bcmlm_cth_link_state.h>



const bcmltd_generic_arg_t
bcm56880_a0_lta_bcmlm_lm_link_state_cth_handler_arg = {
    .sid = LM_LINK_STATEt,
    .values = 0,
    .value = NULL,
    .user_data = NULL
};

const bcmltd_table_handler_t
bcm56880_a0_lta_bcmlm_lm_link_state_cth_handler = {
    .validate = bcmlm_cth_link_state_validate,
    .op_insert       = bcmlm_cth_link_state_insert,
    .op_lookup       = bcmlm_cth_link_state_lookup,
    .op_delete       = bcmlm_cth_link_state_delete,
    .op_update       = bcmlm_cth_link_state_update,
    .op_first        = bcmlm_cth_link_state_first,
    .op_next         = bcmlm_cth_link_state_next,
    .ha       = NULL,
    .arg      = &bcm56880_a0_lta_bcmlm_lm_link_state_cth_handler_arg
};

