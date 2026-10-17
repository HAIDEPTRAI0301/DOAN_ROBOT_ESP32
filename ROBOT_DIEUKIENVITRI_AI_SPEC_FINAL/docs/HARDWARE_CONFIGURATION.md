# Cấu hình phần cứng

## 1. Motion Controller A — thông tin đã biết

| Khớp | Tên vật lý | STEP GPIO | DIR GPIO | ENA GPIO đã có trong sơ đồ | HOME GPIO |
|---|---|---:|---:|---:|---:|
| J1 | Đế / trục X | 15 | 14 | 13 | 21 |
| J2 | Vai / trục Y | 5 | 6 | 7 | 20 |
| J3 | Khuỷu / trục Z | 16 | 18 | 17 | 19 |

- Không tự đổi GPIO. ENA hiện không được firmware điều khiển; driver luôn được cho phép theo cách đấu hiện tại. Không tái sử dụng GPIO ENA cho mục đích khác nếu chưa xin phép.
- Board kết nối PC qua USB-UART (CP2102/CH340 theo mô tả người dùng). GPIO19/20 dùng làm Home trong cách dùng này, nhưng vẫn phải xác minh đường mạch của đúng board; không bật USB native peripheral đồng thời chiếm các chân đó nếu board dùng chung.
- STEP/DIR/PUL của ba TB6600 đang được mô tả nối trực tiếp với GPIO; cần xác minh sơ đồ module, current/input circuit, mức logic 3.3 V và dòng GPIO trước bất kỳ chuyển động motor nào. Không tự thay wiring.

## 2. Home switches A

- Mỗi khớp một công tắc NO.
- COM công tắc → GND; NO → GPIO Home tương ứng.
- Logic dự kiến với pull-up: không nhấn = HIGH; nhấn = LOW.
- Phải đo/đọc bằng diagnostic firmware, debounce và xác minh theo từng switch trước khi homing.
- Chiều tìm Home theo cơ khí: J1 quay cùng chiều kim đồng hồ, J2 nâng cánh tay, J3 duỗi cánh tay. Mô tả đó chưa xác định DIR HIGH/LOW. Với J1, hướng nhìn dùng để định nghĩa chiều kim đồng hồ cần được ghi lại khi bench-test.

## 3. Motor, truyền động, TB6600 của cánh tay

| Thông số | Giá trị ghi nhận | Trạng thái |
|---|---|---|
| Motor | 3 × NEMA17 | Model/nhãn từng motor cần xác minh |
| Góc bước | 1.8°/full step (200 full steps/rev) | Đã cung cấp trước đó; kiểm tra nhãn nếu cần |
| Dòng pha motor | khoảng 1.5 A/phase theo thông tin trước | Xác minh đúng mã motor |
| Vi bước | 1/8 | Người dùng xác nhận; DIP hiện mô tả OFF–ON–OFF cho nhóm microstep |
| Dòng TB6600 | nhóm DIP ON–ON–OFF; nhãn người dùng đọc Current 1.5 A / Peak 1.7 A | Đối chiếu bảng trên đúng module; không tự giả định RMS/peak tương đương |
| Nguồn có sẵn | 12 V DC, 20 A | Chưa xác nhận đây là lựa chọn phù hợp cuối cùng; xác minh module, motor và hiệu năng tốc độ |
| Puly chủ động | 20 răng, gắn trục motor | Đã cung cấp |
| Puly bị động | 90 răng | Đã cung cấp; xác minh gắn chính xác lên trục đầu ra khớp |
| Đai | GT2, rộng 6 mm, dài 200 mm | Đã cung cấp; chiều dài không quyết định tỷ số truyền |
| Tỷ số sơ bộ | 90/20 = 4.5:1 | Chỉ đúng cho một tầng puly này, không có tầng khác |

### Quy đổi lý thuyết (chỉ để tham khảo)

Nếu 200 full steps/rev, 1/8 microstep, ratio 4.5:1 và puly bị động đúng là trục đầu ra của khớp, thì motor có 1600 microsteps/rev; đầu ra có 7200 pulses/rev; lý thuyết 20 pulses/degree. **Không được coi 20 pulses/degree đã được hiệu chuẩn cho góc khớp cơ khí** nếu linkage/cơ cấu song song có quan hệ góc khác hoặc có tầng truyền động bổ sung. Cần xác minh/hiệu chuẩn từng khớp bằng đo thực tế.

## 4. Home offsets và giới hạn cơ khí

- Chọn dùng mốc switch Home với **góc tham chiếu riêng từng khớp** (home offset), không mặc định Home là 0°.
- Offset J1/J2/J3 chưa có số đo; giới hạn góc dương/âm cũng chưa biết.
- Không tạo `robot_positions.h` với góc pick/place giả. Các value chưa xác minh phải được đánh dấu invalid và khóa AUTO.

## 5. B — phần cứng tương lai, chưa triển khai ngay

- Một TB6600 riêng thứ tư điều khiển motor bước băng tải; ESP32-S3 B phát STEP/DIR.
- GPIO STEP/DIR, vi bước, dòng DIP, loại motor, nguồn, tốc độ, gia tốc, truyền động và vị trí cảm biến đều chưa cung cấp.
- ESP32 B điều khiển bơm chân không 12 V bật/tắt qua L298N. GPIO, active level, wiring và mạch nguồn bơm chưa xác minh.
- Cảm biến NPN trên băng tải. Loại NO/NC, nguồn, sink current, dây output, common-ground và mạch interface chưa xác minh. Không nối trực tiếp 12/24 V vào GPIO.

## 6. C — ESP32-CAM tương lai

- Dùng cho camera xử lý ảnh/phân loại vật.
- Model board, camera sensor/optics, thuật toán phân loại, GPIO, đường giao tiếp C–B và format classification chưa chốt.

## 7. Emergency stop

- E-stop vật lý hiện chưa lắp; GPIO chưa gán.
- Trước AUTO không giám sát: cần mạch ngắt động lực độc lập được thiết kế/thử nghiệm và tín hiệu giám sát về controller phù hợp. Không dùng một GPIO hoặc phần mềm làm biện pháp E-stop duy nhất.
- Chưa có phương án phần cứng giữ vacuum khi B reset/mất nguồn; đây là rủi ro cần đánh giá vì vật có thể rơi.
