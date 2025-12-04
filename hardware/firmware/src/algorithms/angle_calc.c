/**
 * Angle Calculation Implementation
 */

#include "algorithms/angle_calc.h"
#include <math.h>
#include <stdbool.h>

#define DEG_TO_RAD (M_PI / 180.0f)
#define RAD_TO_DEG (180.0f / M_PI)

void calculate_angles(const quaternion_t* quat, measurement_angles_t* angles) {
    // Convert quaternion to Euler angles
    euler_angles_t euler;
    
    // Calculate Euler angles from quaternion
    float sinr_cosp = 2.0f * (quat->q0 * quat->q1 + quat->q2 * quat->q3);
    float cosr_cosp = 1.0f - 2.0f * (quat->q1 * quat->q1 + quat->q2 * quat->q2);
    euler.roll = atan2f(sinr_cosp, cosr_cosp);
    
    float sinp = 2.0f * (quat->q0 * quat->q2 - quat->q3 * quat->q1);
    if (fabsf(sinp) >= 1.0f) {
        euler.pitch = copysignf(M_PI / 2.0f, sinp);
    } else {
        euler.pitch = asinf(sinp);
    }
    
    float siny_cosp = 2.0f * (quat->q0 * quat->q3 + quat->q1 * quat->q2);
    float cosy_cosp = 1.0f - 2.0f * (quat->q2 * quat->q2 + quat->q3 * quat->q3);
    euler.yaw = atan2f(siny_cosp, cosy_cosp);
    
    // Calculate angles from Euler angles
    calculate_angles_from_euler(&euler, angles);
}

void calculate_angles_from_euler(const euler_angles_t* euler, measurement_angles_t* angles) {
    // Alpha angle: absolute value of pitch (0-90 degrees)
    // Pitch is rotation around Y-axis
    float pitch_deg = fabsf(euler->pitch * RAD_TO_DEG);
    angles->alpha = (pitch_deg > 90.0f) ? 90.0f : pitch_deg;
    
    // Beta angle: yaw converted to 0-360 degrees
    // Yaw is rotation around Z-axis
    float yaw_deg = euler->yaw * RAD_TO_DEG;
    angles->beta = fmodf(yaw_deg + 360.0f, 360.0f);
    
    // Calculate quality score
    angles->quality_score = calculate_quality_score(angles);
}

bool validate_angles(const measurement_angles_t* angles) {
    // Check alpha range (0-90 degrees)
    if (angles->alpha < 0.0f || angles->alpha > 90.0f) {
        return false;
    }
    
    // Check beta range (0-360 degrees)
    if (angles->beta < 0.0f || angles->beta >= 360.0f) {
        return false;
    }
    
    // Check quality score
    if (angles->quality_score < 0.0f || angles->quality_score > 1.0f) {
        return false;
    }
    
    return true;
}

float calculate_quality_score(const measurement_angles_t* angles) {
    // Simple quality score based on angle ranges
    // Higher quality for angles in typical ranges
    float score = 1.0f;
    
    // Penalize extreme angles (may indicate measurement error)
    if (angles->alpha < 5.0f || angles->alpha > 85.0f) {
        score *= 0.9f;
    }
    
    // Additional quality metrics can be added here:
    // - Sensor stability
    // - Measurement consistency
    // - Calibration status
    
    return score;
}

