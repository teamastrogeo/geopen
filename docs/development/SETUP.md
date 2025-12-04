# GeoPen Development Setup Guide

## Overview

This guide helps developers set up the development environment for GeoPen firmware and mobile applications.

## Prerequisites

### General
- Git
- Code editor (VS Code, Cursor, or IDE)
- Terminal/Command line access

### Firmware Development
- PlatformIO or STM32CubeIDE
- ARM toolchain
- Serial port access (for debugging)

### iOS Development
- macOS (required)
- Xcode 14.0 or later
- iOS 13.0+ device or simulator
- Apple Developer account (for device testing)

### Android Development
- Android Studio Hedgehog or later
- Android SDK 26+
- Android device or emulator
- Java Development Kit (JDK) 11+

## Quick Start

### 1. Clone Repository
```bash
git clone <repository-url>
cd GeoPen_2025
```

### 2. Firmware Setup

#### Using PlatformIO (Recommended)
```bash
cd hardware/firmware
pio install
pio run
```

#### Using STM32CubeIDE
1. Install STM32CubeIDE
2. Import project from `hardware/firmware/`
3. Configure target board (nRF52840 or STM32L4)
4. Build project

### 3. iOS App Setup
```bash
cd software/mobile/ios
open GeoPen.xcodeproj
```

In Xcode:
1. Select development team
2. Build and run (Cmd+R)
3. Select simulator or connected device

### 4. Android App Setup
```bash
cd software/mobile/android
./gradlew build
```

In Android Studio:
1. Open project
2. Sync Gradle files
3. Build and run

## Development Workflow

### Firmware Development
1. Make changes in `hardware/firmware/src/`
2. Build: `pio run`
3. Upload: `pio run -t upload`
4. Monitor: `pio device monitor`

### Mobile App Development
1. Make changes in respective app directory
2. Build and test on simulator/emulator
3. Test on physical device
4. Run tests: `./gradlew test` (Android) or Cmd+U (iOS)

## Code Style

### Firmware (C/C++)
- Follow MISRA C guidelines
- Use 4-space indentation
- Function names: `snake_case`
- Constants: `UPPER_SNAKE_CASE`

### iOS (Swift)
- Follow Swift API Design Guidelines
- Use 4-space indentation
- Use SwiftUI for UI
- Follow MVVM architecture

### Android (Kotlin)
- Follow Kotlin Coding Conventions
- Use 4-space indentation
- Use Jetpack Compose for UI
- Follow MVVM architecture

## Testing

### Run All Tests
```bash
# Firmware
cd hardware/firmware
pio test

# iOS
cd software/mobile/ios
xcodebuild test

# Android
cd software/mobile/android
./gradlew test
```

## Debugging

### Firmware Debugging
- Use serial monitor: `pio device monitor`
- Add logging: `logger_info()`, `logger_error()`
- Use debugger in IDE

### Mobile App Debugging
- Use Xcode debugger (iOS)
- Use Android Studio debugger (Android)
- Check logs in console

## Common Issues

### Firmware
- **Build errors**: Check toolchain installation
- **Upload errors**: Check USB connection and drivers
- **Sensor not working**: Verify I2C/SPI connections

### Mobile Apps
- **BLE not working**: Check permissions in Info.plist/AndroidManifest.xml
- **Build errors**: Clean build folder and rebuild
- **Simulator issues**: Reset simulator/emulator

## Resources

### Documentation
- Firmware: `hardware/firmware/README.md`
- iOS: `software/mobile/ios/README.md`
- Android: `software/mobile/android/README.md`

### External Resources
- PlatformIO: https://platformio.org/
- nRF Connect SDK: https://developer.nordicsemi.com/
- SwiftUI: https://developer.apple.com/xcode/swiftui/
- Jetpack Compose: https://developer.android.com/jetpack/compose

## Getting Help

- Check documentation in `docs/`
- Review code comments
- Ask team members
- Check issue tracker

