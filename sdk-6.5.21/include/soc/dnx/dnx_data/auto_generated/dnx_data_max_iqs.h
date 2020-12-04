

/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_MAX_IQS_H_

#define _DNX_DATA_MAX_IQS_H_




#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif



#define DNX_DATA_MAX_IQS_CREDIT_NOF_PROFILES (32)


#define DNX_DATA_MAX_IQS_CREDIT_MAX_CREDIT_BALANCE_THRESHOLD (131071)


#define DNX_DATA_MAX_IQS_CREDIT_MAX_WORTH (65535)


#define DNX_DATA_MAX_IQS_CREDIT_SATISIFIED_BACK_MIN (0)


#define DNX_DATA_MAX_IQS_CREDIT_SATISIFIED_BACK_MAX (262143)


#define DNX_DATA_MAX_IQS_CREDIT_SATISIFIED_EMPTY_MIN (0)


#define DNX_DATA_MAX_IQS_CREDIT_SATISIFIED_EMPTY_MAX (131071)


#define DNX_DATA_MAX_IQS_CREDIT_HUNGRY_MIN (0)


#define DNX_DATA_MAX_IQS_CREDIT_HUNGRY_MAX (262143)


#define DNX_DATA_MAX_IQS_CREDIT_HUNGRY_MULT_MIN (16)


#define DNX_DATA_MAX_IQS_CREDIT_HUNGRY_MULT_MAX (4096)


#define DNX_DATA_MAX_IQS_CREDIT_NOF_BW_LEVELS (4)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_CREDIT_FC_ON_TH (30)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_CREDIT_FC_OFF_TH (20)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_BYTE_FC_ON_TH (1000)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_BYTE_FC_OFF_TH (800)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_EIR_CREDIT_FC_TH (8191)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_EIR_BYTE_FC_TH (2097151)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_NOF_BE_CLASSES (3)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_MAX_BE_WEIGHT (31)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_MAX_BURST_MAX (63)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_SHP_CRDT_RATE_MLTP (8)


#define DNX_DATA_MAX_IQS_CREDIT_FMQ_SHP_CRDT_RATE_DELTA (7)


#define DNX_DATA_MAX_IQS_CREDIT_MAX_RATE_PROFILE_PRESET_GBPS (4096)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_LOW_DELAY_DEQ_BYTES (16)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_CREDIT_BALANCE_MAX (131072)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_CREDIT_BALANCE_RESOLUTION (4096)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_S2D_CREDIT_BALANCE_MAX (2097152)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_S2D_CREDIT_BALANCE_RESOLUTION (65536)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_SRAM_TO_FABRIC_CREDIT_LFSR_THR (112)


#define DNX_DATA_MAX_IQS_DEQ_DEFAULT_SRAM_TO_FABRIC_CREDIT_LFSR_MASK (3)


#define DNX_DATA_MAX_IQS_DQCQ_MAX_NOF_CONTEXTS (5)


#define DNX_DATA_MAX_IQS_DQCQ_NOF_PRIORITIES (8)


#define DNX_DATA_MAX_IQS_DBAL_IPT_COUNTERS_NOF_BITS (32)


#define DNX_DATA_MAX_IQS_FLUSH_BYTES_UNITS_TO_SEND (128)




#endif 

