# GeoPen Hardware Development

## Overview

This directory contains hardware design files, schematics, PCB layouts, and firmware development.

## Structure

```
hardware/
├── firmware/          # Embedded firmware code
├── schematics/        # Circuit schematics
├── pcb/              # PCB layout files
├── 3d-models/        # 3D CAD models
├── datasheets/       # Component datasheets
└── testing/          # Hardware testing scripts
```

## Development Setup

### Required Tools
- STM32CubeIDE or nRF Connect SDK
- KiCad or Altium Designer (for PCB design)
- 3D CAD software (Fusion 360, SolidWorks)
- Oscilloscope, multimeter, logic analyzer

### Getting Started

1. Review `docs/design/hardware-design.md` for specifications (includes 3D coordinates)
2. Review `docs/mechanical/COMPONENT_DIMENSIONS.md` for component 3D coordinates
3. Set up development environment
4. Review component datasheets in `datasheets/`
5. Start with firmware proof-of-concept

### 3D Design Reference

All components have defined 3D coordinate points:
- **Coordinate System**: Origin at tip (0,0,0), Z-axis 0-180mm
- **IMU Sensor**: (0, 0, 15) mm - Critical alignment ±0.1°
- **PCB**: (0, 0, 90) mm, Z-range: 70-110mm
- **Battery**: (0, 0, 140) mm, Z-range: 115-165mm
- See `docs/mechanical/MECHANICAL_ENGINEER_HANDOVER.md` for complete 3D specifications

