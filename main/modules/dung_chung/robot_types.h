#ifndef ROBOT_TYPES_H
#define ROBOT_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mã lỗi toàn cục cho hệ thống điều khiển robot
 */
typedef enum {
    ROBOT_OK                        = 0,   /**< Hoàn thành không lỗi */
    ROBOT_ERR_GENERAL              = -1,  /**< Lỗi chung không xác định */
    ROBOT_ERR_INVALID_ARG          = -2,  /**< Tham số truyền vào không hợp lệ */
    ROBOT_ERR_INVALID_STATE        = -3,  /**< Trạng thái hiện tại không cho phép thao tác */
    ROBOT_ERR_TIMEOUT              = -4,  /**< Hết thời gian chờ (timeout) */
    ROBOT_ERR_HARDWARE             = -5,  /**< Lỗi phần cứng hoặc GPIO */
    ROBOT_ERR_NOT_HOMED            = -6,  /**< Robot chưa hoàn thành Homing */
    ROBOT_ERR_SAFETY_INTERLOCK     = -7,  /**< Bị chặn bởi cổng kiểm tra an toàn */
    ROBOT_ERR_POSITION_INVALID     = -8,  /**< Vị trí mất tin cậy (nghi mất bước/gián đoạn) */
    ROBOT_ERR_LIMIT_EXCEEDED       = -9,  /**< Góc hoặc số xung vượt giới hạn cho phép */
    ROBOT_ERR_COMMISSIONING_LOCKED = -10, /**< Chế độ Commissioning đang khóa chuyển động */
    ROBOT_ERR_BUSY                 = -11  /**< Bộ điều khiển hoặc trục đang bận */
} robot_err_t;

/**
 * @brief Định danh các khớp của cánh tay robot
 */
typedef enum {
    JOINT_1 = 0,    /**< Khớp J1: Đế quay */
    JOINT_2 = 1,    /**< Khớp J2: Vai (nâng/hạ) */
    JOINT_3 = 2,    /**< Khớp J3: Khuỷu (gập/duỗi) */
    ROBOT_NUM_JOINTS = 3 /**< Tổng số khớp của cánh tay */
} robot_joint_id_t;

/**
 * @brief Chiều chuyển động của động cơ bước
 */
typedef enum {
    DIR_DUONG = 0,  /**< Chiều dương (quy ước chiều vật lý) */
    DIR_AM    = 1   /**< Chiều âm */
} chieu_quay_t;

/**
 * @brief Trạng thái công tắc giới hạn Home
 */
typedef enum {
    CONG_TAC_NHA       = 0, /**< Công tắc đang nhả (tiếp điểm hở) */
    CONG_TAC_NHAN      = 1, /**< Công tắc đang bị nhấn (tiếp điểm đóng) */
    CONG_TAC_KHONG_XAC_DINH = 2  /**< Chưa đọc được trạng thái hoặc lỗi kết nối */
} trang_thai_cong_tac_t;

/**
 * @brief Trạng thái hoạt động tổng thể của Robot
 */
typedef enum {
    ROBOT_TRANG_THAI_KHOI_DONG             = 0, /**< Vừa cấp nguồn, chuẩn bị hệ thống */
    ROBOT_TRANG_THAI_CHO_KHOI_DONG         = 1, /**< Đang chờ 5 giây an toàn sau boot */
    ROBOT_TRANG_THAI_COMMISSIONING_KHOA    = 2, /**< Mặc định: Chế độ hiệu chỉnh, khóa chuyển động AUTO */
    ROBOT_TRANG_THAI_KIEM_TRA_AN_TOAN      = 3, /**< Đang tự kiểm tra cấu hình và cảm biến */
    ROBOT_TRANG_THAI_TIM_HOME              = 4, /**< Đang thực hiện chu trình tìm Home tuần tự */
    ROBOT_TRANG_THAI_SAN_SANG              = 5, /**< Đã Home, vị trí hợp lệ, sẵn sàng nhận lệnh */
    ROBOT_TRANG_THAI_DANG_CHUYEN_DONG      = 6, /**< Đang thực hiện di chuyển JOG hoặc MOVE */
    ROBOT_TRANG_THAI_KHOA_LOI              = 7, /**< Xảy ra lỗi: Dừng khẩn, khóa toàn bộ chuyển động */
    ROBOT_TRANG_THAI_YEU_CAU_KHOI_PHUC     = 8  /**< Đã dừng lỗi, cần người vận hành xác nhận/Home lại */
} robot_trang_thai_t;

/**
 * @brief Cấu trúc lưu góc khớp (đơn vị: độ)
 */
typedef struct {
    float goc[ROBOT_NUM_JOINTS]; /**< Góc từng khớp [J1, J2, J3] */
    bool hop_le;                 /**< Cờ đánh dấu dữ liệu góc có hợp lệ hay không */
} robot_goc_khop_t;

/**
 * @brief Cấu trúc lưu số xung/bước từng khớp
 */
typedef struct {
    int32_t xung[ROBOT_NUM_JOINTS]; /**< Số bước/xung từng khớp [J1, J2, J3] */
    bool hop_le;                    /**< Cờ đánh dấu vị trí xung có đáng tin cậy hay không */
} robot_xung_khop_t;

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_TYPES_H */
