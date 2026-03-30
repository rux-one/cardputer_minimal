# M5Cardputer Minimal Firmware — Build Environment Requirements

## Hardware Target

- **MCU**: ESP32-S3 (Xtensa dual-core)
- **Flash**: 8 MB
- **Display**: ST7789 135×240 TFT (SPI), managed via M5GFX / LovyanGFX
- **Board**: M5Stack Cardputer

## Toolchain

| Component | Version | Notes |
|---|---|---|
| **ESP-IDF** | **v5.5.2** (via Nix) | Nix shell provides v5.5.2 |
| CMake | ≥ 3.16 | Bundled with ESP-IDF |
| Python | 3.8+ | Needed by ESP-IDF build system |
| Xtensa toolchain | `xtensa-esp-elf-` | Provided by the Nix shell |

### Environment Setup (NixOS / Nix)

```bash
nix develop github:mirrexagon/nixpkgs-esp-dev#esp32-idf
```

This drops you into a shell with `idf.py`, the Xtensa toolchain, and all dependencies.

## ESP-IDF Component Dependencies

Resolved from `main/idf_component.yml` and `dependencies.lock`:

| Component | Version | Purpose |
|---|---|---|
| `espressif/cmake_utilities` | 0.5.3 | Build helpers |
| `espressif/esp-now` | 2.5.1 | ESP-NOW wireless |
| `leeebo/tinyusb_src` | 0.16.0~4 | USB HID (IDF 4.4 path) |

These are fetched automatically by the IDF Component Manager on first build.

## Vendored Components (in `components/`)

| Component | Version | Purpose |
|---|---|---|
| **M5GFX** | 0.1.15 | Graphics / display driver (LovyanGFX-based) |
| **mooncake** | — | App framework / launcher |
| **infrared_tools** | — | IR transmit/receive |

## Partition Table

Custom `partitions.csv`:

| Name | Type | SubType | Offset | Size |
|---|---|---|---|---|
| nvs | data | nvs | 0x9000 | 0x5000 (20 KB) |
| phy_init | data | phy | 0xF000 | 0x1000 (4 KB) |
| factory | app | factory | 0x10000 | 4 MB |
| storage | data | fat | auto | 1 MB |

## Key sdkconfig Settings

```
CONFIG_IDF_TARGET="esp32s3"
CONFIG_ESPTOOLPY_FLASHSIZE="8MB"
CONFIG_ESPTOOLPY_FLASHFREQ="80m"
CONFIG_PARTITION_TABLE_CUSTOM=y
CONFIG_PARTITION_TABLE_CUSTOM_FILENAME="partitions.csv"
CONFIG_ESP32S3_DEFAULT_CPU_FREQ_MHZ=160
# No PSRAM / SPIRAM enabled
```

## Build Commands

### hello_world (IDF v5.5.2 via Nix)

```bash
nix develop github:mirrexagon/nixpkgs-esp-dev#esp32-idf
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyACM0 flash -b 1500000 monitor
```

The resulting `.bin` files are output to `build/`:
- `build/<project_name>.bin` — application binary
- `build/bootloader/bootloader.bin` — bootloader
- Connect Cardputer via USB-C, flash: `build/partition_table/partition-table.bin` — partition table
