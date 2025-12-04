# GeoPen Measurement Mechanism - 360° Beta Angle Explanation

## Overview

This document explains how GeoPen measures 360° beta angles using IMU sensors and the device's 3D coordinate system.

## Beta Angle (β) - 360° Circumferential Measurement

### Definition
**Beta (β) Angle**: The circumferential angle around the core's longitudinal axis, measured from a reference line to the feature trace on the core surface.

**Range**: 0° to 360° (full circle)

### How It Works

#### 1. Physical Setup
```
Core Sample (Cylindrical)
    │
    │ Reference Line (0°)
    │
    ├─── GeoPen Device ────┐
    │                       │
    │    [Tip Contact]      │
    │         │             │
    │    IMU Sensor         │  ← Measures device orientation
    │    at (0,0,15)mm      │
    │         │             │
    └───────────────────────┘
            │
            │ Device Z-axis aligned with core axis
            │
    Feature Trace (at angle β)
```

#### 2. Coordinate System Alignment

**Device Coordinate System**:
- **Z-axis**: Device longitudinal axis (aligned with core axis)
- **X-axis**: Horizontal (right side)
- **Y-axis**: Horizontal (front)

**IMU Sensor Position**: (0, 0, 15) mm from tip
- Sensor X-axis → Device X-axis
- Sensor Y-axis → Device Y-axis  
- Sensor Z-axis → Device Z-axis

#### 3. Measurement Process

**Step 1: Device Placement**
1. Place GeoPen tip on core surface at feature trace
2. Align device Z-axis parallel to core longitudinal axis
3. Ensure device is perpendicular to core surface

**Step 2: Reference Alignment**
- Device X-axis defines 0° reference direction
- This can be calibrated relative to core reference line

**Step 3: Orientation Measurement**
1. IMU sensor reads device orientation in 3D space
2. Sensor fusion algorithm calculates quaternion
3. Quaternion converted to Euler angles (roll, pitch, yaw)

**Step 4: Beta Angle Calculation**
```
Beta (β) = Yaw angle around Z-axis
- Yaw angle: Rotation around device Z-axis
- Range: -180° to +180° (from sensor)
- Converted to: 0° to 360° (for display)
- Formula: β = (yaw + 360°) mod 360°
```

#### 4. 360° Measurement Visualization

```
        Top View (Looking down Z-axis)
        
        0°/360°
           ↑
           │
           │ Reference Line
           │
   270° ←──┼──→ 90°
           │
           │
           │
         180°
        
        Beta angle measured clockwise from 0°
        
        Example: Feature at 120° position
        - Device rotated 120° clockwise
        - IMU detects rotation around Z-axis
        - Beta = 120°
```

### Technical Implementation

#### Sensor Fusion
- **Input**: Accelerometer + Gyroscope (6-axis IMU)
- **Optional**: Magnetometer (9-axis IMU) for absolute reference
- **Algorithm**: Madgwick AHRS filter
- **Output**: Quaternion representing device orientation

#### Angle Calculation
```c
// From quaternion to Euler angles
yaw = atan2(2*(q0*q3 + q1*q2), 1 - 2*(q2² + q3²))

// Convert to 0-360° range
beta = (yaw * 180/π + 360) % 360
```

#### Accuracy Considerations

**For 360° Beta Measurement**:
- **Magnetometer helps**: Provides absolute heading reference
- **Without magnetometer**: Relative measurement (needs calibration)
- **Accuracy**: ±2-3° (with proper calibration)
- **Critical**: IMU sensor alignment ±0.1° tolerance

### Reference Line Calibration

**Method 1: Absolute Reference (with Magnetometer)**
- Device knows magnetic north
- User aligns device X-axis with core reference line
- Beta angle measured relative to magnetic north
- Requires initial calibration

**Method 2: Relative Reference (without Magnetometer)**
- User sets 0° reference by pressing calibration button
- All subsequent measurements relative to this reference
- Device rotation around Z-axis measured

### Measurement Workflow

```
1. Power on device
2. Place tip on core surface at feature trace
3. Align device Z-axis with core axis
4. [Optional] Calibrate reference (set 0°)
5. Press trigger button
6. Device measures:
   - Alpha: Inclination (0-90°)
   - Beta: Circumferential angle (0-360°)
7. Data transmitted to mobile app
8. Display shows both angles
```

### Visual Example

**Core Sample with Feature**:
```
        Side View                    Top View
    ┌─────────────┐              ┌─────────────┐
    │             │              │     0°      │
    │    Core     │              │     ↑      │
    │   Sample    │              │     │      │
    │             │              │ 120°│      │ ← Feature
    │   Feature   │              │  ←──┼──    │
    │    Trace    │              │     │      │
    └─────────────┘              └─────────────┘
         │                              │
         │ Alpha = 45°                  │ Beta = 120°
         │ (inclination)                │ (circumferential)
         ↓                              ↓
```

### Accuracy Factors

**Critical for 360° Measurement**:
1. **IMU Alignment**: Sensor must be aligned with device axes (±0.1°)
2. **Device Alignment**: Z-axis parallel to core axis
3. **Calibration**: Reference line calibration
4. **Sensor Quality**: High-quality IMU with magnetometer preferred
5. **Stability**: Hold device steady during measurement

### Display on Device (from design image)

Based on the design image showing:
- **Display**: Shows "GEOANGLE: 25.7°" (example measurement)
- **Battery**: "BATT: 85%"
- **Status Icons**: Power, Bluetooth

**For Beta Angle Display**:
- Can show: "α: 45.0°  β: 120.0°"
- Or: "ALPHA: 45.0°" and "BETA: 120.0°"
- Full 360° range displayed

## Comparison with Manual Tools

### Manual Goniometer
- User visually reads angle from protractor
- Limited to ±5° accuracy
- Requires good lighting
- Manual data entry

### GeoPen Digital Measurement
- Automatic angle calculation
- ±2-3° accuracy (target)
- Works in various lighting
- Instant digital data transfer
- 360° full range measurement

## Technical Specifications (from design image)

Based on the design image:
- **IMU Sensor**: 3-axis accelerometer, gyroscope, magnetometer
- **Accuracy**: ±0.57° (as shown in image, target: ±2-3°)
- **Display**: OLED screen showing angles
- **Connectivity**: Bluetooth 5.0
- **Protection**: IP54 dust/splash resistant
- **Durability**: Shock resistant to 1m drop
- **Design**: Ergonomic for field use

## Related Documents

- **3D Coordinates**: `docs/mechanical/COMPONENT_DIMENSIONS.md`
- **Angle Calculation Code**: `hardware/firmware/src/algorithms/angle_calc.c`
- **Sensor Fusion**: `hardware/firmware/src/algorithms/sensor_fusion.c`
- **Best Practices**: `docs/research/best-practices.md`

---

**Last Updated**: [Date]  
**Status**: Design Specification

