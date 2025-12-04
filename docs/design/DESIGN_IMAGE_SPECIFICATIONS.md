# GeoPen Design Image Specifications

## Overview

This document captures specifications from the design image provided, ensuring alignment between visual design and technical documentation.

## Design Elements from Image

### Physical Design
- **Shape**: Cylindrical, pen-like device
- **Length**: 180mm (confirmed in image)
- **Body Material**: Dark grey metallic (anodized aluminum appearance)
- **Grip**: Textured dark grey rubber/silicone overlay
- **Tip**: Transparent conical tip revealing internal sensor

### Display (Visible in Image)
- **Type**: OLED display (black screen with white text/icons)
- **Location**: Top surface of device
- **Display Content**:
  - "GEOANGLE:" label
  - Power icon (circle with vertical line)
  - Bluetooth icon
  - Angle measurement: "25.7°" (example)
  - Information icon (exclamation mark in circle)
  - Battery level: "BATT: 85%"
- **Size**: Rectangular, embedded in top surface
- **Visibility**: Clear in daylight conditions

### Buttons (Visible in Image)
- **Count**: 2 circular buttons visible
- **Location**: Right side of display
- **Material**: Dark grey, matches body
- **Function**: Power and measurement trigger (inferred)

### Charging Port
- **Type**: USB-C connector
- **Location**: Rear end of device
- **Color**: Silver/metallic
- **Protection**: Visible port (cover not shown in image)

### Annotations from Image

#### IMU Sensor Specifications
- **Type**: 3-axis accelerometer, gyroscope, magnetometer
- **Accuracy**: ±0.57° (shown in image)
  - **Note**: Target specification is ±2-3° for production
  - Image shows ideal/calibrated accuracy
- **Location**: Front tip (visible through transparent tip)

#### Environmental Protection
- **IP Rating**: IP54 (dust and splash resistant)
- **Shock Resistance**: 1m drop protection
- **Design**: Ergonomic for field use

#### Connectivity
- **Bluetooth**: 5.0 connectivity
- **Status**: Bluetooth icon visible on display

## Alignment with Technical Specifications

### Coordinate System
- **Tip Center**: (0, 0, 0) - Origin
- **Display Location**: Estimated (0, 10, 165) mm (top surface)
- **Buttons**: Estimated (10, 0, 165-175) mm (right side)
- **USB-C**: (0, 0, 3) mm (rear)

### Measurement Display
- **Format**: Shows angle measurement (example: 25.7°)
- **Display Type**: Likely showing alpha angle in example
- **Full Display**: Should show both α and β angles
  - Format: "α: 45.0°  β: 120.0°" or separate lines
  - Beta angle: 0-360° range

### 360° Beta Angle Display
- **Display Format Options**:
  1. "BETA: 120.0°" (full 360° range)
  2. "β: 120.0°" (compact)
  3. Circular indicator showing position on 360° circle
- **Update**: Real-time as device rotates around Z-axis

## Design Refinements Based on Image

### Display Integration
- **Recommendation**: Include display in v1.0 design
- **Benefits**: 
  - Immediate angle feedback
  - No need for mobile app for basic measurements
  - Better field usability
- **Trade-off**: Increased cost and complexity

### Accuracy Display
- **Show**: Measurement accuracy/quality score
- **Format**: "±2.3°" or quality percentage
- **Update**: Based on sensor stability

### Status Indicators
- **Power**: Icon on display (shown in image)
- **Bluetooth**: Icon on display (shown in image)
- **Battery**: Percentage display (shown: "BATT: 85%")
- **Measurement**: Visual indicator when measuring

## Implementation Notes

### Display Driver Requirements
- **Interface**: I2C or SPI for OLED
- **Power**: Low power OLED for battery life
- **Brightness**: Adjustable for field conditions
- **Update Rate**: Real-time angle updates (10-20 Hz)

### Button Integration
- **Power Button**: With LED indicator (as per design)
- **Trigger Button**: For measurement
- **Display Control**: Optional button for display settings

### USB-C Integration
- **Location**: Rear end (as shown)
- **Protection**: Cover/cap for IP54 rating
- **Charging**: 5V/1A standard charging

## Next Steps

1. **Finalize Display Specifications**:
   - Exact OLED model selection
   - Display driver implementation
   - UI layout design

2. **Update Mechanical Design**:
   - Incorporate display cutout
   - Button placement refinement
   - USB-C port integration

3. **Firmware Updates**:
   - Display driver code
   - UI rendering for angles
   - Status indicators

4. **Mobile App Integration**:
   - Display can complement mobile app
   - Or replace mobile app for basic use

---

**Design Image Analysis**: Complete  
**Status**: Specifications aligned with design image  
**Last Updated**: [Date]

