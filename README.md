# WiFi Analyzer (C++)

A simple C++ command-line tool for wireless network analysis using monitor mode and passive scanning.

## Features

* Detect available wireless interfaces
* Enable monitor mode
* Disable monitor mode (restore normal Wi-Fi)
* Scan nearby networks using airodump-ng
* Basic menu-driven CLI

## Requirements

Install the following packages before running the tool:

## Hardware Requirements

* A wireless network adapter that supports **monitor mode**
* Some laptop internal adapters support monitor mode, but support depends on the driver and chipset
* For best compatibility, a USB Wi-Fi adapter with confirmed monitor mode support is recommended

## Notes

* Monitor mode availability depends on your wireless adapter and driver
* If monitor mode is not supported, the tool will not be able to scan networks


### Debian / Ubuntu / Kali

sudo apt update
sudo apt install aircrack-ng iw ethtool

### Arch Linux

sudo pacman -S aircrack-ng iw ethtool

## Build

g++ main.cpp -o wifi-analyzer

## Run

sudo ./wifi-analyzer

## Usage

1. Select a wireless interface
2. Enable monitor mode
3. Start scan
4. Disable monitor mode to restore normal Wi-Fi

## Notes

* Root privileges are required to modify network interface modes
* Monitor mode support depends on your wireless adapter and driver
* NetworkManager may need to be stopped or restarted during operation

## Disclaimer

This project is intended for educational and authorized security testing purposes only.

Use this tool only on networks you own or have explicit permission to analyze.

The author is not responsible for any misuse of this software.

## License

MIT License
