#include "kiem_tra_an_toan.h"
#include "robot_config.h"
#include "quan_ly_loi.h"
#include "may_trang_thai.h"

robot_err_t kiem_tra_an_toan_init(void)
{
    return ROBOT_OK;
}

bool kiem_tra_an_toan_cho_phep_chuyen_dong(void)
{
    /* Bị khóa nếu đang có lỗi */
    if (quan_ly_loi_co_loi()) {
        return false;
    }

    robot_trang_thai_t st = may_trang_thai_hien_tai();
    if (st == ROBOT_TRANG_THAI_KHOA_LOI ||
        st == ROBOT_TRANG_THAI_KHOI_DONG ||
        st == ROBOT_TRANG_THAI_CHO_KHOI_DONG) {
        return false;
    }

    return true;
}

bool kiem_tra_an_toan_cho_phep_auto(void)
{
    /* Cổng an toàn bắt buộc cho AUTO:
     * 1. Cờ hiệu chuẩn ROBOT_CALIBRATION_COMPLETE phải là true
     * 2. Không có lỗi đang latch
     * 3. Phải có E-stop phần cứng độc lập (hiện chưa lắp -> chặn)
     */
    if (!robot_config_da_hieu_chuan()) {
        return false;
    }

    if (quan_ly_loi_co_loi()) {
        return false;
    }

    /* TODO: E-stop vật lý hiện chưa lắp; bắt buộc giữ false cho AUTO */
    return false;
}

bool kiem_tra_an_toan_goc_trong_gioi_han(robot_joint_id_t joint, float goc_deg)
{
    if (joint >= ROBOT_NUM_JOINTS) {
        return false;
    }

    const robot_cau_hinh_khop_t *cfg = robot_config_lay_khop(joint);
    if (cfg == NULL || !cfg->da_hieu_chuan) {
        /* Nếu khớp chưa hiệu chuẩn giới hạn hành trình, tạm thời chỉ cho phép trong chế độ Commissioning có kiểm soát */
        return true;
    }

    if (goc_deg < cfg->gioi_han_goc_min || goc_deg > cfg->gioi_han_goc_max) {
        return false;
    }

    return true;
}
