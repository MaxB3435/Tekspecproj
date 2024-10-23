#include <Wire.h>

void setup() {
  Wire.begin(1);                 // join i2c bus with address #4
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);            // start serial for output
}

void loop() {
}

void receiveEvent(int howMany) {
  if (howMany == 1) {
    int Points = Wire.read();  // receive byte as an integer
    Serial.println(Points);    // print the integer
  }
}
