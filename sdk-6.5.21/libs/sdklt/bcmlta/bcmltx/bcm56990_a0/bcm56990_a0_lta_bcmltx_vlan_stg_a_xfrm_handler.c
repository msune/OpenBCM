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
/* Handler: bcm56990_a0_lta_bcmltx_vlan_stg_a_xfrm_handler */
#include <bcmlrd/bcmlrd_types.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmltx/bcmvlan/bcmltx_vlan_stg_a.h>
#include <bcmdrd/chip/bcm56990_a0_enum.h>
#include <bcmlrd/chip/bcm56990_a0/bcm56990_a0_lrd_xfrm_field_desc.h>

extern const bcmltd_field_desc_t
bcm56990_a0_lrd_bcmltx_vlan_stg_a_src_field_desc_s0[];

extern const bcmltd_field_desc_t
bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_dst_field_desc_d0[];

static const
bcmltd_field_list_t
bcm56990_a0_lta_bcmltx_vlan_stg_a_src_list_s0 = {
    .field_num = 1,
    .field_array = bcm56990_a0_lrd_bcmltx_vlan_stg_a_src_field_desc_s0
};

static const bcmltd_field_list_t
bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_dst_list_d0 = {
    .field_num = 136,
    .field_array = bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_dst_field_desc_d0
};

static const uint32_t
bcm56990_a0_lta_bcmltx_vlan_stg_a_transform_src_s0[1] = {
    VLAN_STGt_STATEf,
};

