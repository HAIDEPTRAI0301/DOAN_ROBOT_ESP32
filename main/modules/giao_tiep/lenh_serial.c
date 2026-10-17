#include "lenh_serial.h"
#include "may_trang_thai.h"
#include "quan_ly_loi.h"
#include "tim_home.h"
#include "robot_config.h"
#include <stdio.h>
#include <string.h>

robot_err_t lenh_serial_init(void)
{
    printf("\n[SERIAL] He thong nhan lenh Serial da khoi tao.\n");
    return ROBOT_OK;
}

void lenh_serial_in_tro_giup(void)
{
    printf("\n=== DANH SACH LENH SERIAL COMMISSIONING ===\n");
    printf("  HELP        : Xem danh sach lenh tro giup\n");
    printf("  STATUS      : Xem trang thai robot va cac khop\n");
    printf("  HOME        : Bat dau homing tuan tu (J2 -> J3 -> J1)\n");
    printf("  JOG <J> <G> : Dich chuyen tuong doi khop J goc G do (vd: JOG 1 10.5)\n");
    printf("  MOVE <A B C>: Di chuyen tuyet doi 3 khop den goc A B C do\n");
    printf("  RESET_FAULT : Xoa loi va yeu cau phuc hoi\n");
    printf("===========================================\n\n");
}

void lenh_serial_in_trang_thai(void)
{
    robot_trang_thai_t st = may_trang_thai_hien_tai();
    printf("\n=== TRANG THAI HE THONG ===\n");
    printf("Trang thai may: %s\n", may_trang_thai_chuoi(st));
    printf("Hieu chuan he thong: %s\n", robot_config_da_hieu_chuan() ? "DA HOAN TAT" : "CHUA (COMMISSIONING)");
    printf("Trang thai Home: %s\n", tim_home_da_hoan_thanh() ? "DA HOME" : "CHUA HOME");
    if (quan_ly_loi_co_loi()) {
        printf("CANH BAO LOI: Ma loi = %d | Ly do: %s\n", quan_ly_loi_ma_loi_hien_tai(), quan_ly_loi_ly_do_hien_tai());
    }
    printf("===========================\n\n");
}

void lenh_serial_xu_ly(void)
{
    /* TODO: Giai đoạn Stage 2 sẽ đọc các ký tự từ UART/VFS stdin và thực thi lệnh HELP/STATUS */
}
