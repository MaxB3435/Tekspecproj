#include <Wire.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10
#define DATA_PIN 11
#define CLK_PIN 9


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN2 4
#define DATA_PIN2 5
#define CLK_PIN2 3

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE,DATA_PIN ,CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola myDisplay2 = MD_Parola(HARDWARE_TYPE,DATA_PIN2 ,CLK_PIN2,  CS_PIN2, MAX_DEVICES);

unsigned long previousMillis = 0;
unsigned long prevUpdateTime = 0;
unsigned long interval = 1000;

char scoreBuffer1[10];
char scoreBuffer2[10];
char timeBuffer[6];

int Points1;
int Points2;
int time;
byte timeH;
byte timeL;

byte state;



void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(4);  // Sätt ljusstyrka
  myDisplay.displayClear();   // Rensa displayen

  myDisplay2.begin();
  myDisplay2.setIntensity(4);  // Sätt ljusstyrka
  myDisplay2.displayClear();   // Rensa displayen

  Wire.begin(1);                 // join i2c bus with address #1
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);            // start serial for output
}



void loop() {
  time = timeH * 256 + timeL;
  unsigned long currentMillis = millis();

  sprintf(scoreBuffer1, "%d", Points1);
  myDisplay.displayText(scoreBuffer1, PA_LEFT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();
  sprintf(scoreBuffer2, "%d", Points2);
  myDisplay.displayText(scoreBuffer2, PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();

  if (currentMillis - previousMillis >= interval && time >= 0) {
    previousMillis = currentMillis;

    int minutes = time / 60;
    int seconds = time % 60;

    sprintf(timeBuffer, "%02d:%02d", minutes, seconds);
    myDisplay2.displayText(timeBuffer, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    myDisplay2.displayAnimate();
    Serial.println(timeBuffer);
  }
}

void receiveEvent(int howMany) {
  while (4 < Wire.available()) {
    state = Wire.read();
  }
  while (3 < Wire.available()) {
    timeH = Wire.read();
  }
  while (2 < Wire.available()) {
    timeL = Wire.read();
  }
  while (1 < Wire.available()) {
    Points1 = Wire.read();  // receive byte as an integer
  }
  Points2 = Wire.read();
}