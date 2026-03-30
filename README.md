# Hello World — M5Cardputer

Minimal firmware that displays "Hello World!" centered on the Cardputer screen.

## Prerequisites

- Nix with flakes enabled (see `./BUILD_ENVIRONMENT.md`)

## Build & Flash

```bash
# Enter ESP-IDF Nix shell
nix develop github:mirrexagon/nixpkgs-esp-dev#esp32-idf

# Set target (only needed once)
idf.py set-target esp32s3

# Build
idf.py build

# Flash + monitor
idf.py -p /dev/ttyACM0 flash -b 1500000 monitor
```

## Project Structure

```
cardputer_minimal/
├── CMakeLists.txt          # Top-level project CMake
├── sdkconfig.defaults      # ESP32-S3 / 8MB flash defaults
├── main/
│   ├── CMakeLists.txt      # Component registration
│   ├── idf_component.yml   # Pulls M5GFX from ESP component registry
│   └── main.cpp            # Hello World entry point
└── README.md
```
