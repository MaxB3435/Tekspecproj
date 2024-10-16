#include <Button.h>
//https://github.com/madleech/Button/blob/master/README.md


int team1;
int team2;
const int buttonPinP1T1 = 2;
const int buttonPinP2T1 = 3;
const int buttonPinP3T1 = 4;

const int buttonPinP1T2 = 6;
const int buttonPinP2T2 = 7;
const int buttonPinP3T2 = 8;

unsigned long holdTime = 400;



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
  buttonP1T1.begin();
  buttonP2T1.begin();
  buttonP3T1.begin();

  buttonP1T2.begin();
  buttonP2T2.begin();
  buttonP3T2.begin();

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


  Serial.println(team1);
  //Serial.println(team2);
}
