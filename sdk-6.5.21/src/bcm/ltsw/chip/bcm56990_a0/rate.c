/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/mbcm/rate.h>
#include <bcm_int/ltsw/xgs/rate.h>

#include <shr/shr_debug.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_RATE

/******************************************************************************
 * Private functions
 */

static int
bcm56990_a0_ltsw_rate_init(int unit)
{
    return SHR_E_NONE;
}

static int
bcm56990_a0_ltsw_rate_deinit(int unit)
{
    return SHR_E_NONE;
}

static int
bcm56990_a0_ltsw_rate_set(
    int unit,
    bcm_port_t port,
    bcmint_rate_info_t *rate_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_set(unit, port, rate_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_get(
    int unit,
    bcm_port_t port,
    bcmint_rate_info_t *rate_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_get(unit, port, rate_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_dev_set(
    int unit,
    bcmint_rate_dev_info_t *dev_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_dev_set(unit, dev_info));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_dev_get(
    int unit,
    bcmint_rate_dev_info_t *dev_info)
{
    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(dev_info, SHR_E_PARAM);
    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_dev_get(unit, dev_info));
    dev_info->meter_adjust = TRUE;
    dev_info->shaper_adjust = TRUE;

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_meter_adjust_set(
    int unit,
    bcm_port_t port,
    int value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_meter_adjust_set(unit, port, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_meter_adjust_get(
    int unit,
    bcm_port_t port,
    int *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_meter_adjust_get(unit, port, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_shaper_adjust_set(
    int unit,
    bcm_port_t port,
    int value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_shaper_adjust_set(unit, port, value));

exit:
    SHR_FUNC_EXIT();
}

static int
bcm56990_a0_ltsw_rate_shaper_adjust_get(
    int unit,
    bcm_port_t port,
    int *value)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (xgs_ltsw_rate_shaper_adjust_get(unit, port, value));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Rate driver function variable for bcm56990_a0 device.
 */
static mbcm_ltsw_rate_drv_t bcm56990_a0_ltsw_rate_drv = {
    .rate_init = bcm56990_a0_ltsw_rate_init,
    .rate_deinit = bcm56990_a0_ltsw_rate_deinit,
    .rate_set = bcm56990_a0_ltsw_rate_set,
    .rate_get = bcm56990_a0_ltsw_rate_get,
    .rate_dev_set = bcm56990_a0_ltsw_rate_dev_set,
    .rate_dev_get = bcm56990_a0_ltsw_rate_dev_get,
    .rate_meter_adjust_set = bcm56990_a0_ltsw_rate_meter_adjust_set,
    .rate_meter_adjust_get = bcm56990_a0_ltsw_rate_meter_adjust_get,
    .rate_shaper_adjust_set = bcm56990_a0_ltsw_rate_shaper_adjust_set,
    .rate_shaper_adjust_get = bcm56990_a0_ltsw_rate_shaper_adjust_get
};

/******************************************************************************
 * Public functions
 */

int
bcm56990_a0_ltsw_rate_drv_attach(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
        (mbcm_ltsw_rate_drv_set(unit, &bcm56990_a0_ltsw_rate_drv));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Attach functions for other members.
 */
#define BCM56990_A0_DRV_ATTACH_ENTRY(_dn,_vn,_pf,_pd,_r0) \
int _vn##_ltsw_rate_drv_attach(int unit) \
{ \
    SHR_FUNC_ENTER(unit); \
    SHR_IF_ERR_VERBOSE_EXIT \
        (mbcm_ltsw_rate_drv_set(unit, &bcm56990_a0_ltsw_rate_drv)); \
exit: \
    SHR_FUNC_EXIT(); \
}
#include "sub_devlist.h"
