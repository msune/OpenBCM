/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMINT_LTSW_XFS_IPMC_H
#define BCMINT_LTSW_XFS_IPMC_H

#include <bcm/ipmc.h>
#include <bcm_int/ltsw/flexctr.h>

#include <bcm_int/ltsw/ipmc_int.h>

#include <sal/sal_types.h>

/*!
 * \brief L2 IPMC fields.
 */
typedef enum xfs_ltsw_ipmc_l2_fld_id_s {

    /*! Destination IP Address. */
    XFS_LTSW_IPMC_L2_FLD_DIP_0 = 0,

    /*! Destination IP Address (for IPv6 128b). */
    XFS_LTSW_IPMC_L2_FLD_DIP_1 = 1,

    /*! Source IP Address. */
    XFS_LTSW_IPMC_L2_FLD_SIP_0 = 2,

    /*! Source IP Address (for IPv6 128b). */
    XFS_LTSW_IPMC_L2_FLD_SIP_1 = 3,

    /*! VFI. */
    XFS_LTSW_IPMC_L2_FLD_VFI = 4,

    /*! Index of the strength profile table for this entry. */
    XFS_LTSW_IPMC_L2_FLD_STRENGTH_PROF_IDX = 5,

    /*! Destination object. */
    XFS_LTSW_IPMC_L2_FLD_DEST = 6,

    /*! Destination type. */
    XFS_LTSW_IPMC_L2_FLD_DEST_TYPE = 7,

    /*! Class ID */
    XFS_LTSW_IPMC_L2_FLD_CLASS_ID = 8,

    /*! Misc ctrl 0 */
    XFS_LTSW_IPMC_L2_FLD_MISC_0 = 9,

    /*! Misc ctrl 1 */
    XFS_LTSW_IPMC_L2_FLD_MISC_1 = 10,

    /*! Opaque object */
    XFS_LTSW_IPMC_L2_FLD_OPQ_OBJ = 11,

    /*! Flex counter action */
    XFS_LTSW_IPMC_L2_FLD_FLEXCTR_ACTION = 12,

    /*! Enable wide view */
    XFS_LTSW_IPMC_L2_FLD_WIDE_VIEW_EN = 13,

    /*! The last one, not valid. */
    XFS_LTSW_IPMC_L2_FLD_CNT = 14

} xfs_ltsw_ipmc_l2_fld_id_t;

#define XFS_LTSW_IPMC_L2_FLD_ID_STR \
{ \
    "DIP_0", \
    "DIP_1", \
    "SIP_0", \
    "SIP_1", \
    "VFI", \
    "STRENGTH_PROF_IDX", \
    "DEST", \
    "DEST_TYPE", \
    "CLASS_ID", \
    "MISC_0", \
    "MISC_1", \
    "OPQ_OBJ", \
    "FLEXCTR_ACTION", \
    "WIDE_VIEW_EN", \
    "CNT" \
}

/*!
 * \brief L2 IPMC tables.
 */
typedef enum xfs_ltsw_ipmc_l2_tbl_id_s {

    /*! L2 IPv4 Multicast table. */
    XFS_LTSW_IPMC_L2_TBL_IPV4 = 0,

    /*!  */
    XFS_LTSW_IPMC_L2_TBL_IPV4_WIDE = 1,

    /*!  */
    XFS_LTSW_IPMC_L2_TBL_IPV4_SG = 2,

    /*! L2 IPv6 Multicast table. */
    XFS_LTSW_IPMC_L2_TBL_IPV6 = 3,

    /*!  */
    XFS_LTSW_IPMC_L2_TBL_IPV6_SG = 4,

    /*!  */
    XFS_LTSW_IPMC_L2_TBL_IPV4_CONFIG = 5,

    /*! The last one, not valid. */
    XFS_LTSW_IPMC_L2_TBL_CNT = 6

} xfs_ltsw_ipmc_l2_tbl_id_t;

#define XFS_LTSW_IPMC_L2_TBL_ID_STR \
{ \
    "IPV4", \
    "IPV4_WIDE", \
    "IPV4_SG", \
    "IPV6", \
    "IPV6_SG", \
    "IPV4_CONFIG", \
    "CNT" \
}

