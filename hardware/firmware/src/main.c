/**
 * GeoPen Firmware - Main Entry Point
 * 
 * This firmware implements the core functionality for the GeoPen device:
 * - IMU sensor reading and processing
 * - Alpha and beta angle calculation
 * - BLE communication with mobile app
 * - Power management
 * - Calibration routines
 * 
 * Device Geometry Reference:
 * - Coordinate System: Origin at tip (0,0,0), Z-axis upward to 180mm
 * - IMU Sensor Position: (0, 0, 15) mm - CRITICAL alignment required
 * - See docs/mechanical/ for complete 3D specifications
 */

#include <stdint.h>
#include <stdbool.h>
#include "drivers/imu_driver.h"
#include "drivers/ble_stack.h"
#include "algorithms/sensor_fusion.h"
#include "algorithms/angle_calc.h"
#include "services/measurement_service.h"
#include "services/calibration_service.h"
#include "utils/timer.h"
#include "utils/logger.h"
#include "utils/power_mgmt.h"

// System state
typedef enum {
    STATE_IDLE,
    STATE_MEASURING,
    STATE_CALIBRATING,
    STATE_SLEEP
} system_state_t;

static system_state_t current_state = STATE_IDLE;
static bool measurement_triggered = false;

/**
 * Initialize all system components
 */
void system_init(void) {
    // Initialize logger
    logger_init();
    logger_info("GeoPen Firmware v1.0.0");
    
    // Initialize drivers
    imu_driver_init();
    ble_stack_init();
    timer_init();
    
    // Initialize services
    measurement_service_init();
    calibration_service_init();
    power_mgmt_init();
    
    logger_info("System initialized");
}

/**
 * Process measurement trigger
 */
void process_measurement(void) {
    if (current_state != STATE_IDLE) {
        return;
    }
    
    current_state = STATE_MEASURING;
    logger_info("Starting measurement...");
    
    // Read sensor data
    imu_data_t imu_data;
    if (!imu_driver_read(&imu_data)) {
        logger_error("Failed to read IMU data");
        current_state = STATE_IDLE;
        return;
    }
    
    // Apply sensor fusion
    static sensor_fusion_t fusion_filter;
    static bool fusion_initialized = false;
    if (!fusion_initialized) {
        sensor_fusion_init(&fusion_filter, 0.1f); // Beta = 0.1
        fusion_initialized = true;
    }
    sensor_fusion_update(&fusion_filter, &imu_data);
    quaternion_t quat = fusion_filter.quat;
    
    // Calculate angles
    measurement_angles_t angles;
    calculate_angles(&quat, &angles);
    
    // Validate angles
    if (!validate_angles(&angles)) {
        logger_warn("Invalid angles calculated");
        current_state = STATE_IDLE;
        return;
    }
    
    // Store and transmit measurement
    measurement_service_record(&angles);
    ble_stack_send_measurement(&angles);
    
    logger_info("Measurement complete: alpha=%.1f, beta=%.1f", 
                angles.alpha, angles.beta);
    
    current_state = STATE_IDLE;
}

/**
 * Main loop
 */
int main(void) {
    system_init();
    
    while (1) {
        // Check for measurement trigger
        if (measurement_triggered) {
            measurement_triggered = false;
            process_measurement();
        }
        
        // Process BLE events
        ble_stack_process();
        
        // Handle power management
        if (current_state == STATE_IDLE) {
            power_mgmt_check_timeout();
            timer_delay_ms(100);
        } else {
            power_mgmt_update_activity();
        }
    }
    
    return 0;
}

