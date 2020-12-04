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

#ifndef _NULL_CELL_H__H_
#define _NULL_CELL_H__H_

#include <phymod/phymod_definitions.h>
/*Set/get the interface mode, speed and other configuration related to interface.*/
int null_phy_cell_speed_config_set(const phymod_phy_access_t* phy, const phymod_cell_speed_config_t* speed_config);
int null_phy_cell_speed_config_get(const phymod_phy_access_t* phy, phymod_cell_speed_config_t* speed_config);

/*Set\Get autoneg*/
int null_phy_cell_autoneg_set(const phymod_phy_access_t* phy, const phymod_cell_autoneg_control_t* an);
int null_phy_cell_autoneg_get(const phymod_phy_access_t* phy, phymod_cell_autoneg_control_t* an, uint32_t* an_done);

/*Get Autoneg status*/
int null_phy_cell_autoneg_status_get(const phymod_phy_access_t* phy, phymod_cell_autoneg_status_t* status);

/* Set/Get autoneg advertising abilities*/
int null_phy_cell_autoneg_advert_ability_set(const phymod_phy_access_t* phy, const phymod_cell_autoneg_advert_abilities_t* an_advert_abilities);
int null_phy_cell_autoneg_advert_ability_get(const phymod_phy_access_t* phy, phymod_cell_autoneg_advert_abilities_t* an_advert_abilities);

/* Get remote autoneg advertising abilities*/
int null_phy_cell_autoneg_remote_advert_ability_get(const phymod_phy_access_t* phy, phymod_cell_autoneg_advert_abilities_t* an_advert_abilities);

/*Get link up status indication*/
int null_phy_cell_link_status_get(const phymod_phy_access_t* phy, uint32_t* link_status);

#endif /*_NULL_CELL_H_*/