/*! Indicate IPv4 MC tables. */
#define XFS_LTSW_IPMC_L2_TBL_ATTR_V4 0x00000001

/*! Indicate IPv6 MC tables. */
#define XFS_LTSW_IPMC_L2_TBL_ATTR_V6 0x00000002

/*! Indicate MC (*, G) tables. */
#define XFS_LTSW_IPMC_L2_TBL_ATTR_G 0x00000004

/*! Indicate MC (S, G) tables. */
#define XFS_LTSW_IPMC_L2_TBL_ATTR_SG 0x00000008

/*!
 * \brief Initialize IPMC module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_init(int unit);

/*!
 * \brief De-initialize IPMC module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_detach(int unit);

/*!
 * \brief Get the public info of IPMC module.
 *
 * \param [in] unit Unit Number.
 * \param [out] mc_pub Returned mc public info.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_pub_info_get(
    int unit,
    bcmint_ipmc_pub_info_t *mc_pub);

/*!
 * \brief Add an IPMC entry for L2 domain.
 *
 * \param [in] unit Unit Number.
 * \param [in] data IPMC entry information.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_add(
    int unit,
    bcm_ipmc_addr_t *data);

/*!
 * \brief Remove an IPMC entry for L2 domain.
 *
 * \param [in] unit Unit Number.
 * \param [in] data IPMC entry information.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_remove(
    int unit,
    bcm_ipmc_addr_t *data);

/*!
 * \brief Get an IPMC entry for L2 domain.
 *
 * \param [in] unit Unit Number.
 * \param [in] data IPMC entry information.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_find(
    int unit,
    bcm_ipmc_addr_t *data);

/*!
 * \brief Traverse valid IPMC entry for L2 domain.
 *
 * \param [in] unit Unit Number.
 * \param [in] flags BCM_IPMC_XXX flags.
 * \param [in] cb User callback function, called once per IPMC entry for L2 domain.
 * \param [in] user_data Cookie.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_traverse(
    int unit,
    uint32_t flags,
    bcm_ipmc_traverse_cb cb,
    void *user_data);

/*!
 * \brief Delete all IPMC entry for L2 domain.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_delete_all(int unit);

/*!
 * \brief Attach counter entries to the given L2 IPMC.
 *
 * \param [in] unit Unit Number.
 * \param [in] info L2 IPMC entry info.
 * \param [in] ci Flex counter info.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_flexctr_attach(
    int unit,
    bcm_ipmc_addr_t *info,
    bcmi_ltsw_flexctr_counter_info_t *ci);

/*!
 * \brief Detach counter entries from the given L2 IPMC.
 *
 * \param [in] unit Unit Number.
 * \param [in] info L2 IPMC entry info.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_flexctr_detach(
    int unit,
    bcm_ipmc_addr_t *info);

/*!
 * \brief Get counter info from the given L2 IPMC.
 *
 * \param [in] unit Unit Number.
 * \param [in] info L2 IPMC entry info.
 * \param [out] ci Flex counter info.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_flexctr_info_get(
    int unit,
    bcm_ipmc_addr_t *info,
    bcmi_ltsw_flexctr_counter_info_t *ci);

/*!
 * \brief Set flexctr object value for the given L2 IPMC.
 *
 * \param [in] unit Unit Number.
 * \param [in] info L2 IPMC entry info.
 * \param [in] value Flex counter object value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_flexctr_object_set(
    int unit,
    bcm_ipmc_addr_t *info,
    uint32_t value);

/*!
 * \brief Get the flexctr object value from the given L2 IPMC.
 *
 * \param [in] unit Unit Number.
 * \param [in] info L2 IPMC entry info.
 * \param [out] value Flex counter object value.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
xfs_ltsw_ipmc_l2_flexctr_object_get(
    int unit,
    bcm_ipmc_addr_t *info,
    uint32_t *value);

#endif /* BCMINT_LTSW_XFS_IPMC_H */
