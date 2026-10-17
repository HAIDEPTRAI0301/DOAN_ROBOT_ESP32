#ifndef DONG_BO_BA_TRUC_H
#define DONG_BO_BA_TRUC_H

#include "robot_types.h"
#include "profile_toc_do.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Kế hoạch chuyển động đồng bộ 3 trục
 */
typedef struct {
    int32_t delta_xung[ROBOT_NUM_JOINTS]; /**< Độ lệch xung từng trục (có dấu) */
    chieu_quay_t chieu[ROBOT_NUM_JOINTS]; /**< Chiều quay từng trục */
    uint32_t so_xung_tuyet_doi[ROBOT_NUM_JOINTS]; /**< Số xung dương từng trục */
    robot_joint_id_t truc_chinh;         /**< Trục có quãng đường xung dài nhất (trục chủ) */
    profile_toc_do_ket_qua_t profile_truc_chinh; /**< Profile tốc độ cho trục chính */
    bool hop_le;
} dong_bo_ba_truc_ke_hoach_t;

/**
 * @brief Lập kế hoạch đồng bộ chuyển động 3 trục từ độ lệch xung
 * @param delta_xung Độ lệch xung cần đi của 3 trục
 * @param cfg Cấu hình tốc độ/gia tốc mong muốn cho trục chính
 * @param out_ke_hoach Kết quả phân bổ đồng bộ
 * @return ROBOT_OK nếu lập kế hoạch thành công
 */
robot_err_t dong_bo_ba_truc_lap_ke_hoach(const int32_t delta_xung[ROBOT_NUM_JOINTS],
                                         const profile_toc_do_cfg_t *cfg,
                                         dong_bo_ba_truc_ke_hoach_t *out_ke_hoach);

#ifdef __cplusplus
}
#endif

#endif /* DONG_BO_BA_TRUC_H */
