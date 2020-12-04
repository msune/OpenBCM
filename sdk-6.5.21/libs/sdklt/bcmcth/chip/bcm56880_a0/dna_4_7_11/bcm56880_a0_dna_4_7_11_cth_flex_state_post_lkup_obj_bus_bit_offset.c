/*****************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by xfc_map_parser
 * from the NPL output file(s)  sw_hcf.yml bus_be_output.yml map.yml.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 *
 * Tool Path: $SDK/INTERNAL/fltg/xfc_map_parser
 */


#include "bcm56880_a0_dna_4_7_11_cth_flex_state_post_lkup_obj_bus_bit_offset.h"

const bcmcth_ctr_eflex_obj_bit_offset_t *
bcm56880_a0_dna_4_7_11_flex_state_post_lkup_obj_bus_bit_offset_get(int index)
{
    const bcmcth_ctr_eflex_obj_bit_offset_t *obj_bit_offset = NULL;

    if (index < BCM56880_A0_DNA_4_7_11_FLEX_STATE_POST_LKUP_OBJ_BUS_BIT_OFFSET_MAX_COUNT) {
        obj_bit_offset = &bcm56880_a0_dna_4_7_11_flex_state_post_lkup_obj_bus_bit_offset[index];
    }

    return obj_bit_offset;
}
