/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/mbcm/dlb.h>
#include <bcm_int/ltsw/xfs/dlb.h>
#include <bcm_int/ltsw/dlb.h>
#include <bcm_int/ltsw/lt_intf.h>

#include <shr/shr_debug.h>
#include <bcmltd/chip/bcmltd_str.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_DLB

/******************************************************************************
 * Private functions
 */

static int
bcm56780_a0_ltsw_dlb_feature_get(
    int unit,
    uint32_t *features)
{
    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(features, SHR_E_PARAM);

    *features = 0;
    *features |= BCMI_LTSW_DLB_F_FP_TRUNK;
    *features |= BCMI_LTSW_DLB_F_FABRIC_TRUNK;
    *features |= BCMI_LTSW_DLB_F_ECMP;
    *features |= BCMI_LTSW_DLB_F_TRUNK_DGM;
    *features |= BCMI_LTSW_DLB_F_ECMP_DGM;
    *features |= BCMI_LTSW_DLB_F_TRUNK_SHARED;

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_capability_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_capability_t *cap)
{
    uint64_t min, max;

    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(cap, SHR_E_PARAM);

    switch(dlb_type) {
        case bcmi_dlb_type_fp_trunk:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, DLB_IDs,
                                               &min, &max));
            cap->id_min = (int)min;
            cap->id_max = (int)max;
            cap->max_groups = cap->id_max - cap->id_min + 1;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, NUM_PATHSs,
                                               &min, &max));
            cap->max_members_per_group = (int)max;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, ALTERNATE_NUM_PATHSs,
                                               &min, &max));
            cap->max_alt_members_per_group = (int)max;
            break;
        case bcmi_dlb_type_fabric_trunk:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, DLB_IDs,
                                               &min, &max));
            cap->id_min = (int)min;
            cap->id_max = (int)max;
            cap->max_groups = cap->id_max - cap->id_min + 1;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, NUM_PATHSs,
                                               &min, &max));
            cap->max_members_per_group = (int)max;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_TRUNKs, ALTERNATE_NUM_PATHSs,
                                               &min, &max));
            cap->max_alt_members_per_group = (int)max;
            break;
        case bcmi_dlb_type_ecmp:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_ECMPs, DLB_IDs,
                                               &min, &max));
            cap->id_min = (int)min;
            cap->id_max = (int)max;
            cap->max_groups = cap->id_max - cap->id_min + 1;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_ECMPs, NUM_PATHSs,
                                               &min, &max));
            cap->max_members_per_group = (int)max;
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmi_lt_field_value_range_get(unit, DLB_ECMPs, ALTERNATE_NUM_PATHSs,
                                               &min, &max));
            cap->max_alt_members_per_group = (int)max;
            break;
        default:
            SHR_ERR_EXIT(SHR_E_PARAM);
    }

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_init(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_deinit(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_deinit(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_type_init(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_type_init(unit, dlb_type));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_type_deinit(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_type_deinit(unit, dlb_type));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_config_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_config_t *dlb_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_config_validate(unit, dlb_type, dlb_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_config_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bcmi_ltsw_dlb_config_t *dlb_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_config_set(unit, dlb_type, dlb_id, dlb_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_config_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bcmi_ltsw_dlb_config_t *dlb_config)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_config_get(unit, dlb_type, dlb_id, dlb_config));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_config_clear(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_config_clear(unit, dlb_type, dlb_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_monitor_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_monitor_t *monitor)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_monitor_validate(unit, dlb_type, monitor));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_monitor_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bcmi_ltsw_dlb_monitor_t *monitor)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_monitor_set(unit, dlb_type, dlb_id, monitor));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_monitor_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bcmi_ltsw_dlb_monitor_t *monitor)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_monitor_get(unit, dlb_type, dlb_id, monitor));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_monitor_clear(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_monitor_clear(unit, dlb_type, dlb_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_quality_map_profile_format(
    int unit,
    bcmint_dlb_quality_map_profile_t *quality_map_profile,
    uint32_t *quality_map_profile_format)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_quality_map_profile_format(unit, quality_map_profile, quality_map_profile_format));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_quality_map_profile2id(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    int quality_map_profile_count,
    bcmint_dlb_quality_map_profile_t *quality_map_profile,
    int profile_index,
    int *quality_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_quality_map_profile2id(unit, dlb_type, quality_map_profile_count, quality_map_profile, profile_index, quality_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_quality_map_id2profile(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    int quality_map_profile_count,
    bcmint_dlb_quality_map_profile_t *quality_map_profile,
    int quality_map_id,
    int *profile_index)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_quality_map_id2profile(unit, dlb_type, quality_map_profile_count, quality_map_profile, quality_map_id, profile_index));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_quality_map_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    int quality_map_id,
    int load_percent,
    int qsize_percent)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_quality_map_set(unit, dlb_type, quality_map_id, load_percent, qsize_percent));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_quality_map_clear(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    int quality_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_quality_map_clear(unit, dlb_type, quality_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_pbmp_get(
    int unit,
    bcm_pbmp_t *pbmp)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_pbmp_get(unit, pbmp));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_attribute_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_member_attribute_t *attribute)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_attribute_validate(unit, dlb_type, attribute));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_attribute_set(
    int unit,
    bcm_port_t port,
    bcmi_ltsw_dlb_type_t dlb_type,
    int scaling_factor,
    int quality_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_attribute_set(unit, port, dlb_type, scaling_factor, quality_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_attribute_get(
    int unit,
    bcm_port_t port,
    bcmi_ltsw_dlb_type_t dlb_type,
    int *scaling_factor,
    int *quality_map_id)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_attribute_get(unit, port, dlb_type, scaling_factor, quality_map_id));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_attribute_clear(
    int unit,
    bcm_port_t port,
    bcmi_ltsw_dlb_type_t dlb_type)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_attribute_clear(unit, port, dlb_type));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_status_set(
    int unit,
    bcm_port_t port,
    bcmi_ltsw_dlb_type_t dlb_type,
    int status)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_status_set(unit, port, dlb_type, status));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_member_status_get(
    int unit,
    bcm_port_t port,
    bcmi_ltsw_dlb_type_t dlb_type,
    int *status)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_member_status_get(unit, port, dlb_type, status));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_info_value_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmint_dlb_ctrl_info_t **ctrl_info,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_info_value_validate(unit, dlb_type, ctrl_info, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_info_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmint_dlb_ctrl_info_t **ctrl_info,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_info_set(unit, dlb_type, ctrl_info, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_info_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmint_dlb_ctrl_info_t **ctrl_info,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_info_get(unit, dlb_type, ctrl_info, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_type_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_control_type_t type)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_type_validate(unit, dlb_type, type));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_value_validate(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_value_validate(unit, dlb_type, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_set(unit, dlb_type, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_control_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_control_type_t type,
    uint64_t *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_control_get(unit, dlb_type, type, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_stat_set(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bcmi_ltsw_dlb_stat_t *stat)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_stat_set(unit, dlb_type, dlb_id, stat));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_dlb_stat_get(
    int unit,
    bcmi_ltsw_dlb_type_t dlb_type,
    bcmi_ltsw_dlb_id_t dlb_id,
    bool sync_mode,
    bcmi_ltsw_dlb_stat_t *stat)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_dlb_stat_get(unit, dlb_type, dlb_id, sync_mode, stat));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Dlb driver function variable for bcm56780_a0 device.
 */
static mbcm_ltsw_dlb_drv_t bcm56780_a0_ltsw_dlb_drv = {
    .dlb_feature_get = bcm56780_a0_ltsw_dlb_feature_get,
    .dlb_capability_get = bcm56780_a0_ltsw_dlb_capability_get,
    .dlb_init = bcm56780_a0_ltsw_dlb_init,
    .dlb_deinit = bcm56780_a0_ltsw_dlb_deinit,
    .dlb_type_init = bcm56780_a0_ltsw_dlb_type_init,
    .dlb_type_deinit = bcm56780_a0_ltsw_dlb_type_deinit,
    .dlb_config_validate = bcm56780_a0_ltsw_dlb_config_validate,
    .dlb_config_set = bcm56780_a0_ltsw_dlb_config_set,
    .dlb_config_get = bcm56780_a0_ltsw_dlb_config_get,
    .dlb_config_clear = bcm56780_a0_ltsw_dlb_config_clear,
    .dlb_monitor_validate = bcm56780_a0_ltsw_dlb_monitor_validate,
    .dlb_monitor_set = bcm56780_a0_ltsw_dlb_monitor_set,
    .dlb_monitor_get = bcm56780_a0_ltsw_dlb_monitor_get,
    .dlb_monitor_clear = bcm56780_a0_ltsw_dlb_monitor_clear,
    .dlb_member_quality_map_profile_format = bcm56780_a0_ltsw_dlb_member_quality_map_profile_format,
    .dlb_member_quality_map_profile2id = bcm56780_a0_ltsw_dlb_member_quality_map_profile2id,
    .dlb_member_quality_map_id2profile = bcm56780_a0_ltsw_dlb_member_quality_map_id2profile,
    .dlb_member_quality_map_set = bcm56780_a0_ltsw_dlb_member_quality_map_set,
    .dlb_member_quality_map_clear = bcm56780_a0_ltsw_dlb_member_quality_map_clear,
    .dlb_member_pbmp_get = bcm56780_a0_ltsw_dlb_member_pbmp_get,
    .dlb_member_attribute_validate = bcm56780_a0_ltsw_dlb_member_attribute_validate,
    .dlb_member_attribute_set = bcm56780_a0_ltsw_dlb_member_attribute_set,
    .dlb_member_attribute_get = bcm56780_a0_ltsw_dlb_member_attribute_get,
    .dlb_member_attribute_clear = bcm56780_a0_ltsw_dlb_member_attribute_clear,
    .dlb_member_status_set = bcm56780_a0_ltsw_dlb_member_status_set,
    .dlb_member_status_get = bcm56780_a0_ltsw_dlb_member_status_get,
    .dlb_control_info_value_validate = bcm56780_a0_ltsw_dlb_control_info_value_validate,
    .dlb_control_info_set = bcm56780_a0_ltsw_dlb_control_info_set,
    .dlb_control_info_get = bcm56780_a0_ltsw_dlb_control_info_get,
    .dlb_control_type_validate = bcm56780_a0_ltsw_dlb_control_type_validate,
    .dlb_control_value_validate = bcm56780_a0_ltsw_dlb_control_value_validate,
    .dlb_control_set = bcm56780_a0_ltsw_dlb_control_set,
    .dlb_control_get = bcm56780_a0_ltsw_dlb_control_get,
    .dlb_stat_set = bcm56780_a0_ltsw_dlb_stat_set,
    .dlb_stat_get = bcm56780_a0_ltsw_dlb_stat_get
};

/******************************************************************************
 * Public functions
 */

int
bcm56780_a0_ltsw_dlb_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_dlb_drv_set(unit, &bcm56780_a0_ltsw_dlb_drv));

exit:
    SHR_FUNC_EXIT();
}

