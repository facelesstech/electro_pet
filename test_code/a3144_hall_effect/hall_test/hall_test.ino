const int hallPin = 12; // Hall effect sensor pin
const int ledPin =  13; // LED pin

int hallState = 0; // Variable for reading the hall sensor status

void setup() {
  pinMode(ledPin, OUTPUT); // initialize the LED pin as an output:
  pinMode(hallPin, INPUT); // initialize the hall effect sensor pin as an input:
}

void loop(){
  hallState = digitalRead(hallPin); // read the state of the hall effect sensor:

  if (hallState == LOW) 
  {     
    digitalWrite(ledPin, HIGH); // Turn LED on:    
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // Turn LED off:
  }
}
