/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMI_LTSW_IFA_H
#define BCMI_LTSW_IFA_H

#include <sal/sal_types.h>

/*!
 * \brief Application switch control type of IFA for a specific device.
 */
typedef enum bcmi_ltsw_ifa_control_s {

    /*! IFA protocol value. */
    bcmiIfaControlIfaProtocol = 0,

    /*! IFA probemarker1 value. */
    bcmiIfaControlIntProbeMarker1 = 1,

    /*! IFA probemarker2 value. */
    bcmiIfaControlIntProbeMarker2 = 2,

    /*! IFA control type count. */
    bcmiIfaControlCount = 3

} bcmi_ltsw_ifa_control_t;

#define BCMI_LTSW_IFA_CONTROL_STR \
{ \
    "IfaProtocol", \
    "IntProbeMarker1", \
    "IntProbeMarker2" \
}

/*!
 * \brief Specify IFA switch control behaviors.
 *
 * \param [in] unit Unit Number.
 * \param [in] control The desired configuration parameter to modify.
 * \param [in] value The value with which to set the parameter.
 *
 * \retval SHR_E_NONE Success.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_ifa_control_set(
    int unit,
    bcmi_ltsw_ifa_control_t control,
    uint32_t value);

/*!
 * \brief Retrieve IFA switch control behaviors.
 *
 * \param [in] unit Unit Number.
 * \param [in] control The desired configuration parameter to retrieve.
 * \param [out] value Pointer to where the retrieved value will be written.
 *
 * \retval SHR_E_NONE Success.
 * \retval !SHR_E_NONE Failure.
 */
extern int
bcmi_ltsw_ifa_control_get(
    int unit,
    bcmi_ltsw_ifa_control_t control,
    uint32_t *value);

#endif /* BCMI_LTSW_IFA_H */