static const uint32_t
bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_transform_dst_d0[136] = {
    SP_TREE_PORT0f,
    SP_TREE_PORT1f,
    SP_TREE_PORT2f,
    SP_TREE_PORT3f,
    SP_TREE_PORT4f,
    SP_TREE_PORT5f,
    SP_TREE_PORT6f,
    SP_TREE_PORT7f,
    SP_TREE_PORT8f,
    SP_TREE_PORT9f,
    SP_TREE_PORT10f,
    SP_TREE_PORT11f,
    SP_TREE_PORT12f,
    SP_TREE_PORT13f,
    SP_TREE_PORT14f,
    SP_TREE_PORT15f,
    SP_TREE_PORT16f,
    SP_TREE_PORT17f,
    SP_TREE_PORT18f,
    SP_TREE_PORT19f,
    SP_TREE_PORT20f,
    SP_TREE_PORT21f,
    SP_TREE_PORT22f,
    SP_TREE_PORT23f,
    SP_TREE_PORT24f,
    SP_TREE_PORT25f,
    SP_TREE_PORT26f,
    SP_TREE_PORT27f,
    SP_TREE_PORT28f,
    SP_TREE_PORT29f,
    SP_TREE_PORT30f,
    SP_TREE_PORT31f,
    SP_TREE_PORT32f,
    SP_TREE_PORT33f,
    SP_TREE_PORT34f,
    SP_TREE_PORT35f,
    SP_TREE_PORT36f,
    SP_TREE_PORT37f,
    SP_TREE_PORT38f,
    SP_TREE_PORT39f,
    SP_TREE_PORT40f,
    SP_TREE_PORT41f,
    SP_TREE_PORT42f,
    SP_TREE_PORT43f,
    SP_TREE_PORT44f,
    SP_TREE_PORT45f,
    SP_TREE_PORT46f,
    SP_TREE_PORT47f,
    SP_TREE_PORT48f,
    SP_TREE_PORT49f,
    SP_TREE_PORT50f,
    SP_TREE_PORT51f,
    SP_TREE_PORT52f,
    SP_TREE_PORT53f,
    SP_TREE_PORT54f,
    SP_TREE_PORT55f,
    SP_TREE_PORT56f,
    SP_TREE_PORT57f,
    SP_TREE_PORT58f,
    SP_TREE_PORT59f,
    SP_TREE_PORT60f,
    SP_TREE_PORT61f,
    SP_TREE_PORT62f,
    SP_TREE_PORT63f,
    SP_TREE_PORT64f,
    SP_TREE_PORT65f,
    SP_TREE_PORT66f,
    SP_TREE_PORT67f,
    SP_TREE_PORT68f,
    SP_TREE_PORT69f,
    SP_TREE_PORT70f,
    SP_TREE_PORT71f,
    SP_TREE_PORT72f,
    SP_TREE_PORT73f,
    SP_TREE_PORT74f,
    SP_TREE_PORT75f,
    SP_TREE_PORT76f,
    SP_TREE_PORT77f,
    SP_TREE_PORT78f,
    SP_TREE_PORT79f,
    SP_TREE_PORT80f,
    SP_TREE_PORT81f,
    SP_TREE_PORT82f,
    SP_TREE_PORT83f,
    SP_TREE_PORT84f,
    SP_TREE_PORT85f,
    SP_TREE_PORT86f,
    SP_TREE_PORT87f,
    SP_TREE_PORT88f,
    SP_TREE_PORT89f,
    SP_TREE_PORT90f,
    SP_TREE_PORT91f,
    SP_TREE_PORT92f,
    SP_TREE_PORT93f,
    SP_TREE_PORT94f,
    SP_TREE_PORT95f,
    SP_TREE_PORT96f,
    SP_TREE_PORT97f,
    SP_TREE_PORT98f,
    SP_TREE_PORT99f,
    SP_TREE_PORT100f,
    SP_TREE_PORT101f,
    SP_TREE_PORT102f,
    SP_TREE_PORT103f,
    SP_TREE_PORT104f,
    SP_TREE_PORT105f,
    SP_TREE_PORT106f,
    SP_TREE_PORT107f,
    SP_TREE_PORT108f,
    SP_TREE_PORT109f,
    SP_TREE_PORT110f,
    SP_TREE_PORT111f,
    SP_TREE_PORT112f,
    SP_TREE_PORT113f,
    SP_TREE_PORT114f,
    SP_TREE_PORT115f,
    SP_TREE_PORT116f,
    SP_TREE_PORT117f,
    SP_TREE_PORT118f,
    SP_TREE_PORT119f,
    SP_TREE_PORT120f,
    SP_TREE_PORT121f,
    SP_TREE_PORT122f,
    SP_TREE_PORT123f,
    SP_TREE_PORT124f,
    SP_TREE_PORT125f,
    SP_TREE_PORT126f,
    SP_TREE_PORT127f,
    SP_TREE_PORT128f,
    SP_TREE_PORT129f,
    SP_TREE_PORT130f,
    SP_TREE_PORT131f,
    SP_TREE_PORT132f,
    SP_TREE_PORT133f,
    SP_TREE_PORT134f,
    SP_TREE_PORT135f,
};

static const bcmltd_generic_arg_t
bcm56990_a0_lta_bcmltx_vlan_stg_a_comp_data = {
    .sid       = VLAN_STGt,
    .values    = 0,
    .value     = NULL,
    .user_data = NULL
};

static const bcmltd_transform_arg_t
bcm56990_a0_lta_bcmltx_vlan_stg_a_xfrm_handler_fwd_arg_s0_d0 = {
    .values      = 0,
    .value       = NULL,
    .tables      = 0,
    .table       = NULL,
    .fields      = 1,
    .field       = bcm56990_a0_lta_bcmltx_vlan_stg_a_transform_src_s0,
    .field_list  = &bcm56990_a0_lta_bcmltx_vlan_stg_a_src_list_s0,
    .rfields     = 136,
    .rfield      = bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_transform_dst_d0,
    .rfield_list = &bcm56990_a0_lrd_bcmltx_vlan_stg_a_vlan_stg_dst_list_d0,
    .comp_data   = &bcm56990_a0_lta_bcmltx_vlan_stg_a_comp_data
};

const bcmltd_xfrm_handler_t
bcm56990_a0_lta_bcmltx_vlan_stg_a_xfrm_handler_fwd_s0_d0 = {
    .transform     = bcmltx_vlan_stg_a_transform,
    .arg           = &bcm56990_a0_lta_bcmltx_vlan_stg_a_xfrm_handler_fwd_arg_s0_d0
};


