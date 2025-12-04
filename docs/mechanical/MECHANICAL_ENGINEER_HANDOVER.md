# GeoPen - Engineering Design Package (All Engineers)

## Overview

This document provides comprehensive 3D design information, geometric specifications, and coordinate systems for all engineers (mechanical, electrical, software, firmware) working on the GeoPen project. All components include 3D coordinate points, angles, lengths, and geometric relationships.

**Project**: GeoPen - Core Alpha/Beta Angle Measurement Device  
**Handover Date**: [Date]  
**Target Timeline**: 3-4 months for prototype design  
**Coordinate System**: Right-handed Cartesian (X, Y, Z) with origin at device tip center

## Executive Summary

GeoPen is a pencil-like device for measuring geological core angles. This document provides complete 3D geometric specifications, coordinate systems, and design constraints for collaborative engineering work across all disciplines.

## 3D Coordinate System & Reference Points

### Global Coordinate System
- **Origin (0, 0, 0)**: Center of device tip (contact point)
- **Z-axis**: Device longitudinal axis (positive = upward toward top)
- **X-axis**: Perpendicular to Z, horizontal plane (positive = right side)
- **Y-axis**: Perpendicular to Z, horizontal plane (positive = front)
- **Units**: Millimeters (mm)
- **Angle Convention**: Right-hand rule, degrees

### Key Reference Points
```
Tip Center:        P0 = (0, 0, 0)
Top Center:         P1 = (0, 0, 180)
Center of Gravity:  P2 = (0, 0, 90) [estimated]
Grip Center:        P3 = (0, 0, 100)
```

## Critical Requirements

### Form Factor (Geometric Specifications)
- **Shape**: Cylindrical, pencil-like
- **Length**: 180 mm (18 cm) - **CRITICAL**
  - Tip to Top: 180 mm
  - Tolerance: ±2 mm
- **Diameter**: 20 mm (2.0 cm) at grip - **CRITICAL**
  - Outer diameter: 20 mm
  - Inner diameter: 18 mm (wall thickness: 1 mm)
  - Tolerance: ±0.5 mm
- **Weight**: 150-180 grams (target: <200g) - **CRITICAL**
- **Ergonomics**: Comfortable grip for extended field use
- **Cylindrical Axis Alignment**: Z-axis, deviation <0.1° - **CRITICAL**

### Environmental Protection
- **IP Rating**: IP54 minimum (dust and splash resistant)
- **Operating Temperature**: -10°C to 50°C
- **Storage Temperature**: -20°C to 60°C
- **Shock Resistance**: Survive 1m drop onto concrete
- **Humidity**: 0-95% RH (non-condensing)

### Materials
- **Body**: Anodized aluminum (preferred) or reinforced plastic
- **Grip**: Textured rubber or silicone overlay
- **Tip**: Durable contact point (stainless steel or ceramic)
- **Sealing**: O-rings for IP54 rating

## Component Integration Requirements

### Electronics to Accommodate

#### 1. Main PCB Assembly
- **Size**: TBD (to be provided by electronics team)
- **Location**: Central section of device
- **Mounting**: Secure, vibration-resistant
- **Connections**: I2C, power, BLE antenna

#### 2. Battery
- **Type**: Li-ion or Li-poly
- **Voltage**: 3.7V
- **Capacity**: 1000-1500 mAh
- **Size**: Must fit within 2cm diameter constraint
- **Location**: Upper section
- **Requirements**: 
  - Easy replacement (if needed)
  - Secure mounting
  - Protection from impact

#### 3. IMU Sensor (Critical - 360° Beta Measurement)
- **Type**: 9-axis IMU recommended (BMI160 + magnetometer, MPU6050 + magnetometer, or ICM-20948)
  - **Why 9-axis**: Magnetometer enables absolute 360° beta angle measurement
  - **Alternative**: 6-axis IMU works but requires relative calibration
