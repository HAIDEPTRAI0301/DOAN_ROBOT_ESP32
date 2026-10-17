# Cây thư mục chi tiết — firmware điều khiển vị trí

## Cây đích

```text
ROBOT_DIEUKIENVITRI/
├── AGENTS.md
├── README.md
├── docs/
│   ├── CAY_THU_MUC_CHI_TIET.md
│   ├── KIEN_TRUC_VA_PHU_THUOC.md
│   ├── QUY_TAC_DEBUG.md
│   ├── KE_HOACH_TRIEN_KHAI.md
│   └── DANH_SACH_THONG_SO_CHUA_XAC_MINH.md
├── CMakeLists.txt                 # project-level, giữ file do ESP-IDF tạo
├── sdkconfig                      # generated/configured, không overwrite tùy tiện
└── main/
    ├── CMakeLists.txt             # component manifest, phải review trước khi thay
    ├── main.c                     # entry point rất mỏng
    └── modules/
        ├── dung_chung/
        │   └── kieu_du_lieu_robot.h
        ├── cau_hinh/
        │   ├── robot_config.h
        │   ├── robot_config.c
        │   ├── robot_positions.h
        │   └── robot_positions.c
        ├── phan_cung/
        │   ├── truc_buoc.h/.c
        │   ├── cong_tac_home.h/.c
        │   └── bo_phat_xung.h/.c
        ├── tinh_toan/
        │   ├── quy_doi_goc_xung.h/.c
        │   ├── profile_toc_do.h/.c
        │   └── dong_bo_ba_truc.h/.c
        ├── dieu_khien/
        │   ├── tim_home.h/.c
        │   └── dieu_khien_vi_tri.h/.c
        ├── he_thong/
        │   ├── may_trang_thai.h/.c
        │   ├── quan_ly_loi.h/.c
        │   └── kiem_tra_an_toan.h/.c
        ├── giao_tiep/
        │   └── xu_ly_lenh_serial.h/.c
        └── ung_dung/
            └── trinh_dieu_khien_robot.h/.c
```

Trong cây trên, ký hiệu `truc_buoc.h/.c` là hai file thật: `truc_buoc.h` và `truc_buoc.c`, đặt cùng trong thư mục `phan_cung/`.

## Vai trò theo nhóm

### `dung_chung/`
- `kieu_du_lieu_robot.h`: kiểu dữ liệu dùng chung như `robot_result_t`, `robot_state_t`, `robot_joint_id_t`, `robot_joint_angles_t`, `robot_position_validity_t`.
- Không chứa logic phần cứng và không include ESP-IDF driver nếu không cần.

### `cau_hinh/`
- `robot_config.h/.c`: GPIO, bước/vòng, vi bước, tỷ số truyền, cờ COMMISSIONING/AUTO, tham số runtime có hiệu lực sau khi được xác minh.
- `robot_positions.h/.c`: các vị trí tham chiếu và mục tiêu. Mỗi vị trí có cờ `valid`; giá trị chưa đo không được dùng để chạy motor.
- Không hard-code cùng một thông số trong nhiều module.

### `phan_cung/`
- `truc_buoc`: giao diện theo trục J1/J2/J3, chiều DIR, trạng thái bận/lỗi; không tính profile quỹ đạo.
- `cong_tac_home`: cấu hình/đọc GPIO công tắc, debounce, trạng thái pressed/released; không tự chạy motor.
- `bo_phat_xung`: lớp duy nhất sở hữu bộ phát xung thời gian thực. Chọn công nghệ sau khi kiểm tra ESP-IDF 6.1 và yêu cầu đồng bộ. Không dùng vòng lặp Serial/blocking để tạo STEP trong vận hành.

### `tinh_toan/`
- `quy_doi_goc_xung`: công thức degree↔pulse, tỷ số truyền, kiểm tra overflow và làm tròn.
- `profile_toc_do`: profile tốc độ/gia tốc/giảm tốc cho một chuyển động.
- `dong_bo_ba_truc`: phân bố xung và phối hợp thời gian cho ba trục; không truy cập GPIO trực tiếp.

### `dieu_khien/`
- `tim_home`: homing hai giai đoạn và trình tự J2→J3→J1, timeout/step limit.
- `dieu_khien_vi_tri`: API cấp cao cho JOG tương đối/MOVE tuyệt đối; kiểm tra trạng thái, giới hạn và vị trí hợp lệ trước khi gọi planner.

### `he_thong/`
- `may_trang_thai`: trạng thái tổng quát và chuyển trạng thái hợp lệ.
- `quan_ly_loi`: fault latch, mã lỗi, reset lỗi có điều kiện, log sự kiện.
- `kiem_tra_an_toan`: tập hợp điều kiện cho phép chuyển động; không trực tiếp tạo xung.

### `giao_tiep/`
- `xu_ly_lenh_serial`: đọc dòng lệnh, parse/validate, gửi yêu cầu vào controller. Không gọi driver GPIO trực tiếp.

### `ung_dung/`
- `trinh_dieu_khien_robot`: ghép các dịch vụ, chạy init/state machine, điều phối lệnh. Không chứa thuật toán thấp cấp.

## Không chia nhỏ hơn ở giai đoạn đầu

- Không tạo một ESP-IDF component riêng cho mỗi `.c/.h`.
- Không tạo thư viện PID vì chưa có feedback góc liên tục.
- Không thêm FK/IK/XYZ hoặc camera/UART liên-MCU vào firmware A giai đoạn này.
- Chỉ cân nhắc tách `components/` sau khi API một nhóm đã ổn định và có test.
