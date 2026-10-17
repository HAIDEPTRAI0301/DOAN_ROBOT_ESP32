#include "dieu_khien_vi_tri.h"
#include "truc_buoc.h"
#include "quy_doi_goc_xung.h"
#include "dong_bo_ba_truc.h"
#include "tim_home.h"
#include "bo_phat_xung.h"
#include <string.h>

static bool s_dang_chuyen_dong = false;

robot_err_t dieu_khien_vi_tri_init(void)
{
    s_dang_chuyen_dong = false;
    return ROBOT_OK;
}

robot_err_t dieu_khien_vi_tri_jog(robot_joint_id_t joint, float delta_deg)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return ROBOT_ERR_INVALID_ARG;
    }

    if (!truc_buoc_vi_tri_hop_le(joint)) {
        return ROBOT_ERR_NOT_HOMED;
    }

    if (s_dang_chuyen_dong) {
        return ROBOT_ERR_BUSY;
    }

    /* TODO: Giai đoạn Stage 7 sẽ kiểm tra soft limit, tính profile và phát xung JOG */
    return ROBOT_OK;
}

robot_err_t dieu_khien_vi_tri_move(const robot_goc_khop_t *target_angles)
{
    if (target_angles == NULL || !target_angles->hop_le) {
        return ROBOT_ERR_INVALID_ARG;
    }

    if (!tim_home_da_hoan_thanh()) {
        return ROBOT_ERR_NOT_HOMED;
    }

    if (s_dang_chuyen_dong) {
        return ROBOT_ERR_BUSY;
    }

    /* TODO: Giai đoạn Stage 7 sẽ tính delta xung 3 trục, lập kế hoạch đồng bộ và thực thi */
    return ROBOT_OK;
}

robot_err_t dieu_khien_vi_tri_dung_khan(void)
{
    s_dang_chuyen_dong = false;
    bo_phat_xung_dung_toan_bo();

    /* Đánh dấu vị trí mất tin cậy để buộc phải Home lại */
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        truc_buoc_danh_dau_vi_tri_khong_hop_le((robot_joint_id_t)i);
    }
    return ROBOT_OK;
}

robot_err_t dieu_khien_vi_tri_doc_goc_hien_tai(robot_goc_khop_t *out_angles)
{
    if (out_angles == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }

    robot_xung_khop_t xung_khop;
    bool tat_ca_hop_le = true;

    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        if (!truc_buoc_vi_tri_hop_le((robot_joint_id_t)i)) {
            tat_ca_hop_le = false;
        }
        xung_khop.xung[i] = truc_buoc_doc_vi_tri_xung((robot_joint_id_t)i);
    }
    xung_khop.hop_le = tat_ca_hop_le;

    if (!tat_ca_hop_le) {
        out_angles->hop_le = false;
        return ROBOT_ERR_POSITION_INVALID;
    }

    return quy_doi_bo_xung_sang_goc(&xung_khop, out_angles);
}

bool dieu_khien_vi_tri_dang_chuyen_dong(void)
{
    return s_dang_chuyen_dong;
}
