// RTTTL
#include <rtttl.h>
ProgmemPlayer player(9);
const char song_P[] PROGMEM = "Adams Family:d=8,o=5,b=160:c,4f,a,4f,c,4b4,2g,f,4e,g,4e,g4,4c,2f,c,4f,a,4f,c,4b4,2g,f,4e,c,4d,e,1f,c,d,e,f,1p,d,e,f#,g,1p,d,e,f#,g,4p,d,e,f#,g,4p,c,d,e,f";

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

unsigned long previousMillis = 0;

long skullSince1= 0;
long skullSince2 = 500;
long skullWait1 = 500;
long skullWait2 = 1000;

long eyeSince = 0;
long eyeWait = 200;
boolean eyeLeft = true;
boolean eyeRight = false;
int eyeMoveH = 2;
int eyeMoveV = 4;

long eyeBlinkSince = 0;
long eyeBlinkWait = 2000;
//long blinkSince1 = 0;
//long blinkSince2 = 50;
//long blinkSince3 = 100;
//long blinkSince4 = 150;
//long blinkWait = 150;
boolean blinking = false;

//long creeperSince1= 0;
//long creeperSince2 = 500;
//long creeperWait1 = 500;
//long creeperWait2 = 1000;

int switcher = 0;

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

  creeper[] =
  { B11111111,
    B10011001,
    B10011001,
    B11111111,
    B11100111,
    B11000011,
    B11011011,
    B11111111 },

//  creeper[] =
//  { B11111111,
//    B11111111,
//    B11111111,
//    B11111111,
//    B11100111,
//    B11000011,
//    B11011011,
//    B11111111 },

  pumpkin[] =
  { B00000000,
    B01000010,
    B11100111,
    B10100101,
    B00000000,
    B11011011,
    B11111111,
    B01011010 },

  eye[] =
  { B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100 },

  eyeBlinkOne[] =
  { B00000000,
    B00111100,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00111100,
    B00000000 },

  eyeBlinkTwo[] =
  { B00000000,
    B00000000,
    B00111100,
    B01111110,
    B01111110,
    B00111100,
    B00000000,
    B00000000 },

  eyeBlinkThree[] =
  { B00000000,
    B00000000,
    B00000000,
    B00111100,
    B00111100,
    B00000000,
    B00000000,
    B00000000 },

  skull[] =
  { B01111110,
    B11111111,
    B10011001,
    B10011001,
    B11111111,
    B01111110,
    B01011010,
    B01111110 };


void eyeBlink() {
  Serial.println("blinking");
{
//  if (millis() >= blinkSince1)
//  {
    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, eyeBlinkOne, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(50);
//  blinkSince1 += blinkWait;
//  }

//  if (millis() >= blinkSince2)
//  {
    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, eyeBlinkTwo, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(50);
//  blinkSince2 += blinkWait;
//  }

//  if (millis() >= blinkSince3)
//  {
    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, eyeBlinkThree, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(50);
//  blinkSince3 += blinkWait;
//  }

//  if (millis() >= blinkSince4)
//  {
    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, eyeBlinkTwo, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(50);
//  blinkSince4 += blinkWait;
//  }
}
}


void loop() {
  Serial.println(switcher);
  unsigned long currentMillis = millis();

  hallState = digitalRead(hallPin);
  int reading = digitalRead(buttonPin);
  int reading1 = digitalRead(buttonPin1);

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//    Serial.print("X "); Serial.print(ax); Serial.print("\t");
//    Serial.print("Y "); Serial.print(ay); Serial.print("\t");
//    Serial.print("Z ");Serial.println(az);


  if (switcher == 0)
  {
    // EYE
  matrix.clear(); 
  matrix.setRotation(0); // Rotate to the upright 
  matrix.drawBitmap(0, 0, eye, 8, 8, LED_ON);
  matrix.drawRect(eyeMoveH,eyeMoveV, 2,2, LED_OFF);
  matrix.writeDisplay();  // write the changes we just made to the display

  if (millis() - eyeSince >= eyeWait)
  {
  eyeSince = millis();
    if (eyeLeft == true)  
    {
      eyeMoveH += 1;
      if (eyeMoveH == 5)
      {
        eyeLeft = false;
        eyeRight = true;
      }
    }

    if (eyeRight == true)  
    {
      eyeMoveH -= 1;
      if (eyeMoveH == 2)
      {
        eyeRight = false;
        eyeLeft = true;
      }
    }
  } 

  if (millis() - eyeBlinkSince >= eyeBlinkWait)
  {
  eyeBlinkSince = millis();
    eyeBlink();
  }
  }

  if (switcher == 1)
  {
  // SKULL
    if (millis() - skullSince1 >= skullWait1)
    {
    skullSince1 = millis();
      matrix.clear(); 
      matrix.setRotation(0); // Rotate to the upright 
      matrix.drawBitmap(0, 0, skull, 8, 8, LED_ON);
      matrix.drawPixel(1, 3, LED_ON);  
      matrix.drawPixel(5, 3, LED_ON);  
      matrix.writeDisplay();  // write the changes we just made to the display
    } 

    if (millis() - skullSince2 >= skullWait2)
    {
    skullSince2 = millis();
      matrix.clear(); 
      matrix.setRotation(0); // Rotate to the upright 
      matrix.drawBitmap(0, 0, skull, 8, 8, LED_ON);
      matrix.drawPixel(2, 3, LED_ON);  
      matrix.drawPixel(6, 3, LED_ON);  
      matrix.writeDisplay();  // write the changes we just made to the display
    } 
  }

  if (switcher == 2)
  {

//    if (millis() - creeperSince1 >= creeperWait1)
//    {
//    creeperSince1 = millis();
//      matrix.clear(); 
//      matrix.setRotation(0); // Rotate to the upright 
//      matrix.drawBitmap(0, 0, creeper, 8, 8, LED_ON);
//      matrix.drawRect(1,1, 2,2, LED_OFF);
//      matrix.drawRect(5,1, 2,2, LED_OFF);
//      matrix.writeDisplay();  // write the changes we just made to the display
//    } 
//
//    if (millis() - creeperSince2 >= creeperWait2)
//    {
//    creeperSince2 = millis();
//      matrix.clear(); 
//      matrix.setRotation(0); // Rotate to the upright 
//      matrix.drawBitmap(0, 0, creeper, 8, 8, LED_ON);
//      matrix.drawRect(2,1, 2,2, LED_OFF);
//      matrix.drawRect(6,1, 2,2, LED_OFF);
//      matrix.writeDisplay();  // write the changes we just made to the display
//    } 
    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, creeper, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display

    }

  if (switcher == 3)
  {

    matrix.clear(); 
    matrix.setRotation(0); // Rotate to the upright 
    matrix.drawBitmap(0, 0, pumpkin, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    }

    if (hallState == LOW) {     
      noTone(9);
      tone(9, 440, 200); // Pin number, tone, duration
    } 
    else 
    {

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
            player.setSong(song_P);
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
            Serial.println("pressed");
            noTone(9);
//            tone(9, 440, 200); // Pin number, tone, duration
            tone(9, 200, 200); // Pin number, tone, duration
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
