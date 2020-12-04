/***********************************************************************************
 *                                                                                 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/***********************************************************************************
 ***********************************************************************************
 *                                                                                 *
 *  Revision      :   *
 *                                                                                 *
 *  Description   :  Read/Write macros to Falcon16 IP's uC RAM's User variables    *
 */

/** @file falcon16_api_uc_vars_rdwr_defns.h
 * Read/Write macros to Falcon16 IP's uC RAM's User variables
 */

/* THIS FILE IS GENERATED USING AN AUTOMATED SCRIPT... PLEASE DO NOT EDIT THIS FILE DIRECTLY !!! */


#ifndef FALCON16_API_UC_VARS_RDWR_DEFNS_H
#define FALCON16_API_UC_VARS_RDWR_DEFNS_H

/************************************/
/*  Serdes IP RAM access functions  */
/************************************/

/* RAM access functions for lane_var_struct variables */
#define rdv_config_word()                                            falcon16_v1l4p1_rdwl_uc_var(sa__,__ERR,0x0)
#define wrv_config_word(wr_val)                                      falcon16_v1l4p1_wrwl_uc_var(sa__,0x0,wr_val)
#define rdv_usr_ctrl_fast_link_recovery_byte()                       falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x2)
#define wrv_usr_ctrl_fast_link_recovery_byte(wr_val)                 falcon16_v1l4p1_wrbl_uc_var(sa__,0x2,wr_val)
#define rdv_usr_ctrl_clk90_offset_adjust()                           falcon16_v1l4p1_rdbls_uc_var(sa__,__ERR,0x3)
#define wrv_usr_ctrl_clk90_offset_adjust(wr_val)                     falcon16_v1l4p1_wrbls_uc_var(sa__,0x3,wr_val)
#define rdv_usr_ctrl_clk90_offset_override()                         falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x4)
#define wrv_usr_ctrl_clk90_offset_override(wr_val)                   falcon16_v1l4p1_wrbl_uc_var(sa__,0x4,wr_val)
#define rdv_usr_ctrl_lane_event_log_level()                          falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x5)
#define wrv_usr_ctrl_lane_event_log_level(wr_val)                    falcon16_v1l4p1_wrbl_uc_var(sa__,0x5,wr_val)
#define rdv_usr_ctrl_vertical_threshold_adjust()                     falcon16_v1l4p1_rdbls_uc_var(sa__,__ERR,0x6)
#define wrv_usr_ctrl_vertical_threshold_adjust(wr_val)               falcon16_v1l4p1_wrbls_uc_var(sa__,0x6,wr_val)
#define rdv_usr_ctrl_cl93n72_frc_byte()                              falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x7)
#define wrv_usr_ctrl_cl93n72_frc_byte(wr_val)                        falcon16_v1l4p1_wrbl_uc_var(sa__,0x7,wr_val)
#define rdv_usr_ctrl_disable_startup_functions_word()                falcon16_v1l4p1_rdwl_uc_var(sa__,__ERR,0x8)
#define wrv_usr_ctrl_disable_startup_functions_word(wr_val)          falcon16_v1l4p1_wrwl_uc_var(sa__,0x8,wr_val)
#define rdv_usr_ctrl_disable_steady_state_functions_word()           falcon16_v1l4p1_rdwl_uc_var(sa__,__ERR,0xa)
#define wrv_usr_ctrl_disable_steady_state_functions_word(wr_val)     falcon16_v1l4p1_wrwl_uc_var(sa__,0xa,wr_val)
#define rdv_usr_ctrl_disable_startup_dfe_functions_byte()            falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0xc)
#define wrv_usr_ctrl_disable_startup_dfe_functions_byte(wr_val)      falcon16_v1l4p1_wrbl_uc_var(sa__,0xc,wr_val)
#define rdv_usr_ctrl_disable_steady_state_dfe_functions_byte()       falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0xd)
#define wrv_usr_ctrl_disable_steady_state_dfe_functions_byte(wr_val) falcon16_v1l4p1_wrbl_uc_var(sa__,0xd,wr_val)
#define rdv_usr_sts_restart_counter()                                falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0xe)
#define wrv_usr_sts_restart_counter(wr_val)                          falcon16_v1l4p1_wrbl_uc_var(sa__,0xe,wr_val)
#define rdv_usr_sts_reset_counter()                                  falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0xf)
#define wrv_usr_sts_reset_counter(wr_val)                            falcon16_v1l4p1_wrbl_uc_var(sa__,0xf,wr_val)
#define rdv_usr_sts_pmd_lock_counter()                               falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x10)
#define wrv_usr_sts_pmd_lock_counter(wr_val)                         falcon16_v1l4p1_wrbl_uc_var(sa__,0x10,wr_val)
#define rdv_usr_sts_heye_left()                                      falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x11)
#define wrv_usr_sts_heye_left(wr_val)                                falcon16_v1l4p1_wrbl_uc_var(sa__,0x11,wr_val)
#define rdv_usr_sts_heye_right()                                     falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x12)
#define wrv_usr_sts_heye_right(wr_val)                               falcon16_v1l4p1_wrbl_uc_var(sa__,0x12,wr_val)
#define rdv_usr_sts_veye_upper()                                     falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x13)
#define wrv_usr_sts_veye_upper(wr_val)                               falcon16_v1l4p1_wrbl_uc_var(sa__,0x13,wr_val)
#define rdv_usr_sts_veye_lower()                                     falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x14)
#define wrv_usr_sts_veye_lower(wr_val)                               falcon16_v1l4p1_wrbl_uc_var(sa__,0x14,wr_val)
#define rdv_usr_sts_micro_stopped()                                  falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x15)
#define wrv_usr_sts_micro_stopped(wr_val)                            falcon16_v1l4p1_wrbl_uc_var(sa__,0x15,wr_val)
#define rdv_usr_sts_link_time()                                      falcon16_v1l4p1_rdwl_uc_var(sa__,__ERR,0x16)
#define wrv_usr_sts_link_time(wr_val)                                falcon16_v1l4p1_wrwl_uc_var(sa__,0x16,wr_val)
#define rdv_usr_diag_status()                                        falcon16_v1l4p1_rdwl_uc_var(sa__,__ERR,0x18)
#define wrv_usr_diag_status(wr_val)                                  falcon16_v1l4p1_wrwl_uc_var(sa__,0x18,wr_val)
#define rdv_usr_diag_rd_ptr()                                        falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x1a)
#define wrv_usr_diag_rd_ptr(wr_val)                                  falcon16_v1l4p1_wrbl_uc_var(sa__,0x1a,wr_val)
#define rdv_usr_diag_mode()                                          falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x1b)
#define wrv_usr_diag_mode(wr_val)                                    falcon16_v1l4p1_wrbl_uc_var(sa__,0x1b,wr_val)
#define rdv_usr_main_tap_est()                                       falcon16_v1l4p1_rdwls_uc_var(sa__,__ERR,0x1c)
#define wrv_usr_main_tap_est(wr_val)                                 falcon16_v1l4p1_wrwls_uc_var(sa__,0x1c,wr_val)
#define rdv_usr_sts_phase_hoffset()                                  falcon16_v1l4p1_rdbls_uc_var(sa__,__ERR,0x1e)
#define wrv_usr_sts_phase_hoffset(wr_val)                            falcon16_v1l4p1_wrbls_uc_var(sa__,0x1e,wr_val)
#define rdv_usr_diag_wr_ptr()                                        falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x1f)
#define wrv_usr_diag_wr_ptr(wr_val)                                  falcon16_v1l4p1_wrbl_uc_var(sa__,0x1f,wr_val)
#define rdv_status_byte()                                            falcon16_v1l4p1_rdbl_uc_var(sa__,__ERR,0x79)
#define wrv_status_byte(wr_val)                                      falcon16_v1l4p1_wrbl_uc_var(sa__,0x79,wr_val)

