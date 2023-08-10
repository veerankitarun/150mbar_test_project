#include <Wire.h>
#define SENSOR_ADDRESS 0x30

void setup() {
  Wire.begin(); // Initialize I2C communication
  Serial.begin(9600);
}

bool readSensor(uint8_t* buffer, uint8_t length) {
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.requestFrom(SENSOR_ADDRESS, length);
  if (Wire.available() < length) {
    return false; // Not enough data available
  }
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
  return true;
}

void loop() {
  uint8_t buffer[4];
  if (!readSensor(buffer, 4)) {
    Serial.println("Couldn't read");
    return;
  }

  Serial.print("Read: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print("0x");
    Serial.print(buffer[i], HEX);
    Serial.print(", ");
  }
  Serial.println();

  uint8_t status = buffer[0] >> 6;
  uint16_t pressure = 0;
  pressure = buffer[0] & 0x3F;
  pressure <<= 8;
  pressure |= buffer[1];

  uint16_t temp = buffer[2];
  temp <<= 8;
  temp |= buffer[3];
  temp >>= 5;

  float temp_f = static_cast<float>(temp);
  temp_f = (temp_f / 2047.0) * 200.0 - 50;

  float pres_f = static_cast<float>(pressure);
  
  // Convert hectopascals to millibars
  float millibars = ((pres_f - 1637) / 13107) * 7000;

  Serial.print("Pressure (hPa): ");
  Serial.print(pres_f);
  Serial.println(" hPa");
  
  Serial.print("Pressure (mb): ");
  Serial.print(millibars);
  Serial.println(" mb");

  Serial.print("Temperature: ");
  Serial.print(temp_f);
  Serial.println(" °C");

  delay(2000);
}
