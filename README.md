# Embedded Autonomous Control Simulation

This project simulates a simple embedded control system for tilt stabilization.

The program reads simulated IMU sensor data (pitch and roll) and calculates motor adjustments to stabilize the system. If the tilt exceeds a safety threshold, the system enters an ERROR state and shuts down the motor for safety.

## Features

- Simulated IMU sensor data
- State machine (IDLE → ACTIVE → ERROR)
- Motor adjustment calculation
- Actuator saturation limits
- Safety shutdown on excessive tilt

## Technologies

- C Programming
- GCC
- Git / GitHub

## How to Run

Compile:

gcc main.c -o control

Run:

./control
