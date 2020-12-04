/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMI_LTSW_HASH_OUTPUT_SELECTION_H
#define BCMI_LTSW_HASH_OUTPUT_SELECTION_H

#include <bcm/types.h>

#include <sal/sal_types.h>

/*!
 * \brief Option to create hash output selection profile.
 */
/*! Use input profile Id instead of allocating a new one. */
#define BCMI_LTSW_HOS_PROFILE_CREATE_OPTION_WITH_ID (1 << 0)

/*!
 * \brief The max available profile identifier.
 */
/*! Profile identifier 0. */
#define BCMI_LTSW_HOS_PROFILE_ID_0 0

/*! Profile identifier 1. */
#define BCMI_LTSW_HOS_PROFILE_ID_1 1

/*! Profile identifier 2. */
#define BCMI_LTSW_HOS_PROFILE_ID_2 2

/*! Profile identifier 3. */
#define BCMI_LTSW_HOS_PROFILE_ID_3 3

/*!
 * \brief The Hash Output Selection Resolution type.
 */
typedef enum bcmi_ltsw_hos_type_s {

    /*! For trunk unicast packet resolution. */
    bcmiHosTypeTrunkUc = 0,

    /*! For trunk non-unicast packet resolution. */
    bcmiHosTypeTrunkNonUc = 1,

    /*! For trunk failover resolution. */
    bcmiHosTypeTrunkFailover = 2,

    /*! For trunk system resolution. */
    bcmiHosTypeTrunkSystem = 3,

    /*! For trunk system failover resolution. */
    bcmiHosTypeTrunkSystemFailover = 4,

    /*! For VPLAG resolution. */
    bcmiHosTypeTrunkVp = 5,

    /*! For ECMP overlay resolution. */
    bcmiHosTypeEcmpOverlay = 6,

    /*! For ECMP underlay resolution. */
    bcmiHosTypeEcmpUnderlay = 7,

    /*! For DLB trunk resolution. */
    bcmiHosTypeDlbTrunk = 8,

    /*! For DLB ECMP resolution. */
    bcmiHosTypeDlbEcmp = 9,

    /*! For entropy hash resolution. */
    bcmiHosTypeEntropy = 10,

    /*! HOS resolution type count. */
    bcmiHosTypeCount = 11

} bcmi_ltsw_hos_type_t;

#define BCMI_LTSW_HOS_TYPE_STR \
{ \
    "TrunkUc", \
    "TrunkNonUc", \
    "TrunkFailover", \
    "TrunkSystem", \
    "TrunkSystemFailover", \
    "TrunkVp", \
    "EcmpOverlay", \
    "EcmpUnderlay", \
    "DlbTrunk", \
    "DlbEcmp", \
    "Entropy" \
}

/*!
 * \brief The Hash Output Selection control type.
 */
typedef enum bcmi_ltsw_hos_control_s {

    /*! Use macro flow identifier as shuffle table index. */
    bcmiHosControlUseFlowSel = 0,

    /*! Use higig3 entropy as shuffle table index. */
    bcmiHosControlUseHigig3Entropy = 1,

    /*! Initial seed value. */
    bcmiHosControlSeed = 2,

    /*! Hash value offset. */
    bcmiHosControlOffset = 3,

    /*! For trunk non-unicast packet resolution. */
    bcmiHosControlConcatEnable = 4,

    /*! Minimum offset value to be used in hashing shuffle table. */
    bcmiHosControlMinOffset = 5,

    /*! Maximum offset value to be used in hashing shuffle table. */
    bcmiHosControlMaxOffset = 6,

    /*! Offset increment to be used for programming hash shuffle table. */
    bcmiHosControlStrideOffset = 7,

    /*! Select the bit count of hash result. */
    bcmiHosControlBitCountSelect = 8,

    /*! HOS control type count. */
    bcmiHosControlCount = 9

} bcmi_ltsw_hos_control_t;

#define BCMI_LTSW_HOS_CONTROL_STR \
{ \
    "UseFlowSel", \
    "UseHigig3Entropy", \
    "Seed", \
    "Offset", \
    "ConcatEnable", \
    "MinOffset", \
    "MaxOffset", \
    "StrideOffset", \
    "BitCountSelect" \
}

/*!
 * \brief The Hash Output Selection Profile control type.
 */
