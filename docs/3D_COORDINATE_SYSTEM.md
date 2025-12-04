# GeoPen 3D Coordinate System Reference

## Quick Reference for All Engineers

This document provides a quick reference to the 3D coordinate system used throughout the GeoPen project.

## Coordinate System Definition

### Global Coordinate System
- **Origin (0, 0, 0)**: Center of device tip (contact point)
- **Z-axis**: Device longitudinal axis
  - Positive direction: Upward toward top
  - Range: 0mm (tip) to 180mm (top)
- **X-axis**: Horizontal axis
  - Positive direction: Right side (when viewing from front)
- **Y-axis**: Horizontal axis  
  - Positive direction: Front (away from user)
- **Units**: Millimeters (mm) for distances, Degrees (°) for angles
- **Convention**: Right-handed Cartesian coordinate system

### Visual Reference
```
        Y (Front)
        ↑
        |
        |
        +----→ X (Right)
       /
      /
     Z (Up/Top)
```

## Key Reference Points

| Point | Name | Coordinates (X, Y, Z) | Description |
|-------|------|----------------------|-------------|
| P0 | Tip Center | (0, 0, 0) | Device tip, origin |
| P1 | Top Center | (0, 0, 180) | Device top |
| P2 | Center of Gravity | (0, 0, 90) | Estimated CG |
| P3 | Grip Center | (0, 0, 100) | Grip area |
| P_IMU | IMU Sensor | (0, 0, 15) | **CRITICAL** - Sensor position |
| P_PCB | Main PCB | (0, 0, 90) | PCB center |
| P_BAT | Battery | (0, 0, 140) | Battery center |
| P_PWR_BTN | Power Button | (0, 10, 175) | Power button |
| P_TRIG_BTN | Trigger Button | (10, 0, 50) | Trigger button |
| P_USB | USB-C | (0, 0, 3) | USB connector |
| P_CONTACT | Contact Sensor | (0, 0, 2) | Tip sensor |

## Component Coordinates Summary

### Critical Components

**IMU Sensor** (Accuracy Critical):
- Position: (0, 0, 15) mm
- Alignment: X/Y/Z axes must match device axes
- Tolerance: ±0.1° - **MUST MAINTAIN**

**Main PCB**:
- Center: (0, 0, 90) mm
- Z-range: 70-110mm
- Dimensions: 35-45mm (Z) × 12-18mm (X) × 1.6mm (Y)

**Battery**:
- Center: (0, 0, 140) mm
- Z-range: 115-165mm
- Max diameter: 16mm (cylindrical) or custom shape

### User Interface Components

**Buttons**:
- Power: (0, 10, 175) mm, radial (90° from Z-axis)
- Trigger: (10, 0, 50) mm, radial (90° from Z-axis)

**LEDs** (4 status LEDs):
- LED1: (0, 10, 170) mm
- LED2: (0, 10, 172) mm
- LED3: (0, 10, 174) mm
- LED4: (0, 10, 176) mm

**USB-C Connector**:
- Position: (0, 0, 3) mm
- Orientation: -Z direction (downward)

## Geometric Constraints

### Critical Dimensions
- **Length**: 180mm ±2mm (Z-axis: 0 to 180mm)
- **Diameter**: 20mm outer, 18mm inner (MUST NOT EXCEED)
- **Weight**: <200g (target: 150-180g)
- **Cylindrical Axis**: Z-axis, deviation <0.1°

### Tolerances
- **Position**: ±0.5mm (general), ±0.1mm (critical)
- **Angle**: ±0.1° (critical), ±1° (general)
- **IMU Alignment**: ±0.1° - **CRITICAL**

## Usage in Different Disciplines

### For Mechanical Engineers
- Use coordinates for 3D CAD modeling
- Component placement and fit analysis
- Assembly sequence planning
- Tolerance stack-up analysis

### For Electrical Engineers
- PCB layout with component coordinates
- Connector placement
- Antenna positioning
- Thermal analysis using coordinates

### For Firmware Engineers
- Sensor alignment verification
- Calibration routines
- Coordinate transformation
- Reference for sensor fusion

### For Software Engineers
- Understanding device geometry
- UI element positioning (if display added)
- Data visualization
- Coordinate system documentation

## File Formats

### JSON Format for Point Data
```json
{
  "coordinate_system": {
    "origin": {"x": 0, "y": 0, "z": 0},
    "x_axis": {"x": 1, "y": 0, "z": 0},
    "y_axis": {"x": 0, "y": 1, "z": 0},
    "z_axis": {"x": 0, "y": 0, "z": 1}
  },
  "component": {
    "name": "IMU_Sensor",
    "center": {"x": 0, "y": 0, "z": 15},
    "dimensions": {"length": 3.0, "width": 3.0, "height": 0.95},
    "angles": {"x": 0, "y": 0, "z": 0},
    "tolerance": {"position": 0.5, "angle": 0.1}
  }
}
```

### CSV Format for Point Lists
```csv
Component,X,Y,Z,Description
Tip_Center,0,0,0,Origin
IMU_Sensor,0,0,15,Critical alignment
PCB_Center,0,0,90,Main board
Battery_Center,0,0,140,Power source
```

## Related Documents

- **Complete Specifications**: `docs/mechanical/MECHANICAL_ENGINEER_HANDOVER.md`
- **Component Details**: `docs/mechanical/COMPONENT_DIMENSIONS.md`
- **Hardware Design**: `docs/design/hardware-design.md`
- **Product Specs**: `docs/design/product-specifications.md`

## Notes

- All coordinates are in millimeters (mm)
- All angles are in degrees (°)
- Coordinate system is consistent across all documentation
- Updates to coordinates must be synchronized across all documents

---

**Last Updated**: [Date]  
**Coordinate System Version**: 1.0  
**Status**: Active - Use for all 3D design work

