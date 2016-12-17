// ----------------------
// Left button - pin 16
// Right button - pin 14
// Speaker - pin 9
// Hall effect - pin 8
// ----------------------
// Hat pins, right to left
// GND
// VCC 
// SCL
// SDA
// PIN 6 
// PIN 10
// ----------------------

// RTTTL
#include <rtttl.h>
ProgmemPlayer player(9);
const char wishYou[] PROGMEM = "WeWishYo:d=4,o=5,b=140:4d,4g,8g,8a,8g,8f#,4e,4c,4e,4a,8a,8b,8a,8g,4f#,4d,4f#,4b,8b,8c6,8b,8a,4g,4e,4d,4e,4a,4f#,2g";
//const char jingle[] PROGMEM = "christmas:d=8,o=5,b=150:d,d,4g,g,g,4g,g,g,a,b,c6,a,4b.,p,4d6,a,b,c6,a,d6,d6,a,b,c6,a,4d6,4e6,4d.6,p,d6,c6,b,a,4g,a,b,4c6,4e,4e,4d,g,a,b,c6,4b,4a,2g.";

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

// Hat
const int santaLED = 10;
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
unsigned long blinkSince = 0;  // Millis wait times
unsigned long blinkWait = 40;  // Millis wait times
unsigned long blinkSince1 = 0;  // Millis wait times
unsigned long blinkWait1 = 40;  // Millis wait times

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

unsigned long previousMillis = 0;

// Boolean
boolean naughtyPick = true;

long snowSince = 0;
long snowWait = 200;

int snowMove1 = 0;
int snowMove2 = 3;
int snowMove3 = 5;
int snowMove4 = 2;
int snowMove5 = 6;
int snowMove6 = 1;
int snowMove7 = 7;
int snowMove8 = 4;

int switcher = 0;

long naughtyRand;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  accelgyro.initialize();
  matrix.begin(0x70);  // pass in the address

  pinMode(hallPin, INPUT); // Set hall effect sensor

  pinMode(buttonPin, INPUT_PULLUP); // Set button
  pinMode(buttonPin1, INPUT_PULLUP); // Set button

  pinMode(santaLED, OUTPUT); // Set santa hat led

  randomSeed(analogRead(0));
}

static const uint8_t PROGMEM

  star[] =
  { B00011000,
    B00111100,
    B01111110,
    B11111111,
    B00111100,
    B01111110,
    B01100110,
    B11000011 },

  tree[] =
  { B00011000,
    B00011000,
    B00111100,
    B01111110,
    B00111100,
    B01111110,
    B11111111,
    B00011000 },

  snowMan[] =
  { B00111100,
    B01000010,
    B10101001,
    B10010001,
    B01010010,
    B00111100,
    B01000010,
    B10011001 },

  santa[] =
  { B10000001,
    B10100101,
    B10000001,
    B10111101,
    B11111111,
    B01100110,
    B00111100,
    B00011000 };

