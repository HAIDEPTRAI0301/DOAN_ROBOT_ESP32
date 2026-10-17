#ifndef DIEU_KHIEN_VI_TRI_H
#define DIEU_KHIEN_VI_TRI_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo module điều khiển vị trí
 * @return ROBOT_OK
 */
robot_err_t dieu_khien_vi_tri_init(void);

/**
 * @brief Thực hiện lệnh JOG tương đối trên một trục (đơn vị: độ)
 * @param joint Khớp cần dịch chuyển
 * @param delta_deg Góc dịch chuyển tương đối (có dấu)
 * @return ROBOT_OK nếu lệnh được tiếp nhận hợp lệ
 */
robot_err_t dieu_khien_vi_tri_jog(robot_joint_id_t joint, float delta_deg);

/**
 * @brief Thực hiện lệnh MOVE tuyệt đối đến bộ góc mục tiêu (đơn vị: độ)
 * @param target_angles Bộ 3 góc mục tiêu
 * @return ROBOT_OK nếu hợp lệ và bắt đầu thực hiện
 */
robot_err_t dieu_khien_vi_tri_move(const robot_goc_khop_t *target_angles);

/**
 * @brief Dừng khẩn cấp mọi chuyển động vị trí và khóa lỗi
 * @return ROBOT_OK
 */
robot_err_t dieu_khien_vi_tri_dung_khan(void);

/**
 * @brief Đọc góc ước lượng hiện tại của 3 khớp (tính từ số xung đã phát)
 * @param out_angles Con trỏ nhận giá trị góc
 * @return ROBOT_OK nếu vị trí hợp lệ, ROBOT_ERR_POSITION_INVALID nếu chưa Home hoặc mất độ tin cậy
 */
robot_err_t dieu_khien_vi_tri_doc_goc_hien_tai(robot_goc_khop_t *out_angles);

/**
 * @brief Kiểm tra xem robot có đang trong hành trình chuyển động hay không
 * @return true nếu đang di chuyển
 */
bool dieu_khien_vi_tri_dang_chuyen_dong(void);

#ifdef __cplusplus
}
#endif

#endif /* DIEU_KHIEN_VI_TRI_H */
