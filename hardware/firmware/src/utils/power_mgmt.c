/**
 * Power Management Implementation
 */

#include "utils/power_mgmt.h"
#include "utils/logger.h"
#include "utils/timer.h"

static power_mode_t current_mode = POWER_MODE_ACTIVE;
static uint32_t last_activity_time = 0;
static uint32_t sleep_timeout_ms = 60000; // 60 seconds default

void power_mgmt_init(void) {
    current_mode = POWER_MODE_ACTIVE;
    last_activity_time = timer_get_ms();
    logger_info("Power management initialized");
}

void power_mgmt_set_mode(power_mode_t mode) {
    if (mode == current_mode) {
        return;
    }
    
    power_mode_t old_mode = current_mode;
    current_mode = mode;
    
    switch (mode) {
        case POWER_MODE_ACTIVE:
            // Wake up peripherals
            logger_debug("Entering active mode");
            break;
            
        case POWER_MODE_IDLE:
            // Reduce CPU frequency, keep peripherals on
            logger_debug("Entering idle mode");
            break;
            
        case POWER_MODE_SLEEP:
            // Stop CPU, keep RAM, wake on interrupt
            logger_debug("Entering sleep mode");
            break;
            
        case POWER_MODE_DEEP_SLEEP:
            // Stop CPU, reduce RAM, wake on external interrupt
            logger_debug("Entering deep sleep mode");
            break;
    }
}

power_mode_t power_mgmt_get_mode(void) {
    return current_mode;
}

uint8_t power_mgmt_get_battery_level(void) {
    // Platform-specific implementation needed
    // Read battery voltage/percentage
    return 100; // Stub: return 100%
}

bool power_mgmt_is_charging(void) {
    // Platform-specific implementation needed
    // Read charging status
    return false; // Stub: return false
}

void power_mgmt_update_activity(void) {
    last_activity_time = timer_get_ms();
}

void power_mgmt_check_timeout(void) {
    uint32_t idle_time = timer_get_ms() - last_activity_time;
    
    if (idle_time > sleep_timeout_ms && current_mode == POWER_MODE_ACTIVE) {
        power_mgmt_set_mode(POWER_MODE_IDLE);
    }
}

void power_mgmt_enter_sleep(uint32_t sleep_time_ms) {
    logger_debug("Entering sleep for %d ms", sleep_time_ms);
    power_mgmt_set_mode(POWER_MODE_SLEEP);
    
    // Platform-specific sleep implementation
    // timer_delay_ms(sleep_time_ms); // This is blocking, use interrupt-based sleep
    
    power_mgmt_set_mode(POWER_MODE_ACTIVE);
}

void power_mgmt_update_activity(void) {
    last_activity_time = timer_get_ms();
}

void power_mgmt_check_timeout(void) {
    uint32_t idle_time = timer_get_ms() - last_activity_time;
    
    if (idle_time > sleep_timeout_ms && current_mode == POWER_MODE_ACTIVE) {
        power_mgmt_set_mode(POWER_MODE_IDLE);
    }
}

