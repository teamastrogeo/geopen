# GeoPen Hardware Design

## 1. System Architecture

### 1.1 Block Diagram
```
┌─────────────────────────────────────────┐
│           GeoPen Device                 │
│                                         │
│  ┌──────────┐  ┌──────────┐           │
│  │   IMU    │  │ Contact  │           │
│  │ Sensor   │  │  Sensor  │           │
│  └────┬─────┘  └────┬─────┘           │
│       │             │                  │
│       └──────┬──────┘                  │
│              │                          │
│       ┌──────▼──────┐                   │
│       │             │                   │
│       │Microcontroller│                 │
│       │  (MCU)      │                   │
│       │             │                   │
│       └──────┬──────┘                   │
│              │                          │
│    ┌─────────┼─────────┐               │
│    │         │         │               │
│ ┌──▼──┐  ┌──▼──┐  ┌──▼──┐            │
│ │ BLE │  │Power│  │ UI  │            │
│ │Module│  │Mgmt│  │(LEDs)│            │
│ └─────┘  └─────┘  └─────┘            │
│                                         │
└─────────────────────────────────────────┘
         │
         │ BLE
         │
    ┌────▼────┐
    │  Mobile │
    │   App   │
    └─────────┘
```

### 1.2 Component Selection

#### Microcontroller Unit (MCU)
**Recommended**: Nordic nRF52840 or STM32L4 series
- **Reason**: Low power, BLE 5.0 support, sufficient processing
- **Alternatives**: ESP32 (if cost is critical), nRF5340 (if more processing needed)

#### IMU Sensor
**Recommended**: Bosch BMI160 or InvenSense MPU6050/6500
- **Reason**: Good accuracy, low power, proven reliability
- **Alternatives**: ST LSM6DS3, TDK InvenSense ICM-20948

#### Bluetooth Module
**Recommended**: Integrated in MCU (nRF52840) or separate BLE module
- **Reason**: Lower cost, better integration
- **Alternatives**: External BLE module if MCU doesn't include it

#### Battery
**Recommended**: Li-ion 3.7V, 1200 mAh
- **Reason**: Good capacity/size ratio, standard voltage
- **Alternatives**: Li-poly for thinner form factor

#### Power Management
**Recommended**: Integrated PMIC or dedicated charge controller
- **Reason**: Efficient charging and power management
- **Example**: TI BQ24040 or similar

## 2. Mechanical Design

### 2.1 Form Factor
- **Shape**: Cylindrical, pencil-like
- **Grip Section**: Textured surface for secure handling
- **Tip Section**: Contact point for core surface
- **Body Section**: Main electronics housing

### 2.2 Component Layout
```
┌─────────────────────────────────────┐
│  [Power Button] [LEDs]              │ ← Top
│                                     │
│  ┌─────────────────────────────┐   │
│  │      Battery                │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      MCU + BLE              │   │
│  └─────────────────────────────┘   │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      IMU Sensor             │   │
│  └─────────────────────────────┘   │
│                                     │
│  [Trigger Button]                  │
│                                     │
│  ┌─────────────────────────────┐   │
│  │      Contact Sensor         │   │
│  └─────────────────────────────┘   │
│                                     │
│  [USB-C Port]                      │ ← Bottom
│  [Tip - Contact Point]             │
└─────────────────────────────────────┘
```

### 2.3 Enclosure Design
- **Material**: Anodized aluminum (preferred) or reinforced plastic
- **Sealing**: O-rings for IP54 rating
- **Venting**: None (sealed design)
- **Assembly**: Screw-based or snap-fit

### 2.4 Button and Interface Placement
- **Power Button**: Top or side, with LED indicator
- **Trigger Button**: Side, easily accessible with thumb
- **USB-C Port**: Bottom, protected by cover
- **LEDs**: Top or side, visible during use

## 3. Sensor Integration

### 3.1 IMU Mounting
- **Orientation**: Fixed relative to device axis
- **Mounting**: Secure, vibration-resistant
- **Alignment**: Critical for accurate measurement
- **Calibration**: Factory calibration of sensor orientation

### 3.2 Contact Sensor
- **Type**: Pressure sensor or microswitch
- **Location**: Tip of device
- **Sensitivity**: Adjustable threshold
- **Purpose**: Detect contact with core surface

### 3.3 Sensor Fusion Algorithm
- **Algorithm**: Madgwick filter or Kalman filter
- **Purpose**: Combine accelerometer and gyroscope data
- **Output**: Quaternion or Euler angles
- **Processing**: On-device calculation

## 4. Power Management

### 4.1 Power States
1. **Active**: Full operation, ~200mW
2. **Idle**: Sensors on, low power, ~10mW
3. **Sleep**: Minimal power, ~100µW
4. **Charging**: USB-C power input

