/* 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 * 
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 * search for 'sw_state_cbs_t' for the root of the struct
 */

#ifndef _SHR_SW_STATE_DPP_SOC_ARAD_TM_GUARANTEED_Q_RESOURCE_ACCESS_H_
#define _SHR_SW_STATE_DPP_SOC_ARAD_TM_GUARANTEED_Q_RESOURCE_ACCESS_H_

/********************************* access calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the access calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the access struct by 'sw_state_access_cb_init'.                  */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, CONST soc_dpp_guaranteed_q_resource_t *guaranteed_q_resource);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, soc_dpp_guaranteed_q_resource_t *guaranteed_q_resource);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_alloc */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_alloc_cb)(
    int unit, int nof_instances_to_alloc);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_is_allocated */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_is_allocated_cb)(
    int unit, uint8 *is_allocated);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_free */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_free_cb)(
    int unit);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, CONST soc_dpp_guaranteed_pair_t *dram);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, soc_dpp_guaranteed_pair_t *dram);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 total);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 *total);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 used);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 *used);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, CONST soc_dpp_guaranteed_pair_t *ocb);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, soc_dpp_guaranteed_pair_t *ocb);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 total);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 *total);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_set */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_set_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 used);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_get */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_get_cb)(
    int unit, int guaranteed_q_resource_idx_0, uint32 *used);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_verify */
typedef int (*sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_verify_cb)(
    int unit, int guaranteed_q_resource_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

/*********************************** access calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the access layer for the entire SW state.*/
/* use this tree to alloc/free/set/get fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_verify_cb verify;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_verify_cb verify;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_verify_cb verify;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_total_cbs_t total;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_used_cbs_t used;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_verify_cb verify;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_verify_cb verify;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_verify_cb verify;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_total_cbs_t total;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_used_cbs_t used;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 
#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_tm_guaranteed_q_resource_cbs_s {
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_set_cb set;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_get_cb get;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_alloc_cb alloc;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_is_allocated_cb is_allocated;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_free_cb free;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_verify_cb verify;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_dram_cbs_t dram;
    sw_state_dpp_soc_arad_tm_guaranteed_q_resource_ocb_cbs_t ocb;
} sw_state_dpp_soc_arad_tm_guaranteed_q_resource_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

int sw_state_dpp_soc_arad_tm_guaranteed_q_resource_access_cb_init(int unit);

#endif /* _SHR_SW_STATE_DPP_SOC_ARAD_TM_GUARANTEED_Q_RESOURCE_ACCESS_H_ */
