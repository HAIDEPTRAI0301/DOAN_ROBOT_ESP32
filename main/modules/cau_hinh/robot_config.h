#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================
 * CẤU HÌNH GPIO THEO ĐẶC TẢ PHẦN CỨNG ĐÃ THỐNG NHẤT
 * Tuyệt đối không tự ý thay đổi số chân GPIO.
 * ==================================================================== */

/* Khớp J1 (Đế - Trục quay) */
#define GPIO_J1_STEP        15
#define GPIO_J1_DIR         14
#define GPIO_J1_ENA         13  /* ENA luôn đấu cho phép trên phần cứng, firmware không can thiệp */
#define GPIO_J1_HOME        21

/* Khớp J2 (Vai - Trục nâng/hạ) */
#define GPIO_J2_STEP        5
#define GPIO_J2_DIR         6
#define GPIO_J2_ENA         7
#define GPIO_J2_HOME        20

/* Khớp J3 (Khuỷu - Trục gập/duỗi) */
#define GPIO_J3_STEP        16
#define GPIO_J3_DIR         18
#define GPIO_J3_ENA         17
#define GPIO_J3_HOME        19

/* ====================================================================
 * THỜI GIAN VÀ CỜ AN TOÀN
 * ==================================================================== */

/**
 * @brief Thời gian chờ an toàn sau khi boot (mili-giây)
 */
#define ROBOT_THOI_GIAN_CHO_BOOT_MS     5000

/**
 * @brief Cờ xác nhận hoàn thành hiệu chuẩn toàn bộ hệ thống.
 * MẶC ĐỊNH LÀ FALSE để khóa chế độ AUTO. Chỉ được bật sau khi người dùng
 * hoàn thành đo đạc góc Home, giới hạn hành trình và vị trí gắp/thả.
 */
#define ROBOT_CALIBRATION_COMPLETE      false

/* ====================================================================
 * THÔNG SỐ ĐỘNG CƠ VÀ TRUYỀN ĐỘNG SƠ BỘ
 * ==================================================================== */
#define DONG_CO_BUOC_GOC_DEG            1.8f    /* 200 bước/vòng */
#define TB6600_VI_BUOC                  8       /* Vi bước 1/8 (DIP: OFF-ON-OFF) */
#define TY_SO_TRUYEN_PULY               4.5f    /* 90 răng / 20 răng = 4.5:1 */

/* Số xung lý thuyết trên mỗi độ quay trục đầu ra: (200 * 8 * 4.5) / 360 = 20.0 */
#define XUNG_MOI_DO_LY_THUYET           20.0f

/**
 * @brief Cấu trúc cấu hình phần cứng cho một khớp
 */
typedef struct {
    robot_joint_id_t joint_id;
    int gpio_step;
    int gpio_dir;
    int gpio_ena;
    int gpio_home;
    float xung_moi_do;      /**< Tỷ lệ xung/độ sau hiệu chuẩn */
    float goc_home_offset;  /**< Góc mốc cơ khí tại công tắc Home (độ) - TODO: Xác minh khi hiệu chuẩn */
    float gioi_han_goc_min; /**< Giới hạn góc cơ khí nhỏ nhất (độ) - TODO: Đo đạc thực tế */
    float gioi_han_goc_max; /**< Giới hạn góc cơ khí lớn nhất (độ) - TODO: Đo đạc thực tế */
    bool da_hieu_chuan;     /**< Khớp này đã được hiệu chuẩn đo đạc chưa */
} robot_cau_hinh_khop_t;

/**
 * @brief Khởi tạo module cấu hình robot
 * @return ROBOT_OK nếu thành công
 */
robot_err_t robot_config_init(void);

/**
 * @brief Kiểm tra xem toàn bộ robot đã hoàn tất hiệu chuẩn hay chưa
 * @return true nếu đã hiệu chuẩn, false nếu đang ở chế độ Commissioning khóa
 */
bool robot_config_da_hieu_chuan(void);

/**
 * @brief Lấy cấu hình của một khớp cụ thể
 * @param joint Khớp cần lấy cấu hình
 * @return Con trỏ tới cấu trúc cấu hình khớp, NULL nếu joint không hợp lệ
 */
const robot_cau_hinh_khop_t* robot_config_lay_khop(robot_joint_id_t joint);

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_CONFIG_H */
