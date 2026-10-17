#ifndef KIEM_TRA_AN_TOAN_H
#define KIEM_TRA_AN_TOAN_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo hệ thống kiểm tra an toàn và liên khóa (safety interlocks)
 * @return ROBOT_OK
 */
robot_err_t kiem_tra_an_toan_init(void);

/**
 * @brief Kiểm tra xem hệ thống có đủ điều kiện an toàn để chuyển động (JOG/MOVE) hay không
 * @return true nếu an toàn, false nếu bị khóa
 */
bool kiem_tra_an_toan_cho_phep_chuyen_dong(void);

/**
 * @brief Kiểm tra xem hệ thống có đủ điều kiện để vào chế độ tự động AUTO hay không
 * @return true nếu đủ điều kiện (yêu cầu: đã hiệu chuẩn, đã lắp E-stop phần cứng, v.v.)
 */
bool kiem_tra_an_toan_cho_phep_auto(void);

/**
 * @brief Kiểm tra xem một góc đặt có nằm trong giới hạn góc an toàn của trục hay không
 * @param joint Khớp cần kiểm tra
 * @param goc_deg Góc mục tiêu (độ)
 * @return true nếu nằm trong dải an toàn
 */
bool kiem_tra_an_toan_goc_trong_gioi_han(robot_joint_id_t joint, float goc_deg);

#ifdef __cplusplus
}
#endif

#endif /* KIEM_TRA_AN_TOAN_H */
