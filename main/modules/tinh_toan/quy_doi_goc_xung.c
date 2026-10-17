#include "quy_doi_goc_xung.h"
#include "robot_config.h"
#include <math.h>

robot_err_t quy_doi_goc_sang_xung(robot_joint_id_t joint, float goc_deg, int32_t *out_xung)
{
    if (joint >= ROBOT_NUM_JOINTS || out_xung == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }
    if (isnan(goc_deg) || isinf(goc_deg)) {
        return ROBOT_ERR_INVALID_ARG;
    }

    const robot_cau_hinh_khop_t *cfg = robot_config_lay_khop(joint);
    if (cfg == NULL || cfg->xung_moi_do <= 0.0f) {
        return ROBOT_ERR_GENERAL;
    }

    /* Tính số xung: xung = round(goc * xung_moi_do) */
    double xung_f = (double)goc_deg * (double)cfg->xung_moi_do;
    if (xung_f > 2147483647.0 || xung_f < -2147483648.0) {
        return ROBOT_ERR_LIMIT_EXCEEDED;
    }

    *out_xung = (int32_t)lround(xung_f);
    return ROBOT_OK;
}

robot_err_t quy_doi_xung_sang_goc(robot_joint_id_t joint, int32_t xung, float *out_goc_deg)
{
    if (joint >= ROBOT_NUM_JOINTS || out_goc_deg == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }

    const robot_cau_hinh_khop_t *cfg = robot_config_lay_khop(joint);
    if (cfg == NULL || cfg->xung_moi_do <= 0.0f) {
        return ROBOT_ERR_GENERAL;
    }

    *out_goc_deg = (float)((double)xung / (double)cfg->xung_moi_do);
    return ROBOT_OK;
}

robot_err_t quy_doi_bo_goc_sang_xung(const robot_goc_khop_t *goc_khop, robot_xung_khop_t *out_xung_khop)
{
    if (goc_khop == NULL || out_xung_khop == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }
    if (!goc_khop->hop_le) {
        out_xung_khop->hop_le = false;
        return ROBOT_ERR_POSITION_INVALID;
    }

    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        robot_err_t err = quy_doi_goc_sang_xung((robot_joint_id_t)i, goc_khop->goc[i], &out_xung_khop->xung[i]);
        if (err != ROBOT_OK) {
            out_xung_khop->hop_le = false;
            return err;
        }
    }

    out_xung_khop->hop_le = true;
    return ROBOT_OK;
}

robot_err_t quy_doi_bo_xung_sang_goc(const robot_xung_khop_t *xung_khop, robot_goc_khop_t *out_goc_khop)
{
    if (xung_khop == NULL || out_goc_khop == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }
    if (!xung_khop->hop_le) {
        out_goc_khop->hop_le = false;
        return ROBOT_ERR_POSITION_INVALID;
    }

    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        robot_err_t err = quy_doi_xung_sang_goc((robot_joint_id_t)i, xung_khop->xung[i], &out_goc_khop->goc[i]);
        if (err != ROBOT_OK) {
            out_goc_khop->hop_le = false;
            return err;
        }
    }

    out_goc_khop->hop_le = true;
    return ROBOT_OK;
}
