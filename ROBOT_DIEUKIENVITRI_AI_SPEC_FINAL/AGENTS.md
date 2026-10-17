# AGENTS.md — Quy tắc dự án ROBOT_DIEUKHIENVITRI

> **Đọc file này trước mọi công việc.** Project root dự kiến: `D:\DOAN_ROBOT_IDF\ROBOT_DIEUKHIENVITRI`. Đây là đặc tả cho AI Agent, không phải firmware đã được build hoặc kiểm thử trên robot.

## 1. Phạm vi hiện tại

- Hệ thống đích có **3 bộ điều khiển**: (A) ESP32-S3 điều khiển vị trí cánh tay robot; (B) ESP32-S3/board người dùng gọi là ESP32 Node32S điều khiển cảm biến, băng tải và bơm; (C) ESP32-CAM xử lý hình ảnh/phân loại vật.
- **Giai đoạn đang làm: chỉ phát triển firmware của bộ điều khiển vị trí A.** Không triển khai firmware B/C hoặc giao thức tích hợp hoàn chỉnh trừ khi người dùng yêu cầu riêng.
- ESP-IDF, C (`.c`, `.h`), VS Code và Antigravity. Không tạo web, GUI, Python app hoặc network service trong phạm vi hiện tại.
- Serial Monitor là giao diện thử nghiệm/commissioning ban đầu. Motion controller phải tách khỏi phương tiện nhận lệnh để sau này tích hợp UART với B.
- Project cũ `D:\DOAN_ROBOT_IDF\ROBOT_LON\DOAN_ROBOT` nằm ngoài phạm vi. Không sửa, di chuyển, xóa, ghi đè hoặc lấy lại code từ đó nếu chưa được người dùng cho phép rõ.

## 2. Quy tắc đọc tài liệu để tiết kiệm token

1. Mỗi tác vụ luôn đọc `AGENTS.md`.
2. Sau đó đọc **chỉ** tài liệu liên quan trong `docs/`. Đụng phần cứng/an toàn/thông số thì bắt buộc đọc `docs/OPEN_ITEMS.md` và `docs/HARDWARE_CONFIGURATION.md`; bắt đầu/tiếp tục stage thì đọc `docs/IMPLEMENTATION_PLAN.md`.
3. Chỉ đọc toàn bộ `docs/` nếu thay đổi kiến trúc, rà soát tổng thể hoặc phát hiện mâu thuẫn tài liệu.
4. Không yêu cầu model phân tích lại toàn bộ dự án trong mỗi tác vụ nhỏ. Dùng báo cáo bàn giao của stage trước và kiểm tra đúng file liên quan.
5. Không tạo/đổi một file quy chuẩn lặp lại thông tin khác với nguồn chuẩn. Nếu phát hiện mâu thuẫn, dừng và báo cáo thay vì tự chọn một giá trị.

## 3. Không được tự ý thay đổi

Phải xin phép trước khi đổi GPIO/dây/mức logic, trình tự hoặc chiều homing, vi bước/dòng/nguồn, tỷ số truyền, giao thức/hành vi đã chốt, cấu trúc MCU, API public, file ngoài stage, SDK/toolchain, hoặc thêm web/GUI/Python. Không xóa/đổi tên/di chuyển file. Không tự điền thông số cơ khí hay góc vị trí còn thiếu.

**Cấm flash firmware, cấp lệnh cho motor chạy thật hoặc bật AUTO nếu chưa có sự cho phép rõ ràng trong lượt làm việc đó.** Build và unit/mock test cũng phải được báo cáo trung thực; không nói đã chạy nếu chưa chạy.

## 4. Kiến trúc cấp hệ thống đã thống nhất

- **A — Motion Controller (đang làm trước):** 3 motor bước cánh tay qua 3 TB6600; STEP/DIR; homing; góc tham chiếu; quy đổi góc–xung; chuyển động phối hợp có tăng/giảm tốc; trạng thái vị trí; vị trí gắp/thả.
- **B — Process Controller (giai đoạn sau):** đọc cảm biến NPN; điều khiển động cơ bước băng tải qua TB6600 thứ tư; bật/tắt bơm chân không 12 V qua L298N; điều phối chu trình; UART tới A.
- **C — ESP32-CAM (giai đoạn sau):** xử lý ảnh/phân loại vật và gửi kết quả cho B. Đã chọn thiết bị, nhưng đường truyền/format giữa C và B vẫn cần xác nhận trước khi triển khai.
- Tổng số driver đã chốt: **4 TB6600** — 3 cho cánh tay (A), 1 cho băng tải (B). Thông số driver/motor băng tải chưa được xác minh.
- Serial log: mỗi board có log cục bộ. Khi đường A↔B hoạt động, B có thể chuyển tiếp một phần log A gắn nhãn `MOTION_A`; forwarding chỉ hỗ trợ chẩn đoán, không phải đường log duy nhất.

