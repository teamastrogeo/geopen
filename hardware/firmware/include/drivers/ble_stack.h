/**
 * BLE Stack Interface
 */

#ifndef BLE_STACK_H
#define BLE_STACK_H

#include "algorithms/angle_calc.h"
#include <stdbool.h>

void ble_stack_init(void);
void ble_stack_process(void);
bool ble_stack_send_measurement(const measurement_angles_t* angles);
bool ble_stack_is_connected(void);

#endif // BLE_STACK_H