void loop() {

  unsigned long currentMillis = millis();

  hallState = digitalRead(hallPin);
  int reading = digitalRead(buttonPin);
  int reading1 = digitalRead(buttonPin1);


// Santa hat coded
  if (millis() - blinkSince >= blinkWait) {
    blinkSince = millis();
    analogWrite(santaLED, brightness);
    brightness = brightness + fadeAmount;
  }
  
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }

  if (millis() - blinkSince1 >= blinkWait1) {
    blinkSince1 = millis();
    analogWrite(santaLED, brightness);
    brightness = brightness + fadeAmount;
  }

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }   

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//    Serial.print("X "); Serial.print(ax); Serial.print("\t");
//    Serial.print("Y "); Serial.print(ay); Serial.print("\t");
//    Serial.print("Z ");Serial.println(az);


  if (switcher == 0)
  {
    matrix.clear();
    matrix.setRotation(0); // Rotate to the on front
    matrix.drawBitmap(0, 0, santa, 8, 8, LED_ON);
    matrix.writeDisplay();
  } 

  if (switcher == 1)
  {
    matrix.clear();
    matrix.setRotation(0); // Rotate to the on front
    matrix.drawBitmap(0, 0, snowMan, 8, 8, LED_ON);
    matrix.writeDisplay();
  }

  if (switcher == 2)
  {
    matrix.clear();
    matrix.setRotation(0); // Rotate to the on front
    matrix.drawBitmap(0, 0, tree, 8, 8, LED_ON);
    matrix.writeDisplay();
  }

  if (switcher == 3)
  {

    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawPixel(0,snowMove1, LED_ON); // Draw pixel to screen
    matrix.drawPixel(1,snowMove2, LED_ON); // Draw pixel to screen
    matrix.drawPixel(2,snowMove3, LED_ON); // Draw pixel to screen
    matrix.drawPixel(3,snowMove4, LED_ON); // Draw pixel to screen
    matrix.drawPixel(4,snowMove5, LED_ON); // Draw pixel to screen
    matrix.drawPixel(5,snowMove6, LED_ON); // Draw pixel to screen
    matrix.drawPixel(6,snowMove7, LED_ON); // Draw pixel to screen
    matrix.drawPixel(7,snowMove8, LED_ON); // Draw pixel to screen
    matrix.writeDisplay();  // write the changes we just made to the display

    if (millis() - snowSince >= snowWait)
    {
      snowSince = millis();

      snowMove1 ++;
        if (snowMove1 == 8)
        {
          snowMove1 = 0;
        }

      snowMove2 ++;
        if (snowMove2 == 8)
        {
          snowMove2 = 0;
        }

      snowMove3 ++;
        if (snowMove3 == 8)
        {
          snowMove3 = 0;
        }

      snowMove4 ++;
        if (snowMove4 == 8)
        {
          snowMove4 = 0;
        }

      snowMove5 ++;
        if (snowMove5 == 8)
        {
          snowMove5 = 0;
        }

      snowMove6 ++;
        if (snowMove6 == 8)
        {
          snowMove6 = 0;
        }

      snowMove7 ++;
        if (snowMove7 == 8)
        {
          snowMove7 = 0;
        }

      snowMove8 ++;
        if (snowMove8 == 8)
        {
          snowMove8 = 0;
        }
    }
  }

  if (hallState == LOW) 
  {     
//    noTone(9);
//    tone(9, 440, 200); // Pin number, tone, duration

    if (naughtyPick == true)
    {
      naughtyRand = random(1, 4);
      Serial.print(naughtyRand);
      naughtyPick = false;
    }      

    if (naughtyRand == 1)
    {
      matrix.setTextSize(1);
      matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      matrix.setTextColor(LED_ON);

      for (int8_t x=0; x>=-25; x--) 
      {
        matrix.clear(); // Clear screen
        matrix.setCursor(x,0);
        matrix.print("Nice");
        matrix.writeDisplay(); // write the changes we just made to the display
        delay(100);
      }
    }

    if (naughtyRand == 2)
    {
      matrix.setTextSize(1);
      matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      matrix.setTextColor(LED_ON);

      for (int8_t x=0; x>=-40; x--) 
      {
        matrix.clear(); // Clear screen
        matrix.setCursor(x,0);
        matrix.print("Naughty");
        matrix.writeDisplay(); // write the changes we just made to the display
        delay(100);
      }
    }

    if (naughtyRand == 3)
    {
      matrix.setTextSize(1);
      matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      matrix.setTextColor(LED_ON);

      for (int8_t x=0; x>=-25; x--) 
      {
        matrix.clear(); // Clear screen
        matrix.setCursor(x,0);
        matrix.print("Nice");
        matrix.writeDisplay(); // write the changes we just made to the display
        delay(100);
      }
    }

  } 
  else 
  {
    naughtyPick = true;

  }

    if (reading != lastButtonState) 
    {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

      if ((millis() - lastDebounceTime) > debounceDelay) 
      {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
        if (reading != buttonState) 
        {
          buttonState = reading;

          if (buttonState == LOW) 
          {
            Serial.println("pressed");

            matrix.clear();
            matrix.setRotation(0); // Rotate to the on front
            matrix.drawBitmap(0, 0, star, 8, 8, LED_ON);
            matrix.writeDisplay();

            player.setSong(wishYou);
//            player.setSong(jingle);
            player.finishSong();
          }
        }
      }

      lastButtonState = reading; // save the reading.  Next time through the loop,

    if (reading1 != lastButtonState1) 
    {
        // reset the debouncing timer
        lastDebounceTime1 = millis();
    }

      if ((millis() - lastDebounceTime1) > debounceDelay1) 
      {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading1 != buttonState1) 
        {
          buttonState1 = reading1;

          if (buttonState1 == LOW) 
          {
//            Serial.println("pressed");

            noTone(9);
            tone(9, 500, 200); // Pin number, tone, duration

            switcher += 1;
            if (switcher == 4)
            {
              switcher = 0;
            }
          }
        }
      }

      lastButtonState1 = reading1; // save the reading.  Next time through the loop,
  }
