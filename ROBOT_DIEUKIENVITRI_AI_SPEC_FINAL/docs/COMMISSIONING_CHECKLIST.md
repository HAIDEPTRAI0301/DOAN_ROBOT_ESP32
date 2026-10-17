# Commissioning checklist — trước khi cho motor chuyển động

## Gate 0 — Dự án và môi trường

- [ ] Đã xác nhận project root và không chạm project cũ.
- [ ] Đã xác nhận ESP-IDF version bằng CLI và build baseline.
- [ ] Đã kiểm tra pinout/schematic chính xác board A.
- [ ] `ROBOT_CALIBRATION_COMPLETE=false`; AUTO đang khóa.

## Gate 1 — Điện và driver

- [ ] Đã xác minh model TB6600 và bảng DIP của đúng module.
- [ ] Đã xác minh tín hiệu 3.3 V tương thích với input module và cách đấu hiện tại.
- [ ] Đã kiểm tra nguồn, dây, đấu motor, cực tính và phương tiện ngắt động lực.
- [ ] Không có điện áp 12/24 V đi thẳng tới GPIO.
- [ ] Có cách ngắt nguồn driver nhanh chóng ở vị trí người thử nghiệm.
- [ ] Không có E-stop độc lập: không cho AUTO không giám sát.

## Gate 2 — Inputs

- [ ] Test Home J1/J2/J3 bình thường=HIGH, pressed=LOW theo pull-up.
- [ ] Test debounce, nhả, stuck signal và wire-fault assumptions.
- [ ] Đã xác minh USB-UART/board routing không gây xung đột với GPIO19/20.

## Gate 3 — Một trục tại một thời điểm

- [ ] Chạy pulse-only trên một trục đã được phê duyệt.
- [ ] Xác minh DIR mapping bằng chuyển động thực, không suy luận từ HIGH/LOW.
- [ ] Xác định hướng tới và rời switch Home.
- [ ] Bắt đầu ở speed thấp và số xung nhỏ; giám sát rung, nhiệt độ, kẹt, mất bước.
- [ ] Không chạy trục khác đồng thời trong giai đoạn single-axis.

## Gate 4 — Hiệu chuẩn

- [ ] Đã đo tỷ số truyền đúng và cơ cấu linkage.
- [ ] Đã đo Home offset từng khớp.
- [ ] Đã đo giới hạn cơ khí và cài soft limits.
- [ ] Đã xác minh pulse-per-degree thực tế.
- [ ] Đã kiểm tra PICK/PLACE ngoài va chạm và xác nhận góc thực.
- [ ] Đã chọn tốc độ/gia tốc/timeout/backoff dựa trên thử nghiệm.

## Gate 5 — Cho phép AUTO

- [ ] Hardware interlock/E-stop độc lập đã lắp và thử nghiệm.
- [ ] Commissioning đã được user xác nhận hoàn tất.
- [ ] `robot_positions.h` có giá trị hợp lệ đã đo; không còn placeholder.
- [ ] Không còn blocker từ `OPEN_ITEMS.md` ảnh hưởng tới chuyển động thực.
- [ ] Người dùng cho phép rõ ràng trước khi flash/chạy AUTO.

Không tick thay người dùng hoặc đánh dấu đạt chỉ dựa trên việc code đã compile.
