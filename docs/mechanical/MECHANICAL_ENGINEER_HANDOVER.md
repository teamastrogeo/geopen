# GeoPen - Mechanical Engineer Handover Package

## Overview

This document provides all necessary information for the mechanical engineer to begin design and development of the GeoPen enclosure and mechanical components.

**Project**: GeoPen - Core Alpha/Beta Angle Measurement Device  
**Handover Date**: [Date]  
**Target Timeline**: 3-4 months for prototype design

## Executive Summary

GeoPen is a pencil-like device for measuring geological core angles. The mechanical design must accommodate electronics, sensors, battery, and user interface while maintaining a portable, field-ready form factor.

## Critical Requirements

### Form Factor
- **Shape**: Cylindrical, pencil-like
- **Length**: 18 cm (7.1 inches) - **CRITICAL**
- **Diameter**: 2.0 cm (0.79 inches) at grip - **CRITICAL**
- **Weight**: 150-180 grams (target: <200g) - **CRITICAL**
- **Ergonomics**: Comfortable grip for extended field use

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

#### 3. IMU Sensor (Critical)
- **Type**: 6-axis or 9-axis IMU (BMI160, MPU6050, or similar)
- **Size**: ~3mm x 3mm x 1mm (package dependent)
- **Location**: Near tip, aligned with device axis
- **Critical Requirements**:
  - **Fixed orientation** relative to device axis
  - **Vibration-resistant mounting**
  - **Proper alignment** (critical for accuracy)
  - **Minimal flex** in mounting structure

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

#### 8. Optional Display
- **Type**: Small OLED (1.3" or smaller, 128x64 pixels)
- **Location**: Top or side
- **Requirements**:
  - Visible in various lighting
  - Protected from damage
  - IP54 sealing

### Internal Layout Constraints

```
┌─────────────────────────────────────┐
│  [Power Button] [LEDs]              │ ← Top (18cm)
│                                     │
│  ┌─────────────────────────────┐   │
│  │      Battery (1000-1500mAh) │   │
│  │      ~40-50mm length         │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      Main PCB               │   │
│  │      MCU + BLE              │   │
│  │      ~30-40mm length        │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      IMU Sensor             │   │
│  │      Near tip, aligned      │   │
│  └─────────────────────────────┘   │
│                                     │
│  [Trigger Button]                  │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      Contact Sensor         │   │
│  │      At tip                 │   │
│  └─────────────────────────────┘   │
│                                     │
│  [USB-C Port]                      │ ← Bottom
│  [Tip - Contact Point]             │
└─────────────────────────────────────┘
     Diameter: 2.0cm (20mm)
```

## Design Constraints

### Critical Constraints
1. **Diameter**: Maximum 2.0 cm (20mm) - **MUST NOT EXCEED**
2. **Length**: 18 cm (180mm) - **TARGET, ±5mm acceptable**
3. **Weight**: <200g - **MUST NOT EXCEED**
4. **IMU Alignment**: Sensor axis must align with device axis - **CRITICAL**
5. **IP54 Rating**: Must be achievable with design

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

## Design Considerations

### Thermal Management
- **Heat Sources**: MCU, battery charging
- **Requirements**: 
  - No active cooling
  - Passive heat dissipation
  - Temperature monitoring (sensor compensation)

### Antenna Design
- **BLE Antenna**: Must be integrated or external
- **Requirements**:
  - 10-meter range minimum
  - Not blocked by metal enclosure
  - Consider PCB antenna vs. external

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

## Reference Documents

### Must Read
1. **`docs/design/product-specifications.md`** - Complete specifications
2. **`docs/design/hardware-design.md`** - Hardware architecture and layout
3. **`docs/requirements/product-requirements.md`** - Full requirements

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

