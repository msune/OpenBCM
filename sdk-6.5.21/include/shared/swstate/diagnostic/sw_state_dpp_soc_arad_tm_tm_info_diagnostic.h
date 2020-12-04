/* 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 * search for 'sw_state_diagnostic_cbs_t' for the root of the struct
 */

#ifndef _SHR_SW_STATE_DPP_SOC_ARAD_TM_TM_INFO_DIAGNOSTIC_H_
#define _SHR_SW_STATE_DPP_SOC_ARAD_TM_TM_INFO_DIAGNOSTIC_H_

#ifdef BCM_WARM_BOOT_API_TEST
/********************************* diagnostic calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the diagnostic calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the diagnostic struct by 'sw_state_diagnostic_cb_init'.                  */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_dump_cb)(
    int unit, int tm_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0, int sysport2basequeue_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0, int sysport2basequeue_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_groups_bw_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_groups_bw_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_pg_numq_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_pg_numq_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_dump */
typedef int (*sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_dump_cb)(
    int unit, int tm_idx_0, int tm_info_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

/*********************************** diagnostic calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the diagnostic layer for the entire SW state.*/
/* use this tree to dump fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_dump_cb dump;
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_is_simple_mode_diagnostic_cbs_t is_simple_mode;
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ref_count_diagnostic_cbs_t ref_count;
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_ocb_only_ref_count_diagnostic_cbs_t ocb_only_ref_count;
} sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_diagnostic_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_dump_cb dump;
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_valid_flags_diagnostic_cbs_t valid_flags;
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_base_queue_diagnostic_cbs_t base_queue;
} sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_diagnostic_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_groups_bw_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_groups_bw_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_groups_bw_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_pg_numq_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_pg_numq_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_pg_numq_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_dump_cb dump;
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_credit_watchdog_mode_diagnostic_cbs_t credit_watchdog_mode;
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_exact_credit_watchdog_scan_time_nano_diagnostic_cbs_t exact_credit_watchdog_scan_time_nano;
} sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_diagnostic_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_dump_cb dump;
} sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_diagnostic_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_tm_info_diagnostic_cbs_s {
    sw_state_dpp_soc_arad_tm_tm_info_dump_cb dump;
    sw_state_dpp_soc_arad_tm_tm_info_is_power_saving_called_diagnostic_cbs_t is_power_saving_called;
    sw_state_dpp_soc_arad_tm_tm_info_queue_to_rate_class_mapping_diagnostic_cbs_t queue_to_rate_class_mapping;
    sw_state_dpp_soc_arad_tm_tm_info_sysport2basequeue_diagnostic_cbs_t sysport2basequeue;
    sw_state_dpp_soc_arad_tm_tm_info_queuequartet2sysport_diagnostic_cbs_t queuequartet2sysport;
    sw_state_dpp_soc_arad_tm_tm_info_groups_bw_diagnostic_cbs_t groups_bw;
    sw_state_dpp_soc_arad_tm_tm_info_hr_group_bw_diagnostic_cbs_t hr_group_bw;
    sw_state_dpp_soc_arad_tm_tm_info_rcy_single_context_port_diagnostic_cbs_t rcy_single_context_port;
    sw_state_dpp_soc_arad_tm_tm_info_rcy_reassembly_ctxt_diagnostic_cbs_t rcy_reassembly_ctxt;
    sw_state_dpp_soc_arad_tm_tm_info_rcy_channels_to_egr_nif_mapping_diagnostic_cbs_t rcy_channels_to_egr_nif_mapping;
    sw_state_dpp_soc_arad_tm_tm_info_pg_numq_diagnostic_cbs_t pg_numq;
    sw_state_dpp_soc_arad_tm_tm_info_credit_watchdog_diagnostic_cbs_t credit_watchdog;
    sw_state_dpp_soc_arad_tm_tm_info_ipf_config_mode_diagnostic_cbs_t ipf_config_mode;
} sw_state_dpp_soc_arad_tm_tm_info_diagnostic_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

int sw_state_dpp_soc_arad_tm_tm_info_diagnostic_cb_init(int unit);

#endif /* BCM_WARM_BOOT_API_TEST */

#endif /* _SHR_SW_STATE_DPP_SOC_ARAD_TM_TM_INFO_DIAGNOSTIC_H_ */
