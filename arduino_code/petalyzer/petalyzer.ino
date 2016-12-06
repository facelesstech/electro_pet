#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

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

// Breatherlizer
int analogPin = 10;  // Alcohol sensor
int minReading; // Lowest number as base
int maxReading;  // Max reading 
int adding = 400; // Number to be added to the minReading
int drunkLevel; // Store the mapped sensor value


int screenX; // The x axis on the load screen
int screenY = 0; // The y axis on the load screen

// Boolean
boolean readMode = false;
boolean resetMode = false;
boolean warmUpMode = false;
boolean warmUpText = true;
boolean preWarmUpMode = true;
boolean normalMode = false;
boolean blowText = false;
boolean resetText = true;
boolean loadScreen = true;

// Delay values
unsigned long readingSensorWait;
unsigned long resetingSensorWait;
unsigned long preWarmSince;
unsigned long preWarmWait = 5000;

void setup() {
  Serial.begin(9600); // Start serial
  matrix.begin(0x70);  // pass in the address
  pinMode(buttonPin, INPUT_PULLUP); // Button pullup
  pinMode(buttonPin1, INPUT_PULLUP); // Button pullup
}

static const uint8_t PROGMEM

  blow[] =
  { B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000 },

  reset[] =
  { B00111000,
    B01000100,
    B10000010,
    B10000111,
    B10000010,
    B01000000,
    B00111000,
    B00000000 },

  beer[] =
  { B00111111,
    B00111111,
    B11111111,
    B10100001,
    B10100001,
    B10100001,
    B11100001,
    B00111111 };

void loop() {

  int reading = digitalRead(buttonPin); // Read button
  int reading1 = digitalRead(buttonPin1); // Read button
  int sensor = analogRead(analogPin); // Reads the analogPin
//  Serial.println(drunkLevel);

  if (readMode == true)
  {

    while(millis() <= readingSensorWait)
    {
//      Serial.println("Blow now");
      drunkLevel = map(sensor, minReading, maxReading,0, 10);
      matrix.clear(); // Clear screen
      matrix.setRotation(0); // Rotate to the upright 
      matrix.drawBitmap(0, 0, blow, 8, 8, LED_ON);
      matrix.writeDisplay();  // write the changes we just made to the display
    } 

    readMode = false;
  }

  if (resetMode == true)
  {

    while(millis() <= resetingSensorWait)
    {
//      Serial.println("Reseting");
      minReading = sensor; // Sets the minReading to the curren sensor reading
      maxReading = sensor + adding; // Adds to the minReading to give you max reading
      matrix.clear(); // Clear screen
      matrix.setRotation(0); // Rotate to the upright 
      matrix.drawBitmap(0, 0, reset, 8, 8, LED_ON);
      matrix.writeDisplay();  // write the changes we just made to the display
    } 

    resetMode = false;
  }

  if (preWarmUpMode == true)
  {
    minReading = sensor; // Sets the minReading to the curren sensor reading
    maxReading = sensor + adding; // Adds to the minReading to give you max reading
    matrix.clear(); // Clear screen
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, beer, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    if (millis() - preWarmSince >= preWarmWait)
    {
    preWarmSince = millis();
    warmUpMode = true;
    }    

  }

  if (warmUpMode == true)
  {

    while (warmUpText == true)
    {
      matrix.setTextSize(1);
      matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
      matrix.setTextColor(LED_ON);

      for (int8_t x=0; x>=-35; x--) 
      {
        matrix.clear(); // Clear screen
        matrix.setCursor(x,0);
        matrix.print("Warmup");
        matrix.writeDisplay(); // write the changes we just made to the display
        delay(50);
        if (x == -35)
        {
          warmUpText = false;
        }
      }

    }

    while (loadScreen == true)
    {
      matrix.setRotation(0); // Rotate to the upright 
      matrix.drawPixel(screenX, screenY, LED_ON);  
      matrix.writeDisplay(); // write the changes we just made to the display
      screenX++;
      delay(1000);
      if(screenX == 8)
      {
        screenX = 0;
        screenY++;
      }
      if (screenY == 8)
      {
        loadScreen = false;
      }
//      Serial.println(screenY);
    }

    minReading = sensor; // Sets the minReading to the curren sensor reading
    maxReading = sensor + adding;
    preWarmUpMode = false;
    normalMode = true;
    blowText = true;
  
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
            //Serial.println("pressed right");
            noTone(9);
            tone(9, 500, 200); // Pin number, tone, duration

            while (resetText == true)
            {
              matrix.setTextSize(1);
              matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
              matrix.setTextColor(LED_ON);

              for (int8_t x=0; x>=-55; x--) 
              {
                matrix.clear(); // Clear screen
                matrix.setCursor(x,0);
                matrix.print("Resetting");
                matrix.writeDisplay();  // write the changes we just made to the display
                delay(50);
                if (x == -55)
                {
                resetText = false;
                }
              }
            }

            resetText = true;
            resetingSensorWait = millis() + 1000;
            resetMode = true;

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
            //Serial.println("pressed left");
            noTone(9);
            tone(9, 500, 200); // Pin number, tone, duration

            while (blowText == true)
            {
              matrix.setTextSize(1);
              matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
              matrix.setTextColor(LED_ON);

              for (int8_t x=0; x>=-30; x--) 
              {
                matrix.clear(); // Clear screen
                matrix.setCursor(x,0);
                matrix.print("Blow");
                matrix.writeDisplay(); // write the changes we just made to the display
                delay(50);
                if (x == -30)
                {
                blowText = false;
                }
              }
              readingSensorWait = millis() + 3000;
              readMode = true;

            }

            blowText = true;
            normalMode = true;
            warmUpMode = false;
            preWarmUpMode = false;
            blowText = true;

          }
        }
      }

      lastButtonState1 = reading1; // save the reading.  Next time through the loop,


  if (normalMode == true)
  {

    if (drunkLevel == 0) 
   {
//      Serial.println("0");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen
      matrix.setCursor(1,0);
      matrix.print("0");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 1) 
    {
//      Serial.println("1");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("1");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 2) 
    {
//      Serial.println("2");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("2");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 3) 
    {
//      Serial.println("3");

      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("3");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 4) 
    {
//      Serial.println("4");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("4");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 5) 
    {
//      Serial.println("5");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("5");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 6) 
    {
//      Serial.println("6");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("6");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 7) 
    {
//      Serial.println("7");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("7");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 8) 
    {
//      Serial.println("8");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("8");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 9) 
    {
//      Serial.println("9");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("9");
      matrix.writeDisplay(); // write the changes we just made to the display
    }

    if (drunkLevel == 10) 
    {
//      Serial.println("10");

      matrix.setTextSize(1);
      matrix.setTextColor(LED_ON);
      matrix.clear(); // Clear screen 
      matrix.setCursor(1,0);
      matrix.print("10");
      matrix.writeDisplay(); // write the changes we just made to the display
    }
  }
}