## 5. Hành vi vị trí cánh tay đã thống nhất

- Ba khớp: J1 đế, J2 vai, J3 khuỷu. GPIO đã chỉ định trong `docs/HARDWARE_CONFIGURATION.md`.
- Đợi 5 giây sau boot, rồi thực hiện kiểm tra cấu hình/an toàn. Nhưng mặc định project mới ở **COMMISSIONING**, chưa tự homing hoặc AUTO không giám sát cho đến khi điều kiện commissioning và phần cứng an toàn được xác minh.
- Khi commissioning hoàn tất, người dùng thay cờ trong `robot_config.h`, Build/Flash; lần khởi động tiếp theo chờ 5 giây, kiểm tra an toàn, homing **J2 → J3 → J1**, rồi vào AUTO chỉ khi mọi cổng an toàn đều hợp lệ.
- Homing hai giai đoạn: tìm switch, lùi ra, tiếp cận lần hai chậm hơn; có debounce, timeout, giới hạn xung và fault latch.
- Chiều tìm Home theo mô tả cơ khí: J1 quay cùng chiều kim đồng hồ; J2 nâng cánh tay; J3 duỗi cánh tay. Không quy đổi sang DIR HIGH/LOW nếu chưa bench-test đúng chiều và chưa xác định hướng nhìn cho J1.
- Home switch loại NO; COM→GND, NO→GPIO; dự kiến pull-up: nhả=HIGH, nhấn=LOW. Phải xác minh bằng chẩn đoán GPIO/Serial trước khi motor chuyển động.
- Vị trí gắp cố định; vị trí thả cấu hình trong `robot_positions.h`. Không điền góc giả định. Có cả lệnh thử góc tương đối `JOG` và góc tuyệt đối `MOVE`; chỉ cho phép khi homing/hiệu chuẩn/commissioning state phù hợp.
- Chuyển động giữa vị trí: phối hợp đồng bộ 3 trục có profile tăng tốc/giảm tốc. Điều đó không đồng nghĩa đầu hút đi theo đường thẳng XYZ.
- Chưa có encoder góc liên tục. Vị trí là ước lượng open-loop từ số xung đã phát; không giả lập PID vị trí kín. Nếu mất bước/reset/gián đoạn làm mất độ tin cậy vị trí, cần homing lại.

## 6. Chính sách lỗi và an toàn

- Fault latch: dừng phát lệnh chuyển động (decelerate có kiểm soát nếu còn khả năng), hủy chu trình, ghi mã lỗi và in Serial; không tự restart.
- Lỗi/mất UART A↔B khi tích hợp: A dừng có kiểm soát và khóa lỗi; B dừng băng tải; B giữ bơm bật nếu đang giữ vật. Sau khôi phục không tự tiếp tục; xác minh trạng thái và Home lại nếu vị trí không đáng tin cậy.
- Khi bơm đang giữ vật, không tự tắt bơm trong xử lý lỗi nếu có thể làm rơi vật. Reset/mất nguồn B có thể làm mất lực hút; phần cứng để bảo đảm giữ vật chưa được thiết kế/xác minh.
- E-stop vật lý hiện **chưa lắp**. Không cho AUTO không giám sát trên robot thật cho đến khi có phương tiện ngắt động lực độc lập và đã kiểm tra. GPIO E-stop chưa được gán.
- Không nối trực tiếp tín hiệu cảm biến NPN công nghiệp 12/24 V vào GPIO. Chưa triển khai B trước khi xác minh cách giao tiếp điện. Không mặc định input mọi module TB6600 tương thích trực tiếp với GPIO 3.3 V.

## 7. Quy trình mỗi stage

Trước khi làm: báo mục tiêu, file dự kiến tạo/sửa, tài liệu liên quan và rủi ro. Chỉ làm đúng một stage. Sau đó báo file đổi, lệnh build/test đã chạy thật, kết quả, mục chưa xác minh và bước tiếp theo; rồi dừng chờ người dùng. Không flash/chạy motor nếu chưa được phép. Xem `docs/CHANGE_CONTROL.md` để biết quy trình đầy đủ.
