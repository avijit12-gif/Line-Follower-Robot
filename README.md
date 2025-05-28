# Line-Follower-Robot

# 4-IR Sensor Line Follower Robot using Arduino

👤**Avijit Kushwaha**

## 📌Overview

This is a 4-IR sensor based line follower robot built using Arduino UNO and an L298N motor driver. The robot intelligently follows a black line on a white surface using real-time input from four IR sensors.

Using four sensors (instead of two) enables more precise tracking, smoother turns, and better recovery when the robot goes off the line — making it suitable for more complex paths.

---

##  What It Does

- Uses 4 IR sensors to detect black line path
- Controls 2 DC motors via PWM signals
- Performs straight movement, slight turns, and stops
- Recovers intelligently when the line is lost by remembering last known direction

---

## 🔧 Hardware Components

| Component             | Quantity |
|-----------------------|----------|
| Arduino UNO           | 1        |
| IR Sensors (Digital)  | 4        |
| L298N Motor Driver    | 1        |
| DC Motors             | 2        |
| Robot Chassis         | 1        |
| Wheels + Caster Wheel | 2 + 1    |
| Battery Pack (7.4V/9V)| 1        |
| Jumper Wires          | As needed |
| Breadboard (optional) | 1        |

---

## ⚙️ Pin Configuration

### IR Sensor Pins:
- `L2 = A0`
- `L1 = 11`
- `R1 = 12`
- `R2 = A1`

### Motor Driver Pins:
- Left Motor: `ENA = 5`, `IN1 = 9`, `IN2 = 10`
- Right Motor: `ENB = 6`, `IN3 = 7`, `IN4 = 8`

---

## 🛠️ How It Works

- `digitalRead()` checks each sensor's output (HIGH = black line detected)
- Depending on which sensors detect black, the robot:
  - Goes straight (`L1` or `R1`)
  - Turns slightly left (`L2`)
  - Turns slightly right (`R2`)
  - Recovers by turning in the last known direction if all sensors read white

---

## 📄 Code Features

- Clean, modular Arduino sketch
- Adjustable speed control with constants
- Smart line-loss recovery logic
- Debug output via `Serial Monitor`