- **Size**: ~3mm x 3mm x 1mm (package dependent)
- **Location**: (0, 0, 15) mm from tip center - **CRITICAL POSITION**
- **Critical Requirements**:
  - **Fixed orientation** relative to device axis
  - **Vibration-resistant mounting**
  - **Proper alignment** (critical for accuracy)
    - X-axis alignment: 0° ±0.1°
    - Y-axis alignment: 0° ±0.1°
    - Z-axis alignment: 0° ±0.1°
  - **Minimal flex** in mounting structure
  - **Magnetometer placement**: Must be away from metal components (affects 360° measurement)
- **360° Beta Angle**: 
  - Measured as rotation around Z-axis (device longitudinal axis)
  - Magnetometer provides absolute heading reference
  - Range: 0° to 360° (full circle)
  - See `docs/design/MEASUREMENT_MECHANISM.md` for details

#### 4. Contact Sensor
- **Type**: Pressure sensor or microswitch
- **Location**: Tip of device
- **Requirements**:
  - Contact with core surface
  - Protected from damage
  - Reliable actuation

#### 5. USB-C Connector
- **Location**: Bottom of device
- **Requirements**:
  - Protected by cover/cap
  - IP54 sealing when closed
  - Easy access for charging

#### 6. Buttons
- **Power Button**: Top or side, with LED indicator
- **Trigger Button**: Side, thumb-accessible
- **Requirements**:
  - Tactile feedback
  - IP54 sealing
  - LED visibility

#### 7. LEDs
- **Count**: 3-4 LEDs
- **Location**: Top or side, visible during use
- **Requirements**:
  - Visible in daylight
  - IP54 sealing
  - Color coding (power, measurement, battery, connection)

