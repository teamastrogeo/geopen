# GeoPen Component Dimensions Reference

## Purpose

This document provides reference dimensions for components that need to be accommodated in the mechanical design. **Note**: These are estimates and must be confirmed with the electronics team.

## Critical Components

### 1. Battery

#### Option A: Li-ion Cylindrical
- **Model**: 18650 or similar
- **Dimensions**: 
  - Diameter: 18mm
  - Length: 65mm
  - **Note**: Too large for 20mm diameter constraint

#### Option B: Li-ion Flat/Pouch (Recommended)
- **Capacity**: 1000-1500 mAh
- **Estimated Dimensions**:
  - Length: 40-50mm
  - Width: 25-30mm
  - Thickness: 4-6mm
- **Voltage**: 3.7V nominal
- **Shape**: Rectangular or custom shape

#### Option C: Li-poly Custom
- **Capacity**: 1000-1500 mAh
- **Dimensions**: Custom shape to fit enclosure
- **Voltage**: 3.7V nominal
- **Advantage**: Can be shaped to fit space

**Recommendation**: Li-poly custom shape for optimal space utilization

### 2. Main PCB

#### Estimated Dimensions
- **Length**: 35-45mm (to be confirmed)
- **Width**: 12-18mm (to be confirmed)
- **Thickness**: 1.6mm (standard PCB)
- **Shape**: Rectangular or custom

#### Components on PCB
- MCU (nRF52840 or STM32L4)
- BLE antenna (PCB or external)
- Power management IC
- Connectors (USB-C, I2C, etc.)
- Supporting components

**Action Required**: Get exact dimensions from electronics team

### 3. IMU Sensor

#### BMI160 (Recommended)
- **Package**: LGA-14
- **Dimensions**: 
  - Length: 3.0mm
  - Width: 3.0mm
  - Height: 0.95mm
- **Mounting**: Surface mount on PCB or separate board
- **Critical**: Must be aligned with device axis

#### MPU6050 (Alternative)
- **Package**: QFN-24
- **Dimensions**:
  - Length: 4.0mm
  - Width: 4.0mm
  - Height: 0.9mm
- **Mounting**: Surface mount

**Recommendation**: BMI160 for smaller size

### 4. Contact Sensor

#### Option A: Pressure Sensor
- **Type**: MEMS pressure sensor
- **Estimated Size**: 3mm x 3mm x 1mm
- **Location**: Tip of device

#### Option B: Microswitch
- **Type**: Tactile switch
- **Size**: 6mm x 6mm x 3.5mm
- **Location**: Tip of device

**Recommendation**: Pressure sensor for smaller size

### 5. USB-C Connector

#### Standard USB-C
- **Dimensions**:
  - Length: 8.8mm
  - Width: 2.5mm
  - Height: 3.5mm (above PCB)
- **Location**: Bottom of device
- **Requirements**: Protected by cover

### 6. Buttons

#### Power Button
- **Type**: Tactile switch with LED
- **Size**: 6mm x 6mm x 3.5mm (switch)
- **LED**: 3mm or 5mm LED
- **Location**: Top or side

#### Trigger Button
- **Type**: Tactile switch
- **Size**: 6mm x 6mm x 3.5mm
- **Location**: Side, thumb-accessible

### 7. LEDs

#### Status LEDs
- **Type**: 3mm or 5mm LEDs
- **Count**: 3-4 LEDs
- **Colors**: Red, Green, Blue, Yellow
- **Location**: Top or side, visible

### 8. Optional Display

#### OLED Display
- **Size**: 1.3" or smaller
- **Resolution**: 128x64 pixels
- **Dimensions**: ~35mm x 20mm x 2mm
- **Location**: Top or side

**Note**: May not fit in initial design - evaluate space

## Space Allocation Estimate

### Total Length: 180mm

```
┌─────────────────────────────────────────┐
│ Top Section (30mm)                      │
│ - Power button + LEDs                   │
│ - Battery (40-50mm)                     │
│                                         │
│ Middle Section (80mm)                   │
│ - Main PCB (35-45mm)                   │
│ - Connectors                            │
│ - Power management                      │
│                                         │
│ Lower Section (50mm)                    │
│ - IMU sensor (near tip)                 │
│ - Contact sensor (tip)                  │
│ - Trigger button                        │
│                                         │
│ Bottom Section (20mm)                   │
│ - USB-C connector                       │
│ - Tip contact point                     │
└─────────────────────────────────────────┘
```

### Total Diameter: 20mm (CRITICAL CONSTRAINT)

**Internal Diameter**: ~18mm (accounting for wall thickness)

**Space Considerations**:
- Wall thickness: 1-1.5mm
- Battery: ~15-16mm diameter (if cylindrical) or custom shape
- PCB: ~12-15mm width
- Clearance: 1-2mm between components

## Critical Constraints Summary

1. **Maximum Diameter**: 20mm (2.0 cm) - **MUST NOT EXCEED**
2. **Target Length**: 180mm (18 cm) - ±5mm acceptable
3. **Maximum Weight**: 200g - **MUST NOT EXCEED**
4. **IMU Alignment**: Critical for accuracy
5. **IP54 Rating**: Must be achievable

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

## Next Steps

1. **Request from Electronics Team**:
   - PCB dimensions (exact)
   - Battery specifications (exact model)
   - Component heights (maximum)
   - Connector locations

2. **Research**:
   - Battery options that fit constraints
   - Manufacturing methods
   - Material options

3. **Initial Design**:
   - Create concept sketches
   - Evaluate space allocation
   - Identify potential issues

---

**Document Status**: Draft - Awaiting component specifications  
**Last Updated**: [Date]  
**Next Update**: After receiving electronics specifications

