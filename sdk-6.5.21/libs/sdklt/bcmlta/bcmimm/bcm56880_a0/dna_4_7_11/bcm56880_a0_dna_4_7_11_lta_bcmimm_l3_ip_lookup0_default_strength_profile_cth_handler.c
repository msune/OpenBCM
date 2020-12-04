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
/* Logical Table Adaptor for component bcmimm */
/* Handler: bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler */
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmimm/bcmimm_basic.h>

static const bcmltd_table_ha_handler_t
bcmimm_basic_ha_handler = {
    .commit = bcmimm_basic_commit,
    .abort  = bcmimm_basic_abort
};



const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler_arg = {
    .sid = BCM56880_A0_DNA_4_7_11_L3_IP_LOOKUP0_DEFAULT_STRENGTH_PROFILEt,
    .values = 0,
    .value = NULL,
    .user_data = NULL
};

static const bcmltd_table_entry_limit_handler_t
bcmimm_basic_table_entry_limit_handler = {
    .entry_limit_get = bcmimm_basic_table_entry_limit_get,
    .arg  = &bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler_arg
};


static const bcmltd_table_entry_usage_handler_t
bcmimm_basic_table_entry_usage_handler = {
    .entry_inuse_get = bcmimm_basic_table_entry_inuse_get,
    .max_entries_set = bcmimm_basic_table_max_entries_set,
    .arg  = &bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler_arg
};


const bcmltd_table_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler = {
    .validate = bcmimm_basic_validate,
    .op_insert_alloc = bcmimm_basic_insert_alloc,
    .op_lookup       = bcmimm_basic_lookup,
    .op_delete       = bcmimm_basic_delete,
    .op_update       = bcmimm_basic_update,
    .op_first        = bcmimm_basic_first,
    .op_next         = bcmimm_basic_next,
    .ha       = &bcmimm_basic_ha_handler,
    .entry_limit = &bcmimm_basic_table_entry_limit_handler,
    .entry_usage = &bcmimm_basic_table_entry_usage_handler,
    .arg      = &bcm56880_a0_dna_4_7_11_lta_bcmimm_l3_ip_lookup0_default_strength_profile_cth_handler_arg
};

