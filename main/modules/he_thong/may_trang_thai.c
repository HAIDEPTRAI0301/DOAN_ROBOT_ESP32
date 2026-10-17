#include "may_trang_thai.h"

static robot_trang_thai_t s_trang_thai_hien_tai = ROBOT_TRANG_THAI_KHOI_DONG;

robot_err_t may_trang_thai_init(void)
{
    s_trang_thai_hien_tai = ROBOT_TRANG_THAI_KHOI_DONG;
    return ROBOT_OK;
}

robot_trang_thai_t may_trang_thai_hien_tai(void)
{
    return s_trang_thai_hien_tai;
}

robot_err_t may_trang_thai_chuyen(robot_trang_thai_t state_moi)
{
    /* Mọi trạng thái đều được phép chuyển sang KHOA_LOI khi xảy ra sự cố */
    if (state_moi == ROBOT_TRANG_THAI_KHOA_LOI) {
        s_trang_thai_hien_tai = state_moi;
        return ROBOT_OK;
    }

    /* Kiểm tra tính hợp lệ của các bước chuyển */
    switch (s_trang_thai_hien_tai) {
        case ROBOT_TRANG_THAI_KHOI_DONG:
            if (state_moi == ROBOT_TRANG_THAI_CHO_KHOI_DONG) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_CHO_KHOI_DONG:
            if (state_moi == ROBOT_TRANG_THAI_COMMISSIONING_KHOA || state_moi == ROBOT_TRANG_THAI_KIEM_TRA_AN_TOAN) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_COMMISSIONING_KHOA:
            if (state_moi == ROBOT_TRANG_THAI_KIEM_TRA_AN_TOAN || state_moi == ROBOT_TRANG_THAI_TIM_HOME) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_KIEM_TRA_AN_TOAN:
            if (state_moi == ROBOT_TRANG_THAI_TIM_HOME || state_moi == ROBOT_TRANG_THAI_SAN_SANG || state_moi == ROBOT_TRANG_THAI_COMMISSIONING_KHOA) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_TIM_HOME:
            if (state_moi == ROBOT_TRANG_THAI_SAN_SANG || state_moi == ROBOT_TRANG_THAI_COMMISSIONING_KHOA) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_SAN_SANG:
            if (state_moi == ROBOT_TRANG_THAI_DANG_CHUYEN_DONG || state_moi == ROBOT_TRANG_THAI_TIM_HOME) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_DANG_CHUYEN_DONG:
            if (state_moi == ROBOT_TRANG_THAI_SAN_SANG) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_KHOA_LOI:
            if (state_moi == ROBOT_TRANG_THAI_YEU_CAU_KHOI_PHUC) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        case ROBOT_TRANG_THAI_YEU_CAU_KHOI_PHUC:
            if (state_moi == ROBOT_TRANG_THAI_COMMISSIONING_KHOA || state_moi == ROBOT_TRANG_THAI_TIM_HOME) {
                s_trang_thai_hien_tai = state_moi;
                return ROBOT_OK;
            }
            break;

        default:
            break;
    }

    return ROBOT_ERR_INVALID_STATE;
}

const char* may_trang_thai_chuoi(robot_trang_thai_t state)
{
    switch (state) {
        case ROBOT_TRANG_THAI_KHOI_DONG:          return "KHOI_DONG";
        case ROBOT_TRANG_THAI_CHO_KHOI_DONG:      return "CHO_KHOI_DONG (5s)";
        case ROBOT_TRANG_THAI_COMMISSIONING_KHOA: return "COMMISSIONING_KHOA";
        case ROBOT_TRANG_THAI_KIEM_TRA_AN_TOAN:   return "KIEM_TRA_AN_TOAN";
        case ROBOT_TRANG_THAI_TIM_HOME:           return "TIM_HOME";
        case ROBOT_TRANG_THAI_SAN_SANG:           return "SAN_SANG";
        case ROBOT_TRANG_THAI_DANG_CHUYEN_DONG:   return "DANG_CHUYEN_DONG";
        case ROBOT_TRANG_THAI_KHOA_LOI:           return "KHOA_LOI (FAULT_LATCHED)";
        case ROBOT_TRANG_THAI_YEU_CAU_KHOI_PHUC:  return "YEU_CAU_KHOI_PHUC";
        default:                                  return "KHONG_XAC_DINH";
    }
}
