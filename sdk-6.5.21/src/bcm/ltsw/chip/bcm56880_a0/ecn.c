/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/mbcm/ecn.h>
#include <bcm_int/ltsw/xfs/ecn.h>
#include <bcm_int/ltsw/lt_intf.h>
#include <bcm_int/ltsw/dev.h>

#include <shr/shr_debug.h>
#include <bcmltd/chip/bcmltd_str.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_COSQ

/******************************************************************************
 * Private functions
 */


#define XFS_ECN_TRAFFIC_NON_TNL_STR {\
    FLEX_QOS_QOS_L3_IIF_DSCP_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_DSCP_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_IDOT1P_CFI_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_ODOT1P_CFI_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_DSCP_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_IDOT1P_CFI_NON_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_ODOT1P_CFI_NON_TUNNEL_ECN_INDEXs \
}

#define XFS_ECN_TRAFFIC_L2_TNL_STR {\
    FLEX_QOS_QOS_MPLS_EXP_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L3_IIF_DSCP_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_DSCP_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_IDOT1P_CFI_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_ODOT1P_CFI_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_DSCP_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_IDOT1P_CFI_L2_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_ODOT1P_CFI_L2_TUNNEL_ECN_INDEXs \
}

#define XFS_ECN_TRAFFIC_L3_TNL_STR {\
    FLEX_QOS_QOS_MPLS_EXP_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L3_IIF_DSCP_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_DSCP_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_IDOT1P_CFI_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_SVP_ODOT1P_CFI_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_DSCP_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_IDOT1P_CFI_L3_TUNNEL_ECN_INDEXs, \
    FLEX_QOS_QOS_L2_IIF_ODOT1P_CFI_L3_TUNNEL_ECN_INDEXs \
}

#define XFS_ECN_TRAFFIC_MPLS_STR {\
    FLEX_QOS_QOS_MPLS_EXP_MPLS_ECN_INDEXs, \
    FLEX_QOS_QOS_L3_IIF_DSCP_MPLS_ECN_INDEXs, \
}

static const char *xfs_ecn_traffic_non_tnl_str[] = XFS_ECN_TRAFFIC_NON_TNL_STR;
static const char *xfs_ecn_traffic_l2_tnl_str[] = XFS_ECN_TRAFFIC_L2_TNL_STR;
static const char *xfs_ecn_traffic_l3_tnl_str[] = XFS_ECN_TRAFFIC_L3_TNL_STR;
static const char *xfs_ecn_traffic_mpls_str[] = XFS_ECN_TRAFFIC_MPLS_STR;
#define XFS_ECN_TRAFFIC_NON_TNL_BASE_PTR 0
#define XFS_ECN_TRAFFIC_L2_TNL_BASE_PTR  1
#define XFS_ECN_TRAFFIC_L3_TNL_BASE_PTR  2
#define XFS_ECN_TRAFFIC_MPLS_BASE_PTR    3

