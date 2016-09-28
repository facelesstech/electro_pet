/*
Multiple tone player

Plays multiple tones on multiple pins in sequence

circuit:
8-ohm speaker on digital pins 9 

created 8 March 2010
by Tom Igoe
based on a snippet from Greg Borenstein

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/Tone4

*/

void setup() {

}

void loop() {
  noTone(9); // Turn off tone function for pin 9 
  tone(9, 440, 200); // Play a note on pin 9 for 200 ms
  delay(200); // Delay 200 ms

  noTone(9); // Turn off tone function for pin 9
  tone(9, 494, 500); // Play a note on pin 9 for 500 ms:
  delay(500); // Delay 500 ms

  noTone(9); // Turn off tone function for pin 9 
  tone(9, 523, 300); // Play a note on pin 9 for 300 ms
  delay(300); // Delay 300 ms
}
