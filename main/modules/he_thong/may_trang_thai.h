#ifndef MAY_TRANG_THAI_H
#define MAY_TRANG_THAI_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo máy trạng thái toàn cục
 * @return ROBOT_OK
 */
robot_err_t may_trang_thai_init(void);

/**
 * @brief Lấy trạng thái hoạt động hiện tại của hệ thống
 * @return Trạng thái robot_trang_thai_t
 */
robot_trang_thai_t may_trang_thai_hien_tai(void);

/**
 * @brief Yêu cầu chuyển sang trạng thái mới (có kiểm tra tính hợp lệ của bước chuyển)
 * @param state_moi Trạng thái đích
 * @return ROBOT_OK nếu chuyển thành công, ROBOT_ERR_INVALID_STATE nếu bước chuyển không hợp lệ
 */
robot_err_t may_trang_thai_chuyen(robot_trang_thai_t state_moi);

/**
 * @brief Lấy chuỗi mô tả của trạng thái để in log
 * @param state Trạng thái cần lấy tên
 * @return Chuỗi ký tự hằng
 */
const char* may_trang_thai_chuoi(robot_trang_thai_t state);

#ifdef __cplusplus
}
#endif

#endif /* MAY_TRANG_THAI_H */
