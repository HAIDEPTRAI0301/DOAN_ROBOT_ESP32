#ifndef TIM_HOME_H
#define TIM_HOME_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Trạng thái chi tiết trong chu trình Homing từng trục
 */
typedef enum {
    TIM_HOME_TRANG_THAI_IDLE = 0,
    TIM_HOME_TRANG_THAI_KIEM_TRA_SWITCH_BAN_DAU, /**< Kiểm tra switch trước khi chạy */
    TIM_HOME_TRANG_THAI_TIEP_CAN_NHANH,          /**< Giai đoạn 1: Chạy tìm switch */
    TIM_HOME_TRANG_THAI_LUI_RA,                  /**< Lùi ra giải phóng tiếp điểm */
    TIM_HOME_TRANG_THAI_TIEP_CAN_CHAM,           /**< Giai đoạn 2: Chạm lại switch tốc độ chậm */
    TIM_HOME_TRANG_THAI_HOAN_THANH_TRUC,         /**< Đã xong 1 trục, chốt mốc vị trí */
    TIM_HOME_TRANG_THAI_HOAN_THANH_TOAN_BO,      /**< Đã xong toàn bộ J2 -> J3 -> J1 */
    TIM_HOME_TRANG_THAI_LOI                      /**< Lỗi (timeout, kẹt switch, v.v.) */
} tim_home_trang_thai_t;

/**
 * @brief Khởi tạo module tìm Home
 * @return ROBOT_OK
 */
robot_err_t tim_home_init(void);

/**
 * @brief Bắt đầu chu trình Homing tự động theo thứ tự tuần tự J2 -> J3 -> J1
 * @return ROBOT_OK nếu bắt đầu thành công
 */
robot_err_t tim_home_bat_dau(void);

/**
 * @brief Hàm xử lý định kỳ máy trạng thái Homing (gọi trong vòng lặp chính / task)
 * @return ROBOT_OK nếu đang chạy bình thường, mã lỗi nếu xảy ra sự cố
 */
robot_err_t tim_home_xu_ly(void);

/**
 * @brief Kiểm tra xem toàn bộ 3 trục đã hoàn tất Homing chưa
 * @return true nếu cả J1, J2, J3 đã được Home hợp lệ
 */
bool tim_home_da_hoan_thanh(void);

/**
 * @brief Kiểm tra một trục cụ thể đã được Home chưa
 * @param joint Khớp cần kiểm tra
 * @return true nếu trục đã hoàn thành Home
 */
bool tim_home_truc_da_home(robot_joint_id_t joint);

/**
 * @brief Lấy khớp tương ứng theo thứ tự homing tuần tự (0: J2, 1: J3, 2: J1)
 * @param buoc Thứ tự bước (0 đến ROBOT_NUM_JOINTS - 1)
 * @return Khớp tương ứng
 */
robot_joint_id_t tim_home_lay_thu_tu_truc(uint8_t buoc);

/**
 * @brief Lấy trạng thái hiện tại của tiến trình Homing
 * @return Trạng thái tim_home_trang_thai_t
 */
tim_home_trang_thai_t tim_home_lay_trang_thai(void);

#ifdef __cplusplus
}
#endif

#endif /* TIM_HOME_H */
