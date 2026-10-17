#include "trinh_dieu_khien_robot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    /* Khởi tạo toàn bộ hệ thống điều khiển robot */
    trinh_dieu_khien_robot_init();

    /* Vòng lặp điều phối chính */
    while (1) {
        trinh_dieu_khien_robot_vong_lap();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
