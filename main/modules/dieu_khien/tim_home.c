#include "tim_home.h"
#include "robot_config.h"
#include "truc_buoc.h"
#include "cong_tac_home.h"
#include "bo_phat_xung.h"

/* Thứ tự Homing tuần tự đã chốt: J2 (vai) -> J3 (khuỷu) -> J1 (đế) */
static const robot_joint_id_t s_thu_tu_home[ROBOT_NUM_JOINTS] = {
    JOINT_2,
    JOINT_3,
    JOINT_1
};

static uint8_t s_buoc_truc_hien_tai = 0;
static tim_home_trang_thai_t s_trang_thai = TIM_HOME_TRANG_THAI_IDLE;
static bool s_truc_da_home[ROBOT_NUM_JOINTS] = {false, false, false};

robot_err_t tim_home_init(void)
{
    s_buoc_truc_hien_tai = 0;
    s_trang_thai = TIM_HOME_TRANG_THAI_IDLE;
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        s_truc_da_home[i] = false;
    }
    return ROBOT_OK;
}

robot_err_t tim_home_bat_dau(void)
{
    /* Kiểm tra cờ an toàn: Không cho Homing nếu chưa qua bước kiểm tra an toàn */
    s_buoc_truc_hien_tai = 0;
    s_trang_thai = TIM_HOME_TRANG_THAI_KIEM_TRA_SWITCH_BAN_DAU;

    /* TODO: Giai đoạn Stage 4 (từng trục) và Stage 5 (tuần tự 3 trục) sẽ thực thi */
    return ROBOT_OK;
}

robot_err_t tim_home_xu_ly(void)
{
    if (s_trang_thai == TIM_HOME_TRANG_THAI_IDLE || s_trang_thai == TIM_HOME_TRANG_THAI_HOAN_THANH_TOAN_BO) {
        return ROBOT_OK;
    }

    (void)s_buoc_truc_hien_tai;

    /* TODO: Giai đoạn Stage 4/5:
     * - Kiểm tra trạng thái switch ban đầu (nếu đã bị nhấn: dừng và khóa lỗi, không tự đoán chiều lùi).
     * - Phát xung tìm switch ở tốc độ vừa phải.
     * - Khi chạm: dừng, lùi ra đến khi nhả.
     * - Tiếp cận lại tốc độ chậm, gán mốc số xung và đánh dấu trục đã home.
     * - Chuyển sang trục tiếp theo theo thứ tự J2 -> J3 -> J1.
     */

    return ROBOT_OK;
}

bool tim_home_da_hoan_thanh(void)
{
    return (s_truc_da_home[JOINT_1] && s_truc_da_home[JOINT_2] && s_truc_da_home[JOINT_3]);
}

bool tim_home_truc_da_home(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return false;
    }
    return s_truc_da_home[joint];
}

robot_joint_id_t tim_home_lay_thu_tu_truc(uint8_t buoc)
{
    if (buoc >= ROBOT_NUM_JOINTS) {
        return JOINT_1;
    }
    return s_thu_tu_home[buoc];
}

tim_home_trang_thai_t tim_home_lay_trang_thai(void)
{
    return s_trang_thai;
}
