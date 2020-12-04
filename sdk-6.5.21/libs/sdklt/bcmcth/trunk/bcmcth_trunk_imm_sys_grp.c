/*! \file bcmcth_trunk_imm_sys_grp.c
 *
 * Purpose:     handler implementation for TRUNK_SYSTEM LT.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/*******************************************************************************
 * Includes
 */
#include <shr/shr_debug.h>
#include <shr/shr_ha.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmlrd/bcmlrd_table.h>
#include <bcmmgmt/bcmmgmt_sysm.h>
#include <bcmcth/bcmcth_trunk_types.h>
#include <bcmcth/bcmcth_trunk_util.h>
#include <bcmcth/bcmcth_trunk_db.h>
#include <bcmcth/bcmcth_trunk_drv.h>
#include <bcmimm/bcmimm_int_comp.h>
#include <bcmissu/issu_api.h>
#include <bcmlrd/bcmlrd_map.h>
#include <shr/shr_pb.h>

/*******************************************************************************
 * Private variables
 */
/*! TRUNK_SYSTEM bookkeeping HA structure. */
static bcmcth_trunk_sys_grp_bk_t *sys_grp_bk[BCMDRD_CONFIG_MAX_UNITS];

/*! TRUNK_SYSTEM bookkeeping temporary structure. */
static bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp[BCMDRD_CONFIG_MAX_UNITS];

/*! TRUNK_SYSTEM group SW bitmap changed in one commit. */
SHR_BITDCL *bcmcth_trunk_sys_grp_bitmap_diff[BCMDRD_CONFIG_MAX_UNITS];

/*! Pointer to trunk group state. */
#define SYS_GRP_HA(unit)                 sys_grp_bk[unit]

/*! Pointer to trunk group temporary state. */
#define SYS_GRP_TEMP(unit)               sys_grp_bk_temp[unit]

/*! Pointer to trunk group temporary state. */
#define SYS_GRP_DIFF(unit)               bcmcth_trunk_sys_grp_bitmap_diff[unit]

#define BCMCTH_TRUNK_SYS_GRP_INFO(_u_) \
    (SYS_GRP_TEMP(_u_)->grp_ptr->sys_grp_array)

#define BCMCTH_TRUNK_SYS_GRP(_u_, _idx_) \
    (&(SYS_GRP_TEMP(_u_)->grp_ptr->sys_grp_array[_idx_]))

#define SYS_GRP_EXIST(_u_, _idx_)  \
    ((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->inserted)

#define BCMCTH_TRUNK_SYS_GRP_INSERTED_SET(_u_, _idx_, _val_)  \
    (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->inserted) = _val_)

#define SYS_GRP_MEMBER_CNT(_u_, _idx_)  \
    ((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->cnt)

#define BCMCTH_TRUNK_SYS_GRP_MEMBER_CNT_SET(_u_, _idx_, _val_)  \
    (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->cnt) = _val_)

#define SYS_GRP_MAX_MEMBERS(_u_, _idx_)  \
    ((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->max_members)

#define BCMCTH_TRUNK_SYS_GRP_MAX_MEMBERS_SET(_u_, _idx_, _val_)  \
    (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->max_members) = _val_)

#define SYS_GRP_BASE_PTR(_u_, _idx_)  \
    ((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->base_ptr)

#define SYS_GRP_PRECONFIG_SET(_u_, _idx_)            \
     (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->flags)    \
     |= (BCMCTH_TRUNK_SYSTEM_ENTRY_PRECONFIG))

#define SYS_GRP_PRECONFIG_CLEAR(_u_, _idx_)          \
     (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->flags)    \
     &= (~BCMCTH_TRUNK_SYSTEM_ENTRY_PRECONFIG))

#define SYS_GRP_PRECONFIG_GET(_u_, _idx_)          \
     (((BCMCTH_TRUNK_SYS_GRP(_u_, _idx_))->flags)  \
     & (BCMCTH_TRUNK_SYSTEM_ENTRY_PRECONFIG))

/* BSL Module TBD */
#define BSL_LOG_MODULE BSL_LS_BCMCTH_TRUNK
/*******************************************************************************
 * Private functions
 */
/*!
 * \brief Resilient hash TRUNK_SYSTEM group data print debug function.
 *
 * Resilient hash TRUNK_SYSTEM group data print debug function.
 *
 * \param [in] unit     Unit number.
 * \param [in] str      Debug string.
 * \param [in] trunk_id Resilient hash group identifier.
 * \param [in] lt_entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
rh_sys_grp_data_debug_print(int unit,
                        char *str,
                        uint32_t trunk_id,
                        bcmcth_trunk_sys_grp_param_t *lt_entry)
{
    uint32_t rh_member_cnt = 0;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;

    uint32_t idx; /* Index iterator variable. */
    shr_pb_t *pb = NULL; /* Print buffer. */

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(lt_entry, SHR_E_PARAM);

    if (lt_entry->gtype != BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
        SHR_EXIT();
    }

    SHR_NULL_CHECK(sys_grp_bk_temp_ptr->rhg[trunk_id], SHR_E_PARAM);
    /* Read the trunk group temp info. */
    sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    pb = shr_pb_create();
    if (str) {
        shr_pb_printf(pb, "%s\n", str);
    } else {
        shr_pb_printf(pb, "\n");
    }
    rh_member_cnt = sys_grp->cnt;
    shr_pb_printf(
          pb,
          "\tTRUNK_SYSTEM_ID=%-4d rh_member_cnt=%-4d members[rh_member_cnt=%-4d]:\n",
          trunk_id,
          rh_member_cnt,
          lt_entry->cnt);
    shr_pb_printf
        (pb,
         "\tFORMAT {eindex: rh_port[eindex] / mindex}");
    for (idx = 0; idx < lt_entry->max_members; idx++) {
        if (!(idx % 3)) {
            shr_pb_printf(pb, "\n\t");
        }
        shr_pb_printf(pb,
                      "%4d: %5d / %-4d",
                      idx,
                      lt_entry->rh_port[idx],
                      lt_entry->rh_mindex_arr[idx]);
    }
    shr_pb_printf(pb, "\n\n");
    shr_pb_printf
        (pb, "\t=====================================\n");
    for (idx = 0; idx < lt_entry->cnt; idx++) {
        shr_pb_printf
            (pb,
             "\t%4d) "
             "Replicas=Cur:%-4u New:%-4u]\n",
             idx,
             sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx],
             lt_entry->rh_memb_ecnt_arr[idx]);
    }
    shr_pb_printf(pb, "\n");
    LOG_ERROR(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                            "%s"), shr_pb_str(pb)));
    shr_pb_destroy(pb);
    exit:
        SHR_FUNC_EXIT();
}

static void
bcmcth_trunk_sys_grp_param_t_init(
                 bcmcth_trunk_sys_grp_param_t *entry)
{
    sal_memset(entry,
               0,
               sizeof(bcmcth_trunk_sys_grp_param_t));
    entry->rh_mindex_arr = NULL;
    entry->rh_memb_ecnt_arr = NULL;
    entry->rh_port = NULL;
}

/*!
 * \brief IMM input fields TRUNK.LB_MODE parse routine.
 *
 * Parse TRUNK_SYSTEM IMM entry field LB_MODE and save the data to entry.
 *
 * \param [in]  unit       Unit number.
 * \param [in]  data       Data field list.
 * \param [out] entry TRUNK_SYSTEM LT entry data buffer.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to convert \c in to \c LT entry.
 */
static int
bcmcth_trunk_imm_sys_grp_entry_lb_mode_parse(
                                          int unit,
                                          const bcmltd_field_t *data,
                                          bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t fid;
    uint64_t fval;
    const bcmltd_field_t *in = NULL;
    const bcmlrd_field_data_t *fdata = NULL;     /* LT field data map. */
    const bcmlrd_map_t *map = NULL;
    uint32_t lb_val = 0; /* LB mode value. */
    uint32_t i = 0;

    SHR_FUNC_ENTER(unit);

    if (SHR_FAILURE(bcmlrd_map_get(unit, TRUNK_SYSTEMt, &map))) {
        SHR_EXIT();
    }

    /* Read the TRUNK_LB_MODE before other data fields. */
    for (in = data; (in != NULL); in = in->next) {
        fid = in->id;
        fval = in->data;
        if (fid == TRUNK_SYSTEMt_LB_MODEf) {
           fdata = &(map->field_data->field[TRUNK_SYSTEMt_LB_MODEf]);
            for (i = 0; i <  fdata->edata->num_sym; i++) {
                /*
                 * LB_MODE derives the group type - group.
                 * Get the enum option value for the LB_MODE.
                 */
                lb_val = (uint32_t)fdata->edata->sym[i].val;
                if (lb_val == (uint8_t)fval) {
                    if (!sal_strcmp("RESILIENT",
                        fdata->edata->sym[i].name)) {
                        entry->lb_mode = BCMCTH_TRUNK_LB_HASH;
                        entry->gtype = BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT;
                    } else {
                        entry->lb_mode = (uint8_t)fval;
                        entry->gtype = BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR;
                    }
                }
            }
            entry->lb_mode_valid = TRUE;
            LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "TRUNK_SYSTEMt_LB_MODEf = %d.\n"),
                (uint8_t) fval));
            break;

        } else {
            continue;
        }
    }
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief IMM input fields parse routine.
 *
 * Parse TRUNK_SYSTEM IMM entry fields and save the data to entry.
 *
 * \param [in]  unit Unit number.
 * \param [in]  data field list.
 * \param [out] entry TRUNK_SYSTEM LT entry data buffer.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to convert \c in to \c LT entry.
 */
static int
bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(int unit,
                                     const bcmltd_field_t *data,
                                     bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t fid;
    uint32_t arr_idx;
    uint64_t fval;
    const bcmltd_field_t *in = NULL;
    const bcmlrd_map_t *map = NULL;
    uint16_t rh_size = 0;

    SHR_FUNC_ENTER(unit);

    if (SHR_FAILURE(bcmlrd_map_get(unit, TRUNK_SYSTEMt, &map))) {
        SHR_EXIT();
    }


    /* For each field ID read IMM table data fields for regular groups */
    for (in = data; (in != NULL); in = in->next) {
        fid = in->id;
        fval = in->data;
        arr_idx = in->idx;
        if (entry->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
            break;
        }
        if (fid == TRUNK_SYSTEMt_LB_MODEf) {
            continue;
        }
        switch (fid) {
             case TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf:
                entry->id = (uint32_t) fval;
                LOG_VERBOSE(BSL_LOG_MODULE,
                   (BSL_META_U(unit, "TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf = %d.\n"),
                    entry->id));
                break;
            case TRUNK_SYSTEMt_MAX_MEMBERSf:
               entry->max_members = (uint16_t)fval;
                entry->max_members_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_MAX_MEMBERSf = %d.\n"),
                 (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_MEMBER_CNTf:
                entry->cnt = (uint16_t)fval;
                entry->cnt_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_UC_MEMBER_CNTf = %d.\n"),
                  (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_MEMBER_PORT_IDf:
                if ((arr_idx) >= BCMCTH_TRUNK_SYSTEM_MAX_MEMBERS) {
                    LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                    "TRUNK_SYSTEMt_UC_MEMBER_PORT_IDf[%d] index invalid.\n"),
                            arr_idx));
                    SHR_ERR_EXIT(SHR_E_PARAM);
                }
                entry->port[arr_idx] = (uint8_t) fval;
                entry->port_valid[arr_idx] = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEMt_UC_MEMBER_PORT_IDf[%d] = %d.\n"),
                                arr_idx, (uint8_t) fval));
                break;
            case TRUNK_SYSTEMt_RESOLUTION_DISABLEf:
                entry->disable = (bool) fval;
                entry->disable_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_RESOLUTION_DISABLEf= %d.\n"),
                  (bool) fval));
                break;
           default:
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                         "Invalid field for TRUNK_SYSTEM %d reg_hash or random"
                         " load balancing mode group. \n"),
                                entry->id));
                break;
        }
    }

    /* For each field ID read IMM table data fields for resilient groups */
    for (in = data; (in != NULL); in = in->next) {
        fid = in->id;
        fval = in->data;
        arr_idx = in->idx;
        if (entry->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR) {
            break;
        }
        if (fid == TRUNK_SYSTEMt_LB_MODEf) {
            continue;
        }
        switch (fid) {
             case TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf:
                entry->id = (uint32_t) fval;
                LOG_VERBOSE(BSL_LOG_MODULE,
                   (BSL_META_U(unit, "TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf = %d.\n"),
                    entry->id));
                break;
            case TRUNK_SYSTEMt_RESOLUTION_DISABLEf:
                entry->disable = (bool) fval;
                entry->disable_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_RESOLUTION_DISABLEf= %d.\n"),
                  (bool) fval));
                break;
            case TRUNK_SYSTEMt_RH_SIZEf:
                rh_size = (uint16_t) fval;
                entry->max_members =
                    bcmcth_trunk_sys_grp_rh_size_to_max_members(rh_size);
                entry->max_members_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "TRUNK_SYSTEMt_RH_SIZEf = %d.\n"),
                    (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_RH_RANDOM_SEEDf:
                entry->rh_random_seed = (uint16_t) fval;
                entry->rh_random_seed_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "TRUNK_SYSTEMt_RH_RANDOM_SEEDf = %d.\n"),
                    (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_RH_MEMBER_CNTf:
                entry->cnt = (uint16_t) fval;
                entry->cnt_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "TRUNK_SYSTEMt_RH_MEMBER_CNTf = %d.\n"),
                    (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_RH_MEMBER_PORT_IDf:
                if ((arr_idx) >= BCMCTH_TRUNK_SYSTEM_RH_MAX_MEMBERS) {
                    LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit,
                    "TRUNK_SYSTEMt_RH_MEMBER_PORT_IDf[%d] index invalid.\n"),
                                    arr_idx));
                    SHR_ERR_EXIT(SHR_E_PARAM);
                }
                entry->port[arr_idx] = (uint16_t) fval;
                entry->port_valid[arr_idx] = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                        "TRUNK_SYSTEMt_RH_MEMBER_PORT_IDf[%d] = %d.\n"),
                                arr_idx, (uint16_t) fval));
                break;
           default:
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                         "Invalid field for TRUNK_SYSTEM %d reg_hash or random"
                         " load balancing mode group. \n"),
                                entry->id));
                break;
        }
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief TRUNK_SYSTEM Lt entry init function.
 *
 * Parse TRUNK_SYSTEM lt initialize the entry fields to default values.
 *
 * \param [in]  unit  Unit number.
 * \param [out] entry TRUNK_SYSTEM LT entry data buffer.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to convert \c in to \c LT entry.
 */
static int
bcmcth_trunk_sys_grp_lt_entry_def_val_get(
                                   int unit,
                                   bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t num;
    uint64_t def_val;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    if (entry->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR) {
        if (!entry->max_members_valid) {
            SHR_IF_ERR_VERBOSE_EXIT
           (bcmlrd_field_default_get(unit,
                                     TRUNK_SYSTEMt,
                                     TRUNK_SYSTEMt_MAX_MEMBERSf,
                                     1,
                                     &def_val,
                                     &num));
            entry->max_members = (uint16_t)def_val;
            entry->max_members_valid = TRUE;
        }
   } else if (entry->gtype
                   == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
        /* Resilient group type. */
        if (!entry->max_members_valid) {
            SHR_IF_ERR_VERBOSE_EXIT
               (bcmlrd_field_default_get(unit,
                                         TRUNK_SYSTEMt,
                                         TRUNK_SYSTEMt_RH_SIZEf,
                                         1,
                                         &def_val,
                                         &num));
            entry->max_members =
            bcmcth_trunk_sys_grp_rh_size_to_max_members(def_val);
            entry->max_members_valid = TRUE;
            entry->lb_mode = BCMCTH_TRUNK_LB_HASH;
            entry->lb_mode_valid = TRUE;
        }
    } else {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }
exit:
   SHR_FUNC_EXIT();
}

/*!
 * \brief IMM output fields fill routine for lookup.
 *
 * Fill TRUNK_SYSTEM IMM entry fields from hardware load.
 *
 * \param [out] out_struct TRUNK_SYSTEM LT .
 *
 *
 * \param [in] unit Unit number.
 * \param [in] sid Logical table database source identifier.
 * \param [in] para Logical table entry data buffer.
 * \param [out] out LT fields.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to convert \c in to \c LT entry.
 */
static int
bcmcth_trunk_imm_sys_grp_extend_fill(int unit,
                                     bcmltd_sid_t sid,
                                     bcmcth_trunk_sys_grp_param_t *para,
                                     bcmltd_fields_t *out)
{
    bcmltd_field_t *out_fld;
    uint32_t fval;
    uint32_t idx;

    SHR_FUNC_ENTER(unit);

    /* For each field ID access the IMM table data fields */
    for (idx = 0; idx < out->count; idx++) {
        out_fld = (bcmltd_field_t *) out->field[idx];

        switch (out_fld->id) {
            case TRUNK_SYSTEMt_MAX_MEMBERSf:
                /* This is LT field only - no hardware readout needed. */
                continue;

            case TRUNK_SYSTEMt_LB_MODEf:
                fval = para->lb_mode;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_LB_MODEf = %d.\n"),
                 (uint8_t) fval));
                break;

            case TRUNK_SYSTEMt_MEMBER_CNTf:
                fval = para->cnt;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_UC_MEMBER_CNTf = %d.\n"),
                  (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_MEMBER_PORT_IDf:
                fval = para->port[out_fld->idx];

                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEMt_UC_MEMBER_PORT_IDf[%d] = %d.\n"),
                     out_fld->idx, (uint8_t) fval));
                break;
            case TRUNK_SYSTEMt_RESOLUTION_DISABLEf:
                fval = (bool) para->disable;
                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_RESOLUTION_DISABLEf= %d.\n"),
                  (bool) fval));
                break;
           case TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf:
                /* Leave key untouched. */
                continue;
           case TRUNK_SYSTEMt_RH_SIZEf:
           case TRUNK_SYSTEMt_RH_RANDOM_SEEDf:
           case TRUNK_SYSTEMt_RH_MEMBER_CNTf:
           case TRUNK_SYSTEMt_RH_MEMBER_PORT_IDf:
                /* Resilient hashing fields are not supported. */
                continue;
           default:
                SHR_ERR_EXIT(SHR_E_PARAM);
                break;
        }

        out_fld->data = fval;
    }

exit:
    SHR_FUNC_EXIT();
}


/*!
 * \brief IMM input fields parse routine for loopback.
 *
 * Parse TRUNK_SYSTEM IMM entry fields and save the data to entry.
 *
 * \param [in]  unit Unit number.
 * \param [in]  in_fld   Field list.
 * \param [out] out_struct TRUNK_SYSTEM LT .
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to convert \c in to \c LT entry.
 */
static int
bcmcth_trunk_imm_sys_grp_extend_parse(int unit,
                                      const bcmltd_fields_t *input,
                                      bcmcth_trunk_sys_grp_param_t *para)
{
    uint32_t fid;
    uint32_t arr_idx;
    uint32_t fval;
    uint32_t idx;

    bcmcth_trunk_sys_grp_param_t *entry = para;
    const bcmltd_field_t *in;

    SHR_FUNC_ENTER(unit);

    /* For each field ID access the IMM table data fields */
    for (idx = 0; idx < input->count; idx++) {
        in = input->field[idx];

        fid = in->id;
        fval = in->data;
        arr_idx = in->idx;

        switch (fid) {
            case TRUNK_SYSTEMt_LB_MODEf:
                entry->lb_mode = (uint8_t) fval;
                entry->lb_mode_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_LB_MODEf = %d.\n"),
                 (uint8_t) fval));
                break;
            case TRUNK_SYSTEMt_MAX_MEMBERSf:
                entry->max_members = (uint16_t)fval;
                entry->max_members_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_MAX_MEMBERSf = %d.\n"),
                 (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_MEMBER_CNTf:
                entry->cnt = (uint16_t)fval;
                entry->cnt_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_UC_MEMBER_CNTf = %d.\n"),
                  (uint16_t) fval));
                break;
            case TRUNK_SYSTEMt_MEMBER_PORT_IDf:
                if ((arr_idx) >= BCMCTH_TRUNK_SYSTEM_MAX_MEMBERS) {
                    LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                    "TRUNK_SYSTEMt_UC_MEMBER_PORT_IDf[%d] index invalid.\n"),
                            arr_idx));
                    SHR_ERR_EXIT(SHR_E_PARAM);
                }
                entry->port[arr_idx] = (uint8_t) fval;
                entry->port_valid[arr_idx] = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEMt_UC_MEMBER_PORT_IDf[%d] = %d.\n"),
                                arr_idx, (uint8_t) fval));
                break;
            case TRUNK_SYSTEMt_RESOLUTION_DISABLEf:
                entry->disable = (bool) fval;
                entry->disable_valid = TRUE;
                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_RESOLUTION_DISABLEf= %d.\n"),
                  (bool) fval));
                break;
           case TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf:
                entry->id = fval;

                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf= %d.\n"),
                  (bool) fval));
                break;
           case TRUNK_SYSTEMt_RH_SIZEf:
           case TRUNK_SYSTEMt_RH_RANDOM_SEEDf:
           case TRUNK_SYSTEMt_RH_MEMBER_CNTf:
           case TRUNK_SYSTEMt_RH_MEMBER_PORT_IDf:
                /* Resilient hashing fields are not supported. */
                break;
           default:
                SHR_ERR_EXIT(SHR_E_PARAM);
                break;
        }
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief TRUNK_SYSTEM transaction validate.
 *
 * \param [in] unit Unit number.
 * \param [in] sid LTD Symbol ID.
 * \param [in] event_reason Reason code.
 * \param [in] key List of the key fields.
 * \param [in] data List of the data fields.
 * \param [in] context Is a pointer that was given during registration.
 * The callback can use this pointer to retrieve some context.
 *
 * \retval SHR_E_NONE         No errors.
 * \retval !SHR_E_NONE        Failure.
 */
