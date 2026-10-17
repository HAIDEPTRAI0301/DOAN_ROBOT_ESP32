#ifndef TRUC_BUOC_H
#define TRUC_BUOC_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo giao diện điều khiển cho một trục động cơ bước
 * @param joint Khớp cần khởi tạo (JOINT_1, JOINT_2, JOINT_3)
 * @return ROBOT_OK nếu thành công
 */
robot_err_t truc_buoc_init(robot_joint_id_t joint);

/**
 * @brief Đặt chiều quay cho trục
 * @param joint Khớp cần đặt chiều
 * @param chieu Chiều quay (DIR_DUONG hoặc DIR_AM)
 * @return ROBOT_OK nếu thành công
 */
robot_err_t truc_buoc_dat_chieu(robot_joint_id_t joint, chieu_quay_t chieu);

/**
 * @brief Đọc vị trí ước lượng hiện tại theo số xung
 * @param joint Khớp cần đọc
 * @return Số xung vị trí hiện tại
 */
int32_t truc_buoc_doc_vi_tri_xung(robot_joint_id_t joint);

/**
 * @brief Gán giá trị mốc số xung cho trục (thường dùng sau khi Homing thành công)
 * @param joint Khớp cần gán
 * @param xung Giá trị xung mới
 */
void truc_buoc_dat_vi_tri_xung(robot_joint_id_t joint, int32_t xung);

/**
 * @brief Kiểm tra xem vị trí hiện tại của trục có đáng tin cậy hay không
 * @param joint Khớp cần kiểm tra
 * @return true nếu vị trí hợp lệ
 */
bool truc_buoc_vi_tri_hop_le(robot_joint_id_t joint);

/**
 * @brief Đánh dấu vị trí của trục là không đáng tin cậy (khi mất bước, lỗi, hoặc gián đoạn)
 * @param joint Khớp cần đánh dấu
 */
void truc_buoc_danh_dau_vi_tri_khong_hop_le(robot_joint_id_t joint);

#ifdef __cplusplus
}
#endif

#endif /* TRUC_BUOC_H */
