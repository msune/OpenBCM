/**************************************************************************************
 **************************************************************************************
 *                                                                                    *
 *  Revision      :  $Id: falcon_furia_dependencies.h 816 2014-12-05 02:44:44Z kirand $ *
 *                                                                                    *
 *  Description   :  API Dependencies to be provided by IP user                       *
 *                                                                                    *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.                                                              *
 *  No portions of this material may be reproduced in any form without                *
 *  the written permission of:                                                        *
 *      Broadcom Corporation                                                          *
 *      5300 California Avenue                                                        *
 *      Irvine, CA  92617                                                             *
 *                                                                                    *
 *  All information contained in this document is Broadcom Corporation                *
 *  company private proprietary, and trade secret.                                    *
 */

/** @file falcon_furia_dependencies.h
 * Dependencies to be provided by IP User
 */

#ifndef FALCON_FURIA_API_DEPENDENCIES_H
#define FALCON_FURIA_API_DEPENDENCIES_H

#include "falcon_furia_sesto_usr_includes.h"
#include "../common/srds_api_err_code.h"
#include "falcon_furia_sesto_ipconfig.h"
#include <phymod/phymod.h>

/** Read a register from the currently selected Serdes IP Lane.
 * @param address Address of register to be read
 * @param *val value read out from the register
 * @return Error code generated by read function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_pmd_rdt_reg(const phymod_access_t *pa,uint16_t address, uint16_t *val);           

/** Write to a register from the currently selected Serdes IP Lane.
 * @param address Address of register to be written
 * @param val Value to be written to the register
 * @return Error code generated by write function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_pmd_wr_reg(const phymod_access_t *pa,uint16_t address, uint16_t val); 

/** Masked Register Write to the currently selected Serdes IP core/lane.
 * If using Serdes MDIO controller to access the registers, implement this function using falcon_furia_sesto_pmd_mdio_mwr_reg(..)
 *
 * If NOT using a Serdes MDIO controller or the Serdes PMI Masked write feature, please use the following code to
 * implement this function
 *
 *    falcon_furia_sesto_pmd_wr_reg(const phymod_access_t *pa,addr, ((falcon_furia_sesto_pmd_rd_reg(addr) & ~mask) | (mask & (val << lsb))));
 *
 * @param addr Address of register to be written
 * @param mask 16-bit mask indicating the position of the field with bits of 1s
 * @param lsb  LSB of the field
 * @param val  16bit value to be written
 * @return Error code generated by write function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_pmd_mwr_reg(const phymod_access_t *pa,uint16_t addr, uint16_t mask, uint8_t lsb, uint16_t val); 

/** Delay the execution of the code for atleast specified amount of time in nanoseconds.
 * This function is used ONLY for delays less than 1 microsecond, non-zero error code may be returned otherwise.
 * The user can implement this as an empty function if their register access latency exceeds 1 microsecond.
 * @param delay_ns Delay in nanoseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_delay_ns(uint16_t delay_ns); 

/** Delay the execution of the code for atleast specified amount of time in microseconds.
 * For longer delays, accuracy is required. When requested delay is > 100ms, the implemented delay is assumed 
 * to be < 10% bigger than requested.
 * This function is used ONLY for delays greater than or equal to 1 microsecond.
 * @param delay_us Delay in microseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_delay_us(uint32_t delay_us);

/** Delay the execution of the code for atleast specified amount of time in milliseconds.
 * For longer delays, accuracy is required. When requested delay is > 100ms, the implemented delay is assumed 
 * to be < 10% bigger than requested.
 * This function is used ONLY for delays greater than or equal to 1 millisecond.
 * @param delay_ms Delay in milliseconds
 * @return Error code generated by delay function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_delay_ms(uint32_t delay_ms);

/** Return the address of current selected Serdes IP lane.
 * @return the IP level address of the current lane. 0 to N-1, for an N lane IP
 */
uint8_t falcon_furia_sesto_get_lane(const phymod_access_t *pa);

/** Return the address of current selected Serdes IP Core.
 * @return the IP level address of the current core.
 */
uint8_t falcon_furia_sesto_get_core(const phymod_access_t *pa);

