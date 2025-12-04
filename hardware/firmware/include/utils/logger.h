/**
 * Logger Interface
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

typedef enum {
    LOGGER_LEVEL_DEBUG = 0,
    LOGGER_LEVEL_INFO = 1,
    LOGGER_LEVEL_WARN = 2,
    LOGGER_LEVEL_ERROR = 3
} logger_level_t;

void logger_init(void);
void logger_set_level(logger_level_t level);
void logger_log(logger_level_t level, const char* format, ...);

// Convenience functions (implemented as macros for variadic args)
#define logger_debug(...) logger_log(LOGGER_LEVEL_DEBUG, __VA_ARGS__)
#define logger_info(...) logger_log(LOGGER_LEVEL_INFO, __VA_ARGS__)
#define logger_warn(...) logger_log(LOGGER_LEVEL_WARN, __VA_ARGS__)
#define logger_error(...) logger_log(LOGGER_LEVEL_ERROR, __VA_ARGS__)

#endif // LOGGER_H

