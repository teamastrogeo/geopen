# GeoPen Hardware Setup Guide

## Overview

This guide helps you set up the hardware development environment for GeoPen proof-of-concept testing.

## Recommended Hardware

### Option 1: Nordic nRF52840 Development Kit (Recommended)

**Why**: Built-in BLE 5.0, good documentation, PlatformIO support

**Components**:
- nRF52840 DK (~$50)
- BMI160 or MPU6050 IMU breakout (~$10-20)
- Jumper wires
- Breadboard

**Pros**:
- Excellent BLE support
- Good development tools
- Active community

**Cons**:
- Slightly more expensive

### Option 2: STM32L4 Nucleo

**Why**: Lower cost, good performance, Arduino-compatible

**Components**:
- STM32L476RG Nucleo (~$30)
- BMI160 or MPU6050 IMU breakout (~$10-20)
- Jumper wires
- Breadboard

**Pros**:
- Lower cost
- Good performance
- STM32CubeIDE support

**Cons**:
- BLE requires external module (nRF52840 or ESP32)

### Option 3: ESP32 Development Board

**Why**: Very low cost, built-in BLE and Wi-Fi

**Components**:
- ESP32 DevKit (~$10)
- MPU6050 IMU breakout (~$5)
- Jumper wires
- Breadboard

**Pros**:
- Very low cost
- Built-in BLE
- Good for rapid prototyping

**Cons**:
- Less suitable for final product
- Power consumption higher

## Hardware Connections

### IMU Sensor Connections

#### For I2C Interface (Recommended):

```
IMU Sensor    →    Development Board
VCC          →    3.3V
GND          →    GND
SDA          →    I2C SDA (varies by board)
SCL          →    I2C SCL (varies by board)
```

**nRF52840 DK**:
- SDA → P0.26 (Arduino A4)
- SCL → P0.27 (Arduino A5)

**STM32L4 Nucleo**:
- SDA → PB9 (D14)
- SCL → PB8 (D15)

**ESP32**:
- SDA → GPIO 21
- SCL → GPIO 22

### Power Connections

- Use 3.3V for IMU sensors (most are 3.3V compatible)
- Check sensor datasheet for voltage requirements
- Use appropriate pull-up resistors for I2C (usually 4.7kΩ)

## Software Setup

### PlatformIO Setup

1. Install PlatformIO:
```bash
# Install PlatformIO IDE or VS Code extension
# Or use pip:
pip install platformio
```

2. Navigate to firmware directory:
```bash
cd hardware/firmware
```

3. Select target board in `platformio.ini`:
```ini
[env:nrf52840]
platform = nordicnrf52
board = nrf52840_dk
```

4. Build and upload:
```bash
pio run -t upload
```

5. Monitor serial output:
```bash
pio device monitor
```

### STM32CubeIDE Setup (Alternative)

1. Download and install STM32CubeIDE
2. Import project from `hardware/firmware/`
3. Configure target board
4. Build and flash

## Sensor Configuration

### MPU6050 Configuration

```c
// I2C address: 0x68 (default) or 0x69
// Accelerometer range: ±2g, ±4g, ±8g, ±16g
// Gyroscope range: ±250°/s, ±500°/s, ±1000°/s, ±2000°/s
// Sample rate: 1kHz (internal), configurable output rate
```

### BMI160 Configuration

```c
// I2C address: 0x68 (default) or 0x69
// Accelerometer range: ±2g, ±4g, ±8g, ±16g
// Gyroscope range: ±125°/s, ±250°/s, ±500°/s, ±1000°/s, ±2000°/s
// Sample rate: Up to 1600Hz
```

## Testing Procedures

### 1. Sensor Reading Test

**Objective**: Verify sensor is connected and reading data

**Steps**:
1. Flash firmware with sensor reading code
2. Open serial monitor
3. Move sensor and observe values
4. Verify values change appropriately

**Expected Output**:
```
Accel: X=0.12, Y=-0.05, Z=9.81
Gyro: X=0.01, Y=0.02, Z=-0.01
```

### 2. Calibration Test

**Objective**: Verify calibration procedure works

**Steps**:
1. Place device on flat surface
2. Run calibration routine
3. Verify offsets calculated correctly
4. Test with known orientations

**Expected**: Offsets should compensate for sensor bias

### 3. Angle Calculation Test

**Objective**: Verify angle calculation accuracy

**Steps**:
1. Place device at known angle (use protractor)
2. Take measurement
3. Compare calculated angle with reference
4. Repeat for multiple angles

**Expected**: Accuracy within ±3°

### 4. BLE Communication Test

**Objective**: Verify BLE advertising and connection

**Steps**:
1. Flash firmware with BLE enabled
2. Use nRF Connect app (mobile) to scan
3. Verify device appears
4. Connect and verify services discovered

**Expected**: Device visible, connection successful

## Troubleshooting

### Sensor Not Detected

**Symptoms**: No data from sensor, I2C errors

**Solutions**:
- Check wiring (VCC, GND, SDA, SCL)
- Verify I2C address (check datasheet)
- Check pull-up resistors (4.7kΩ on SDA/SCL)
- Verify power supply (3.3V)
- Test with I2C scanner sketch

### Incorrect Sensor Readings

**Symptoms**: Values don't make sense, constant values

**Solutions**:
- Check sensor configuration
- Verify sensor range settings
- Check for sensor initialization
- Verify I2C communication speed
- Test with known sensor library

### BLE Not Advertising

**Symptoms**: Device not visible in scan

**Solutions**:
- Verify BLE stack initialized
- Check service UUIDs
- Verify advertising started
- Check BLE power/range settings
- Use BLE sniffer to debug

### Connection Issues

**Symptoms**: Can't connect, connection drops

**Solutions**:
- Check connection parameters
- Verify service/characteristic UUIDs match
- Check MTU size
- Verify notification enabled
- Review BLE stack logs

## Development Tips

1. **Start Simple**: Get basic sensor reading first
2. **Test Incrementally**: Add features one at a time
3. **Use Serial Monitor**: Debug with print statements
4. **Document Changes**: Keep notes on what works
5. **Version Control**: Commit working versions

## Next Steps

After hardware setup:
1. Test sensor reading
2. Implement sensor fusion
3. Test angle calculation
4. Implement BLE
5. Test end-to-end

## Resources

- Sensor Datasheets: Check manufacturer websites
- Development Board Docs: Check manufacturer sites
- PlatformIO Docs: https://docs.platformio.org/
- nRF Connect App: For BLE testing
- Arduino Libraries: Good starting point for sensor code

## Cost Estimate

**Minimum Setup** (ESP32):
- ESP32 DevKit: $10
- MPU6050: $5
- Breadboard + wires: $5
- **Total**: ~$20

**Recommended Setup** (nRF52840):
- nRF52840 DK: $50
- BMI160 breakout: $15
- Breadboard + wires: $5
- **Total**: ~$70

**Professional Setup** (STM32 + nRF):
- STM32L4 Nucleo: $30
- nRF52840 module: $10
- BMI160 breakout: $15
- Breadboard + wires: $5
- **Total**: ~$60

