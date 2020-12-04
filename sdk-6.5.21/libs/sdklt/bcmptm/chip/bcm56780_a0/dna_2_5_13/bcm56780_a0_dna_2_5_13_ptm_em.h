/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by xfcr from NPL files files.
 *
 * Tool: $SDK/INTERNAL/fltg/bin/xfcr
 *
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
#ifndef BCM56780_A0_DNA_2_5_13_PTM_EM_H
#define BCM56780_A0_DNA_2_5_13_PTM_EM_H
static const bcmdrd_sid_t bcm56780_a0_dna_2_5_13_bank_ptid[112];
static const bcmdrd_sid_t bcm56780_a0_dna_2_5_13_alpm_ptid[112];
static const uint32_t bcm56780_a0_dna_2_5_13_bank_tile_id[112];

#include "bcm56780_a0_dna_2_5_13_ptm_em_tile.h"

#include "bcm56780_a0_dna_2_5_13_ptm_em.ptrm.data.h"

#define BCM56780_A0_DNA_2_5_13_UFT_MODE_CNT (0)

#define BCM56780_A0_DNA_2_5_13_EM_BANK_CNT ((int)(sizeof(bcm56780_a0_dna_2_5_13_em_bank_info)/sizeof(em_bank_info_t)))

#define BCM56780_A0_DNA_2_5_13_EM_TILE_CNT ((int)(sizeof(bcm56780_a0_dna_2_5_13_em_tile_info)/sizeof(em_tile_info_t)))

#define BCM56780_A0_DNA_2_5_13_EM_GRP_CNT ((int)(sizeof(bcm56780_a0_dna_2_5_13_em_mode_grp)/sizeof(em_grp_info_t*)))

#define BCM56780_A0_DNA_2_5_13_EM_TILE_MODE_CNT ((int)(sizeof(bcm56780_a0_dna_2_5_13_em_tile_mode)/sizeof(em_tile_mode_info_t*)))

#define BCM56780_A0_DNA_2_5_13_EM_LT_INFO_CNT ((int)(sizeof(bcm56780_a0_dna_2_5_13_em_lt_info)/sizeof(em_lt_info_t)))

#define DEV_EM_GRP_CNT (BCM56780_A0_DNA_2_5_13_EM_GRP_CNT)

#define DEV_EM_GRP_MAX (BCM56780_A0_DNA_2_5_13_EM_GRP_CNT + 1)

#define DEV_EM_BANK_CNT (BCM56780_A0_DNA_2_5_13_EM_BANK_CNT)

#define DEV_UFT_PHY_BANKS_MAX (BCM56780_A0_DNA_2_5_13_EM_BANK_CNT)

#define DEV_UFT_TILE_MAX (BCM56780_A0_DNA_2_5_13_EM_TILE_CNT)

#define DEV_UFT_MODE_CNT (BCM56780_A0_DNA_2_5_13_UFT_MODE_CNT)

#define DEV_UFT_FIRST_BANK (IFTA90_E2T_00_BANK0)

#define DEV_UFT_BANKS_CNT (16)

