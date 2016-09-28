#include "I2Cdev.h" // I2C library
#include "MPU6050.h" // MPU6050 library
#include "Wire.h" // Wire library

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN_Z 10 // Set LED to pin 10
#define LED_PIN_X 9 // Set LED to pin 9 
#define LED_PIN_Y 8  // Set LED to pin 8

bool blinkState = false;
 
void setup() {
 
  Wire.begin(); // Start wire library
  Serial.begin(9600); // Start serial
  accelgyro.initialize(); // Start mpu6050
  pinMode(LED_PIN_Z, OUTPUT); // Set LED pin as output
  pinMode(LED_PIN_X, OUTPUT); // Set LED pin as output
  pinMode(LED_PIN_Y, OUTPUT); // Set LED pin as output
}
 
void loop() {
 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Read mps6050
    Serial.print(ax); Serial.print("\t"); // Print X
    Serial.print(ay); Serial.print("\t"); // Print Y
    Serial.println(az); // Print Z

  if(16000 <= az or -16000 >= az) // If within range of the Z axis LED lights up
  {
    digitalWrite(LED_PIN_Z, HIGH); // Turn LED on
    Serial.println("Z"); // Serial print
    delay(50);
  }

  if(16000 <= ax or -16000 >= ax) // If within range of the X axis LED lights up
  {
    digitalWrite(LED_PIN_X, HIGH); // Turn LED on
    Serial.println("X"); // Serial print
    delay(50);
  }

  if(16000 <= ay or -16000 >= ay) // If within range of the Y axis LED lights up
  {
    digitalWrite(LED_PIN_Y, HIGH); // Turn LED on
    Serial.println("Y"); // Serial print
    delay(50);
  }

  else // Turn LED's off when out of range
  {
    digitalWrite(LED_PIN_Z, LOW); // Turn LED off
    digitalWrite(LED_PIN_X, LOW); // Turn LED off
    digitalWrite(LED_PIN_Y, LOW); // Turn LED off
  }
}
