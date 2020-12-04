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
/* Handler: bcm56780_a0_lta_bcmltx_sec_macsec_sectag_ethertype_sec_valid_table_entry_limit_handler */
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmsec/bcmltx_sec_valid_table_entry_limit.h>

static const bcmltd_generic_arg_t
bcm56780_a0_lta_bcmltx_sec_macsec_sectag_ethertype_sec_valid_comp_data = {
    .sid       = SEC_MACSEC_SECTAG_ETHERTYPEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

const bcmltd_table_entry_limit_handler_t
bcm56780_a0_lta_bcmltx_sec_macsec_sectag_ethertype_sec_valid_table_entry_limit_handler = {
    .entry_limit_get = bcmltx_sec_valid_table_entry_limit_get,
    .arg     = &bcm56780_a0_lta_bcmltx_sec_macsec_sectag_ethertype_sec_valid_comp_data
};


