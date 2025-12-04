# GeoPen Firmware

## Overview

Embedded firmware for the GeoPen device, running on ARM Cortex-M4 microcontroller.

## Architecture

```
firmware/
├── src/
│   ├── main.c              # Main entry point
│   ├── drivers/            # Hardware drivers
│   ├── algorithms/         # Sensor fusion, angle calculation
│   ├── services/          # BLE services, measurement logic
│   └── utils/              # Utilities, storage, logging
├── include/                # Header files
├── tests/                  # Unit tests
└── platformio.ini          # PlatformIO configuration
```

## Building

Using PlatformIO:
```bash
cd hardware/firmware
pio run
pio run -t upload
```

Using STM32CubeIDE:
1. Import project
2. Build project
3. Flash to device

## Development Status

- [ ] Basic sensor reading
- [ ] Sensor fusion algorithm
- [ ] Angle calculation
- [ ] BLE communication
- [ ] Calibration system
- [ ] Power management

