#ifndef TRINH_DIEU_KHIEN_ROBOT_H
#define TRINH_DIEU_KHIEN_ROBOT_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo toàn bộ các module trong hệ thống điều khiển robot
 * @return ROBOT_OK nếu toàn bộ khởi tạo thành công
 */
robot_err_t trinh_dieu_khien_robot_init(void);

/**
 * @brief Vòng lặp điều phối chính của ứng dụng robot (chạy trong task FreeRTOS)
 */
void trinh_dieu_khien_robot_vong_lap(void);

#ifdef __cplusplus
}
#endif

#endif /* TRINH_DIEU_KHIEN_ROBOT_H */
