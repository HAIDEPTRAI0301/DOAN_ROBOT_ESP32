# Kế hoạch triển khai theo stage nhỏ

> **Thứ tự bắt buộc: hoàn thiện MCU A trước.** Mỗi stage làm xong phải báo cáo và dừng chờ. Không tự chuyển sang stage sau.

## Stage 0 — Audit project và thiết lập baseline

- Xác minh root, cây thư mục, `main/`, `CMakeLists.txt`, `sdkconfig`, `idf.py --version`, target board và build status.
- Không đổi code chức năng và không flash. Không mở project cũ.
- Báo file hiện có, file đặc tả root/nested, build thực tế và rủi ro.

## Stage 1 — Tạo scaffold motion controller C/H

- Dựa vào cây hiện có, đề xuất cấu trúc module nhỏ: state/config/diagnostics/CLI/input/axis/planner/homing/safety.
- Chỉ scaffold tối thiểu được duyệt; không thay toàn bộ project template một lượt.
- Có `robot_config.h` với commissioning flag mặc định khóa AUTO; chưa có calibration values hợp lệ.
- Build compile-only; chưa cấu hình motor real-run.

## Stage 2 — Serial diagnostics + đọc Home switch (không motor)

- Serial banner có board ID, SDK/version, current state và config validity.
- Đọc ba input, debounce, hiển thị raw/stable state và test nhấn/nhả.
- Không phát xung STEP. Xác minh logic NO COM→GND/NO→GPIO theo mạch thực.
- Test parser chỉ cho `HELP`, `STATUS` ở stage này; lệnh motion chưa enable.

## Stage 3 — Xác minh phần cứng và phát xung test một trục

- Trước tiên review TB6600 đúng model, 3.3 V input compatibility, current DIP, nguồn, dây và phương tiện ngắt động lực.
- Tạo mock/unit test phép phát xung; sau approval, bench-test một trục ở tần số thấp, biên độ nhỏ.
- Xác nhận DIR và STEP polarity/width từ datasheet đúng module; không tự đổi wiring.
- Không thử cả ba trục cùng lúc ở stage này.

## Stage 4 — Homing an toàn cho từng trục riêng

- Bắt đầu từng trục, xác minh hướng tới Home và hướng rời Home.
- Implement state machine 2-stage: seek → backoff/clear → slow re-approach.
- Có switch debounce, timeout, max pulse, stuck/no-release fault; không tự backoff khi hướng chưa được xác minh.
- Vẫn khóa AUTO.

## Stage 5 — Homing tuần tự J2 → J3 → J1

- Ghép ba quy trình single-axis đã test.
- Kiểm tra trạng thái switch ban đầu, timeout và fault latch giữa trục.
- Không triển khai auto-home khi commissioning flag còn false; lệnh HOME thủ công chỉ trong điều kiện được phê duyệt.

## Stage 6 — Hiệu chuẩn góc-xung và soft limits

- Xác minh tỉ số truyền, góc tham chiếu Home, pulse-per-degree và hướng dương từng trục bằng đo thực tế.
- Đo giới hạn góc cơ khí. Không dùng giới hạn mặc định giả định.
- Viết `robot_positions.h`; PICK/PLACE chỉ valid sau khi người dùng hiệu chuẩn/duyệt.
- Unit tests cho deg↔steps, offset, limits, round/overflow, values NaN/Inf.

## Stage 7 — Bộ điều khiển vị trí và profile đồng bộ

- Tạo planner phối hợp 3 trục với acceleration/deceleration.
- Trước hardware, test offline/mock nhiều trường hợp: axis delta=0, trục ngắn/dài, chiều âm/dương, limit, cancel, timeout.
- Xác minh pulse timing và không blocking vì Serial/logging.
- Chưa bật AUTO.

## Stage 8 — CLI Serial commissioning

- Cú pháp đề xuất: `HELP`, `STATUS`, `HOME`, `JOG`, `MOVE`, `RESET_FAULT`.
- Strict parser, reject malformed/extra values, no move while busy/fault/not-homed/config-invalid.
- Lệnh không được bypass interlocks. `RESET_FAULT` chỉ acknowledge sau khi nguyên nhân đã xóa; không tự động move/home.

## Stage 9 — Commissioning cơ khí và xác nhận cấu hình

- Chỉ sau khi user cho phép hardware test: xác nhận home offsets, limits, max velocity/acceleration, PICK/PLACE và pump/conveyor interfaces (các phần sau này).
- Cài lại các cờ calibration/safety chỉ khi người dùng xác nhận đã đo/xác minh.
- E-stop độc lập phải lắp và test trước AUTO không giám sát.

## Stage 10 — AUTO trên MCU A

- Mở theo `robot_config.h` flag sau commissioning approval; boot chờ 5 s, self-check, homing J2→J3→J1, rồi AUTO chỉ khi tất cả gates hợp lệ.
- Đây là bước sau; không thực hiện tự động trong yêu cầu hiện tại nếu người dùng chưa ra lệnh.

## Stage 11 — Tích hợp MCU B và MCU C (chưa làm hiện tại)

- Giao thức UART A↔B, ACK/status/sequence/watchdog, fail-state.
- B sensor/belt/pump state machine; C camera classification + matching object.
- Test fake object stream, stale/no classification, single pending slot, UART disconnect/reconnect; sau đó nghiệm thu phần cứng có kiểm soát.

## Exit criteria mọi stage

- Nêu chính xác file đổi; `idf.py build`/unit test/mock đã chạy thực tế nếu có.
- Phân biệt rõ chưa test, test simulator, test board và test với cơ cấu thật.
- Ghi open item mới vào `OPEN_ITEMS.md`; không tự quyết thông số còn thiếu.
- Dừng, chờ người dùng.
