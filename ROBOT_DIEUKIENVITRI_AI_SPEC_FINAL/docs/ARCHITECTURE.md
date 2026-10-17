# Kiến trúc hệ thống

## 1. Sơ đồ trách nhiệm

```text
ESP32-CAM (MCU C)                  ESP32/ESP32-S3 Process (MCU B)
- Camera                           - Nhận kết quả phân loại
- Phân loại vật                    - Đọc cảm biến NPN
- Gửi class/object reference ----> - Điều khiển băng tải stepper + TB6600 #4
                                   - Điều khiển bơm 12 V qua L298N
                                   - State machine gắp-đặt
                                   - UART command/status <---->
                                                   ESP32-S3 Motion (MCU A)
                                                   - 3 trục J1/J2/J3 + 3 TB6600
                                                   - Homing, STEP/DIR, góc-xung
                                                   - Planner, limits, fault state
                                                   - PICK/PLACE position
```

Sơ đồ thể hiện phân công chức năng, chưa chốt dây/baud/protocol C–B hoặc A–B.

## 2. Giai đoạn hiện tại: MCU A only

Project root chứa firmware motion của MCU A. Không tạo thêm firmware B/C trừ khi người dùng yêu cầu rõ. Thiết kế interface command nên độc lập với Serial parser để tương lai có thể nhận lệnh UART mà không viết lạ    i motion layer.

### Phân lớp dự kiến

- `app_state`: trạng thái khởi động/commissioning/ready/fault.
- `board_config`: GPIO, polarity đã xác minh, các tuỳ chọn compile-time.
- `limit_switch`: đọc Home, debounce, diagnostic.
- `stepper_axis`: điều khiển một trục, direction, xung, bộ đếm vị trí.
- `motion_planner`: profile tăng/giảm tốc và phối hợp ba trục.
- `homing`: quy trình tìm Home, backoff, tiếp cận chậm, timeout.
- `kinematics_config` hoặc `joint_calibration`: offset Home, pulses-per-degree, limits sau khi đo.
- `robot_positions`: vị trí PICK/PLACE, có cờ hợp lệ; không chứa số giả định.
- `command_service`: nhận lệnh qua Serial trong commissioning; tách khỏi motion logic.
- `diagnostics`: log theo cấp độ, mã lỗi, state, uptime.
- `safety_interlocks`: kiểm tra commissioning flag, config validity, E-stop readiness và các điều kiện cho phép.

Đây là đề xuất module, không bắt buộc tạo tất cả file cùng lúc. Chỉ tạo module cho stage đang được duyệt. Tên/đường dẫn cụ thể phải khớp layout project hiện tại sau khi inspect.

## 3. Hai kênh UART tương lai

### A–B

Đưa command/ACK/status/result qua giao thức có sequence ID, message type, payload length/format, checksum hoặc kiểm tra tính toàn vẹn, timeout, heartbeat, deduplication và state synchronization. Format cụ thể chưa chốt.

### C–B

ESP32-CAM gửi classification result phải gắn đúng object/event, có ID hoặc cơ chế liên kết đối tượng, timestamp/expiry và class validity. Lối truyền chưa chốt sau khi người dùng sửa kiến trúc thành ba MCU; không gán GPIO hoặc baud.

## 4. Quy tắc liên kết camera và cảm biến

- Chỉ một classification result hợp lệ ứng với đúng vật mới cho phép B dừng băng tải ở cạnh sensor và tạo yêu cầu gắp.
- Không có result, result hết hạn, class không hợp lệ hoặc không ghép được result với vật tại sensor: vật đi qua, không phát sinh lệnh pick.
- Không dùng một classification result đã tiêu thụ cho vật tiếp theo.
- Nếu detection hợp lệ đến khi A bận, B có thể giữ tối đa một request; request có object ID và không tạo motion overlap. Nếu storage slot đã có request, policy của vật tiếp theo cần được xác định an toàn trước khi triển khai.

## 5. Logs

Mỗi board log cục bộ qua USB-UART/Serial. B có thể chuyển tiếp một phần log từ A khi A–B sẵn sàng; gắn nguồn `MOTION_A`. Không chuyển tiếp log kiểu blocking ở trong interrupt hoặc task tạo xung. Log không phải giao thức safety.
