#include "bo_phat_xung.h"
#include "robot_config.h"

static bool s_dang_phat_xung[ROBOT_NUM_JOINTS] = {false, false, false};

robot_err_t bo_phat_xung_init(void)
{
    /* TODO: Giai đoạn Stage 3 sẽ khởi tạo driver phần cứng RMT hoặc GPTimer theo ESP-IDF 6.1 */
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        s_dang_phat_xung[i] = false;
    }
    return ROBOT_OK;
}

robot_err_t bo_phat_xung_chay_xung_don(robot_joint_id_t joint, uint32_t so_xung, uint32_t tan_so_hz)
{
    if (joint >= ROBOT_NUM_JOINTS || so_xung == 0 || tan_so_hz == 0) {
        return ROBOT_ERR_INVALID_ARG;
    }

    /* Ở Stage 1 chưa cho phép phát xung thực tế ra phần cứng */
    /* TODO: Giai đoạn Stage 3 sẽ triển khai phát xung đơn trục có kiểm soát */
    return ROBOT_OK;
}

robot_err_t bo_phat_xung_dung(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return ROBOT_ERR_INVALID_ARG;
    }
    s_dang_phat_xung[joint] = false;
    /* TODO: Ngắt xung phần cứng */
    return ROBOT_OK;
}

robot_err_t bo_phat_xung_dung_toan_bo(void)
{
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        s_dang_phat_xung[i] = false;
    }
    return ROBOT_OK;
}

bool bo_phat_xung_dang_ban(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return false;
    }
    return s_dang_phat_xung[joint];
}