typedef enum bcmi_ltsw_hos_profile_control_s {

    /*! For trunk unicast packet resolution. */
    bcmiHosProfileControlInstance = 0,

    /*! For trunk non-unicast packet resolution. */
    bcmiHosProfileControlFlowIdSrc = 1,

    /*! For trunk non-unicast packet use higig3 entropy resolution. */
    bcmiHosProfileControlUseHigig3Entropy = 2,

    /*! Enable to select ECMP level0 member index from the input bus. */
    bcmiHosProfileControlMemberIndex = 3,

    /*! Enable for weighted distribution ECMP. */
    bcmiHosProfileControlWEcmp = 4,

    /*! HOS profile control type count. */
    bcmiHosProfileControlCount = 5

} bcmi_ltsw_hos_profile_control_t;

#define BCMI_LTSW_HOS_PROFILE_CONTROL_STR \
{ \
    "Instance", \
    "FlowIdSrc", \
    "UseHigig3Entropy", \
    "MemberIndex", \
    "WEcmp" \
}

/*!
 * \brief The hash output selection instance control type.
 */
typedef enum bcmi_ltsw_hos_instance_control_s {

    /*! Hash result size of instance for a specific hash type. */
    bcmiHosInstaceControlResultSize = 0,

    /*! Hash offset of instance for a specific hash type. */
    bcmiHosInstaceControlOffset = 1,

    /*! Hash subselect of instance for a specific hash type. */
    bcmiHosInstaceControlSubSelect = 2,

    /*! Hash concatenation of instance for a specific hash type. */
    bcmiHosInstaceControlConcat = 3,

    /*! HOS instance field type count. */
    bcmiHosInstaceControlCount = 4

} bcmi_ltsw_hos_instance_control_t;

#define BCMI_LTSW_HOS_INSTANCE_CONTROL_STR \
{ \
    "ResultSize", \
    "Offset", \
    "SubSelect", \
    "Concat" \
}

/*!
 * \brief The hash flow identifier source.
 */
typedef enum bcmi_ltsw_hos_flow_id_source_s {

    /*! The bus hash index. */
    bcmiHosFlowIdSrcBusHashIndex = 0,

    /*! Hash A0 Low. */
    bcmiHosFlowIdSrcHashA0Lo = 1,

    /*! Hash A0 High. */
    bcmiHosFlowIdSrcHashA0Hi = 2,

    /*! Hash A1 Low. */
    bcmiHosFlowIdSrcHashA1Lo = 3,

    /*! Hash A1 High. */
    bcmiHosFlowIdSrcHashA1Hi = 4,

    /*! Hash B0 Low. */
    bcmiHosFlowIdSrcHashB0Lo = 5,

    /*! Hash B0 High. */
    bcmiHosFlowIdSrcHashB0Hi = 6,

    /*! Hash B1 Low. */
    bcmiHosFlowIdSrcHashB1Lo = 7,

    /*! Hash B1 High. */
    bcmiHosFlowIdSrcHashB1Hi = 8,

    /*! Hash C0 Low. */
    bcmiHosFlowIdSrcHashC0Lo = 9,

    /*! Hash C0 High. */
    bcmiHosFlowIdSrcHashC0Hi = 10,

    /*! Hash C1 Low. */
    bcmiHosFlowIdSrcHashC1Lo = 11,

    /*! Hash C1 High. */
    bcmiHosFlowIdSrcHashC1Hi = 12,

    /*! HOS flow identifier source count. */
    bcmiHosFlowIdSrcCount = 13

} bcmi_ltsw_hos_flow_id_source_t;

#define BCMI_LTSW_HOS_FLOW_ID_SOURCE_STR \
{ \
    "BusHashIndex", \
    "HashA0Lo", \
    "HashA0Hi", \
    "HashA1Lo", \
    "HashA1Hi", \
    "HashB0Lo", \
    "HashB0Hi", \
    "HashB1Lo", \
    "HashB1Hi", \
    "HashC0Lo", \
    "HashC0Hi", \
    "HashC1Lo", \
    "HashC1Hi" \
}

/*!
 * \brief ECMP member index source source.
 */
typedef enum bcmi_ltsw_hos_ecmp_member_idx_s {

    /*! Member index is locally generated. */
    bcmiHosEcmpMemberIndexLocallyGenerated = 0,

    /*! Member index is taken from the input bus. */
    bcmiHosEcmpMemberIndexInputBus = 1,

    /*! The ecmp member index source count. */
    bcmiHosEcmpMemberIndexCount = 2

} bcmi_ltsw_hos_ecmp_member_idx_t;