static const bcmdrd_sid_t bcm56780_a0_dna_2_5_13_bank_ptid[112] = {
    MEMDB_EFTA10_MEM0m,
    MEMDB_EFTA10_MEM1m,
    MEMDB_EFTA10_MEM2m,
    MEMDB_EFTA10_MEM3m,
    MEMDB_EFTA10_MEM4m,
    MEMDB_EFTA20_2P_MEM0m,
    MEMDB_EFTA20_2P_MEM1m,
    MEMDB_EFTA20_MEM0m,
    MEMDB_EFTA20_MEM1m,
    MEMDB_EFTA20_MEM2m,
    MEMDB_EFTA20_2P_MEM2m,
    EFTA30_E2T_00_B0_QUADm,
    EFTA30_E2T_00_B1_QUADm,
    INVALIDm,
    MEMDB_IFTA130_MEM0m,
    MEMDB_IFTA130_MEM1m,
    MEMDB_IFTA130_MEM2m,
    MEMDB_IFTA130_MEM3m,
    MEMDB_IFTA130_MEM4m,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    IFTA30_E2T_00_B0_QUADm,
    IFTA30_E2T_00_B1_QUADm,
    IFTA40_E2T_00_B0_QUADm,
    IFTA40_E2T_00_B1_QUADm,
    IFTA40_E2T_01_B0_QUADm,
    IFTA40_E2T_01_B1_QUADm,
    MEMDB_TCAM_IFTA40_MEM0_0_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_1_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_2_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_3_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_0_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_1_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_2_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_3_ONLYm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    IFTA80_E2T_00_B0_QUADm,
    IFTA80_E2T_00_B1_QUADm,
    IFTA80_E2T_01_B0_QUADm,
    IFTA80_E2T_01_B1_QUADm,
    IFTA80_E2T_02_B0_QUADm,
    IFTA80_E2T_02_B1_QUADm,
    IFTA80_E2T_03_B0_QUADm,
    IFTA80_E2T_03_B1_QUADm,
    MEMDB_TCAM_IFTA80_MEM0_0m,
    MEMDB_TCAM_IFTA80_MEM0_1m,
    MEMDB_TCAM_IFTA80_MEM1_0m,
    MEMDB_TCAM_IFTA80_MEM1_1m,
    MEMDB_TCAM_IFTA80_MEM2_0m,
    MEMDB_TCAM_IFTA80_MEM2_1m,
    MEMDB_TCAM_IFTA80_MEM3_0m,
    MEMDB_TCAM_IFTA80_MEM3_1m,
    MEMDB_TCAM_IFTA80_MEM4_0m,
    MEMDB_TCAM_IFTA80_MEM4_1m,
    MEMDB_TCAM_IFTA80_MEM5_0m,
    MEMDB_TCAM_IFTA80_MEM5_1m,
    MEMDB_TCAM_IFTA80_MEM6_0m,
    MEMDB_TCAM_IFTA80_MEM6_1m,
    MEMDB_TCAM_IFTA80_MEM7_0m,
    MEMDB_TCAM_IFTA80_MEM7_1m,
    IFTA90_E2T_00_B0_QUADm,
    IFTA90_E2T_00_B1_QUADm,
    IFTA90_E2T_00_B2_QUADm,
    IFTA90_E2T_00_B3_QUADm,
    IFTA90_E2T_01_B0_QUADm,
    IFTA90_E2T_01_B1_QUADm,
    IFTA90_E2T_01_B2_QUADm,
    IFTA90_E2T_01_B3_QUADm,
    M_E2T_B0_QUADm,
    M_E2T_B1_QUADm,
    M_E2T_B2_QUADm,
    M_E2T_B3_QUADm,
    M_E2T_B4_QUADm,
    M_E2T_B5_QUADm,
    M_E2T_B6_QUADm,
    M_E2T_B7_QUADm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
};

static const bcmdrd_sid_t bcm56780_a0_dna_2_5_13_alpm_ptid[112] = {
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    MEMDB_TCAM_IFTA40_MEM0_0_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_1_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_2_ONLYm,
    MEMDB_TCAM_IFTA40_MEM0_3_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_0_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_1_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_2_ONLYm,
    MEMDB_TCAM_IFTA40_MEM1_3_ONLYm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    INVALIDm,
    MEMDB_TCAM_IFTA80_MEM0_0m,
    MEMDB_TCAM_IFTA80_MEM0_1m,
    MEMDB_TCAM_IFTA80_MEM1_0m,
    MEMDB_TCAM_IFTA80_MEM1_1m,
    MEMDB_TCAM_IFTA80_MEM2_0m,
    MEMDB_TCAM_IFTA80_MEM2_1m,
    MEMDB_TCAM_IFTA80_MEM3_0m,
    MEMDB_TCAM_IFTA80_MEM3_1m,
    MEMDB_TCAM_IFTA80_MEM4_0m,
    MEMDB_TCAM_IFTA80_MEM4_1m,
    MEMDB_TCAM_IFTA80_MEM5_0m,
    MEMDB_TCAM_IFTA80_MEM5_1m,
    MEMDB_TCAM_IFTA80_MEM6_0m,
    MEMDB_TCAM_IFTA80_MEM6_1m,
    MEMDB_TCAM_IFTA80_MEM7_0m,
    MEMDB_TCAM_IFTA80_MEM7_1m,
    L3_DEFIP_ALPM_LEVEL3_B0m,
    L3_DEFIP_ALPM_LEVEL3_B1m,
    L3_DEFIP_ALPM_LEVEL3_B2m,
    L3_DEFIP_ALPM_LEVEL3_B3m,
    L3_DEFIP_ALPM_LEVEL3_B4m,
    L3_DEFIP_ALPM_LEVEL3_B5m,
    L3_DEFIP_ALPM_LEVEL3_B6m,
    L3_DEFIP_ALPM_LEVEL3_B7m,
    M_DEFIP_ALPM_LEVEL3_B0m,
    M_DEFIP_ALPM_LEVEL3_B1m,
    M_DEFIP_ALPM_LEVEL3_B2m,
    M_DEFIP_ALPM_LEVEL3_B3m,
    M_DEFIP_ALPM_LEVEL3_B4m,
    M_DEFIP_ALPM_LEVEL3_B5m,
    M_DEFIP_ALPM_LEVEL3_B6m,
    M_DEFIP_ALPM_LEVEL3_B7m,
    L3_DEFIP_ALPM_LEVEL2_B0m,
    L3_DEFIP_ALPM_LEVEL2_B1m,
    L3_DEFIP_ALPM_LEVEL2_B2m,
    L3_DEFIP_ALPM_LEVEL2_B3m,
    L3_DEFIP_ALPM_LEVEL2_B4m,
    L3_DEFIP_ALPM_LEVEL2_B5m,
    MEMDB_TCAM_M_CTL_MEM0_0m,
    MEMDB_TCAM_M_CTL_MEM0_1m,
    MEMDB_TCAM_M_CTL_MEM5_0m,
    MEMDB_TCAM_M_CTL_MEM5_1m,
    MEMDB_TCAM_M_CTL_MEM6_0m,
    MEMDB_TCAM_M_CTL_MEM6_1m,
    MEMDB_TCAM_M_CTL_MEM7_0m,
    MEMDB_TCAM_M_CTL_MEM7_1m,
    MEMDB_TCAM_M_CTL_MEM1_0m,
    MEMDB_TCAM_M_CTL_MEM1_1m,
    MEMDB_TCAM_M_CTL_MEM2_0m,
    MEMDB_TCAM_M_CTL_MEM2_1m,
    MEMDB_TCAM_M_CTL_MEM3_0m,
    MEMDB_TCAM_M_CTL_MEM3_1m,
    MEMDB_TCAM_M_CTL_MEM4_0m,
    MEMDB_TCAM_M_CTL_MEM4_1m,
    M_DEFIP_ALPM_LEVEL2_B0m,
    M_DEFIP_ALPM_LEVEL2_B1m,
    M_DEFIP_ALPM_LEVEL2_B2m,
    M_DEFIP_ALPM_LEVEL2_B3m,
    M_DEFIP_ALPM_LEVEL2_B4m,
    M_DEFIP_ALPM_LEVEL2_B5m,
};

