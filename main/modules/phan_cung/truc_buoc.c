#include "truc_buoc.h"
#include "robot_config.h"

typedef struct {
    int32_t vi_tri_xung;
    chieu_quay_t chieu_hien_tai;
    bool vi_tri_hop_le;
    bool da_khoi_tao;
} truc_buoc_trang_thai_t;

static truc_buoc_trang_thai_t s_trang_thai_truc[ROBOT_NUM_JOINTS] = {0};

robot_err_t truc_buoc_init(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return ROBOT_ERR_INVALID_ARG;
    }

    s_trang_thai_truc[joint].vi_tri_xung = 0;
    s_trang_thai_truc[joint].chieu_hien_tai = DIR_DUONG;
    s_trang_thai_truc[joint].vi_tri_hop_le = false; /* Chưa Homing -> vị trí chưa hợp lệ */
    s_trang_thai_truc[joint].da_khoi_tao = true;

    /* TODO: Giai đoạn Stage 3 sẽ cấu hình GPIO DIR/STEP và kiểm tra tương thích mức 3.3V */

    return ROBOT_OK;
}

robot_err_t truc_buoc_dat_chieu(robot_joint_id_t joint, chieu_quay_t chieu)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return ROBOT_ERR_INVALID_ARG;
    }
    s_trang_thai_truc[joint].chieu_hien_tai = chieu;

    /* TODO: Giai đoạn Stage 3 sẽ điều khiển mức logic GPIO DIR thực tế sau khi bench-test */
    return ROBOT_OK;
}

int32_t truc_buoc_doc_vi_tri_xung(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return 0;
    }
    return s_trang_thai_truc[joint].vi_tri_xung;
}

void truc_buoc_dat_vi_tri_xung(robot_joint_id_t joint, int32_t xung)
{
    if (joint < ROBOT_NUM_JOINTS) {
        s_trang_thai_truc[joint].vi_tri_xung = xung;
        s_trang_thai_truc[joint].vi_tri_hop_le = true;
    }
}

bool truc_buoc_vi_tri_hop_le(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return false;
    }
    return s_trang_thai_truc[joint].vi_tri_hop_le;
}

void truc_buoc_danh_dau_vi_tri_khong_hop_le(robot_joint_id_t joint)
{
    if (joint < ROBOT_NUM_JOINTS) {
        s_trang_thai_truc[joint].vi_tri_hop_le = false;
    }
}