/** Polls for register field "uc_dsc_ready_for_cmd" to be 1 within the time interval specified by timeout_ms.
 * Function returns 0 if polling passes, else it returns error code. 
 * Define macro CUSTOM_REG_POLLING to replace the default implementation provided in falcon_furia_sesto_functions.c.
 * @param timeout_ms Maximum time interval in milliseconds for which the polling is done
 * @return Error code generated by polling function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_poll_uc_dsc_ready_for_cmd_equals_1( const phymod_access_t *pa, uint32_t timeout_ms);

/** Polls lane variable "usr_diag_status" to verify data is available in uC diag buffer.
 * It then reads a WORD of data wich is 2 float8_t samples, it converts them to uint32_t
 * and returns them in the memory pointed to by *data.
 *
 * @param *data is pointer to 2 element array of uint32_tpassed from uC through dsc_data
 * @param *status returns a status byte           \n
 *    bit 15 - indicates the ey scan is complete \n
 *    bit 14 - indicates uC is slower than read access \n
 *    bit 13 - indicates uC is faster than read access \n
 *    bit 7-0 - indicates amount of data in the uC buffer 
 *
 * @param timeout_ms Maximum time interval in milliseconds for which the polling is done
 * @return Error code generated by polling function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_poll_diag_eye_data(const phymod_access_t *pa,uint32_t *data,uint16_t *status, uint32_t timeout_ms);

/** Polls lane variable "usr_diag_status" to verify data is available in uC diag buffer.
 *
 * @param *status returns a status byte \n
 *    bit 15 - indicates the ey scan is complete \n
 *    bit 14-0 - reserved for debug
 *
 * @param timeout_ms Maximum time interval in milliseconds for which the polling is done
 * @return Error code generated by polling function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_poll_diag_done( const phymod_access_t *pa, uint16_t *status, uint32_t timeout_ms);

/** Polls for register field "dsc_state" to be "DSC_STATE_UC_TUNE"
 * within the time interval specified by timeout_ms.
 * Function returns 0 if polling passes, else it returns error code. 
 * Define macro CUSTOM_REG_POLLING to replace the default implementation provided in
 * falcon_furia_sesto_functions.c. 
 * @param timeout_ms Maximum time interval in milliseconds for which the polling is done
 * @return Error code generated by polling function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_poll_dsc_state_equals_uc_tune( const phymod_access_t *pa, uint32_t timeout_ms);

/** Convert uC lane index.
* Convert uC lane index to system ID string.
* @param *string an output pointer pointed to system ID
* @param uc_lane_idx uC lane index
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_uc_lane_idx_to_system_id(const phymod_access_t *pa, const char *string , uint8_t uc_lane_idx);

/*-----------------------------------*/
/*  Serdes uC Lane Info Structure    */
/*-----------------------------------*/

/** uC Lane Info Struct */
typedef struct {
    /** Direct RAM access available */
    uint8_t   is_direct_ram_access_avail;
    /** Core variable base address */
    uint16_t  core_var_base_address;
    /** Trace memory base address */
    uint16_t  trace_mem_base_address;
    /** Lane variable base address */
    uint16_t  lane_var_base_address;
    /** Diagnostic base address [tracemem_size/num_uc_lanes*uc_lane_idx] */
    uint16_t  diag_base_address; 
    /** Micro Lane index */
    uint8_t   uc_lane_idx;
    /** RAM size available to each lane */
    uint16_t  lane_ram_size;
    /** Maximum index into diag lane memory (tracemem_size/num_uc_lanes - 1) */  
    uint16_t  diag_max_idx;     
    /** Trace Memory size */
	uint16_t  trace_mem_size;
    /** Number of Lanes */
    uint8_t   num_lanes;
} falcon_furia_sesto_uc_lane_info_st;

/** Retrieve Lane Based Information.
* Retrieve current lane memory address information.
* @param *ext_uc_lane_info an output pointer pointed to uC lane info struct
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_get_uc_ln_info(const phymod_access_t *pa, falcon_furia_sesto_uc_lane_info_st *ext_uc_lane_info);

/*---------------------------------------------*/
/*  Serdes IP RAM access - Lane RAM Variables  */
/*---------------------------------------------*/
/*          rd - read; wr - write              */ 
/*          b  - byte; w  - word               */
/*---------------------------------------------*/
/** Unsigned Word Read of a uC RAM variable.
* Write access through Micro Register Interface for PMD IPs. Output is in little-endian format (LSB is the lower address).
* @param *rd_val 16bit unsigned value to be read from RAM variable
* @param addr Address of RAM variable to be read
* @param size Size of RAM in word to be read
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_rdw_ram(const phymod_access_t *pa, uint16_t *rd_val, uint16_t addr, uint16_t size);

/** Unsigned Byte Read of a uC RAM variable.
* Write access through Micro Register Interface for PMD IPs. 
* @param *rd_val 8bit unsigned value to be read from RAM variable
* @param addr Address of RAM variable to be read
* @param size Size of RAM in byte to be read
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_rdb_ram(const phymod_access_t *pa, uint8_t *rd_val, uint16_t addr, uint16_t size);

/** Unsigned Byte Write of a uC RAM variable.
* Write access through Micro Register Interface for PMD IPs.
* @param addr Address of RAM variable to be written
* @param size Size of RAM in byte to be written
* @param *wr_val 8bit unsigned value to be written to RAM variable
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_wrb_ram(const phymod_access_t *pa, uint16_t addr, uint16_t size, uint8_t *wr_val);

/** Unsigned Word Write of a uC RAM variable.
* Write access through Micro Register Interface for PMD IPs.
* @param addr Address of RAM variable to be written
* @param size Size of RAM in word to be written
* @param *wr_val 16bit unsigned value to be written to RAM variable
* @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
*/ 
err_code_t falcon_furia_sesto_wrw_ram(const phymod_access_t *pa, uint16_t addr, uint16_t size, uint16_t *wr_val);

/** Polls for register field "st_afe_tx_fifo_resetb" to be 1 within the time interval specified by timeout_ms.
 * Function returns 0 if polling passes, else it returns error code.
 * Define macro CUSTOM_REG_POLLING to replace the default implementation provided in falcon_furia_sesto_functions.c.
 * @param timeout_ms Maximum time interval in milliseconds for which the polling is done
 * @return Error code generated by polling function (returns ERR_CODE_NONE if no errors)  
 */
err_code_t falcon_furia_sesto_poll_st_afe_tx_fifo_resetb_equals_1( const phymod_access_t *pa, uint32_t timeout_ms);


#endif
