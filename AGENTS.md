# Quy tắc gốc cho AI Agent — ROBOT_DIEUKIENVITRI

## 1. Phạm vi dự án

Project ESP-IDF hiện tại nằm tại:

`D:\DOAN_ROBOT_IDF\ROBOT_DIEUKIENVITRI`

Giai đoạn hiện tại chỉ phát triển firmware điều khiển vị trí cánh tay robot bằng ESP32-S3 A.

Chưa triển khai firmware ESP32-S3 B, ESP32-CAM, web hoặc GUI.

Không chỉnh sửa, di chuyển hoặc xóa project cũ.

## 2. Tài liệu đặc tả chính thức

Bộ tài liệu chi tiết nằm tại:

`ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/`

Trước khi lập trình, bắt buộc đọc đầy đủ:

1. `ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/AGENTS.md`
2. `ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/README.md`
3. `ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/AI_START_PROMPT.md`
4. Toàn bộ file Markdown trong `ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/docs/` ở lần khởi tạo đầu tiên.

Sau lần đọc đầu tiên, có thể đọc các tài liệu theo nhiệm vụ để tiết kiệm token. Tuy nhiên, phải kiểm tra lại các yêu cầu an toàn và thông số liên quan trước khi sửa code hoặc thực hiện kiểm thử phần cứng.

Không tự ý kết hợp các phiên bản tài liệu có nội dung mâu thuẫn. Khi không xác định được quyết định có thẩm quyền, hãy hỏi người dùng.

## 3. Quy tắc thay đổi

- Trước khi thực hiện, báo cáo mục tiêu và các file dự kiến tạo hoặc sửa.
- Không tự ý thay đổi GPIO, dây đấu, kiến trúc, giao diện module hoặc thông số phần cứng đã thống nhất.
- Không tự đặt góc Home, góc gắp/thả, giới hạn hành trình hoặc thông số chuyển động chưa được xác minh.
- Không xóa hay thay thế toàn bộ file chỉ để tránh sửa một lỗi nhỏ.
- Không tự ý sửa các tài liệu đặc tả chính thức.
- Nếu phát hiện mâu thuẫn hoặc thiếu thông số, hãy báo cáo và hỏi trước khi đưa ra quyết định ảnh hưởng đến phần cứng hoặc kiến trúc.

## 4. An toàn phần cứng

- Không flash firmware khi chưa có sự cho phép rõ ràng.
- Không cho động cơ chuyển động thực tế khi chưa có sự cho phép rõ ràng.
- Không coi vị trí tính từ số xung là góc thực tế được đo trực tiếp.
- Không cho phép AUTO khi hiệu chuẩn hoặc các điều kiện an toàn bắt buộc chưa đạt.
- Khi có lỗi, phải khóa chuyển động theo thiết kế và không tự tiếp tục chỉ vì lỗi đã biến mất.

## 5. Quy trình làm việc

Triển khai từng giai đoạn nhỏ theo `ROBOT_DIEUKIENVITRI_AI_SPEC_FINAL/docs/IMPLEMENTATION_PLAN.md`.

Sau mỗi giai đoạn, báo cáo:
- File đã tạo hoặc sửa.
- Chức năng đã hoàn thành.
- Kết quả build và kiểm thử thực tế.
- Lỗi còn tồn tại.
- Các thông số chưa xác minh.
- Đề xuất bước tiếp theo.

Không tự chuyển sang giai đoạn tiếp theo khi chưa được người dùng đồng ý.