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
/* Handler: bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_fv_handler */
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmdrd/chip/bcm56880_a0_enum.h>
#include <bcmltx/bcmltx_std_table_validator.h>

static const uint32_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_validate_src[4] = {
    BCM56880_A0_DNA_4_7_11_DT_EM_FP_RULE_TEMPLATEt_PKT_ALT_FIELD_BUS_IP_HDR_DIPf,
    BCM56880_A0_DNA_4_7_11_DT_EM_FP_RULE_TEMPLATEt_PKT_FWD_FIELD_BUS_IP_HDR_SIPf,
    BCM56880_A0_DNA_4_7_11_DT_EM_FP_RULE_TEMPLATEt_PKT_ALT_FIELD_BUS_IP_HDR_SIPf,
    BCM56880_A0_DNA_4_7_11_DT_EM_FP_RULE_TEMPLATEt_PKT_FWD_FIELD_BUS_IP_HDR_DIPf,
};

static const bcmltd_generic_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_comp_data = {
    .sid       = BCM56880_A0_DNA_4_7_11_DT_EM_FP_RULE_TEMPLATEt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

const bcmltd_field_val_arg_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_fv_handler_arg = {
    .values = 0,
    .value = NULL,
    .fields = 4,
    .field = bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_validate_src,
    .comp_data = &bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_comp_data
};

const bcmltd_field_val_handler_t
bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_fv_handler = {
    .validate = bcmltx_std_table_validator,
    .arg      = &bcm56880_a0_dna_4_7_11_lta_bcmltx_dt_em_fp_rule_template_std_val_fv_handler_arg
};


