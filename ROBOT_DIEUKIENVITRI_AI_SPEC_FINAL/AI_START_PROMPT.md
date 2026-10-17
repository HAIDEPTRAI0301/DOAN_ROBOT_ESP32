# Prompt khởi động dành cho Antigravity

Đọc `AGENTS.md` trước. Xác định stage hiện tại từ `docs/IMPLEMENTATION_PLAN.md`. Chỉ đọc những tài liệu cần cho stage; nếu đụng phần cứng/thông số/an toàn, đọc `docs/OPEN_ITEMS.md` và `docs/HARDWARE_CONFIGURATION.md`.

Phạm vi hiện tại chỉ là firmware ESP-IDF điều khiển vị trí cho ESP32-S3 A. Chưa triển khai Process Controller B, ESP32-CAM, web, GUI hay Python. Không lấy code từ project cũ, không tự đổi GPIO/cơ cấu/logic đã chốt, không xóa/đổi tên/di chuyển file, không tự điền góc hoặc thông số cơ khí chưa xác minh.

Trước khi thay đổi, hãy báo:
1. Mục tiêu của stage.
2. File dự định tạo/sửa và lý do.
3. Tài liệu liên quan đã đọc.
4. Các thông số còn thiếu/rủi ro và cách tránh giả định.

Chỉ thực hiện một stage. Có thể kiểm tra mã và chạy build/mock tests khi phù hợp; ghi chính xác lệnh và kết quả thực tế. Không flash firmware hoặc cho motor di chuyển thật nếu chưa được tôi cho phép rõ ràng trong lượt làm việc này. Khi hoàn thành, báo các file đổi, build/test, open items và đề xuất stage kế tiếp; sau đó dừng chờ.
