/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/mbcm/mpls.h>
#include <bcm_int/ltsw/xfs/mpls.h>
#include <bcm_int/ltsw/chip/bcm56880_a0/variant_dispatch.h>

#include <shr/shr_bitop.h>
#include <shr/shr_debug.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_MPLS

/******************************************************************************
 * Private functions
 */

static int
bcm56880_a0_ltsw_mpls_sw_dump(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_sw_dump(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_init(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_detach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_detach(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_switch_add(
    int unit,
    bcm_mpls_tunnel_switch_t *info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_switch_add(unit, info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_switch_delete(
    int unit,
    bcm_mpls_tunnel_switch_t *info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_switch_delete(unit, info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_switch_get(
    int unit,
    bcm_mpls_tunnel_switch_t *info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_switch_get(unit, info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_switch_traverse(
    int unit,
    bcm_mpls_tunnel_switch_traverse_cb cb,
    void *user_data)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_switch_traverse(unit, cb, user_data));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_switch_delete_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_switch_delete_all(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_encap_create(
    int unit,
    uint32_t options,
    bcm_mpls_tunnel_encap_t *tunnel_encap)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_encap_create(unit, options, tunnel_encap));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_encap_get(
    int unit,
    bcm_mpls_tunnel_encap_t *tunnel_encap)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_encap_get(unit, tunnel_encap));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_encap_destroy(
    int unit,
    bcm_gport_t tunnel_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_encap_destroy(unit, tunnel_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_tnl_encap_destroy_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_tnl_encap_destroy_all(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vfi_op(
    int unit,
    bcmlt_opcode_t opcode,
    int vfi_idx,
    bcm_mpls_vpn_config_t *info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vfi_op(unit, opcode, vfi_idx, info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vpws_info_get(
    int unit,
    int *idx_min,
    int *idx_max)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vpws_info_get(unit, idx_min, idx_max));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_add(
    int unit,
    bcm_vpn_t vpn,
    bcm_mpls_port_t *mpls_port)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_add(unit, vpn, mpls_port));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_get(
    int unit,
    bcm_vpn_t vpn,
    bcm_gport_t mpls_port_id,
    bcm_mpls_port_t *mpls_port)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_get(unit, vpn, mpls_port_id, mpls_port));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vpls_port_get_all(
    int unit,
    bcm_vpn_t vpn,
    int port_max,
    bcm_mpls_port_t *port_array,
    int *port_count)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vpls_port_get_all(unit, vpn, port_max, port_array, port_count));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_delete(
    int unit,
    bcm_vpn_t vpn,
    bcm_gport_t mpls_port_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_delete(unit, vpn, mpls_port_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vpls_port_delete_by_vpn(
    int unit,
    bcm_vpn_t vpn)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vpls_port_delete_by_vpn(unit, vpn));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vpls_port_delete_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vpls_port_delete_all(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_attach(
    int unit,
    bcm_gport_t src_port_id,
    bcm_gport_t dst_port_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_attach(unit, src_port_id, dst_port_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_detach(
    int unit,
    bcm_gport_t mpls_port_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_detach(unit, mpls_port_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_validate(
    int unit,
    bcm_gport_t mpls_port_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_validate(unit, mpls_port_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_vlan_list_get(
    int unit,
    int *vlan_cnt,
    int *vlan_list)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_vlan_list_get(unit, vlan_cnt, vlan_list));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_special_label_identifier_add(
    int unit,
    bcm_mpls_special_label_t label_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_special_label_identifier_add(unit, label_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_special_label_identifier_get(
    int unit,
    bcm_mpls_special_label_t *label_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_special_label_identifier_get(unit, label_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_special_label_identifier_delete(
    int unit,
    bcm_mpls_special_label_t label_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_special_label_identifier_delete(unit, label_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_special_label_identifier_delete_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_special_label_identifier_delete_all(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_special_label_identifier_traverse(
    int unit,
    bcm_mpls_special_label_identifier_traverse_cb cb,
    void *user_data)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_special_label_identifier_traverse(unit, cb, user_data));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_global_label_range_set(
    int unit,
    int range_num,
    int range_min,
    int label_val)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_global_label_range_set(unit, range_num, range_min, label_val));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_global_label_range_get(
    int unit,
    int range_num,
    int *min_label,
    int *max_label)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_global_label_range_get(unit, range_num, min_label, max_label));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_global_control_set(
    int unit,
    bcmi_ltsw_mpls_global_ctrl_t control_type,
    int value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_global_control_set(unit, control_type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_global_control_get(
    int unit,
    bcmi_ltsw_mpls_global_ctrl_t control_type,
    int *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_global_control_get(unit, control_type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_encap_label_add(
    int unit,
    bcmi_ltsw_mpls_encap_label_info_t *label_info,
    int *label_index)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_encap_label_add(unit, label_info, label_index));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_encap_label_get(
    int unit,
    int label_index,
    bcmi_ltsw_mpls_encap_label_info_t *label_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_encap_label_get(unit, label_index, label_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_encap_label_delete(
    int unit,
    int label_index)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_encap_label_delete(unit, label_index));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_encap_label_ref_inc(
    int unit,
    int label_index)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_encap_label_ref_inc(unit, label_index));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_vp_replace(
    int unit,
    bcm_gport_t mpls_port_id,
    int new_vp)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_vp_replace(unit, mpls_port_id, new_vp));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_vp_get(
    int unit,
    bcm_gport_t mpls_port_id,
    int *new_vp)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_vp_get(unit, mpls_port_id, new_vp));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_control_pkt_add(
    int unit,
    uint32_t options,
    bcm_mpls_control_pkt_match_t *match,
    bcm_mpls_control_pkt_action_t *action)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_control_pkt_add(unit, options, match, action));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_control_pkt_get(
    int unit,
    bcm_mpls_control_pkt_match_t *match,
    bcm_mpls_control_pkt_action_t *action)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_control_pkt_get(unit, match, action));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_control_pkt_delete(
    int unit,
    bcm_mpls_control_pkt_match_t *match)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_control_pkt_delete(unit, match));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_control_pkt_traverse(
    int unit,
    bcm_mpls_control_pkt_traverse_cb cb,
    void *user_data)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_control_pkt_traverse(unit, cb, user_data));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_control_pkt_delete_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_control_pkt_delete_all(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_label_stat_get(
    int unit,
    bcm_mpls_label_t label,
    bcm_gport_t mpls_port,
    bcm_mpls_stat_t stat,
    uint64_t *val)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_label_stat_get(unit, label, mpls_port, stat, val));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_label_stat_clear(
    int unit,
    bcm_mpls_label_t label,
    bcm_gport_t mpls_port,
    bcm_mpls_stat_t stat)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_label_stat_clear(unit, label, mpls_port, stat));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_set(
    int unit,
    bcm_gport_t mpls_port_id,
    bcmi_ltsw_mpls_port_match_t *match)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_set(unit, mpls_port_id, match));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_clear(
    int unit,
    bcm_gport_t mpls_port_id,
    bcmi_ltsw_mpls_port_match_t *match)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_clear(unit, mpls_port_id, match));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_multi_get(
    int unit,
    bcm_gport_t mpls_port_id,
    int size,
    bcmi_ltsw_mpls_port_match_t *match_array,
    int *count)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_multi_get(unit, mpls_port_id, size, match_array, count));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_mpls_port_match_delete_all(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_mpls_port_match_delete_all(unit));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Mpls driver function variable for bcm56880_a0 device.
 */
static mbcm_ltsw_mpls_drv_t bcm56880_a0_ltsw_mpls_drv = {
    .mpls_sw_dump = bcm56880_a0_ltsw_mpls_sw_dump,
    .mpls_init = bcm56880_a0_ltsw_mpls_init,
    .mpls_detach = bcm56880_a0_ltsw_mpls_detach,
    .mpls_tnl_switch_add = bcm56880_a0_ltsw_mpls_tnl_switch_add,
    .mpls_tnl_switch_delete = bcm56880_a0_ltsw_mpls_tnl_switch_delete,
    .mpls_tnl_switch_get = bcm56880_a0_ltsw_mpls_tnl_switch_get,
    .mpls_tnl_switch_traverse = bcm56880_a0_ltsw_mpls_tnl_switch_traverse,
    .mpls_tnl_switch_delete_all = bcm56880_a0_ltsw_mpls_tnl_switch_delete_all,
    .mpls_tnl_encap_create = bcm56880_a0_ltsw_mpls_tnl_encap_create,
    .mpls_tnl_encap_get = bcm56880_a0_ltsw_mpls_tnl_encap_get,
    .mpls_tnl_encap_destroy = bcm56880_a0_ltsw_mpls_tnl_encap_destroy,
    .mpls_tnl_encap_destroy_all = bcm56880_a0_ltsw_mpls_tnl_encap_destroy_all,
    .mpls_vfi_op = bcm56880_a0_ltsw_mpls_vfi_op,
    .mpls_vpws_info_get = bcm56880_a0_ltsw_mpls_vpws_info_get,
    .mpls_port_add = bcm56880_a0_ltsw_mpls_port_add,
    .mpls_port_get = bcm56880_a0_ltsw_mpls_port_get,
    .mpls_vpls_port_get_all = bcm56880_a0_ltsw_mpls_vpls_port_get_all,
    .mpls_port_delete = bcm56880_a0_ltsw_mpls_port_delete,
    .mpls_vpls_port_delete_by_vpn = bcm56880_a0_ltsw_mpls_vpls_port_delete_by_vpn,
    .mpls_vpls_port_delete_all = bcm56880_a0_ltsw_mpls_vpls_port_delete_all,
    .mpls_port_attach = bcm56880_a0_ltsw_mpls_port_attach,
    .mpls_port_detach = bcm56880_a0_ltsw_mpls_port_detach,
    .mpls_port_validate = bcm56880_a0_ltsw_mpls_port_validate,
    .mpls_vlan_list_get = bcm56880_a0_ltsw_mpls_vlan_list_get,
    .mpls_special_label_identifier_add = bcm56880_a0_ltsw_mpls_special_label_identifier_add,
    .mpls_special_label_identifier_get = bcm56880_a0_ltsw_mpls_special_label_identifier_get,
    .mpls_special_label_identifier_delete = bcm56880_a0_ltsw_mpls_special_label_identifier_delete,
    .mpls_special_label_identifier_delete_all = bcm56880_a0_ltsw_mpls_special_label_identifier_delete_all,
    .mpls_special_label_identifier_traverse = bcm56880_a0_ltsw_mpls_special_label_identifier_traverse,
    .mpls_global_label_range_set = bcm56880_a0_ltsw_mpls_global_label_range_set,
    .mpls_global_label_range_get = bcm56880_a0_ltsw_mpls_global_label_range_get,
    .mpls_global_control_set = bcm56880_a0_ltsw_mpls_global_control_set,
    .mpls_global_control_get = bcm56880_a0_ltsw_mpls_global_control_get,
    .mpls_encap_label_add = bcm56880_a0_ltsw_mpls_encap_label_add,
    .mpls_encap_label_get = bcm56880_a0_ltsw_mpls_encap_label_get,
    .mpls_encap_label_delete = bcm56880_a0_ltsw_mpls_encap_label_delete,
    .mpls_encap_label_ref_inc = bcm56880_a0_ltsw_mpls_encap_label_ref_inc,
    .mpls_port_match_vp_replace = bcm56880_a0_ltsw_mpls_port_match_vp_replace,
    .mpls_port_match_vp_get = bcm56880_a0_ltsw_mpls_port_match_vp_get,
    .mpls_control_pkt_add = bcm56880_a0_ltsw_mpls_control_pkt_add,
    .mpls_control_pkt_get = bcm56880_a0_ltsw_mpls_control_pkt_get,
    .mpls_control_pkt_delete = bcm56880_a0_ltsw_mpls_control_pkt_delete,
    .mpls_control_pkt_traverse = bcm56880_a0_ltsw_mpls_control_pkt_traverse,
    .mpls_control_pkt_delete_all = bcm56880_a0_ltsw_mpls_control_pkt_delete_all,
    .mpls_label_stat_get = bcm56880_a0_ltsw_mpls_label_stat_get,
    .mpls_label_stat_clear = bcm56880_a0_ltsw_mpls_label_stat_clear,
    .mpls_port_match_set = bcm56880_a0_ltsw_mpls_port_match_set,
    .mpls_port_match_clear = bcm56880_a0_ltsw_mpls_port_match_clear,
    .mpls_port_match_multi_get = bcm56880_a0_ltsw_mpls_port_match_multi_get,
    .mpls_port_match_delete_all = bcm56880_a0_ltsw_mpls_port_match_delete_all,
};

/******************************************************************************
 * Public functions
 */

int
bcm56880_a0_ltsw_mpls_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_mpls_drv_set(unit, &bcm56880_a0_ltsw_mpls_drv));

    SHR_IF_ERR_VERBOSE_EXIT
        (bcm56880_a0_ltsw_variant_drv_attach(unit, BCM56880_A0_LTSW_VARIANT_MPLS));

exit:
    SHR_FUNC_EXIT();
}

