#ifndef LENH_SERIAL_H
#define LENH_SERIAL_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo giao tiếp Serial nhận lệnh từ người vận hành
 * @return ROBOT_OK
 */
robot_err_t lenh_serial_init(void);

/**
 * @brief Đọc và xử lý chuỗi lệnh từ Serial Monitor (non-blocking)
 */
void lenh_serial_xu_ly(void);

/**
 * @brief In thông tin trạng thái hệ thống ra Serial
 */
void lenh_serial_in_trang_thai(void);

/**
 * @brief In danh sách câu lệnh trợ giúp ra Serial
 */
void lenh_serial_in_tro_giup(void);

#ifdef __cplusplus
}
#endif

#endif /* LENH_SERIAL_H */
