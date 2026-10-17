#ifndef ROBOT_POSITIONS_H
#define ROBOT_POSITIONS_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SO_VI_TRI_THA_TOI_DA    4

/**
 * @brief Cấu trúc điểm vị trí làm việc của cánh tay robot
 */
typedef struct {
    robot_goc_khop_t goc_khop;  /**< Bộ 3 góc [J1, J2, J3] */
    bool da_xac_minh;           /**< Cờ đánh dấu vị trí này đã được đo đạc và duyệt */
} robot_diem_vi_tri_t;

/**
 * @brief Khởi tạo module lưu trữ vị trí
 * @return ROBOT_OK
 */
robot_err_t robot_positions_init(void);

/**
 * @brief Lấy tọa độ góc điểm gắp (PICK) cố định
 * @param out_pos Con trỏ nhận dữ liệu vị trí gắp
 * @return ROBOT_OK nếu hợp lệ, ROBOT_ERR_INVALID_ARG nếu out_pos NULL, ROBOT_ERR_POSITION_INVALID nếu chưa đo
 */
robot_err_t robot_positions_lay_diem_gap(robot_diem_vi_tri_t *out_pos);

/**
 * @brief Lấy tọa độ góc điểm thả (PLACE) theo chỉ số phân loại
 * @param chi_so Chỉ số điểm thả (0 đến SO_VI_TRI_THA_TOI_DA - 1)
 * @param out_pos Con trỏ nhận dữ liệu vị trí thả
 * @return ROBOT_OK nếu hợp lệ, mã lỗi nếu thất bại
 */
robot_err_t robot_positions_lay_diem_tha(uint8_t chi_so, robot_diem_vi_tri_t *out_pos);

/**
 * @brief Cập nhật tọa độ điểm thả sau khi hiệu chuẩn
 * @param chi_so Chỉ số điểm thả
 * @param pos Vị trí mới cần lưu
 * @return ROBOT_OK nếu thành công
 */
robot_err_t robot_positions_dat_diem_tha(uint8_t chi_so, const robot_diem_vi_tri_t *pos);

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_POSITIONS_H */
