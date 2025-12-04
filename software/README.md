# GeoPen Software Development

## Overview

This directory contains mobile applications (iOS and Android) and any supporting software for the GeoPen project.

**Device Geometry Reference**: 
- Device receives angle measurements from hardware
- Angles calculated based on IMU sensor at (0, 0, 15) mm position
- See `docs/mechanical/COMPONENT_DIMENSIONS.md` for device 3D specifications

## Structure

```
software/
├── mobile/
│   ├── ios/           # iOS application (Swift/SwiftUI)
│   └── android/       # Android application (Kotlin/Jetpack Compose)
├── web/              # Web dashboard (future)
└── api/              # Backend API (future)
```

## Mobile Applications

### iOS App
- **Language**: Swift
- **Framework**: SwiftUI
- **Minimum iOS**: 13.0
- **Location**: `software/mobile/ios/`

### Android App
- **Language**: Kotlin
- **Framework**: Jetpack Compose
- **Minimum Android**: API 26 (Android 8.0)
- **Location**: `software/mobile/android/`

## Getting Started

### iOS Development
```bash
cd software/mobile/ios
open GeoPen.xcodeproj
```

### Android Development
```bash
cd software/mobile/android
./gradlew build
```

## Features

- [ ] BLE device discovery and pairing
- [ ] Real-time angle display
- [ ] Measurement recording
- [ ] Measurement history
- [ ] Data export (CSV, JSON, PDF)
- [ ] Settings and configuration
- [ ] Calibration assistant

