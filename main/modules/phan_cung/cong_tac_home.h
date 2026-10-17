#ifndef CONG_TAC_HOME_H
#define CONG_TAC_HOME_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo các chân GPIO cho 3 công tắc Home (J1, J2, J3)
 * @return ROBOT_OK nếu thành công
 */
robot_err_t cong_tac_home_init(void);

/**
 * @brief Đọc trạng thái thô (chưa qua lọc nhiễu) từ chân GPIO
 * @param joint Khớp cần đọc công tắc Home
 * @return CONG_TAC_NHAN (LOW), CONG_TAC_NHA (HIGH) hoặc CONG_TAC_KHONG_XAC_DINH
 */
trang_thai_cong_tac_t cong_tac_home_doc_raw(robot_joint_id_t joint);

/**
 * @brief Đọc trạng thái đã qua bộ lọc chống rung (debounce)
 * @param joint Khớp cần đọc
 * @return Trạng thái ổn định đã lọc
 */
trang_thai_cong_tac_t cong_tac_home_doc_loc(robot_joint_id_t joint);

/**
 * @brief Cập nhật định kỳ máy trạng thái lọc nhiễu cho 3 công tắc (gọi từ timer hoặc task)
 */
void cong_tac_home_cap_nhat(void);

#ifdef __cplusplus
}
#endif

#endif /* CONG_TAC_HOME_H */
