# GeoPen 2025

A pencil-like device for measuring core alpha and beta angles to help geologists measure with accuracy and speed. The device delivers measurement data to an application form once angles are measured.

## Project Overview

GeoPen is an innovative tool designed to streamline geological core orientation measurements by providing:
- **Accurate measurement** of alpha (α) and beta (β) angles
- **Speed** in field data collection
- **Digital data delivery** to application forms
- **Portable, pencil-like form factor** for ease of use

## Project Phases

1. **Research Phase** - Study existing tools, best practices, and industry standards
2. **Design Phase** - Product design and technical specifications
3. **Development Phase** - Hardware and software development
4. **Testing Phase** - Field testing and validation

## Project Structure

```
GeoPen_2025/
├── docs/
│   ├── research/              # Research findings
│   ├── design/                # Product design documents
│   ├── requirements/          # Product requirements
│   ├── user-research/         # User research templates
│   ├── testing/               # Test plans and procedures
│   ├── development/           # Development guides
│   └── PROJECT_PLAN.md        # Project timeline
├── hardware/
│   ├── firmware/              # Embedded firmware code
│   ├── schematics/            # Circuit schematics (future)
│   ├── pcb/                   # PCB layouts (future)
│   └── 3d-models/            # 3D CAD models (future)
├── software/
│   └── mobile/
│       ├── ios/               # iOS application
│       └── android/           # Android application
└── README.md
```

## Key Definitions

- **Alpha (α) Angle**: The inclination of a planar feature relative to the core axis (0-90°)
  - Measured as device inclination relative to Z-axis
  - Range: 0° (horizontal) to 90° (vertical)

- **Beta (β) Angle**: The circumferential angle around the core axis (0-360° full circle)
  - Measured as rotation around device Z-axis (core longitudinal axis)
  - Range: 0° to 360° (complete circle)
  - Uses magnetometer for absolute heading reference
  - See `docs/design/MEASUREMENT_MECHANISM.md` for detailed explanation

## 3D Design & Geometry

All design documents include comprehensive 3D coordinate systems, geometric specifications, angles, and lengths for collaborative engineering:

- **Coordinate System**: Right-handed Cartesian (X, Y, Z)
- **Origin**: Device tip center (0, 0, 0)
- **Z-axis**: Longitudinal axis (0mm tip → 180mm top)
- **Units**: Millimeters (mm) for distances, Degrees (°) for angles
- **Component Coordinates**: All components have defined 3D coordinate points
- See `docs/mechanical/MECHANICAL_ENGINEER_HANDOVER.md` for complete 3D specifications

## Getting Started

### Quick Start (30 minutes)
1. Follow `docs/development/QUICK_START.md` to get hardware running
2. Test basic sensor reading
3. Verify mobile app builds

### For Developers
1. Review `docs/development/SETUP.md` for development environment setup
2. Check `hardware/firmware/README.md` for firmware development
3. Check `software/mobile/ios/README.md` or `software/mobile/android/README.md` for app development
4. Follow `docs/development/HARDWARE_SETUP.md` for hardware connections

### For Proof of Concept Phase
1. Review `docs/development/PROOF_OF_CONCEPT_PHASE.md` for phase plan
2. Use `docs/development/POC_CHECKLIST.md` to track progress
3. Follow `docs/development/BLE_TESTING.md` for communication testing

### For Project Management
1. Review `docs/PROJECT_PLAN.md` for project timeline
2. Check `docs/research/` for research findings
3. Review `docs/design/` for product specifications

### For User Research
1. Follow `docs/user-research/EXECUTION_PLAN.md` for research execution
2. Use `docs/user-research/interview-template.md` for interviews
3. Use `docs/user-research/survey-template.md` for surveys

### For Testing
1. Review `docs/testing/test-plan.md` for testing procedures
2. Set up test environments per setup guide

### For Mechanical Engineering
1. Start with `docs/mechanical/MECHANICAL_ENGINEER_HANDOVER.md` for complete handover package
2. Review `docs/mechanical/DOCUMENT_CHECKLIST.md` for all documents
3. Check `docs/mechanical/COMPONENT_DIMENSIONS.md` for component reference with 3D coordinates
4. Review `docs/3D_COORDINATE_SYSTEM.md` for coordinate system quick reference
5. Review design documents in `docs/design/` for specifications

### For All Engineers - 3D Design
1. Review `docs/3D_COORDINATE_SYSTEM.md` for coordinate system reference
2. All components have defined 3D coordinate points
3. Use consistent coordinate system across all disciplines
4. See `docs/mechanical/COMPONENT_DIMENSIONS.md` for detailed component coordinates

## Development Status

- ✅ Research Phase: Complete
- ✅ Design Phase: Complete
- ✅ Development Phase: Foundation Complete
- 🚧 Proof of Concept Phase: Ready to Start
- ⏳ Testing Phase: Pending

## Current Phase: Proof of Concept

**Status**: Ready to begin hardware testing and validation

**Next Actions**:
1. Set up hardware (see `docs/development/HARDWARE_SETUP.md`)
2. Test sensor integration
3. Validate BLE communication
4. Conduct user research

**Resources**:
- `docs/development/PROOF_OF_CONCEPT_PHASE.md` - Phase plan
- `docs/development/POC_CHECKLIST.md` - Execution checklist
- `docs/development/QUICK_START.md` - Quick setup guide