static const uint32_t bcm56780_a0_dna_2_5_13_bank_tile_id[112] = {
    EFTA10_I1T_00,
    EFTA10_I1T_01,
    EFTA10_I1T_01,
    EFTA10_I1T_02,
    EFTA10_I1T_03,
    EFTA20_I1T_00,
    EFTA20_I1T_01,
    EFTA20_I1T_02,
    EFTA20_I1T_03,
    EFTA20_I1T_04,
    EFTA20_I1T_05,
    EFTA30_E2T_00,
    EFTA30_E2T_00,
    IFTA10_I1T_00,
    IFTA130_I1T_00,
    IFTA130_I1T_01,
    IFTA130_I1T_01,
    IFTA130_I1T_02,
    IFTA130_I1T_03,
    IFTA140_I1T_00,
    IFTA150_T4T_00,
    IFTA150_T4T_00,
    IFTA150_T4T_00,
    IFTA150_T4T_00,
    IFTA30_E2T_00,
    IFTA30_E2T_00,
    IFTA40_E2T_00,
    IFTA40_E2T_00,
    IFTA40_E2T_01,
    IFTA40_E2T_01,
    IFTA40_T4T_00,
    IFTA40_T4T_00,
    IFTA40_T4T_00,
    IFTA40_T4T_00,
    IFTA40_T4T_01,
    IFTA40_T4T_01,
    IFTA40_T4T_01,
    IFTA40_T4T_01,
    IFTA50_I1T_00,
    IFTA60_I1T_00,
    IFTA60_I1T_01,
    IFTA60_T4T_00,
    IFTA60_T4T_00,
    IFTA60_T4T_00,
    IFTA80_E2T_00,
    IFTA80_E2T_00,
    IFTA80_E2T_01,
    IFTA80_E2T_01,
    IFTA80_E2T_02,
    IFTA80_E2T_02,
    IFTA80_E2T_03,
    IFTA80_E2T_03,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_00,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA80_T2T_01,
    IFTA90_E2T_00,
    IFTA90_E2T_00,
    IFTA90_E2T_00,
    IFTA90_E2T_00,
    IFTA90_E2T_01,
    IFTA90_E2T_01,
    IFTA90_E2T_01,
    IFTA90_E2T_01,
    IFTA90_E2T_02,
    IFTA90_E2T_02,
    IFTA90_E2T_02,
    IFTA90_E2T_02,
    IFTA90_E2T_03,
    IFTA90_E2T_03,
    IFTA90_E2T_03,
    IFTA90_E2T_03,
    UFT_MINI_TILE,
    UFT_MINI_TILE,
    UFT_MINI_TILE,
    UFT_MINI_TILE,
    UFT_MINI_TILE,
    UFT_MINI_TILE,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL1,
    UFT_MTOP_ALPM_LEVEL2,
    UFT_MTOP_ALPM_LEVEL2,
    UFT_MTOP_ALPM_LEVEL2,
    UFT_MTOP_ALPM_LEVEL2,
    UFT_MTOP_ALPM_LEVEL2,
    UFT_MTOP_ALPM_LEVEL2,
};


#endif /* BCM56780_A0_DNA_2_5_13_PTM_EM_H */
