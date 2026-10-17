#include "cong_tac_home.h"
#include "robot_config.h"

static trang_thai_cong_tac_t s_trang_thai_raw[ROBOT_NUM_JOINTS] = {
    CONG_TAC_KHONG_XAC_DINH, CONG_TAC_KHONG_XAC_DINH, CONG_TAC_KHONG_XAC_DINH
};

static trang_thai_cong_tac_t s_trang_thai_loc[ROBOT_NUM_JOINTS] = {
    CONG_TAC_KHONG_XAC_DINH, CONG_TAC_KHONG_XAC_DINH, CONG_TAC_KHONG_XAC_DINH
};

robot_err_t cong_tac_home_init(void)
{
    /* TODO: Giai đoạn Stage 2 sẽ cấu hình GPIO input có pull-up nội cho GPIO 21, 20, 19 */
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        s_trang_thai_raw[i] = CONG_TAC_KHONG_XAC_DINH;
        s_trang_thai_loc[i] = CONG_TAC_KHONG_XAC_DINH;
    }
    return ROBOT_OK;
}

trang_thai_cong_tac_t cong_tac_home_doc_raw(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return CONG_TAC_KHONG_XAC_DINH;
    }
    /* TODO: Giai đoạn Stage 2 sẽ gọi gpio_get_level() */
    return s_trang_thai_raw[joint];
}

trang_thai_cong_tac_t cong_tac_home_doc_loc(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return CONG_TAC_KHONG_XAC_DINH;
    }
    return s_trang_thai_loc[joint];
}

void cong_tac_home_cap_nhat(void)
{
    /* TODO: Giai đoạn Stage 2 sẽ thực hiện thuật toán lọc rung tiếp điểm debounce 10-20ms */
}
