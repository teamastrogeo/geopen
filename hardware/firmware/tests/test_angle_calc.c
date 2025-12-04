/**
 * Unit Tests for Angle Calculation
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "algorithms/angle_calc.h"
#include "algorithms/sensor_fusion.h"

#define EPSILON 0.01f
#define PI 3.14159265359f

void test_alpha_calculation() {
    printf("Testing alpha angle calculation...\n");
    
    euler_angles_t euler;
    measurement_angles_t angles;
    
    // Test 0 degrees (horizontal)
    euler.pitch = 0.0f;
    euler.yaw = 0.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.alpha - 0.0f) < EPSILON);
    printf("  ✓ 0 degrees: PASS\n");
    
    // Test 45 degrees
    euler.pitch = 45.0f * PI / 180.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.alpha - 45.0f) < EPSILON);
    printf("  ✓ 45 degrees: PASS\n");
    
    // Test 90 degrees (vertical)
    euler.pitch = 90.0f * PI / 180.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.alpha - 90.0f) < EPSILON);
    printf("  ✓ 90 degrees: PASS\n");
    
    printf("Alpha calculation tests: ALL PASS\n\n");
}

void test_beta_calculation() {
    printf("Testing beta angle calculation...\n");
    
    euler_angles_t euler;
    measurement_angles_t angles;
    
    // Test 0 degrees
    euler.yaw = 0.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.beta - 0.0f) < EPSILON);
    printf("  ✓ 0 degrees: PASS\n");
    
    // Test 90 degrees
    euler.yaw = 90.0f * PI / 180.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.beta - 90.0f) < EPSILON);
    printf("  ✓ 90 degrees: PASS\n");
    
    // Test 360 degrees (wrap around)
    euler.yaw = 360.0f * PI / 180.0f;
    calculate_angles_from_euler(&euler, &angles);
    assert(fabsf(angles.beta - 0.0f) < EPSILON);
    printf("  ✓ 360 degrees (wrap): PASS\n");
    
    printf("Beta calculation tests: ALL PASS\n\n");
}

void test_angle_validation() {
    printf("Testing angle validation...\n");
    
    measurement_angles_t angles;
    
    // Valid angles
    angles.alpha = 45.0f;
    angles.beta = 180.0f;
    angles.quality_score = 0.9f;
    assert(validate_angles(&angles) == true);
    printf("  ✓ Valid angles: PASS\n");
    
    // Invalid alpha (too high)
    angles.alpha = 95.0f;
    assert(validate_angles(&angles) == false);
    printf("  ✓ Invalid alpha (high): PASS\n");
    
    // Invalid beta (too high)
    angles.alpha = 45.0f;
    angles.beta = 365.0f;
    assert(validate_angles(&angles) == false);
    printf("  ✓ Invalid beta (high): PASS\n");
    
    printf("Angle validation tests: ALL PASS\n\n");
}

int main() {
    printf("Running angle calculation unit tests...\n\n");
    
    test_alpha_calculation();
    test_beta_calculation();
    test_angle_validation();
    
    printf("All tests passed!\n");
    return 0;
}