static int
bcmcth_trunk_imm_sys_grp_validate(int unit,
                                  bcmltd_sid_t sid,
                                  bcmimm_entry_event_t event_reason,
                                  const bcmltd_field_t *key,
                                  const bcmltd_field_t *data,
                                  void *context)
{
    bcmcth_trunk_sys_grp_param_t trunk_entry;
    uint32_t trunk_id = 0;
    uint32_t max_group_cnt;
    uint16_t cnt = 0;
    int max_members;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(key, SHR_E_PARAM);

    if (sid != TRUNK_SYSTEMt) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    if (!SYS_GRP_TEMP(unit)) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }

    sal_memset(&trunk_entry, 0, sizeof(trunk_entry));

    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(
                                             unit,
                                             key,
                                             &trunk_entry));
    /* Trunk group identifier. */
    trunk_id = trunk_entry.id;
    /* Read the trunk group temp info. */
    sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;
    if (event_reason == BCMIMM_ENTRY_UPDATE) {
        trunk_entry.gtype = sys_grp->gtype;
    }

    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_lb_mode_parse(
                                             unit,
                                             data,
                                             &trunk_entry));
    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(
                                             unit,
                                             data,
                                             &trunk_entry));

    max_group_cnt = SYS_GRP_TEMP(unit)->max_group_cnt;
    if (trunk_id >= max_group_cnt) {
        LOG_VERBOSE(BSL_LOG_MODULE,
            (BSL_META_U(unit, "TRUNK_SYSTEM_ID=%d invalid.\n"), trunk_id));
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    switch (event_reason) {
        case BCMIMM_ENTRY_INSERT:
            if (SYS_GRP_EXIST(unit, trunk_id)) {
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEM_ID=%d exist.\n"), trunk_id));
                SHR_ERR_EXIT(SHR_E_EXISTS);
            }
            SHR_IF_ERR_VERBOSE_EXIT(
               bcmcth_trunk_sys_grp_lt_entry_def_val_get(
                                                unit,
                                                &trunk_entry));

            if (trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR) {
                if (trunk_entry.cnt > trunk_entry.max_members) {
                    LOG_VERBOSE(BSL_LOG_MODULE,
                       (BSL_META_U(unit,
                       "TRUNK_SYSTEM_ID=%d MEMBER_CNT= %d is greater than" \
                       " MAX_MEMEBERS = %d."),
                       trunk_id,
                       trunk_entry.cnt,
                       trunk_entry.max_members));
                    SHR_ERR_EXIT(SHR_E_PARAM);
                }

            } else {
                if (trunk_entry.cnt > trunk_entry.max_members) {
                    LOG_VERBOSE(BSL_LOG_MODULE,
                       (BSL_META_U(unit,
                       "TRUNK_SYSTEM_ID=%d RH_MEMBER_CNT= %d is greater than" \
                       " RH_SIZE = %d."),
                       trunk_id,
                       trunk_entry.cnt,
                       bcmcth_trunk_sys_grp_max_members_to_rh_size
                       (trunk_entry.max_members)));
                    SHR_ERR_EXIT(SHR_E_PARAM);
                }

            }
           break;
        case BCMIMM_ENTRY_LOOKUP:
            if (!SYS_GRP_EXIST(unit, trunk_id)) {
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEM_ID=%d not found.\n"), trunk_id));
                SHR_ERR_EXIT(SHR_E_NOT_FOUND);
            }
            break;
        case BCMIMM_ENTRY_DELETE:
            if (!SYS_GRP_EXIST(unit, trunk_id)) {
                LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                     "TRUNK_SYSTEM_ID=%d not found.\n"), trunk_id));
                SHR_ERR_EXIT(SHR_E_NOT_FOUND);
            }
            break;
        case BCMIMM_ENTRY_UPDATE:
            if (!SYS_GRP_EXIST(unit, trunk_id)) {
               LOG_VERBOSE(BSL_LOG_MODULE,
                   (BSL_META_U(unit,
                    "TRUNK_SYSTEM_ID=%d not found.\n"), trunk_id));
                SHR_ERR_EXIT(SHR_E_NOT_FOUND);
            }
            if (trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR) {
                if (trunk_entry.cnt_valid) {
                    cnt = trunk_entry.cnt;
                } else {
                    cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);;
                }

            } else if (trunk_entry.gtype ==
                       BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
                if (trunk_entry.cnt_valid) {
                    cnt = trunk_entry.cnt;
                } else {
                    cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);;
                }
            }

            if (trunk_entry.max_members_valid) {
                max_members = trunk_entry.max_members;
            } else {
                max_members = SYS_GRP_MAX_MEMBERS(unit, trunk_id);
            }
            if (cnt > max_members) {
                LOG_VERBOSE(BSL_LOG_MODULE,
                  (BSL_META_U(unit,
                  "TRUNK_SYSTEM_ID=%d cnt= %d is greater than" \
                  " max_members = %d."),
                  trunk_id, cnt, max_members));
                SHR_ERR_EXIT(SHR_E_PARAM);
            }

            break;
        default:
            SHR_ERR_EXIT(SHR_E_PARAM);
            break;
   }

exit:
   SHR_FUNC_EXIT();
}
/*!
 * \brief Free RH memory for the trunk group.
 *
 * \param [in] unit  Unit number.
 * \param [in] entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return none.
 */
static void
bcmcth_trunk_sys_grp_rh_free(
            int unit,
            uint32_t trunk_id)
{
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    if (sys_grp_bk_ptr->rhg[trunk_id]) {
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_port) {
            BCMCTH_TRUNK_FREE(
                  sys_grp_bk_ptr->rhg[trunk_id]->rh_port);
        }
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(
                  sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr);
        }
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(
                  sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
        }
        BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]);
    }

    if (sys_grp_bk_temp_ptr->rhg[trunk_id]) {
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port) {
            BCMCTH_TRUNK_FREE(
                  sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port);
        }

        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(
                 sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr);
        }
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(
                 sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
        }
        BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]);
    }

    return;
}

/*!
 * \brief Reallocate RH memory for the trunk group
 *        to account for change in size.
 *
 * \param [in] unit Unit number.
 * \param [in] entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_RESOURCE if there is no space
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_grp_rh_realloc(
            int unit,
            bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t trunk_id = BCMCTH_TRUNK_INVALID;    /* Group TRUNK_SYSTEM_ID. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;
    if (sys_grp_bk_ptr->rhg[trunk_id]) {
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_port) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]->rh_port);
        }
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr);
        }
        if (sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
        }
        BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]);
    }

    if (sys_grp_bk_temp_ptr->rhg[trunk_id]) {
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port);
        }

        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr);
        }
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
        }
        BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]);
    }

    /*
     * Allocate group memory to store Resilient
     * TRUNK_SYSTEM group entries.
     */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id],
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id])),
                   "bcmcthTrunkSysRhGrpReallocRhgInfo");
    /*
     * Allocate group temprary memory to store resilient TRUNK
     * group entries.
     */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id],
                   sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id])),
                   "bcmcthTrunkSysRhGrpReallocRhgInfoTemp");
    /*
     * Allocate memory to store group resilient TRUNK_SYSTEM entries
     * member fields.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
         entry->max_members *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port)),
         "bcmcthTrunkSysRhGrpReallocGrpRhEntPort");

    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
         entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)),
         "bcmcthTrunkSysRhGrpReallocGrpRhEntPortTemp");

    /*
     * Allocate memory to store group resilient TRUNK_SYSTEM entries
     * mapped member index information.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpReallocGrpRhMindexArr");
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpReallocGrpRhMindexArrTemp");


    /*
     * Allocate memory to store resilient TRUNK_SYSTEM members
     * entries usage count information.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
         entry->cnt *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)),
         "bcmcthTrunkSysRhGrpReallocGrpRhMembEntCntArr");
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
         entry->cnt *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)),
         "bcmcthTrunkSysRhGrpReallocGrpRhMembEntCntArrTemp");
    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Returns a random member index value within an index range.
 *
 * Generates and returns a random member index value given an index range.
 *
 * \param [in] unit        Unit number.
 * \param [in] trunk_id    TRUNK_SYSTEM group ID.
 * \param [in] rand_max    Max index value limit for random index generation.
 * \param [out] rand_index Pointer to generated randon index value.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_rh_rand_memb_index_get(int unit,
                               uint32_t trunk_id,
                               uint32_t rand_max,
                               uint32_t *rand_index)
{
    uint32_t modulus;
    uint32_t rand_seed_shift = 16;
    uint32_t random_value = 0;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(rand_index, SHR_E_PARAM);

    /* Read the trunk group temp info. */
    sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    modulus = rand_max + 1;

    /* Modulus should not be greater than 16 bits. */
    if (modulus > (uint32_t)(1 << (32 - rand_seed_shift))) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    random_value =
           sys_grp->rh_random_seed *
           BCMCTH_TRUNK_RESILIENT_MAGIC_NUM_1 +
           BCMCTH_TRUNK_RESILIENT_MAGIC_NUM_2;

    sys_grp->rh_random_seed = random_value;

    *rand_index = (random_value >> rand_seed_shift)
                     % modulus;

    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Returnes RH member array index where the member fields
 *  (port) value must be set.
 *
 * Calculates and returns the RH member array index where the member fields
 * value must be set. Maximum entries and additional overflow entries that a RH
 * group's member can occupy in TRUNK_SYSTEM member table are used in this calculation
 * for RH member array index selection.
 *
 * \param [in] unit             Unit number.
 * \param [in] max_ent_cnt      Maximum entries a RH group member can occupy.
 * \param [in] overflow_cnt     Surplus entries that RH
 *                              group members can occupy.
 * \param [in] entry            Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [out] selected_index  Pointer to selected to member fields
 *                              (port) member index.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 * \return SHR_E_INTERNAL Internal error.
 */
static int
bcmcth_trunk_sys_grp_rh_memb_select(
                                  int unit,
                                  uint32_t max_ent_cnt,
                                  uint32_t *overflow_cnt,
                                  bcmcth_trunk_sys_grp_param_t *entry,
                                  uint32_t *selected_index)
{
    uint32_t mindex = 0; /* Random member index value. */
    uint32_t nindex = 0; /* New member index value. */

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(overflow_cnt, SHR_E_PARAM);
    SHR_NULL_CHECK(selected_index, SHR_E_PARAM);

    LOG_DEBUG(BSL_LOG_MODULE,
              (BSL_META_U(unit,
                          "bcmcth_trunk_sys_grp_rh_memb_select.\n")));
    /*
     * Member array index is zero based, hence mindex must be less than
     * "member_cnt - 1".
     */
    SHR_IF_ERR_EXIT
        (bcmcth_trunk_rh_rand_memb_index_get
            (unit, entry->id, (entry->cnt - 1),
             &mindex));
    if (entry->rh_memb_ecnt_arr[mindex] < max_ent_cnt) {
        entry->rh_memb_ecnt_arr[mindex] += 1;
        *selected_index = mindex;
    } else {
        /* Overflow entries. */
        nindex = (mindex + 1) % entry->cnt;
        while (nindex != mindex) {
            if (entry->rh_memb_ecnt_arr[nindex] < max_ent_cnt) {
                entry->rh_memb_ecnt_arr[nindex] += 1;
                *selected_index = nindex;
                break;
            } else {
                nindex = (nindex + 1) % entry->cnt;
            }
        }
        if (nindex == mindex) {
            if (entry->rh_memb_ecnt_arr[nindex]< (max_ent_cnt + 1)
                && (0 != *overflow_cnt)) {
                entry->rh_memb_ecnt_arr[nindex] += 1;
                *selected_index = nindex;
                *overflow_cnt -= 1;
            } else {
                nindex = (mindex + 1) % entry->cnt;
                while (nindex != mindex) {
                    if (entry->rh_memb_ecnt_arr[nindex] < (max_ent_cnt + 1)
                        && (0 != *overflow_cnt)) {
                        entry->rh_memb_ecnt_arr[nindex] += 1;
                        *selected_index = nindex;
                        *overflow_cnt -= 1;
                        break;
                    } else {
                        nindex = (nindex + 1) % entry->cnt;
                    }
                }
                if (nindex == mindex) {
                    SHR_ERR_EXIT(SHR_E_INTERNAL);
                }
            }
        }
    }

    exit:
        SHR_FUNC_EXIT();
}

static inline int
bcmcth_trunk_sys_compare_ent_idx(int unit,
                         bcmcth_trunk_sys_grp_param_t *entry1,
                         int idx1,
                         bcmcth_trunk_sys_grp_param_t *entry2,
                         int idx2)
{
    if (entry1->port[idx1]
           != entry2->port[idx2]) {
        return 0;
    }
    return 1;
}

static inline int
bcmcth_trunk_sys_compare_rh_ent_idx(int unit,
                         bcmcth_trunk_sys_grp_param_t *entry1,
                         int idx1,
                         bcmcth_trunk_sys_grp_param_t *entry2,
                         int idx2)
{
    if ((entry1->port[idx1]
                     != (uint16_t) BCMCTH_TRUNK_INVALID) &&
        (entry1->port[idx1]
                     != entry2->rh_port[idx2])) {
        return 0;
    }
    return 1;
}

/*!
 * \brief Distributes group members as per RH load balance algorithm.
 *
 * Distributes RH_UC_MEMBER_CNT group members among
 * RH_SIZE member table entries for
 * installation in TRUNK_SYSTEM hardware tables.
 *
 * \param [in] unit Unit number.
 * \param [in] entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_grp_rh_entries_set(
                                  int unit,
                                  bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t max_ent_cnt = 0;  /* Maxiumum entries a member can occupy. */
    uint32_t overflow_cnt = 0; /* Overflow count. */
    uint32_t idx;              /* loop iterator variable. */
    uint32_t selected_index = (uint32_t)BCMCTH_TRUNK_INVALID; /* Selected member
                                                            index. */

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    /*
     * Validate RH_UC_MEMBER_CNT value and confirm
     * it's non-zero to perform RH load
     * balancing. If value is zero, there are no members to perform load
     * balancing.
     */
    if (!entry->cnt) {
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                                "No members RH_MEMBER_CNT=%u.\n"),
                     entry->cnt));
        SHR_EXIT();
    }


    max_ent_cnt = (entry->max_members / entry->cnt);
    overflow_cnt = (entry->max_members % entry->cnt);

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                 "[max_members=%-4u, "
                 "cnt=%-4d, max_ent_cnt:%-4u, ovf_cnt=%u].\n"),
                 entry->max_members,
                 entry->cnt,
                 max_ent_cnt,
                 overflow_cnt));

    for (idx = 0; idx < entry->max_members; idx++) {
        SHR_IF_ERR_EXIT
            (bcmcth_trunk_sys_grp_rh_memb_select(
                                          unit,
                                          max_ent_cnt,
                                          &overflow_cnt,
                                          entry,
                                          &selected_index));

        /* Member entry fields. */
        entry->rh_port[idx] =
            entry->port[selected_index];
        /*
         * Store selected array member index value for use during
         * Add/Delete/Replace operations.
         */
        entry->rh_mindex_arr[idx] = selected_index;
    }


    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief resilient TRUNK_SYSTEM groups pre-config function for warm start sequence.
 *
 * For all resilient TRUNK_SYSTEM groups that have non-zero RH_UC_MEMBER_CNT
 * value set during insert operation in cold boot mode,
 * their load balanced members state has to be
 * reconstructed for use during update operation post warm boot. This function
 * identifies such resilient TRUNK_SYSTEM groups during warm start pre_config sequence.
 *
 * \param [in] unit Unit number.
 *
 * \return SHR_E_NONE No errors.
 */
