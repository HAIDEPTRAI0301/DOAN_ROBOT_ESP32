#ifndef PROFILE_TOC_DO_H
#define PROFILE_TOC_DO_H

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Tham số cấu hình profile vận tốc hình thang
 */
typedef struct {
    float v_khoi_dong;  /**< Vận tốc khởi động (bước/giây) */
    float v_toi_da;     /**< Vận tốc tối đa mong muốn (bước/giây) */
    float gia_toc;      /**< Gia tốc tăng tốc (bước/giây^2) */
    float giam_toc;     /**< Gia tốc giảm tốc (bước/giây^2) */
} profile_toc_do_cfg_t;

/**
 * @brief Kết quả tính toán phân đoạn chuyển động hình thang
 */
typedef struct {
    uint32_t tong_so_xung;      /**< Tổng số xung của hành trình */
    uint32_t xung_tang_toc;     /**< Số xung trong giai đoạn tăng tốc */
    uint32_t xung_deu;          /**< Số xung trong giai đoạn chạy đều */
    uint32_t xung_giam_toc;     /**< Số xung trong giai đoạn giảm tốc */
    float v_thuc_te_dat_duoc;   /**< Vận tốc đỉnh thực tế (v_toi_da hoặc đỉnh tam giác nếu hành trình ngắn) */
    float tong_thoi_gian_s;     /**< Tổng thời gian dự kiến hoàn thành (giây) */
    bool hop_le;                /**< Kế hoạch profile có hợp lệ không */
} profile_toc_do_ket_qua_t;

/**
 * @brief Tính toán phân đoạn profile vận tốc hình thang cho một chuyển động
 * @param tong_xung Tổng số xung cần đi
 * @param cfg Cấu hình tham số tốc độ/gia tốc
 * @param out_ket_qua Kết quả phân chia số xung và thời gian
 * @return ROBOT_OK nếu tính toán thành công
 */
robot_err_t profile_toc_do_tinh_toan(uint32_t tong_xung, const profile_toc_do_cfg_t *cfg, profile_toc_do_ket_qua_t *out_ket_qua);

#ifdef __cplusplus
}
#endif

#endif /* PROFILE_TOC_DO_H */