#### 8. Display (Recommended - Shown in Design)
- **Type**: Small OLED (1.3" or smaller, 128x64 pixels)
- **Center Point**: P_DISP = (0, 10, 165) mm
- **Location**: Top surface, visible during use
- **Dimensions**: ~35mm x 20mm x 2mm
- **Display Content**:
  - Alpha angle (0-90°)
  - Beta angle (0-360°) - **Full circle display**
  - Battery level percentage
  - Status icons (power, Bluetooth)
  - Measurement quality indicator
- **Requirements**:
  - Visible in various lighting (daylight readable)
  - Protected from damage
  - IP54 sealing
  - Low power consumption
  - Real-time angle updates (10-20 Hz)

### 3D Component Layout with Coordinates

```
Coordinate System: Origin at tip center, Z-axis upward
All coordinates in mm: (X, Y, Z)

┌─────────────────────────────────────┐
│  [Power Button] [LEDs]              │ ← Top Z=180mm
│  Power Button: (0, 10, 175)         │
│  LEDs: (0, 10, 170-175)             │
│                                     │
│  ┌─────────────────────────────┐   │
│  │ Battery (1000-1500mAh)      │   │
│  │ Center: (0, 0, 140)         │   │
│  │ Length: 40-50mm             │   │
│  │ Z-range: 115-165mm          │   │
│  │ Diameter: 16mm max          │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │ Main PCB                    │   │
│  │ Center: (0, 0, 90)          │   │
│  │ Length: 30-40mm             │   │
│  │ Z-range: 70-110mm           │   │
│  │ Width: 12-15mm              │   │
│  │ Thickness: 1.6mm            │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │ IMU Sensor (CRITICAL)       │   │
│  │ Center: (0, 0, 15)          │   │
│  │ Size: 3x3x1mm               │   │
│  │ Alignment: Z-axis parallel  │   │
│  │ Angle tolerance: ±0.1°     │   │
│  └─────────────────────────────┘   │
│                                     │
│  [Trigger Button]                  │
│  Center: (10, 0, 50)               │
│  Angle: 90° from Z-axis            │
│                                     │
│  ┌─────────────────────────────┐   │
│  │ Contact Sensor              │   │
│  │ Center: (0, 0, 2)           │   │
│  │ At tip surface              │   │
│  └─────────────────────────────┘   │
│                                     │
│  [USB-C Port]                      │ ← Bottom Z=0-5mm
│  Center: (0, 0, 3)                 │
│  Orientation: -Z direction          │
│  [Tip - Contact Point]             │
│  Origin: (0, 0, 0)                 │
└─────────────────────────────────────┘
     Diameter: 20mm outer, 18mm inner
     Z-axis: 0mm (tip) to 180mm (top)
```

### Component Coordinate Points

#### 1. Main PCB Assembly
- **Center Point**: P_PCB = (0, 0, 90)
- **Dimensions**: 
  - Length (Z): 30-40mm
  - Width (X): 12-15mm
  - Thickness (Y): 1.6mm
- **Z-range**: 70mm to 110mm
- **Orientation**: 
  - PCB plane: X-Z plane
  - Normal vector: (0, 1, 0)
  - Angle: 0° rotation about Z-axis
- **Mounting Points**: 
  - M1 = (-7, 0, 75)
  - M2 = (7, 0, 75)
  - M3 = (-7, 0, 105)
  - M4 = (7, 0, 105)

#### 2. Battery
- **Center Point**: P_BAT = (0, 0, 140)
- **Dimensions**:
  - Length (Z): 40-50mm
  - Diameter: 16mm max (cylindrical) or 25x30x5mm (flat)
- **Z-range**: 115mm to 165mm
- **Orientation**: Z-axis aligned
- **Mounting Points**: TBD based on battery type

#### 3. IMU Sensor (CRITICAL - Accuracy Dependent)
- **Center Point**: P_IMU = (0, 0, 15)
- **Dimensions**: 
  - Length: 3.0mm
  - Width: 3.0mm
  - Height: 0.95mm
- **Orientation**: 
  - Sensor X-axis: Device X-axis (parallel)
  - Sensor Y-axis: Device Y-axis (parallel)
  - Sensor Z-axis: Device Z-axis (parallel)
  - **Alignment Tolerance**: ±0.1° - **CRITICAL**
- **Mounting**: 
  - Surface mount on PCB or dedicated board
  - Mounting plane: X-Z plane at Y=0
  - Reference corner: (-1.5, 0, 13.5)

#### 4. Contact Sensor
- **Center Point**: P_CONTACT = (0, 0, 2)
- **Dimensions**: 3mm x 3mm x 1mm (pressure sensor) or 6mm x 6mm x 3.5mm (switch)
- **Location**: Tip surface
- **Orientation**: 
  - Sensing surface: -Z direction (downward)
  - Normal vector: (0, 0, -1)

#### 5. USB-C Connector
- **Center Point**: P_USB = (0, 0, 3)
- **Dimensions**: 8.8mm x 2.5mm x 3.5mm
- **Location**: Bottom of device
- **Orientation**: 
  - Connector axis: -Z direction
  - Insertion angle: 0° (straight)
- **Access**: Through bottom cover

#### 6. Power Button
- **Center Point**: P_PWR_BTN = (0, 10, 175)
- **Dimensions**: 6mm x 6mm x 3.5mm
- **Location**: Top section, side
- **Orientation**: 
  - Button axis: Radial (X direction)
  - Angle from Z-axis: 90°
- **LED Location**: P_PWR_LED = (0, 10, 173)

#### 7. Trigger Button
- **Center Point**: P_TRIG_BTN = (10, 0, 50)
- **Dimensions**: 6mm x 6mm x 3.5mm
- **Location**: Mid-section, side
- **Orientation**: 
  - Button axis: Radial (X direction)
  - Angle from Z-axis: 90°
  - Thumb-accessible position

#### 8. Status LEDs
- **LED1 (Power)**: P_LED1 = (0, 10, 170)
- **LED2 (Measurement)**: P_LED2 = (0, 10, 172)
- **LED3 (Battery)**: P_LED3 = (0, 10, 174)
- **LED4 (Connection)**: P_LED4 = (0, 10, 176)
- **Dimensions**: 3mm or 5mm diameter
- **Orientation**: Radial outward (visible from side)

#### 9. Optional Display
- **Center Point**: P_DISP = (0, 10, 165)
- **Dimensions**: 35mm x 20mm x 2mm
- **Location**: Top section, side
- **Orientation**: 
  - Display plane: Y-Z plane
  - Viewing angle: 0° (perpendicular to X-axis)

## Geometric Design Constraints

### Critical Constraints
1. **Diameter**: Maximum 20mm (2.0 cm) - **MUST NOT EXCEED**
   - Outer diameter: 20mm ±0.5mm
   - Inner diameter: 18mm (wall thickness: 1mm)
   - Circularity tolerance: ±0.1mm

2. **Length**: 180mm (18 cm) - **TARGET, ±2mm acceptable**
   - Tip to top: 180mm ±2mm
   - Straightness: <0.5mm deviation from Z-axis

3. **Weight**: <200g - **MUST NOT EXCEED**
   - Target: 150-180g
   - Center of gravity: Z = 90mm ±10mm

4. **IMU Alignment**: Sensor axis must align with device axis - **CRITICAL**
   - X-axis alignment: 0° ±0.1°
   - Y-axis alignment: 0° ±0.1°
   - Z-axis alignment: 0° ±0.1°
   - Position tolerance: ±0.5mm in X, Y, Z

5. **IP54 Rating**: Must be achievable with design
   - Sealing surfaces: O-ring grooves
   - Gap tolerance: <0.1mm when sealed

### Geometric Tolerances
- **Cylindricality**: ±0.1mm
- **Parallelism**: ±0.1° (to Z-axis)
- **Perpendicularity**: ±0.1° (to Z-axis)
- **Position**: ±0.5mm (component placement)
- **Angle**: ±0.1° (critical components), ±1° (non-critical)

### Manufacturing Constraints
- **Volume**: Low to medium volume (1000-5000 units/year initially)
- **Cost Target**: Enclosure cost <$50 per unit (manufacturing)
- **Tooling**: Consider injection molding vs. machining
- **Assembly**: Design for easy assembly and serviceability

### User Experience Constraints
- **Grip**: Must be comfortable for extended use
- **Balance**: Center of gravity near grip area
- **Accessibility**: Buttons easily accessible
- **Visibility**: LEDs visible in field conditions

## 3D Design Considerations

### Coordinate System for 3D Modeling
- **CAD Software**: Use standard coordinate system
- **Origin**: Tip center (0, 0, 0)
- **Units**: Millimeters
- **Precision**: 0.01mm for critical features, 0.1mm for general

### Geometric Relationships
- **Cylindrical Symmetry**: Device is rotationally symmetric about Z-axis
- **Component Alignment**: All components aligned to Z-axis unless specified
- **Angular Relationships**:
  - Buttons: 90° from Z-axis (radial)
  - LEDs: 90° from Z-axis (radial)
  - USB-C: 0° (parallel to Z-axis, -Z direction)

### Thermal Management (3D Considerations)
- **Heat Sources**: MCU at (0, 0, 90), battery at (0, 0, 140)
- **Heat Flow**: Radial outward, axial along Z-axis
- **Requirements**: 
  - No active cooling
  - Passive heat dissipation
  - Temperature monitoring (sensor compensation)
- **Thermal Paths**: 
  - PCB to enclosure: Direct contact
  - Battery to enclosure: Air gap + contact

### Antenna Design (3D Considerations)
- **BLE Antenna**: Must be integrated or external
- **Location Options**:
  - PCB antenna: On PCB at (0, 0, 90), orientation TBD
  - External antenna: Top section, Z=160-180mm
- **Requirements**:
  - 10-meter range minimum
  - Not blocked by metal enclosure
  - Antenna axis: Prefer Z-axis or radial
  - Clearance: 5mm minimum from metal
- **3D Considerations**:
  - Antenna pattern: Omni-directional preferred
  - Ground plane: PCB ground plane location
  - Enclosure effect: Metal enclosure may affect pattern

### Assembly Method
- **Options**:
  1. Screw-based assembly (more secure, serviceable)
  2. Snap-fit (faster, lower cost)
  3. Hybrid approach
- **Recommendation**: Screw-based for prototype, evaluate for production

### Serviceability
- **Battery Replacement**: Consider user-replaceable vs. sealed
- **Repair**: Design for field repair if possible
- **Calibration**: Access to calibration points if needed

## 3D Collaboration Guidelines

### For All Engineers
- **Coordinate System**: Use global coordinate system defined above
- **Units**: Millimeters (mm) for all dimensions
- **Angles**: Degrees (°) for all angles
- **Precision**: 
  - Critical features: 0.01mm
  - General features: 0.1mm
  - Angles: 0.1° (critical), 1° (general)

### File Exchange Formats
- **3D Models**: STEP (.step, .stp), IGES (.iges, .igs)
- **2D Drawings**: PDF, DWG, DXF
- **Point Data**: CSV, JSON with coordinate arrays
- **CAD Native**: Keep native formats for collaboration

### Component Point Data Format
```json
{
  "component_name": "IMU_Sensor",
  "center_point": {"x": 0, "y": 0, "z": 15},
  "dimensions": {"length": 3.0, "width": 3.0, "height": 0.95},
  "orientation": {
    "x_axis": {"x": 1, "y": 0, "z": 0},
    "y_axis": {"x": 0, "y": 1, "z": 0},
    "z_axis": {"x": 0, "y": 0, "z": 1}
  },
  "mounting_points": [
    {"x": -1.5, "y": 0, "z": 13.5},
    {"x": 1.5, "y": 0, "z": 13.5}
  ],
  "tolerance": {
    "position": 0.5,
    "angle": 0.1
  }
}
```

## Reference Documents

### Must Read (All Engineers)
1. **`docs/design/product-specifications.md`** - Complete specifications with geometric data
2. **`docs/design/hardware-design.md`** - Hardware architecture and 3D layout
3. **`docs/requirements/product-requirements.md`** - Full requirements
4. **`docs/mechanical/COMPONENT_DIMENSIONS.md`** - Component dimensions and coordinates

### Should Read
4. **`docs/research/existing-tools.md`** - Competitive products for reference
5. **`docs/research/best-practices.md`** - Field use considerations
6. **`docs/testing/test-plan.md`** - Testing requirements

### Reference
7. **`docs/PROJECT_PLAN.md`** - Overall project timeline
8. **`IMPLEMENTATION_STATUS.md`** - Current project status

## Deliverables Expected

### Phase 1: Concept Design (Month 1)
- [ ] 3D concept models (2-3 options)
- [ ] Material selection analysis
- [ ] Component fit analysis
- [ ] Manufacturing method evaluation
- [ ] Cost estimate
- [ ] Design review presentation

### Phase 2: Detailed Design (Month 2)
- [ ] Detailed 3D CAD model
- [ ] 2D engineering drawings
- [ ] Tolerance analysis
- [ ] Assembly drawings
- [ ] Bill of Materials (BOM)
- [ ] Material specifications

### Phase 3: Prototype (Month 3)
- [ ] 3D printed prototype (for fit check)
- [ ] Machined prototype (for testing)
- [ ] Assembly instructions
- [ ] Test results
- [ ] Design refinements

### Phase 4: Production Design (Month 4)
- [ ] Final production-ready design
- [ ] Tooling design (if injection molding)
- [ ] Quality control specifications
- [ ] Manufacturing documentation

## Key Contacts & Information

### Electronics Team
- **PCB Design**: [Contact] - For PCB dimensions and mounting
- **Component Selection**: [Contact] - For component sizes
- **Sensor Integration**: [Contact] - For IMU mounting requirements

### Project Management
- **Project Manager**: [Contact]
- **Timeline**: See `docs/PROJECT_PLAN.md`

### Questions & Clarifications
- **Technical Questions**: [Contact]
- **Requirements Clarification**: [Contact]

## Critical Design Decisions Needed

### Immediate Decisions Required
1. **Material Selection**: Aluminum vs. Plastic
   - Aluminum: Better durability, higher cost
   - Plastic: Lower cost, lighter, easier molding
   - **Recommendation**: Start with aluminum for prototype

2. **Assembly Method**: Screw vs. Snap-fit
   - Screw: More secure, serviceable
   - Snap-fit: Faster assembly, lower cost
   - **Recommendation**: Screw-based for prototype

3. **Battery Access**: Sealed vs. Replaceable
   - Sealed: Better IP rating, simpler design
   - Replaceable: User convenience, design complexity
   - **Recommendation**: Sealed for v1.0

4. **Display**: Include or not?
   - With display: Higher cost, more complex
   - Without display: Simpler, relies on mobile app
   - **Recommendation**: Start without, add if needed

### Design Trade-offs to Consider
- **Weight vs. Durability**: Lighter materials may be less durable
- **Cost vs. Quality**: Balance manufacturing cost with quality
- **Size vs. Functionality**: Fit all components within constraints
- **Serviceability vs. Sealing**: Easy repair vs. IP rating

## Testing Requirements

### Mechanical Testing
- [ ] Drop test (1m onto concrete)
- [ ] IP54 ingress protection test
- [ ] Temperature cycling test
- [ ] Vibration test (field conditions)
- [ ] Button durability test (10,000+ presses)
- [ ] USB connector durability test

### Fit & Function Testing
- [ ] Component fit verification
- [ ] Assembly/disassembly test
- [ ] Button actuation test
- [ ] LED visibility test
- [ ] Grip comfort evaluation

## Timeline & Milestones

### Month 1: Concept Design
- Week 1-2: Research and initial concepts
- Week 3: Concept review and selection
- Week 4: Detailed concept development

### Month 2: Detailed Design
- Week 1-2: CAD modeling
- Week 3: Engineering drawings
- Week 4: Design review

### Month 3: Prototype
- Week 1: 3D printing
- Week 2: Fit check and refinement
- Week 3: Machined prototype
- Week 4: Testing and evaluation

### Month 4: Production Design
- Week 1-2: Design refinements
- Week 3: Final documentation
- Week 4: Handover to manufacturing

## Success Criteria

### Design Success
- [ ] All components fit within size constraints
- [ ] Weight target met (<200g)
- [ ] IP54 rating achievable
- [ ] Manufacturing cost within budget
- [ ] Assembly time reasonable (<10 minutes)

### Functional Success
- [ ] Buttons accessible and functional
- [ ] LEDs visible in field conditions
- [ ] USB connector accessible
- [ ] Grip comfortable for extended use
- [ ] Device balanced and ergonomic

## Notes & Special Considerations

### Field Use Considerations
- Device will be used in harsh field conditions
- Users may wear gloves
- Device may be dropped or mishandled
- Must work in various weather conditions
- Battery life critical (8+ hours)

### Accuracy Requirements
- IMU sensor alignment is **CRITICAL** for measurement accuracy
- Any misalignment will affect angle measurement
- Consider alignment features in design
- May need calibration jig for assembly

### Future Considerations
- Design for potential future features (display, GPS, etc.)
- Consider modular design for variants
- Plan for potential size changes (different core sizes)

## Questions for Electronics Team

Before starting detailed design, please clarify:

1. **PCB Dimensions**: Exact size and shape?
2. **Component Heights**: Maximum component height?
3. **Connector Locations**: Where are connectors on PCB?
4. **Antenna Requirements**: PCB antenna or external?
5. **Battery Specifications**: Exact battery model and dimensions?
6. **Sensor Mounting**: Specific IMU package and mounting requirements?
7. **Thermal Requirements**: Maximum operating temperature?
8. **EMI Considerations**: Any shielding requirements?

## Getting Started

### Immediate Actions
1. Review all reference documents
2. Request component dimensions from electronics team
3. Research similar products (see `docs/research/existing-tools.md`)
4. Create initial concept sketches
5. Schedule kickoff meeting with team

### First Week Deliverables
- Initial concept sketches (2-3 options)
- Material selection analysis
- Preliminary component fit analysis
- Questions list for electronics team

## Appendix: Component Reference Dimensions

### Estimated Component Sizes (To be confirmed)

**Battery (Li-ion 1200mAh)**:
- Typical: ~50mm x 18mm x 6mm (cylindrical)
- Or: ~40mm x 30mm x 5mm (flat)

**Main PCB**:
- Estimated: ~40mm x 15mm (to be confirmed)
- Thickness: ~1.6mm (standard)

**IMU Sensor**:
- BMI160: 3mm x 3mm x 0.95mm (LGA package)
- MPU6050: 4mm x 4mm x 0.9mm (QFN package)

**USB-C Connector**:
- Standard: ~8.8mm x 2.5mm x 3.5mm

**Buttons**:
- Tactile switch: ~6mm x 6mm x 3.5mm

---

**Document Version**: 1.0  
**Last Updated**: [Date]  
**Next Review**: [Date]

