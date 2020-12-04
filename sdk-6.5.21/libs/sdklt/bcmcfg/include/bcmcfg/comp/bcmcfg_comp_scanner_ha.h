/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by cfg from component configuration definition files.
 *
 * Tool: $SDK/INTERNAL/cfg/bin/cfg
 *
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */
#ifndef BCMCFG_COMP_SCANNER_HA_H
#define BCMCFG_COMP_SCANNER_HA_H
#ifndef DOXYGEN_IGNORE_AUTOGEN

#include <bcmcfg/bcmcfg_types.h>

/*!
 * \brief Save BCMCFG HA data for component resource.
 *
 * Save BCMCFG HA data for component resource.
 *
 * \param [in] ptr Pointer to the HA data.
 *
 * \retval SHR_E_NONE   OK
 * \retval !SHR_E_NONE  Error
 */
extern int
bcmcfg_ha_data_comp_resource_issu_report(void);

/*!
 * \brief Save BCMCFG HA data for component resource.
 *
 * Save BCMCFG HA data for component resource.
 *
 * \param [in] ptr Pointer to the HA data.
 *
 * \retval SHR_E_NONE   OK
 * \retval !SHR_E_NONE  Error
 */
extern int
bcmcfg_ha_data_comp_resource_save(uint8_t *ptr);

/*!
 * \brief Restore BCMCFG HA data for component resource.
 *
 * Restore BCMCFG HA data for component resource.
 *
 * \param [in] ptr Pointer to the HA data.
 *
 * \retval SHR_E_NONE   OK
 * \retval !SHR_E_NONE  Error
 */
extern int
bcmcfg_ha_data_comp_resource_restore(uint8_t *ptr);

#endif /* DOXYGEN_IGNORE_AUTOGEN */
#endif /* BCMCFG_COMP_SCANNER_HA_H */
