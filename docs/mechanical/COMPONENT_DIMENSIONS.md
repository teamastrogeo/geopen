# GeoPen Component Dimensions & 3D Coordinates Reference

## Purpose

This document provides reference dimensions, 3D coordinates, angles, and geometric specifications for all components. Suitable for all engineers (mechanical, electrical, software, firmware) working on 3D design and integration.

## Coordinate System

- **Origin (0, 0, 0)**: Center of device tip (contact point)
- **Z-axis**: Device longitudinal axis (positive = upward toward top)
- **X-axis**: Perpendicular to Z, horizontal plane (positive = right side)
- **Y-axis**: Perpendicular to Z, horizontal plane (positive = front)
- **Units**: Millimeters (mm) for distances, Degrees (°) for angles
- **Precision**: 0.01mm for critical features, 0.1mm for general

## Critical Components

### 1. Battery

#### 3D Coordinates & Geometry
- **Center Point**: P_BAT = (0, 0, 140)
- **Z-range**: 115mm to 165mm
- **Orientation**: Z-axis aligned (0° rotation)

#### Option A: Li-ion Cylindrical
- **Model**: 18650 or similar
- **Dimensions**: 
  - Diameter: 18mm
  - Length: 65mm
  - **Note**: Too large for 20mm diameter constraint
- **Center**: (0, 0, 140)
- **Orientation**: Z-axis (0°)

#### Option B: Li-ion Flat/Pouch (Recommended)
- **Capacity**: 1000-1500 mAh
- **Dimensions**:
  - Length (Z): 40-50mm
  - Width (X): 25-30mm
  - Thickness (Y): 4-6mm
- **Voltage**: 3.7V nominal
- **Shape**: Rectangular or custom shape
- **Center Point**: (0, 0, 140)
- **Corner Points**:
  - P_BAT1 = (-12.5, -3, 115)
  - P_BAT2 = (12.5, -3, 115)
  - P_BAT3 = (12.5, -3, 165)
  - P_BAT4 = (-12.5, -3, 165)
- **Orientation**: X-Z plane, Y-normal

#### Option C: Li-poly Custom (Best Fit)
- **Capacity**: 1000-1500 mAh
- **Dimensions**: Custom shape to fit 18mm inner diameter
- **Voltage**: 3.7V nominal
- **Center Point**: (0, 0, 140)
- **Shape**: Cylindrical segment or custom
- **Max Diameter**: 16mm
- **Length**: 40-50mm

**Recommendation**: Li-poly custom shape for optimal space utilization

### 2. Main PCB

#### 3D Coordinates & Geometry
- **Center Point**: P_PCB = (0, 0, 90)
- **Z-range**: 70mm to 110mm
- **Orientation**: X-Z plane (PCB plane), Y-normal

#### Estimated Dimensions
- **Length (Z)**: 35-45mm (to be confirmed)
- **Width (X)**: 12-18mm (to be confirmed)
- **Thickness (Y)**: 1.6mm (standard PCB)
- **Shape**: Rectangular or custom

#### Corner Points (Estimated)
- P_PCB1 = (-9, -0.8, 72.5)  // Bottom-left-front
- P_PCB2 = (9, -0.8, 72.5)   // Bottom-right-front
- P_PCB3 = (9, -0.8, 107.5)  // Top-right-front
- P_PCB4 = (-9, -0.8, 107.5) // Top-left-front
- P_PCB5 = (-9, 0.8, 72.5)   // Bottom-left-back
- P_PCB6 = (9, 0.8, 72.5)    // Bottom-right-back
- P_PCB7 = (9, 0.8, 107.5)   // Top-right-back
- P_PCB8 = (-9, 0.8, 107.5)  // Top-left-back

#### Mounting Points
- M1 = (-7, 0, 75)
- M2 = (7, 0, 75)
- M3 = (-7, 0, 105)
- M4 = (7, 0, 105)

#### Components on PCB
- MCU (nRF52840 or STM32L4) - Location TBD
- BLE antenna (PCB or external) - Location TBD
- Power management IC - Location TBD
- Connectors (USB-C, I2C, etc.) - Location TBD
- Supporting components - Location TBD

#### Orientation Angles
- **Rotation about X-axis**: 0°
- **Rotation about Y-axis**: 0°
- **Rotation about Z-axis**: 0°
- **PCB Normal Vector**: (0, 1, 0)

**Action Required**: Get exact dimensions and component locations from electronics team

### 3. IMU Sensor (CRITICAL - Accuracy Dependent)

#### 3D Coordinates & Geometry
- **Center Point**: P_IMU = (0, 0, 15)
- **Orientation**: Aligned with device axes (CRITICAL)
- **Alignment Tolerance**: ±0.1° - **MUST MAINTAIN**

