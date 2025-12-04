# GeoPen Mechanical Engineering Documentation

## Overview

This directory contains all documentation related to mechanical design and engineering for the GeoPen project.

## Key Documents

### Start Here
1. **`MECHANICAL_ENGINEER_HANDOVER.md`** - Complete handover package
   - All requirements consolidated
   - Design constraints
   - Component requirements
   - Deliverables expected

2. **`DOCUMENT_CHECKLIST.md`** - Document checklist
   - List of all documents to review
   - Status tracking
   - Communication plan

3. **`COMPONENT_DIMENSIONS.md`** - Component reference
   - Estimated component sizes
   - Space allocation
   - Critical constraints

## Reference Documents (In Other Directories)

### Design Documents
- `../design/product-specifications.md` - Complete specifications
- `../design/hardware-design.md` - Hardware architecture
- `../requirements/product-requirements.md` - Full requirements

### Research Documents
- `../research/existing-tools.md` - Competitive products
- `../research/best-practices.md` - Field use considerations

### Testing Documents
- `../testing/test-plan.md` - Testing requirements

## Quick Reference

### Critical Requirements (3D Geometry)
- **Length**: 180 mm (18 cm) - Z-axis: 0mm (tip) to 180mm (top)
- **Diameter**: 20 mm (2.0 cm) outer, 18 mm inner - **MUST NOT EXCEED**
- **Weight**: <200g (target: 150-180g)
- **IP Rating**: IP54 minimum
- **Materials**: Anodized aluminum or reinforced plastic
- **Coordinate System**: Origin at tip (0,0,0), Z-axis upward
- **IMU Alignment**: Critical ±0.1° tolerance at (0, 0, 15) mm

### Key Components (with 3D Coordinates)
- **Battery**: 1000-1500 mAh Li-ion/Li-poly
  - Center: (0, 0, 140) mm, Z-range: 115-165mm
- **Main PCB**: ~35-45mm x 12-18mm
  - Center: (0, 0, 90) mm, Z-range: 70-110mm
- **IMU Sensor**: BMI160 or MPU6050
  - Center: (0, 0, 15) mm - **CRITICAL alignment**
  - Alignment tolerance: ±0.1°
- **USB-C connector**: Bottom at (0, 0, 3) mm
- **Power Button**: (0, 10, 175) mm
- **Trigger Button**: (10, 0, 50) mm
- **LEDs**: (0, 10, 170-176) mm - 4 status LEDs

### Timeline
- Month 1: Concept design
- Month 2: Detailed design
- Month 3: Prototype
- Month 4: Production design

## Getting Started

1. Read `MECHANICAL_ENGINEER_HANDOVER.md` completely
2. Review reference documents listed in checklist
3. Request component dimensions from electronics team
4. Create initial concept sketches
5. Schedule kickoff meeting

## Contact Information

- **Project Manager**: [Contact]
- **Electronics Team**: [Contact]
- **Questions**: [Contact]

## Document Status

- ✅ Handover document: Complete
- ✅ Checklist: Complete
- ⏳ Component dimensions: Awaiting electronics specs
- ⏳ Design files: To be created

---

**Last Updated**: [Date]

