/**
 * Calibration Service
 * 
 * Handles device calibration routines
 */

#ifndef CALIBRATION_SERVICE_H
#define CALIBRATION_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "drivers/imu_driver.h"

typedef enum {
    CALIBRATION_STATE_IDLE,
    CALIBRATION_STATE_COLLECTING,
    CALIBRATION_STATE_COMPLETE,
    CALIBRATION_STATE_ERROR
} calibration_state_t;

typedef struct {
    float accel_offset[3];
    float gyro_offset[3];
    float accel_scale[3];
    float gyro_scale[3];
    uint32_t sample_count;
} calibration_data_t;

void calibration_service_init(void);
bool calibration_service_start(void);
bool calibration_service_process(imu_data_t* imu_data);
bool calibration_service_complete(calibration_data_t* cal_data);
calibration_state_t calibration_service_get_state(void);
bool calibration_service_apply(const calibration_data_t* cal_data, imu_data_t* imu_data);

#endif // CALIBRATION_SERVICE_H

