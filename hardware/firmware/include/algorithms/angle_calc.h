/**
 * Angle Calculation
 * 
 * Calculates alpha and beta angles from orientation data
 */

#ifndef ANGLE_CALC_H
#define ANGLE_CALC_H

#include "sensor_fusion.h"

// Measurement angles structure
typedef struct {
    float alpha;  // Alpha angle (0-90 degrees)
    float beta;   // Beta angle (0-360 degrees)
    float quality_score;  // Quality score (0.0-1.0)
} measurement_angles_t;

/**
 * Calculate alpha and beta angles from quaternion
 * @param quat Pointer to quaternion
 * @param angles Pointer to measurement_angles_t structure to fill
 */
void calculate_angles(const quaternion_t* quat, measurement_angles_t* angles);

/**
 * Calculate alpha and beta angles from Euler angles
 * @param euler Pointer to euler_angles_t structure
 * @param angles Pointer to measurement_angles_t structure to fill
 */
void calculate_angles_from_euler(const euler_angles_t* euler, measurement_angles_t* angles);

/**
 * Validate calculated angles
 * @param angles Pointer to measurement_angles_t structure
 * @return true if angles are valid
 */
bool validate_angles(const measurement_angles_t* angles);

/**
 * Calculate quality score for measurement
 * @param angles Pointer to measurement_angles_t structure
 * @return Quality score (0.0-1.0)
 */
float calculate_quality_score(const measurement_angles_t* angles);

#endif // ANGLE_CALC_H

