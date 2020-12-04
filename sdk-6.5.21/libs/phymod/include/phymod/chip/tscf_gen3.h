/*
 *         
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 *         
 *     
 * DO NOT EDIT THIS FILE!
 */

#ifndef _TSCF_GEN3_H__H_
#define _TSCF_GEN3_H__H_

#include <phymod/phymod_definitions.h>
/*Initialize phymod module*/
int tscf_gen3_core_identify(const phymod_core_access_t* core, uint32_t core_id, uint32_t* is_identified);

/*Retrive core information*/
int tscf_gen3_core_info_get(const phymod_core_access_t* core, phymod_core_info_t* info);

/*Set\get lane mapping*/
int tscf_gen3_core_lane_map_set(const phymod_core_access_t* core, const phymod_lane_map_t* lane_map);
int tscf_gen3_core_lane_map_get(const phymod_core_access_t* core, phymod_lane_map_t* lane_map);

/*Reset Core*/
int tscf_gen3_core_reset_set(const phymod_core_access_t* core, phymod_reset_mode_t reset_mode, phymod_reset_direction_t direction);
int tscf_gen3_core_reset_get(const phymod_core_access_t* core, phymod_reset_mode_t reset_mode, phymod_reset_direction_t* direction);

/*Retrive firmware information*/
int tscf_gen3_core_firmware_info_get(const phymod_core_access_t* core, phymod_core_firmware_info_t* fw_info);

/*Set\get firmware operation mode*/
int tscf_gen3_phy_firmware_core_config_set(const phymod_phy_access_t* phy, phymod_firmware_core_config_t fw_core_config);
int tscf_gen3_phy_firmware_core_config_get(const phymod_phy_access_t* phy, phymod_firmware_core_config_t* fw_core_config);

/*Set\get firmware operation mode*/
int tscf_gen3_phy_firmware_lane_config_set(const phymod_phy_access_t* phy, phymod_firmware_lane_config_t fw_lane_config);
int tscf_gen3_phy_firmware_lane_config_get(const phymod_phy_access_t* phy, phymod_firmware_lane_config_t* fw_lane_config);

/*Start\Stop the sequencer*/
int tscf_gen3_core_pll_sequencer_restart(const phymod_core_access_t* core, uint32_t flags, phymod_sequencer_operation_t operation);

/*Wait for core event*/
int tscf_gen3_core_wait_event(const phymod_core_access_t* core, phymod_core_event_t event, uint32_t timeout);

/* re-tune rx path*/
int tscf_gen3_phy_rx_restart(const phymod_phy_access_t* phy);

/*Set phy polarity*/
int tscf_gen3_phy_polarity_set(const phymod_phy_access_t* phy, const phymod_polarity_t* polarity);
int tscf_gen3_phy_polarity_get(const phymod_phy_access_t* phy, phymod_polarity_t* polarity);

/*Set\Get TX Parameters*/
int tscf_gen3_phy_tx_set(const phymod_phy_access_t* phy, const phymod_tx_t* tx);
int tscf_gen3_phy_tx_get(const phymod_phy_access_t* phy, phymod_tx_t* tx);

/*Set\Get TX override Parameters*/
int tscf_gen3_phy_tx_override_set(const phymod_phy_access_t* phy, const phymod_tx_override_t* tx_override);
int tscf_gen3_phy_tx_override_get(const phymod_phy_access_t* phy, phymod_tx_override_t* tx_override);

/*Set/get TXPI config: enable/disable it and set work mode. */
int tscf_gen3_phy_txpi_config_set(const phymod_phy_access_t* phy, const phymod_txpi_config_t* config);
int tscf_gen3_phy_txpi_config_get(const phymod_phy_access_t* phy, phymod_txpi_config_t* config);

/*Set\Get RX Parameters*/
int tscf_gen3_phy_rx_set(const phymod_phy_access_t* phy, const phymod_rx_t* rx);
int tscf_gen3_phy_rx_get(const phymod_phy_access_t* phy, phymod_rx_t* rx);

/*PHY Rx adaptation resume*/
int tscf_gen3_phy_rx_adaptation_resume(const phymod_phy_access_t* phy);

/*Reset phy*/
int tscf_gen3_phy_reset_set(const phymod_phy_access_t* phy, const phymod_phy_reset_t* reset);
int tscf_gen3_phy_reset_get(const phymod_phy_access_t* phy, phymod_phy_reset_t* reset);

