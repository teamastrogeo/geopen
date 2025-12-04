/**
 * IMU Driver Interface
 * 
 * Provides interface for reading IMU sensor data (accelerometer, gyroscope)
 * 
 * CRITICAL: IMU sensor must be aligned with device coordinate system
 * - Physical Location: (0, 0, 15) mm from tip center
 * - Alignment Tolerance: ±0.1° for X, Y, Z axes
 * - Sensor X-axis → Device X-axis (parallel)
 * - Sensor Y-axis → Device Y-axis (parallel)  
 * - Sensor Z-axis → Device Z-axis (parallel)
 * - See docs/mechanical/COMPONENT_DIMENSIONS.md for 3D coordinates
 */

#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// IMU data structure
typedef struct {
    float accel_x;      // Accelerometer X (m/s²)
    float accel_y;      // Accelerometer Y (m/s²)
    float accel_z;      // Accelerometer Z (m/s²)
    float gyro_x;       // Gyroscope X (rad/s)
    float gyro_y;       // Gyroscope Y (rad/s)
    float gyro_z;       // Gyroscope Z (rad/s)
    uint32_t timestamp; // Timestamp in milliseconds
} imu_data_t;

/**
 * Initialize IMU driver
 * @return true if initialization successful
 */
bool imu_driver_init(void);

/**
 * Read IMU sensor data
 * @param data Pointer to imu_data_t structure to fill
 * @return true if read successful
 */
bool imu_driver_read(imu_data_t* data);

/**
 * Calibrate IMU sensors
 * @return true if calibration successful
 */
bool imu_driver_calibrate(void);

/**
 * Get IMU status
 * @return true if IMU is ready
 */
bool imu_driver_is_ready(void);

#endif // IMU_DRIVER_H