static int
bcmcth_trunk_sys_rh_grps_preconfig(
                            int unit,
                            uint16_t max_grp_cnt)
{
    uint32_t trunk_id;     /* Group identifier. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;

    SHR_FUNC_ENTER(unit);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit, "%s.\n"), __func__));


    /*
     * For resilient TRUNK_SYSTEM groups, load balanced members state must be recovered
     * prior to members update operation. Check and set the pre_config
     * flag for this type of group.
     */
    for (trunk_id = 0;
         trunk_id < max_grp_cnt;
         trunk_id++) {

         /* Read the trunk group temp info. */
         sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

         if ((sys_grp->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)  &&
            (sys_grp->cnt != 0)) {

            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit,
                                    "TRUNK_SYSTEM_ID[RH_UC_MEMBER_CNT=%u]=%u:"
                                    " in-use.\n"),
                         sys_grp->cnt,
                         trunk_id));
            SYS_GRP_PRECONFIG_SET(unit, trunk_id);
        }
        continue;
    }

    SHR_EXIT();
    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Add new member to an existing resilient TRUNK_SYSTEM group.
 *
 * This function adds a new member to an existing
 * resilient TRUNK_SYSTEM group and re-balances
 * the group with limited impact to existing flows.
 *
 * \param [in] unit       Unit number.
 * \param [in] new_mindex New RH group member array index.
 * \param [in] entry      Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_memb_add(int unit,
                        uint32_t new_mindex,
                        bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t ubound = 0, lbound = 0; /* Upper bound and lower bound. */
    uint32_t threshold = 0;          /* Upper threshold value. */
    uint32_t eindex = 0;      /* Selected entry index. */
    uint32_t next_eindex = 0; /* Next entry index. */
    uint32_t *ecount = NULL;  /* New member entries usage count. */
    uint32_t mindex;          /* member index. */
    bool new_memb_sel = FALSE; /* New member selected. */

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
              "%s - n_mindex=%u. \n"),
             __func__,
             new_mindex));

    lbound = entry->max_members / entry->cnt;
    ubound = (entry->max_members % entry->cnt)
                    ? (lbound + 1) : lbound;
    threshold = ubound;

    /*
     * Set local entry count pointer to point to new member's entry usage
     * count array element address.
     */
   ecount = &(entry->rh_memb_ecnt_arr[new_mindex]);

    /*
     * New member initial entries usage count is expected to be zero. If it's
     * non-zero it's an error.
     */
    if (*ecount) {
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                                "Error: new_mindex=%u non-zero ecount=%u.\n"),
                     new_mindex,
                     *ecount));
        return (SHR_E_INTERNAL);
    }

    while (*ecount < lbound) {
        /* Select a random entry to replace with new member. */
        SHR_IF_ERR_EXIT
            (bcmcth_trunk_rh_rand_memb_index_get
                (unit, entry->id, (entry->max_members - 1),
                 &eindex));
        if (entry->rh_mindex_arr[eindex] == new_mindex) {
            new_memb_sel = TRUE;
        } else {
            new_memb_sel = FALSE;
            mindex = entry->rh_mindex_arr[eindex];
        }

        if (!new_memb_sel && (entry->rh_memb_ecnt_arr[mindex] > threshold)) {
            entry->rh_port[eindex] =
                 entry->port[new_mindex];
            entry->rh_mindex_arr[eindex] = new_mindex;

            /* Decrement entry usage count value for the replaced member. */
            entry->rh_memb_ecnt_arr[mindex] -= 1;
            /* Increment entry usage count value for the new member. */
            *ecount += 1;
        } else {
            /*
             * Arrived here because the randomly selected entry index happened
             * to be the new member or the selected existing member's entry
             * usage count is below the threshold value.
             *
             * In either case, find the next entry index that's either not
             * populated with the new member or existing entry with entry usage
             * count value that's equal to greater than the threshold value.
             */
            next_eindex = (eindex + 1) % entry->max_members;
            while (next_eindex != eindex) {

                mindex = entry->rh_mindex_arr[next_eindex];

                if (mindex == new_mindex) {
                    new_memb_sel = TRUE;
                } else {
                    new_memb_sel = FALSE;
                }

                if (!new_memb_sel
                    && (entry->rh_memb_ecnt_arr[mindex] > threshold)) {
                    /*
                     * Replace existing member with new member
                     * member fields(port) ID
                     * value.
                     */
                    entry->rh_port[next_eindex] =
                                    entry->port[new_mindex];
                    /*
                     * Replace existing member with the new member index
                     * value.
                     */
                    entry->rh_mindex_arr[next_eindex] = new_mindex;

                    /*
                     * Decrement entry usage count value for the replaced
                     * member.
                     */
                    entry->rh_memb_ecnt_arr[mindex] -= 1;

                    /* Increment entry usage count value for the new member. */
                    *ecount += 1;
                    break;
              } else {
                    next_eindex = (next_eindex + 1) % entry->max_members;
                }
            }
            if (next_eindex == eindex) {
                threshold--;
            }
        }
    }

    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Add member/s to an existing resilient TRUNK_SYSTEM group.
 *
 * This function adds member or members to an existing resilient TRUNK_SYSTEM group
 * and re-balances the group with limited impact to existing flows.
 *
 * \param [in] unit  Unit number.
 * \param [in] entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_members_add(
                           int unit,
                           bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t trunk_id = BCMCTH_TRUNK_INVALID; /* Group TRUNK_SYSTEM_ID. */
    uint32_t grp_member_cnt = 0;  /* Current member_cnt value of the group. */
    uint32_t new_mindex; /* New member array index. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    /* Initialize the TRUNK_SYSTEM group identifier value. */
    trunk_id = entry->id;



    LOG_INFO(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                             "bcmcth_trunk_sys_rh_grp_members_add.\n")));

    /* Get group's current member_cnt value. */
    grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);

    /*
     * For update operation, copy existing group RH entries array
     * into LT entry's RH entries array for updation.
     */
    sal_memcpy(entry->rh_port,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port))
               * entry->max_members));
    /*
     * Copy RH group's existing entries mapped member index array into LT
     * entry's RH entries mapped member index array for update operation.
     */
    sal_memcpy(entry->rh_mindex_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               (sizeof(*(entry->rh_mindex_arr)) * entry->max_members));
    /*
     * Copy RH group's existing entries usage count array into LT entry's RH
     * entries usage count array for update operation.
     */
    sal_memcpy(entry->rh_memb_ecnt_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               (sizeof(*(entry->rh_memb_ecnt_arr)) * grp_member_cnt));

    /*
     * Call RH member add function for every new member in the
     * member fields(port) array.
     * New members must be set in the array after the
     * current member fields(port) member elements.
     */
    for (new_mindex = grp_member_cnt; new_mindex < entry->cnt;
         new_mindex++) {
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmcth_trunk_sys_rh_grp_memb_add(unit, new_mindex, entry));
    }

    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Delete a member from an existing resilient TRUNK_SYSTEM group.
 *
 * This function deletes a member from an existing resilient TRUNK_SYSTEM group and
 * re-balances the group with no impact to existing flows.
 *
 * \param [in] unit Unit number.
 * \param [in] del_mindex New RH group member array index.
 * \param [in] entry Pointer to TRUNK_SYSTEM logical table entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_memb_delete(int unit,
                           uint32_t del_mindex,
                           bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t idx; /* Index iterator variable. */
    uint32_t max_ent_cnt = 0;  /* Maxiumum entries a member can occupy. */
    uint32_t overflow_cnt = 0; /* Overflow count. */
    uint32_t selected_index = (uint32_t)BCMCTH_TRUNK_INVALID; /* Selected member
                                                            index. */
    uint32_t trunk_id; /* TRUNK_SYSTEM group identifier. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;


    LOG_INFO(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                             "bcmcth_trunk_sys_rh_grp_memb_delete: mindex=%u.\n"),
                  del_mindex));

    max_ent_cnt = (entry->max_members / entry->cnt);
    overflow_cnt = (entry->max_members % entry->cnt);
    trunk_id = entry->id;


    for (idx = 0; idx < entry->max_members; idx++) {
        /*
         * If current member is not the member to be deleted, continue to the
         * next member.
         */
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr[idx] != del_mindex) {
            continue;
        }
        SHR_IF_ERR_EXIT
            (bcmcth_trunk_sys_grp_rh_memb_select(unit,
                                          max_ent_cnt,
                                          &overflow_cnt,
                                          entry,
                                          &selected_index));

        entry->rh_port[idx] =
              entry->port[selected_index];
        /*
         * Delay this update until all members are deleted so that mindex array
         * has old mindex member value for multi member delete operation.
         */
        entry->rh_mindex_arr[idx] = selected_index;

        /* Decrement deleted members entry usage count value.  */
        sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[del_mindex] -= 1;

    }
    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Delete member/s from an existing resilient TRUNK_SYSTEM group.
 *
 * This function deletes member or members from an
 * existing resilient TRUNK_SYSTEM group and re-balances the group with
 * no impact to existing flows.
 *
 * \param [in] unit      Unit number.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table previous entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_members_delete(int unit,
                              bcmcth_trunk_sys_grp_param_t *entry,
                              bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    uint32_t deleted_cnt = 0; /* Number of members deleted from the group. */
    uint32_t grp_member_cnt = 0;  /* Current member_cnt value of the group. */
    uint32_t *deleted_mindex = NULL; /* Array of deleted members indices. */
    uint32_t *shrd_mindex = NULL; /* Array of shared member/s indices. */
    uint32_t shrd_new_mindex_cnt = 0; /* Count of shared members with new
                                         mindex. */
    uint32_t shrd_cnt = 0; /* Number of members replaced in the group. */
    uint32_t del_idx = 0; /* Deleted members array index iterator. */
    uint32_t new_idx = 0; /* New member array index. */
    uint32_t idx, uidx; /* Array index iterator variables. */
    uint32_t trunk_id; /* TRUNK_SYSTEM group identifier. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "bcmcth_trunk__rh_grp_members_delete.\n")));

    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;

    /*
     * Check if member_cnt is non-zero in this delete (update) operation. If
     * there are valid members after delete, the remaining members must be
     * re-balanced.
     *
     * If there no members left in the group after this delete operation,
     * re-balance operation is not required. Clear the entries in the member
     * table, clear the mindex value for all entries in this group, reset
     * entries usage count and return.
     */
    if (entry->cnt) {
        grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);

        /* Determine how many members have been deleted. */
        deleted_cnt = (grp_member_cnt - entry->cnt);

        /*
         * For update operation, copy existing group RH entries array
         * into LT entry's RH entries array for updation.
         */
        sal_memcpy(entry->rh_port,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                          entry->max_members));
        /*
         * Copy RH group's existing entries mapped member index array into LT
         * entry's RH entries mapped member index array for update operation.
         */
        sal_memcpy(entry->rh_mindex_arr,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                   (sizeof(*(entry->rh_mindex_arr)) *
                    entry->max_members));
        BCMCTH_TRUNK_ALLOC(deleted_mindex,
                      deleted_cnt * sizeof(*deleted_mindex),
                      "bcmcthTrunkSysRhGrpMembsDelMindexArr");

        BCMCTH_TRUNK_ALLOC(shrd_mindex,
                      (grp_member_cnt * sizeof(*shrd_mindex)),
                      "bcmcthTrunkSysRhGrpMembsDelShrdMindexArr");
        sal_memset(shrd_mindex,
                   BCMCTH_TRUNK_INVALID,
                   (grp_member_cnt * sizeof(*shrd_mindex)));

        /*
         * The set of new group members are a sub-set of the current members
         * list as some of the existing members have been deleted from the list
         * as part of update operation.
         *
         * So, for every member in the existing members array (outer for-loop),
         * check if this member exists in the updated members array
         * (inner for-loop). If it's not present, store this member index in the
         * deleted member indices array.
         */
        for (idx = 0; idx < grp_member_cnt; idx++) {
            /*
             * member_cnt value must be less than grp_member_cnt as it's members
             * delete operation and number of elements in umemb_arr is equal to
             * member_cnt.
             */
            for (uidx = 0; uidx < entry->cnt; uidx++) {
                /*
                 * Compare existing members with members in updated
                 * array, confirm rh_memb_ecnt_arr value is equal to zero for
                 * the updated nhop member to skip duplicate members.
                 */
                if (bcmcth_trunk_sys_compare_ent_idx(
                       unit, entry, idx, cur_entry, uidx)
                    && (0 == entry->rh_memb_ecnt_arr[uidx])) {
                    entry->rh_memb_ecnt_arr[uidx] =
                      sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx];
                    shrd_cnt++;
                    if (idx != uidx) {
                        /*
                         * Save new mindex mapped to the old mindex value for
                         * update after the delete operation.
                         */
                        shrd_mindex[idx] = uidx;
                        shrd_new_mindex_cnt++;

                        /*
                         * Reset the entry usage counter value as this member
                         * will be maintained in the new index location "uidx"
                         * after the delete operation.
                         */
                        sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx]
                           = 0;
                    }
                    break;
                }
            }

            /*
             * If the member is present in the updated nhop members array, move
             * to the next member in existing array.
             */
            if (uidx != entry->cnt) {
                continue;
            }

            /*
             * Member not found in the updated array, add this member index to
             * be deleted members list.
             */
            if (del_idx < deleted_cnt) {
                deleted_mindex[del_idx++] = idx;
            } else {
                LOG_VERBOSE(BSL_LOG_MODULE,
                            (BSL_META_U(unit,
                                        "del_idx = %u > del_max_idx = %u.\n"),
                            del_idx,
                            (deleted_cnt - 1)));
                SHR_ERR_EXIT(SHR_E_INTERNAL);
            }
        }

        for (idx = 0; idx < deleted_cnt; idx++) {
            /* Delete the member and re-balance the group entries. */
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_memb_delete(unit,
                                            deleted_mindex[idx],
                                            entry));
        }
        /*
         * For the shared members, check and update the member index value in
         * the LT entry mindex array if it has changed.
         */
        if (shrd_new_mindex_cnt) {
            for (idx = 0; idx < grp_member_cnt; idx++) {
                new_idx = shrd_mindex[idx];
                if (new_idx == (uint32_t)BCMCTH_TRUNK_INVALID) {
                    continue;
                }
                for (uidx = 0; uidx < entry->max_members; uidx++) {
                    if (bcmcth_trunk_sys_compare_ent_idx(unit,
                                  entry, idx, cur_entry, uidx)
                        && idx == entry->rh_mindex_arr[uidx]) {
                        /* Update mindex with new mindex value. */
                        entry->rh_mindex_arr[uidx] = new_idx;
                    }
                }
                shrd_new_mindex_cnt--;
            }
        }
    } else {
        /* Clear resilient TRUNK_SYSTEM group member table entries. */
        sal_memset(entry->rh_port,
                   0,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                    entry->max_members));
        /* Clear stored resilient TRUNK_SYSTEM group member indices data. */
        sal_memset(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                   0,
                   (sizeof(*sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr) *
                    entry->max_members));

        /* Clear stored resilient TRUNK_SYSTEM group members entry usage count data. */
        sal_memset(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                   0,
                   (sizeof(*sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) *
                    entry->cnt));
    }


    exit:
        if (entry->cnt) {
            /* Free memory allocated to store mindex array. */
            BCMCTH_TRUNK_FREE(deleted_mindex);
            BCMCTH_TRUNK_FREE(shrd_mindex);
        }
        SHR_FUNC_EXIT();
}

/*!
 * \brief Replace member/s from an existing resilient TRUNK_SYSTEM group.
 *
 * This function replaces member or members from an
 * existing resilient TRUNK_SYSTEM group and re-balances the
 * group with limited impact to existing flows.
 *
 * \param [in] unit      Unit number.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table previous entry data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_members_replace(int unit,
                                    bcmcth_trunk_sys_grp_param_t *entry,
                                    bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    uint32_t grp_member_cnt = 0;  /* Current member_cnt value of the group. */
    uint32_t idx, uidx;       /* Array index iterator variables. */
    uint32_t trunk_id;     /* TRUNK_SYSTEM group identifier. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "bcmcth_trunk_sys_rh_grp_members_replace.\n")));
    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;

    grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);

    /*
     * For replace operation, update member_cnt must be equal to group's current
     * member_cnt value.
     */
    if (grp_member_cnt - entry->cnt) {
        SHR_ERR_EXIT(SHR_E_PARAM);
    }

    /*
     * Initialize member array pointers based on the
     * group's member fields(port)
     * type.
     */
    SHR_NULL_CHECK(sys_grp_bk_temp_ptr->rhg[trunk_id], SHR_E_INTERNAL);

    /*
     * For update operation, copy existing group RH entries array
     * into LT entry's RH entries array for updation.
     */
    sal_memcpy(entry->rh_port,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                        entry->max_members));
    /*
     * Copy RH group's existing entries mapped member index array into LT
     * entry's RH entries mapped member index array for update operation.
     */
    sal_memcpy(entry->rh_mindex_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               (sizeof(*(entry->rh_mindex_arr)) *
                entry->max_members));

    /* Copy members entry usage count information. */
    sal_memcpy(entry->rh_memb_ecnt_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               (sizeof(*(entry->rh_memb_ecnt_arr)) * entry->cnt));

    /*
     * Find and replace the existing nhop member with the new nhop member
     * ID value.
     */
    for (idx = 0; idx < entry->cnt; idx++) {
        if (bcmcth_trunk_sys_compare_ent_idx(unit,
                    entry, idx, cur_entry, idx) == 0) {
            for (uidx = 0; uidx < entry->max_members; uidx++) {
                if (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                    cur_entry, idx, entry, uidx)
                    && (idx == entry->rh_mindex_arr[uidx])) {
                    entry->rh_port[uidx] =
                       entry->port[idx];

                }
            }
        }
    }

    exit:
        SHR_FUNC_EXIT();
}

/*!
 * \brief Determine the type of operation being
 *        performed on the resilient TRUNK_SYSTEM group.
 *
 * This function determines the type of operation being performed on the
 * member/s of a resilient TRUNK_SYSTEM group.
 *
 * \param [in] unit      Unit number.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table entry previous data.
 * \param [out] rh_oper  Resilient hashing TRUNK_SYSTEM group members operation type.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 * \return SHR_E_MEMORY Memory allocation error.
 */
static int
bcmcth_trunk_sys_grp_rh_oper_get(int unit,
                          bcmcth_trunk_sys_grp_param_t *entry,
                          bcmcth_trunk_sys_grp_param_t *cur_entry,
                          bcmcth_trunk_rh_oper_t *rh_oper)
{
    uint32_t trunk_id = BCMCTH_TRUNK_INVALID; /* Group TRUNK_SYSTEM_ID. */
    uint32_t grp_member_cnt; /* Group current MEMBER_CNT value. */
    uint32_t grp_rh_entries_cnt; /* Group current RH entries count value. */
    volatile uint32_t idx = 0, uidx = 0; /* Member fields iterator variables. */
    uint32_t shared_member_cnt = 0; /* Shared member fields count. */
    uint32_t new_member_cnt = 0; /* New member fields count. */
    uint32_t alloc_sz = 0; /* Alloc size current and new. */
    int *member_field_arr = NULL; /* member fields members array. */
    bool mindex_changed =
                 FALSE; /* Member index has changed in member fields array. */
    const char * const rh_op_str[BCMCTH_TRUNK_RH_OPER_COUNT] =
                 BCMCTH_TRUNK_RH_OPER_NAME;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);
    SHR_NULL_CHECK(rh_oper, SHR_E_PARAM);

    COMPILER_REFERENCE(trunk_id);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "bcmcth_trunk_sys_grp_rh_oper_get.\n")));
    trunk_id = entry->id;

    /*
     * If there are no members in the resilient TRUNK_SYSTEM group,
     * then there is no SW load
     * balancing operation to performed for this group in the UPDATE operation.
     */
    if (SYS_GRP_MEMBER_CNT(unit, trunk_id) == 0 &&
        entry->cnt == 0) {

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(
                        unit,
                        "(RH_MEMBER_CNT = %u): BCMCTH_TRUNK_RH_OPER_NONE."
                        "\n"),
                    entry->cnt));

        *rh_oper = BCMCTH_TRUNK_RH_OPER_NONE;
        SHR_EXIT();
    }

    /*
     * This UPDATE operation is equivalent to members add via an INSERT
     * operation as all the members are newly added to this group. These new
     * members must be SW load balanced by using
     * bcmcth_trunk_sys_grp_rh_entries_set()
     * function and not expected to be handled in this function, return
     * SHR_E_INTERNAL error.
     */
    if (SYS_GRP_MEMBER_CNT(unit, trunk_id) == 0
        && entry->cnt > 0) {
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(
                       unit,
                       "No members to members (RH_MEMBER_CNT = %u) rv=%s"
                       ".\n"),
                     entry->cnt,
                    shr_errmsg(SHR_E_INTERNAL)));
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }

    /*
     * If the resilient TRUNK_SYSTEM group previously
     * had members and there are no members
     * in the group as part of this UPDATE operation, then set 'rh_oper' to
     * BCMCTH_TRUNK_RH_OPER_DELETE and return from this function. There are no
     * shared members between the old and new members for this group.
     */
    if (SYS_GRP_MEMBER_CNT(unit, trunk_id) > 0
        && entry->cnt == 0) {

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                    "(RH_MEMBER_CNT = %u): BCMCTH_TRUNK_RH_OPER_DELETE.\n"),
                    entry->cnt));

        *rh_oper = BCMCTH_TRUNK_RH_OPER_DELETE;
        SHR_EXIT();
    }

    /* Get group's current member_cnt value. */
    grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);
    grp_rh_entries_cnt = SYS_GRP_MAX_MEMBERS(unit, trunk_id);
    alloc_sz = sizeof(*member_field_arr) * grp_member_cnt;

    if (alloc_sz) {
        BCMCTH_TRUNK_ALLOC(member_field_arr,
                      alloc_sz,
                      "bcmcthTrunkRhOperGetMemberFieldArr");
    }

    /*
     * Identify the shared members and the new members in the updated
     * member fields(port) members array.
     */
    if (member_field_arr) {
        int start_idx = 0;
        sal_memset(member_field_arr, 0, alloc_sz);

        for (uidx = 0; uidx < entry->cnt; uidx++) {
            for (idx = start_idx; idx < grp_member_cnt; idx++) {
                if ((member_field_arr[idx] != -1)
                     && bcmcth_trunk_sys_compare_ent_idx(
                         unit, entry, idx, cur_entry, uidx)) {
                    /* Old memebr also member of the updated member array. */
                    shared_member_cnt++;
                    member_field_arr[idx] = -1;
                    /*
                     * Check if member index has changed in the updated
                     * members array.
                     */
                    if (idx != uidx) {
                        mindex_changed = TRUE;
                    }
                    break;
                }
            }
            if (idx == grp_member_cnt) {
                new_member_cnt++;
            }
            while (member_field_arr[start_idx] == -1) {
                start_idx++;
            }
        }
    }

    /* Determine the type of operation to be performed on RH group members. */
    if (entry->cnt > grp_member_cnt) {
        if ((shared_member_cnt == grp_member_cnt) && !mindex_changed) {
            *rh_oper = BCMCTH_TRUNK_RH_OPER_ADD;
        } else {
            *rh_oper = BCMCTH_TRUNK_RH_OPER_ADD_REPLACE;
        }
    } else if (entry->cnt < grp_member_cnt) {
        if (shared_member_cnt == entry->cnt) {
            /*
             * This condition is TRUE when all the members passed in the
             * member/s delete-update operation are already members of this
             * group (Their mindex could have changed but they are still common
             * members between the member fields members list).
             * This condition is also TRUE when all the members have been
             * deleted in the update operation i.e. 'entry->member_cnt == 0',
             * means there are no shared members in the group in this delete
             * operation. As shared_member_cnt default value is initialized to
             * '0' at the start of this function, This condition will be TRUE.
             */
            *rh_oper = BCMCTH_TRUNK_RH_OPER_DELETE;
        } else {
            *rh_oper = BCMCTH_TRUNK_RH_OPER_DELETE_REPLACE;
        }
    } else if (entry->cnt == grp_member_cnt) {
        if (entry->max_members != grp_rh_entries_cnt) {
            *rh_oper = BCMCTH_TRUNK_RH_OPER_ADD_REPLACE;
        } else {
            *rh_oper = BCMCTH_TRUNK_RH_OPER_REPLACE;
        }
    }

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                            "[grp_member_cnt=%-4u cnt=%-4u"
                            "shared_member_cnt=%-4u\n"
                            "\t new_member_cnt=%-4u mindex_changed=%s "
                            "rh_oper=(%s)]\n"),
                 grp_member_cnt,
                 entry->cnt,
                 shared_member_cnt,
                 new_member_cnt,
                 mindex_changed ? "TRUE" : "FALSE",
                 rh_op_str[*rh_oper]));

    exit:
        BCMCTH_TRUNK_FREE(member_field_arr);
        SHR_FUNC_EXIT();
}

/*!
 * \brief Add, replace and re-balance member/s in
 *        an existing resilient TRUNK_SYSTEM group.
 *
 * This function performs member/s add, replace and re-balance operation.
 *
 * \param [in] unit      Unit number.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table entry previous data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 * \return SHR_E_MEMORY Memory allocation error.
 * \return SHR_E_INTERNAL Invalid configuration.
 */
