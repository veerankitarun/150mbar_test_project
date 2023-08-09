#include <Wire.h>

// Define the I2C address of the pressure sensor
#define SENSOR_ADDRESS 0x30

// Define the scale factor and offset for the pressure sensor
const float SCALE_FACTOR = 1000;
const float OFFSET = 0;

// Define variables to store the sensor output voltage and the calculated pressure
float sensorOutputVoltage;
float pressure;

void setup() {
  // Initialize the Wire library
  Wire.begin();

  // Set up the serial port for debugging
  Serial.begin(9600);
}

void loop() {
  // Request data from the pressure sensor
  Wire.requestFrom(SENSOR_ADDRESS, 2);

  // Read the sensor output voltage from the sensor
  sensorOutputVoltage = Wire.read() + (Wire.read() << 8);

  // Calculate the pressure
  pressure = sensorOutputVoltage * SCALE_FACTOR + OFFSET;

  // Print the pressure to the serial port
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Delay for a second
  delay(1000);
}