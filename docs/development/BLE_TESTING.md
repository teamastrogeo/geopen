# BLE Communication Testing Guide

## Overview

This guide covers end-to-end testing of Bluetooth Low Energy (BLE) communication between the GeoPen device and mobile applications.

## Test Setup

### Hardware Requirements
- GeoPen device (or development board with BLE)
- iOS device (iPhone/iPad) running iOS 13+
- Android device running Android 8.0+
- BLE-capable development board (nRF52840 DK recommended)

### Software Requirements
- iOS app installed on iOS device
- Android app installed on Android device
- Firmware flashed to GeoPen device
- Serial monitor for firmware debugging

## Test Scenarios

### 1. Device Discovery

**Objective**: Verify mobile app can discover GeoPen device

**Steps**:
1. Power on GeoPen device
2. Open mobile app
3. Navigate to Settings
4. Tap "Connect Device"
5. Tap "Scan"

**Expected Result**:
- GeoPen device appears in device list
- Device name and MAC address displayed
- Connection status shows "Scanning"

**Troubleshooting**:
- Ensure device is powered on
- Check BLE is enabled on mobile device
- Verify device is advertising (check firmware logs)
- Ensure app has Bluetooth permissions

### 2. Device Connection

**Objective**: Verify successful connection to GeoPen device

**Steps**:
1. Complete device discovery
2. Tap on GeoPen device in list
3. Wait for connection

**Expected Result**:
- Connection status changes to "Connected"
- Green indicator shown
- Device services discovered

**Troubleshooting**:
- Check firmware logs for connection events
- Verify BLE service UUIDs match
- Check mobile app logs for errors
- Ensure device is not already connected to another device

### 3. Measurement Trigger

**Objective**: Verify measurement can be triggered from mobile app

**Steps**:
1. Ensure device is connected
2. Navigate to Measurement screen
3. Tap "Measure" button
4. Observe measurement display

**Expected Result**:
- Measurement button responds
- Device receives trigger command
- Measurement data appears on screen
- Alpha and beta angles displayed

**Troubleshooting**:
- Check firmware receives trigger command (serial monitor)
- Verify measurement characteristic is writable
- Check sensor data is being read
- Verify angle calculation is working

### 4. Real-time Measurement Display

**Objective**: Verify measurement data updates in real-time

**Steps**:
1. Connect device
2. Trigger multiple measurements
3. Observe angle values

**Expected Result**:
- Angles update immediately after measurement
- Values are within valid ranges (alpha: 0-90°, beta: 0-360°)
- Quality score displayed
- Timestamp updates

**Troubleshooting**:
- Check BLE notification is enabled
- Verify data packet format matches specification
- Check for data parsing errors in app logs
- Verify sensor fusion is working correctly

### 5. Data Persistence

**Objective**: Verify measurements are saved correctly

**Steps**:
1. Take several measurements
2. Add metadata (operator, core sample, project IDs)
3. Save measurements
4. Navigate to History screen

**Expected Result**:
- All measurements appear in history
- Metadata is preserved
- Measurements persist after app restart

**Troubleshooting**:
- Check data storage implementation
- Verify measurement model serialization
- Check for storage permission issues
- Review data manager logs

### 6. Data Export

**Objective**: Verify measurement data can be exported

**Steps**:
1. Navigate to History screen
2. Tap export button
3. Select format (CSV or JSON)
4. Export data

**Expected Result**:
- Export file generated
- Data format is correct
- All measurements included
- File can be opened/shared

**Troubleshooting**:
- Check file format matches specification
- Verify all fields are included
- Check sharing permissions
- Review export implementation

### 7. Connection Stability

**Objective**: Verify connection remains stable during use

**Steps**:
1. Connect device
2. Use app for extended period (10+ minutes)
3. Take multiple measurements
4. Monitor connection status

**Expected Result**:
- Connection remains stable
- No unexpected disconnections
- Measurements continue to work
- Reconnection works if disconnected

**Troubleshooting**:
- Check BLE connection parameters
- Monitor signal strength (RSSI)
- Review power management settings
- Check for interference

### 8. Multiple Device Support

**Objective**: Verify app can handle multiple GeoPen devices

**Steps**:
1. Power on multiple GeoPen devices
2. Scan for devices
3. Connect to one device
4. Disconnect and connect to another

**Expected Result**:
- All devices appear in scan
- Can switch between devices
- Each device maintains separate measurements
- No conflicts between devices

**Troubleshooting**:
- Verify device identification
- Check measurement association with device ID
- Review connection management

## Test Checklist

### iOS Testing
- [ ] Device discovery works
- [ ] Connection successful
- [ ] Measurement trigger works
- [ ] Real-time updates work
- [ ] Data persistence works
- [ ] Export functionality works
- [ ] Connection stability verified
- [ ] Permissions properly requested

### Android Testing
- [ ] Device discovery works
- [ ] Connection successful
- [ ] Measurement trigger works
- [ ] Real-time updates work
- [ ] Data persistence works
- [ ] Export functionality works
- [ ] Connection stability verified
- [ ] Permissions properly requested (including runtime)

### Firmware Testing
- [ ] BLE advertising works
- [ ] Connection handling works
- [ ] Service discovery works
- [ ] Characteristic read/write works
- [ ] Notification works
- [ ] Measurement trigger received
- [ ] Data transmission works

## Debugging Tools

### iOS
- Xcode Console for app logs
- Instruments for BLE monitoring
- System Logs for Bluetooth events

### Android
- Logcat for app logs
- Bluetooth HCI snoop log
- Android Studio Profiler

### Firmware
- Serial monitor (PlatformIO)
- BLE sniffer (nRF Connect, Wireshark)
- Firmware debug logs

## Common Issues and Solutions

### Issue: Device Not Discovered
**Solution**: 
- Check device is advertising
- Verify service UUID matches
- Check scan filters
- Ensure BLE is enabled

### Issue: Connection Fails
**Solution**:
- Check device is not already connected
- Verify service/characteristic UUIDs
- Check connection parameters
- Review firmware connection handling

### Issue: No Measurement Data
**Solution**:
- Verify trigger command received
- Check sensor reading
- Verify data packet format
- Check notification enabled

### Issue: Data Parsing Errors
**Solution**:
- Verify byte order (little-endian)
- Check data packet size
- Review parsing implementation
- Add debug logging

## Performance Metrics

### Target Metrics
- Connection time: <5 seconds
- Measurement latency: <500ms
- Data transfer rate: Sufficient for real-time
- Connection range: 10+ meters

### Measurement
- Use timestamps to measure latency
- Monitor connection events
- Track data transfer rates
- Measure signal strength

## Next Steps

After successful BLE testing:
1. Proceed to field testing
2. Validate accuracy with reference measurements
3. Test in various environmental conditions
4. Gather user feedback
5. Optimize based on results

