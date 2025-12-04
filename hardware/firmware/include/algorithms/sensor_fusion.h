/**
 * Sensor Fusion Algorithm
 * 
 * Implements Madgwick AHRS filter for combining accelerometer and gyroscope data
 */

#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

#include <stdint.h>
#include "drivers/imu_driver.h"

// Quaternion structure
typedef struct {
    float q0, q1, q2, q3;  // Quaternion components
} quaternion_t;

// Euler angles structure
typedef struct {
    float roll;   // Rotation around X-axis (radians)
    float pitch;  // Rotation around Y-axis (radians)
    float yaw;    // Rotation around Z-axis (radians)
} euler_angles_t;

// Sensor fusion filter structure
typedef struct {
    quaternion_t quat;     // Current quaternion
    float beta;            // Filter gain (typically 0.1)
    uint32_t last_update;  // Last update timestamp
} sensor_fusion_t;

/**
 * Initialize sensor fusion filter
 * @param filter Pointer to sensor_fusion_t structure
 * @param beta Filter gain (0.1 recommended)
 */
void sensor_fusion_init(sensor_fusion_t* filter, float beta);

/**
 * Update filter with new IMU data
 * @param filter Pointer to sensor_fusion_t structure
 * @param imu_data Pointer to IMU data
 */
void sensor_fusion_update(sensor_fusion_t* filter, const imu_data_t* imu_data);

/**
 * Convert quaternion to Euler angles
 * @param quat Pointer to quaternion
 * @param euler Pointer to euler_angles_t structure to fill
 */
void quaternion_to_euler(const quaternion_t* quat, euler_angles_t* euler);

/**
 * Normalize quaternion
 * @param quat Pointer to quaternion to normalize
 */
void quaternion_normalize(quaternion_t* quat);

#endif // SENSOR_FUSION_H