### 4.2 Battery Management
- **Charging**: USB-C, 5V/1A
- **Protection**: Overcharge, over-discharge, short circuit
- **Monitoring**: Battery voltage and capacity
- **Indication**: LED or display

### 4.3 Power Optimization
- **Sleep Mode**: Automatic sleep after inactivity
- **Sensor Sampling**: Adaptive rate (higher during measurement)
- **BLE**: Low power advertising when idle
- **Display**: Optional, can be disabled to save power

## 5. Connectivity

### 5.1 Bluetooth Low Energy (BLE)
- **Standard**: BLE 5.0 or higher
- **Range**: 10 meters minimum
- **Power**: Low power advertising and connection
- **Services**: 
  - Device information
  - Measurement data
  - Configuration
  - Firmware update

### 5.2 BLE GATT Services
```
Service: Device Information (0x180A)
  - Manufacturer Name
  - Model Number
  - Firmware Version
  - Battery Level

Service: Measurement Service (Custom UUID)
  - Alpha Angle (Read/Notify)
  - Beta Angle (Read/Notify)
  - Measurement Trigger (Write)
  - Measurement Status (Notify)

Service: Configuration Service (Custom UUID)
  - Calibration Data (Read/Write)
  - Device Settings (Read/Write)
  - Measurement Mode (Read/Write)
```

## 6. PCB Design

### 6.1 PCB Layout Considerations
- **Size**: Fit within 2cm diameter cylinder
- **Layers**: 4-layer PCB (power, ground, signals)
- **Components**: Surface mount (SMD) components
- **Routing**: Careful routing for sensor signals

### 6.2 Critical Design Elements
- **Ground Plane**: Solid ground plane for noise reduction
- **Power Distribution**: Decoupling capacitors near ICs
- **Sensor Isolation**: Separate analog and digital sections
- **Antenna**: BLE antenna placement and tuning

### 6.3 Thermal Management
- **Heat Dissipation**: Minimal heat generation
- **Venting**: Not required (low power design)
- **Materials**: Standard FR4 PCB material

## 7. Manufacturing Considerations

### 7.1 Assembly
- **Process**: Automated SMD assembly
- **Testing**: In-circuit testing (ICT)
- **Calibration**: Factory calibration of sensors
- **Quality Control**: 100% functional testing

### 7.2 Cost Optimization
- **Component Selection**: Balance cost and performance
- **PCB Design**: Minimize layers and size
- **Assembly**: Standard processes
- **Volume**: Consider volume pricing

### 7.3 Supply Chain
- **Components**: Standard, readily available parts
- **Lead Times**: Consider component availability
- **Alternatives**: Identify alternative components
- **Standards**: RoHS compliant components

## 8. Testing and Validation

### 8.1 Hardware Testing
- **Functional Testing**: All features tested
- **Environmental Testing**: Temperature, humidity, shock
- **EMC Testing**: Electromagnetic compatibility
- **Battery Testing**: Life and charging cycles

### 8.2 Sensor Calibration
- **Factory Calibration**: Initial calibration
- **User Calibration**: Field calibration procedure
- **Verification**: Accuracy verification
- **Stability**: Long-term stability testing

### 8.3 Reliability Testing
- **MTBF Testing**: Mean time between failures
- **Accelerated Life Testing**: Stress testing
- **Field Testing**: Real-world usage testing
- **Failure Analysis**: Root cause analysis

## 9. Design Challenges and Solutions

### 9.1 Form Factor Constraints
- **Challenge**: Fit all components in pencil-like form
- **Solution**: Careful component selection and PCB design
- **Trade-offs**: May limit battery size or display

### 9.2 Sensor Accuracy
- **Challenge**: Achieve ±2-3° accuracy in small form factor
- **Solution**: High-quality sensors, proper calibration, sensor fusion
- **Trade-offs**: Cost vs. accuracy

### 9.3 Power Consumption
- **Challenge**: Long battery life in small form factor
- **Solution**: Low-power components, efficient algorithms, sleep modes
- **Trade-offs**: Performance vs. battery life

### 9.4 Environmental Robustness
- **Challenge**: Field conditions (dust, moisture, temperature)
- **Solution**: IP54 rating, rugged materials, proper sealing
- **Trade-offs**: Cost vs. protection level

## 10. Prototype Development Plan

### 10.1 Phase 1: Proof of Concept
- Basic sensor reading
- Simple angle calculation
- BLE communication
- Basic mobile app

### 10.2 Phase 2: Alpha Prototype
- Complete hardware design
- Full firmware implementation
- Mobile app with core features
- Initial testing

### 10.3 Phase 3: Beta Prototype
- Refined design based on testing
- Improved accuracy
- User testing
- Field trials

### 10.4 Phase 4: Production
- Final design
- Manufacturing setup
- Quality control
- Launch

