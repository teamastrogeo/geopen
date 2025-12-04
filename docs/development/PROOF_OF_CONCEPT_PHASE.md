# GeoPen Proof of Concept Phase - Execution Plan

## Phase Overview

**Duration**: 2-3 months  
**Objective**: Validate core technology and create working prototype  
**Success Criteria**: Working device that can measure angles and communicate with mobile app

**3D Design Reference**: 
- All components have defined 3D coordinates (see `docs/mechanical/COMPONENT_DIMENSIONS.md`)
- IMU sensor alignment critical: Position (0,0,15mm), Tolerance ±0.1°
- Device geometry: 180mm length, 20mm diameter, coordinate system defined

## Phase Goals

1. ✅ Validate sensor accuracy (±2-3°)
2. ✅ Establish BLE communication
3. ✅ Test end-to-end measurement flow
4. ✅ Gather initial user feedback
5. ✅ Identify and resolve critical issues

## Month 1: Hardware Setup & Basic Functionality

### Week 1-2: Hardware Acquisition & Setup

**Tasks**:
- [ ] Order development boards (nRF52840 DK or STM32L4 Nucleo)
- [ ] Order IMU sensors (BMI160, MPU6050, or LSM6DS3)
- [ ] Set up development environment
- [ ] Flash initial firmware to development board
- [ ] Test basic sensor reading

**Deliverables**:
- Working development board setup
- Basic sensor data reading
- Serial communication working

**Resources Needed**:
- nRF52840 Development Kit (~$50) or STM32L4 Nucleo (~$30)
- IMU sensor breakout board (~$10-20)
- USB cables, breadboard, jumper wires
- Multimeter, oscilloscope (optional)

### Week 3-4: Firmware Integration

**Tasks**:
- [ ] Integrate IMU driver with actual sensor
- [ ] Test sensor fusion algorithm
- [ ] Validate angle calculation accuracy
- [ ] Implement BLE advertising
- [ ] Test BLE connection from mobile app

**Deliverables**:
- Sensor reading working
- Angle calculation functional
- BLE connection established

**Testing**:
- Sensor accuracy test (compare with reference angles)
- BLE range test (measure connection distance)
- Measurement repeatability test

## Month 2: Mobile App Integration & Testing

### Week 5-6: BLE Communication

**Tasks**:
- [ ] Complete BLE service implementation
- [ ] Test device discovery
- [ ] Test measurement trigger
- [ ] Test data transmission
- [ ] Debug communication issues

**Deliverables**:
- End-to-end BLE communication working
- Measurement data flowing from device to app
- Real-time display functional

**Testing**:
- Follow `docs/development/BLE_TESTING.md` procedures
- Test connection stability
- Test data accuracy

### Week 7-8: App Refinement & Data Management

**Tasks**:
- [ ] Test measurement saving
- [ ] Test data export (CSV/JSON)
- [ ] Refine UI based on testing
- [ ] Fix bugs and issues
- [ ] Optimize performance

**Deliverables**:
- Complete mobile app functionality
- Data persistence working
- Export functionality tested

## Month 3: Validation & User Testing

### Week 9-10: Accuracy Validation

**Tasks**:
- [ ] Create test rig with known angles
- [ ] Measure accuracy across angle ranges
- [ ] Test repeatability
- [ ] Document results
- [ ] Optimize calibration if needed

**Deliverables**:
- Accuracy test report
- Calibration procedure validated
- Performance metrics documented

**Test Setup**:
- Use protractor or calibrated angle reference
- Test alpha angles: 0°, 15°, 30°, 45°, 60°, 75°, 90°
- Test beta angles: 0°, 90°, 180°, 270°, 360°
- Take 10 measurements per angle
- Calculate mean error and standard deviation

### Week 11-12: User Research & Field Testing

**Tasks**:
- [ ] Recruit 3-5 beta testers (field geologists)
- [ ] Conduct user interviews (use `docs/user-research/interview-template.md`)
- [ ] Distribute survey (use `docs/user-research/survey-template.md`)
- [ ] Field test with actual core samples
- [ ] Gather feedback and iterate

**Deliverables**:
- User feedback report
- Field test results
- List of improvements needed
- Updated requirements based on feedback

## Critical Path Items

### Must-Have for PoC Success:
1. **Sensor Accuracy**: Must achieve ±3° accuracy
2. **BLE Communication**: Must work reliably
3. **Measurement Flow**: End-to-end must work
4. **User Feedback**: Must gather initial feedback

### Nice-to-Have (Can defer):
- Advanced calibration features
- Cloud sync
- GPS integration
- Image capture

## Risk Mitigation

### Risk: Sensor accuracy not meeting target
**Mitigation**: 
- Test multiple sensor options
- Refine calibration procedure
- Consider sensor fusion improvements

### Risk: BLE communication issues
**Mitigation**:
- Test early and often
- Use proven BLE stacks
- Have fallback communication method

### Risk: User feedback negative
**Mitigation**:
- Involve users early
- Iterate based on feedback
- Keep requirements flexible

## Success Metrics

### Technical Metrics:
- [ ] Measurement accuracy: ±3° or better
- [ ] BLE connection success rate: >95%
- [ ] Measurement time: <2 seconds
- [ ] Battery life: >4 hours continuous use

### User Metrics:
- [ ] 80% of testers can use without training
- [ ] User satisfaction: >3.5/5.0
- [ ] 70% would use in their work

## Next Steps After PoC

1. **Alpha Prototype**: Refined design based on PoC learnings
2. **Custom PCB**: Design and manufacture custom board
3. **Enclosure Design**: 3D design and prototyping
4. **Production Planning**: Manufacturing partner selection

## Resources & Support

### Documentation:
- `docs/development/BLE_TESTING.md` - BLE testing procedures
- `docs/development/SETUP.md` - Development setup
- `docs/testing/test-plan.md` - Comprehensive test plan
- `docs/user-research/` - User research templates

### Code:
- Firmware: `hardware/firmware/`
- iOS App: `software/mobile/ios/`
- Android App: `software/mobile/android/`

### Getting Help:
- Review documentation
- Check code comments
- Test incrementally
- Document issues and solutions

## Weekly Check-ins

**Format**: 
- What was accomplished?
- What issues were encountered?
- What's planned for next week?
- Any blockers?

**Frequency**: Weekly team sync (or individual review)

## Notes

- Start simple, iterate quickly
- Test early and often
- Document everything
- Keep user feedback central
- Don't optimize prematurely

