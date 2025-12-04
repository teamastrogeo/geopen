# GeoPen Software Design

## 1. System Architecture

### 1.1 Overall Architecture
```
┌─────────────────────────────────────────┐
│         GeoPen Device (Firmware)        │
│  ┌──────────┐  ┌──────────┐            │
│  │  Sensor  │  │   BLE    │            │
│  │  Driver  │  │  Stack   │            │
│  └────┬─────┘  └────┬─────┘            │
│       │             │                   │
│  ┌────▼────────────▼─────┐            │
│  │   Measurement Engine   │            │
│  │  - Sensor Fusion       │            │
│  │  - Angle Calculation   │            │
│  │  - Calibration         │            │
│  └────────────────────────┘            │
└─────────────────────────────────────────┘
              │ BLE
              │
┌─────────────▼───────────────────────────┐
│      Mobile Application                 │
│  ┌──────────┐  ┌──────────┐            │
│  │   BLE    │  │   Data   │            │
│  │ Manager  │  │ Manager  │            │
│  └────┬─────┘  └────┬─────┘            │
│       │             │                   │
│  ┌────▼────────────▼─────┐            │
│  │   UI Layer             │            │
│  │  - Measurement Display  │            │
│  │  - History             │            │
│  │  - Settings            │            │
│  └────────────────────────┘            │
└─────────────────────────────────────────┘
              │
              │ Optional
              │
┌─────────────▼───────────────────────────┐
│      Cloud Service (Future)             │
│  - Data Sync                            │
│  - Backup                               │
│  - Collaboration                        │
└─────────────────────────────────────────┘
```

## 2. Firmware Design

### 2.1 Firmware Architecture

#### 2.1.1 Main Components
```
firmware/
├── main.c                    # Main entry point
├── drivers/
│   ├── imu_driver.c         # IMU sensor driver
│   ├── contact_sensor.c     # Contact sensor driver
│   ├── ble_stack.c          # BLE communication
│   └── power_mgmt.c        # Power management
├── algorithms/
│   ├── sensor_fusion.c     # Madgwick/Kalman filter
│   ├── angle_calc.c        # Angle calculation
│   └── calibration.c       # Calibration routines
├── services/
│   ├── measurement_service.c # Measurement logic
│   ├── config_service.c     # Configuration
│   └── device_info.c        # Device information
└── utils/
    ├── timer.c              # Timer utilities
    ├── storage.c            # Local storage
    └── logger.c            # Debug logging
```

### 2.2 Core Algorithms

#### 2.2.1 Sensor Fusion
**Algorithm**: Madgwick AHRS filter or Extended Kalman Filter

**Purpose**: Combine accelerometer and gyroscope data to estimate orientation

**Inputs**:
- Accelerometer data (ax, ay, az)
- Gyroscope data (gx, gy, gz)
- Magnetometer data (optional) (mx, my, mz)

**Outputs**:
- Quaternion (q0, q1, q2, q3) or Euler angles (roll, pitch, yaw)

**Implementation**:
```c
typedef struct {
    float q0, q1, q2, q3;  // Quaternion
    float beta;             // Filter gain
} MadgwickFilter;

void madgwick_update(MadgwickFilter* filter, 
                     float ax, float ay, float az,
                     float gx, float gy, float gz);
```

#### 2.2.2 Angle Calculation
**Alpha Angle**: 
- Calculated from pitch angle (rotation around Y-axis)
- Range: 0° to 90°
- Formula: `alpha = abs(pitch)`

**Beta Angle**:
- Calculated from yaw angle (rotation around Z-axis)
- Range: 0° to 360°
- Formula: `beta = (yaw + 360) % 360`

**Implementation**:
```c
typedef struct {
    float alpha;  // 0-90 degrees
    float beta;   // 0-360 degrees
} MeasurementAngles;

MeasurementAngles calculate_angles(float roll, float pitch, float yaw);
```

#### 2.2.3 Calibration
**Types**:
1. **Factory Calibration**: Offset and scale factors
2. **User Calibration**: Zero-point calibration
3. **Auto-Calibration**: Drift compensation

**Procedure**:
```c
typedef struct {
    float accel_offset[3];
    float gyro_offset[3];
    float accel_scale[3];
    float gyro_scale[3];
} CalibrationData;

void calibrate_sensors(CalibrationData* cal);
void apply_calibration(float* raw_data, CalibrationData* cal);
```

### 2.3 Measurement Flow

