#include "trinh_dieu_khien_robot.h"
#include "robot_config.h"
#include "robot_positions.h"
#include "truc_buoc.h"
#include "cong_tac_home.h"
#include "bo_phat_xung.h"
#include "tim_home.h"
#include "dieu_khien_vi_tri.h"
#include "may_trang_thai.h"
#include "quan_ly_loi.h"
#include "kiem_tra_an_toan.h"
#include "lenh_serial.h"
#include <stdio.h>

robot_err_t trinh_dieu_khien_robot_init(void)
{
    printf("\n======================================================\n");
    printf("   ROBOT 3-DOF POSITION CONTROLLER (ESP32-S3 A)\n");
    printf("   Firmware: Baseline Stage 1 Framework\n");
    printf("======================================================\n");

    /* 1. Khởi tạo quản lý lỗi và máy trạng thái */
    quan_ly_loi_init();
    may_trang_thai_init();

    /* 2. Khởi tạo cấu hình và vị trí */
    robot_config_init();
    robot_positions_init();

    /* 3. Khởi tạo phần cứng trừu tượng */
    for (int i = 0; i < ROBOT_NUM_JOINTS; i++) {
        truc_buoc_init((robot_joint_id_t)i);
    }
    cong_tac_home_init();
    bo_phat_xung_init();

    /* 4. Khởi tạo các bộ điều khiển */
    tim_home_init();
    dieu_khien_vi_tri_init();

    /* 5. Khởi tạo liên khóa an toàn và giao tiếp Serial */
    kiem_tra_an_toan_init();
    lenh_serial_init();

    /* Chuyển sang trạng thái chờ 5 giây khởi động */
    may_trang_thai_chuyen(ROBOT_TRANG_THAI_CHO_KHOI_DONG);
    printf("[ROBOT] Trang thai hien tai: %s\n", may_trang_thai_chuoi(may_trang_thai_hien_tai()));

    return ROBOT_OK;
}

void trinh_dieu_khien_robot_vong_lap(void)
{
    /* Cập nhật lọc rung công tắc Home */
    cong_tac_home_cap_nhat();

    /* Xử lý nhận lệnh qua Serial */
    lenh_serial_xu_ly();

    /* Xử lý máy trạng thái Homing nếu đang chạy */
    if (may_trang_thai_hien_tai() == ROBOT_TRANG_THAI_TIM_HOME) {
        tim_home_xu_ly();
    }
}
