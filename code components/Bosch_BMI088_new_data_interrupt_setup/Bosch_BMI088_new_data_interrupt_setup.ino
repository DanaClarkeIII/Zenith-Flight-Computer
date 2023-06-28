#include <Wire.h>

#define ACCEL_ADDRESS 0x18
#define GYRO_ADDRESS 0x69

#define ACCEL_INT_MAP_REG 0x58
#define GYRO_INT_MAP_REG 0x18

void setup() {
  Wire.begin();
  Wire.setClock(400000); // Set I²C clock speed to 400kHz

  writeRegister(ACCEL_ADDRESS, ACCEL_INT_MAP_REG, 0x04);
  writeRegister(GYRO_ADDRESS, GYRO_INT_MAP_REG, 0x01);
}

void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.write(data);
  Wire.endTransmission();
}