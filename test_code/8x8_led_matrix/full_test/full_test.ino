/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {

  matrix.setRotation(0); // Rotate upright
  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.setRotation(1); // Rotate left
  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.setRotation(2);  // Rotate upside down
  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.setRotation(3); // Rotate right
  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawPixel(0, 0, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawLine(0,0, 7,7, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawRect(0,0, 8,8, LED_ON); // Tell the screen what you want it to draw
  matrix.fillRect(2,2, 4,4, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.clear(); // Clears all pixals
  matrix.drawCircle(3,3, 3, LED_ON); // Tell the screen what you want it to draw
  matrix.writeDisplay(); // Write the changes we just made to the display
  delay(500);

  matrix.setTextSize(0); // Text size 0 will fit on normal 8x8 but 2 is too big
  matrix.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON); // Turn display on LED_OFF to turn it off
  matrix.setRotation(1); // Set rotation
  for (int8_t x=0; x>=-36; x--) { // X is lenght of text
    matrix.clear(); // Clears all pixals
    matrix.setCursor(x,0);  // Tell the screen what you want it to draw
    matrix.print("Hello"); // Tell the screen what you want it to draw
    matrix.writeDisplay(); // Write the changes we just made to the display
    delay(100);
  }
  matrix.setTextSize(1); // 1 Doesn't appear to change from 0 but 2 is too big
  matrix.setRotation(3); // Set rotation
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear(); // Clears all pixals
    matrix.setCursor(x,0); // set which line it start on
    matrix.print("World"); // text that will be displayed
    matrix.writeDisplay(); // Write the changes we just made to the display
    delay(100);
  }
}
