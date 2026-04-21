#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ── System State Machine ──────────────────────────────────────────────────────
typedef enum {
    IDLE,
    ACTIVE,
    ERROR
} SystemState;

// ── Sensor Data ───────────────────────────────────────────────────────────────
typedef struct {
    float pitch;
    float roll;
} IMUData;

// ── PID Controller ────────────────────────────────────────────────────────────
typedef struct {
    float kp, ki, kd;
    float prev_error;
    float integral;
} PIDController;

float pid_compute(PIDController *pid, float setpoint, float measurement, float dt) {
    float error      = setpoint - measurement;
    pid->integral   += error * dt;
    float derivative = (error - pid->prev_error) / dt;
    pid->prev_error  = error;

    float output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;

    // Actuator saturation
    if (output >  10.0f) output =  10.0f;
    if (output < -10.0f) output = -10.0f;

    return output;
}

// ── Simulated IMU Sensor ──────────────────────────────────────────────────────
IMUData readIMUSensor() {
    IMUData data;
    data.pitch = (rand() % 200 - 100) / 10.0f;
    data.roll  = (rand() % 200 - 100) / 10.0f;
    return data;
}

// ── Main Control Loop ─────────────────────────────────────────────────────────
int main() {
    srand(time(NULL));

    const float TILT_LIMIT = 5.0f;
    const float DT         = 0.01f;   // 10 ms timestep → 100 Hz control loop
    const int   MAX_CYCLES = 50;

    SystemState state = IDLE;

    // PID tuning: Kp=0.8, Ki=0.1, Kd=0.05
    PIDController pitch_pid = {0.8f, 0.1f, 0.05f, 0.0f, 0.0f};
    PIDController roll_pid  = {0.8f, 0.1f, 0.05f, 0.0f, 0.0f};

    printf("=== Embedded Autonomous Control System ===\n");
    printf("Setpoint: Pitch=0.00 | Roll=0.00\n");
    printf("PID Gains: Kp=%.2f  Ki=%.2f  Kd=%.2f\n\n",
           pitch_pid.kp, pitch_pid.ki, pitch_pid.kd);
    printf("System Booting...\n");

    state = ACTIVE;
    printf("State: IDLE → ACTIVE\n\n");

    int cycle = 0;
    while (cycle < MAX_CYCLES) {
        IMUData imu = readIMUSensor();

        if (state == ACTIVE) {
            float pitch_cmd = pid_compute(&pitch_pid, 0.0f, imu.pitch, DT);
            float roll_cmd  = pid_compute(&roll_pid,  0.0f, imu.roll,  DT);

            printf("[Cycle %02d | t=%.2fs]\n", cycle, cycle * DT);
            printf("  IMU     → Pitch: %+6.2f°  Roll: %+6.2f°\n",
                   imu.pitch, imu.roll);
            printf("  PID CMD → Pitch: %+6.2f   Roll: %+6.2f\n",
                   pitch_cmd, roll_cmd);

            if (imu.pitch > TILT_LIMIT || imu.pitch < -TILT_LIMIT ||
                imu.roll  > TILT_LIMIT || imu.roll  < -TILT_LIMIT) {
                state = ERROR;
            }
        }

        if (state == ERROR) {
            printf("\n[!] ERROR: Excessive tilt detected at cycle %d!\n", cycle);
            printf("[!] Safety shutdown → Motors stopped.\n");
            printf("[!] State: ACTIVE → ERROR\n");
            return 1;
        }

        cycle++;
    }

    printf("\n[OK] Control loop completed: %d cycles at %.0f Hz.\n",
           MAX_CYCLES, 1.0f / DT);
    printf("[OK] System nominal. State: ACTIVE → IDLE\n");
    state = IDLE;

    return 0;
}
