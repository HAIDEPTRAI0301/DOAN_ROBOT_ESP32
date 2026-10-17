# UART protocol — bản dự thảo, chưa được phép triển khai như spec cuối

## 1. Các link

- **A ↔ B:** UART hai chiều cho lệnh motion, ACK/accepted, running, done, error, heartbeat và trạng thái. Pins/baud/protocol chưa chốt.
- **C → B:** truyền kết quả phân loại/object identity. Trước khi triển khai phải xác nhận interface cuối cùng; UART là phương án được đề xuất trước khi người dùng tổng kết kiến trúc 3 MCU, nhưng chưa chốt hoàn toàn sau thay đổi kiến trúc.

## 2. Các trường dữ liệu phải có

- `protocol_version`
- `message_type`
- `sequence_id`/`command_id`
- `source_id` và `destination_id`
- `payload` có schema/version rõ
- `result/status` và mã lỗi nếu có
- Kiểm tra độ dài, ký tự/format, integrity (checksum/CRC tùy thiết kế)

Không được gửi raw command string thiếu kiểm tra và lập tức chạy motor. Cần parser framing (ví dụ newline-delimited JSON hoặc binary framing), validation, timeout, duplicate command handling và queue giới hạn. Format cuối sẽ được chọn sau khi kiểm tra RAM/tài nguyên và yêu cầu serial.

## 3. A–B handshake

B chỉ phát motion command khi A đang ready và position/config valid. A trả lời `ACCEPTED` hoặc `REJECTED`; sau đó `RUNNING`, rồi `DONE` hoặc `ERROR`. B phải phân biệt ACK tiếp nhận với báo đã hoàn thành chuyển động. Command lặp cùng ID không được thực thi hai lần. Không cho chuyển động mới khi axis planner đang chạy hoặc state không phù hợp.

## 4. Mất kết nối

- Timeout heartbeat/ACK phải có ngưỡng cấu hình được sau khi đo link thực tế; hiện chưa chốt con số.
- Khi timeout trong motion, A latch fault và invalidates position nếu cần; B dừng belt và giữ vacuum nếu đang nắm vật. Không auto-resume khi link trở lại.
- Cả hai board ghi log cục bộ; forwarding A→B chỉ là tiện ích chẩn đoán.

## 5. ESP32-CAM object result

- Result phải xác định được class validity, object/event ID hoặc mapping cơ học đủ tin cậy để ghép với đúng object tại sensor, timestamp/sequence và expiration policy.
- Result không có, hết hạn, đã consumed hoặc không ghép được đúng vật: vật đi qua, không dừng băng tải và không tạo pick request.
- Chưa chốt giao thức, format phân loại, pin, baud, hoặc cơ chế đo khoảng cách/thời gian từ camera đến sensor. Không tự gán.
