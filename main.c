#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    IDLE,
    ACTIVE,
    ERROR
} SystemState;

typedef struct {
    float pitch;
    float roll;
} IMUData;

IMUData readIMUSensor() {
    IMUData data;
    data.pitch = (rand() % 200 - 100) / 10.0;
    data.roll  = (rand() % 200 - 100) / 10.0;
    return data;
}

int main() {
    srand(time(NULL));

    float tiltLimit = 5.0;
    SystemState state = IDLE;

    printf("System Booting...\n");

    state = ACTIVE;


    while (1) {

        IMUData imu = readIMUSensor();

        if (state == ACTIVE) {

            float motorAdjustment = -imu.pitch * 0.5;

            if (motorAdjustment > 10)
                motorAdjustment = 10;

            if (motorAdjustment < -10)
                motorAdjustment = -10;


            printf("Pitch: %.2f | Roll: %.2f\n", imu.pitch, imu.roll);
            printf("Motor Adjustment: %.2f\n\n", motorAdjustment);


if (imu.pitch > tiltLimit || imu.pitch < -tiltLimit)
 {
                state = ERROR;
            }

        }

        if (state == ERROR) {
            printf("ERROR: Excessive tilt detected!\n");
             printf("Motor Stopped for Safety.\n");
            break;

        }
    }

    return 0;
}