static int
bcm56880_a0_ltsw_ecn_sfc_qos_phb_setup(int unit)
{
    bcmlt_entry_handle_t entry_hdl = BCMLT_INVALID_HDL;
    int idx, entry_num;
    int dunit;

    SHR_FUNC_ENTER(unit);

    dunit = bcmi_ltsw_dev_dunit(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (bcmlt_entry_allocate(dunit, FLEX_QOS_ING_POLICYs, &entry_hdl));

    /* Initialize ingress ECN mapping base ptrs for non-tunnel traffic. */
    entry_num = (sizeof(xfs_ecn_traffic_non_tnl_str)
                    / sizeof(xfs_ecn_traffic_non_tnl_str[0]));
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmlt_entry_field_add(entry_hdl, INT_CN_MAPPING_PTRs,
                               XFS_ECN_TRAFFIC_NON_TNL_BASE_PTR));
    for (idx = 0; idx < entry_num; idx++) {
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmlt_entry_field_symbol_add(entry_hdl, FLEX_QOS_ING_POLICY_IDs,
                                          xfs_ecn_traffic_non_tnl_str[idx]));
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmi_lt_entry_set_commit(unit, entry_hdl, BCMLT_PRIORITY_NORMAL));
    }

    /* Initialize ingress ECN mapping base ptrs for L2-tunnel traffic. */
    entry_num = (sizeof(xfs_ecn_traffic_l2_tnl_str)
                    / sizeof(xfs_ecn_traffic_l2_tnl_str[0]));
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmlt_entry_field_add(entry_hdl, INT_CN_MAPPING_PTRs,
                               XFS_ECN_TRAFFIC_L2_TNL_BASE_PTR));
    for (idx = 0; idx < entry_num; idx++) {
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmlt_entry_field_symbol_add(entry_hdl, FLEX_QOS_ING_POLICY_IDs,
                                          xfs_ecn_traffic_l2_tnl_str[idx]));
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmi_lt_entry_set_commit(unit, entry_hdl, BCMLT_PRIORITY_NORMAL));
    }

    /* Initialize ingress ECN mapping base ptrs for L3-tunnel traffic. */
    entry_num = (sizeof(xfs_ecn_traffic_l3_tnl_str)
                    / sizeof(xfs_ecn_traffic_l3_tnl_str[0]));
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmlt_entry_field_add(entry_hdl, INT_CN_MAPPING_PTRs,
                               XFS_ECN_TRAFFIC_L3_TNL_BASE_PTR));
    for (idx = 0; idx < entry_num; idx++) {
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmlt_entry_field_symbol_add(entry_hdl, FLEX_QOS_ING_POLICY_IDs,
                                          xfs_ecn_traffic_l3_tnl_str[idx]));
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmi_lt_entry_set_commit(unit, entry_hdl, BCMLT_PRIORITY_NORMAL));
    }

    /* Initialize ingress ECN mapping base ptrs for MPLS traffic. */
    entry_num = (sizeof(xfs_ecn_traffic_mpls_str)
                    / sizeof(xfs_ecn_traffic_mpls_str[0]));
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmlt_entry_field_add(entry_hdl, INT_CN_MAPPING_PTRs,
                               XFS_ECN_TRAFFIC_MPLS_BASE_PTR));
    for (idx = 0; idx < entry_num; idx++) {
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmlt_entry_field_symbol_add(entry_hdl, FLEX_QOS_ING_POLICY_IDs,
                                          xfs_ecn_traffic_mpls_str[idx]));
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmi_lt_entry_set_commit(unit, entry_hdl, BCMLT_PRIORITY_NORMAL));
    }

exit:
    if (entry_hdl != BCMLT_INVALID_HDL) {
        (void)bcmlt_entry_free(entry_hdl);
        entry_hdl = BCMLT_INVALID_HDL;
    }

    SHR_FUNC_EXIT();
}


