#ifndef QUY_DOI_GOC_XUNG_H
#define QUY_DOI_GOC_XUNG_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Quy đổi từ góc (độ) sang số xung tương ứng của một khớp
 * @param joint Khớp cần tính toán
 * @param goc_deg Góc mong muốn (độ)
 * @param out_xung Con trỏ lưu số xung tính được
 * @return ROBOT_OK nếu hợp lệ, ROBOT_ERR_INVALID_ARG nếu out_xung NULL hoặc goc_deg không hợp lệ
 */
robot_err_t quy_doi_goc_sang_xung(robot_joint_id_t joint, float goc_deg, int32_t *out_xung);

/**
 * @brief Quy đổi từ số xung sang góc (độ)
 * @param joint Khớp cần tính toán
 * @param xung Số xung hiện tại
 * @param out_goc_deg Con trỏ lưu giá trị góc tính được
 * @return ROBOT_OK nếu hợp lệ
 */
robot_err_t quy_doi_xung_sang_goc(robot_joint_id_t joint, int32_t xung, float *out_goc_deg);

/**
 * @brief Quy đổi bộ 3 góc sang bộ 3 số xung
 * @param goc_khop Bộ góc đầu vào
 * @param out_xung_khop Bộ xung đầu ra
 * @return ROBOT_OK nếu thành công
 */
robot_err_t quy_doi_bo_goc_sang_xung(const robot_goc_khop_t *goc_khop, robot_xung_khop_t *out_xung_khop);

/**
 * @brief Quy đổi bộ 3 số xung sang bộ 3 góc
 * @param xung_khop Bộ xung đầu vào
 * @param out_goc_khop Bộ góc đầu ra
 * @return ROBOT_OK nếu thành công
 */
robot_err_t quy_doi_bo_xung_sang_goc(const robot_xung_khop_t *xung_khop, robot_goc_khop_t *out_goc_khop);

#ifdef __cplusplus
}
#endif

#endif /* QUY_DOI_GOC_XUNG_H */
