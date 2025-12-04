/**
 * Timer Utilities
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
uint32_t timer_get_ms(void);
void timer_delay_ms(uint32_t ms);

#endif // TIMER_H

