/*! \file l3_egress.c
 *
 * BCM56880_A0 L3 Egress Driver.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm_int/ltsw/chip/bcm56880_a0/variant_dispatch.h>

#include <shr/shr_debug.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_L3

/******************************************************************************
 * Private functions
 */

/******************************************************************************
 * Public functions
 */

int
bcm56880_a0_ltsw_l3_egress_drv_attach(int unit)
{
    return bcm56880_a0_ltsw_variant_drv_attach(unit,
                                            BCM56880_A0_LTSW_VARIANT_L3_EGRESS);
}
