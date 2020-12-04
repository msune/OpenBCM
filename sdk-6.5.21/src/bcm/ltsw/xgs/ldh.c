/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

#include <bcm/latency_monitor.h>

#include <bcm_int/ltsw/xgs/ldh.h>
#include <bcm_int/ltsw/lt_intf.h>

#include <shr/shr_debug.h>
#include <bcmltd/chip/bcmltd_str.h>
#include <bcmlt/bcmlt.h>

/******************************************************************************
 * Local definitions
 */

#define BSL_LOG_MODULE BSL_LS_BCM_LATENCY_MONITOR

/******************************************************************************
 * Private functions
 */


static int
ldh_monitor_enable(int unit, uint8_t monitor_id, uint8_t enable)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {MONITORs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;
    field[1].u.val = enable;

    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_set(unit, MON_LDH_CONTROLs, &lt_entry, NULL));

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_monitor_count_mode_set(
        int unit, uint8_t monitor_id, bcm_latency_monitor_count_mode_t mode)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {COUNT_MODEs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;
    field[1].flags |= BCMI_LT_FIELD_F_SYMBOL;
    switch (mode) {
        case bcmLatencyMonitorCutThrough:
            field[1].u.sym_val = CUT_THROUGHs;
            break;
        case bcmLatencyMonitorStoreAndForward:
            field[1].u.sym_val = STORE_AND_FORWARDs;
            break;
        case bcmLatencyMonitorCountAll:
            field[1].u.sym_val = COUNT_ALLs;
            break;
        default:
            SHR_ERR_EXIT(SHR_E_PARAM);
    }

    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_set(unit, MON_LDH_CONTROLs, &lt_entry, NULL));

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_monitor_count_mode_get(
        int unit, uint8_t monitor_id, bcm_latency_monitor_count_mode_t *mode)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {COUNT_MODEs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    int rv;
    bcmlt_field_def_t fld_def;

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;
    field[1].flags |= BCMI_LT_FIELD_F_SYMBOL;

    rv = bcmi_lt_entry_get(unit,
                           MON_LDH_CONTROLs,
                           &lt_entry,
                           NULL, NULL);
    if (rv == SHR_E_NOT_FOUND) {
        SHR_IF_ERR_EXIT
            (bcmi_lt_field_def_get(unit, MON_LDH_CONTROLs,
                                   field[1].fld_name, &fld_def));
        if (!sal_strcmp(fld_def.sym_def, CUT_THROUGHs)) {
            *mode = bcmLatencyMonitorCutThrough;
        } else if (!sal_strcmp(fld_def.sym_def, STORE_AND_FORWARDs)) {
            *mode = bcmLatencyMonitorStoreAndForward;
        } else if (!sal_strcmp(fld_def.sym_def, COUNT_ALLs)) {
            *mode = bcmLatencyMonitorCountAll;
        } else {
            SHR_ERR_EXIT(SHR_E_INTERNAL);
        }
    } else {
        SHR_IF_ERR_EXIT(rv);
        if (!sal_strcmp(field[1].u.sym_val, CUT_THROUGHs)) {
            *mode = bcmLatencyMonitorCutThrough;
        } else if (!sal_strcmp(field[1].u.sym_val, STORE_AND_FORWARDs)) {
            *mode = bcmLatencyMonitorStoreAndForward;
        } else if (!sal_strcmp(field[1].u.sym_val, COUNT_ALLs)) {
            *mode = bcmLatencyMonitorCountAll;
        } else {
            SHR_ERR_EXIT(SHR_E_INTERNAL);
        }
    }
exit:
    SHR_FUNC_EXIT();
}