/* RAM access functions for core_var_struct variables */
#define rdcv_config_word()                                           falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x0)
#define wrcv_config_word(wr_val)                                     falcon16_v1l4p1_wrwc_uc_var(sa__,0x0,wr_val)
#define rdcv_config_pll1_word()                                      falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x2)
#define wrcv_config_pll1_word(wr_val)                                falcon16_v1l4p1_wrwc_uc_var(sa__,0x2,wr_val)
#define rdcv_common_ucode_version()                                  falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x4)
#define wrcv_common_ucode_version(wr_val)                            falcon16_v1l4p1_wrwc_uc_var(sa__,0x4,wr_val)
#define rdcv_avg_tmon_reg13bit()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x6)
#define wrcv_avg_tmon_reg13bit(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x6,wr_val)
#define rdcv_trace_mem_rd_idx()                                      falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x8)
#define wrcv_trace_mem_rd_idx(wr_val)                                falcon16_v1l4p1_wrwc_uc_var(sa__,0x8,wr_val)
#define rdcv_trace_mem_wr_idx()                                      falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0xa)
#define wrcv_trace_mem_wr_idx(wr_val)                                falcon16_v1l4p1_wrwc_uc_var(sa__,0xa,wr_val)
#define rdcv_temp_idx()                                              falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0xc)
#define wrcv_temp_idx(wr_val)                                        falcon16_v1l4p1_wrbc_uc_var(sa__,0xc,wr_val)
#define rdcv_usr_ctrl_core_event_log_level()                         falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0xd)
#define wrcv_usr_ctrl_core_event_log_level(wr_val)                   falcon16_v1l4p1_wrbc_uc_var(sa__,0xd,wr_val)
#define rdcv_common_ucode_minor_version()                            falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0xe)
#define wrcv_common_ucode_minor_version(wr_val)                      falcon16_v1l4p1_wrbc_uc_var(sa__,0xe,wr_val)
#define rdcv_afe_hardware_version()                                  falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0xf)
#define wrcv_afe_hardware_version(wr_val)                            falcon16_v1l4p1_wrbc_uc_var(sa__,0xf,wr_val)
#define rdcv_status_byte()                                           falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0x10)
#define wrcv_status_byte(wr_val)                                     falcon16_v1l4p1_wrbc_uc_var(sa__,0x10,wr_val)
#define rdcv_diag_max_time_control()                                 falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0x11)
#define wrcv_diag_max_time_control(wr_val)                           falcon16_v1l4p1_wrbc_uc_var(sa__,0x11,wr_val)
#define rdcv_diag_max_err_control()                                  falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0x12)
#define wrcv_diag_max_err_control(wr_val)                            falcon16_v1l4p1_wrbc_uc_var(sa__,0x12,wr_val)
#define rdcv_misc_ctrl_byte()                                        falcon16_v1l4p1_rdbc_uc_var(sa__,__ERR,0x13)
#define wrcv_misc_ctrl_byte(wr_val)                                  falcon16_v1l4p1_wrbc_uc_var(sa__,0x13,wr_val)
#define rdcv_dummy()                                                 falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x14)
#define wrcv_dummy(wr_val)                                           falcon16_v1l4p1_wrwc_uc_var(sa__,0x14,wr_val)
#define rdcv_ahb_reg_address_0()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x20)
#define wrcv_ahb_reg_address_0(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x20,wr_val)
#define rdcv_ahb_reg_address_1()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x22)
#define wrcv_ahb_reg_address_1(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x22,wr_val)
#define rdcv_ahb_reg_address_2()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x24)
#define wrcv_ahb_reg_address_2(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x24,wr_val)
#define rdcv_ahb_reg_address_3()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x26)
#define wrcv_ahb_reg_address_3(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x26,wr_val)
#define rdcv_ahb_reg_address_4()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x28)
#define wrcv_ahb_reg_address_4(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x28,wr_val)
#define rdcv_ahb_reg_address_5()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x2a)
#define wrcv_ahb_reg_address_5(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x2a,wr_val)
#define rdcv_ahb_reg_address_6()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x2c)
#define wrcv_ahb_reg_address_6(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x2c,wr_val)
#define rdcv_ahb_reg_address_7()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x2e)
#define wrcv_ahb_reg_address_7(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x2e,wr_val)
#define rdcv_ahb_reg_address_8()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x30)
#define wrcv_ahb_reg_address_8(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x30,wr_val)
#define rdcv_ahb_reg_address_9()                                     falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x32)
#define wrcv_ahb_reg_address_9(wr_val)                               falcon16_v1l4p1_wrwc_uc_var(sa__,0x32,wr_val)
#define rdcv_ahb_reg_data_0()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x34)
#define wrcv_ahb_reg_data_0(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x34,wr_val)
#define rdcv_ahb_reg_data_1()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x36)
#define wrcv_ahb_reg_data_1(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x36,wr_val)
#define rdcv_ahb_reg_data_2()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x38)
#define wrcv_ahb_reg_data_2(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x38,wr_val)
#define rdcv_ahb_reg_data_3()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x3a)
#define wrcv_ahb_reg_data_3(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x3a,wr_val)
#define rdcv_ahb_reg_data_4()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x3c)
#define wrcv_ahb_reg_data_4(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x3c,wr_val)
#define rdcv_ahb_reg_data_5()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x3e)
#define wrcv_ahb_reg_data_5(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x3e,wr_val)
#define rdcv_ahb_reg_data_6()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x40)
#define wrcv_ahb_reg_data_6(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x40,wr_val)
#define rdcv_ahb_reg_data_7()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x42)
#define wrcv_ahb_reg_data_7(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x42,wr_val)
#define rdcv_ahb_reg_data_8()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x44)
#define wrcv_ahb_reg_data_8(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x44,wr_val)
#define rdcv_ahb_reg_data_9()                                        falcon16_v1l4p1_rdwc_uc_var(sa__,__ERR,0x46)
#define wrcv_ahb_reg_data_9(wr_val)                                  falcon16_v1l4p1_wrwc_uc_var(sa__,0x46,wr_val)

#endif
