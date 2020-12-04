/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMI_LTSW_UFT_H
#define BCMI_LTSW_UFT_H

#include <bcm/switch.h>

#include <bcm_int/ltsw/uft_int.h>

#include <sal/sal_types.h>

/*!
 * \brief UFT mode.
 */
typedef enum bcmi_ltsw_uft_mode_s {

    /*! Invalid UFT mode */
    bcmiUftModeInvalid = 0,

    /*! UFT mode 1 */
    bcmiUftMode1 = 1,

    /*! UFT mode 2 */
    bcmiUftMode2 = 2,

    /*! UFT mode 3 */
    bcmiUftMode3 = 3,

    /*! UFT mode 4 */
    bcmiUftMode4 = 4,

    /*! UFT mode 5 */
    bcmiUftMode5 = 5,

    /*! UFT mode 6 */
    bcmiUftMode6 = 6,

    /*! UFT mode 7 */
    bcmiUftMode7 = 7,

    /*! UFT mode 8 */
    bcmiUftMode8 = 8,

    /*! UFT mode 9 */
    bcmiUftMode9 = 9,

    /*! UFT mode 10 */
    bcmiUftMode10 = 10,

    /*! UFT mode 11 */
    bcmiUftMode11 = 11,

    /*! UFT mode 12 */
    bcmiUftMode12 = 12,

    /*! UFT mode 13 */
    bcmiUftMode13 = 13,

    /*! UFT mode 14 */
    bcmiUftMode14 = 14,

    /*! UFT mode 15 */
    bcmiUftMode15 = 15,

    /*! UFT mode 16 */
    bcmiUftMode16 = 16,

    /*! UFT mode 17 */
    bcmiUftMode17 = 17,

    /*! UFT mode 18 */
    bcmiUftMode18 = 18,

    /*! UFT mode 19 */
    bcmiUftMode19 = 19,

    /*! UFT mode 20 */
    bcmiUftMode20 = 20,

    /*! UFT mode 21 */
    bcmiUftMode21 = 21,

    /*! Count of UFT modes. */
    bcmiUftModeCount = 22

} bcmi_ltsw_uft_mode_t;

#define BCMI_LTSW_UFT_MODE_STR \
{ \
    "ModeInvalid", \
    "Mode1", \
    "Mode2", \
    "Mode3", \
    "Mode4", \
    "Mode5", \
    "Mode6", \
    "Mode7", \
    "Mode8", \
    "Mode9", \
    "Mode10", \
    "Mode11", \
    "Mode12", \
    "Mode13", \
    "Mode14", \
    "Mode15", \
    "Mode16", \
    "Mode17", \
    "Mode18", \
    "Mode19", \
    "Mode20", \
    "Mode21", \
    "ModeCount" \
}

/*!
 * \brief Switch hash table to logical table mapping.
 */
typedef struct bcmi_ltsw_uft_table_map_s {

    /*! Logical table. */
    const char *table;

    /*! EM group attribute. */
    int group_attr;

    /*! Hash table. */
    int hash_table;

} bcmi_ltsw_uft_table_map_t;

/*!
 * \brief Initializes the UFT module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_init(int unit);

/*!
 * \brief De-initializes the UFT module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_detach(int unit);

/*!
 * \brief Get the current UFT mode.
 *
 * \param [in] unit Unit Number.
 * \param [out] uft_mode UFT mode.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_mode_get(
    int unit,
    bcmi_ltsw_uft_mode_t *uft_mode);

/*!
 * \brief Set the maximum number of entry moves for hash reordering.
 *
 * \param [in] unit Unit Number.
 * \param [in] type Move depth switch control type.
 * \param [in] arg Move depth value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_multi_move_depth_set(
    int unit,
    bcm_switch_control_t type,
    int arg);

/*!
 * \brief Get the maximum number of entry moves for hash reordering.
 *
 * \param [in] unit Unit Number.
 * \param [in] type Move depth switch control type.
 * \param [out] arg Move depth value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_multi_move_depth_get(
    int unit,
    bcm_switch_control_t type,
    int *arg);

/*!
 * \brief Get information about a hash bank.
 *
 * \param [in] unit Unit Number.
 * \param [in/out] bank_info Hash bank information structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_info_get(
    int unit,
    bcm_switch_hash_bank_info_t *bank_info);

/*!
 * \brief Get the UFT banks assigned to a hash table.
 *
 * \param [in] unit Unit Number.
 * \param [in] hash_table Hash table.
 * \param [in] array_size Array size of bank_array.
 * \param [out] bank_array Hash bank array.
 * \param [out] num_banks Actual number of UFT banks returned in bank_array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_multi_get(
    int unit,
    bcm_switch_hash_table_t hash_table,
    int array_size,
    bcm_switch_hash_bank_t *bank_array,
    int *num_banks);

/*!
 * \brief Get the hash tables to which a given UFT bank is assigned.
 *
 * \param [in] unit Unit Number.
 * \param [in] bank_num UFT bank number.
 * \param [in] array_size Array size of table_array.
 * \param [out] table_array Hash table array.
 * \param [out] num_tables Actual number of hash tables returned in table_array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_table_multi_get(
    int unit,
    bcm_switch_hash_bank_t bank_num,
    int array_size,
    bcm_switch_hash_table_t *table_array,
    int *num_tables);

/*!
 * \brief UFT bank control set function.
 *
 * \param [in] unit Unit Number.
 * \param [in] bank_control Hash bank control structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_control_set(
    int unit,
    bcm_switch_hash_bank_control_t *bank_control);

/*!
 * \brief Hash bank control get function.
 *
 * \param [in] unit Unit Number.
 * \param [in/out] bank_control Hash bank control structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_control_get(
    int unit,
    bcm_switch_hash_bank_control_t *bank_control);

/*!
 * \brief Hash bank config set function.
 *
 * \param [in] unit Unit Number.
 * \param [in] hash_table Hash table.
 * \param [in] bank_num Bank number.
 * \param [in] hash_type Hash type.
 * \param [in] hash_offset Hash offset.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_config_set(
    int unit,
    bcm_switch_hash_table_t hash_table,
    uint32_t bank_num,
    int hash_type,
    uint32_t hash_offset);

/*!
 * \brief Hash bank config get function.
 *
 * \param [in] unit Unit Number.
 * \param [in] hash_table Hash table.
 * \param [in] bank_num Bank number.
 * \param [out] hash_type Hash type.
 * \param [out] hash_offset Hash offset.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_config_get(
    int unit,
    bcm_switch_hash_table_t hash_table,
    uint32_t bank_num,
    int *hash_type,
    uint32_t *hash_offset);

/*!
 * \brief Hash bank max num get function.
 *
 * \param [in] unit Unit Number.
 * \param [in] hash_table Hash table.
 * \param [out] bank_count Bank count.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_bank_max_get(
    int unit,
    bcm_switch_hash_table_t hash_table,
    uint32_t *bank_count);

/*!
 * \brief Get UFT variant database.
 *
 * \param [in] unit Unit Number.
 * \param [out] uft_var_db UFT variant database.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_uft_var_db_get(
    int unit,
    bcmint_uft_var_db_t **uft_var_db);

#endif /* BCMI_LTSW_UFT_H */
