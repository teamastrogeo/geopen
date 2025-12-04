# GeoPen Research Summary

## Executive Summary

This document summarizes research findings for the GeoPen project - a pencil-like device for measuring core alpha and beta angles in geological field work.

## Key Findings

### 1. Market Landscape

**Existing Solutions**:
- **Manual Tools** (Kenometer, Discoverer Goniometer): Low cost, simple, but require manual data entry
- **Digital Tools** (StructMaster, CoreMaster): High accuracy, automated, but expensive and larger form factor

**Market Gap**: No existing "pencil-like" form factor device combining digital measurement with instant data transfer

### 2. Technical Requirements

**Alpha Angle (α)**:
- Definition: Inclination of planar feature relative to core axis
- Range: 0° to 90°
- Accuracy Target: ±2-3 degrees

**Beta Angle (β)**:
- Definition: Circumferential angle from reference line to feature trace
- Range: 0° to 360°
- Accuracy Target: ±2-3 degrees

### 3. Best Practices Identified

1. **Automation**: Digital tools reduce human error significantly
2. **Data Integration**: Instant wireless data transfer is highly valued
3. **Portability**: Lightweight, compact design essential for field use
4. **Durability**: Rugged construction needed for harsh field conditions
5. **Calibration**: Regular calibration critical for accuracy
6. **Image Verification**: Optional photo capture for audit trail

### 4. Technology Recommendations

**Sensors**:
- IMU (Inertial Measurement Unit) with accelerometer and gyroscope
- 6-axis or 9-axis sensor recommended
- Sensor fusion algorithm (Madgwick or Kalman filter) for accuracy

**Connectivity**:
- Bluetooth Low Energy (BLE) 5.0+ for low power consumption
- Range: 10 meters minimum
- Instant data transfer to mobile devices

**Power**:
- Rechargeable Li-ion battery (1000-1500 mAh)
- USB-C charging
- Target: 8+ hours continuous use

**Form Factor**:
- Pencil-like: 15-20 cm length, 1.5-2.5 cm diameter
- Weight: <200g
- IP54 rating for field durability

### 5. Competitive Advantages for GeoPen

1. **Unique Form Factor**: Pencil-like design for intuitive use
2. **Cost-Effective**: Balance between manual tools and high-end solutions
3. **Digital Accuracy**: Automated measurement reduces errors
4. **Instant Data Transfer**: Wireless connectivity to mobile apps
5. **Portability**: Lightweight and compact for field use

## Research Sources

### Commercial Products
1. Kenometer Core Orientation Tool (Deakin Industries)
2. Discoverer Goniometer (Dynamics G-Ex)
3. StructMaster™ (SPT)
4. CoreMaster™ (SPT)

### Academic Studies
1. "Pseudo-Outcrop Visualization of Borehole Images and Core Scans" (arXiv:1702.02633)
2. "Robust Estimation of Structural Orientation Parameters" (arXiv:2409.05754)
3. "Automatic System for Extracting Planar Orientations" (arXiv:2012.11780)
4. "Measurement of Beta Angle - Oriented Core Procedures" (Geokniga)

### Industry Standards
- ISO standards for geological measurements
- ASTM standards for core orientation
- Industry best practices for field measurement

## Key Insights for Product Design

### Hardware Design
- **Sensor Selection**: High-quality IMU with sensor fusion
- **Form Factor**: Compact, pencil-like design
- **Durability**: IP54 rating, rugged materials
- **Power**: Long battery life with USB-C charging

### Software Design
- **Firmware**: Efficient sensor processing and angle calculation
- **Mobile App**: iOS and Android support
- **Data Management**: Local storage with export capabilities
- **User Interface**: Simple, intuitive design

### User Experience
- **Ease of Use**: Minimal training required
- **Speed**: <2 seconds per measurement
- **Feedback**: Visual and haptic feedback
- **Data Integration**: Seamless transfer to applications

## Recommendations

### Phase 1: Research (Current)
✅ **Completed**: Research existing tools, best practices, and technical studies

### Phase 2: Design
- Finalize product specifications
- Develop detailed hardware design
- Create software architecture
- Design user interface mockups

### Phase 3: Prototyping
- Build proof-of-concept prototype
- Test sensor accuracy
- Validate form factor
- Develop basic mobile app

### Phase 4: Development
- Refine hardware design
- Complete firmware development
- Develop full mobile application
- Conduct field testing

### Phase 5: Production
- Finalize manufacturing design
- Set up production
- Quality assurance
- Launch

## Next Steps

1. **Review Research**: Validate findings with geological experts
2. **Design Phase**: Begin detailed product design
3. **Technology Validation**: Test sensor accuracy and algorithms
4. **User Research**: Interview field geologists for requirements
5. **Prototype Development**: Build initial proof-of-concept

## References

See individual research documents:
- `existing-tools.md` - Detailed analysis of commercial products
- `best-practices.md` - Industry best practices
- `technical-studies.md` - Academic research and technical concepts