#### BMI160 (Recommended)
- **Package**: LGA-14
- **Dimensions**: 
  - Length (X): 3.0mm
  - Width (Y): 3.0mm
  - Height (Z): 0.95mm
- **Center Point**: (0, 0, 15)
- **Corner Points** (on mounting surface):
  - P_IMU1 = (-1.5, -1.5, 14.525)  // Bottom-left
  - P_IMU2 = (1.5, -1.5, 14.525)   // Bottom-right
  - P_IMU3 = (1.5, 1.5, 14.525)    // Top-right
  - P_IMU4 = (-1.5, 1.5, 14.525)   // Top-left
- **Mounting**: Surface mount on PCB or separate board
- **Orientation Angles**:
  - X-axis alignment: 0° ±0.1°
  - Y-axis alignment: 0° ±0.1°
  - Z-axis alignment: 0° ±0.1°
- **Sensor Axes** (must match device axes):
  - Sensor X → Device X: (1, 0, 0)
  - Sensor Y → Device Y: (0, 1, 0)
  - Sensor Z → Device Z: (0, 0, 1)

#### MPU6050 (Alternative)
- **Package**: QFN-24
- **Dimensions**:
  - Length (X): 4.0mm
  - Width (Y): 4.0mm
  - Height (Z): 0.9mm
- **Center Point**: (0, 0, 15)
- **Corner Points**:
  - P_IMU1 = (-2, -2, 14.55)
  - P_IMU2 = (2, -2, 14.55)
  - P_IMU3 = (2, 2, 14.55)
  - P_IMU4 = (-2, 2, 14.55)
- **Mounting**: Surface mount
- **Orientation**: Same as BMI160 (0° ±0.1°)

**Recommendation**: BMI160 for smaller size and better fit

### 4. Contact Sensor

#### 3D Coordinates & Geometry
- **Center Point**: P_CONTACT = (0, 0, 2)
- **Location**: Tip surface
- **Orientation**: Sensing surface facing -Z direction

#### Option A: Pressure Sensor (Recommended)
- **Type**: MEMS pressure sensor
- **Dimensions**: 
  - Length (X): 3.0mm
  - Width (Y): 3.0mm
  - Height (Z): 1.0mm
- **Center Point**: (0, 0, 2)
- **Corner Points**:
  - P_CONT1 = (-1.5, -1.5, 1.5)
  - P_CONT2 = (1.5, -1.5, 1.5)
  - P_CONT3 = (1.5, 1.5, 1.5)
  - P_CONT4 = (-1.5, 1.5, 1.5)
- **Sensing Surface**: Z = 1.5mm (facing downward)
- **Orientation**: 
  - Normal vector: (0, 0, -1)
  - Angle from Z-axis: 180° (downward)

#### Option B: Microswitch
- **Type**: Tactile switch
- **Dimensions**:
  - Length (X): 6.0mm
  - Width (Y): 6.0mm
  - Height (Z): 3.5mm
- **Center Point**: (0, 0, 2)
- **Corner Points**:
  - P_CONT1 = (-3, -3, 0.25)
  - P_CONT2 = (3, -3, 0.25)
  - P_CONT3 = (3, 3, 0.25)
  - P_CONT4 = (-3, 3, 0.25)
- **Actuator**: At Z = 0 (tip surface)
- **Orientation**: Same as pressure sensor

**Recommendation**: Pressure sensor for smaller size

### 5. USB-C Connector

#### 3D Coordinates & Geometry
- **Center Point**: P_USB = (0, 0, 3)
- **Location**: Bottom of device
- **Orientation**: Connector axis along -Z direction

#### Standard USB-C
- **Dimensions**:
  - Length (X): 8.8mm
  - Width (Y): 2.5mm
  - Height (Z): 3.5mm (above PCB)
- **Center Point**: (0, 0, 3)
- **Corner Points** (connector body):
  - P_USB1 = (-4.4, -1.25, 1.25)
  - P_USB2 = (4.4, -1.25, 1.25)
  - P_USB3 = (4.4, 1.25, 1.25)
  - P_USB4 = (-4.4, 1.25, 1.25)
- **Connector Opening**: At Z = 0 (device tip)
- **Orientation**:
  - Connector axis: -Z direction (0, 0, -1)
  - Insertion angle: 0° (straight)
- **Requirements**: Protected by cover, IP54 sealing when closed

### 6. Buttons

#### Power Button
- **Type**: Tactile switch with LED
- **Center Point**: P_PWR_BTN = (0, 10, 175)
- **Dimensions**:
  - Length (X): 6.0mm
  - Width (Y): 6.0mm
  - Height (Z): 3.5mm (switch)
- **Location**: Top section, side
- **Corner Points**:
  - P_PWR1 = (-3, 7, 173.25)
  - P_PWR2 = (3, 7, 173.25)
  - P_PWR3 = (3, 13, 173.25)
  - P_PWR4 = (-3, 13, 173.25)
