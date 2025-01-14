#include <Wire.h>
#include <Button.h>
//https://github.com/madleech/Button/blob/master/README.md
// https://docs.arduino.cc/learn/communication/wire/


byte team1;
byte team2;

byte state = 0;  // 0 = startup; 1 = game;

const int buttonPinP1T1 = 2;
const int buttonPinP2T1 = 3;
const int buttonPinP3T1 = 4;


const int buttonPinTime = 5;


const int buttonPinP1T2 = 6;
const int buttonPinP2T2 = 7;
const int buttonPinP3T2 = 8;


unsigned long holdTime = 650;
unsigned long prevUpdateTime = 0;

unsigned long interval = 1000;

short timeLeft = 0;

byte timeH;  // 2^8
byte timeL;  // 2^0

unsigned long updateInterval = 500;


bool timeRuning = false;

unsigned long previousMillis = 0;

unsigned long P1T1Time = 0;  // time since button pressed
unsigned long P2T1Time = 0;
unsigned long P3T1Time = 0;
unsigned long P1T2Time = 0;
unsigned long P2T2Time = 0;
unsigned long P3T2Time = 0;

unsigned long BTTime = 0;


Button buttonP1T1(buttonPinP1T1);
Button buttonP2T1(buttonPinP2T1);
Button buttonP3T1(buttonPinP3T1);


Button buttontime(buttonPinTime);


Button buttonP1T2(buttonPinP1T2);
Button buttonP2T2(buttonPinP2T2);
Button buttonP3T2(buttonPinP3T2);


void setup() {
  Wire.begin();
  buttonP1T1.begin();
  buttonP2T1.begin();
  buttonP3T1.begin();

  buttontime.begin();

  buttonP1T2.begin();
  buttonP2T2.begin();
  buttonP3T2.begin();



  Serial.begin(9600);
}

void loop() {
  buttonUpdate();
  unsigned long currentMillis = millis();
  if (timeRuning == true) {
    if (currentMillis - previousMillis >= interval && timeLeft > 0) {
      previousMillis = currentMillis;
      timeLeft--;
    }
    state = 1;
  }

  timeH = (timeLeft - (timeLeft % 256)) / 256;
  timeL = timeLeft % 256;

  sendCode();
}

void sendCode() {
  if (millis() - prevUpdateTime >= updateInterval) {
    prevUpdateTime = millis();
    Wire.beginTransmission(1);
    Wire.write(state);
    Wire.write(timeH);
    Wire.write(timeL);
    Wire.write(team1);
    Wire.write(team2);
    Wire.endTransmission();
  }
}

void buttonUpdate() {
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
  if (buttontime.pressed()) {
    BTTime = millis();
  }


  if (state == 0) {
    if (buttonP1T1.released()) {
      if (timeLeft > 59) {
        timeLeft -= 1;
      }
    }
    if (buttonP1T2.released()) {
      if (timeLeft < 5940) {
        timeLeft += 1;
      }
    }
    if (buttonP2T1.released()) {
      if (timeLeft > 0) {
        timeLeft -= 60;
      }
    }
    if (buttonP2T2.released()) {
      if (timeLeft < 5999) {
        timeLeft += 60;
      }
    }
    if (buttonP3T1.released()) {
      if (timeLeft > 599) {
        timeLeft -= 600;
      }
    }
    if (buttonP3T2.released()) {
      if (timeLeft < 5399) {
        timeLeft += 600;
      }
    }
  }

  if (state == 1) {
    if (buttonP1T1.released()) {
      if ((millis() - P1T1Time) > holdTime) {
        if (team1 == 0) {
          team1 = team1;
        } else {
          team1 -= 1;
        }
      } else {
        if (team1 < 99) {
          team1 += 1;
        } else {
          team1 = team1;
        }
      }
    }
    if (buttonP2T1.released()) {
      if ((millis() - P2T1Time) > holdTime) {
        if (team1 <= 1) {
          team1 = team1;
        } else {
          team1 -= 2;
        }
      } else {
        if (team1 < 98) {
          team1 += 2;
        } else {
          team1 = team1;
        }
      }
    }
    if (buttonP3T1.released()) {
      if ((millis() - P3T1Time) > holdTime) {
        if (team1 <= 2) {
          team1 = team1;
        } else {
          team1 -= 3;
        }
      } else {
        if (team1 < 97) {
          team1 += 3;
        } else {
          team1 = team1;
        }
      }
    }

    if (buttonP1T2.released()) {
      if ((millis() - P1T2Time) > holdTime) {
        if (team2 == 0) {
          team2 = team2;
        } else {
          team2 -= 1;
        }
      } else {
        if (team2 < 99) {
          team2 += 1;
        } else {
          team2 = team2;
        }
      }
    }
    if (buttonP2T2.released()) {
      if ((millis() - P2T2Time) > holdTime) {
        if (team2 <= 1) {
          team2 = team2;
        } else {
          team2 -= 2;
        }
      } else {
        if (team2 < 98) {
          team2 += 2;
        } else {
          team2 = team2;
        }
      }
    }
    if (buttonP3T2.released()) {
      if ((millis() - P3T2Time) > holdTime) {
        if (team2 <= 2) {
          team2 = team2;
        } else {
          team2 -= 3;
        }
      } else {
        if (team2 < 97) {
          team2 += 3;
        } else {
          team2 = team2;
        }
      }
    }
  }




  if (buttontime.released()) {
    if ((millis() - BTTime) > holdTime) {
      if (timeRuning == false) {
        if (state == 0) {
          state = 1;
        }
        if (state == 1) {
          state = 0;
        }
      }
    }


    else {
      if (timeRuning == true) {
        timeRuning = false;
      } else if (timeRuning == false) {
        timeRuning = true;
      }
    }
  }
}