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

#ifndef _SHR_SW_STATE_DPP_SOC_ARAD_PP_VTT_ACCESS_H_
#define _SHR_SW_STATE_DPP_SOC_ARAD_PP_VTT_ACCESS_H_

/********************************* access calbacks definitions *************************************/
/* this set of callbacks, are the callbacks used in the access calbacks struct 'sw_state_cbs_t' to */
/* access the data in 'sw_state_t'.                                                                */
/* the calbacks are inserted into the access struct by 'sw_state_access_cb_init'.                  */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_set */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_set_cb)(
    int unit, CONST ARAD_VTT *vtt);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_get */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_get_cb)(
    int unit, ARAD_VTT *vtt);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_alloc */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_alloc_cb)(
    int unit);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_is_allocated */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_is_allocated_cb)(
    int unit, uint8 *is_allocated);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_free */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_free_cb)(
    int unit);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_verify */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_verify_cb)(
    int unit);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_set */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_set_cb)(
    int unit, SOC_SAND_HASH_TABLE_PTR isem_key_to_entry_id);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_get */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_get_cb)(
    int unit, SOC_SAND_HASH_TABLE_PTR *isem_key_to_entry_id);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_verify */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_verify_cb)(
    int unit);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_vt_programs_set */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_vt_programs_set_cb)(
    int unit, int vt_programs_idx_0, int vt_programs);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_vt_programs_get */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_vt_programs_get_cb)(
    int unit, int vt_programs_idx_0, int *vt_programs);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_vt_programs_verify */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_vt_programs_verify_cb)(
    int unit, int vt_programs_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_tt_programs_set */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_tt_programs_set_cb)(
    int unit, int tt_programs_idx_0, int tt_programs);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_tt_programs_get */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_tt_programs_get_cb)(
    int unit, int tt_programs_idx_0, int *tt_programs);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
/* implemented by: sw_state_dpp_soc_arad_pp_vtt_tt_programs_verify */
typedef int (*sw_state_dpp_soc_arad_pp_vtt_tt_programs_verify_cb)(
    int unit, int tt_programs_idx_0);
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

/*********************************** access calbacks struct ****************************************/
/* this set of structs, rooted at 'sw_state_cbs_t' define the access layer for the entire SW state.*/
/* use this tree to alloc/free/set/get fields in the sw state rooted at 'sw_state_t'.              */
/* NOTE: 'sw_state_t' data should not be accessed directly.                                        */
/***************************************************************************************************/

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_cbs_s {
    sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_set_cb set;
    sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_get_cb get;
    sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_verify_cb verify;
} sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_pp_vtt_vt_programs_cbs_s {
    sw_state_dpp_soc_arad_pp_vtt_vt_programs_set_cb set;
    sw_state_dpp_soc_arad_pp_vtt_vt_programs_get_cb get;
    sw_state_dpp_soc_arad_pp_vtt_vt_programs_verify_cb verify;
} sw_state_dpp_soc_arad_pp_vtt_vt_programs_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_pp_vtt_tt_programs_cbs_s {
    sw_state_dpp_soc_arad_pp_vtt_tt_programs_set_cb set;
    sw_state_dpp_soc_arad_pp_vtt_tt_programs_get_cb get;
    sw_state_dpp_soc_arad_pp_vtt_tt_programs_verify_cb verify;
} sw_state_dpp_soc_arad_pp_vtt_tt_programs_cbs_t;
#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

#ifdef BCM_PETRA_SUPPORT
#if defined(BCM_PETRA_SUPPORT)
typedef struct sw_state_dpp_soc_arad_pp_vtt_cbs_s {
    sw_state_dpp_soc_arad_pp_vtt_set_cb set;
    sw_state_dpp_soc_arad_pp_vtt_get_cb get;
    sw_state_dpp_soc_arad_pp_vtt_alloc_cb alloc;
    sw_state_dpp_soc_arad_pp_vtt_is_allocated_cb is_allocated;
    sw_state_dpp_soc_arad_pp_vtt_free_cb free;
    sw_state_dpp_soc_arad_pp_vtt_verify_cb verify;
    sw_state_dpp_soc_arad_pp_vtt_isem_key_to_entry_id_cbs_t isem_key_to_entry_id;
    sw_state_dpp_soc_arad_pp_vtt_vt_programs_cbs_t vt_programs;
    sw_state_dpp_soc_arad_pp_vtt_tt_programs_cbs_t tt_programs;
} sw_state_dpp_soc_arad_pp_vtt_cbs_t;

#endif /* defined(BCM_PETRA_SUPPORT)*/ 
#endif /* BCM_PETRA_SUPPORT*/ 

int sw_state_dpp_soc_arad_pp_vtt_access_cb_init(int unit);

#endif /* _SHR_SW_STATE_DPP_SOC_ARAD_PP_VTT_ACCESS_H_ */
