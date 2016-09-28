#include "I2Cdev.h" // I2C library
#include "MPU6050.h" // MPU6050 library
#include "Wire.h" // Wire library

MPU6050 accelgyro;
int16_t ax, ay, az; 
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO
bool blinkState = false;
 
void setup() {
 
  Wire.begin(); // Start wire library
  Serial.begin(9600); // Start serial
  accelgyro.initialize(); // Start mpu6050
}
 
void loop() {
 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Read mps6050
    Serial.print(ax); Serial.print("\t"); // Print X
    Serial.print(ay); Serial.print("\t"); // Print Y
    Serial.println(az); // Print Z

}