static int
bcmcth_trunk_sys_rh_grp_members_add_replace(int unit,
                                   bcmcth_trunk_sys_grp_param_t *entry,
                                   bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    uint32_t trunk_id = BCMCTH_TRUNK_INVALID; /* Group TRUNK_SYSTEM_ID. */
    uint32_t grp_member_cnt = 0;  /* Current member_cnt value of the group. */
    uint32_t *replace_mindex = NULL; /* Array of replaced member/s indices. */
    uint32_t *shrd_mindex = NULL; /* Array of shared member/s indices. */
    uint32_t *new_mindex = NULL; /* Array of new member/s indices. */
    uint32_t added_cnt = 0; /* Number of members added to the group. */
    uint32_t replace_cnt = 0; /* Number of members replaced in the group. */
    volatile uint32_t shrd_cnt
                     = 0; /* Number of members replaced in the group. */
    uint32_t shrd_mindex_cnt = 0; /* Count of shared members with new mindex. */
    volatile uint32_t rep_idx = 0; /* Added member array index. */
    volatile uint32_t new_idx = 0; /* New member array index. */
    uint32_t idx, uidx; /* Array index iterator variables. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];


    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);

    LOG_INFO(BSL_LOG_MODULE,
                 (BSL_META_U(unit,
                             "bcmcth_trunk_sys_rh_grp_members_add_replace.\n")));
    /* Initialize the TRUNK_SYSTEM group identifier value. */
    trunk_id = entry->id;

    /* Get group's current member_cnt value. */
    grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);

    /*
     * For update operation, copy existing group RH entries array
     * into LT entry's RH entries array for updation.
     */
    sal_memcpy(entry->rh_port,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                        entry->max_members));
    /*
     * Copy RH group's existing entries mapped member index array into LT
     * entry's RH entries mapped member index array for update operation.
     */
    sal_memcpy(entry->rh_mindex_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               (sizeof(*(entry->rh_mindex_arr)) * entry->max_members));

    BCMCTH_TRUNK_ALLOC(replace_mindex,
                  (grp_member_cnt * sizeof(*replace_mindex)),
                  "bcmcthTrunkSysRhGrpMembsAddRepReplaceMindexArr");
    BCMCTH_TRUNK_ALLOC(shrd_mindex,
                  (grp_member_cnt * sizeof(*shrd_mindex)),
                  "bcmcthTrunkSysRhGrpMembsAddRepShrdMindexArr");
    sal_memset(shrd_mindex,
               BCMCTH_TRUNK_INVALID,
               (grp_member_cnt * sizeof(*shrd_mindex)));

    /*
     * Identify the members that are shared
     * between the updated member fields array and
     * the current member fields members up
     * to the group's current MEMBER_CNT value.
     * Members in the updated array after current MEMBER_CNT value will be
     * treated as member add operation.
     * For members up to grp_member_cnt that are
     * not shared with the updated members
     * array will be candidates for replace
     * operation.
     */
    for (idx = 0; idx < grp_member_cnt; idx++) {
        for (uidx = 0; uidx < entry->cnt; uidx++) {
            if (bcmcth_trunk_sys_compare_ent_idx(unit, entry, uidx, cur_entry, idx)
                && (entry->rh_memb_ecnt_arr[uidx] == 0)) {
                /* Update entry usage count. */
                entry->rh_memb_ecnt_arr[uidx] =
                    sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx];

                /* Increment shared entry count. */
                shrd_cnt++;

                if (idx != uidx) {
                    shrd_mindex[idx] = uidx;
                    shrd_mindex_cnt++;
                }

                /* Clear old entry usage count value. */
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx] = 0;
                break;
            }
        }

        /*
         * Existing member at current index
         * is also part of the updated
         * member fields(port) members array,
         * continue to the next member.
         */
        if (uidx != entry->cnt) {
            continue;
        }

        /* Member not shared hence add to replace member elements list. */
        replace_mindex[replace_cnt++] = idx;
    }

    if (replace_cnt) {
        BCMCTH_TRUNK_ALLOC(new_mindex,
                      replace_cnt * sizeof(*new_mindex),
                      "bcmcthTrunkSysRhGrpMembsAddRepNewMindexArr");

        for (idx = 0; idx < replace_cnt; idx++) {

            /* Get the old to be replaced index value. */
            rep_idx = replace_mindex[idx];
            for (uidx = 0; uidx < grp_member_cnt; uidx++) {

                if (entry->rh_memb_ecnt_arr[uidx]) {
                    /* Already updated, move to next member. */
                    continue;
                }

                /* Update entry count value. */
                entry->rh_memb_ecnt_arr[uidx] =
                    sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[rep_idx];

                /* Clear old entry usage count value. */
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[rep_idx] = 0;

                /*
                 * Store the new mindex mapped to this old mindex for updating
                 * the mindex and rh_entries_arr arrays.
                 */
                new_mindex[idx] = uidx;

                break;
            }
        }
    }

    /*
     * For the shared members, check and update the member index value in the
     * LT entry mindex array if it has changed.
     */
    if (shrd_mindex_cnt) {
        for (idx = 0; idx < grp_member_cnt; idx++) {
            new_idx = shrd_mindex[idx];
            if (new_idx == (uint32_t)BCMCTH_TRUNK_INVALID) {
                continue;
            }
            for (uidx = 0; uidx < entry->max_members; uidx++) {
                if (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                    cur_entry,
                    idx,
                    entry,
                    uidx)
                    && (idx == entry->rh_mindex_arr[uidx])) {
                    /* Update mindex with new mindex value. */
                    entry->rh_mindex_arr[uidx] = new_idx;
                }
            }
           shrd_mindex_cnt--;
        }
    }

    /*
     * For the replaced members, check and update
     * the member index value with
     * the new members index value and also update
     * the member fields member value in
     * rh_entries_array.
     */
    if (replace_cnt) {
        for (idx = 0; idx < replace_cnt; idx++) {
            rep_idx = replace_mindex[idx];

            for (uidx = 0; uidx < entry->max_members; uidx++) {
                if (bcmcth_trunk_sys_compare_rh_ent_idx(
                      unit,
                      cur_entry,
                      rep_idx,
                      entry,
                      uidx)
                    && (rep_idx == entry->rh_mindex_arr[uidx])) {

                    new_idx = new_mindex[idx];
                    /* Update mindex with new mindex value. */
                    entry->rh_mindex_arr[uidx] = new_idx;
                    /* Update with new member value. */
                    entry->rh_port[uidx] =
                          entry->port[new_idx];
                }
            }
        }
    }


    for (new_idx = 0; new_idx < entry->cnt;
         new_idx++) {
        if (entry->rh_memb_ecnt_arr[new_idx]) {
            continue;
        }

        SHR_IF_ERR_VERBOSE_EXIT
            (bcmcth_trunk_sys_rh_grp_memb_add(unit, new_idx, entry));
        added_cnt++;
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                                "added_cnt=%u n_mindex=%u\n"),
                     added_cnt, new_idx));
    }

    exit:
        /* Free memory allocated to store mindex array. */
        BCMCTH_TRUNK_FREE(replace_mindex);
        BCMCTH_TRUNK_FREE(shrd_mindex);
        if (replace_cnt) {
            BCMCTH_TRUNK_FREE(new_mindex);
        }
        SHR_FUNC_EXIT();
}

/*!
 * \brief Delete, replace and re-balance member/s
 * in an existing resilient TRUNK_SYSTEM group.
 *
 * This function performs member/s delete, replace and re-balance operation.
 *
 * \param [in] unit      Unit number.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table entry previous data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 * \return SHR_E_MEMORY Memory allocation error.
 * \return SHR_E_INTERNAL Invalid configuration.
 */
static int
bcmcth_trunk_sys_rh_grp_members_delete_replace(
                                      int unit,
                                      bcmcth_trunk_sys_grp_param_t *entry,
                                      bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    uint32_t trunk_id; /* TRUNK_SYSTEM group identifier. */
    uint32_t grp_member_cnt = 0; /* Current member_cnt value of the group. */
    uint32_t *deleted_mindex = NULL; /* Array of deleted member/s indices. */
    uint32_t *replace_mindex = NULL; /* Array of replaced member/s indices. */
    uint32_t *shrd_mindex = NULL; /* Array of shared member/s indices. */
    uint32_t *new_mindex = NULL; /* Array of new member/s indices. */
    uint32_t deleted_cnt = 0; /* Number of members deleted from the group. */
    uint32_t replace_cnt = 0; /* Number of members replaced in the group. */
    uint32_t shrd_cnt = 0; /* Number of members replaced in the group. */
    uint32_t shrd_new_mindex_cnt = 0; /* Count of shared members with new
                                         mindex. */
    uint32_t del_idx = 0; /* Deleted members array index. */
    uint32_t rep_idx = 0; /* Replace member array index. */
    uint32_t new_idx = 0; /* New member array index. */
    uint32_t idx, uidx; /* Array index iterator variables. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];



    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "bcmcth_trunk_sys_rh_grp_members_delete_replace.\n")));

    /*
     * MEMBER_CNT must be non-zero when this
     * function is called for member delete
     * operation, check and return if this condition is not met.
     */
    if (!entry->cnt) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }

    /* Get the group's TRUNK_SYSTEM_ID value and current MEMBER_CNT values. */
    trunk_id = entry->id;
    grp_member_cnt = SYS_GRP_MEMBER_CNT(unit, trunk_id);

    /*
     * Determine how many members have been deleted based on the updated
     * MEMBER_CNT value.
     */
    deleted_cnt = (grp_member_cnt - entry->cnt);

    /*
     * Copy existing group RH entries array into LT entry RH entries array for
     * members delete + replace operation.
     */
    sal_memcpy(entry->rh_port,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                        entry->max_members));
    /*
     * Copy RH group's existing entries mapped member index array into LT
     * entry's RH entries mapped member index array for update operation.
     */
    sal_memcpy(entry->rh_mindex_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               (sizeof(*(entry->rh_mindex_arr)) *
                entry->max_members));

    BCMCTH_TRUNK_ALLOC(deleted_mindex,
                  deleted_cnt * sizeof(*deleted_mindex),
                  "bcmcthTrunkSysRhGrpMembsDelRepDelMindexArr");

    BCMCTH_TRUNK_ALLOC(replace_mindex,
                  (entry->cnt) * sizeof(*replace_mindex),
                  "bcmcthTrunkSysRhGrpMembsDelRepReplaceMindexArr");

    BCMCTH_TRUNK_ALLOC(shrd_mindex,
                  (grp_member_cnt * sizeof(*shrd_mindex)),
                  "bcmcthTrunkSysRhGrpMembsDelRepShrdMindexArr");
    sal_memset(shrd_mindex,
               BCMCTH_TRUNK_INVALID,
               (grp_member_cnt * sizeof(*shrd_mindex)));

    /*
     * Order of member fields members in updated
     * member fields array is not same as the stored
     * member fields members array and some of the
     * members in the updated array might be
     * shared with the stored members. Identify
     * these shared members, deleted
     * members and members to be replaced.
     */
    for (idx = 0; idx < grp_member_cnt; idx++) {
        for (uidx = 0; uidx < entry->cnt; uidx++) {
            /*
             * Identify the common members and copy the stored member entry
             * usage count value to LT entry usage count element at the new
             * member index for delete and rebalance operation.
             */
            if (bcmcth_trunk_sys_compare_ent_idx(unit, entry, uidx, cur_entry, idx)
                && (0 == entry->rh_memb_ecnt_arr[uidx])) {
                entry->rh_memb_ecnt_arr[uidx] =
                        sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx];
                shrd_cnt++;
                if (idx != uidx) {
                    shrd_mindex[idx] = uidx;
                    shrd_new_mindex_cnt++;
                    /*
                     * Reset the entry usage counter value as this member
                     * will be maintained in the new index location "uidx"
                     * after the delete operation.
                     */
                }
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx] = 0;
                break;
            }
        }

        /*
         * If the member is a shared member, then continue to the next member
         * in the list.
         */
        if (uidx != entry->cnt) {
            continue;
        }

        /*
         * Member not found in the updated array, add this old member index
         * value be the deleted members array.
         */
        if (del_idx < deleted_cnt) {
            deleted_mindex[del_idx++] = idx;
        } else {
            /*
             * If this member is not a shared member and members delete count
             * has already been reached, then save this member for replacing
             * with a new member in the updated members array.
             */
            replace_mindex[replace_cnt++] = idx;
        }
    }
    /*
     * If there are members to be replaced, identify the members from the
     * updated member fields members array that
     * will be replacing the current members.
     * Save the new member index value that is replacing a current member and
     * also assign the current members entry usage count value to the new
     * member in LT entry array for use during delete member rebalance
     * calculations.
     */
    if (replace_cnt) {
        BCMCTH_TRUNK_ALLOC(new_mindex,
                      (replace_cnt) * sizeof(*new_mindex),
                      "bcmcthTrunkSysRhGrpMembsNewMindexArr");
        for (uidx = 0; uidx < entry->cnt; uidx++) {
            /*
             * Shared member entry count is already found, skip to next
             * member.
             */
            if (entry->rh_memb_ecnt_arr[uidx]) {
                continue;
            }
            for (idx = 0; idx < replace_cnt; idx++) {
                rep_idx = replace_mindex[idx];
                if (!sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[rep_idx])
                {
                    /*
                     * This replacement member candidate has already been
                     * associate with a new member from the updated array, move
                     * on to the next member in the replace mindex array.
                     */
                    continue;
                }
                entry->rh_memb_ecnt_arr[uidx] =
                  sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[rep_idx];
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[rep_idx] = 0;
                /*
                 * Save the new member index value that is replacing the current
                 * replacement member.
                 */
                new_mindex[idx] = uidx;

                break;

            }
        }
    }

    /* Perform members delete and rebalance operation. */
    for (idx = 0; idx < deleted_cnt; idx++) {
        /* Delete the member and re-balance the group entries. */
        SHR_IF_ERR_VERBOSE_EXIT
            (bcmcth_trunk_sys_rh_grp_memb_delete(unit,
                                        deleted_mindex[idx],
                                        entry));
    }
    /*
     * For the shared members, check and update the member index value in the
     * LT entry mindex array if it has changed.
     */
    if (shrd_new_mindex_cnt) {
        for (idx = 0; idx < grp_member_cnt; idx++) {
            new_idx = shrd_mindex[idx];
            if (new_idx == (uint32_t)BCMCTH_TRUNK_INVALID) {
                continue;
            }
            for (uidx = 0; uidx < entry->max_members; uidx++) {
                if (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                      cur_entry,
                      idx, entry, uidx)
                    && (idx == entry->rh_mindex_arr[uidx])) {

                    /* Update mindex with new mindex value. */
                    entry->rh_mindex_arr[uidx] = new_idx;
                }
            }
            shrd_new_mindex_cnt--;
        }
    }


    /*
     * For the replaced members, check and update the member index value with
     * the new members index value and also
     * update the member fields member value in
     * rh_entries_array.
     */
    if (replace_cnt) {
        for (idx = 0; idx < replace_cnt; idx++) {
            rep_idx = replace_mindex[idx];
            for (uidx = 0; uidx < entry->max_members; uidx++) {
                if (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                    cur_entry,
                    rep_idx,
                    entry,
                    uidx)
                    && (rep_idx == entry->rh_mindex_arr[uidx])) {

                    new_idx = new_mindex[idx];
                    /* Update mindex with new mindex value. */
                    entry->rh_mindex_arr[uidx] = new_idx;
                    /* Update with new member value. */
                    entry->rh_port[uidx] =
                        entry->port[new_idx];
                }
            }
        }
    }

    exit:
        /* Free memory allocated to store mindex array. */
        BCMCTH_TRUNK_FREE(deleted_mindex);
        BCMCTH_TRUNK_FREE(replace_mindex);
        BCMCTH_TRUNK_FREE(shrd_mindex);
        if (replace_cnt) {
            BCMCTH_TRUNK_FREE(new_mindex);
        }
        SHR_FUNC_EXIT();
}

