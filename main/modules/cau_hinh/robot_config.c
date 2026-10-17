#include "robot_config.h"
#include <stddef.h>

/* Bảng cấu hình mặc định cho 3 khớp */
static const robot_cau_hinh_khop_t s_cau_hinh_khop[ROBOT_NUM_JOINTS] = {
    [JOINT_1] = {
        .joint_id = JOINT_1,
        .gpio_step = GPIO_J1_STEP,
        .gpio_dir = GPIO_J1_DIR,
        .gpio_ena = GPIO_J1_ENA,
        .gpio_home = GPIO_J1_HOME,
        .xung_moi_do = XUNG_MOI_DO_LY_THUYET,
        .goc_home_offset = 0.0f,    /* TODO: Cần đo đạc góc thực tế khi chạm switch */
        .gioi_han_goc_min = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình âm */
        .gioi_han_goc_max = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình dương */
        .da_hieu_chuan = false
    },
    [JOINT_2] = {
        .joint_id = JOINT_2,
        .gpio_step = GPIO_J2_STEP,
        .gpio_dir = GPIO_J2_DIR,
        .gpio_ena = GPIO_J2_ENA,
        .gpio_home = GPIO_J2_HOME,
        .xung_moi_do = XUNG_MOI_DO_LY_THUYET,
        .goc_home_offset = 0.0f,    /* TODO: Cần đo đạc góc thực tế khi chạm switch */
        .gioi_han_goc_min = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình âm */
        .gioi_han_goc_max = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình dương */
        .da_hieu_chuan = false
    },
    [JOINT_3] = {
        .joint_id = JOINT_3,
        .gpio_step = GPIO_J3_STEP,
        .gpio_dir = GPIO_J3_DIR,
        .gpio_ena = GPIO_J3_ENA,
        .gpio_home = GPIO_J3_HOME,
        .xung_moi_do = XUNG_MOI_DO_LY_THUYET,
        .goc_home_offset = 0.0f,    /* TODO: Cần đo đạc góc thực tế khi chạm switch */
        .gioi_han_goc_min = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình âm */
        .gioi_han_goc_max = 0.0f,   /* TODO: Cần đo đạc giới hạn hành trình dương */
        .da_hieu_chuan = false
    }
};

robot_err_t robot_config_init(void)
{
    /* Khởi tạo cấu hình - ở Stage 1 chưa cấu hình phần cứng */
    return ROBOT_OK;
}

bool robot_config_da_hieu_chuan(void)
{
    return ROBOT_CALIBRATION_COMPLETE;
}

const robot_cau_hinh_khop_t* robot_config_lay_khop(robot_joint_id_t joint)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return NULL;
    }
    return &s_cau_hinh_khop[joint];
}