- **Orientation**:
  - Button axis: Radial (X direction)
  - Angle from Z-axis: 90°
  - Normal vector: (1, 0, 0)
- **LED Location**: P_PWR_LED = (0, 10, 173)
- **LED Dimensions**: 3mm or 5mm diameter

#### Trigger Button
- **Type**: Tactile switch
- **Center Point**: P_TRIG_BTN = (10, 0, 50)
- **Dimensions**:
  - Length (X): 6.0mm
  - Width (Y): 6.0mm
  - Height (Z): 3.5mm
- **Location**: Mid-section, side, thumb-accessible
- **Corner Points**:
  - P_TRIG1 = (7, -3, 48.25)
  - P_TRIG2 = (13, -3, 48.25)
  - P_TRIG3 = (13, 3, 48.25)
  - P_TRIG4 = (7, 3, 48.25)
- **Orientation**:
  - Button axis: Radial (X direction)
  - Angle from Z-axis: 90°
  - Normal vector: (1, 0, 0)
  - Thumb access angle: Optimized for right-hand use

### 7. LEDs

#### Status LEDs - 3D Coordinates
- **Type**: 3mm or 5mm LEDs
- **Count**: 4 LEDs
- **Colors**: Red, Green, Blue, Yellow
- **Location**: Top section, side, visible

#### LED Points
- **LED1 (Power - Green)**: P_LED1 = (0, 10, 170)
  - Diameter: 3mm or 5mm
  - Orientation: Radial outward (X direction)
  - Angle: 90° from Z-axis
  
- **LED2 (Measurement - Blue)**: P_LED2 = (0, 10, 172)
  - Diameter: 3mm or 5mm
  - Orientation: Radial outward (X direction)
  - Angle: 90° from Z-axis
  
- **LED3 (Battery - Red)**: P_LED3 = (0, 10, 174)
  - Diameter: 3mm or 5mm
  - Orientation: Radial outward (X direction)
  - Angle: 90° from Z-axis
  
- **LED4 (Connection - Yellow)**: P_LED4 = (0, 10, 176)
  - Diameter: 3mm or 5mm
  - Orientation: Radial outward (X direction)
  - Angle: 90° from Z-axis

#### LED Spacing
- **Vertical spacing**: 2mm between LEDs
- **Radial position**: 10mm from center (Y = 10)
- **Visibility**: Must be visible in daylight conditions

### 8. Optional Display

#### OLED Display - 3D Coordinates
- **Size**: 1.3" or smaller
- **Resolution**: 128x64 pixels
- **Center Point**: P_DISP = (0, 10, 165)
- **Dimensions**:
  - Length (Z): 35mm
  - Width (Y): 20mm
  - Thickness (X): 2mm
- **Location**: Top section, side
- **Corner Points**:
  - P_DISP1 = (-1, 0, 147.5)   // Bottom-left
  - P_DISP2 = (-1, 20, 147.5)  // Bottom-right
  - P_DISP3 = (-1, 20, 182.5)  // Top-right
  - P_DISP4 = (-1, 0, 182.5)   // Top-left
- **Orientation**:
  - Display plane: Y-Z plane
  - Viewing angle: 0° (perpendicular to X-axis)
  - Normal vector: (1, 0, 0) - facing outward
- **Note**: May not fit in initial design - evaluate space and weight

## 3D Space Allocation with Coordinates

### Total Length: 180mm (Z-axis: 0 to 180mm)

```
Coordinate System: Origin at tip (0,0,0), Z-axis upward

┌─────────────────────────────────────────┐
│ Top Section (Z: 150-180mm)               │
│ - Power button: (0, 10, 175)            │
│ - LEDs: (0, 10, 170-176)                │
│ - Battery: (0, 0, 140), Z: 115-165mm    │
│                                         │
│ Middle Section (Z: 70-150mm)            │
│ - Main PCB: (0, 0, 90), Z: 70-110mm    │
│ - Connectors                            │
│ - Power management                      │
│                                         │
│ Lower Section (Z: 0-70mm)              │
│ - IMU sensor: (0, 0, 15)                │
│ - Contact sensor: (0, 0, 2)             │
│ - Trigger button: (10, 0, 50)           │
│                                         │
│ Bottom Section (Z: 0-20mm)             │
│ - USB-C connector: (0, 0, 3)            │
│ - Tip contact point: (0, 0, 0)         │
└─────────────────────────────────────────┘
     Diameter: 20mm outer, 18mm inner
     X-Y plane: ±9mm radius
```

### Total Diameter: 20mm (CRITICAL CONSTRAINT)

