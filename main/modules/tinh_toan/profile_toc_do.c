#include "profile_toc_do.h"
#include <math.h>
#include <string.h>

robot_err_t profile_toc_do_tinh_toan(uint32_t tong_xung, const profile_toc_do_cfg_t *cfg, profile_toc_do_ket_qua_t *out_ket_qua)
{
    if (cfg == NULL || out_ket_qua == NULL || tong_xung == 0) {
        return ROBOT_ERR_INVALID_ARG;
    }
    if (cfg->v_toi_da <= 0.0f || cfg->gia_toc <= 0.0f || cfg->giam_toc <= 0.0f) {
        return ROBOT_ERR_INVALID_ARG;
    }

    memset(out_ket_qua, 0, sizeof(profile_toc_do_ket_qua_t));
    out_ket_qua->tong_so_xung = tong_xung;

    float v0 = cfg->v_khoi_dong;
    float v_max = cfg->v_toi_da;
    float a = cfg->gia_toc;
    float d = cfg->giam_toc;

    /* Tính số xung cần thiết để đạt v_max */
    float s_acc = (v_max * v_max - v0 * v0) / (2.0f * a);
    float s_dec = (v_max * v_max - v0 * v0) / (2.0f * d);

    if (s_acc < 0.0f) s_acc = 0.0f;
    if (s_dec < 0.0f) s_dec = 0.0f;

    if (s_acc + s_dec <= (float)tong_xung) {
        /* Profile hình thang (đạt được v_max) */
        uint32_t n_acc = (uint32_t)lroundf(s_acc);
        uint32_t n_dec = (uint32_t)lroundf(s_dec);
        uint32_t n_cruise = tong_xung - (n_acc + n_dec);

        out_ket_qua->xung_tang_toc = n_acc;
        out_ket_qua->xung_deu = n_cruise;
        out_ket_qua->xung_giam_toc = n_dec;
        out_ket_qua->v_thuc_te_dat_duoc = v_max;

        float t_acc = (v_max - v0) / a;
        float t_dec = (v_max - v0) / d;
        float t_cruise = (float)n_cruise / v_max;
        out_ket_qua->tong_thoi_gian_s = t_acc + t_cruise + t_dec;
    } else {
        /* Profile hình tam giác (không đủ hành trình để đạt v_max) */
        float v_peak_sq = (2.0f * a * d * (float)tong_xung + d * v0 * v0 + a * v0 * v0) / (a + d);
        float v_peak = (v_peak_sq > 0.0f) ? sqrtf(v_peak_sq) : v0;

        float s_acc_peak = (v_peak * v_peak - v0 * v0) / (2.0f * a);
        uint32_t n_acc = (uint32_t)lroundf(s_acc_peak);
        if (n_acc > tong_xung) n_acc = tong_xung;
        uint32_t n_dec = tong_xung - n_acc;

        out_ket_qua->xung_tang_toc = n_acc;
        out_ket_qua->xung_deu = 0;
        out_ket_qua->xung_giam_toc = n_dec;
        out_ket_qua->v_thuc_te_dat_duoc = v_peak;

        float t_acc = (v_peak - v0) / a;
        float t_dec = (v_peak - v0) / d;
        out_ket_qua->tong_thoi_gian_s = t_acc + t_dec;
    }

    out_ket_qua->hop_le = true;
    return ROBOT_OK;
}
