# Firmware Unit Tests

## Overview

Unit tests for GeoPen firmware components.

## Running Tests

### Using PlatformIO
```bash
cd hardware/firmware
pio test
```

### Manual Compilation
```bash
gcc -o test_angle_calc test_angle_calc.c ../src/algorithms/angle_calc.c -lm
./test_angle_calc
```

## Test Coverage

### Current Tests
- [x] Angle calculation (alpha/beta)
- [x] Angle validation
- [ ] Sensor fusion algorithm
- [ ] Calibration routines
- [ ] Measurement service

## Adding New Tests

1. Create test file in `tests/` directory
2. Include necessary headers
3. Use assert() for test assertions
4. Add to test runner or run individually