/*Control phy power*/
int tscf_gen3_phy_power_set(const phymod_phy_access_t* phy, const phymod_phy_power_t* power);
int tscf_gen3_phy_power_get(const phymod_phy_access_t* phy, phymod_phy_power_t* power);

/*Control phy hg2 codec*/
int tscf_gen3_phy_hg2_codec_control_set(const phymod_phy_access_t* phy, phymod_phy_hg2_codec_t hg2_codec);
int tscf_gen3_phy_hg2_codec_control_get(const phymod_phy_access_t* phy, phymod_phy_hg2_codec_t* hg2_codec);

/*TX transmission control*/
int tscf_gen3_phy_tx_lane_control_set(const phymod_phy_access_t* phy, phymod_phy_tx_lane_control_t tx_control);
int tscf_gen3_phy_tx_lane_control_get(const phymod_phy_access_t* phy, phymod_phy_tx_lane_control_t* tx_control);

/*Rx control*/
int tscf_gen3_phy_rx_lane_control_set(const phymod_phy_access_t* phy, phymod_phy_rx_lane_control_t rx_control);
int tscf_gen3_phy_rx_lane_control_get(const phymod_phy_access_t* phy, phymod_phy_rx_lane_control_t* rx_control);

/*forced speed FEC control*/
int tscf_gen3_phy_fec_enable_set(const phymod_phy_access_t* phy, uint32_t enable);
int tscf_gen3_phy_fec_enable_get(const phymod_phy_access_t* phy, uint32_t* enable);

/*Change OUI to consortium OUI*/
int tscf_gen3_phy_autoneg_oui_set(const phymod_phy_access_t* phy, phymod_autoneg_oui_t an_oui);
int tscf_gen3_phy_autoneg_oui_get(const phymod_phy_access_t* phy, phymod_autoneg_oui_t* an_oui);

/*energy efficient control*/
int tscf_gen3_phy_eee_set(const phymod_phy_access_t* phy, uint32_t enable);
int tscf_gen3_phy_eee_get(const phymod_phy_access_t* phy, uint32_t* enable);

/*Set the interface mode, speed and other configuration related to interface.*/
int tscf_gen3_phy_interface_config_set(const phymod_phy_access_t* phy, uint32_t flags, const phymod_phy_inf_config_t* config);
int tscf_gen3_phy_interface_config_get(const phymod_phy_access_t* phy, uint32_t flags, phymod_ref_clk_t ref_clock, phymod_phy_inf_config_t* config);

/*Set\Get CL72*/
int tscf_gen3_phy_cl72_set(const phymod_phy_access_t* phy, uint32_t cl72_en);
int tscf_gen3_phy_cl72_get(const phymod_phy_access_t* phy, uint32_t* cl72_en);

/*Get CL72 status*/
int tscf_gen3_phy_cl72_status_get(const phymod_phy_access_t* phy, phymod_cl72_status_t* status);

/*Set\Get autoneg*/
int tscf_gen3_phy_autoneg_ability_set(const phymod_phy_access_t* phy, const phymod_autoneg_ability_t* an_ability_set_type);
int tscf_gen3_phy_autoneg_ability_get(const phymod_phy_access_t* phy, phymod_autoneg_ability_t* an_ability_get_type);

/*Get  remote link autoneg*/
int tscf_gen3_phy_autoneg_remote_ability_get(const phymod_phy_access_t* phy, phymod_autoneg_ability_t* an_ability_get_type);

/*Set\Get autoneg*/
int tscf_gen3_phy_autoneg_set(const phymod_phy_access_t* phy, const phymod_autoneg_control_t* an);
int tscf_gen3_phy_autoneg_get(const phymod_phy_access_t* phy, phymod_autoneg_control_t* an, uint32_t* an_done);

/*Get Autoneg status*/
int tscf_gen3_phy_autoneg_status_get(const phymod_phy_access_t* phy, phymod_autoneg_status_t* status);

/*Core Initialization*/
int tscf_gen3_core_init(const phymod_core_access_t* core, const phymod_core_init_config_t* init_config, const phymod_core_status_t* core_status);

/*Core vco freq get function*/
int tscf_gen3_phy_pll_multiplier_get(const phymod_phy_access_t* phy, uint32_t* core_vco_pll_multiplier);

