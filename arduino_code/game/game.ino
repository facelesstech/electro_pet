// LED matrix
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Accelerometer
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO

// Hall effect sensor
const int hallPin = 8; // the number of the hall effect sensor pin
int hallState = 0; // variable for reading the hall sensor status

// Button right
const int buttonPin = 14; // the number of the pushbutton pin
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 50; // the debounce time; increase if the output flickers

// Button left
const int buttonPin1 = 16; // the number of the pushbutton pin
int buttonState1; // the current reading from the input pin
int lastButtonState1 = LOW; // the previous reading from the input pin
long lastDebounceTime1 = 0; // the last time the output pin was toggled
long debounceDelay1 = 50; // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  accelgyro.initialize();
  matrix.begin(0x70);  // pass in the address

  pinMode(hallPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
}

static const uint8_t PROGMEM

  edge[] =
  { B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111 };

void loop() {

  hallState = digitalRead(hallPin);
  int reading = digitalRead(buttonPin);
  int reading1 = digitalRead(buttonPin1);

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print("X "); Serial.print(ax); Serial.print("\t");
  Serial.print("Y "); Serial.print(ay); Serial.print("\t");
  Serial.print("Z ");Serial.println(az);

  int mappedY = map(ay, -3000, 3000, 0, 7);
  Serial.println(mappedY);
  int mappedX = map(ax, -3000, 3000, 7, 0);
  Serial.println(mappedX);

//  matrix.clear();
//  matrix.setRotation(0); // Rotate to the on front
//  matrix.drawBitmap(0, 0, edge, 8, 8, LED_ON);
//  matrix.writeDisplay();

  matrix.clear(); 
  matrix.setRotation(0); // Rotate to the upright 
  matrix.drawPixel(mappedY, mappedX, LED_ON);  
  matrix.drawBitmap(0, 0, edge, 8, 8, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display

  if (mappedX == 0 || mappedX == 7 || mappedY == 0 || mappedY == 7)
  {
    noTone(9);
    tone(9, 500, 100); // Pin number, tone, duration
  }

  if (hallState == LOW) 
  {     
    noTone(9);
    tone(9, 440, 200); // Pin number, tone, duration
  } 
  else 
  {
  }

  if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == LOW) {
          Serial.println("pressed");
          noTone(9);
          tone(9, 440, 200); // Pin number, tone, duration
        }
      }
    }

    lastButtonState = reading; // save the reading.  Next time through the loop,

  if (reading1 != lastButtonState1) {
      // reset the debouncing timer
      lastDebounceTime1 = millis();
    }

    if ((millis() - lastDebounceTime1) > debounceDelay1) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading1 != buttonState1) {
        buttonState1 = reading1;

        if (buttonState1 == LOW) {
          Serial.println("pressed");
          noTone(9);
          tone(9, 440, 200); // Pin number, tone, duration
        }
      }
    }

    lastButtonState1 = reading1; // save the reading.  Next time through the loop,
}
