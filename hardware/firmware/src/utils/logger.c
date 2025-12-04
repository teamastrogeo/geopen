/**
 * Logger Implementation
 * 
 * Simple logging utility for firmware debugging
 */

#include "utils/logger.h"
#include <stdio.h>
#include <stdarg.h>

static logger_level_t current_level = LOGGER_LEVEL_INFO;

void logger_init(void) {
    // Initialize UART or other output
    // This is platform-specific
    current_level = LOGGER_LEVEL_INFO;
}

void logger_set_level(logger_level_t level) {
    current_level = level;
}

void logger_log(logger_level_t level, const char* format, ...) {
    if (level < current_level) {
        return;
    }
    
    const char* level_str;
    switch (level) {
        case LOGGER_LEVEL_DEBUG:
            level_str = "DEBUG";
            break;
        case LOGGER_LEVEL_INFO:
            level_str = "INFO";
            break;
        case LOGGER_LEVEL_WARN:
            level_str = "WARN";
            break;
        case LOGGER_LEVEL_ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }
    
    printf("[%s] ", level_str);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    printf("\n");
}