/*!
 * \brief Reconstruct resilient TRUNK_SYSTEM group mebers load balanced state.
 *
 * This function reconstructs resilient
 * TRUNK_SYSTEM group members load balanced state post
 * warm start sequence to support subsequent members update operation.
 *
 * \param [in] unit      Unit number.
 * \param [in] sid       LT sid.
 * \param [in] op_arg    Operational arguments.
 * \param [in] entry     Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry Pointer to TRUNK_SYSTEM logical table entry previous data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_rh_grp_members_recover(int unit,
                                    bcmltd_sid_t sid,
                                    const bcmltd_op_arg_t *op_arg,
                                    bcmcth_trunk_sys_grp_param_t *entry,
                                    bcmcth_trunk_sys_grp_param_t *cur_entry)
{

    bcmcth_trunk_sys_grp_param_t *rhg_entry = NULL; /* Resilient group entry. */
    uint32_t trunk_id = BCMCTH_TRUNK_INVALID; /* Group identifier. */
    uint32_t idx = 0, memb_idx;      /* Index iterator variables. */
    uint32_t ubound = 0, lbound = 0; /* Upper bound and lower bound. */
    uint32_t threshold = 0;          /* Upper threshold value. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];


    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "%s.\n"), __func__));
    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */

    trunk_id = entry->id;
    /*
     * Allocate memory for resilient hashing group entry for performing the get
     * operation.
     */
    BCMCTH_TRUNK_ALLOC(rhg_entry, sizeof(*rhg_entry), "bcmcthTrunkRhLtEntry");
    BCMCTH_TRUNK_ALLOC
        (rhg_entry->rh_port,
         entry->max_members * sizeof(*(entry->rh_port)),
         "bcmcthTrunkRhLtEntryPortArr");
    /*
     * Setup input attribute values necessary for reading the RH group hardware
     * table entries.
     */
    rhg_entry->gtype = entry->gtype;
    rhg_entry->id = entry->id;

    /* Get resilient TRUNK_SYSTEM Group entry from hardware tables. */
    SHR_IF_ERR_EXIT
        (bcmcth_trunk_drv_sys_grp_lookup(unit,
                                  op_arg,
                                  sid,
                                  sys_grp_bk_temp_ptr,
                                  rhg_entry));

    lbound = (SYS_GRP_MAX_MEMBERS
                    (unit, trunk_id) / SYS_GRP_MEMBER_CNT(unit, trunk_id));
    ubound = ((SYS_GRP_MAX_MEMBERS(unit, trunk_id) %
                    SYS_GRP_MEMBER_CNT(unit, trunk_id))
                    ? (lbound + 1) : lbound);
    threshold = ubound;

    LOG_ERROR(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                            "\tLBND=%u UBND=%u THRSLD=%u LB_MODE=%u "
                            "max_members=%u \n"),
                lbound,
                ubound,
                threshold,
                rhg_entry->lb_mode,
                rhg_entry->max_members));

    /*
     * Verify retrieved total RH group member table entries count matches
     * stored/expected value before further processing for this RH group.
     */
    if (rhg_entry->max_members
        != SYS_GRP_MAX_MEMBERS(unit, trunk_id)) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }


    /* Allocate memory for RHG members structure. */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id],
                  sizeof(*(sys_grp_bk_ptr->rhg[trunk_id])),
                  "bcmcthTrunkSysRhGrpMembRcvrRhgInfo");
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id],
                  sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id])),
                  "bcmcthTrunkSysRhGrpMembRcvrRhgInfoTemp");

    /* Allocate memory to store RHG member table entries. */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
                  (rhg_entry->max_members *
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhEntArr");
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                  (rhg_entry->max_members *
                   sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhEntArrTemp");

    /* Copy load balanced RH members array. */
    sal_memcpy(sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
               rhg_entry->rh_port,
               sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port)) *
               rhg_entry->max_members);
    sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
               rhg_entry->rh_port,
               sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
               rhg_entry->max_members);

    /*
     * Allocate memory to store group resilient TRUNK_SYSTEM entries mapped member
     * index information.
     */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
                  (rhg_entry->max_members *
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhMindexArr");
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                  (rhg_entry->max_members *
                   sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhMindexArrTemp");

    /*
     * Allocate memory to store resilient TRUNK_SYSTEM members entries usage count
     * information.
     */
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                  (SYS_GRP_MAX_MEMBERS(unit, trunk_id) *
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhMembEntCntArr");
    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                  (SYS_GRP_MAX_MEMBERS(unit, trunk_id) *
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr))),
                  "bcmcthTrunkSysRhGrpMembRcvrRhMembEntCntArrTemp");


    for (memb_idx = 0;
         memb_idx < SYS_GRP_MEMBER_CNT(unit, trunk_id);
         memb_idx++) {
        for (idx = 0; idx < rhg_entry->max_members; idx++) {
            if ((rhg_entry->rh_port[idx]
                        != (uint16_t)(BCMCTH_TRUNK_INVALID)) &&
                (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                                   cur_entry,
                                   memb_idx, rhg_entry, idx))
                && (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[memb_idx]
                   < lbound)) {
                /* Update member index mapping */
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr[idx] = memb_idx;

                /* Update member table entries usage count for this member. */
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[memb_idx] += 1;
                /* Update as invalid as it's been matched. */
                rhg_entry->rh_port[idx] = BCMCTH_TRUNK_INVALID;

                /* Move on to the next member as lower bound as been reached. */
                if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx]
                    == lbound) {
                    break;
                }
            }
        }
    }
    /*
     * For remaining members compare the upper limit and update the member index
     * and member entries usage count values.
     */
    for (memb_idx = 0;
         memb_idx < SYS_GRP_MEMBER_CNT(unit, trunk_id);
         memb_idx++) {
        for (idx = 0; idx < rhg_entry->max_members; idx++) {
            if ((rhg_entry->rh_port[idx]
                           != (uint16_t)(BCMCTH_TRUNK_INVALID)) &&
                (bcmcth_trunk_sys_compare_rh_ent_idx(unit,
                                cur_entry,
                                memb_idx, rhg_entry, idx))
                && sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[memb_idx]
                   < ubound) {
                /* Update member index mapping */
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr[idx] = memb_idx;

                /* Update member table entries usage count for this member. */
                sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[memb_idx] += 1;

                /* Update as invalid as it's been matched. */
                rhg_entry->rh_port[idx] = BCMCTH_TRUNK_INVALID;

                /* Move on to the next member as upper bound as been reached. */
                if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr[idx]
                    == ubound) {
                    break;
                }
            }
        }
    }

    /*
     * Copy group entries mapped member index array elements into the backup
     * array.
     */
    sal_memcpy(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                rhg_entry->max_members));

    /*
     * Copy members entry usage count array elements into the backup
     * array.
     */
    sal_memcpy(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)) *
                SYS_GRP_MEMBER_CNT(unit, trunk_id)));

    exit:
        if (rhg_entry) {
            BCMCTH_TRUNK_FREE(rhg_entry->rh_port);
            BCMCTH_TRUNK_FREE(rhg_entry->rh_mindex_arr);
            BCMCTH_TRUNK_FREE(rhg_entry->rh_memb_ecnt_arr);
            BCMCTH_TRUNK_FREE(rhg_entry);
        }
        if (SHR_FUNC_ERR() && trunk_id != (uint32_t)(BCMCTH_TRUNK_INVALID)) {
            if (sys_grp_bk_ptr->rhg[trunk_id]) {
                BCMCTH_TRUNK_FREE(
                           sys_grp_bk_ptr->rhg[trunk_id]->rh_port);
                BCMCTH_TRUNK_FREE(
                           sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr);
                BCMCTH_TRUNK_FREE(
                           sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
                BCMCTH_TRUNK_FREE(
                           sys_grp_bk_ptr->rhg[trunk_id]);
            }

            if (sys_grp_bk_temp_ptr->rhg[trunk_id]) {
                BCMCTH_TRUNK_FREE(
                         sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port);
                BCMCTH_TRUNK_FREE(
                         sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr);
                BCMCTH_TRUNK_FREE(
                         sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
                BCMCTH_TRUNK_FREE(
                         sys_grp_bk_temp_ptr->rhg[trunk_id]);
            }
        }
        SHR_FUNC_EXIT();
}

/*!
 * \brief Distributes group members as per RH load balance algorithm.
 *
 * Distributes MEMBER_CNT group members among RH_SIZE member table entries for
 * installation in TRUNK_SYSTEM hardware tables.
 *
 * \param [in] unit       Unit number.
 * \param [in] entry      Pointer to TRUNK_SYSTEM logical table entry data.
 * \param [in] cur_entry  Pointer to TRUNK_SYSTEM logical table entry previous data.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_trunk_sys_grp_rh_entries_update(int unit,
                                     bcmcth_trunk_sys_grp_param_t *entry,
                                     bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    bcmcth_trunk_rh_oper_t rh_oper =
                 BCMCTH_TRUNK_RH_OPER_NONE; /* RH oper type. */

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    SHR_NULL_CHECK(cur_entry, SHR_E_PARAM);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META_U(unit,
                         "bcmcth_trunk_sys_grp_rh_entries_update.\n")));

    /* Get the type of resilient TRUNK_SYSTEM group operation. */
    SHR_IF_ERR_VERBOSE_EXIT
        (bcmcth_trunk_sys_grp_rh_oper_get(unit, entry, cur_entry, &rh_oper));

    /* Invoke operation dependent function. */
    switch (rh_oper) {
        case BCMCTH_TRUNK_RH_OPER_NONE:
            SHR_EXIT();
            break;
        case BCMCTH_TRUNK_RH_OPER_ADD:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_members_add(
                           unit, entry));
            break;
        case BCMCTH_TRUNK_RH_OPER_DELETE:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_members_delete(
                          unit, entry, cur_entry));
            break;
        case BCMCTH_TRUNK_RH_OPER_REPLACE:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_members_replace(
                         unit, entry, cur_entry));
            break;
        case BCMCTH_TRUNK_RH_OPER_ADD_REPLACE:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_members_add_replace(
                        unit, entry, cur_entry));
            break;
        case BCMCTH_TRUNK_RH_OPER_DELETE_REPLACE:
            SHR_IF_ERR_VERBOSE_EXIT
                (bcmcth_trunk_sys_rh_grp_members_delete_replace(
                        unit, entry, cur_entry));
            break;
        default:
            SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    exit:
        SHR_FUNC_EXIT();
}

static int
bcmcth_trunk_sys_rh_grp_entry_update(
                        int unit,
                        bcmltd_sid_t sid,
                        const bcmltd_op_arg_t *op_arg,
                        bcmcth_trunk_sys_grp_param_t *entry,
                        bcmcth_trunk_sys_grp_param_t *cur_entry)
{
    uint16_t trunk_id = 0;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    uint32_t cnt = 0;
    int rv  = SHR_E_NONE;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);
    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;

    /*
     * Check if group's LB_MODE is RESILIENT and call the corresponding
     * group install routine.
     */
    cnt =
        entry->cnt;

    if (entry->cnt
        > entry->max_members) {
        rv = SHR_E_PARAM;
        SHR_ERR_EXIT(rv);
    }

    /*
     * Allocate memory to store the RH balanced system ports for
     * installation in hardware tables.
     */
    BCMCTH_TRUNK_ALLOC
        (entry->rh_port,
         entry->max_members * sizeof(*(entry->rh_port)),
         "bcmcthTrunkSysRhGrpUpdateLtEntRhPort");
    /*
     * Allocate memory to store the RH group entry's mapped member index
     * data.
     */
    BCMCTH_TRUNK_ALLOC
        (entry->rh_mindex_arr,
         entry->max_members * sizeof(*(entry->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpUpdateLtEntRhMindexArr");

    /*
     * Allocate memory to store the RH group members entries usage count
     * data.
     */
    if (entry->cnt) {
        BCMCTH_TRUNK_ALLOC
            (entry->rh_memb_ecnt_arr,
             entry->cnt * sizeof(*(entry->rh_memb_ecnt_arr)),
             "bcmcthTrunkSysRhGrpUpdateLtEntRhMembEntCntArr");
    }
    /*
     * If UC_CNT value for this RH-group was zero prior to this update
     * operation and valid member fields are being added to this RH-group
     * in this UPDATE operation i.e. UC_CNT > 0, then this UPDATE
     * operation is equivalent to new members INSERT operation for
     * this group. So, use RH entries SET function for load balance
     * operation.
     */
    if (((SYS_GRP_MEMBER_CNT(unit, trunk_id) == 0)
        && (entry->cnt)) ||
        (entry->max_members != cur_entry->max_members)) {
        SHR_IF_ERR_EXIT(
        bcmcth_trunk_sys_grp_rh_realloc(unit, entry));
        SHR_IF_ERR_EXIT
        (bcmcth_trunk_sys_grp_rh_entries_set(unit, entry));
        /* Clear the preconfig if set. */
        if (SYS_GRP_PRECONFIG_GET(unit, trunk_id)) {
            SYS_GRP_PRECONFIG_CLEAR(unit, trunk_id);
        }
    } else {
        /* Check if pre-config flag is set for this group. */
        if (SYS_GRP_PRECONFIG_GET(unit, trunk_id)) {

            /*
             * Rebuild is not needed since the entry is already present
             * in the HA grp pointers.
             */
            SHR_IF_ERR_EXIT
                (bcmcth_trunk_sys_rh_grp_members_recover(
                                 unit,
                                 sid,
                                 op_arg,
                                 entry,
                                 cur_entry));

            /* Clear pre-config flag for this resilient TRUNK_SYSTEM group. */
            SYS_GRP_PRECONFIG_CLEAR(unit, trunk_id);
        }

        /*
         * This is an existing RH group members Add/Delete/Replace type of
         * operation. So, use RH entries UPDATE function to perform the
         * rebalancing work.
         */
        SHR_IF_ERR_EXIT
            (bcmcth_trunk_sys_grp_rh_entries_update(
                                unit,
                                entry,
                                cur_entry));
        SHR_IF_ERR_EXIT(
        bcmcth_trunk_sys_grp_rh_realloc(unit, entry));


    }
    /* Copy load balanced RH members system port array. */
    sal_memcpy
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
         entry->rh_port,
         (entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port))));

    /* Copy group entries mapped member index array. */
    sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               entry->rh_mindex_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                      entry->max_members));

    /* Copy members entry usage count information. */
    sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               entry->rh_memb_ecnt_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr))
                * cnt));


exit:
    SHR_FUNC_EXIT();

}

static int
bcmcth_trunk_sys_rh_grp_entry_add(int unit,
                        bcmcth_trunk_sys_grp_param_t *entry)
{
    uint16_t cnt;
    uint32_t trunk_id = 0;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *grp = NULL;
    int rv = SHR_E_NONE;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    /* Initialize group TRUNK_SYSTEM_ID and group type local variables. */
    trunk_id = entry->id;
    grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    /*
     * Check if group's LB_MODE is RESILIENT and call the corresponding
     * group install routine.
     */
    cnt =
        entry->cnt;

    if (entry->cnt
        > entry->max_members) {
        rv = SHR_E_PARAM;
        SHR_ERR_EXIT(rv);
    }

    /*
     * Allocate memory to store the RH balanced system ports for
     * installation in hardware tables.
     */
    BCMCTH_TRUNK_ALLOC
        (entry->rh_port,
         entry->max_members * sizeof(*(entry->rh_port)),
         "bcmcthTrunkSysRhGrpAddLtEntRhPort");
    /*
     * Allocate memory to store the RH group entry's mapped member index
     * data.
     */
    BCMCTH_TRUNK_ALLOC
        (entry->rh_mindex_arr,
         entry->max_members * sizeof(*(entry->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpAddLtEntRhMindexArr");

    /*
     * Allocate memory to store the RH group members entries usage count
     * data.
     */
    if (entry->cnt) {
        BCMCTH_TRUNK_ALLOC
            (entry->rh_memb_ecnt_arr,
             entry->cnt * sizeof(*(entry->rh_memb_ecnt_arr)),
             "bcmcthTrunkSysRhGrpAddLtEntRhMembEntCntArr");
    }

    /*
     * Set RH random seed from the user, which is used for selecting member
     */
    grp->rh_random_seed = entry->rh_random_seed;

    SHR_IF_ERR_EXIT
    (bcmcth_trunk_sys_grp_rh_entries_set(unit, entry));


    BCMCTH_TRUNK_ALLOC(sys_grp_bk_ptr->rhg[trunk_id],
                   sizeof(*(sys_grp_bk_ptr->rhg[trunk_id])),
                   "bcmcthTrunkSysRhGrpAddRhgInfo");

    BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id],
                   sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id])),
                   "bcmcthTrunkSysRhGrpAddRhgInfoTemp");
    /* Allocate memory to store resilient TRUNK_SYSTEM group system port entries. */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
         entry->max_members *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port)),
         "bcmcthTrunkSysRhGrpAddGrpRhPortArr");

    /*
     * Allocate temp memory to store resilient TRUNK_SYSTEM group
     * system port entries.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
         entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)),
         "bcmcthTrunkSysRhGrpAddGrpRhPortArr");

    /* Copy load balanced RH members system port array. */
    sal_memcpy
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
         entry->rh_port,
         (entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port))));

    /*
     * Allocate memory to store group resilient TRUNK_SYSTEM entries mapped member
     * index information.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpAddGrpRhMindexArr");

    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)),
         "bcmcthTrunkSysRhGrpAddGrpRhMindexArrTemp");

    /* Copy group entries mapped member index array. */
    sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
               entry->rh_mindex_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                      entry->max_members));

    /*
     * Allocate memory to store resilient TRUNK_SYSTEM members entries usage count
     * information.
     */
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)),
         "bcmcthTrunkSysRhGrpAddGrpRhMembEntCntArr");
    BCMCTH_TRUNK_ALLOC
        (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
         entry->max_members *
         sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)),
         "bcmcthTrunkSysRhGrpAddGrpRhMembEntCntArrTemp");

    /* Copy members entry usage count information. */
    sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
               entry->rh_memb_ecnt_arr,
               (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr))
                * cnt));


exit:
    SHR_FUNC_EXIT();

}


static int
bcmcth_sys_trunk_find_trunk_id(int unit,
                            bcmcth_trunk_sys_grp_bk_t *bk,
                            uint32_t base_index,
                            uint32_t *sys_trunk_id)
{
    bcmcth_trunk_imm_sys_group_t *grp;
    int group_cnt;
    int group_id;

    SHR_FUNC_ENTER(unit);

    *sys_trunk_id = -1;
    grp = bk->grp_ptr->sys_grp_array;
    group_cnt = bk->max_group_cnt;

    for (group_id = 0; group_id < group_cnt; group_id++) {
        if ((grp->base_ptr == base_index) &&
            (grp->inserted == TRUE)) {
            *sys_trunk_id = group_id;
            SHR_EXIT();
        }
        grp++;
    }

    SHR_VERBOSE_EXIT(SHR_E_NOT_FOUND);

exit:
   SHR_FUNC_EXIT();
}

static int
bcmcth_sys_trunk_itbm_defragment(int unit,
                                 const bcmltd_op_arg_t *op_arg,
                                 bcmltd_sid_t lt_id,
                                 uint32_t trunk_id,
                                 uint32_t new_mem_max,
                                 bcmcth_trunk_sys_grp_bk_t *bk_record,
                                 shr_itbm_list_hdl_t itbm_hdl)
{
    shr_itbm_blk_t *itbm_blk = NULL;
    uint32_t itbm_blk_count;
    shr_itbm_defrag_blk_mseq_t *m_seq;
    bcmcth_trunk_grp_defrag_t m_src, m_dest;
    int rv;
    uint32_t i, j;
    bcmcth_trunk_imm_sys_group_t *grp = NULL;
    uint32_t dfg_fblk_count = 0;
    shr_itbm_blk_t *dfg_fblk_arr = NULL;
    shr_itbm_blk_t dfg_lfblk;
    int old_base = -1;
    int new_base = -1;
    uint32_t last_idx = 0;
    bool defrag_start = FALSE;

    SHR_FUNC_ENTER(unit);
    grp = SYS_GRP_HA(unit)->grp_ptr->sys_grp_array + trunk_id;
    old_base = grp->base_ptr;

    /*
     * Initialize group member start index to the table Min index value as we have
     * to start the compression operation from the first (Min) index of the
     * table.
     */
    shr_itbm_blk_t_init(&dfg_lfblk);
    SHR_IF_ERR_EXIT
        (shr_itbm_list_defrag_start(itbm_hdl,
                                    &itbm_blk_count,
                                    &itbm_blk,
                                    &m_seq,
                                    &dfg_fblk_count,
                                    &dfg_fblk_arr,
                                    &dfg_lfblk));
    if (dfg_fblk_count) {
        /*
         * Free block size available.
         * 1. Check for the largest lock if availble for the
         * requested resources.
         * 2. Check if the free block sie meets the criteria for
         * resize.
         */
        if (dfg_lfblk.ecount  >= new_mem_max) {
            defrag_start = TRUE;
        } else {
            for (i = 0; i < itbm_blk_count; i++) {
                if (old_base != (int) itbm_blk[i].first_elem) {
                    continue;
                }
                last_idx = (int) (m_seq[i].mcount - 1);
                new_base = m_seq[i].first_elem[last_idx];
                for (j = 0; j < dfg_fblk_count; j++) {
                    if (dfg_fblk_arr[j].first_elem ==
                       new_base + itbm_blk[i].ecount) {
                        if ((dfg_fblk_arr[j].ecount +
                             itbm_blk[i].ecount) >= new_mem_max) {
                            defrag_start = TRUE;
                        }
                        break;
                    }
                }
            }
        }
    }

    if (defrag_start == FALSE) {
        LOG_VERBOSE(BSL_LOG_MODULE,
        (BSL_META_U(unit,
        "TRUNK_SYSTEM GROUP_ID=%d cannot be inserted due to lack of resources."),
        trunk_id));
        SHR_IF_ERR_EXIT(shr_itbm_list_defrag_end(itbm_hdl, false));
        SHR_ERR_EXIT(SHR_E_RESOURCE);
    }

    for (i = 0; i < itbm_blk_count; ++i) {
        /* itbm_blk gives source information */
        m_src.group_base = itbm_blk[i].first_elem;
        m_src.group_size = itbm_blk[i].ecount;

        /* Needs to retrive group ID based on source index */
        rv = bcmcth_sys_trunk_find_trunk_id(unit, bk_record, m_src.group_base, &m_src.trunk_id);

        if (rv == SHR_E_NOT_FOUND) {
            LOG_ERROR(BSL_LOG_MODULE,
                      (BSL_META_U(unit, "Trunk ITBM trunk id not found")));

            SHR_ERR_EXIT(rv);
        }
        for (j = 0; j < (m_seq[i].mcount); ++j) {
            /* m_seq gives move to - destination information */
            m_dest.group_base = m_seq[i].first_elem[j];
            m_dest.group_size = m_seq[i].ecount;

            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit,
                                    "Trunk ITBM defragment oper - blk[%d] seq[%d] - tid: %4d, "
                                    "src_base: %4d, src_size: %d, dest_base: %4d, dest_size: %4d \n"),
                                    i, j, m_src.trunk_id,
                                    m_src.group_base,
                                    m_src.group_size,
                                    m_dest.group_base,
                                    m_dest.group_size));

            rv = bcmcth_trunk_drv_sys_grp_move(unit,
                                               op_arg,
                                               lt_id,
                                               bk_record,
                                               &m_src,
                                               &m_dest);

            if (rv != SHR_E_NONE) {
                LOG_ERROR(BSL_LOG_MODULE,
                          (BSL_META_U(unit, "Trunk ITBM defragmentation HW move error: %d "), rv));
                SHR_ERR_EXIT(rv);
            }

            m_src.group_base = m_dest.group_base;
            m_src.group_size = m_dest.group_size;
        }

        /* Mark that this trunk group is moved */
        SHR_BITSET(SYS_GRP_DIFF(unit), m_src.trunk_id);
    }

    SHR_IF_ERR_EXIT(shr_itbm_list_defrag_end(itbm_hdl, true));

exit:
    SHR_FUNC_EXIT();
}

static int
bcmcth_sys_trunk_itbm_base_allocate(int unit,
                                    const bcmltd_op_arg_t *op_arg,
                                    bcmltd_sid_t lt_id,
                                    uint32_t trunk_id,
                                    bcmcth_trunk_sys_grp_bk_t *bk_record,
                                    uint32_t new_mem_max,
                                    uint32_t *new_base)
{
    int rv;
    uint32_t bucket = SHR_ITBM_INVALID;
    uint32_t itbm_new_base;
    shr_itbm_list_hdl_t itbm_hdl;
    bcmcth_trunk_imm_sys_group_t *grp = NULL;
    uint32_t old_max = 0;
    int old_base = -1;

    SHR_FUNC_ENTER(unit);

    grp = SYS_GRP_HA(unit)->grp_ptr->sys_grp_array + trunk_id;
    old_base = grp->base_ptr;
    old_max = grp->max_members;

    itbm_hdl = bk_record->itbm_hdl;

    /* Try to allocate new blocks */
    rv = shr_itbm_list_block_alloc(itbm_hdl,
                                   new_mem_max,
                                   &bucket,
                                   &itbm_new_base);
    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                            "Trunk ITBM base allocate rv=%d new_base %d.\n"),
                            rv, itbm_new_base));

    /* Need defragmentation. */
    if ((SHR_E_FULL == rv) || (SHR_E_RESOURCE == rv)) {

        /* Defragment the member table and retry for index allocation. */
        SHR_IF_ERR_EXIT(
            bcmcth_sys_trunk_itbm_defragment(unit,
                                             op_arg,
                                             lt_id,
                                             trunk_id,
                                             new_mem_max,
                                             bk_record,
                                             itbm_hdl));

        rv = shr_itbm_list_block_resize(itbm_hdl,
                                        old_max,
                                        bucket,
                                        old_base,
                                        new_mem_max);
        if (rv == SHR_E_NONE) {
            *new_base = old_base;
            SHR_ERR_EXIT(rv);
        } else {
            /* Try to allocate again after defragmentation */
            rv = shr_itbm_list_block_alloc(
                                       itbm_hdl,
                                       new_mem_max,
                                       &bucket,
                                       &itbm_new_base);
        }
    }

    if (rv == SHR_E_NONE) {
        *new_base = itbm_new_base;
    } else {
        SHR_ERR_EXIT(SHR_E_RESOURCE);
    }

