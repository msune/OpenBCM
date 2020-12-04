/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMINT_LTSW_FLEXSTATE_INT_H
#define BCMINT_LTSW_FLEXSTATE_INT_H

#include <bcm_int/ltsw/profile_mgmt.h>

#include <sal/sal_types.h>

/*! Ingress state lookup quantization sub component id. */
#define BCMINT_FLEXSTATE_ING_LKUP_QUANT_SUB_COMP_ID (0)

/*! Ingress state forward lookup quantization sub component id. */
#define BCMINT_FLEXSTATE_ING_FWD_QUANT_SUB_COMP_ID (1)

/*! Egress state quantization sub component id. */
#define BCMINT_FLEXSTATE_EGR_QUANT_SUB_COMP_ID (2)

/*! Ingress state lookup action sub component id. */
#define BCMINT_FLEXSTATE_ING_LKUP_ACTION_SUB_COMP_ID (3)

/*! Ingress state forward action sub component id. */
#define BCMINT_FLEXSTATE_ING_FWD_ACTION_SUB_COMP_ID (4)

/*! Egress stateaction sub component id. */
#define BCMINT_FLEXSTATE_EGR_ACTION_SUB_COMP_ID (5)

/*! Ingress state lookup pool sub component id. */
#define BCMINT_FLEXSTATE_ING_LKUP_POOL_SUB_COMP_ID (6)

/*! Ingress state forward pool sub component id. */
#define BCMINT_FLEXSTATE_ING_FWD_POOL_SUB_COMP_ID (7)

/*! Egress state pool sub component id. */
#define BCMINT_FLEXSTATE_EGR_POOL_SUB_COMP_ID (8)

/*! Ingress state lookup group action sub component id. */
#define BCMINT_FLEXSTATE_ING_LKUP_GRP_ACTION_SUB_COMP_ID (9)

/*! Ingress state forward group action sub component id. */
#define BCMINT_FLEXSTATE_ING_FWD_GRP_ACTION_SUB_COMP_ID (10)

/*! Egress state group action sub component id. */
#define BCMINT_FLEXSTATE_EGR_GRP_ACTION_SUB_COMP_ID (11)

/*! Table bit of emft. */
#define BCMINT_FLEXSTATE_ING_LKUP_EMFT_TBL_BIT (0)

/*! Table bit of ing l2 iif attributes. */
#define BCMINT_FLEXSTATE_ING_LKUP_ING_L2_IIF_ATTRIBUTES_TBL_BIT (1)

/*! Table bit of ecn state. */
#define BCMINT_FLEXSTATE_EGR_ECN_STATE_TBL_BIT (0)

/*! Table bit of tx byte state. */
#define BCMINT_FLEXSTATE_EGR_TX_BYTE_STATE_TBL_BIT (1)

/*! Maximum pipe number. */
#define BCMINT_FLEXSTATE_MAX_PIPE 8

/*!
 * \brief Flex state source infomation.
 */
typedef struct bcmint_flexstate_source_info_s {

    /*! Source enumeration in HSDK API. */
    int source;

    /*! Stage id. */
    int stage;

    /*! Logical table in SDKLT. */
    const char *table;

    /*! Table bit. */
    uint32_t tbl_bit;

} bcmint_flexstate_source_info_t;

/*!
 * \brief Object type.
 */
typedef enum bcmint_flexstate_object_type_s {

    /*! Const object. */
    FlexstateObjectTypeConst = 0,

    /*! Trigger object. */
    FlexstateObjectTypeTrigger = 1,

    /*! Quantization object. */
    FlexstateObjectTypeQuant = 2,

    /*! Menu object. */
    FlexstateObjectTypeMenu = 3,

    /*! Always last one. */
    FlexstateObjectTypeCount = 4

} bcmint_flexstate_object_type_t;

#define BCMINT_FLEXSTATE_OBJECT_TYPE_STR \
{ \
    "Const", \
    "Trigger", \
    "Quant", \
    "Menu" \
}

/*!
 * \brief Flex state object information.
 */
typedef struct bcmint_flexstate_object_info_s {

    /*! Object enumeration in HSDK API. */
    int object;

    /*! Stage id. */
    int stage;

    /*! Object type. */
    bcmint_flexstate_object_type_t obj_type;

    /*! Object symbol in SDKLT. */
    const char *symbol;

} bcmint_flexstate_object_info_t;

/*!
 * \brief Flex state stage properties.
 */
typedef struct bcmint_flexstate_stage_info_s {

    /*! Stage. */
    int stage;

    /*! Name. */
    const char *name;

    /*! Direction. */
    int dir;

    /*! HA pool id. */
    uint8_t ha_pool_id;

    /*! HA quantization id. */
    uint8_t ha_quant_id;

    /*! HA action id. */
    uint8_t ha_action_id;

    /*! HA group action id. */
    uint8_t ha_grp_act_id;

    /*! Profile handle. */
    bcmi_ltsw_profile_hdl_t ph[BCMINT_FLEXSTATE_MAX_PIPE];

    /*! Object quantization config. */
    const char *obj_quant_cfg;

    /*! Range check profile. */
    const char *range_chk_profile;

    /*! Range check profile ID. */
    const char *range_chk_profile_id;

    /*! Action profile. */
    const char *act_profile;

    /*! Action profile ID. */
    const char *act_profile_id;

    /*! Action index. */
    const char *act_index;

    /*! Action value a compare. */
    const char *act_value_a_comp;

    /*! Action value a true. */
    const char *act_value_a_true;

    /*! Action value a false. */
    const char *act_value_a_false;

    /*! Action value b compare. */
    const char *act_value_b_comp;

    /*! Action value b true. */
    const char *act_value_b_true;

    /*! Action value b false. */
    const char *act_value_b_false;

    /*! Group action profile. */
    const char *grp_act_profile;

    /*! Group action profile ID. */
    const char *grp_act_profile_id;

    /*! Operand profile. */
    const char *operand_profile;

    /*! Operand profile ID. */
    const char *operand_profile_id;

    /*! Stats. */
    const char *stats;

    /*! Trigger. */
    const char *trigger;

    /*! Error stats. */
    const char *err_stats;

    /*! Instance. */
    const char *inst;

    /*! Hit ctrl. */
    const char *hit_ctrl;

    /*! Hit dst group. */
    const char *hit_dst_grp;

    /*! Hit src group. */
    const char *hit_src_grp;

} bcmint_flexstate_stage_info_t;

/*!
 * \brief Flex state enumeration map.
 */
typedef struct bcmint_flexstate_enum_map_s {

    /*! Enum name. */
    const char *name;

    /*! Enum value. */
    int val;

} bcmint_flexstate_enum_map_t;

#endif /* BCMINT_LTSW_FLEXSTATE_INT_H */
