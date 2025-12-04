# GeoPen Product Requirements Document (PRD)

## 1. Product Overview

### 1.1 Purpose
GeoPen is a portable, pencil-like device that measures core alpha and beta angles for geologists, providing accurate measurements with instant digital data transfer to mobile applications.

### 1.2 Target Users
- Field geologists
- Core logging technicians
- Geological survey teams
- Mining and exploration companies

### 1.3 Key Value Propositions
- **Accuracy**: Automated measurement reduces human error
- **Speed**: Faster than manual measurement tools
- **Portability**: Pencil-like form factor for easy field use
- **Digital Integration**: Instant data transfer to applications
- **Cost-Effective**: Balance between manual tools and high-end digital solutions

## 2. Functional Requirements

### 2.1 Core Measurement Functions

**FR-1: Alpha Angle Measurement**
- Device must measure alpha (α) angle from 0° to 90°
- Accuracy: ±2-3 degrees
- Measurement range: 0° to 90°
- Display: Real-time angle display (optional on-device display)

**FR-2: Beta Angle Measurement**
- Device must measure beta (β) angle from 0° to 360°
- Accuracy: ±2-3 degrees
- Measurement range: 0° to 360°
- Display: Real-time angle display (optional on-device display)

**FR-3: Simultaneous Measurement**
- Device must be capable of measuring both angles simultaneously or sequentially
- Measurement mode selection (alpha-only, beta-only, or both)

**FR-4: Measurement Trigger**
- User-initiated measurement trigger (button press or gesture)
- Measurement hold/lock function
- Clear indication of measurement status

### 2.2 Data Transfer Functions

**FR-5: Wireless Connectivity**
- Bluetooth Low Energy (BLE) connectivity
- Pairing with mobile devices (iOS/Android)
- Connection status indication
- Automatic reconnection capability

**FR-6: Data Transmission**
- Transmit measured angles to connected application
- Include metadata: timestamp, measurement ID, device ID
- Support multiple measurements per session
- Data format: JSON or structured format

**FR-7: Data Storage**
- Local storage of measurements (on-device memory)
- Storage capacity: Minimum 100 measurements
- Data export capability

### 2.3 User Interface Functions

**FR-8: Device Controls**
- Power on/off button
- Measurement trigger button
- Mode selection (if applicable)
- LED indicators for status

**FR-9: Feedback**
- Visual feedback (LEDs) for measurement status
- Haptic feedback (vibration) for measurement confirmation
- Audio feedback (optional beep)

### 2.4 Calibration and Setup

**FR-10: Calibration**
- Built-in calibration routine
- User-initiated calibration
- Calibration verification
- Calibration data storage

**FR-11: Configuration**
- Device settings configuration via mobile app
- Measurement units (degrees)
- Default measurement mode
- Device name/ID configuration

## 3. Non-Functional Requirements

### 3.1 Physical Requirements

**NFR-1: Form Factor**
- Pencil-like shape and size
- Length: 15-20 cm (similar to standard pencil)
- Diameter: 1.5-2.5 cm (comfortable grip)
- Weight: <200g (lightweight for field use)

**NFR-2: Durability**
- IP54 or better (dust and water resistance)
- Operating temperature: -10°C to 50°C
- Shock resistance: Survive 1m drop
- Rugged construction for field use

**NFR-3: Materials**
- Durable outer casing
- Non-slip grip surface
- Weather-resistant materials

### 3.2 Performance Requirements

**NFR-4: Measurement Speed**
- Measurement time: <2 seconds per angle
- Response time: <500ms from trigger to measurement

**NFR-5: Battery Life**
- Operating time: Minimum 8 hours continuous use
- Standby time: Minimum 30 days
- Rechargeable battery (USB-C charging)
- Battery level indication

**NFR-6: Connectivity**
- BLE range: Minimum 10 meters
- Connection time: <5 seconds
- Data transfer rate: Sufficient for real-time transmission

### 3.3 Accuracy Requirements

**NFR-7: Measurement Accuracy**
- Alpha angle: ±2-3 degrees
- Beta angle: ±2-3 degrees
- Repeatability: ±1 degree for same measurement
- Calibration stability: Maintain accuracy over 6 months

### 3.4 Usability Requirements

**NFR-8: Ease of Use**
- Intuitive operation (minimal training required)
- Simple button interface
- Clear status indicators
- Quick setup (<5 minutes)

**NFR-9: Documentation**
- User manual (digital and printed)
- Quick start guide
- Video tutorials
- Technical specifications

## 4. Software Requirements

### 4.1 Mobile Application

**SR-1: Platform Support**
- iOS (iOS 13+)
- Android (Android 8+)
- Tablet support (iPad, Android tablets)

**SR-2: Core Features**
- Device pairing and connection
- Real-time angle display
- Measurement history
- Data export (CSV, JSON, PDF)
- Measurement validation and editing

**SR-3: Data Management**
- Local database for measurements
- Cloud sync (optional)
- Data backup and restore
- Measurement search and filtering

**SR-4: User Interface**
- Clean, intuitive design
- Offline operation capability
- Multi-language support (English, Spanish, French)
- Accessibility features

### 4.2 Firmware

**SR-5: Embedded Software**
- Sensor reading and processing
- Angle calculation algorithms
- BLE communication stack
- Power management
- Calibration routines

**SR-6: Updates**
- Firmware update capability via mobile app
- Over-the-air (OTA) updates
- Update rollback capability

## 5. Integration Requirements

### 5.1 Data Formats

**IR-1: Standard Formats**
- CSV export
- JSON export
- PDF reports
- Integration with geological databases

**IR-2: Metadata**
- Timestamp
- Location (GPS, if available)
- Operator ID
- Core sample ID
- Project ID
- Measurement quality score

### 5.2 Third-Party Integration

**IR-3: Cloud Services**
- Optional cloud sync (AWS, Azure, or custom)
- API for data access
- Web dashboard (optional)

**IR-4: Database Integration**
- Export to common geological databases
- API for custom integrations

## 6. Compliance and Standards

### 6.1 Regulatory

**CR-1: Certifications**
- CE marking (European compliance)
- FCC certification (US)
- Bluetooth SIG certification
- RoHS compliance

### 6.2 Industry Standards

**CR-2: Standards Compliance**
- ISO standards for geological measurements (where applicable)
- Industry best practices for core orientation
- Data format standards

## 7. Success Criteria

### 7.1 User Acceptance
- 90% of users can perform measurements without training
- User satisfaction score >4.0/5.0
- Adoption rate: 50% of target users within first year

### 7.2 Performance Metrics
- Measurement accuracy meets specifications (±2-3°)
- Battery life meets requirements (8+ hours)
- Device reliability: <2% failure rate in first year

### 7.3 Business Metrics
- Cost target: <$500 per unit (manufacturing cost)
- Time to market: 12-18 months
- Market penetration: Target market share

## 8. Out of Scope (v1.0)

- Image capture and processing
- GPS integration
- Cloud sync (may be v2.0)
- Multiple core size adapters (may be v2.0)
- Advanced analytics and visualization

## 9. Future Enhancements (v2.0+)

- Image capture for verification
- GPS location tagging
- Cloud sync and collaboration
- Multiple core size support
- Advanced data analytics
- Machine learning for quality improvement
- Integration with geological modeling software