exit:

    SHR_FUNC_EXIT();
}

static int
bcmcth_sys_trunk_itbm_base_update(int unit,
                                  const bcmltd_op_arg_t *op_arg,
                                  bcmltd_sid_t lt_id,
                                  bcmcth_trunk_sys_grp_bk_t *bk,
                                  bcmcth_trunk_sys_grp_param_t *param,
                                  uint32_t *new_base)
{
    int rv;
    shr_itbm_list_hdl_t itbm_hdl;
    bcmcth_trunk_imm_sys_group_t *grp;
    uint32_t old_base, old_max, new_max;

    SHR_FUNC_ENTER(unit);

    /* Locate info structure based on trunk_id */
    grp = bk->grp_ptr->sys_grp_array + param->id;
    old_base = grp->base_ptr;
    old_max  = grp->max_members;
    *new_base = old_base;

    itbm_hdl = bk->itbm_hdl;


    if (param->max_members_valid) {
        new_max  = param->max_members;
    } else {
        new_max = grp->max_members;
    }

    /* If member max is the same, return */
    if (new_max == old_max) {
        SHR_EXIT();
    }

    /* Run resize first which will handle two cases:
     * 1. Same base with shrinked member count - pass for sure
     * 2. Same base with Slightly increased member count, pass based on gap size
     *    between blocks.
     */
    rv = shr_itbm_list_block_resize(itbm_hdl,
                                    old_max,
                                    SHR_ITBM_INVALID,
                                    old_base,
                                    new_max);

    if (rv != SHR_E_NONE) {
        /* Now we have to look for a new base and do defragmentation if needed */
        rv = bcmcth_sys_trunk_itbm_base_allocate(unit,
                                                 op_arg,
                                                 lt_id,
                                                 param->id,
                                                 bk,
                                                 new_max,
                                                 new_base);
        if (rv == SHR_E_NONE) {
            /*
             * Get old base.
             * Old base could have changed due to defragmentation.
             */
            old_base = grp->base_ptr;

            /* Get new base. Free old one if not resize. */
            if (old_base != *new_base) {
                rv = shr_itbm_list_block_free(itbm_hdl,
                                              old_max,
                                              SHR_ITBM_INVALID,
                                              old_base);
                if (rv != SHR_E_NONE) {
                    LOG_ERROR(BSL_LOG_MODULE,
                          (BSL_META_U(unit, "Trunk ITBM list block free failure")));

                    SHR_ERR_EXIT(rv);
                }
            }
        } else {
            SHR_ERR_EXIT(rv);
        }
    }

exit:
    SHR_FUNC_EXIT();
}

static int
bcmcth_sys_trunk_itbm_delete_block(int unit,
                                   bcmcth_trunk_sys_grp_bk_t *bk,
                                   bcmcth_trunk_sys_grp_param_t *param)
{
    bcmcth_trunk_imm_sys_group_t *grp;

    SHR_FUNC_ENTER(unit);

    /* Locate info structure based on trunk_id */
    grp = bk->grp_ptr->sys_grp_array + param->id;

    /* Delete current ITBM block */
    SHR_IF_ERR_EXIT(shr_itbm_list_block_free(bk->itbm_hdl,
                                             grp->max_members,
                                             SHR_ITBM_INVALID,
                                             grp->base_ptr));

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief Check the availability of the member pool resources before the
 * load balancing mode change for an LT update operation.
 *
 * returns a bool flag res_avial set if resources are available.
 *
 * \param [in] unit            Unit number.
 * \param [in] trunk_entry     Pointer to LT entry.
 * \param [out res_avail       Flag indicating the resource availability.
 *
 * \return SHR_E_NONE No errors.
 * \return SHR_E_PARAM Input parameter error.
 */
static int
bcmcth_sys_trunk_itbm_check_member_pool_resource(
                             int unit,
                             bcmcth_trunk_sys_grp_param_t *trunk_entry,
                             bool *res_avail)
{
    shr_itbm_blk_t *itbm_blk = NULL;
    uint32_t itbm_blk_count;
    shr_itbm_defrag_blk_mseq_t *m_seq;
    int rv;
    int rv1;
    bcmcth_trunk_imm_sys_group_t *grp = NULL;
    bcmcth_trunk_imm_sys_group_t *grp_temp = NULL;
    uint32_t dfg_fblk_count = 0;
    shr_itbm_blk_t *dfg_fblk_arr = NULL;
    shr_itbm_blk_t dfg_lfblk;
    int new_base = -1;
    uint32_t trunk_id = -1;
    bool is_grp_members_free = FALSE;
    uint32_t bucket = SHR_ITBM_INVALID;
    /* Grp TEMP. */
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit]; /* GRP HA.*/

    SHR_FUNC_ENTER(unit);
    LOG_VERBOSE(BSL_LOG_MODULE,
               (BSL_META_U(unit,
                           "%s.\n"), __func__));
    SHR_NULL_CHECK(trunk_entry, SHR_E_PARAM);
    SHR_NULL_CHECK(sys_grp_bk_temp_ptr, SHR_E_PARAM);
    SHR_NULL_CHECK(sys_grp_bk_ptr, SHR_E_PARAM);
    /* Get thr trunk group identifier. */
    trunk_id = trunk_entry->id;
    *res_avail = FALSE;

    /* Locate HA info structure based on trunk_id */
    grp = sys_grp_bk_ptr->grp_ptr->sys_grp_array + trunk_id;
    /* Locate TEMP info structure based on trunk_id */
    grp_temp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    /* Free the member block resources. */
    SHR_IF_ERR_EXIT(
          shr_itbm_list_block_free(sys_grp_bk_ptr->itbm_hdl,
                                   grp->max_members,
                                   SHR_ITBM_INVALID,
                                   grp->base_ptr));

    /* Set the group members free flag. */
    is_grp_members_free = TRUE;
    /* Get the free the member table block for new max_members. */
    rv = shr_itbm_list_block_alloc(sys_grp_bk_temp_ptr->itbm_hdl,
                                    trunk_entry->max_members,
                                    &bucket,
                                    (uint32_t *) &new_base);

    if (SHR_E_NONE == rv) {
        /* Free the current usage. */
        SHR_IF_ERR_EXIT(
          shr_itbm_list_block_free(sys_grp_bk_temp_ptr->itbm_hdl,
                                   trunk_entry->max_members,
                                   SHR_ITBM_INVALID,
                                   (uint32_t) new_base));
        *res_avail = TRUE;
        SHR_EXIT();
    } else if ((SHR_E_FULL != rv) && (SHR_E_RESOURCE != rv)) {
        SHR_ERR_EXIT(rv);
    }

   /*
     * Initialize group member start index to the table
     * Min index value as we have
     * to start the compression operation from the first (Min) index of the
     * table.
     */
    shr_itbm_blk_t_init(&dfg_lfblk);
    rv = shr_itbm_list_defrag_start(sys_grp_bk_temp_ptr->itbm_hdl,
                                    &itbm_blk_count,
                                    &itbm_blk,
                                    &m_seq,
                                    &dfg_fblk_count,
                                    &dfg_fblk_arr,
                                    &dfg_lfblk);
    if (rv != SHR_E_NONE) {
        LOG_ERROR(BSL_LOG_MODULE,
                             (BSL_META_U(unit,
                                         "defrag start failed rv=%d\n"),
                             rv));
        SHR_ERR_EXIT(rv);
    }
    if (dfg_fblk_count <= 0) {
        *res_avail = FALSE;
    } else if (dfg_lfblk.ecount >= trunk_entry->max_members) {
        *res_avail = TRUE;
    }

    rv = shr_itbm_list_defrag_end(sys_grp_bk_temp_ptr->itbm_hdl, false);
    if (rv != SHR_E_NONE) {
        LOG_ERROR(BSL_LOG_MODULE,
                            (BSL_META_U(unit,
                                        "defrag end failed rv=%d\n"),
                             rv));
        SHR_ERR_EXIT(rv);
    }

exit:
    if (is_grp_members_free) {
        rv1 = shr_itbm_list_block_alloc(sys_grp_bk_ptr->itbm_hdl,
                                        grp->max_members,
                                        &bucket,
                                        (uint32_t *) &grp_temp->base_ptr);
        if (SHR_SUCCESS(rv1)){
            if ((grp_temp->base_ptr != grp->base_ptr)) {
                LOG_VERBOSE(BSL_LOG_MODULE,
                            (BSL_META_U(unit,
                                 "Change in base pointer due to the member"
                                 "resource check for TRUNK_SYSTEM group %d\n"),
                            trunk_id));
            }
        } else {
            /* Record the latest error. */
            rv = rv1;
        }
    }
    SHR_FUNC_EXIT();
}

/*!
 * \brief Get all current imm TRUNK_SYSTEM LT fields.
 *
 * Get the current fields from imm TRUNK_SYSTEM LT
 *
 * \param [in]  unit   Unit number.
 * \param [in]  sid    LT sid.
 * \param [out] entry  TRUNK_SYSTEM LT entry data buffer.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Faild to geet current LT entry fields.
 */
static int
bcmcth_trunk_sys_grp_lt_fields_lookup(int unit,
                                  bcmltd_sid_t sid,
                                  bcmcth_trunk_sys_grp_param_t *entry)
{
    bcmltd_fields_t key_fields = {0};
    bcmltd_fields_t imm_fields = {0};
    bcmltd_fields_t *flist;
    bcmltd_field_t *data_field;
    size_t num_fields= 0, i;
    int rv = SHR_E_NONE;
    uint16_t member_count = 1;

    SHR_FUNC_ENTER(unit);

    /* Validate input parameter. */
    SHR_NULL_CHECK(entry, SHR_E_PARAM);

    /* Allocate key field */
    SHR_IF_ERR_EXIT
        (bcmcth_trunk_group_lt_fields_allocate(unit,
                                               1,
                                               &key_fields));
    key_fields.field[0]->id   = TRUNK_SYSTEMt_TRUNK_SYSTEM_IDf;
    key_fields.field[0]->data = entry->id;

    /* Allocate imm fields */
    SHR_IF_ERR_EXIT
        (bcmlrd_field_count_get(unit, sid, &num_fields));

    /* Get the member fields count for the TRUNK_SYSTEM LT. */
    member_count =
         bcmcth_trunk_drv_sys_grp_member_flds_cnt_get(unit);

    num_fields += (size_t) member_count *
                 SYS_GRP_MAX_MEMBERS(unit, entry->id);
    SHR_IF_ERR_EXIT
        (bcmcth_trunk_group_lt_fields_allocate(unit,
                                               num_fields,
                                               &imm_fields));

    /* Lookup IMM table; error if entry not found */
    rv = bcmimm_entry_lookup(unit,
                             sid,
                             &key_fields,
                             &imm_fields);
    if (rv == SHR_E_RESOURCE) {
        /* In the case that some array elements are reset to default value after
         * MAX paths is decreasing, but they will still be returned by IMM. So
         * use BCMCTH_TRUNK_LT_MAX_NMEMBERS to lookup again
         * when resource error.
         */
        /* reset imm fields count for freeing mem */
        imm_fields.count = num_fields;
        bcmcth_trunk_group_lt_fields_free(unit, &imm_fields);

        num_fields -= (size_t) member_count *
                      SYS_GRP_MAX_MEMBERS(unit, entry->id);
        num_fields += (size_t) member_count *
                      SYS_GRP_TEMP(unit)->max_member_cnt;

        SHR_IF_ERR_EXIT
            (bcmcth_trunk_group_lt_fields_allocate(unit,
                                                   num_fields,
                                                   &imm_fields));
        SHR_IF_ERR_EXIT
            (bcmimm_entry_lookup(unit,
                                 sid,
                                 &key_fields,
                                 &imm_fields));
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit,
                                "TRUNK_SYSTEM_ID=%d contains %u fields.\n"),
                     entry->id,
                     (unsigned int)imm_fields.count));
    } else {
        SHR_IF_ERR_EXIT(rv);
    }
    flist = &imm_fields;

    /* Parse IMM table data fields */
    for (i = 0; i < flist->count; i++) {
        data_field = flist->field[i];
        SHR_IF_ERR_EXIT
              (bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(
                     unit,
                     data_field,
                     entry));
    }

exit:
    bcmcth_trunk_group_lt_fields_free(unit, &key_fields);
    /* reset imm fields count for freeing mem */
    imm_fields.count = num_fields;
    bcmcth_trunk_group_lt_fields_free(unit, &imm_fields);

    SHR_FUNC_EXIT();
}

/*!
 * \brief Fill TRUNK_SYSTEM member fields into
           lt member field array from cur entry.
 *
 * \param [in] unit                      Unit number.
 * \param [in] cur_mfield                Array of current entry
 *                                       Member fields.
 * \param [in] entry                     Pointer to lt entry.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_INTERNAL failure.
 */
static int
bcmcth_trunk_sys_grp_member_fields_fill(
                                int unit,
                                bcmcth_trunk_sys_grp_param_t *cur_entry,
                                bcmcth_trunk_sys_grp_param_t *entry)
{
    uint32_t idx;

    SHR_FUNC_ENTER(unit);

    if ((entry == NULL) || (cur_entry == NULL)) {
       SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    for (idx = 0; idx < entry->cnt; idx++) {
        if ((!entry->port[idx]) &&
             (!entry->port_valid[idx])) {
             entry->port[idx] =
                     cur_entry->port[idx];
             entry->port_valid[idx] = TRUE;
        }
    }

    SHR_ERR_EXIT(SHR_E_NONE);
exit:
        SHR_FUNC_EXIT();
}

static int
bcmcth_trunk_imm_sys_grp_update(int unit,
                                const bcmltd_op_arg_t *op_arg,
                                bcmltd_sid_t sid,
                                const bcmltd_field_t *key,
                                const bcmltd_field_t *data,
                                bcmimm_entry_event_t event_reason)
{
    bcmcth_trunk_sys_grp_param_t trunk_entry = {0};
    bcmcth_trunk_sys_grp_param_t *cur_entry = NULL;
    int trunk_id = 0;
    uint32_t new_base = -1;
    int i = 0;
    uint16_t *val = NULL;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;
    bool space_available = FALSE;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(key, SHR_E_PARAM);

    if (sid != TRUNK_SYSTEMt) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    bcmcth_trunk_sys_grp_param_t_init(&trunk_entry);
    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(unit,
                                              key,
                                              &trunk_entry));
    /* Trunk group identifier. */
    trunk_id = trunk_entry.id;
    /* Read the trunk group temp info. */
    sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    if (event_reason == BCMIMM_ENTRY_UPDATE) {
        trunk_entry.gtype = sys_grp->gtype;
    }

    /* Parse the TRUNK.LB_MODE field. */
    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_lb_mode_parse(unit,
                                              data,
                                              &trunk_entry));
    /* Parse the TRUNK_SYSTEM LT data fields. */
    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(unit,
                                              data,
                                              &trunk_entry));
    trunk_id = trunk_entry.id;
    if (event_reason == BCMIMM_ENTRY_UPDATE) {
        /* Read the previous TRUNK_SYSTEM LT entry. */
        cur_entry = sal_alloc(sizeof(bcmcth_trunk_sys_grp_param_t),
                               "bcmcthTrunkCurLtEntry");
        SHR_NULL_CHECK(cur_entry, SHR_E_MEMORY);
        bcmcth_trunk_sys_grp_param_t_init(cur_entry);

        /* Initialize the key - trunk_id. */
        cur_entry->id = trunk_id;
        /*
         * gtype is resolved indirectly from lb_mode.
         */
        if (trunk_entry.lb_mode_valid) {
            cur_entry->gtype = trunk_entry.gtype;
        } else {
            cur_entry->gtype = sys_grp->gtype;
            trunk_entry.gtype = sys_grp->gtype;
        }

        /*
         * Read the default values for the currrent entry.
         */
        SHR_IF_ERR_VERBOSE_EXIT(
               bcmcth_trunk_sys_grp_lt_entry_def_val_get(
                                                unit,
                                                cur_entry));

        SHR_IF_ERR_EXIT(
            bcmcth_trunk_sys_grp_lt_fields_lookup(
                                  unit,
                                  sid,
                                  cur_entry));

        /*
         * cnt carries the UC_MEMBER_CNT for regular hashing groups.
         * cnt carries the RH_UC_MEMBER_CNT for the resilient hashing groups.
         */
        if (!trunk_entry.cnt_valid) {
            trunk_entry.cnt = cur_entry->cnt;
            trunk_entry.cnt_valid = TRUE;
        }

        /*
         * max_members carries the value of the field
         * UC_MAX_MEMBER for the regular hash load balancing groups.
         * uc_max_memebers carries the count derived from the conversion
         * of field RH_SIZE to max member count for the resilient
         * hashing load balancing groups.
         */
        if (!trunk_entry.max_members_valid) {
            trunk_entry.max_members = cur_entry->max_members;
            trunk_entry.max_members_valid = TRUE;
        }
        if (!trunk_entry.rh_random_seed_valid) {
            trunk_entry.rh_random_seed = sys_grp->rh_random_seed;
            trunk_entry.rh_random_seed_valid = TRUE;
        } else {
            sys_grp->rh_random_seed = trunk_entry.rh_random_seed;
        }

        /* Copy the member fields from previous lt entry. */
        SHR_IF_ERR_EXIT
            (bcmcth_trunk_sys_grp_member_fields_fill(
                                         unit,
                                         cur_entry,
                                         &trunk_entry));

        if ((trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)  &&
            (sys_grp->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)) {
            /* Resilient group redistribute the entries. */
            SHR_IF_ERR_EXIT(
                bcmcth_trunk_sys_rh_grp_entry_update(
                                    unit,
                                    sid,
                                    op_arg,
                                    &trunk_entry,
                                    cur_entry));
            if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_base_update(unit,
                                                  op_arg,
                                                  sid,
                                                  SYS_GRP_TEMP(unit),
                                                  &trunk_entry,
                                                  &new_base));
            }

            SHR_IF_ERR_EXIT(
                bcmcth_trunk_drv_sys_grp_update(unit,
                                                op_arg,
                                                sid,
                                                SYS_GRP_TEMP(unit),
                                                &trunk_entry,
                                                new_base));


        } else if ((trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)  &&
            (sys_grp->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR)) {
            /*
             * Group updated to the load balancing mode resilient from
             * regular hashing. This operation is like insert.
             * However the LT fields have to be recovered from the
             * grp_bk, if all fields applicable to resilient hashing are
             * not supplied in the LT update operation.
             * Delete the exisiting group and re-add.
             */
            if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_check_member_pool_resource(
                                           unit,
                                           &trunk_entry,
                                           &space_available));
                if (space_available == FALSE) {
                    SHR_IF_ERR_EXIT(SHR_E_RESOURCE);
                }
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_delete_block(unit,
                                                   SYS_GRP_TEMP(unit),
                                                   &trunk_entry));
            }
            SHR_IF_ERR_EXIT(
                 bcmcth_trunk_drv_sys_grp_del(unit,
                                              op_arg,
                                              sid,
                                              SYS_GRP_TEMP(unit),
                                              &trunk_entry));
            bcmcth_trunk_sys_grp_rh_free(unit,
                                       trunk_id);

            BCMCTH_TRUNK_SYS_GRP_INSERTED_SET(unit, trunk_id, FALSE);

            if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT
                    (bcmcth_sys_trunk_itbm_base_allocate(
                                                 unit,
                                                 op_arg,
                                                 sid,
                                                 trunk_id,
                                                 SYS_GRP_TEMP(unit),
                                                 trunk_entry.max_members,
                                                 &new_base));
            }


            /* Resilient group redistribute the entries. */

            SHR_IF_ERR_EXIT(
               bcmcth_trunk_sys_rh_grp_entry_add(
                                    unit,
                                    &trunk_entry));

            SHR_IF_ERR_EXIT(
                bcmcth_trunk_drv_sys_grp_add(unit,
                                             op_arg,
                                             sid,
                                             SYS_GRP_TEMP(unit),
                                             &trunk_entry,
                                             new_base));

        } else if ((trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR)  &&
            (sys_grp->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)) {
            /*
             * Group updated to the load balancing mode regular from
             * resilient hashing. This operation is like insert.
             * However the LT fields have to be recovered from the
             * grp_bk, if all fields applicable to regular hashing or
             * random mode are not supplied in the LT update operation.
             * Delete the exisiting group and re-add.
             */
            if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_check_member_pool_resource(
                                           unit,
                                           &trunk_entry,
                                           &space_available));
                if (space_available == FALSE) {
                    SHR_IF_ERR_EXIT(SHR_E_RESOURCE);
                }
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_delete_block(unit,
                                                   SYS_GRP_TEMP(unit),
                                                   &trunk_entry));
            }
            SHR_IF_ERR_EXIT(
                 bcmcth_trunk_drv_sys_grp_del(unit,
                                              op_arg,
                                              sid,
                                              SYS_GRP_TEMP(unit),
                                              &trunk_entry));

            bcmcth_trunk_sys_grp_rh_free(unit,
                                       trunk_id);
            /* Clear pre-config flag for this resilient TRUNK_SYSTEM group. */
            if (SYS_GRP_PRECONFIG_GET(unit, trunk_id)) {
                SYS_GRP_PRECONFIG_CLEAR(unit, trunk_id);
            }

            BCMCTH_TRUNK_SYS_GRP_INSERTED_SET(unit, trunk_id, FALSE);

             if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT
                    (bcmcth_sys_trunk_itbm_base_allocate(
                                                 unit,
                                                 op_arg,
                                                 sid,
                                                 trunk_id,
                                                 SYS_GRP_TEMP(unit),
                                                 trunk_entry.max_members,
                                                 &new_base));
            }

            SHR_IF_ERR_EXIT(
                bcmcth_trunk_drv_sys_grp_add(unit,
                                             op_arg,
                                             sid,
                                             SYS_GRP_TEMP(unit),
                                             &trunk_entry,
                                             new_base));

        } else if ((trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR)  &&
            (sys_grp->gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR)) {
            /*
             * Group updated with load balancing mode regular hashing
             * to regular hashing.
             */
            if (SYS_GRP_TEMP(unit)->itbm_support) {
                SHR_IF_ERR_EXIT(
                    bcmcth_sys_trunk_itbm_base_update(unit,
                                                  op_arg,
                                                  sid,
                                                  SYS_GRP_TEMP(unit),
                                                  &trunk_entry,
                                                  &new_base));
            }

            SHR_IF_ERR_EXIT(
                bcmcth_trunk_drv_sys_grp_update(unit,
                                             op_arg,
                                             sid,
                                             SYS_GRP_TEMP(unit),
                                             &trunk_entry,
                                             new_base));

        } else {
            SHR_ERR_EXIT(SHR_E_INTERNAL);
        }
    } else if (event_reason == BCMIMM_ENTRY_INSERT) {
        /*
        * Read the default values for the currrent entry.
        */
        SHR_IF_ERR_VERBOSE_EXIT(
               bcmcth_trunk_sys_grp_lt_entry_def_val_get(
                                                unit,
                                                &trunk_entry));

        if (SYS_GRP_TEMP(unit)->itbm_support) {
            SHR_IF_ERR_EXIT
                (bcmcth_sys_trunk_itbm_base_allocate(unit,
                                                     op_arg,
                                                     TRUNK_SYSTEMt,
                                                     trunk_id,
                                                     SYS_GRP_TEMP(unit),
                                                     trunk_entry.max_members,
                                                     &new_base));
        }

        /* Resilient group redistribute the entries. */
        if (trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
            SHR_IF_ERR_EXIT(
               bcmcth_trunk_sys_rh_grp_entry_add(
                                    unit,
                                    &trunk_entry));
        }

        SHR_IF_ERR_VERBOSE_EXIT(
            bcmcth_trunk_drv_sys_grp_add(unit,
                                         op_arg,
                                        TRUNK_SYSTEMt,
                                         SYS_GRP_TEMP(unit),
                                         &trunk_entry,
                                         new_base));
    } else {
       SHR_ERR_EXIT(SHR_E_INTERNAL);
    }


    BCMCTH_TRUNK_SYS_GRP_INSERTED_SET(unit, trunk_id, TRUE);

    if (trunk_entry.cnt_valid) {
       (BCMCTH_TRUNK_SYS_GRP_MEMBER_CNT_SET(unit,
                                            trunk_id,
                                            trunk_entry.cnt));
    }

    if (trunk_entry.max_members_valid) {
       (BCMCTH_TRUNK_SYS_GRP_MAX_MEMBERS_SET(unit,
                                             trunk_id,
                                             trunk_entry.max_members));
    }

    if (trunk_entry.cnt_valid) {
        BCMCTH_TRUNK_SYS_GRP_MEMBER_CNT_SET(
                  unit, trunk_id, trunk_entry.cnt);
    }

    /* Write the gtype to group temp info. */
    sys_grp->gtype = trunk_entry.gtype;

    if (trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
        for (i = 0; i < BCMCTH_TRUNK_SYSTEM_RH_MAX_MEMBERS; i++) {
            if (trunk_entry.port_valid[i]) {
                val = (uint16_t *) sys_grp->rh_port;
                *(val + i) = trunk_entry.port[i];
            }
        }
    }

    /* Set in use group difference flag for system trunk id. */
    SHR_BITSET(SYS_GRP_DIFF(unit), trunk_id);

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                            "rv=%d"),
                            rh_sys_grp_data_debug_print(unit, "After update",
                            trunk_id, &trunk_entry)));
