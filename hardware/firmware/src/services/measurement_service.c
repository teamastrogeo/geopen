/**
 * Measurement Service Implementation
 */

#include "services/measurement_service.h"
#include "utils/timer.h"
#include <string.h>

static stored_measurement_t measurements[MAX_MEASUREMENTS];
static uint8_t measurement_count = 0;
static uint8_t next_id = 0;

void measurement_service_init(void) {
    measurement_count = 0;
    next_id = 0;
    memset(measurements, 0, sizeof(measurements));
}

bool measurement_service_record(const measurement_angles_t* angles) {
    if (measurement_count >= MAX_MEASUREMENTS) {
        return false;  // Storage full
    }
    
    stored_measurement_t* m = &measurements[measurement_count];
    m->angles = *angles;
    m->timestamp = timer_get_ms();
    
    // Generate simple ID (in production, use proper UUID)
    memset(m->measurement_id, 0, sizeof(m->measurement_id));
    m->measurement_id[0] = next_id++;
    
    measurement_count++;
    return true;
}

bool measurement_service_get(uint8_t index, stored_measurement_t* measurement) {
    if (index >= measurement_count) {
        return false;
    }
    
    *measurement = measurements[index];
    return true;
}

uint8_t measurement_service_count(void) {
    return measurement_count;
}

bool measurement_service_clear(void) {
    measurement_count = 0;
    memset(measurements, 0, sizeof(measurements));
    return true;
}

