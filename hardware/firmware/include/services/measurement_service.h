/**
 * Measurement Service
 * 
 * Handles measurement recording and storage
 */

#ifndef MEASUREMENT_SERVICE_H
#define MEASUREMENT_SERVICE_H

#include "algorithms/angle_calc.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_MEASUREMENTS 100

typedef struct {
    measurement_angles_t angles;
    uint32_t timestamp;
    uint8_t measurement_id[16];  // UUID
} stored_measurement_t;

void measurement_service_init(void);
bool measurement_service_record(const measurement_angles_t* angles);
bool measurement_service_get(uint8_t index, stored_measurement_t* measurement);
uint8_t measurement_service_count(void);
bool measurement_service_clear(void);

#endif // MEASUREMENT_SERVICE_H