#define BCMI_LTSW_HOS_ECMP_MEMBER_IDX_STR \
{ \
    "LocallyGenerated", \
    "InputBus" \
}

/*!
 * \brief Control the hash output selection.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [in] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_set(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcmi_ltsw_hos_control_t ctrl_type,
    int value);

/*!
 * \brief Get the hash output selection configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [out] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_get(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcmi_ltsw_hos_control_t ctrl_type,
    int *value);

/*!
 * \brief Control the port based hash output selection.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] port Port Number.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [in] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_port_set(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcm_port_t port,
    bcmi_ltsw_hos_control_t ctrl_type,
    int value);

/*!
 * \brief Get the port based hash output selection configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] port Port Number.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [out] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_port_get(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcm_port_t port,
    bcmi_ltsw_hos_control_t ctrl_type,
    int *value);

/*!
 * \brief Control the macro flow based hash output selection.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [in] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_flow_set(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcmi_ltsw_hos_control_t ctrl_type,
    int value);

/*!
 * \brief Get the macro flow based hash output selection configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] ctrl_type The hash output selection control type.
 * \param [out] value The hash output selection control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_control_flow_get(
    int unit,
    bcmi_ltsw_hos_type_t type,
    bcmi_ltsw_hos_control_t ctrl_type,
    int *value);

/*!
 * \brief dump software information for HOS module.
 *
 * \param [in] unit Unit Number.
 */
extern void
bcmi_ltsw_hos_sw_dump(int unit);

/*!
 * \brief Insert a hash output selection profile to logical table.
 *
 * \param [in] unit Unit Number.
 * \param [in] option Profile created option.
 * \param [inout] profile_id Profile identifier.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_profile_create(
    int unit,
    uint32_t option,
    int *profile_id);

/*!
 * \brief Delete a hash output selection profile from logical table.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile identifier.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_profile_destroy(
    int unit,
    int profile_id);

/*!
 * \brief Multi-control the hash output selection profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile identifier.
 * \param [in] type The hash output selection type.
 * \param [in] array_size controlling configuration array size.
 * \param [in] ctrl_type The hash output selection profile control type array.
 * \param [in] value The hash output selection profile control value array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_profile_set(
    int unit,
    int profile_id,
    bcmi_ltsw_hos_type_t type,
    int array_size,
    bcmi_ltsw_hos_profile_control_t *ctrl_type,
    int *value);

/*!
 * \brief Get the hash output selection profile configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id Profile identifier.
 * \param [in] type The hash output selection type.
 * \param [in] ctrl_type The hash output selection profile control type.
 * \param [out] value The hash output selection profile control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_profile_get(
    int unit,
    int profile_id,
    bcmi_ltsw_hos_type_t type,
    bcmi_ltsw_hos_profile_control_t ctrl_type,
    int *value);

/*!
 * \brief Multi-control the hash output selection instance.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] inst_id Instance identifier.
 * \param [in] flow_id Flow identifier.
 * \param [in] array_size Controlling configuration array size.
 * \param [in] ctrl_type The hash output selection instance control type array.
 * \param [in] value The hash output selection instance control value array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_instance_set(
    int unit,
    bcmi_ltsw_hos_type_t type,
    int inst_id,
    int flow_id,
    int array_size,
    bcmi_ltsw_hos_instance_control_t *ctrl_type,
    int *value);

/*!
 * \brief Get the hash output selection instance configuration.
 *
 * \param [in] unit Unit Number.
 * \param [in] type The hash output selection type.
 * \param [in] inst_id Instance identifier.
 * \param [in] flow_id Flow identifier.
 * \param [in] array_size Controlling configuration array size.
 * \param [in] ctrl_type The hash output selection instance control type.
 * \param [out] value The hash output selection instance control value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_instance_get(
    int unit,
    bcmi_ltsw_hos_type_t type,
    int inst_id,
    int flow_id,
    int array_size,
    bcmi_ltsw_hos_instance_control_t *ctrl_type,
    int *value);

/*!
 * \brief Initialize the hash output selection module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_init(int unit);

/*!
 * \brief De-init the hash output selection module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_hos_deinit(int unit);

#endif /* BCMI_LTSW_HASH_OUTPUT_SELECTION_H */