```
1. User presses trigger button
2. Device enters measurement mode
3. Wait for contact sensor (optional)
4. Read IMU data (100Hz for 2 seconds)
5. Apply sensor fusion algorithm
6. Calculate alpha and beta angles
7. Apply calibration corrections
8. Validate angles (range checking)
9. Store measurement locally
10. Transmit to mobile app via BLE
11. Return to idle mode
```

### 2.4 BLE Communication Protocol

#### 2.4.1 GATT Services

**Device Information Service (0x180A)**
- Manufacturer Name String (0x2A29)
- Model Number String (0x2A24)
- Firmware Revision String (0x2A26)
- Battery Level (0x2A19)

**Measurement Service (Custom UUID)**
- Alpha Angle Characteristic (Read/Notify)
- Beta Angle Characteristic (Read/Notify)
- Measurement Trigger Characteristic (Write)
- Measurement Status Characteristic (Notify)

**Configuration Service (Custom UUID)**
- Calibration Data Characteristic (Read/Write)
- Device Settings Characteristic (Read/Write)
- Measurement Mode Characteristic (Read/Write)

#### 2.4.2 Data Packets

**Measurement Packet**:
```c
typedef struct {
    uint32_t timestamp;      // Unix timestamp
    float alpha;             // Alpha angle (degrees)
    float beta;              // Beta angle (degrees)
    uint8_t quality_score;   // 0-100
    uint8_t status;          // Measurement status flags
} MeasurementPacket;
```

**Configuration Packet**:
```c
typedef struct {
    uint8_t measurement_mode;  // Single/Dual/Continuous
    uint8_t units;             // Degrees/Radians
    uint8_t auto_sleep;        // Enable/disable
    uint16_t sleep_timeout;    // Seconds
} ConfigurationPacket;
```

## 3. Mobile Application Design

### 3.1 Application Architecture

#### 3.1.1 Platform-Specific Architecture

**iOS (Swift/SwiftUI)**:
```
GeoPenApp/
├── App/
│   ├── GeoPenApp.swift          # App entry
│   └── AppDelegate.swift        # App delegate
├── Models/
│   ├── Measurement.swift         # Measurement model
│   ├── Device.swift             # Device model
│   └── Project.swift             # Project model
├── Services/
│   ├── BLEManager.swift         # BLE communication
│   ├── DataManager.swift        # Local data storage
│   └── CloudService.swift       # Cloud sync (future)
├── Views/
│   ├── ContentView.swift        # Main view
│   ├── MeasurementView.swift    # Measurement display
│   ├── HistoryView.swift        # Measurement history
│   └── SettingsView.swift       # Settings
└── Utils/
    ├── Extensions.swift          # Swift extensions
    └── Constants.swift          # App constants
```

**Android (Kotlin/Jetpack Compose)**:
```
GeoPenApp/
├── app/
│   ├── MainActivity.kt          # Main activity
│   ├── models/
│   │   ├── Measurement.kt      # Measurement model
│   │   ├── Device.kt           # Device model
│   │   └── Project.kt          # Project model
│   ├── services/
│   │   ├── BLEManager.kt       # BLE communication
│   │   ├── DataManager.kt      # Local data storage
│   │   └── CloudService.kt     # Cloud sync (future)
│   ├── ui/
│   │   ├── MainScreen.kt       # Main screen
│   │   ├── MeasurementScreen.kt # Measurement screen
│   │   ├── HistoryScreen.kt   # History screen
│   │   └── SettingsScreen.kt   # Settings screen
│   └── utils/
│       ├── Extensions.kt        # Kotlin extensions
│       └── Constants.kt         # App constants
```

### 3.2 Core Features Implementation

#### 3.2.1 BLE Manager

**iOS (Swift)**:
```swift
import CoreBluetooth

class BLEManager: NSObject, ObservableObject {
    @Published var isConnected = false
    @Published var currentMeasurement: Measurement?
    
    private var centralManager: CBCentralManager!
    private var connectedPeripheral: CBPeripheral?
    
    func scanForDevices()
    func connect(to device: CBPeripheral)
    func disconnect()
    func triggerMeasurement()
    func readMeasurement()
}
```

**Android (Kotlin)**:
```kotlin
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothGatt

class BLEManager(context: Context) {
    private val bluetoothAdapter: BluetoothAdapter?
    private var connectedGatt: BluetoothGatt? = null
    
    var isConnected = MutableStateFlow(false)
    var currentMeasurement = MutableStateFlow<Measurement?>(null)
    
    fun scanForDevices()
    fun connect(device: BluetoothDevice)
    fun disconnect()
    fun triggerMeasurement()
    fun readMeasurement()
}
```

