# GeoPen Product Specifications

## 1. Physical Specifications

### 1.1 Dimensions & 3D Geometry
- **Length**: 180 mm (18 cm, 7.1 inches)
  - Tip to Top: 180 mm ±2 mm
  - Z-axis range: 0 mm (tip) to 180 mm (top)
- **Diameter**: 20 mm (2.0 cm, 0.79 inches) at grip
  - Outer diameter: 20 mm ±0.5 mm
  - Inner diameter: 18 mm (wall thickness: 1 mm)
  - Circularity tolerance: ±0.1 mm
- **Weight**: 150-180 grams (target: <200g)
- **Form Factor**: Cylindrical, pencil-like shape
- **Coordinate System**: 
  - Origin (0,0,0): Tip center
  - Z-axis: Longitudinal axis (positive upward)
  - X-axis: Horizontal (positive right)
  - Y-axis: Horizontal (positive front)
- **Cylindrical Axis Alignment**: Z-axis, deviation <0.1°

### 1.2 Materials
- **Body**: Anodized aluminum or reinforced plastic
- **Grip**: Textured rubber or silicone
- **Tip**: Durable contact point (stainless steel or ceramic)
- **Display**: Optional small OLED display (1.3" or smaller)

### 1.3 Environmental Specifications
- **IP Rating**: IP54 (dust and splash resistant)
- **Operating Temperature**: -10°C to 50°C
- **Storage Temperature**: -20°C to 60°C
- **Humidity**: 0-95% RH (non-condensing)
- **Shock Resistance**: 1m drop onto concrete

## 2. Sensor Specifications

### 2.1 Inertial Measurement Unit (IMU)
- **Type**: 6-axis or 9-axis IMU
- **Accelerometer**: ±16g range, 16-bit resolution
- **Gyroscope**: ±2000°/s range, 16-bit resolution
- **Magnetometer**: Optional (for compass direction)
- **Sampling Rate**: 100 Hz minimum
- **Accuracy**: ±0.1° for orientation (after calibration)

### 2.2 Contact Sensor
- **Type**: Pressure sensor or contact switch
- **Purpose**: Detect contact with core surface
- **Sensitivity**: Adjustable threshold

### 2.3 Optional Sensors
- **Temperature Sensor**: For sensor compensation
- **Ambient Light Sensor**: For display brightness

## 3. Electronics Specifications

### 3.1 Microcontroller
- **Type**: ARM Cortex-M4 or similar
- **Clock Speed**: 100+ MHz
- **Memory**: 
  - Flash: 512 KB minimum
  - RAM: 128 KB minimum
- **Features**: 
  - Low power operation
  - Floating point unit (FPU)
  - Multiple ADC channels

### 3.2 Connectivity
- **Bluetooth**: BLE 5.0 or higher
- **Range**: 10 meters minimum
- **Data Rate**: Sufficient for real-time transmission
- **Pairing**: Standard BLE pairing

### 3.3 Power
- **Battery**: Rechargeable Li-ion or Li-poly
- **Capacity**: 1000-1500 mAh
- **Operating Time**: 8+ hours continuous use
- **Standby Time**: 30+ days
- **Charging**: USB-C connector
- **Charging Time**: <3 hours
- **Battery Indicator**: LED or display

### 3.4 User Interface
- **Buttons**: 
  - Power button (with LED indicator)
  - Measurement trigger button
  - Mode selection button (optional)
- **LEDs**: 
  - Power status (green/red)
  - Measurement status (blue)
  - Battery low (red)
  - Connection status (yellow)
- **Display**: Optional small OLED (128x64 pixels)
- **Haptic Feedback**: Vibration motor (optional)

## 4. Measurement Specifications

### 4.1 Alpha Angle
- **Range**: 0° to 90°
- **Resolution**: 0.1°
- **Accuracy**: ±2-3 degrees
- **Repeatability**: ±1 degree
- **Measurement Time**: <2 seconds

### 4.2 Beta Angle
- **Range**: 0° to 360°
- **Resolution**: 0.1°
- **Accuracy**: ±2-3 degrees
- **Repeatability**: ±1 degree
- **Measurement Time**: <2 seconds

### 4.3 Measurement Modes
- **Single Mode**: Measure alpha or beta individually
- **Dual Mode**: Measure both angles simultaneously
- **Continuous Mode**: Continuous measurement (for alignment)

## 5. Software Specifications

### 5.1 Firmware
- **Language**: C/C++
- **RTOS**: FreeRTOS or similar (optional)
- **Libraries**: 
  - Sensor fusion library (Madgwick, Mahony, or Kalman filter)
  - BLE stack
  - Power management
- **Update Method**: OTA via mobile app

### 5.2 Mobile Application

#### 5.2.1 Platform Requirements
- **iOS**: iOS 13.0 or later
- **Android**: Android 8.0 (API level 26) or later
- **Tablets**: iPad and Android tablets supported

#### 5.2.2 Core Features
- Device discovery and pairing
- Real-time angle display
- Measurement recording
- Measurement history
- Data export (CSV, JSON, PDF)
- Settings and configuration
- Calibration assistant

#### 5.2.3 User Interface
- **Design**: Material Design (Android) / Human Interface Guidelines (iOS)
- **Languages**: English, Spanish, French (initial)
- **Accessibility**: Screen reader support, high contrast mode

## 6. Data Specifications

### 6.1 Data Format
```json
{
  "measurement_id": "uuid",
  "timestamp": "ISO 8601 format",
  "device_id": "string",
  "operator_id": "string",
  "core_sample_id": "string",
  "project_id": "string",
  "alpha_angle": 45.5,
  "beta_angle": 120.3,
  "quality_score": 0.95,
  "calibration_id": "uuid",
  "location": {
    "latitude": 0.0,
    "longitude": 0.0,
    "altitude": 0.0
  },
  "metadata": {
    "temperature": 25.0,
    "battery_level": 85
  }
}
```

### 6.2 Storage
- **On-Device**: Minimum 100 measurements
- **Mobile App**: Unlimited (device storage dependent)
- **Cloud**: Optional, unlimited

## 7. Calibration Specifications

### 7.1 Calibration Types
- **Factory Calibration**: Performed during manufacturing
- **User Calibration**: Periodic recalibration by user
- **Auto-Calibration**: Automatic compensation for drift

### 7.2 Calibration Procedure
1. Place device in known orientation
2. Initiate calibration mode
3. Follow on-screen/app instructions
4. Verify calibration accuracy
5. Store calibration data

### 7.3 Calibration Stability
- **Duration**: 6 months minimum
- **Drift**: <1 degree per month
- **Verification**: Built-in calibration check

## 8. Performance Specifications

### 8.1 Measurement Performance
- **Measurement Time**: <2 seconds per angle
- **Response Time**: <500ms from trigger
- **Processing Time**: <100ms for angle calculation
- **Data Transfer Time**: <200ms per measurement

### 8.2 Power Performance
- **Active Power**: <200mW during measurement
- **Idle Power**: <10mW
- **Sleep Power**: <100µW
- **Charging Power**: 5V, 1A (USB-C)

### 8.3 Connectivity Performance
- **Pairing Time**: <5 seconds
- **Connection Time**: <2 seconds
- **Data Latency**: <100ms
- **Range**: 10 meters (line of sight)

## 9. Quality and Reliability

### 9.1 Quality Standards
- **Manufacturing**: ISO 9001 compliant
- **Testing**: Comprehensive test suite
- **Quality Control**: 100% functional testing

### 9.2 Reliability
- **MTBF**: >10,000 hours
- **Warranty**: 1 year
- **Failure Rate**: <2% in first year

## 10. Packaging and Accessories

### 10.1 Package Contents
- GeoPen device
- USB-C charging cable
- Quick start guide
- User manual (digital)
- Carrying case
- Calibration reference card

### 10.2 Optional Accessories
- Spare charging cable
- Protective case
- Mounting bracket (for fixed measurements)
- Extended warranty

## 11. Compliance

### 11.1 Regulatory
- **CE Marking**: European compliance
- **FCC Certification**: US compliance
- **Bluetooth SIG**: Certified BLE device
- **RoHS**: Restriction of Hazardous Substances

### 11.2 Standards
- **ISO**: Relevant ISO standards for measurement devices
- **ASTM**: Geological measurement standards (where applicable)

