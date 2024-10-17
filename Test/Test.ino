#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Button.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

unsigned long previousMillis = 0;
const long interval = 1000;  // Uppdateringsintervall (1 sekund)
int timeLeft = 610;          // Starta nedräkningen från 600 sekunder (10 minuter)

const int buttonPinTime = 9;

bool buttonpressed = false;

Button buttontime(buttonPinTime);

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(4);  // Sätt ljusstyrka
  myDisplay.displayClear();   // Rensa displayen

  buttontime.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (buttontime.pressed()) {
    if (buttonpressed == true) {
      buttonpressed = false;
    }
    else if (buttonpressed == false) {
      buttonpressed = true;
    }
  }

  if (buttonpressed == true) {
    if (currentMillis - previousMillis >= interval && timeLeft >= 0) {
      previousMillis = currentMillis;

      // Beräkna minuter och sekunder
      int minutes = timeLeft / 60;
      int seconds = timeLeft % 60;

      // Formatera tiden som mm:ss
      char timeBuffer[6];
      sprintf(timeBuffer, "%02d:%02d", minutes, seconds);

      // Visa tiden på displayen
      myDisplay.displayText(timeBuffer, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

      // Minska tiden med 1 sekund
      timeLeft--;
    }
    if (timeLeft == 600) {
      myDisplay.displayText("start", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

    } else if (timeLeft == 0) {
      myDisplay.displayText("slut", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    }
  }

  // Uppdatera displayen
  myDisplay.displayAnimate();
}