#### 3.2.2 Data Manager

**Local Storage**: SQLite or Core Data (iOS) / Room (Android)

**Data Model**:
```swift
struct Measurement: Codable, Identifiable {
    let id: UUID
    let timestamp: Date
    let alphaAngle: Double
    let betaAngle: Double
    let deviceId: String
    let operatorId: String?
    let coreSampleId: String?
    let projectId: String?
    let qualityScore: Double
    let location: Location?
}

struct Location: Codable {
    let latitude: Double
    let longitude: Double
    let altitude: Double?
}
```

#### 3.2.3 Measurement Display

**Real-time Display**:
- Large, readable angle display
- Visual indicators (LED-like)
- Measurement status
- Connection status

**History View**:
- List of measurements
- Filtering and sorting
- Search functionality
- Export options

### 3.3 User Interface Design

#### 3.3.1 Main Screen
- Device connection status
- Quick measurement button
- Recent measurements
- Navigation to other screens

#### 3.3.2 Measurement Screen
- Large angle display (alpha and beta)
- Real-time updates
- Measurement trigger button
- Save measurement button
- Measurement metadata input

#### 3.3.3 History Screen
- List/grid view of measurements
- Filter by date, project, operator
- Search functionality
- Export options (CSV, JSON, PDF)
- Delete/edit measurements

#### 3.3.4 Settings Screen
- Device pairing and management
- Calibration assistant
- Measurement preferences
- Data export settings
- About and help

## 4. Data Management

### 4.1 Local Storage

**iOS**: Core Data or SQLite
**Android**: Room Database

**Schema**:
```sql
CREATE TABLE measurements (
    id TEXT PRIMARY KEY,
    timestamp INTEGER NOT NULL,
    alpha_angle REAL NOT NULL,
    beta_angle REAL NOT NULL,
    device_id TEXT,
    operator_id TEXT,
    core_sample_id TEXT,
    project_id TEXT,
    quality_score REAL,
    latitude REAL,
    longitude REAL,
    altitude REAL
);

CREATE INDEX idx_timestamp ON measurements(timestamp);
CREATE INDEX idx_project ON measurements(project_id);
```

### 4.2 Data Export

**CSV Format**:
```csv
Timestamp,Alpha Angle,Beta Angle,Device ID,Operator ID,Core Sample ID,Project ID,Quality Score,Latitude,Longitude
2025-01-15T10:30:00Z,45.5,120.3,GP-001,John Doe,CORE-123,PROJ-456,0.95,40.7128,-74.0060
```

**JSON Format**:
```json
{
  "measurements": [
    {
      "id": "uuid",
      "timestamp": "2025-01-15T10:30:00Z",
      "alpha_angle": 45.5,
      "beta_angle": 120.3,
      ...
    }
  ]
}
```

**PDF Report**:
- Formatted report with measurements
- Charts and graphs
- Project information
- Quality metrics

## 5. Security and Privacy

### 5.1 Data Security
- Encrypted local storage
- Secure BLE communication (encrypted characteristics)
- User authentication (optional)
- Data backup encryption

### 5.2 Privacy
- User data privacy compliance
- Optional location data
- User consent for data collection
- Data deletion options

## 6. Testing Strategy

### 6.1 Firmware Testing
- Unit tests for algorithms
- Integration tests for BLE
- Hardware-in-the-loop testing
- Field testing

### 6.2 Mobile App Testing
- Unit tests for business logic
- UI tests for user flows
- Integration tests for BLE
- Device compatibility testing
- User acceptance testing

## 7. Development Tools and Technologies

### 7.1 Firmware Development
- **IDE**: STM32CubeIDE, nRF Connect SDK, or PlatformIO
- **Language**: C/C++
- **RTOS**: FreeRTOS (optional)
- **Version Control**: Git
- **Build System**: CMake or Make

### 7.2 Mobile App Development
- **iOS**: Xcode, Swift, SwiftUI
- **Android**: Android Studio, Kotlin, Jetpack Compose
- **Cross-platform**: Consider Flutter or React Native (future)
- **Version Control**: Git
- **CI/CD**: GitHub Actions, GitLab CI, or similar

## 8. Future Enhancements

### 8.1 Cloud Integration
- Cloud sync service
- Web dashboard
- Multi-user collaboration
- Data analytics

### 8.2 Advanced Features
- Image capture for verification
- GPS integration
- Machine learning for quality improvement
- Integration with geological software

### 8.3 Platform Expansion
- Web application
- Desktop application
- API for third-party integration

