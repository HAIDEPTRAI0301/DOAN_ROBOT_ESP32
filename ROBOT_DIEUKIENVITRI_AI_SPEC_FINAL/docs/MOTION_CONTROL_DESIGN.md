# Thiết kế motion controller A

## 1. Nguyên tắc

- Điều khiển open-loop stepper: software phát STEP và cập nhật số xung. Không encoder nghĩa là không thể đo xác nhận actual angle và không thể dùng PID vị trí kín đúng nghĩa.
- Không để Serial `printf`, UART protocol, logging hoặc parsing chặn chuỗi phát xung.
- Homing tuần tự; chuyển động từ góc này sang góc khác phối hợp ba trục đồng bộ theo profile chung.
- Ưu tiên pulse generation định thời/phần cứng hoặc driver phù hợp ESP-IDF đang cài. Agent phải kiểm tra API của SDK thật trước khi chọn RMT/MCPWM/GPTimer hay giải pháp khác; không đưa API vào code dựa vào trí nhớ nếu chưa xác minh tương thích.

## 2. Module dự kiến

Không cần tạo tất cả file trong một stage; tên có thể được tinh chỉnh sau khi inspect project, nhưng trách nhiệm phải tách rõ:

- `robot_config.h`: board/pin polarity đã xác minh, flag `ROBOT_CALIBRATION_COMPLETE`, motion safety options. Không chứa giá trị góc bịa.
- `robot_positions.h`: vị trí PICK và PLACE; mỗi vị trí gồm ba góc và cờ valid. PLACE thay đổi được; PICK được giữ cố định theo yêu cầu. Giá trị không được xác nhận thì invalid.
- `stepper_axis.h/.c`: thiết lập DIR, yêu cầu STEP count/profile cho một axis, step counter và position validity.
- `motion_planner.h/.c`: chuyển 3 trục đồng bộ, hướng, số step từng trục, profile accel/decel và completion/abort.
- `homing.h/.c`: state machine 2-stage cho mỗi switch, sequential order J2→J3→J1, debounce/timeout.
- `limit_switch.h/.c`: đọc NO switch, debounce và diagnostics.
- `command_parser.h/.c`: parse Serial strict, không thực thi trực tiếp GPIO; tạo command struct.
- `command_service.h/.c`: validate quyền/state/interlocks rồi dispatch command.
- `robot_state.h/.c`: canonical state, homed flags, position-valid, faults.
- `diagnostics.h/.c`: log có cấp độ, không blocking motion path.
- `safety_interlocks.h/.c`: central gates để ngăn move/AUTO khi config/safety không hợp lệ.

## 3. Tính xung

Từ data hiện có: motor 1.8° (200 full steps/rev), microstep 1/8, 20T driver pulley, 90T driven pulley. Với giả định một stage và driven pulley trực tiếp là output joint, 1600 pulses/motor rev × 4.5 = 7200 pulses/output rev ≈ 20 pulses/output degree.

Không hardcode con số đó là calibration cuối cùng cho joint. Đưa vào config riêng khi verified; nếu chưa hiệu chuẩn, `position_calibration_valid=false` và không cho AUTO. Đảm bảo quy đổi deg/rad nếu tính toán sau này; hiện CLI dùng độ.

## 4. Lập kế hoạch chuyển động

- Chuyển động coordinated point-to-point: số xung từng axis khác nhau nhưng bắt đầu/kết thúc theo kế hoạch thời gian chung; profile velocity/acceleration cần được kiểm thử.
- Trước tiên implement pure calculation/profile function có unit tests, sau đó phát xung trên bàn test từng trục và mới phối hợp.
- Không chọn velocity/acceleration/backoff/timeout mặc định như thể đã được người dùng xác nhận. Có thể tạo defaults bảo thủ chỉ cho test/mocked mode, nhưng bất kỳ chuyển động phần cứng thật vẫn phải nhận approval và có limits đã thiết lập.
- Xử lý integer overflow, float NaN/Inf, mục tiêu ngoài giới hạn, pulses vượt giới hạn, queue đầy, cancel/abort và `position_valid=false`.

## 5. Giới hạn chuyển động

- J1/J2/J3 soft limits chưa đo. Không giả định `-90..90` hoặc các khoảng phổ biến.
- Không chạy MOVE/JOG đến khi angle limits của từng trục được cấu hình hợp lệ.
- Home switch là mốc tham chiếu, không bảo vệ toàn hành trình. Không thay hardware limit bằng soft limit như thể tương đương.
- Nếu bất kỳ sự kiện nào làm cho số xung không đại diện đáng tin cậy cho vị trí, invalidate position và yêu cầu homing.

## 6. FreeRTOS

FreeRTOS có thể dùng để chia tasks/queues: motion planner/controller, CLI/Serial, diagnostics, input monitoring. Nhưng tasks không tự tạo độ chính xác xung. Dùng timer/hardware pulse backend phù hợp và ưu tiên control over logging. Không thêm PID library chỉ vì user yêu cầu điều khiển ổn định; không có encoder thì chưa có feedback position.
