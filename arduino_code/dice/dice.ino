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

long randNumber;

// Boolean
boolean warmUpText = true;
boolean warmUpMode = true;

void setup() {
  Serial.begin(9600);
  
  accelgyro.initialize();
  matrix.begin(0x70);  // pass in the address

  pinMode(hallPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);

  randomSeed(analogRead(0));
}

static const uint8_t PROGMEM

  question[] =
  { B00111100,
    B01000010,
    B01000010,
    B00000100,
    B00001000,
    B00010000,
    B00000000,
    B00010000 };

void loop() {

  hallState = digitalRead(hallPin);
  int reading = digitalRead(buttonPin);
  int reading1 = digitalRead(buttonPin1);

  if (warmUpMode == true)
  {

    while (warmUpText == true)
    {
      matrix.setTextSize(1);
      matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      matrix.setTextColor(LED_ON);

      for (int8_t x=0; x>=-25; x--) 
      {
        matrix.clear(); // Clear screen
        matrix.setCursor(x,0);
        matrix.print("Dice");
        matrix.writeDisplay(); // write the changes we just made to the display
        delay(50);
        if (x == -25)
        {
          warmUpText = false;
        }
      }
    matrix.clear();
    matrix.setRotation(0); // Rotate to the on back
    matrix.drawBitmap(0, 0, question, 8, 8, LED_ON);
    matrix.writeDisplay();
    }
  }

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//    Serial.print("Z ");Serial.println(az);
//    Serial.print("X "); Serial.print(ax); Serial.print("\t");
//    Serial.print("Y "); Serial.print(ay); Serial.print("\t");
    Serial.println(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);   

  if(30000 <= gx || 30000  <= gz || -30000 >= gx || -30000 >= gz)
  {
    matrix.clear();
    matrix.setRotation(0); // Rotate to the on back
    matrix.drawBitmap(0, 0, question, 8, 8, LED_ON);
    matrix.writeDisplay();
    randNumber = random(1, 7);
    delay(500);
  }

    Serial.println(randNumber);

    if (randNumber == 1) 
    {
      Serial.println("1");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("1");
      matrix.writeDisplay();
    }

    if (randNumber == 2) 
    {
      Serial.println("2");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("2");
      matrix.writeDisplay();
    }

    if (randNumber == 3) 
    {
      Serial.println("3");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("3");
      matrix.writeDisplay();
    }

    if (randNumber == 4) 
    {
      Serial.println("4");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("4");
      matrix.writeDisplay();
    }

    if (randNumber == 5) 
    {
      Serial.println("5");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("5");
      matrix.writeDisplay();
    }

    if (randNumber == 6) 
    {
      Serial.println("6");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear();
      matrix.setCursor(1,0);
      matrix.print("6");
      matrix.writeDisplay();
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
