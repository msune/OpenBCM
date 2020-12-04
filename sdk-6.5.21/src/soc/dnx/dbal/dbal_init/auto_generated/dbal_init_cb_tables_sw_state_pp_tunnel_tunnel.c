
/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

shr_error_e
srv6_sid_formats_per_tunnel_gport_sw_indirect_table_size_0_cb(
int unit,
void * entry_handle,
dbal_fields_e current_mapped_field_id,
uint32 * offset)
{
    int phy_db_size__inlif_2;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FORMULA_CB_GET_PHYDB_SIZE(unit, DBAL_PHYSICAL_TABLE_INLIF_2, phy_db_size__inlif_2);
    *offset = phy_db_size__inlif_2/dnx_data_lif.in_lif.inlif_minimum_index_size_get(unit);
    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}
