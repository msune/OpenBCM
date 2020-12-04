/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#ifndef BCMINT_LTSW_MBCM_OOB_H
#define BCMINT_LTSW_MBCM_OOB_H

#include <bcm/oob.h>
#include <bcm/types.h>

/*!
 * \brief Initialize OOB module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_init_f)(int unit);

/*!
 * \brief Detach OOB module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_detach_f)(int unit);

/*!
 * \brief Set OOB Tx Queue configuration profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id OOB Tx Queue configuration profile id.
 * \param [in] count The number of Queue configurations in the config array.
 * \param [in] config Queue configuration array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_queue_profile_set_f)(
    int unit,
    int profile_id,
    int count,
    bcm_oob_fc_tx_queue_config_t *config);

/*!
 * \brief Retrieve OOB Tx Queue configuration profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id OOB Tx Queue configuration profile id.
 * \param [in] max_count Allocated number of Queue configurations.
 * \param [out] config Queue configuration array.
 * \param [out] count The number of Queue configurations returned.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_queue_profile_get_f)(
    int unit,
    int profile_id,
    int max_count,
    bcm_oob_fc_tx_queue_config_t *config,
    int *count);

/*!
 * \brief Set logical port to OOB port mapping.
 *
 * \param [in] unit Unit Number.
 * \param [in] count The number of device port to OOB port mappings.
 * \param [in] port_array Logical port array.
 * \param [in] oob_port_array OOB port array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_port_mapping_set_f)(
    int unit,
    int count,
    int *port_array,
    int *oob_port_array);

/*!
 * \brief Retrieve logical port to OOB port mapping.
 *
 * \param [in] unit Unit Number.
 * \param [in] max_count Allocated number of device port to oob port mappings.
 * \param [in] port_array Logical port array.
 * \param [out] oob_port_array Returned OOB port array.
 * \param [out] count The number of mappings returned.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_port_mapping_get_f)(
    int unit,
    int max_count,
    int *port_array,
    int *oob_port_array,
    int *count);

/*!
 * \brief Configure the global configuration parameters for OOB Flow Control Tx.
 *
 * \param [in] unit Unit Number.
 * \param [in] config OOB Tx global configuration structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_config_set_f)(
    int unit,
    bcm_oob_fc_tx_config_t *config);

/*!
 * \brief Retrieve the global configuration parameters for OOB Flow Control Tx.
 *
 * \param [in] unit Unit Number.
 * \param [out] config OOB Tx global configuration structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_config_get_f)(
    int unit,
    bcm_oob_fc_tx_config_t *config);

/*!
 * \brief Retrieve the OOB Flow Control Tx global information.
 *
 * \param [in] unit Unit Number.
 * \param [out] info Pointer to OOB Flow Control Tx global information structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_tx_info_get_f)(
    int unit,
    bcm_oob_fc_tx_info_t *info);

/*!
 * \brief Set OOB queue profile id for a port.
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] profile_id OOB queue profile id.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_egr_profile_id_set_f)(
    int unit,
    bcm_port_t port,
    int profile_id);

/*!
 * \brief Get OOB queue profile id on a port.
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [out] profile_id OOB queue profile id.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_egr_profile_id_get_f)(
    int unit,
    bcm_port_t port,
    int *profile_id);

/*!
 * \brief Get OOB queue profile number.
 *
 * \param [in] unit Unit Number.
 * \param [out] num OOB queue profile number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_egr_profile_num_get_f)(
    int unit,
    int *num);

/*!
 * \brief Set OOB port configuration(enable/disable OOB notification on a port).
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] egress 0 = Ingreess, 1 = Egress.
 * \param [in] enable Enable/Disable congestion State reporting.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_port_control_set_f)(
    int unit,
    bcm_port_t port,
    int egress,
    int enable);

/*!
 * \brief Get OOB port configuration(OOB notification status on a port).
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] egress 0 = Ingreess, 1 = Egress.
 * \param [out] enable Enable/Disable congestion State reporting.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
typedef int (*oob_port_control_get_f)(
    int unit,
    bcm_port_t port,
    int egress,
    int *enable);

/*!
 * \brief Oob driver structure.
 */
typedef struct mbcm_ltsw_oob_drv_s {

    /*! Initialize OOB module. */
    oob_init_f oob_init;

    /*! Detach OOB module. */
    oob_detach_f oob_detach;

    /*! Set OOB Tx Queue configuration profile. */
    oob_tx_queue_profile_set_f oob_tx_queue_profile_set;

    /*! Retrieve OOB Tx Queue configuration profile. */
    oob_tx_queue_profile_get_f oob_tx_queue_profile_get;

    /*! Set logical port to OOB port mapping. */
    oob_tx_port_mapping_set_f oob_tx_port_mapping_set;

    /*! Retrieve logical port to OOB port mapping. */
    oob_tx_port_mapping_get_f oob_tx_port_mapping_get;

    /*! Configure the global configuration parameters for OOB Flow Control Tx. */
    oob_tx_config_set_f oob_tx_config_set;

    /*! Retrieve the global configuration parameters for OOB Flow Control Tx. */
    oob_tx_config_get_f oob_tx_config_get;

    /*! Retrieve the OOB Flow Control Tx global information. */
    oob_tx_info_get_f oob_tx_info_get;

    /*! Set OOB queue profile id for a port. */
    oob_egr_profile_id_set_f oob_egr_profile_id_set;

    /*! Get OOB queue profile id on a port. */
    oob_egr_profile_id_get_f oob_egr_profile_id_get;

    /*! Get OOB queue profile number. */
    oob_egr_profile_num_get_f oob_egr_profile_num_get;

    /*! Set OOB port configuration(enable/disable OOB notification on a port). */
    oob_port_control_set_f oob_port_control_set;

    /*! Get OOB port configuration(OOB notification status on a port). */
    oob_port_control_get_f oob_port_control_get;

} mbcm_ltsw_oob_drv_t;

