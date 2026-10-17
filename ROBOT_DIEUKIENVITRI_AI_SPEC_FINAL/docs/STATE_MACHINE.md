# State machine và quy trình

## 1. Motion Controller A — state đề xuất

`BOOT` → `STARTUP_DELAY` (5 s) → `SELF_CHECK` → một trong các trạng thái:

- `COMMISSIONING_LOCKED`: mặc định của firmware mới. Không AUTO. Cho phép chẩn đoán không chuyển động; lệnh JOG/HOME chỉ sau khi các kiểm tra liên quan được duyệt và người dùng chủ động gọi.
- `HOMING_J2` → `HOMING_J3` → `HOMING_J1`: chỉ khi cờ commissioning-complete hợp lệ và interlock đạt.
- `READY`: homing thành công, vị trí được xem là tham chiếu hợp lệ.
- `MOVING`: thực hiện lệnh mục tiêu đã kiểm tra; motion planner phối hợp ba trục với profile acceleration/deceleration.
- `AUTO_READY`: chỉ khi commissioning hoàn tất, vị trí PICK/PLACE hợp lệ, giới hạn hành trình và phần cứng an toàn đã xác minh; nhận lệnh chu trình từ B ở giai đoạn tích hợp.
- `FAULT_LATCHED`: lỗi; không tự tiếp tục.
- `RECOVERY_REQUIRED`: cần xác nhận xử lý và có thể Home lại.

Tên state mang tính đề xuất. Giữ state machine rõ ràng, không dùng nhiều boolean mâu thuẫn làm thay thế state chính.

## 2. Chế độ commissioning

- Cấu hình ban đầu phải khóa AUTO (ví dụ `ROBOT_CALIBRATION_COMPLETE = false` trong `robot_config.h`).
- Trong commissioning, kiểm tra GPIO Home, chiều DIR và pulse output từng trục ở tốc độ thấp, biên độ nhỏ, chỉ theo lệnh chủ động. Không tự động cho motor di chuyển ngay sau boot.
- Sau khi người dùng đo xác nhận home offsets, giới hạn góc, tỷ số/steps-per-degree, PICK/PLACE và kiểm tra phần cứng an toàn, người dùng đổi cờ, Build và Flash.
- Boot sau khi đã hoàn tất commissioning vẫn chờ 5 giây, self-check, tự homing tuần tự; chỉ vào AUTO khi mọi interlock đạt. E-stop chưa lắp hiện là blocker cho AUTO không giám sát trên robot thật.

## 3. Homing hai giai đoạn cho từng trục

1. Xác minh input switch khởi tạo ổn định và không có lỗi.
2. Giai đoạn tìm: hướng cơ khí đã được xác minh, tốc độ giới hạn, số xung/timeouts giới hạn.
3. Khi switch được debounce thành active: dừng phát xung.
4. Lùi khỏi switch đến khi switch không-active ổn định.
5. Tiếp cận lần hai chậm hơn.
6. Khi switch active ổn định: dừng, gán mốc switch/offset đã hiệu chuẩn, ghi nhận homed.
7. Chuyển khớp theo J2 → J3 → J1.
8. Bất kỳ switch timeout/stuck/no-release/mâu thuẫn nào → FAULT_LATCHED, in state/error ra Serial.

**Chưa trả lời:** nếu switch đang bị nhấn ngay khi boot thì có tự backoff hay khóa lỗi. Hành vi mặc định an toàn là không tự đoán chiều backoff; chỉ cho lùi tự động sau khi đã xác minh chiều rời switch trên trục đó và được chấp thuận. Nếu chưa xác minh thì khóa/đợi thao tác commissioning.

## 4. Move/JOG

- `JOG`: mục tiêu tương đối theo độ từ estimated joint angle hiện tại.
- `MOVE`: mục tiêu tuyệt đối theo độ, dựa vào home offset/calibration.
- Trước move: parse toàn bộ lệnh, kiểm tra finite number, limits, homed/position-valid, state, planner idle, profile hợp lệ; chỉ thực thi nếu tất cả hợp lệ.
- Các trục chạy theo profile phối hợp đồng bộ; giới hạn velocity/acceleration là cấu hình chưa điền cho tới khi thử.
- Khi hoàn thành, cập nhật step counter và báo hoàn tất; không được tuyên bố actual angle đo được vì không có encoder.
- Khi interrupted/limit unexpected/position uncertain: invalidate position và yêu cầu Home.

## 5. Quy trình tự động tương lai — B điều phối, A chạy motion

### Camera gate

- C phân loại phía trước sensor và gửi một result liên kết được với đúng object.
- Sensor có cạnh detect nhưng không có classification hợp lệ tương ứng: **không dừng vì object đó, không pick request; để object đi qua**.
- Có class hợp lệ khớp đúng object, sensor detect stable: B dừng băng tải có kiểm soát và yêu cầu A đi tới PICK.

### Pick/place cycle

1. A xác nhận sẵn sàng; B chạy băng tải.
2. Class hợp lệ + sensor detect ổn định → B dừng băng tải; gửi pick request cho A.
3. A tới PICK; B bật bơm, đợi vacuum delay đã cấu hình.
4. Khi object được lấy khỏi vùng sensor và `NO_DETECT` ổn định qua debounce, B chạy lại băng tải ngay — không cần chờ A hoàn thành đặt vật.
5. A đến PLACE; B tắt bơm; A trở lại PICK và báo ready.
6. B chờ object tiếp theo.

### Object tiếp theo khi A còn bận

- Nếu một object mới có class hợp lệ đến sensor trong lúc A còn bận, B dừng băng tải, ghi tối đa một pending request; không gửi move chồng lấn.
- Chỉ giao pending request khi cycle trước hoàn tất, A đã trở lại PICK và xác nhận ready.
- Nếu pending slot đã đầy hoặc kết quả class/object mapping không hợp lệ, policy chưa được chốt; không tự mở rộng queue, không tự đoán tiếp tục hay loại bỏ object.

## 6. UART loss giữa A–B (giai đoạn tích hợp)

- Timeout/heartbeat fail khi A đang chuyển động: A dừng có kiểm soát nếu task/hardware còn phản hồi, invalid position nếu không bảo đảm biết vị trí, latch fault.
- B dừng băng tải, latch fault, giữ bơm bật nếu đang giữ object và output vẫn hoạt động.
- Không tự resume khi UART hồi phục. In log ở cả Serial cục bộ; yêu cầu thao tác recovery và Home lại nếu vị trí mất tin cậy.
- Nếu board B reset/mất nguồn, bơm có thể mất điện; chưa có phần cứng bảo đảm giữ vật. Không tuyên bố firmware đã giải quyết rủi ro vật lý này.

## 7. Serial logging và lệnh dự kiến

Log cục bộ của A có uptime, board ID `MOTION_A`, level, state/event, error code, sequence ID nếu liên quan. Những event chính: `BOOT`, `STARTUP_DELAY`, `SELF_CHECK`, `HOMING_J2/J3/J1`, `MOVE_START/DONE`, `POSITION_INVALID`, `FAULT`, `RECOVERY_REQUIRED`.

Lệnh commissioning dự kiến: `STATUS`, `HOME`, `JOG`, `MOVE`, `RESET_FAULT`, `HELP`. Cú pháp cuối cùng phải được định nghĩa và kiểm tra parser trước implementation. `RESET_FAULT` không được tự Home hoặc chạy move. `JOG/HOME/MOVE` bị khóa nếu chưa đủ điều kiện và phải có giới hạn timeout/pulse.
