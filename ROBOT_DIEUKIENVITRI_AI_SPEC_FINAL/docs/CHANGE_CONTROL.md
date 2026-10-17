# Change control — kiểm soát sửa đổi

## 1. Trước khi sửa

AI phải ghi trong câu trả lời:
- Stage và mục tiêu;
- files dự định tạo/sửa;
- logic/phần cứng bị ảnh hưởng;
- tài liệu liên quan đã đọc;
- test dự kiến;
- rủi ro/open items.

Không bắt đầu sửa nếu scope chưa rõ hoặc cần đổi quyết định đã chốt. Hỏi người dùng trước thay vì tự mở rộng phạm vi.

## 2. Được phép theo stage

Có thể tạo/sửa file nội bộ trong stage đã được duyệt nếu nó không thay đổi GPIO/hardware/public behavior đã chốt. Giữ thay đổi nhỏ, có thể review, build/test mock được. Không thay toàn bộ `main.c` bằng một kiến trúc khác mà chưa kiểm kê code/file hiện tại.

## 3. Bắt buộc xin phép trước

- Thay GPIO, dây, logic polarity, nguồn, dòng, DIP, microstep, ratio hoặc cơ khí.
- Thay thứ tự/chiều homing, pump policy, conveyor/camera behavior, queue policy hoặc state transitions đã chốt.
- Đổi giao thức, pin hoặc board; thêm dependency lớn; thay API/public interface ngoài phạm vi.
- Xóa/đổi tên/di chuyển file, thay C/C++ direction, thêm web/GUI/Python/Wi-Fi, thay SDK/toolchain hoặc chỉnh system environment.
- Flash, vận hành motor thật, chuyển sang AUTO hoặc tự khởi động chu trình.
- Bỏ safety gate, timeout, fault latch hoặc commissioning lock.

## 4. Quy tắc file

- Không chạm project cũ `D:\DOAN_ROBOT_IDF\ROBOT_LON\DOAN_ROBOT`.
- Project mới cần giữ `CMakeLists.txt`, `sdkconfig`, `.vscode`, `.devcontainer`, `main/` và các file khác sau khi inspect; không ghi đè chỉ vì muốn dựng lại project mẫu.
- `AGENTS.md` có hiệu lực ở root. Bản spec cũ lồng trong `ROBOT_DIEUKIENVITRI_AI_SPEC/` có thể gây nhầm: không xóa nó tự động; báo cho người dùng để quyết định lưu trữ/xóa sau khi xác nhận root docs mới.

## 5. Hoàn tất stage

Báo danh sách file thêm/sửa, tóm tắt từng sửa đổi, lệnh build/test **đã thực sự chạy**, kết quả và lỗi. Phân biệt compile/test mock với test hardware. Đưa các giá trị chưa xác minh vào `OPEN_ITEMS.md`. Dừng sau stage, chờ yêu cầu tiếp theo.