/*!
 * \brief Set the OOB driver of the device.
 *
 * \param [in] unit Unit Number.
 * \param [in] drv Oob driver to set.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_drv_set(
    int unit,
    mbcm_ltsw_oob_drv_t *drv);

/*!
 * \brief Initialize OOB module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_init(int unit);

/*!
 * \brief Detach OOB module.
 *
 * \param [in] unit Unit Number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_detach(int unit);

/*!
 * \brief Set OOB Tx Queue configuration profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id OOB Tx Queue configuration profile id.
 * \param [in] count The number of Queue configurations in the config array.
 * \param [in] config Queue configuration array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_queue_profile_set(
    int unit,
    int profile_id,
    int count,
    bcm_oob_fc_tx_queue_config_t *config);

/*!
 * \brief Retrieve OOB Tx Queue configuration profile.
 *
 * \param [in] unit Unit Number.
 * \param [in] profile_id OOB Tx Queue configuration profile id.
 * \param [in] max_count Allocated number of Queue configurations.
 * \param [out] config Queue configuration array.
 * \param [out] count The number of Queue configurations returned.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_queue_profile_get(
    int unit,
    int profile_id,
    int max_count,
    bcm_oob_fc_tx_queue_config_t *config,
    int *count);

/*!
 * \brief Set logical port to OOB port mapping.
 *
 * \param [in] unit Unit Number.
 * \param [in] count The number of device port to OOB port mappings.
 * \param [in] port_array Logical port array.
 * \param [in] oob_port_array OOB port array.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_port_mapping_set(
    int unit,
    int count,
    int *port_array,
    int *oob_port_array);

/*!
 * \brief Retrieve logical port to OOB port mapping.
 *
 * \param [in] unit Unit Number.
 * \param [in] max_count Allocated number of device port to oob port mappings.
 * \param [in] port_array Logical port array.
 * \param [out] oob_port_array Returned OOB port array.
 * \param [out] count The number of mappings returned.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_port_mapping_get(
    int unit,
    int max_count,
    int *port_array,
    int *oob_port_array,
    int *count);

/*!
 * \brief Configure the global configuration parameters for OOB Flow Control Tx.
 *
 * \param [in] unit Unit Number.
 * \param [in] config OOB Tx global configuration structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_config_set(
    int unit,
    bcm_oob_fc_tx_config_t *config);

/*!
 * \brief Retrieve the global configuration parameters for OOB Flow Control Tx.
 *
 * \param [in] unit Unit Number.
 * \param [out] config OOB Tx global configuration structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_config_get(
    int unit,
    bcm_oob_fc_tx_config_t *config);

/*!
 * \brief Retrieve the OOB Flow Control Tx global information.
 *
 * \param [in] unit Unit Number.
 * \param [out] info Pointer to OOB Flow Control Tx global information structure.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_tx_info_get(
    int unit,
    bcm_oob_fc_tx_info_t *info);

/*!
 * \brief Set OOB queue profile id for a port.
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] profile_id OOB queue profile id.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_egr_profile_id_set(
    int unit,
    bcm_port_t port,
    int profile_id);

/*!
 * \brief Get OOB queue profile id on a port.
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [out] profile_id OOB queue profile id.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_egr_profile_id_get(
    int unit,
    bcm_port_t port,
    int *profile_id);

/*!
 * \brief Get OOB queue profile number.
 *
 * \param [in] unit Unit Number.
 * \param [out] num OOB queue profile number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_egr_profile_num_get(
    int unit,
    int *num);

/*!
 * \brief Set OOB port configuration(enable/disable OOB notification on a port).
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] egress 0 = Ingreess, 1 = Egress.
 * \param [in] enable Enable/Disable congestion State reporting.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_port_control_set(
    int unit,
    bcm_port_t port,
    int egress,
    int enable);

/*!
 * \brief Get OOB port configuration(OOB notification status on a port).
 *
 * \param [in] unit Unit Number.
 * \param [in] port Port id.
 * \param [in] egress 0 = Ingreess, 1 = Egress.
 * \param [out] enable Enable/Disable congestion State reporting.
 *
 * \retval SHR_E_NONE No errors.
 * \retval !SHR_E_NONE Failure.
 */
extern int
mbcm_ltsw_oob_port_control_get(
    int unit,
    bcm_port_t port,
    int egress,
    int *enable);

#endif /* BCMINT_LTSW_MBCM_OOB_H */