exit:
    if (trunk_entry.rh_port) {
        BCMCTH_TRUNK_FREE(trunk_entry.rh_port);
    }
    if (trunk_entry.rh_mindex_arr) {
        BCMCTH_TRUNK_FREE(trunk_entry.rh_mindex_arr);
    }
    if (trunk_entry.rh_memb_ecnt_arr) {
        BCMCTH_TRUNK_FREE(trunk_entry.rh_memb_ecnt_arr);
    }
    if (cur_entry) {
        if (cur_entry->rh_port) {
            BCMCTH_TRUNK_FREE(cur_entry->rh_port);
        }
        if (cur_entry->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(cur_entry->rh_mindex_arr);
        }
        if (cur_entry->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(cur_entry->rh_memb_ecnt_arr);
        }
        BCMCTH_TRUNK_FREE(cur_entry);
    }

    SHR_FUNC_EXIT();

}

/*!
 * \brief TRUNK_SYSTEM imm commit call back
 *
 * Discard the backup state as the current
 * transaction is getting committed.
 *
 * \param [in] unit This is device unit number.
 * \param [in] sid This is the logical table ID.
 * \param [in] trans_id is the transaction ID associated with this operation.
 * \param [in] context Is a pointer that was given during registration.
 * The callback can use this pointer to retrieve some context.
 *
 * \retval SHR_E_NONE         No errors.
 * \retval !SHR_E_NONE        Failure.
 */
static int
bcmcth_trunk_imm_sys_grp_commit(int unit,
                                bcmltd_sid_t sid,
                                uint32_t trans_id,
                                void *context)
{
    uint32_t max_group_cnt = 0;
    uint32_t size = 0;
    uint32_t trunk_id;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp_temp = NULL;

    SHR_FUNC_ENTER(unit);

    if (!SYS_GRP_HA(unit)) {
        SHR_EXIT();
    }

    if (!SYS_GRP_TEMP(unit)) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    max_group_cnt = SYS_GRP_TEMP(unit)->max_group_cnt;

    size = SHR_BITALLOCSIZE(max_group_cnt);

    for (trunk_id = 0; trunk_id < max_group_cnt; trunk_id++) {
        if (SHR_BITGET(SYS_GRP_DIFF(unit), trunk_id)) {
            sys_grp_temp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

            if (sys_grp_temp->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) {
                if (sys_grp_bk_temp_ptr->rhg[trunk_id]) {
                sal_memcpy(
                   sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)) *
                           sys_grp_temp->max_members));

                sal_memcpy(
                   sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                           sys_grp_temp->max_members));
                sal_memcpy(
                    sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                   sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                   (sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)) *
                           sys_grp_temp->cnt));
                }

            }
            /*
             * On TRUNK_SYSTEM entry delete for resilient hashing group,
             * free the sys_grp_bk_ptr->rhg[trunk_id], if the
             * sys_grp_bk_temp_ptr->rhg does not exisit.
             */
            if ((!sys_grp_bk_temp_ptr->rhg[trunk_id]) &&
                 (sys_grp_bk_ptr->rhg[trunk_id])) {
                /*
                 * Free memory allocated for storing RH load balanced group
                 * entries.
                 */
                if (sys_grp_bk_ptr->rhg[trunk_id]->rh_port) {
                    BCMCTH_TRUNK_FREE(
                         sys_grp_bk_ptr->rhg[trunk_id]->rh_port);
                }

                /*
                 * Free memory allocated for storing per RH entry
                 * mapped member's index information.
                 */
                if (sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr) {
                    BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr);
                }

                /*
                 * Free memory allocated for storing per member RH entries usage
                 * count.
                 */
                if (sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
                    BCMCTH_TRUNK_FREE(
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
                }

                BCMCTH_TRUNK_FREE(sys_grp_bk_ptr->rhg[trunk_id]);
            }

            SYS_GRP_HA(unit)->grp_ptr->sys_grp_array[trunk_id] =
            SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[trunk_id];
        }
    }
    sal_memcpy(SYS_GRP_HA(unit)->mbmp_ptr->mbmp,
               SYS_GRP_TEMP(unit)->mbmp_ptr->mbmp,
               SHR_BITALLOCSIZE(SYS_GRP_TEMP(unit)->max_member_cnt));

    sal_memset(SYS_GRP_DIFF(unit), 0, size);

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief TRUNK_SYSTEM transaction abort
 *
 * Rollback the DLB Trunk entry from backup state
 * as current transaction is getting aborted.
 *
 * \param [in] unit This is device unit number.
 * \param [in] sid This is the logical table ID.
 * \param [in] trans_id is the transaction ID associated with this operation.
 * \param [in] context Is a pointer that was given during registration.
 * The callback can use this pointer to retrieve some context.
 *
 * \retval None.
 */
static void
bcmcth_trunk_imm_sys_grp_abort(int unit,
                               bcmltd_sid_t sid,
                               uint32_t trans_id,
                               void *context)
{
    uint32_t trunk_id;
    uint32_t  max_group_cnt = 0;
    uint32_t size = 0;
    int rv = SHR_E_NONE;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp_temp = NULL;
    bcmcth_trunk_imm_sys_group_t *sys_grp_ha = NULL;

    SHR_FUNC_ENTER(unit);

    if (!SYS_GRP_HA(unit) || !SYS_GRP_TEMP(unit)) {
        return;
    }

    max_group_cnt = SYS_GRP_TEMP(unit)->max_group_cnt;
    size = SHR_BITALLOCSIZE(max_group_cnt);

    /* Iterate each trunk_id and release working copy resource. */
    for (trunk_id = 0; trunk_id < max_group_cnt; trunk_id++) {
        if (SHR_BITGET(SYS_GRP_DIFF(unit), trunk_id)) {
            if (SYS_GRP_TEMP(unit)->itbm_support == TRUE) {
                if (SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[trunk_id].inserted == TRUE) {
                    rv = shr_itbm_list_block_free(
                             SYS_GRP_TEMP(unit)->itbm_hdl,
                             SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[trunk_id].max_members,
                             SHR_ITBM_INVALID,
                             SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[trunk_id].base_ptr);
                    if (rv != SHR_E_NONE) {
                        LOG_ERROR(BSL_LOG_MODULE,
                                  (BSL_META_U(unit,
                                              "System trunk ITBM release resource error.")));
                        return;
                    }
                }
            }
        }
    }

    /* Iterate each trunk_id and restore from master copy resource. */
    for (trunk_id = 0; trunk_id < max_group_cnt; trunk_id++) {
        if (SHR_BITGET(SYS_GRP_DIFF(unit), trunk_id)) {
            SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[trunk_id] =
            SYS_GRP_HA(unit)->grp_ptr->sys_grp_array[trunk_id];

            /* Lopate temp info structure based on trunk_id */
            sys_grp_temp = SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array + trunk_id;
            /* Lopate ha info structure based on trunk_id */
            sys_grp_ha = SYS_GRP_HA(unit)->grp_ptr->sys_grp_array + trunk_id;

            if (SYS_GRP_TEMP(unit)->itbm_support == TRUE) {
                if (SYS_GRP_HA(unit)->grp_ptr->sys_grp_array[trunk_id].inserted == TRUE) {
                    rv = shr_itbm_list_block_alloc_id(
                             SYS_GRP_HA(unit)->itbm_hdl,
                             SYS_GRP_HA(unit)->grp_ptr->sys_grp_array[trunk_id].max_members,
                             SHR_ITBM_INVALID,
                             SYS_GRP_HA(unit)->grp_ptr->sys_grp_array[trunk_id].base_ptr);
                    if (rv != SHR_E_NONE) {
                        LOG_ERROR(BSL_LOG_MODULE,
                                  (BSL_META_U(unit,
                                              "System trunk ITBM rebuild resource error.")));
                        return;
                    }
                }
            }
            if ((sys_grp_temp->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) &&
                (sys_grp_ha->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)) {
                sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port)) *
                               SYS_GRP_MAX_MEMBERS(unit, trunk_id)));

                sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                               SYS_GRP_MAX_MEMBERS(unit, trunk_id)));
                sal_memcpy(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)) *
                               SYS_GRP_MEMBER_CNT(unit, trunk_id)));
            }

            if ((sys_grp_temp->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) &&
                (sys_grp_ha->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR)) {
                if (sys_grp_bk_temp_ptr->rhg[trunk_id]) {
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_temp_ptr->rhg[trunk_id]);
                }
                if (sys_grp_bk_ptr->rhg[trunk_id]) {
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_ptr->rhg[trunk_id]->rh_port);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
                    BCMCTH_TRUNK_FREE(
                          sys_grp_bk_ptr->rhg[trunk_id]);
                }
            }
            if ((sys_grp_temp->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_REGULAR) &&
                (sys_grp_ha->gtype ==
                BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT)) {
                /*
                 * Allocate the sys_grp_bk_temp_ptr->rhg[trunk_id] and
                 * recover the data from sys_grp_bk_ptr->rhg[trunk_id].
                 */
                BCMCTH_TRUNK_ALLOC(sys_grp_bk_temp_ptr->rhg[trunk_id],
                               sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id])),
                               "bcmcthTrunkSysRhGrpAddRhgInfoTemp");

                /*
                 * Allocate temp memory to store resilient TRUNK
                 * group system port entries.
                 */
                BCMCTH_TRUNK_ALLOC
                    (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                     sys_grp_ha->max_members *
                     sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port)),
                     "bcmcthTrunkSysRhGrpAddGrpRhPortArr");

                /*
                 * Allocate memory to store group resilient
                 * TRUNK_SYSTEM entries mapped member
                 * index information.
                 */
                BCMCTH_TRUNK_ALLOC
                    (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                     sys_grp_ha->max_members *
                     sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr)),
                     "bcmcthTrunkSysRhGrpAddGrpRhMindexArrTemp");
               BCMCTH_TRUNK_ALLOC
                (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                 sys_grp_ha->cnt *
                 sizeof(*(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)),
                 "bcmcthTrunkSysRhGrpAddGrpRhMembEntCntArrTemp");

                sal_memcpy(
                       sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_port,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_port)) *
                               SYS_GRP_MAX_MEMBERS(unit, trunk_id)));

                sal_memcpy(
                       sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_mindex_arr)) *
                               SYS_GRP_MAX_MEMBERS(unit, trunk_id)));
                sal_memcpy(
                       sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                       sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr,
                       (sizeof(*(sys_grp_bk_ptr->rhg[trunk_id]->rh_memb_ecnt_arr)) *
                               SYS_GRP_MEMBER_CNT(unit, trunk_id)));
            }
        }
    }

    sal_memcpy(SYS_GRP_TEMP(unit)->mbmp_ptr->mbmp,
               SYS_GRP_HA(unit)->mbmp_ptr->mbmp,
               SHR_BITALLOCSIZE(SYS_GRP_TEMP(unit)->max_member_cnt));
    sal_memset(SYS_GRP_DIFF(unit), 0, size);

    exit:
        return;
}

/*!
 * \brief TRUNK_SYSTEM LT entry delete
 *
 * \param [in] unit Unit number.
 * \param [in] trans_id Transaction ID.
 * \param [in] sid LTD Symbol ID.
 * \param [in] key List of the key fields.
 * \param [in] data List of the data fields.
 *
 * \retval SHR_E_NONE         No errors.
 * \retval !SHR_E_NONE        Failure.
 */
static int
bcmcth_trunk_imm_sys_grp_delete(int unit,
                                const bcmltd_op_arg_t *op_arg,
                                bcmltd_sid_t sid,
                                const bcmltd_field_t *key,
                                const bcmltd_field_t *data)
{
    bcmcth_trunk_sys_grp_param_t trunk_entry;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];
    bcmcth_trunk_imm_sys_group_t *sys_grp = NULL;
    int trunk_id = 0;

    SHR_FUNC_ENTER(unit);
    SHR_NULL_CHECK(key, SHR_E_PARAM);

    if (sid != TRUNK_SYSTEMt) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }
    sal_memset(&trunk_entry, 0, sizeof(trunk_entry));

    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_imm_sys_grp_entry_in_fields_parse(
                                             unit,
                                             key,
                                             &trunk_entry));
    /* Trunk group identifier. */
    trunk_id = trunk_entry.id;
    /* Read the trunk group temp info. */
    sys_grp = sys_grp_bk_temp_ptr->grp_ptr->sys_grp_array + trunk_id;

    trunk_entry.gtype = sys_grp->gtype;

    if (SYS_GRP_TEMP(unit)->itbm_support) {
        SHR_IF_ERR_EXIT(
            bcmcth_sys_trunk_itbm_delete_block(unit,
                                               SYS_GRP_TEMP(unit),
                                               &trunk_entry));
    }

    SHR_IF_ERR_VERBOSE_EXIT(
        bcmcth_trunk_drv_sys_grp_del(unit,
                                     op_arg,
                                     TRUNK_SYSTEMt,
                                     SYS_GRP_TEMP(unit),
                                     &trunk_entry));

   if ((trunk_entry.gtype == BCMCTH_TRUNK_SYSTEM_GRP_TYPE_RESILIENT) &&
        (sys_grp_bk_temp_ptr->rhg[trunk_id])) {

        /* Clear pre-config flag for this resilient TRUNK_SYSTEM group. */
        if (SYS_GRP_PRECONFIG_GET(unit, trunk_id)) {
            SYS_GRP_PRECONFIG_CLEAR(unit, trunk_id);
        }
        /*
         * Free memory allocated for storing RH load balanced group
         * entries.
         */
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_port);
        }

        /*
         * Free memory allocated for storing per RH entry mapped member's
         * index information.
         */
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_mindex_arr);
        }

        /*
         * Free memory allocated for storing per member RH entries usage
         * count.
         */
        if (sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr) {
            BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]->rh_memb_ecnt_arr);
        }

        BCMCTH_TRUNK_FREE(sys_grp_bk_temp_ptr->rhg[trunk_id]);
    }

    sal_memset(BCMCTH_TRUNK_SYS_GRP(unit, trunk_id), 0,
              sizeof(bcmcth_trunk_imm_sys_group_t));
    BCMCTH_TRUNK_SYS_GRP_INSERTED_SET(unit, trunk_id, FALSE);
    /* Set in use group difference flag for system trunk id. */
    SHR_BITSET(SYS_GRP_DIFF(unit), trunk_id);
exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief  TRUNK_SYSTEM table extended lookup function.
 *
 * \param [in]  unit            Unit number.
 * \param [in]  sid             Logical table ID.
 * \param [in]  op_arg          The operation arguments.
 * \param [in]  context         Pointer to retrieve some context.
 * \param [in]  lkup_type       Lookup type.
 * \param [in]  In              Input key fields list.
 * \param [in/out] out          Output parameter list.
 *
 * \retval SHR_E_NONE  OK
 * \retval !SHR_E_NONE ERROR
 */
