#include <Wire.h>
#include <Button.h>
//https://github.com/madleech/Button/blob/master/README.md
// https://docs.arduino.cc/learn/communication/wire/


byte team1;
byte team2;

int state = 0;  // 0 = startup; 1 = - ;2 = gameover;

const int buttonPinP1T1 = 2;
const int buttonPinP2T1 = 3;
const int buttonPinP3T1 = 4;

const int buttonPinP1T2 = 6;
const int buttonPinP2T2 = 7;
const int buttonPinP3T2 = 8;


const int buttonPinTime = 5;

unsigned long previousMillis = 0;
unsigned long holdTime = 650;
unsigned long prevUpdateTime = 0;
unsigned long interval = 1000;
short timeLeft = 3000;

byte timeH;  // 2^8
byte timeL;  // 2^0

unsigned long updateInterval = 500;


Button buttontime(buttonPinTime);

bool buttonpressed = false;

unsigned long P1T1Time = 0;  // time since button pressed
unsigned long P2T1Time = 0;
unsigned long P3T1Time = 0;
unsigned long P1T2Time = 0;
unsigned long P2T2Time = 0;
unsigned long P3T2Time = 0;



Button buttonP1T1(buttonPinP1T1);
Button buttonP2T1(buttonPinP2T1);
Button buttonP3T1(buttonPinP3T1);

Button buttonP1T2(buttonPinP1T2);
Button buttonP2T2(buttonPinP2T2);
Button buttonP3T2(buttonPinP3T2);


void setup() {
  Wire.begin();
  buttonP1T1.begin();
  buttonP2T1.begin();
  buttonP3T1.begin();

  buttonP1T2.begin();
  buttonP2T2.begin();
  buttonP3T2.begin();

  buttontime.begin();

  Serial.begin(9600);
}

void loop() {

  if (buttonP1T1.pressed()) {
    P1T1Time = millis();
  }
  if (buttonP2T1.pressed()) {
    P2T1Time = millis();
  }
  if (buttonP3T1.pressed()) {
    P3T1Time = millis();
  }

  if (buttonP1T2.pressed()) {
    P1T2Time = millis();
  }
  if (buttonP2T2.pressed()) {
    P2T2Time = millis();
  }
  if (buttonP3T2.pressed()) {
    P3T2Time = millis();
  }


  if (buttonP1T1.released()) {
    if ((millis() - P1T1Time) > holdTime) {
      team1 -= 1;
    } else {
      team1 += 1;
    }
  }
  if (buttonP2T1.released()) {
    if ((millis() - P2T1Time) > holdTime) {
      team1 -= 2;
    } else {
      team1 += 2;
    }
  }
  if (buttonP3T1.released()) {
    if ((millis() - P3T1Time) > holdTime) {
      team1 -= 3;
    } else {
      team1 += 3;
    }
  }

  if (buttonP1T2.released()) {
    if ((millis() - P1T2Time) > holdTime) {
      team2 -= 1;
    } else {
      team2 += 1;
    }
  }
  if (buttonP2T2.released()) {
    if ((millis() - P2T2Time) > holdTime) {
      team2 -= 2;
    } else {
      team2 += 2;
    }
  }
  if (buttonP3T2.released()) {
    if ((millis() - P3T2Time) > holdTime) {
      team2 -= 3;
    } else {
      team2 += 3;
    }
  }

  unsigned long currentMillis = millis();

  if (buttontime.pressed()) {
    if (buttonpressed == true) {
      buttonpressed = false;
    } else if (buttonpressed == false) {
      buttonpressed = true;
    }
  }

  if (buttonpressed == true) {
    if (currentMillis - previousMillis >= interval && timeLeft >= 0) {
      previousMillis = currentMillis;
      timeLeft--;
    }
  }

  timeH = (timeLeft - (timeLeft % 256))/256;
  timeL = timeLeft % 256; 



  //Serial.println(team1);
  //Serial.println(team2);
  //Serial.println(timeLeft);
  Serial.println(timeL);



  if (millis() - prevUpdateTime >= updateInterval) {
    prevUpdateTime = millis();
    Wire.beginTransmission(1);
    Wire.write(timeH);
    Wire.write(timeL);
    Wire.write(team1);
    Wire.write(team2);
    Wire.endTransmission();
  }
}