#include <Wire.h>

// Define accelerometer and gyroscope I2C addresses
#define ACCEL_ADDRESS 0x18 
#define GYRO_ADDRESS 0x69

// Define accelerometer and gyroscope interrupt mapping register addresses
#define ACCEL_INT_MAP_REG 0x58
#define GYRO_INT_MAP_REG 0x18

void setup() {
  Wire.begin(); // Initiate the Wire library and join the I2C bus as a master

  Wire.setClock(400000); // Set I²C clock speed to 400kHz.

  // Write to the accelerometer and gyroscope interrupt mapping registers.
  // This sets up how interrupts from the devices will be mapped and handled.
  writeRegister(ACCEL_ADDRESS, ACCEL_INT_MAP_REG, 0x04);
  writeRegister(GYRO_ADDRESS, GYRO_INT_MAP_REG, 0x01);
}

// Function to write a single byte of data to a specific register in the device.
void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress); // Send the register address to the device
  Wire.write(data); // Write the data to the register
  Wire.endTransmission();
}
