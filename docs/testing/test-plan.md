# GeoPen Test Plan

## Overview

This document outlines the testing strategy for GeoPen hardware and software components.

## Test Categories

### 1. Unit Tests
**Scope**: Individual functions and algorithms  
**Location**: `hardware/firmware/tests/`, `software/mobile/*/tests/`

#### Firmware Unit Tests
- [ ] Sensor fusion algorithm accuracy
- [ ] Angle calculation correctness
- [ ] Angle validation logic
- [ ] Calibration routines
- [ ] Data packet encoding/decoding

#### Mobile App Unit Tests
- [ ] Measurement model validation
- [ ] BLE data parsing
- [ ] Data export formats (CSV, JSON)
- [ ] Storage operations

### 2. Integration Tests
**Scope**: Component interactions

- [ ] IMU sensor → Firmware → BLE communication
- [ ] BLE → Mobile app data flow
- [ ] Mobile app → Storage → Export
- [ ] Calibration → Measurement accuracy

### 3. Hardware Tests
**Scope**: Physical device testing

#### Sensor Accuracy Tests
- [ ] Alpha angle accuracy (±2-3°)
- [ ] Beta angle accuracy (±2-3°)
- [ ] Repeatability (±1°)
- [ ] Temperature stability
- [ ] Long-term drift
- [ ] IMU sensor alignment verification (position: 0,0,15mm, tolerance: ±0.1°)
- [ ] Coordinate system alignment check (device vs. sensor axes)

#### Environmental Tests
- [ ] IP54 rating (dust and splash)
- [ ] Temperature range (-10°C to 50°C)
- [ ] Shock resistance (1m drop)
- [ ] Vibration resistance
- [ ] Geometric stability (dimensions: 180mm length, 20mm diameter)
- [ ] Component position stability after impact (verify 3D coordinates maintained)

#### Power Tests
- [ ] Battery life (8+ hours continuous)
- [ ] Standby time (30+ days)
- [ ] Charging time (<3 hours)
- [ ] Low battery behavior

#### Connectivity Tests
- [ ] BLE range (10 meters)
- [ ] Connection stability
- [ ] Data transfer reliability
- [ ] Multiple device support

### 4. Software Tests
**Scope**: Mobile application testing

#### Functional Tests
- [ ] Device discovery
- [ ] Pairing and connection
- [ ] Real-time measurement display
- [ ] Measurement recording
- [ ] History view
- [ ] Data export (CSV, JSON, PDF)
- [ ] Settings and configuration
- [ ] Calibration assistant

#### Usability Tests
- [ ] User interface navigation
- [ ] Error handling
- [ ] Offline operation
- [ ] Multi-language support

#### Performance Tests
- [ ] App startup time
- [ ] Measurement display latency
- [ ] Data export speed
- [ ] Memory usage

#### Compatibility Tests
- [ ] iOS versions (13.0+)
- [ ] Android versions (8.0+)
- [ ] Device models (various)
- [ ] Tablet support

### 5. Field Tests
**Scope**: Real-world usage

- [ ] Field measurement accuracy
- [ ] User workflow validation
- [ ] Durability in field conditions
- [ ] Battery life in actual use
- [ ] Data quality and consistency

## Test Procedures

### Sensor Accuracy Test

**Objective**: Verify measurement accuracy meets ±2-3° requirement

**Setup**:
1. Mount device in known orientation
2. Use calibrated reference angles
3. Take 100 measurements at various angles

**Procedure**:
1. Set reference angle (e.g., 30° alpha, 120° beta)
2. Take 10 measurements
3. Calculate mean and standard deviation
4. Repeat for multiple reference angles

**Pass Criteria**:
- Mean error < ±2°
- Standard deviation < 1°
- 95% of measurements within ±3°

### Battery Life Test

**Objective**: Verify 8+ hours continuous operation

**Setup**:
1. Fully charge device
2. Set to continuous measurement mode
3. Measure every 2 seconds

**Procedure**:
1. Start measurement cycle
2. Monitor battery level
3. Record time until battery depletion

**Pass Criteria**:
- Operating time ≥ 8 hours

### BLE Range Test

**Objective**: Verify 10-meter range

**Setup**:
1. Connect device to mobile app
2. Measure distance with measuring tape

**Procedure**:
1. Start at 1 meter distance
2. Move device away in 1-meter increments
3. Test connection stability at each distance
4. Record maximum reliable range

**Pass Criteria**:
- Reliable connection ≥ 10 meters

## Test Schedule

### Phase 1: Unit Tests (Weeks 1-2)
- Implement unit test framework
- Write tests for core algorithms
- Achieve 80%+ code coverage

### Phase 2: Integration Tests (Weeks 3-4)
- Test component interactions
- Verify data flow
- Fix integration issues

### Phase 3: Hardware Tests (Weeks 5-8)
- Sensor accuracy validation
- Environmental testing
- Power testing
- Connectivity testing

### Phase 4: Software Tests (Weeks 9-12)
- Mobile app functional testing
- Usability testing
- Performance testing
- Compatibility testing

### Phase 5: Field Tests (Weeks 13-16)
- Beta user testing
- Field accuracy validation
- Real-world usage feedback

## Test Tools and Equipment

### Hardware Testing
- Calibrated angle reference
- Environmental chamber
- Oscilloscope
- Power analyzer
- BLE testing equipment

### Software Testing
- Unit test frameworks (CUnit, XCTest, JUnit)
- UI testing tools (XCUITest, Espresso)
- Performance profiling tools
- Device farms for compatibility testing

## Test Reporting

### Test Results Template
- Test ID and name
- Test objective
- Test procedure
- Results (pass/fail)
- Issues found
- Recommendations

### Metrics
- Test coverage percentage
- Pass/fail rate
- Defect density
- Test execution time

## Risk Assessment

### High-Risk Areas
1. Sensor accuracy
2. Battery life
3. BLE connectivity
4. Field durability

### Mitigation
- Early prototype testing
- Multiple test iterations
- Beta user feedback
- Continuous improvement

## Sign-off Criteria

Before production release:
- [ ] All unit tests passing
- [ ] Integration tests passing
- [ ] Hardware tests meeting specifications
- [ ] Software tests passing
- [ ] Field tests successful
- [ ] User acceptance testing complete
- [ ] Documentation complete

