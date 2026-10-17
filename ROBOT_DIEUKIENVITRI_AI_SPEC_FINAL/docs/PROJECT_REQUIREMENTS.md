# Yêu cầu dự án

## 1. Mục tiêu

Xây dựng firmware điều khiển vị trí một cánh tay robot 3 bậc tự do dùng ESP32-S3 và 3 driver TB6600 cho 3 motor bước. Làm firmware motion trước; sau khi ổn định mới tích hợp Process Controller và camera. Ưu tiên tính đúng đắn, có thể kiểm thử, dễ bảo trì, chia file C/H, không viết một file chứa toàn bộ logic.

## 2. Phạm vi giai đoạn hiện tại

**Trong phạm vi:**
- Project mới tại `D:\DOAN_ROBOT_IDF\ROBOT_DIEUKIENVITRI`.
- ESP-IDF, C, VS Code + Antigravity.
- GPIO/limit input diagnostics; STEP/DIR driver; homing; bộ đếm vị trí open-loop; quy đổi góc–xung; JOG tương đối và MOVE tuyệt đối qua Serial; profile chuyển động đồng bộ; fault latch; cấu hình vị trí và cờ commissioning.
- Serial Monitor dùng để chẩn đoán và thử trong commissioning.

**Chưa trong phạm vi:**
- Firmware đầy đủ cho MCU B, firmware ESP32-CAM, phân loại ảnh, băng tải, bơm, tích hợp UART giữa tất cả board.
- Web, GUI, Python, Wi-Fi/cloud.
- PID vị trí kín khi chưa có encoder; điều khiển Cartesian XYZ/IK trong giai đoạn đầu.
- Tự chạy cơ khí thật mà chưa qua nghiệm thu và chưa được người dùng cho phép.

## 3. Mô hình phần cứng cấp hệ thống

1. **MCU A — ESP32-S3 Motion Controller:** 3 motor cánh tay, 3 TB6600, 3 Home switch; hiện phát triển trước.
2. **MCU B — Process Controller:** board người dùng gọi là ESP32 Node32S/ESP32-S3; cảm biến NPN, một TB6600 riêng cho động cơ bước băng tải, L298N điều khiển bơm 12 V; tương lai giao tiếp A.
3. **MCU C — ESP32-CAM:** xử lý ảnh/phân loại vật; kết quả phân loại phải gắn đúng vật và đến B trước khi vật đến cảm biến NPN.

Tổng cộng 4 TB6600: 3 cánh tay + 1 băng tải. Tên/model chính xác MCU B và giao tiếp C–B cần xác minh.

## 4. Chu trình gắp đặt cấp hệ thống đã chốt

Sau khi hệ thống được nghiệm thu và vào AUTO:

1. Băng tải chạy liên tục.
2. C nhận diện/phân loại vật ở phía trước cảm biến NPN; B phải có kết quả phân loại hợp lệ tương ứng với đúng vật.
3. Khi vật đến cảm biến NPN:
   - Có kết quả phân loại hợp lệ tương ứng: B giảm tốc/dừng băng tải và phối hợp với A để gắp.
   - Không có kết quả phân loại hợp lệ: không dừng vì vật đó, không tạo lệnh gắp; cho vật đi qua.
4. A đến vị trí gắp cố định; B bật bơm qua L298N và chờ thời gian hút cấu hình được (thời lượng chưa chốt).
5. Khi vật được lấy khỏi vùng cảm biến và tín hiệu không-phát-hiện ổn định qua debounce, B cho băng tải chạy lại ngay, kể cả khi A đang mang vật đi đặt.
6. A đến vị trí thả cấu hình được; B tắt bơm để nhả vật; A trở về vị trí gắp.
7. Nếu một vật đã phân loại hợp lệ khác đến cảm biến khi A còn bận, B dừng băng tải và giữ tối đa một yêu cầu chờ; không gửi lệnh chuyển động chồng lấn. Chỉ xử lý yêu cầu chờ sau khi A hoàn tất chu trình trước và báo sẵn sàng.

Nếu cảm biến không clear sau khi vật được gắp, hết timeout, camera/classification link hỏng hoặc vật chưa rời vùng cảm biến thì cần policy lỗi an toàn trong giai đoạn tích hợp; không tự đoán.

## 5. Motion Controller A

- Khởi động chờ 5 giây, self-check và kiểm tra cấu hình/an toàn.
- Homing khi đã bật commissioning-complete và đủ điều kiện: J2 → J3 → J1, mỗi trục homing hai giai đoạn.
- Commissioning ban đầu khóa AUTO. Sau hiệu chuẩn, người dùng đổi cờ trong `robot_config.h`, Build/Flash; boot kế tiếp chờ 5 giây, kiểm tra an toàn, Home, sau đó AUTO nếu mọi interlock hợp lệ.
- Hỗ trợ `JOG` tương đối (độ) và `MOVE` tuyệt đối (độ) qua Serial trong commissioning; cú pháp cuối cùng được ghi trong thiết kế giao thức/CLI trước khi code.
- Ba trục đi đến bộ góc đích theo chuyển động phối hợp đồng bộ có gia tốc/giảm tốc. Homing vẫn tuần tự.
- `PICK` cố định và `PLACE` thay đổi được, lưu trong `robot_positions.h`. Không nhập giá trị giả định. Hiện chưa có góc thật nên AUTO bị khóa.
- Không có encoder: không dùng PID vị trí closed-loop; vị trí ước lượng từ xung, phải invalid khi xảy ra sự kiện có thể làm mất vị trí.

## 6. Lỗi

- Fault latch: dừng phát lệnh chuyển động có kiểm soát nếu có thể, ghi lỗi lên Serial, không tự chạy lại.
- E-stop chưa lắp. Không được tuyên bố đã có bảo vệ E-stop. AUTO không giám sát trên robot thật bị khóa cho đến khi có mạch ngắt động lực độc lập đã thử nghiệm.
- Khi UART A–B về sau mất trong chu trình: A dừng có kiểm soát và khóa lỗi; B dừng băng tải, giữ bơm nếu đang giữ vật; log cục bộ hai board; không tự resume.

## 7. Chất lượng

- Chia module theo trách nhiệm; dùng FreeRTOS/state machine có mục đích rõ ràng; bộ phát xung không được làm nghẽn bởi printf/log/Serial.
- Dùng dry-run/mock/unit tests cho phép tính xung, giới hạn góc, profile và state machine trước phần cứng.
- Mỗi stage có báo cáo file đổi, build/test đã chạy thật và các mục còn thiếu.
