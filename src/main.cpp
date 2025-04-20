#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <SPI.h>
#include <SD.h>

// ========== HARDWARE CONFIGURATION ==========
// ADXL345 I2C Configuration
#define I2C_SDA 21  // Default ESP32 I2C SDA
#define I2C_SCL 22  // Default ESP32 I2C SCL

// SD Card SPI Configuration (ESP32 VSPI default)
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SCK  18
#define SD_CS   5

// ========== SENSOR & SD CARD OBJECTS ==========
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
File dataFile;

// ========== DATA LOGGING SETTINGS ==========
const unsigned long logInterval = 1000; // Log every 1 second
unsigned long lastLogTime = 0;
const char* filename = "/sensor_data.csv";

void initializeAccelerometer() {
  if(!accel.begin()) {
    Serial.println("Could not find ADXL345! Check:");
    Serial.println("- I2C connections (SDA/SCL)");
    Serial.println("- I2C address (try wire.begin(0x53))");
    Serial.println("- 3.3V power connection");
    while(1); // Halt on failure
  }
  accel.setRange(ADXL345_RANGE_16_G);
  Serial.println("ADXL345 initialized");
}

void initializeSDCard() {
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    Serial.println("Check:");
    Serial.println("- SPI pin connections");
    Serial.println("- SD card format (must be FAT32)");
    Serial.println("- CS pin configuration");
    while(1); // Halt on failure
  }
  Serial.println("SD Card initialized");

  // Create header if file doesn't exist
  if(!SD.exists(filename)) {
    dataFile = SD.open(filename, FILE_WRITE);
    if(dataFile) {
      dataFile.println("Timestamp (ms),X (m/s²),Y (m/s²),Z (m/s²)");
      dataFile.close();
      Serial.println("Created new data file");
    }
  }
}

void logData() {
  sensors_event_t event;
  accel.getEvent(&event);

  dataFile = SD.open(filename, FILE_APPEND);
  if(dataFile) {
    String dataString = String(millis()) + "," +
                       String(event.acceleration.x, 4) + "," +
                       String(event.acceleration.y, 4) + "," +
                       String(event.acceleration.z, 4);
    
    dataFile.println(dataString);
    dataFile.close();
    Serial.println("Logged: " + dataString);
  } else {
    Serial.println("Error opening data file!");
  }
}

void setup() {
  Serial.begin(115200);
  while(!Serial); // Wait for serial port
  
  Wire.begin(I2C_SDA, I2C_SCL);
  initializeAccelerometer();
  initializeSDCard();
}

void loop() {
  if(millis() - lastLogTime >= logInterval) {
    logData();
    lastLogTime = millis();
  }
}