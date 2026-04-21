# Embedded Autonomous Control Simulation

A dual-axis embedded control simulation written in C, modeling real-time stabilization behavior found in drone and robotics systems.

The system reads simulated IMU sensor data (pitch and roll), runs independent PID controllers on each axis, and manages system state through a 3-state finite state machine. On tilt threshold violation, the system triggers an automatic safety shutdown.

---

## Features

- Dual-axis PID controller (pitch + roll) with proportional, integral, and derivative terms
- 3-state finite state machine: IDLE → ACTIVE → ERROR
- 100 Hz simulated control loop (10 ms timestep)
- Actuator saturation limiting (±10 output clamp)
- Automatic safety shutdown on excessive tilt detection
- Formatted real-time console output per cycle

---

## Technologies

- C Programming
- GCC
- Git / GitHub

---

## How to Run

Compile:
```
gcc main.c -o control
```

Run:
```
./control
```

---

## Sample Output

```
=== Embedded Autonomous Control System ===
Setpoint: Pitch=0.00 | Roll=0.00
PID Gains: Kp=0.80  Ki=0.10  Kd=0.05

System Booting...
State: IDLE → ACTIVE

[Cycle 00 | t=0.00s]
  IMU     → Pitch:  -0.40°  Roll:  +1.20°
  PID CMD → Pitch:  +2.32   Roll:  -6.96

[!] ERROR: Excessive tilt detected at cycle 1!
[!] Safety shutdown → Motors stopped.
[!] State: ACTIVE → ERROR
```

---

## Concepts Demonstrated

- PID control theory (proportional, integral, derivative)
- Finite state machine design
- Real-time control loop simulation
- Embedded systems safety logic
- Low-level C programming and memory management

---

## Author

Oguz Mermer
