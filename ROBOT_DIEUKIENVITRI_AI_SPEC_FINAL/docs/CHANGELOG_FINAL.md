# Change log — consolidated spec

## FINAL-CONSOLIDATED-2026-10-16

- Tổng hợp các quyết định từ các lượt hỏi đáp tới khi người dùng yêu cầu dừng câu hỏi ở câu 54.
- Sửa phạm vi: 3 bộ điều khiển (Motion A, Process B, ESP32-CAM C), nhưng implementation hiện tại chỉ làm A.
- Nhấn mạnh băng tải chỉ được bật khi whole system ready; vật không có classification hợp lệ từ camera phải đi qua, không pick.
- Khi sensor clear sau khi pickup, B cho băng tải chạy lại ngay, kể cả khi A còn đang mang vật đi đặt.
- Nếu object hợp lệ tiếp theo đến khi A bận, B dừng belt và lưu tối đa một pending object; không motion overlap.
- Thêm câu hỏi chưa trả lời về switch Home bị nhấn ngay khi boot; quy định mặc định không tự backoff theo hướng chưa xác minh.
- Thêm gate E-stop phần cứng độc lập, commissioning lock, local Serial logs, token-efficient document reading, no unapproved motor tests.
- Đây là tài liệu thiết kế; không có thay đổi firmware/hardware nào đã thực hiện.
