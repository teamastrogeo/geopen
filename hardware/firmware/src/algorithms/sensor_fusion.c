/**
 * Sensor Fusion Implementation - Madgwick AHRS Filter
 * 
 * Based on: Madgwick, S.O.H., et al. "An efficient orientation filter for 
 * inertial and inertial/magnetic sensor arrays"
 */

#include "algorithms/sensor_fusion.h"
#include <math.h>

#define PI 3.14159265359f

void sensor_fusion_init(sensor_fusion_t* filter, float beta) {
    // Initialize quaternion to identity (no rotation)
    filter->quat.q0 = 1.0f;
    filter->quat.q1 = 0.0f;
    filter->quat.q2 = 0.0f;
    filter->quat.q3 = 0.0f;
    filter->beta = beta;
    filter->last_update = 0;
}

void sensor_fusion_update(sensor_fusion_t* filter, const imu_data_t* imu_data) {
    float q0 = filter->quat.q0;
    float q1 = filter->quat.q1;
    float q2 = filter->quat.q2;
    float q3 = filter->quat.q3;
    
    // Normalize accelerometer measurement
    float ax = imu_data->accel_x;
    float ay = imu_data->accel_y;
    float az = imu_data->accel_z;
    float norm = sqrtf(ax*ax + ay*ay + az*az);
    if (norm > 0.0f) {
        ax /= norm;
        ay /= norm;
        az /= norm;
    }
    
    // Normalize gyroscope measurement
    float gx = imu_data->gyro_x;
    float gy = imu_data->gyro_y;
    float gz = imu_data->gyro_z;
    
    // Compute feedback
    float f1 = 2.0f * (q1*q3 - q0*q2) - ax;
    float f2 = 2.0f * (q0*q1 + q2*q3) - ay;
    float f3 = 2.0f * (0.5f - q1*q1 - q2*q2) - az;
    
    float j11or24 = 2.0f * q2;
    float j12or23 = 2.0f * q3;
    float j13or22 = 2.0f * q0;
    float j14or21 = 2.0f * q1;
    float j32 = 2.0f * j14or21;
    float j33 = 2.0f * j11or24;
    
    float s1 = j11or24 * f2 - j12or23 * f1;
    float s2 = j13or22 * f1 + j14or21 * f2 - j32 * f3;
    float s3 = j14or21 * f1 - j13or22 * f2 + j33 * f3;
    
    // Normalize step magnitude
    norm = sqrtf(s1*s1 + s2*s2 + s3*s3);
    if (norm > 0.0f) {
        s1 /= norm;
        s2 /= norm;
        s3 /= norm;
    }
    
    // Compute rate of change of quaternion
    float qDot1 = 0.5f * (-q1*gx - q2*gy - q3*gz) - filter->beta * s1;
    float qDot2 = 0.5f * (q0*gx + q2*gz - q3*gy) - filter->beta * s2;
    float qDot3 = 0.5f * (q0*gy - q1*gz + q3*gx) - filter->beta * s3;
    float qDot4 = 0.5f * (q0*gz + q1*gy - q2*gx) - filter->beta * s3;
    
    // Integrate to yield quaternion
    float dt = 0.01f; // Assume 100Hz sampling rate
    q0 += qDot1 * dt;
    q1 += qDot2 * dt;
    q2 += qDot3 * dt;
    q3 += qDot4 * dt;
    
    // Normalize quaternion
    filter->quat.q0 = q0;
    filter->quat.q1 = q1;
    filter->quat.q2 = q2;
    filter->quat.q3 = q3;
    quaternion_normalize(&filter->quat);
}

void quaternion_to_euler(const quaternion_t* quat, euler_angles_t* euler) {
    float q0 = quat->q0;
    float q1 = quat->q1;
    float q2 = quat->q2;
    float q3 = quat->q3;
    
    // Roll (x-axis rotation)
    float sinr_cosp = 2.0f * (q0 * q1 + q2 * q3);
    float cosr_cosp = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
    euler->roll = atan2f(sinr_cosp, cosr_cosp);
    
    // Pitch (y-axis rotation)
    float sinp = 2.0f * (q0 * q2 - q3 * q1);
    if (fabsf(sinp) >= 1.0f) {
        euler->pitch = copysignf(PI / 2.0f, sinp);
    } else {
        euler->pitch = asinf(sinp);
    }
    
    // Yaw (z-axis rotation)
    float siny_cosp = 2.0f * (q0 * q3 + q1 * q2);
    float cosy_cosp = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
    euler->yaw = atan2f(siny_cosp, cosy_cosp);
}

void quaternion_normalize(quaternion_t* quat) {
    float norm = sqrtf(quat->q0*quat->q0 + quat->q1*quat->q1 + 
                       quat->q2*quat->q2 + quat->q3*quat->q3);
    if (norm > 0.0f) {
        quat->q0 /= norm;
        quat->q1 /= norm;
        quat->q2 /= norm;
        quat->q3 /= norm;
    }
}

