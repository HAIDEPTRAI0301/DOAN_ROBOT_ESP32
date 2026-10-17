#include "quan_ly_loi.h"
#include "may_trang_thai.h"
#include "bo_phat_xung.h"
#include <string.h>

static bool s_co_loi = false;
static robot_err_t s_ma_loi = ROBOT_OK;
static char s_ly_do[DO_DAI_LY_DO_LOI_MAX] = {0};

void quan_ly_loi_init(void)
{
    s_co_loi = false;
    s_ma_loi = ROBOT_OK;
    memset(s_ly_do, 0, sizeof(s_ly_do));
}

void quan_ly_loi_kich_hoat(robot_err_t ma_loi, const char *ly_do)
{
    s_co_loi = true;
    s_ma_loi = ma_loi;
    if (ly_do != NULL) {
        strncpy(s_ly_do, ly_do, DO_DAI_LY_DO_LOI_MAX - 1);
        s_ly_do[DO_DAI_LY_DO_LOI_MAX - 1] = '\0';
    } else {
        strncpy(s_ly_do, "Loi khong xac dinh", DO_DAI_LY_DO_LOI_MAX - 1);
    }

    /* Khóa chuyển động ngay lập tức */
    bo_phat_xung_dung_toan_bo();

    /* Khóa máy trạng thái vào FAULT_LATCHED */
    may_trang_thai_chuyen(ROBOT_TRANG_THAI_KHOA_LOI);
}

bool quan_ly_loi_co_loi(void)
{
    return s_co_loi;
}

robot_err_t quan_ly_loi_ma_loi_hien_tai(void)
{
    return s_ma_loi;
}

const char* quan_ly_loi_ly_do_hien_tai(void)
{
    return s_ly_do;
}

robot_err_t quan_ly_loi_xoa_loi(void)
{
    if (!s_co_loi) {
        return ROBOT_OK;
    }

    /* Xóa cờ lỗi cục bộ và chuyển sang trạng thái chờ phục hồi */
    s_co_loi = false;
    s_ma_loi = ROBOT_OK;
    memset(s_ly_do, 0, sizeof(s_ly_do));

    may_trang_thai_chuyen(ROBOT_TRANG_THAI_YEU_CAU_KHOI_PHUC);
    return ROBOT_OK;
}
