#include "robot_positions.h"
#include <string.h>

/* Vị trí gắp (PICK) cố định - Ban đầu chưa xác minh */
static robot_diem_vi_tri_t s_diem_gap = {
    .goc_khop = {
        .goc = {0.0f, 0.0f, 0.0f},
        .hop_le = false
    },
    .da_xac_minh = false /* TODO: Đo góc thực tế khi gắp trên băng tải */
};

/* Các vị trí thả (PLACE) theo phân loại - Ban đầu chưa xác minh */
static robot_diem_vi_tri_t s_danh_sach_diem_tha[SO_VI_TRI_THA_TOI_DA] = {
    [0] = { .goc_khop = { .goc = {0.0f, 0.0f, 0.0f}, .hop_le = false }, .da_xac_minh = false },
    [1] = { .goc_khop = { .goc = {0.0f, 0.0f, 0.0f}, .hop_le = false }, .da_xac_minh = false },
    [2] = { .goc_khop = { .goc = {0.0f, 0.0f, 0.0f}, .hop_le = false }, .da_xac_minh = false },
    [3] = { .goc_khop = { .goc = {0.0f, 0.0f, 0.0f}, .hop_le = false }, .da_xac_minh = false },
};

robot_err_t robot_positions_init(void)
{
    return ROBOT_OK;
}

robot_err_t robot_positions_lay_diem_gap(robot_diem_vi_tri_t *out_pos)
{
    if (out_pos == NULL) {
        return ROBOT_ERR_INVALID_ARG;
    }
    *out_pos = s_diem_gap;
    if (!s_diem_gap.da_xac_minh) {
        return ROBOT_ERR_POSITION_INVALID;
    }
    return ROBOT_OK;
}

robot_err_t robot_positions_lay_diem_tha(uint8_t chi_so, robot_diem_vi_tri_t *out_pos)
{
    if (out_pos == NULL || chi_so >= SO_VI_TRI_THA_TOI_DA) {
        return ROBOT_ERR_INVALID_ARG;
    }
    *out_pos = s_danh_sach_diem_tha[chi_so];
    if (!s_danh_sach_diem_tha[chi_so].da_xac_minh) {
        return ROBOT_ERR_POSITION_INVALID;
    }
    return ROBOT_OK;
}

robot_err_t robot_positions_dat_diem_tha(uint8_t chi_so, const robot_diem_vi_tri_t *pos)
{
    if (pos == NULL || chi_so >= SO_VI_TRI_THA_TOI_DA) {
        return ROBOT_ERR_INVALID_ARG;
    }
    s_danh_sach_diem_tha[chi_so] = *pos;
    return ROBOT_OK;
}
