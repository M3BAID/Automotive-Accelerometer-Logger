# 🚗 ESP32-C3 Accelerometer Logger with ADXL345 and SD Card

This project is an embedded system designed to **log real-time 3-axis acceleration data** using the **ADXL345 accelerometer** and store it on an **SD card** using an **ESP32-C3 microcontroller**. It is ideal for applications like **road condition monitoring**, **vehicle motion analysis**, or **vibration studies**.

---

## 📦 Features

- Logs X, Y, Z acceleration data with timestamps (`millis()`)
- Saves data in a CSV format on an SD card
- Uses I2C for ADXL345 and SPI for SD card
- Modular and clean Arduino-style code
- Easy to extend with RTC, GPS, or wireless communication

---

## 🔧 Hardware Requirements

- [x] ESP32-C3 board  
- [x] ADXL345 Accelerometer (I2C)  
- [x] SD Card Module (SPI)  
- [x] MicroSD card (FAT32 formatted)  
- [x] USB Cable + Power Source  

---

## 🔌 Wiring

### I2C (ADXL345)
| ADXL345 Pin | ESP32-C3 Pin |
|-------------|--------------|
| VCC         | 3.3V         |
| GND         | GND          |
| SDA         | GPIO 21      |
| SCL         | GPIO 22      |

### SPI (SD Card)
| SD Module Pin | ESP32-C3 Pin |
|---------------|--------------|
| MISO          | GPIO 19      |
| MOSI          | GPIO 23      |
| SCK           | GPIO 18      |
| CS            | GPIO 5       |
| VCC           | 3.3V         |
| GND           | GND          |

---

## 📁 File Format

The SD card will contain a file named `sensor_data.csv` with the following format:

