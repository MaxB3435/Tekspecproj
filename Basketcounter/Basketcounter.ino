#include <Button.h>
//https://github.com/madleech/Button/blob/master/README.md


int team1;
int team2;
const int buttonPinP1T1 = 2;
const int buttonPinP2T1 = 3;
const int buttonPinP3T1 = 4;
const int buttonPinPmin1T1 = 5;

const int buttonPinP1T2 = 6;
const int buttonPinP2T2 = 7;
const int buttonPinP3T2 = 8;
const int buttonPinPmin1T2 = 9;

Button buttonP1T1(buttonPinP1T1);
Button buttonP2T1(buttonPinP2T1);
Button buttonP3T1(buttonPinP3T1);
Button buttonPmin1T1(buttonPinPmin1T1);

Button buttonP1T2(buttonPinP1T2);
Button buttonP2T2(buttonPinP2T2);
Button buttonP3T2(buttonPinP3T2);
Button buttonPmin1T2(buttonPinPmin1T2);


void setup() {
  buttonP1T1.begin();
  buttonP2T1.begin();
  buttonP3T1.begin();
  buttonPmin1T1.begin();

  buttonP1T2.begin();
  buttonP2T2.begin();
  buttonP3T2.begin();
  buttonPmin1T2.begin();

  Serial.begin(9600);
}

void loop() {

  if (buttonP1T1.pressed()) {
    team1 = team1 + 1;
  }
  if (buttonP2T1.pressed()) {
    team1 = team1 + 2;
  }
  if (buttonP3T1.pressed()) {
    team1 = team1 + 3;
  }
  if (buttonPmin1T1.pressed()) {
    team1 = team1 - 1;
  }

  if (buttonP1T2.pressed()) {
    team2 = team2 + 1;
  }
  if (buttonP2T2.pressed()) {
    team2 = team2 + 2;
  }
  if (buttonP3T2.pressed()) {
    team2 = team2 + 3;
  }
  if (buttonPmin1T2.pressed()) {
    team2 = team2 - 1;
  }

  Serial.println(team1);
  //Serial.println(team2);
}