**Geometric Specifications**:
- **Outer Diameter**: 20mm ±0.5mm
- **Inner Diameter**: 18mm (wall thickness: 1mm)
- **Wall Thickness**: 1-1.5mm
- **Circularity**: ±0.1mm
- **Cylindrical Axis**: Z-axis, deviation <0.1°

**Space Considerations**:
- Wall thickness: 1-1.5mm
- Battery: Max 16mm diameter (cylindrical) or custom shape
- PCB: 12-15mm width (X-direction)
- Clearance: 1-2mm between components
- Radial clearance: Components must fit within 9mm radius (18mm inner diameter)

## Critical Constraints Summary (Geometric)

1. **Maximum Diameter**: 20mm (2.0 cm) - **MUST NOT EXCEED**
   - Outer: 20mm ±0.5mm
   - Inner: 18mm (wall: 1mm)
   - Circularity: ±0.1mm

2. **Target Length**: 180mm (18 cm) - ±2mm acceptable
   - Z-axis range: 0mm (tip) to 180mm (top)
   - Straightness: <0.5mm deviation from Z-axis

3. **Maximum Weight**: 200g - **MUST NOT EXCEED**
   - Target: 150-180g
   - Center of gravity: Z = 90mm ±10mm

4. **IMU Alignment**: Critical for accuracy - **MUST MAINTAIN**
   - X-axis: 0° ±0.1°
   - Y-axis: 0° ±0.1°
   - Z-axis: 0° ±0.1°
   - Position: ±0.5mm

5. **IP54 Rating**: Must be achievable
   - Sealing surfaces: O-ring grooves
   - Gap tolerance: <0.1mm when sealed

## Geometric Tolerances Summary

- **Position Tolerance**: ±0.5mm (general), ±0.1mm (critical)
- **Angle Tolerance**: ±0.1° (critical), ±1° (general)
- **Cylindricality**: ±0.1mm
- **Parallelism**: ±0.1° (to Z-axis)
- **Perpendicularity**: ±0.1° (to Z-axis)

## Questions for Electronics Team

### Urgent (Before Design Start)
1. Exact PCB dimensions (length, width, thickness)
2. Maximum component height on PCB
3. Battery exact model and dimensions
4. IMU sensor package and mounting method
5. Connector locations on PCB

### Important (During Design)
6. Antenna type and requirements
7. Thermal requirements
8. EMI shielding needs
9. Component clearance requirements
10. Assembly sequence

## Design Recommendations

### Space Optimization
- Use custom-shaped battery to maximize space
- Minimize wall thickness (1mm if possible)
- Optimize component layout
- Consider stacked PCB design if needed

### Manufacturing Considerations
- Design for 2-part enclosure (top/bottom)
- Consider injection molding vs. machining
- Plan for assembly fixtures
- Design for serviceability

### Accuracy Considerations
- IMU sensor mounting must be rigid
- Minimize flex in sensor mounting
- Consider alignment features
- Plan for calibration jig

## 3D Point Data Export Format

For CAD software and 3D modeling, use this JSON format:

```json
{
  "coordinate_system": {
    "origin": {"x": 0, "y": 0, "z": 0},
    "x_axis": {"x": 1, "y": 0, "z": 0},
    "y_axis": {"x": 0, "y": 1, "z": 0},
    "z_axis": {"x": 0, "y": 0, "z": 1},
    "units": "mm"
  },
  "components": [
    {
      "name": "IMU_Sensor",
      "type": "sensor",
      "center": {"x": 0, "y": 0, "z": 15},
      "dimensions": {"length": 3.0, "width": 3.0, "height": 0.95},
      "orientation": {
        "x_axis": {"x": 1, "y": 0, "z": 0},
        "y_axis": {"x": 0, "y": 1, "z": 0},
        "z_axis": {"x": 0, "y": 0, "z": 1}
      },
      "angles": {"x": 0, "y": 0, "z": 0},
      "tolerance": {"position": 0.5, "angle": 0.1}
    }
  ]
}
```

## Next Steps

1. **Request from Electronics Team**:
   - PCB dimensions (exact) with 3D coordinates
   - Battery specifications (exact model) with dimensions
   - Component heights (maximum) and locations
   - Connector locations with coordinates
   - Component mounting points

2. **3D Modeling**:
   - Create 3D CAD model using provided coordinates
   - Verify component fit and clearances
   - Check geometric constraints
   - Export point data for collaboration

3. **Research**:
   - Battery options that fit constraints
   - Manufacturing methods
   - Material options

4. **Initial Design**:
   - Create concept sketches with coordinates
   - Evaluate space allocation in 3D
   - Identify potential issues
   - Generate point cloud data

---

**Document Status**: Updated with 3D coordinates and geometric specifications  
**Last Updated**: [Date]  
**Coordinate System**: Right-handed Cartesian, Origin at tip center  
**Units**: Millimeters (mm) for distances, Degrees (°) for angles

