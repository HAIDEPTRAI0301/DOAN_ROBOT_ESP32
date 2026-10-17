#ifndef QUAN_LY_LOI_H
#define QUAN_LY_LOI_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DO_DAI_LY_DO_LOI_MAX    64

/**
 * @brief Khởi tạo hệ thống quản lý lỗi
 */
void quan_ly_loi_init(void);

/**
 * @brief Kích hoạt lỗi và khóa hệ thống (Fault Latch)
 * @param ma_loi Mã lỗi định danh
 * @param ly_do Chuỗi ký tự mô tả nguyên nhân lỗi
 */
void quan_ly_loi_kich_hoat(robot_err_t ma_loi, const char *ly_do);

/**
 * @brief Kiểm tra xem hệ thống có đang bị khóa lỗi hay không
 * @return true nếu đang có lỗi bị khóa
 */
bool quan_ly_loi_co_loi(void);

/**
 * @brief Lấy mã lỗi hiện tại
 * @return Mã lỗi robot_err_t
 */
robot_err_t quan_ly_loi_ma_loi_hien_tai(void);

/**
 * @brief Lấy chuỗi mô tả nguyên nhân lỗi gần nhất
 * @return Chuỗi ký tự
 */
const char* quan_ly_loi_ly_do_hien_tai(void);

/**
 * @brief Yêu cầu xóa lỗi (chỉ xóa được khi nguyên nhân lỗi vật lý đã được xử lý)
 * @return ROBOT_OK nếu xóa thành công, ROBOT_ERR_INVALID_STATE nếu không thể xóa
 */
robot_err_t quan_ly_loi_xoa_loi(void);

#ifdef __cplusplus
}
#endif

#endif /* QUAN_LY_LOI_H */