static int
bcmcth_trunk_imm_sys_grp_lookup(int unit,
                                 bcmltd_sid_t sid,
                                 const bcmltd_op_arg_t *op_arg,
                                 void *context,
                                 bcmimm_lookup_type_t lkup_type,
                                 const bcmltd_fields_t *in,
                                 bcmltd_fields_t *out)
{
    bcmcth_trunk_sys_grp_param_t trunk_entry;
    int rv;

    SHR_FUNC_ENTER(unit);

    if ((op_arg->attrib & BCMLT_ENT_ATTR_GET_FROM_HW) !=
          BCMLT_ENT_ATTR_GET_FROM_HW) {
        SHR_EXIT();
    }

    if (sid != TRUNK_SYSTEMt) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }

    if (!SYS_GRP_TEMP(unit)) {
        SHR_ERR_EXIT(SHR_E_INTERNAL);
    }

    sal_memset(&trunk_entry, 0, sizeof(trunk_entry));

    if (lkup_type == BCMIMM_LOOKUP) {
        /* Parse key information for lookup operation. */
        SHR_IF_ERR_VERBOSE_EXIT(
            bcmcth_trunk_imm_sys_grp_extend_parse(unit,
                                                 in,
                                                 &trunk_entry));
    } else {
        /* Parse key information for TRAVERSE operation. */
        SHR_IF_ERR_VERBOSE_EXIT(
            bcmcth_trunk_imm_sys_grp_extend_parse(unit,
                                                  out,
                                                  &trunk_entry));
    }

    /* Look for hardware readback. */
    rv = bcmcth_trunk_drv_sys_grp_lookup(unit,
                                         op_arg,
                                         TRUNK_SYSTEMt,
                                         SYS_GRP_TEMP(unit),
                                         &trunk_entry);

    if (rv == SHR_E_NONE) {
        /*
         * Do information fill only if feature is supported with no
         * operation error.
         */
        SHR_IF_ERR_VERBOSE_EXIT(
            bcmcth_trunk_imm_sys_grp_extend_fill(unit,
                                                 sid,
                                                 &trunk_entry,
                                                 out));
    } else if (rv == SHR_E_UNAVAIL) {
        /* Skip fill as feature not supported by chip dispatcher. */
    } else {
        /* Return other errors if any. */
        SHR_ERR_EXIT(rv);
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief TRUNK_SYSTEM table change callback function for staging.
 *
 * Handle TRUNK_SYSTEM IMM table change events.
 *
 * \param [in] unit Unit number.
 * \param [in] sid This is the logical table ID.
 * \param [in] trans_id LT Transaction Id
 * \param [in] event_reason Call back reason.
 * \param [in] key This is a linked list of the key fields identifying
 * the entry.
 * \param [in] data This is a linked list of the data fields in
 * modified entry.
 * \param [in] context Is a pointer that was given during registration.
 * The callback can use this pointer to retrieve some context.
 * \param [out] output_fields This is a linked list of fields,
 * can be used by the component to add fields into the entry.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL LM fails to handle LT change events.
 */
static int
bcmcth_trunk_imm_sys_grp_stage(int unit,
                               bcmltd_sid_t sid,
                               const bcmltd_op_arg_t *op_arg,
                               bcmimm_entry_event_t event_reason,
                               const bcmltd_field_t *key,
                               const bcmltd_field_t *data,
                               void *context,
                               bcmltd_fields_t *output_fields)
{
    SHR_FUNC_ENTER(unit);

    if (output_fields) {
        output_fields->count = 0;
    }
    switch (event_reason) {
        case BCMIMM_ENTRY_INSERT:
        case BCMIMM_ENTRY_UPDATE:
            SHR_IF_ERR_VERBOSE_EXIT(bcmcth_trunk_imm_sys_grp_update(
                                                            unit,
                                                            op_arg,
                                                            sid,
                                                            key,
                                                            data,
                                                            event_reason));
            break;
        case BCMIMM_ENTRY_DELETE:
            SHR_IF_ERR_VERBOSE_EXIT(bcmcth_trunk_imm_sys_grp_delete(
                                                            unit,
                                                            op_arg,
                                                            sid,
                                                            key,
                                                            data));
            break;
        default:
            SHR_ERR_EXIT(SHR_E_PARAM);
    }

exit:
    SHR_FUNC_EXIT();
}

/*!
 * \brief TRUNK_SYSTEM In-memory event callback structure.
 *
 * This structure contains callback functions that will be corresponding
 * to TRUNK_SYSTEM logical table entry commit stages.
 */
static bcmimm_lt_cb_t bcmcth_trunk_imm_sys_grp_callback = {

    /*! Validate function. */
    .validate = bcmcth_trunk_imm_sys_grp_validate,

    /*! Staging function. */
    .op_stage    = bcmcth_trunk_imm_sys_grp_stage,

    /*! Commit function. */
    .commit   = bcmcth_trunk_imm_sys_grp_commit,

    /*! Extended lookup function. */
    .op_lookup = bcmcth_trunk_imm_sys_grp_lookup,

    /*! Abort function. */
    .abort    = bcmcth_trunk_imm_sys_grp_abort
};

/*!
 * \brief TRUNK_SYSTEM LT imm registration
 *
 *
 * \param [in] unit Unit number.
 *
 * \retval SHR_E_NONE No errors.
 * \retval SHR_E_FAIL Failed to register the imm callbacks.
 */
static int
bcmcth_trunk_imm_sys_grp_register(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_VERBOSE_EXIT
       (bcmimm_lt_event_reg(unit,
                            TRUNK_SYSTEMt,
                            &bcmcth_trunk_imm_sys_grp_callback,
                            NULL));

    SHR_EXIT();

exit:
    SHR_FUNC_EXIT();
}

/*******************************************************************************
 * Public functions
 */
int
bcmcth_trunk_imm_sys_grp_init(int unit, bool warm)
{
    uint32_t ha_alloc_size = 0, ha_req_size = 0;
    uint32_t alloc_size = 0;
    uint32_t max_group_cnt = 0;
    uint32_t ref_sign_1 = 0x68880000;
    uint32_t ref_sign_2 = 0x68880001;
    char     *ptr = NULL;
    bcmcth_trunk_imm_sys_group_ha_blk_t *grp_ptr = NULL;
    bcmcth_trunk_imm_sys_group_mbmp_ha_blk_t *mbmp_ptr = NULL;
    uint32_t size_of_grp_array= 0, size_of_grp = 0;
    uint32_t size_of_grp_mbmp= 0, size_of_mbmp = 0;
    uint32_t idx;
    int rv = SHR_E_NONE;

    SHR_FUNC_ENTER(unit);

    if (!SYS_GRP_HA(unit)) {
        alloc_size = sizeof(bcmcth_trunk_sys_grp_bk_t);
        SHR_ALLOC(SYS_GRP_HA(unit), alloc_size, "bcmcthTrunkSysGrpBk");
        SHR_NULL_CHECK(SYS_GRP_HA(unit), SHR_E_MEMORY);
        sal_memset(SYS_GRP_HA(unit), 0, alloc_size);

        SHR_ALLOC(SYS_GRP_TEMP(unit), alloc_size, "bcmcthTrunkSysGrpBkTemp");
        SHR_NULL_CHECK(SYS_GRP_TEMP(unit), SHR_E_MEMORY);
        sal_memset(SYS_GRP_TEMP(unit), 0, alloc_size);

        SHR_IF_ERR_VERBOSE_EXIT(
           bcmcth_trunk_drv_sys_grp_init(unit, SYS_GRP_TEMP(unit)));
        SYS_GRP_HA(unit)->max_member_cnt = SYS_GRP_TEMP(unit)->max_member_cnt;
        SYS_GRP_HA(unit)->max_group_cnt = SYS_GRP_TEMP(unit)->max_group_cnt;

        /* Incorporate ITBM info to master copy */
        SYS_GRP_HA(unit)->itbm_support = SYS_GRP_TEMP(unit)->itbm_support;
        SYS_GRP_HA(unit)->itbm_hdl = SYS_GRP_TEMP(unit)->itbm_hdl;

        max_group_cnt = SYS_GRP_TEMP(unit)->max_group_cnt;

        size_of_grp_array = max_group_cnt * sizeof(bcmcth_trunk_imm_sys_group_t);

        size_of_grp_mbmp = SHR_BITALLOCSIZE(
                           SYS_GRP_TEMP(unit)->max_member_cnt);
        size_of_grp = sizeof(bcmcth_trunk_imm_sys_group_ha_blk_t) +
                      size_of_grp_array;
        size_of_mbmp = sizeof(bcmcth_trunk_imm_sys_group_mbmp_ha_blk_t) +
                      size_of_grp_mbmp;
        /* HA allocation for system group. */
        ha_req_size = size_of_grp;
        ha_alloc_size = ha_req_size;
        ptr = shr_ha_mem_alloc(unit,
                               BCMMGMT_TRUNK_COMP_ID,
                               BCMCTH_TRUNK_SYSTEM_GRP_SUB_COMP_ID,
                               "bcmcthTrunkSystemGrpHaInfo",
                               &ha_alloc_size);
        SHR_IF_ERR_VERBOSE_EXIT((ha_alloc_size < ha_req_size) ?
                        SHR_E_MEMORY : SHR_E_NONE);
        SHR_NULL_CHECK(ptr, SHR_E_MEMORY);
        grp_ptr = (bcmcth_trunk_imm_sys_group_ha_blk_t *)ptr;
        SHR_NULL_CHECK(grp_ptr, SHR_E_MEMORY);

        /* HA allocation for system group member bitmap. */
        ha_req_size = size_of_mbmp;
        ha_alloc_size = ha_req_size;
        ptr = shr_ha_mem_alloc(unit,
                               BCMMGMT_TRUNK_COMP_ID,
                               BCMCTH_TRUNK_SYSTEM_MEMBER_BMP_SUB_COMP_ID,
                               "bcmcthTrunkSystemMbmpHaInfo",
                               &ha_alloc_size);
        SHR_IF_ERR_VERBOSE_EXIT((ha_alloc_size < ha_req_size) ?
                        SHR_E_MEMORY : SHR_E_NONE);
        SHR_NULL_CHECK(ptr, SHR_E_MEMORY);
        mbmp_ptr = (bcmcth_trunk_imm_sys_group_mbmp_ha_blk_t *) ptr;
        SHR_NULL_CHECK(mbmp_ptr, SHR_E_MEMORY);

        SYS_GRP_HA(unit)->grp_ptr = grp_ptr;
        SYS_GRP_HA(unit)->mbmp_ptr = mbmp_ptr;
        if (!warm) {
            sal_memset(SYS_GRP_HA(unit)->grp_ptr, 0, size_of_grp);
            SYS_GRP_HA(unit)->grp_ptr->signature = ref_sign_1;
            SYS_GRP_HA(unit)->grp_ptr->array_size = max_group_cnt;
            sal_memset(SYS_GRP_HA(unit)->grp_ptr->sys_grp_array, 0, size_of_grp_array);

            bcmissu_struct_info_report(unit, BCMMGMT_TRUNK_COMP_ID,
                                        BCMCTH_TRUNK_SYSTEM_GRP_SUB_COMP_ID, 0,
                                        size_of_grp, 1,
                                        BCMCTH_TRUNK_IMM_SYS_GROUP_HA_BLK_T_ID);

            bcmissu_struct_info_report(unit, BCMMGMT_TRUNK_COMP_ID,
                                        BCMCTH_TRUNK_SYSTEM_MEMBER_BMP_SUB_COMP_ID, 0,
                                        size_of_mbmp, 1,
                                        BCMCTH_TRUNK_IMM_SYS_GROUP_MBMP_HA_BLK_T_ID);

            sal_memset(SYS_GRP_HA(unit)->mbmp_ptr, 0, size_of_mbmp);
            SYS_GRP_HA(unit)->mbmp_ptr->array_size = max_group_cnt;
            SYS_GRP_HA(unit)->mbmp_ptr->signature = ref_sign_2;
            sal_memset(SYS_GRP_HA(unit)->mbmp_ptr->mbmp, 0, size_of_grp_mbmp);

            /*
             * Reserve entry 0 of system trunk member, as invalid
             * system trunk groups have their TRUNK_SYSTEM_GROUP table entry's
             * BASE_PTR and TG_SIZE fields set to 0.
             * The default value of entry 0 should be null,
             * so it is not set here.
             */
            SHR_BITSET(SYS_GRP_HA(unit)->mbmp_ptr->mbmp, 0);

        } else {
            SHR_IF_ERR_MSG_EXIT
            ((grp_ptr->signature != ref_sign_1
              ? SHR_E_FAIL : SHR_E_NONE),
              (BSL_META_U(unit,
              "\n\t WB system trunk group info: "
              "Signature mismatch for group info"
              "exp=0x%-8x act=0x%-8x\n"),
               ref_sign_1,
               grp_ptr->signature));
            SHR_IF_ERR_MSG_EXIT
            ((mbmp_ptr->signature != ref_sign_2
              ? SHR_E_FAIL : SHR_E_NONE),
              (BSL_META_U(unit,
               "\n\t WB system trunk group mbmp info: "
               "Signature mismatch for group mbmp info"
               "/exp=0x%-8x act=0x%-8x\n"),
               ref_sign_2,
               mbmp_ptr->signature));

        }
        LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                "\n\t WB system trunk group info: "
                "Signature=0x%-8x HA addr=0x%p\n"),
                 grp_ptr->signature,
                 (void*)grp_ptr));

        LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit,
                "\n\t WB system trunk group mbmp info: "
                "Signature=0x%-8x HA addr=0x%p\n"),
                 mbmp_ptr->signature,
                 (void*)mbmp_ptr));

        SHR_ALLOC(SYS_GRP_TEMP(unit)->grp_ptr,
                  size_of_grp,
                  "bcmcthTrunkImmSysGrpHaBlkTemp");
        SHR_ALLOC(SYS_GRP_TEMP(unit)->mbmp_ptr,
                  size_of_mbmp,
                  "bcmcthTrunkImmSysGrpMbmpHaBlkTemp");
        SHR_NULL_CHECK(SYS_GRP_TEMP(unit)->grp_ptr, SHR_E_MEMORY);
        SHR_NULL_CHECK(SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array, SHR_E_MEMORY);
        if (!warm) {
            sal_memset(SYS_GRP_TEMP(unit)->grp_ptr,
                       0,
                       size_of_grp);
            SYS_GRP_TEMP(unit)->grp_ptr->signature =
                           ref_sign_1;
            SYS_GRP_TEMP(unit)->grp_ptr->array_size =
                            max_group_cnt;
        } else {
            sal_memcpy(SYS_GRP_TEMP(unit)->grp_ptr,
                       SYS_GRP_HA(unit)->grp_ptr,
                       size_of_grp);
        }

        SHR_NULL_CHECK(SYS_GRP_TEMP(unit)->mbmp_ptr, SHR_E_MEMORY);
        if (!warm) {
            sal_memset(SYS_GRP_TEMP(unit)->mbmp_ptr, 0, size_of_mbmp);
            SYS_GRP_TEMP(unit)->mbmp_ptr->signature =
                       ref_sign_2;
            SYS_GRP_TEMP(unit)->mbmp_ptr->array_size =
                       max_group_cnt;
            SHR_BITSET(SYS_GRP_TEMP(unit)->mbmp_ptr->mbmp, 0);
        } else {
            sal_memcpy(SYS_GRP_TEMP(unit)->mbmp_ptr,
                                SYS_GRP_HA(unit)->mbmp_ptr,
                                size_of_mbmp);

            if (TRUE == SYS_GRP_TEMP(unit)->itbm_support) {
                /* Rebuild itbm database for warmboot. */
                for (idx = 0; idx < SYS_GRP_TEMP(unit)->max_group_cnt; idx++) {
                    if (SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].inserted == TRUE) {
                        /* Rebuild ITBM resource database. */
                        rv = shr_itbm_list_block_alloc_id(
                                 SYS_GRP_TEMP(unit)->itbm_hdl,
                                 SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].max_members,
                                 SHR_ITBM_INVALID,
                                 SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].base_ptr);
                        if (rv != SHR_E_NONE) {
                            LOG_ERROR(BSL_LOG_MODULE,
                                      (BSL_META_U(unit,
                                                  "System trunk warmboot ITBM error.")));
                            SHR_ERR_EXIT(rv);
                        }
                    }
                }
            }
            /* Set the preconfig flag for the resilient  groups. */
            SHR_IF_ERR_EXIT(bcmcth_trunk_sys_rh_grps_preconfig(
                               unit,
                               SYS_GRP_HA(unit)->max_group_cnt));

        }
        /* TRUNK_SYSTEM bitmap diff in one commit.*/
        alloc_size = SHR_BITALLOCSIZE(max_group_cnt);
        SHR_ALLOC(SYS_GRP_DIFF(unit), alloc_size, "bcmcthTrunkSysGrpBmpDiff");
        SHR_NULL_CHECK(SYS_GRP_DIFF(unit), SHR_E_MEMORY);
        sal_memset(SYS_GRP_DIFF(unit), 0, alloc_size);
    }

    /* IMM registration. */
    SHR_IF_ERR_VERBOSE_EXIT(bcmcth_trunk_imm_sys_grp_register(unit));

exit:
    if (SHR_FUNC_ERR()) {
        (void) bcmcth_trunk_imm_sys_grp_cleanup(unit, TRUE);
    }
    SHR_FUNC_EXIT();
}

int
bcmcth_trunk_imm_sys_grp_cleanup(int unit, bool ha_free)
{
    uint32_t idx;
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_ptr = sys_grp_bk[unit];
    bcmcth_trunk_sys_grp_bk_t *sys_grp_bk_temp_ptr = sys_grp_bk_temp[unit];

    SHR_FUNC_ENTER(unit);
    if (SYS_GRP_HA(unit) != NULL) {
        if (SYS_GRP_HA(unit)->grp_ptr != NULL && SYS_GRP_HA(unit)->mbmp_ptr) {
            /* Free resilient group variables. */
            for (idx = 0;
                 idx < sys_grp_bk_temp_ptr->max_group_cnt;
                 idx++) {

                if (idx != (uint32_t)(BCMCTH_TRUNK_INVALID)) {

                    if (sys_grp_bk_ptr->rhg[idx]) {
                        BCMCTH_TRUNK_FREE(
                                     sys_grp_bk_ptr->rhg[idx]->rh_port);
                        BCMCTH_TRUNK_FREE(
                                     sys_grp_bk_ptr->rhg[idx]->rh_mindex_arr);
                        BCMCTH_TRUNK_FREE(
                                     sys_grp_bk_ptr->rhg[idx]->rh_memb_ecnt_arr);
                        BCMCTH_TRUNK_FREE(
                                     sys_grp_bk_ptr->rhg[idx]);
                    }
                }
            }

            if (ha_free) {
                bcmissu_struct_info_clear(
                                      unit,
                                      BCMCTH_TRUNK_IMM_SYS_GROUP_HA_BLK_T_ID,
                                      BCMMGMT_TRUNK_COMP_ID,
                                      BCMCTH_TRUNK_SYSTEM_GRP_SUB_COMP_ID);
                bcmissu_struct_info_clear(
                                      unit,
                                      BCMCTH_TRUNK_IMM_SYS_GROUP_MBMP_HA_BLK_T_ID,
                                      BCMMGMT_TRUNK_COMP_ID,
                                      BCMCTH_TRUNK_SYSTEM_MEMBER_BMP_SUB_COMP_ID);
                shr_ha_mem_free(unit, SYS_GRP_HA(unit)->grp_ptr);
                shr_ha_mem_free(unit, SYS_GRP_HA(unit)->mbmp_ptr);
            }
            SHR_FREE(SYS_GRP_HA(unit));
        }
    }

    if (SYS_GRP_TEMP(unit) != NULL) {
        /* Iterate each trunk_id and release itbm resource. */
        for (idx = 0;
             idx < sys_grp_bk_temp_ptr->max_group_cnt;
             idx++) {
            if (SYS_GRP_TEMP(unit)->itbm_support == TRUE) {
                if (SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].inserted == TRUE) {
                    shr_itbm_list_block_free(
                        SYS_GRP_TEMP(unit)->itbm_hdl,
                        SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].max_members,
                        SHR_ITBM_INVALID,
                        SYS_GRP_TEMP(unit)->grp_ptr->sys_grp_array[idx].base_ptr);
                }
            }
        }

        /* Destroy ITBM handle */
        shr_itbm_list_destroy(SYS_GRP_TEMP(unit)->itbm_hdl, 0, 0);

        /* Free resilient group variables. */
        for (idx = 0;
             idx < sys_grp_bk_temp_ptr->max_group_cnt;
             idx++) {
            if (idx != (uint32_t)(BCMCTH_TRUNK_INVALID)) {

                if (sys_grp_bk_temp_ptr->rhg[idx]) {
                    BCMCTH_TRUNK_FREE(
                      sys_grp_bk_temp_ptr->rhg[idx]->rh_port);
                    BCMCTH_TRUNK_FREE(
                      sys_grp_bk_temp_ptr->rhg[idx]->rh_mindex_arr);
                    BCMCTH_TRUNK_FREE(
                      sys_grp_bk_temp_ptr->rhg[idx]->rh_memb_ecnt_arr);
                    BCMCTH_TRUNK_FREE(
                      sys_grp_bk_temp_ptr->rhg[idx]);
                }
            }
        }

        SHR_FREE(SYS_GRP_TEMP(unit)->grp_ptr);
        SHR_FREE(SYS_GRP_TEMP(unit)->mbmp_ptr);
        SYS_GRP_TEMP(unit)->grp_ptr = NULL;
        SYS_GRP_TEMP(unit)->mbmp_ptr = NULL;
    }
    SHR_FREE(SYS_GRP_TEMP(unit));
    SHR_FREE(SYS_GRP_DIFF(unit));
    SHR_FUNC_EXIT();
}
