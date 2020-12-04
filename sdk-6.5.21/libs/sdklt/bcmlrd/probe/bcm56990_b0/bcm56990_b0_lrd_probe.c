/*! \file bcm56990_b0_lrd_probe.c
 *
 * BCM56xxx_A0 configuration probe function.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcmdrd/bcmdrd_dev.h>
#include <bcmlrd/chip/bcm56990_b0/bcm56990_b0_lrd_map_frag.h>

int
bcm56990_b0_lrd_probe(int unit)
{
    return sal_strcmp(bcmdrd_dev_type_str(unit), "bcm56990_b0") == 0;
}
