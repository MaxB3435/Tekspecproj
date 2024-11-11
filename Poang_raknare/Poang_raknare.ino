#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Button.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int team1 = 0;  // Poängen för Team 1
int team2 = 0;
char scoreBuffer1[10];  // Buffer för att lagra poäng som sträng
char scoreBuffer2[10];

const int buttonPinP1T1 = 9;
const int buttonPinP2T1 = 3;
const int buttonPinP3T1 = 4;


const int buttonPinP1T2 = 8;
const int buttonPinP2T2 = 7;
const int buttonPinP3T2 = 6;

unsigned long holdTime = 650;  // Gräns för att avgöra lång- eller korttryck

unsigned long P1T1Time = 0;  // Tid sedan knappen trycktes ned
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

  myDisplay.begin();
  myDisplay.setIntensity(4);  // Sätt ljusstyrka
  myDisplay.displayClear();   // Rensa displayen

  Serial.begin(9600);  // Starta seriell kommunikation för felsökning
}

void loop() {
  // Kolla om någon av knapparna trycks ned
  if (buttonP1T1.pressed()) {
    P1T1Time = millis();  // Registrera tid när knappen trycks ned
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

  // Kontrollera när knapparna släpps och uppdatera poängen
  if (buttonP1T1.released()) {
    if ((millis() - P1T1Time) > holdTime) {
      team1 -= 1;
      Serial.println((millis() - P1T1Time));
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

  // Konvertera poängen till en sträng och visa på displayen
  sprintf(scoreBuffer1, "%d", team1);
  myDisplay.displayText(scoreBuffer1, PA_LEFT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();
  sprintf(scoreBuffer2, "%d", team2);
  myDisplay.displayText(scoreBuffer2, PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  myDisplay.displayAnimate();
  

}
