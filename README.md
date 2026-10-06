# ⚔️ Bot Wrestling — MindSpark COEP

RC combat robot built for **MindSpark Robotica** hosted by COEP Technological University, Pune.

---

## What It Is

4-wheeled differential drive combat robot.
Controlled over 2.4 GHz RC with tank-mix steering, smooth acceleration ramp, and signal-loss failsafe.

---

## Hardware

| Component | Model | Key Specs |
|---|---|---|
| Microcontroller | ESP32 DevKit V1 | 240MHz, 3.3V logic |
| Motor Driver | Rhino MDD20A (RMCS-2310) | 20A continuous / 60A peak per channel |
| Motors ×4 | RKI-1310 DC Geared | 12V, 600 RPM, 4.5 kg-cm |
| Battery (main) | GenX 3S LiPo RKI-4891 | 11.1V, 5200mAh, 40C |
| Battery (backup) | GenX 3S LiPo RKI-4890 | 11.1V, 3300mAh, 40C |
| RC Transmitter | FlySky FS-i6S | 10CH, 2.4GHz AFHDS 2A |
| RC Receiver | FlySky FS-iA10B | 10CH |
| Buck Converter | LM2596S | 11.1V → 5V, 2A |
| Wheels ×4 | — | 100mm, 6mm D-shaft |
| Chassis | Metal | 300 × 300mm |

---

## Firmware Features

**Tank Mix Steering**
Left and right motor speeds are computed independently from both sticks:
```cpp
targetLeft  = throttle + steering;
targetRight = throttle - steering;
```

**Smooth Acceleration**
Motors ramp at 15 units per 10ms tick instead of snapping to target.
Reduces wheel slip and drivetrain shock under load.

**Deadzone**
Ignores stick values within ±70 of center to prevent drift from stick noise.

**Failsafe**
If PWM pulses go out of range (signal loss), bot decelerates smoothly to a stop instead of jerking or running away.

---

## Files

```
├── code.ino          — Main firmware (ESP32 / Arduino)
├── CONNECTIONS.md    — Full wiring reference (pin mapping + power rail)
├── components.txt    — Complete BOM with specs
├── flowchart.png     — System architecture diagram
└── README.md
```

---

## Competition

| | |
|---|---|
| Event | MindSpark Robotica — Bot Wrestling |
| Host | COEP Technological University, Pune |
| Chassis limit | 300 × 300mm |

