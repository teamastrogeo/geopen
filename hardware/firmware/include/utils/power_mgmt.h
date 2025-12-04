/**
 * Power Management
 */

#ifndef POWER_MGMT_H
#define POWER_MGMT_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    POWER_MODE_ACTIVE,
    POWER_MODE_IDLE,
    POWER_MODE_SLEEP,
    POWER_MODE_DEEP_SLEEP
} power_mode_t;

void power_mgmt_init(void);
void power_mgmt_set_mode(power_mode_t mode);
power_mode_t power_mgmt_get_mode(void);
uint8_t power_mgmt_get_battery_level(void);
bool power_mgmt_is_charging(void);
void power_mgmt_enter_sleep(uint32_t sleep_time_ms);
void power_mgmt_update_activity(void);
void power_mgmt_check_timeout(void);

#endif // POWER_MGMT_H

