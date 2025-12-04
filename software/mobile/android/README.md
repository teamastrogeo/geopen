# GeoPen Android Application

## Overview

Android application for GeoPen device, built with Kotlin and Jetpack Compose.

## Requirements

- Android Studio Hedgehog or later
- Android SDK 26 (Android 8.0) or later
- Kotlin 1.9.0 or later

## Project Structure

```
android/
├── app/
│   ├── src/
│   │   ├── main/
│   │   │   ├── java/com/geopen/
│   │   │   │   ├── MainActivity.kt
│   │   │   │   ├── models/
│   │   │   │   ├── services/
│   │   │   │   ├── ui/
│   │   │   │   └── utils/
│   │   │   └── AndroidManifest.xml
│   │   └── test/
│   └── build.gradle.kts
├── build.gradle.kts
└── settings.gradle.kts
```

## Setup

1. Open project in Android Studio
2. Sync Gradle files
3. Build and run

## Features

- BLE device connection
- Real-time measurement display
- Measurement history
- Data export
- Settings and calibration