static int
ldh_monitor_count_action_set(int unit, uint8_t monitor_id, uint32_t action)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {CTR_EGR_EFLEX_ACTIONs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;
    field[1].u.val = action;

    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_set(unit, MON_LDH_CONTROLs, &lt_entry, NULL));

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_monitor_count_action_get(int unit, uint8_t monitor_id, uint32_t *action)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {CTR_EGR_EFLEX_ACTIONs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    int rv;
    bcmlt_field_def_t fld_def;

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;

    rv = bcmi_lt_entry_get(unit,
                           MON_LDH_CONTROLs,
                           &lt_entry,
                           NULL, NULL);
    if (rv == SHR_E_NOT_FOUND) {
        SHR_IF_ERR_EXIT
            (bcmi_lt_field_def_get(unit, MON_LDH_CONTROLs,
                                   field[1].fld_name,
                                   &fld_def));
        *action = fld_def.def;
    } else {
        SHR_IF_ERR_EXIT(rv);
        *action = field[1].u.val;
    }

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_port_config_set(int unit, int port, bool ingress,
                    uint8_t monitor_id, bool enable)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {PORT_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {MONITOR_STATEs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = port;
    field[1].idx = monitor_id;

    field[1].u.sym_val = enable ? MONITOR_ACTIVEs : MONITOR_INACTIVEs;
    field[1].flags |= BCMI_LT_FIELD_F_ARRAY | BCMI_LT_FIELD_F_ELE_VALID |
                      BCMI_LT_FIELD_F_SYMBOL;

    if (ingress) {
        SHR_IF_ERR_EXIT
            (bcmi_lt_entry_set(unit, MON_ING_LDH_PORTs, &lt_entry, NULL));
    } else {
        SHR_IF_ERR_EXIT
            (bcmi_lt_entry_set(unit, MON_EGR_LDH_PORTs, &lt_entry, NULL));
    }

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_port_config_get(int unit, int port, bool ingress,
                    uint8_t monitor_id, bool *enable)
{
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {PORT_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
        /*1*/ {MONITOR_STATEs, BCMI_LT_FIELD_F_GET, 0, {0}},
    };
    int rv = SHR_E_NONE;
    const char *lt_name;
    bcmlt_field_def_t fld_def;

    SHR_FUNC_ENTER(unit);

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = port;
    field[1].idx = monitor_id;
    field[1].flags |= BCMI_LT_FIELD_F_ARRAY | BCMI_LT_FIELD_F_SYMBOL;;

    if (ingress) {
        lt_name = MON_ING_LDH_PORTs;
    } else {
        lt_name = MON_EGR_LDH_PORTs;
    }

    rv = bcmi_lt_entry_get(unit, lt_name, &lt_entry, NULL, NULL);
    if (rv == SHR_E_NOT_FOUND) {
        SHR_IF_ERR_EXIT
            (bcmi_lt_field_def_get(unit, lt_name,
                                   field[1].fld_name,
                                   &fld_def));

        if (!sal_strcmp(fld_def.sym_def, MONITOR_ACTIVEs)) {
            *enable = true;
        } else {
            *enable = false;
        }
    } else {
        SHR_IF_ERR_EXIT(rv);
        if (!sal_strcmp(field[1].u.sym_val, MONITOR_ACTIVEs)) {
            *enable = true;
        } else {
            *enable = false;
        }
    }

exit:
    SHR_FUNC_EXIT();
}

static int
ldh_port_table_clear_cb(int unit, const char *lt_name,
                        bcmlt_entry_handle_t ent_hdl, void *cookie)
{
    uint64_t port_id;
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {PORT_IDs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (bcmlt_entry_field_get(ent_hdl,
                               PORT_IDs,
                               &port_id));

    lt_entry.fields = field;
    lt_entry.nfields = sizeof(field)/sizeof(field[0]);
    lt_entry.attr = 0;

    field[0].u.val = port_id;

    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_delete(unit, lt_name, &lt_entry, NULL));
exit:
    SHR_FUNC_EXIT();
}

static int
ldh_table_clear_cb(int unit, const char *lt_name, bcmlt_entry_handle_t ent_hdl,
                   void *cookie)
{
    uint64_t monitor_id;
    bcmi_lt_entry_t lt_entry;
    bcmi_lt_field_t field[] =
    {
        /*0*/ {MON_LDH_INSTANCEs, BCMI_LT_FIELD_F_SET, 0, {0}},
    };

    SHR_FUNC_ENTER(unit);
    SHR_IF_ERR_EXIT
        (bcmlt_entry_field_get(ent_hdl,
                               MON_LDH_INSTANCEs,
                               &monitor_id));

    lt_entry.fields = field;
    lt_entry.nfields = 1;
    lt_entry.attr = 0;

    field[0].u.val = monitor_id;

    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_delete(unit, lt_name, &lt_entry, NULL));
exit:
    SHR_FUNC_EXIT();
}

static int
ldh_monitor_table_clear(int unit)
{
    SHR_FUNC_ENTER(unit);
    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_traverse(unit, MON_ING_LDH_PORTs,
                                NULL, ldh_port_table_clear_cb));
    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_traverse(unit, MON_EGR_LDH_PORTs,
                                NULL, ldh_port_table_clear_cb));
    SHR_IF_ERR_EXIT
        (bcmi_lt_entry_traverse(unit, MON_LDH_CONTROLs,
                                NULL, ldh_table_clear_cb));
exit:
    SHR_FUNC_EXIT();
}

/******************************************************************************
 * Public functions
 */

int
xgs_ltsw_ldh_monitor_table_clear(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_table_clear(unit));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_port_enable_get(
    int unit,
    int port,
    bool ingress,
    uint8_t monitor_id,
    bool *enable)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_port_config_get(unit, port, ingress, monitor_id, enable));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_port_enable_set(
    int unit,
    int port,
    bool ingress,
    uint8_t monitor_id,
    bool enable)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_port_config_set(unit, port, ingress, monitor_id, enable));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_count_mode_set(
    int unit,
    uint8_t monitor_id,
    bcm_latency_monitor_count_mode_t mode)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_count_mode_set(unit, monitor_id, mode));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_count_mode_get(
    int unit,
    uint8_t monitor_id,
    bcm_latency_monitor_count_mode_t *mode)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_count_mode_get(unit, monitor_id, mode));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_count_action_set(
    int unit,
    uint8_t monitor_id,
    uint32_t action)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_count_action_set(unit, monitor_id, action));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_count_action_get(
    int unit,
    uint8_t monitor_id,
    uint32_t *action)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_count_action_get(unit, monitor_id, action));
exit:
    SHR_FUNC_EXIT();
}

int
xgs_ltsw_ldh_monitor_enable(
    int unit,
    uint8_t monitor_id,
    uint8_t enable)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (ldh_monitor_enable(unit, monitor_id, enable));
exit:
    SHR_FUNC_EXIT();
}

