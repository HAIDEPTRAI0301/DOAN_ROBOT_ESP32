# ROBOT_DIEUKIENVITRI — Bộ đặc tả tổng hợp cho Antigravity/AI Agent

**Bản tổng hợp:** `FINAL-CONSOLIDATED-2026-10-16`  
**Project root:** `D:\DOAN_ROBOT_IDF\ROBOT_DIEUKIENVITRI`  
**Phạm vi trước mắt:** firmware ESP-IDF của bộ điều khiển vị trí cánh tay robot (MCU A) בלבד.

## Điểm bắt đầu

1. Đặt `AGENTS.md` ở **thư mục gốc project**, ngang cấp với `CMakeLists.txt` và `main/`.
2. Đặt `README.md` ở cùng thư mục gốc.
3. Chép thư mục `docs/` vào cùng cấp. Không đặt `AGENTS.md` chỉ bên trong thư mục tài liệu con.
4. Mỗi yêu cầu, AI đọc `AGENTS.md` rồi đọc theo tác vụ; không cần đọc lại toàn bộ tài liệu cho mọi việc nhỏ.
5. Bắt đầu tại `docs/IMPLEMENTATION_PLAN.md`, Stage 0. Không flash hoặc chạy motor thật khi chưa được người dùng cho phép.

Ảnh màn hình trước đó cho thấy project đã có `.vscode/`, `.devcontainer/`, `main/`, `CMakeLists.txt` và một thư mục đặc tả cũ tên `ROBOT_DIEUKIENVITRI_AI_SPEC/`. Hãy đặt bộ mới tại **root của project**, không để bộ tài liệu hoạt động chỉ ở thư mục con lồng bên trong. Giữ nguyên file firmware và cấu hình hiện có; chỉ thay tài liệu theo bộ tổng hợp sau khi đã sao lưu/kiểm tra. Không xóa thư mục cũ nếu chưa được người dùng cho phép.

## Các tài liệu

- `AGENTS.md`: quy tắc cốt lõi mà AI phải tuân thủ.
- `docs/PROJECT_REQUIREMENTS.md`: yêu cầu và phạm vi hệ thống.
- `docs/ARCHITECTURE.md`: phân công 3 bộ điều khiển và ranh giới trách nhiệm.
- `docs/HARDWARE_CONFIGURATION.md`: GPIO, truyền động và thông số đã biết/chưa xác minh.
- `docs/STATE_MACHINE.md`: trạng thái dự kiến cho motion controller và logic tích hợp sau này.
- `docs/MOTION_CONTROL_DESIGN.md`: mô-đun điều khiển vị trí, homing, profile chuyển động và open-loop.
- `docs/UART_PROTOCOL_DRAFT.md`: nguyên tắc giao thức dự thảo; không phải giao thức đã chốt để implement.
- `docs/CHANGE_CONTROL.md`: quyền sửa đổi và phê duyệt.
- `docs/OPEN_ITEMS.md`: các mục chưa xác minh, bao gồm câu hỏi chưa trả lời.
- `docs/IMPLEMENTATION_PLAN.md`: kế hoạch stage, chỉ bắt đầu với MCU A.
- `docs/COMMISSIONING_CHECKLIST.md`: cổng an toàn và kiểm tra nghiệm thu.
- `docs/DECISIONS_LOG.md`: các quyết định đã thống nhất và những điều không được tự suy luận.
- `AI_START_PROMPT.md`: mẫu prompt ngắn dùng khi giao việc cho Antigravity.

## Trạng thái

Đây là **tài liệu yêu cầu/thiết kế**, không phải firmware đã biên dịch, chạy, hoặc được xác nhận an toàn. Các thông số trong `OPEN_ITEMS.md` không được biến thành giá trị code giả định. Bộ tài liệu ưu tiên độ chính xác, phạm vi nhỏ và tiết kiệm token; chỉ tạo firmware sau khi đã đọc quy tắc và bắt đầu stage phù hợp.
