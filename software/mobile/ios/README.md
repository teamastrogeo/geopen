# GeoPen iOS Application

## Overview

iOS application for GeoPen device, built with Swift and SwiftUI.

## Requirements

- Xcode 14.0 or later
- iOS 13.0 or later
- Swift 5.7 or later

## Project Structure

```
ios/
├── GeoPen/
│   ├── App/
│   │   ├── GeoPenApp.swift
│   │   └── AppDelegate.swift
│   ├── Models/
│   │   ├── Measurement.swift
│   │   ├── Device.swift
│   │   └── Project.swift
│   ├── Services/
│   │   ├── BLEManager.swift
│   │   ├── DataManager.swift
│   │   └── CloudService.swift
│   ├── Views/
│   │   ├── ContentView.swift
│   │   ├── MeasurementView.swift
│   │   ├── HistoryView.swift
│   │   └── SettingsView.swift
│   └── Utils/
│       ├── Extensions.swift
│       └── Constants.swift
├── GeoPenTests/
└── GeoPenUITests/
```

## Setup

1. Open `GeoPen.xcodeproj` in Xcode
2. Select your development team in Signing & Capabilities
3. Build and run

## Features

- BLE device connection
- Real-time measurement display
- Measurement history
- Data export
- Settings and calibration