static int
bcm56880_a0_ltsw_ecn_deinit(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_deinit(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_init(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_create(
    int unit,
    uint32_t flags,
    int *ecn_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_create(unit, flags, ecn_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_destroy(
    int unit,
    int ecn_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_destroy(unit, ecn_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_set(
    int unit,
    uint32_t options,
    int ecn_map_id,
    bcm_ecn_map_t *ecn_map)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_set(unit, options, ecn_map_id, ecn_map));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_get(
    int unit,
    int ecn_map_id,
    bcm_ecn_map_t *ecn_map)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_get(unit, ecn_map_id, ecn_map));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_latency_based_mode_set(
    int unit,
    bcm_switch_latency_ecn_mark_mode_t mode)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_latency_based_mode_set(unit, mode));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_latency_based_mode_get(
    int unit,
    bcm_switch_latency_ecn_mark_mode_t *mode)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_latency_based_mode_get(unit, mode));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_latency_based_threshold_set(
    int unit,
    bcm_gport_t gport,
    bcm_cos_queue_t cosq,
    bcm_switch_latency_ecn_mark_mode_t mode,
    uint32_t threshold)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_latency_based_threshold_set(unit, gport, cosq, mode, threshold));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_latency_based_threshold_get(
    int unit,
    bcm_gport_t gport,
    bcm_cos_queue_t cosq,
    bcm_switch_latency_ecn_mark_mode_t mode,
    uint32_t *threshold)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_latency_based_threshold_get(unit, gport, cosq, mode, threshold));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_id_resolve(
    int unit,
    int ecn_map_id,
    int *ecn_map_type,
    uint32_t *prof_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_id_resolve(unit, ecn_map_id, ecn_map_type, prof_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_map_id_construct(
    int unit,
    int ecn_map_type,
    uint32_t prof_id,
    int *ecn_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_map_id_construct(unit, ecn_map_type, prof_id, ecn_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_traffic_map_set(
    int unit,
    bcm_ecn_traffic_map_info_t *map)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_traffic_map_set(unit, map));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_traffic_map_get(
    int unit,
    bcm_ecn_traffic_map_info_t *map)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_traffic_map_get(unit, map));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_action_enqueue_set(
    int unit,
    bcm_ecn_traffic_action_config_t *ecn_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_action_enqueue_set(unit, ecn_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_action_enqueue_get(
    int unit,
    bcm_ecn_traffic_action_config_t *ecn_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_action_enqueue_get(unit, ecn_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_action_dequeue_set(
    int unit,
    bcm_ecn_traffic_action_config_t *ecn_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_action_dequeue_set(unit, ecn_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_action_dequeue_get(
    int unit,
    bcm_ecn_traffic_action_config_t *ecn_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_action_dequeue_get(unit, ecn_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_responsive_default_set(
    int unit,
    int value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_responsive_default_set(unit, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56880_a0_ltsw_ecn_responsive_default_get(
    int unit,
    int *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_ecn_responsive_default_get(unit, value));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Ecn driver function variable for bcm56880_a0 device.
 */
static mbcm_ltsw_ecn_drv_t bcm56880_a0_ltsw_ecn_drv = {
    .ecn_deinit = bcm56880_a0_ltsw_ecn_deinit,
    .ecn_init = bcm56880_a0_ltsw_ecn_init,
    .ecn_map_create = bcm56880_a0_ltsw_ecn_map_create,
    .ecn_map_destroy = bcm56880_a0_ltsw_ecn_map_destroy,
    .ecn_map_set = bcm56880_a0_ltsw_ecn_map_set,
    .ecn_map_get = bcm56880_a0_ltsw_ecn_map_get,
    .ecn_latency_based_mode_set = bcm56880_a0_ltsw_ecn_latency_based_mode_set,
    .ecn_latency_based_mode_get = bcm56880_a0_ltsw_ecn_latency_based_mode_get,
    .ecn_latency_based_threshold_set = bcm56880_a0_ltsw_ecn_latency_based_threshold_set,
    .ecn_latency_based_threshold_get = bcm56880_a0_ltsw_ecn_latency_based_threshold_get,
    .ecn_map_id_resolve = bcm56880_a0_ltsw_ecn_map_id_resolve,
    .ecn_map_id_construct = bcm56880_a0_ltsw_ecn_map_id_construct,
    .ecn_traffic_map_set = bcm56880_a0_ltsw_ecn_traffic_map_set,
    .ecn_traffic_map_get = bcm56880_a0_ltsw_ecn_traffic_map_get,
    .ecn_action_enqueue_set = bcm56880_a0_ltsw_ecn_action_enqueue_set,
    .ecn_action_enqueue_get = bcm56880_a0_ltsw_ecn_action_enqueue_get,
    .ecn_action_dequeue_set = bcm56880_a0_ltsw_ecn_action_dequeue_set,
    .ecn_action_dequeue_get = bcm56880_a0_ltsw_ecn_action_dequeue_get,
    .ecn_responsive_default_set = bcm56880_a0_ltsw_ecn_responsive_default_set,
    .ecn_responsive_default_get = bcm56880_a0_ltsw_ecn_responsive_default_get,
    .ecn_sfc_qos_phb_setup = bcm56880_a0_ltsw_ecn_sfc_qos_phb_setup
};

/******************************************************************************
 * Public functions
 */

int
bcm56880_a0_ltsw_ecn_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_ecn_drv_set(unit, &bcm56880_a0_ltsw_ecn_drv));

exit:
    SHR_FUNC_EXIT();
}