/*Phy Initialization*/
int tscf_gen3_phy_init(const phymod_phy_access_t* phy, const phymod_phy_init_config_t* init_config);

/*Set\get loopback mode*/
int tscf_gen3_phy_loopback_set(const phymod_phy_access_t* phy, phymod_loopback_mode_t loopback, uint32_t enable);
int tscf_gen3_phy_loopback_get(const phymod_phy_access_t* phy, phymod_loopback_mode_t loopback, uint32_t* enable);

/*Get rx pmd locked indication*/
int tscf_gen3_phy_rx_pmd_locked_get(const phymod_phy_access_t* phy, uint32_t* rx_pmd_locked);

/*Get rx pmd locked indication*/
int tscf_gen3_phy_rx_signal_detect_get(const phymod_phy_access_t* phy, uint32_t* rx_signal_detect);

/*Get link up status indication*/
int tscf_gen3_phy_link_status_get(const phymod_phy_access_t* phy, uint32_t* link_status);

/*Set/Get User Speed Paramateres*/
int tscf_gen3_phy_pcs_userspeed_set(const phymod_phy_access_t* phy, const phymod_pcs_userspeed_config_t* config);
int tscf_gen3_phy_pcs_userspeed_get(const phymod_phy_access_t* phy, phymod_pcs_userspeed_config_t* config);

/*Read phymod register*/
int tscf_gen3_phy_reg_read(const phymod_phy_access_t* phy, uint32_t reg_addr, uint32_t* val);

/*Write phymod register*/
int tscf_gen3_phy_reg_write(const phymod_phy_access_t* phy, uint32_t reg_addr, uint32_t val);

/*Set/Get timesync enable*/
int tscf_gen3_timesync_enable_set(const phymod_phy_access_t* phy, uint32_t flags, uint32_t enable);
int tscf_gen3_timesync_enable_get(const phymod_phy_access_t* phy, uint32_t flags, uint32_t* enable);

/*Set/Get timesync ts_offset*/
int tscf_gen3_timesync_offset_set(const phymod_core_access_t* core, uint32_t ts_offset);
int tscf_gen3_timesync_offset_get(const phymod_core_access_t* core, uint32_t* ts_offset);

/*Set timesync adjust*/
int tscf_gen3_timesync_adjust_set(const phymod_phy_access_t* phy, uint32_t flags, phymod_timesync_compensation_mode_t ts_am_norm_mode);

/*eye margin estimate get*/
int tscf_gen3_phy_eye_margin_est_get(const phymod_phy_access_t* phy, phymod_eye_margin_mode_t eye_margin_mode, uint32_t* value);

/*tscf16_rescal*/
int tscf_gen3_phy_rescal_set(const phymod_phy_access_t* phy, uint32_t enable, uint32_t value);
int tscf_gen3_phy_rescal_get(const phymod_phy_access_t* phy, uint32_t* value);

/* Set/Get synce clock config*/
int tscf_gen3_phy_synce_clk_ctrl_set(const phymod_phy_access_t* phy, phymod_synce_clk_ctrl_t cfg);
int tscf_gen3_phy_synce_clk_ctrl_get(const phymod_phy_access_t* phy, phymod_synce_clk_ctrl_t* cfg);

/*Get rx ppm*/
int tscf_gen3_phy_rx_ppm_get(const phymod_phy_access_t* phy, int16_t* rx_ppm);

/*Get timestamp tx info*/
int tscf_gen3_timesync_tx_info_get(const phymod_phy_access_t* phy, phymod_ts_fifo_status_t* ts_tx_info);

/*Set or get fec bypass indication. Valid for RS-FEC.*/
int tscf_gen3_phy_fec_bypass_indication_set(const phymod_phy_access_t* phy, uint32_t enable);
int tscf_gen3_phy_fec_bypass_indication_get(const phymod_phy_access_t* phy, uint32_t* enable);

/* get the PMD oversample mode */
int tscf_gen3_phy_osr_mode_get(const phymod_phy_access_t* phy, phymod_osr_mode_t* osr_mode);

/* get the ref clk value */
int tscf_gen3_phy_ref_clk_get(const phymod_phy_access_t* phy, phymod_ref_clk_t* ref_clk);

#endif /*_TSCF_GEN3_H_*/
