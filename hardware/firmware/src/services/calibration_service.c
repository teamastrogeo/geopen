/**
 * Calibration Service Implementation
 */

#include "services/calibration_service.h"
#include "utils/logger.h"
#include <string.h>
#include <math.h>

#define CALIBRATION_SAMPLES 100

static calibration_state_t calibration_state = CALIBRATION_STATE_IDLE;
static calibration_data_t calibration_buffer;
static float accel_sum[3] = {0};
static float gyro_sum[3] = {0};
static uint32_t sample_count = 0;

void calibration_service_init(void) {
    calibration_state = CALIBRATION_STATE_IDLE;
    memset(&calibration_buffer, 0, sizeof(calibration_buffer));
    memset(accel_sum, 0, sizeof(accel_sum));
    memset(gyro_sum, 0, sizeof(gyro_sum));
    sample_count = 0;
}

bool calibration_service_start(void) {
    if (calibration_state != CALIBRATION_STATE_IDLE) {
        return false;
    }
    
    calibration_state = CALIBRATION_STATE_COLLECTING;
    sample_count = 0;
    memset(accel_sum, 0, sizeof(accel_sum));
    memset(gyro_sum, 0, sizeof(gyro_sum));
    
    logger_info("Calibration started");
    return true;
}

bool calibration_service_process(imu_data_t* imu_data) {
    if (calibration_state != CALIBRATION_STATE_COLLECTING) {
        return false;
    }
    
    // Accumulate samples
    accel_sum[0] += imu_data->accel_x;
    accel_sum[1] += imu_data->accel_y;
    accel_sum[2] += imu_data->accel_z;
    
    gyro_sum[0] += imu_data->gyro_x;
    gyro_sum[1] += imu_data->gyro_y;
    gyro_sum[2] += imu_data->gyro_z;
    
    sample_count++;
    
    // Check if enough samples collected
    if (sample_count >= CALIBRATION_SAMPLES) {
        calibration_state = CALIBRATION_STATE_COMPLETE;
        logger_info("Calibration samples collected: %d", sample_count);
        return true;
    }
    
    return false;
}

bool calibration_service_complete(calibration_data_t* cal_data) {
    if (calibration_state != CALIBRATION_STATE_COMPLETE) {
        return false;
    }
    
    // Calculate offsets (mean values)
    calibration_buffer.accel_offset[0] = accel_sum[0] / sample_count;
    calibration_buffer.accel_offset[1] = accel_sum[1] / sample_count;
    calibration_buffer.accel_offset[2] = accel_sum[2] / sample_count - 9.81f; // Remove gravity
    
    calibration_buffer.gyro_offset[0] = gyro_sum[0] / sample_count;
    calibration_buffer.gyro_offset[1] = gyro_sum[1] / sample_count;
    calibration_buffer.gyro_offset[2] = gyro_sum[2] / sample_count;
    
    // Set scale factors to 1.0 (can be calibrated separately)
    calibration_buffer.accel_scale[0] = 1.0f;
    calibration_buffer.accel_scale[1] = 1.0f;
    calibration_buffer.accel_scale[2] = 1.0f;
    
    calibration_buffer.gyro_scale[0] = 1.0f;
    calibration_buffer.gyro_scale[1] = 1.0f;
    calibration_buffer.gyro_scale[2] = 1.0f;
    
    calibration_buffer.sample_count = sample_count;
    
    if (cal_data) {
        *cal_data = calibration_buffer;
    }
    
    calibration_state = CALIBRATION_STATE_IDLE;
    logger_info("Calibration complete");
    
    return true;
}

calibration_state_t calibration_service_get_state(void) {
    return calibration_state;
}

bool calibration_service_apply(const calibration_data_t* cal_data, imu_data_t* imu_data) {
    if (!cal_data || !imu_data) {
        return false;
    }
    
    // Apply offset and scale
    imu_data->accel_x = (imu_data->accel_x - cal_data->accel_offset[0]) * cal_data->accel_scale[0];
    imu_data->accel_y = (imu_data->accel_y - cal_data->accel_offset[1]) * cal_data->accel_scale[1];
    imu_data->accel_z = (imu_data->accel_z - cal_data->accel_offset[2]) * cal_data->accel_scale[2];
    
    imu_data->gyro_x = (imu_data->gyro_x - cal_data->gyro_offset[0]) * cal_data->gyro_scale[0];
    imu_data->gyro_y = (imu_data->gyro_y - cal_data->gyro_offset[1]) * cal_data->gyro_scale[1];
    imu_data->gyro_z = (imu_data->gyro_z - cal_data->gyro_offset[2]) * cal_data->gyro_scale[2];
    
    return true;
}

