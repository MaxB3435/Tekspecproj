#include <Wire.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

char scoreBuffer1[10];
char scoreBuffer2[10];

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(4);  // Sätt ljusstyrka
  myDisplay.displayClear();   // Rensa displayen



  Wire.begin(1);                 // join i2c bus with address #4
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);            // start serial for output
}
int Points1;
int Points2;

void loop() {
  sprintf(scoreBuffer1, "%d", Points1);
  myDisplay.displayText(scoreBuffer1, PA_LEFT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();
  sprintf(scoreBuffer2, "%d", Points2);
  myDisplay.displayText(scoreBuffer2, PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {
    Points1 = Wire.read();  // receive byte as an integer
  }
  Points2 = Wire.read();
}