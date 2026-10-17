# OPEN ITEMS — Thông số chưa xác minh

> Không điền giá trị giả định vào code. Các mục này khóa commissioning/AUTO hoặc phần tích hợp tương ứng cho tới khi được xác minh.

## A. Blocker trước motor test của MCU A

1. **Model chính xác ESP32-S3 board**, pinout/schematic và xác nhận GPIO19/20 không xung đột electrical với cổng/linh kiện board khi dùng USB-UART.
2. **TB6600 model/clone cụ thể**; xác minh input wiring hiện tại và khả năng nhận trực tiếp logic GPIO 3.3 V. Không tự chuyển wiring hoặc thêm mạch khi chưa được duyệt.
3. Motor NEMA17 nhãn/model, dòng pha chính xác; đối chiếu nhóm DIP dòng ON–ON–OFF với bảng đúng driver để xác minh Current 1.5 A / Peak 1.7 A có đúng ý nghĩa nào.
4. Xác nhận nhóm vi bước DIP OFF–ON–OFF thực tế đúng là 1/8 trên đúng module.
5. Nguồn có sẵn 12 V–20 A: xác minh dải điện áp module, motor, cấu hình driver, dây/fuse và khả năng đạt tốc độ/moment mong muốn. Chưa mặc định nguồn này là cấu hình đã nghiệm thu.
6. Kiểm tra từng Home input: COM→GND, NO→GPIO, nhả=HIGH/nhấn=LOW; debounce và dây thực tế.
7. Bench-test đúng chiều tìm Home trên từng khớp, xác định cách nhìn để định nghĩa J1 clockwise, và chiều rời công tắc. Chưa quy ra DIR HIGH/LOW.
8. Xác minh cơ cấu puly 20T→90T thực sự là một tầng truyền động trên từng khớp; kiểm tra cơ cấu liên kết có làm angle-to-output khác tỷ số 4.5 hay không.
9. Đo home offset/góc tham chiếu riêng từng khớp và giới hạn góc cơ khí J1/J2/J3.
10. Định nghĩa vị trí PICK/PLACE thực tế bằng đo/jog sau khi hiệu chuẩn. PLACE đổi được; PICK giữ cố định. Chưa có số góc.
11. Chọn max velocity, acceleration/deceleration, max homing travel, timeout, backoff distances và tốc độ tiếp cận lần hai sau test có kiểm soát.
12. Chính sách khi switch đã pressed ngay lúc boot chưa được trả lời: default không tự lùi trừ khi chiều rời switch được kiểm chứng; ở commissioning thì dừng và log để tránh đoán hướng.
13. E-stop vật lý chưa lắp; GPIO chưa gán. Không AUTO không giám sát trên robot thật cho tới khi có biện pháp ngắt động lực độc lập được thử nghiệm.
14. Cờ cấu hình commissioning-complete/`robot_config.h` phải giữ false mặc định; chưa có file config hợp lệ thì không tạo move.
15. Xác nhận ESP-IDF version/toolchain bằng `idf.py --version` và build baseline project hiện có. Ảnh IDE cho thấy extension/environment có ESP-IDF v6.1, nhưng agent vẫn phải xác minh CLI SDK thực tế.

## B. Blocker trước AUTO của toàn hệ thống

1. Model chính xác controller B (“ESP32 Node32S”/ESP32-S3) và MCU C (ESP32-CAM/camera sensor).
2. GPIO/baud/UART peripheral và electrical interface A↔B; protocol version, framing, timeout/heartbeat/CRC policy.
3. Giao tiếp C→B sau kiến trúc 3 MCU (UART đã được đề xuất trước đó nhưng cần xác nhận cuối cùng), baud/pin/format.
4. Cách nhận biết object identity: camera nhìn trước NPN sensor; phải nối classification result đúng với vật qua distance/time/sequence, TTL/expiry, consume-once.
5. Cách đấu NPN: model, NO/NC, 12/24 V supply, output type, wire colors, sinking current, interface circuit; không nối trực tiếp industrial output lên GPIO.
6. Băng tải: motor label/rated current, ratio/conveyor mechanism, direction, steps/rev, microstep/dip of TB6600 #4, supply and wiring, step/dir GPIO B, pulse rates, acceleration/deceleration, sensor location and physical stop point.
7. Bơm: L298N wiring, enable/input pins, active level, pump current/startup current, source, default safe output on B boot/reset.
8. Vacuum delay until object reliably held; no vacuum/pressure confirmation sensor yet.
9. Behavior if sensor does not clear after pick, camera result is late/stale, camera link lost, sensor stuck/noise, queue slot full, or a second/unclassified object arrives.
10. Queue limited to one pending eligible object; behavior when slot full is not defined. Do not accept multiple arbitrary pending requests.
11. E-stop system-level wiring that disables motor drivers/conveyor safely; pump retention strategy if holding object during fault or B power loss/reset.
12. Mechanical collision-safe paths for J2/J3/J1, pickup/drop height strategy, and proof that current sequential/planned joint trajectories cannot collide.
13. Camera classification labels and actual action mapping (which class is picked, ignored, or placed at which location) not provided.

## C. Implementation status

- Architecture spec only; no implementation is implied.
- No firmware build, flash, motor test, PID tuning, pulse backend test or UART test has been claimed.
- `robot_positions.h`, motion profile and hardware-specific values must remain invalid/unconfigured until measurement/verification.
