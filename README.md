# WiFi Analyzer (C++)

A simple C++ command-line tool for wireless network analysis using monitor mode and passive scanning.

## Features

* Detect available wireless interfaces
* Enable monitor mode
* Disable monitor mode (restore normal Wi-Fi)
* Scan nearby networks using airodump-ng
* Menu-driven CLI interface

## Requirements

### Software

Install the following packages:

#### Debian / Ubuntu / Kali

```bash
sudo apt update
sudo apt install aircrack-ng iw ethtool
```

#### Arch Linux

```bash
sudo pacman -S aircrack-ng iw ethtool
```

### Hardware

* A wireless network adapter that supports **monitor mode**
* Some internal laptop adapters support monitor mode (depends on driver and chipset)
* For best compatibility, a USB Wi-Fi adapter with confirmed monitor mode support is recommended

## Installation

Clone the repository:

```bash
git clone https://github.com/B2krobbery/wifi-analyzer-cpp.git
cd wifi-analyzer-cpp
```

## Build

```bash
g++ main.cpp -o wifi-analyzer
```

## Run

```bash
sudo ./wifi-analyzer
```

## Usage

1. Select a wireless interface
2. Enable monitor mode
3. Start scanning
4. Disable monitor mode to restore normal Wi-Fi

## Notes

* Root privileges are required to modify network interface modes
* Monitor mode availability depends on your wireless adapter and driver
* NetworkManager may need to be stopped or restarted during operation

## Disclaimer

This project is intended for educational and authorized security testing purposes only.

Use this tool only on networks you own or have explicit permission to analyze.

The author is not responsible for any misuse of this software.

## License

MIT License
