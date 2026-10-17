#include "dong_bo_ba_truc.h"
#include <stdlib.h>
#include <string.h>

robot_err_t dong_bo_ba_truc_lap_ke_hoach(const int32_t delta_xung[ROBOT_NUM_JOINTS],
                                         const profile_toc_do_cfg_t *cfg,
                                         dong_bo_ba_truc_ke_hoach_t *out_ke_hoach)
{
    if (delta_xung == NULL || cfg == NULL || out_ke_hoach == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }

    memset(out_ke_hoach, 0, sizeof(dong_bo_ba_truc_ke_hoach_t));

    uint32_t max_xung = 0;
    robot_joint_id_t truc_max = JOINT_1;

    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        out_ke_hoach->delta_xung[i] = delta_xung[i];
        if (delta_xung[i] >= 0) {
            out_ke_hoach->chieu[i] = DIR_DUONG;
            out_ke_hoach->so_xung_tuyet_doi[i] = (uint32_t)delta_xung[i];
        } else {
            out_ke_hoach->chieu[i] = DIR_AM;
            out_ke_hoach->so_xung_tuyet_doi[i] = (uint32_t)(-delta_xung[i]);
        }

        if (out_ke_hoach->so_xung_tuyet_doi[i] > max_xung) {
            max_xung = out_ke_hoach->so_xung_tuyet_doi[i];
            truc_max = (robot_joint_id_t)i;
        }
    }

    out_ke_hoach->truc_chinh = truc_max;

    if (max_xung == 0) {
        /* Không có trục nào cần di chuyển */
        out_ke_hoach->hop_le = true;
        return ROBOT_OK;
    }

    /* Tính toán profile tốc độ cho trục có số xung lớn nhất */
    robot_err_t err = profile_toc_do_tinh_toan(max_xung, cfg, &out_ke_hoach->profile_truc_chinh);
    if (err != ROBOT_OK) {
        out_ke_hoach->hop_le = false;
        return err;
    }

    out_ke_hoach->hop_le = true;
    return ROBOT_OK;
}
