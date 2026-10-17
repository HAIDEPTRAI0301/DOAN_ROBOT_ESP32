# Nhật ký quyết định đã thống nhất

| ID | Quyết định | Quy tắc |
|---|---|---|
| D-01 | Project mới | `D:\DOAN_ROBOT_IDF\ROBOT_DIEUKIENVITRI`; không sửa project cũ |
| D-02 | IDE/toolchain | ESP-IDF, C `.c/.h`, VS Code/Antigravity |
| D-03 | Scope hiện tại | Làm firmware vị trí MCU A trước; B/C là integration sau |
| D-04 | Kiến trúc hệ thống | A: arm motion; B: sensor/belt/pump/process; C: ESP32-CAM vision |
| D-05 | GPIO A | J1 STEP15 DIR14 ENA13 HOME21; J2 STEP5 DIR6 ENA7 HOME20; J3 STEP16 DIR18 ENA17 HOME19 |
| D-06 | Home switches | NO, COM→GND, NO→GPIO; dự kiến pull-up, press LOW; phải verify |
| D-07 | Home order | J2→J3→J1; two-stage homing |
| D-08 | Home directions | J1 clockwise, J2 raise arm, J3 extend arm; DIR logic unverified |
| D-09 | Startup delay | 5 seconds, then self-check; timeout alone never authorizes movement |
| D-10 | Commissioning | Default locked; `robot_config.h` flag switched only after user confirms calibration; next boot auto-home then AUTO if safe gates pass |
| D-11 | Position values | PICK fixed; PLACE configurable in `robot_positions.h`; angles not yet measured |
| D-12 | Motion command | Serial first; relative `JOG` and absolute `MOVE`; parser/limits/interlocks required |
| D-13 | Motion profile | Three joints coordinated synchronously with accel/decel; homing is sequential |
| D-14 | Feedback | No encoder confirmed; open-loop steps, no fake closed-loop PID |
| D-15 | Arm motors | 3 × NEMA17, 1.8° info; current approx 1.5A/phase from previous information, verify exact label |
| D-16 | Arm pulley stage | Driver pulley 20T, driven 90T, GT2 6mm, belt 200mm; ratio 4.5 provisional if direct one stage |
| D-17 | Arm TB6600 microstep | 1/8 confirmed by user; DIP OFF-ON-OFF per their module |
| D-18 | Arm TB6600 current | Current switch group ON-ON-OFF; label reported 1.5A current / 1.7A peak; verify exact module table |
| D-19 | Available motor supply | 12V 20A available, suitability not approved/verified yet |
| D-20 | ENA | Not used by firmware; leave drivers enabled according to current wiring; do not reassign ENA GPIOs |
| D-21 | Position storage | `robot_positions.h`; edit values and build/flash; no fabricated angles |
| D-22 | Serial logs | Both A/B local logs; B may forward selected A logs while link works with source label |
| D-23 | Fault | Fault latch; report Serial, no auto retry/resume; home again if position invalid |
| D-24 | UART loss A–B | Controlled stop/latch on A; stop belt on B; retain vacuum ON if holding object; log local; no auto resume |
| D-25 | E-stop | Not yet installed; no unattended real-hardware AUTO until independent stop exists and is tested |
| D-26 | Belt | Stepper + separate 4th TB6600 controlled by B |
| D-27 | Pump | 12V vacuum pump on L298N, on/off; B-owned module |
| D-28 | Belt cycle | Belt runs when whole system ready; classified-valid object + sensor detection stops belt; sensor clear after pickup starts belt immediately while A may still place/return |
| D-29 | Vision prerequisite | ESP32-CAM classifies first; no valid matched classification at sensor → let item pass, no pick |
| D-30 | Busy robot / next object | B stops belt and stores max one valid pending request; deliver after prior cycle complete and A reports ready at PICK; no overlapping move commands |
| D-31 | Startup no valid classification | If NPN detects but no corresponding valid camera result, pass item through |
| D-32 | Vacuum confirmation | No feedback sensor; use configurable delay, exact delay TBD |
| D-33 | No Web/GUI | Not in current scope |

## Unanswered / not settled

- What to do if Home switch is already pressed at startup: not answered; default do not auto-backoff until away direction is verified. In commissioning, stop/log or require operator.
- Final protocol/link C–B and A–B baud/GPIO/framing not settled.
- Policy if queue slot full, sensor fails to clear, camera data is late/stale, or MCU B resets while vacuum holds object not settled; follow fail-safe lock and ask before implementation.
