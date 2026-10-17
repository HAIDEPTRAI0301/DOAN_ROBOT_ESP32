#ifndef BO_PHAT_XUNG_H
#define BO_PHAT_XUNG_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo hệ thống phát xung thời gian thực (RMT hoặc GPTimer của ESP-IDF 6.1)
 * @return ROBOT_OK nếu thành công
 */
robot_err_t bo_phat_xung_init(void);

/**
 * @brief Phát số lượng xung xác định cho một trục ở tần số cố định (chế độ kiểm thử đơn trục)
 * @param joint Khớp cần phát xung
 * @param so_xung Tổng số xung cần phát
 * @param tan_so_hz Tần số phát xung (Hz)
 * @return ROBOT_OK nếu yêu cầu được tiếp nhận
 */
robot_err_t bo_phat_xung_chay_xung_don(robot_joint_id_t joint, uint32_t so_xung, uint32_t tan_so_hz);

/**
 * @brief Dừng phát xung ngay lập tức trên trục
 * @param joint Khớp cần dừng
 * @return ROBOT_OK nếu thành công
 */
robot_err_t bo_phat_xung_dung(robot_joint_id_t joint);

/**
 * @brief Dừng phát xung khẩn cấp trên toàn bộ các trục
 * @return ROBOT_OK
 */
robot_err_t bo_phat_xung_dung_toan_bo(void);

/**
 * @brief Kiểm tra xem trục có đang trong quá trình phát chuỗi xung hay không
 * @param joint Khớp cần kiểm tra
 * @return true nếu đang bận phát xung
 */
bool bo_phat_xung_dang_ban(robot_joint_id_t joint);

#ifdef __cplusplus
}
#endif

#endif /* BO_PHAT_XUNG_H */
