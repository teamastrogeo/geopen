# GeoPen Quick Start Guide

## Get Started in 30 Minutes

This guide helps you get up and running quickly with GeoPen development.

## Prerequisites Check

- [ ] Development board (nRF52840 DK, STM32L4, or ESP32)
- [ ] IMU sensor (MPU6050 or BMI160)
- [ ] Computer with USB port
- [ ] Basic tools (breadboard, jumper wires)

## Step 1: Hardware Setup (10 minutes)

### Connect Sensor to Development Board

**For nRF52840 DK**:
```
MPU6050    →    nRF52840 DK
VCC       →     3.3V
GND       →     GND
SDA       →     P0.26 (A4)
SCL       →     P0.27 (A5)
```

**For ESP32**:
```
MPU6050    →    ESP32
VCC       →     3.3V
GND       →     GND
SDA       →     GPIO 21
SCL       →     GPIO 22
```

### Verify Connections
- Double-check all connections
- Ensure power is 3.3V (not 5V)
- Verify I2C pull-up resistors (usually on breakout board)

## Step 2: Software Setup (10 minutes)

### Install PlatformIO

**Option A: VS Code Extension**
1. Install VS Code
2. Install PlatformIO IDE extension
3. Restart VS Code

**Option B: Command Line**
```bash
pip install platformio
```

### Configure Project

1. Navigate to firmware directory:
```bash
cd hardware/firmware
```

2. Edit `platformio.ini` to match your board:
```ini
[env:nrf52840]  # or esp32dev, nucleo_l476rg
platform = nordicnrf52
board = nrf52840_dk
```

3. Install dependencies:
```bash
pio lib install "Wire"  # For I2C
```

## Step 3: Flash Firmware (5 minutes)

### Build and Upload

```bash
pio run -t upload
```

### Monitor Output

```bash
pio device monitor
```

**Expected Output**:
```
GeoPen Firmware v1.0.0
System initialized
IMU driver initialized
BLE stack initialized
```

## Step 4: Test Sensor (5 minutes)

### Verify Sensor Reading

You should see sensor data in serial monitor:
```
Accel: X=0.12, Y=-0.05, Z=9.81
Gyro: X=0.01, Y=0.02, Z=-0.01
```

### Test Movement

Move the sensor and verify values change appropriately.

## Step 5: Test Mobile App (Optional)

### iOS App

1. Open `software/mobile/ios/GeoPen.xcodeproj` in Xcode
2. Select your development team
3. Build and run on device or simulator
4. Grant Bluetooth permissions
5. Scan for devices

### Android App

1. Open `software/mobile/android/` in Android Studio
2. Sync Gradle files
3. Build and run on device or emulator
4. Grant Bluetooth permissions
5. Scan for devices

## Troubleshooting

### Sensor Not Detected

**Check**:
- Wiring connections
- I2C address (usually 0x68)
- Power supply (3.3V)
- Pull-up resistors

**Test**:
- Use I2C scanner sketch
- Check with multimeter

### No Serial Output

**Check**:
- USB cable (data capable)
- COM port selection
- Baud rate (115200)
- Serial monitor settings

### Build Errors

**Check**:
- PlatformIO version
- Board selection
- Library dependencies
- Toolchain installation

## Next Steps

1. **Test BLE**: Follow `docs/development/BLE_TESTING.md`
2. **Validate Accuracy**: Follow `docs/testing/test-plan.md`
3. **User Research**: Follow `docs/user-research/EXECUTION_PLAN.md`

## Getting Help

1. Check documentation in `docs/`
2. Review code comments
3. Check PlatformIO forums
4. Review sensor datasheets

## Common Commands

```bash
# Build firmware
pio run

# Upload firmware
pio run -t upload

# Monitor serial
pio device monitor

# Clean build
pio run -t clean

# List devices
pio device list
```

## Success Indicators

✅ Sensor data appears in serial monitor  
✅ Values change when sensor moved  
✅ No I2C errors  
✅ BLE advertising (check with nRF Connect app)  
✅ Mobile app can discover device  

## Ready for Development

Once you see sensor data and basic functionality working:
1. Start implementing sensor fusion
2. Test angle calculation
3. Implement BLE communication
4. Test end-to-end flow

Good luck with your development!

