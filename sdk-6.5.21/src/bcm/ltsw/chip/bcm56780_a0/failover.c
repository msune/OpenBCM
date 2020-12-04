/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/mbcm/failover.h>
#include <bcm_int/ltsw/xfs/failover.h>

#include <shr/shr_debug.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_FAILOVER

/******************************************************************************
 * Private functions
 */

static int
bcm56780_a0_ltsw_failover_clear(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_failover_clear(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_failover_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_failover_init(unit));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_failover_egress_status_set(
    int unit,
    int nh_idx,
    int enable)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_failover_egress_status_set(unit, nh_idx, enable));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56780_a0_ltsw_failover_egress_status_get(
    int unit,
    int nh_idx,
    int *enable)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xfs_ltsw_failover_egress_status_get(unit, nh_idx, enable));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Failover driver function variable for bcm56780_a0 device.
 */
static mbcm_ltsw_failover_drv_t bcm56780_a0_ltsw_failover_drv = {
    .failover_clear = bcm56780_a0_ltsw_failover_clear,
    .failover_init = bcm56780_a0_ltsw_failover_init,
    .failover_egress_status_set = bcm56780_a0_ltsw_failover_egress_status_set,
    .failover_egress_status_get = bcm56780_a0_ltsw_failover_egress_status_get
};

/******************************************************************************
 * Public functions
 */

int
bcm56780_a0_ltsw_failover_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_failover_drv_set(unit, &bcm56780_a0_ltsw_failover_drv));

exit:
    SHR_FUNC_EXIT();
}

