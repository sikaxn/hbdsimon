#include "pin_config.h"
#include "picoImage.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h
SPIClass hspi(HSPI);
int x, y = 0;

#define BOOT_PIN 0     // IO0 button
bool manualMode = false;



void setup(void)
{
  Serial.begin(115200);

  // LED indicator
  pinMode(LED_PIN, OUTPUT);

  pinMode(BOOT_PIN, INPUT_PULLUP);   


  digitalWrite(LED_PIN, LOW);

  // Init TFT
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.setTextFont(2);
  tft.fillScreen(TFT_BLACK);

  // Show the default LilyGO image on boot
  //tft.pushImage(0, 0, 240, 135, Lilygo1);

  // Backlight fade-in
  ledcSetup(0, 4000, 8);
  ledcAttachPin(TFT_BL, 0);
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle += 5) {
    ledcWrite(0, dutyCycle);
    delay(5);
  }

  // Prepare for your own text/drawing later
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeMono9pt7b);

}

void loop()
{
  static uint32_t lastSwitch = 0;
  static int mode = 0;   // 0 = text, 1 = hbd1, 2 = hbd2, 3 = hbd3
  static uint32_t lastButton = 0;

  // ----------------------------------------------------------
  // AUTO MODE
  // ----------------------------------------------------------
  if (!manualMode) {
    if (millis() - lastSwitch >= 2000) {
      lastSwitch = millis();
      mode = (mode + 1) % 4;
      tft.fillScreen(TFT_BLACK);

      if (mode == 0) {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.setTextSize(2);
        tft.drawString("HBD", tft.width() / 2, tft.height() / 2);
      }
      else if (mode == 1) tft.pushImage(0, 0, HBD_W, HBD_H, hbd1);
      else if (mode == 2) tft.pushImage(0, 0, HBD_W, HBD_H, hbd2);
      else if (mode == 3) tft.pushImage(0, 0, HBD_W, HBD_H, hbd3);
    }
  }

  // ----------------------------------------------------------
  // MANUAL MODE (BOOT pressed at startup)
  // ----------------------------------------------------------
  else {
    // BOOT = LOW = pressed
    if (digitalRead(BOOT_PIN) == LOW) {
      if (millis() - lastButton > 300) {   // debounce
        lastButton = millis();

        mode = (mode + 1) % 4;
        tft.fillScreen(TFT_BLACK);

        if (mode == 0) {
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.setTextDatum(MC_DATUM);
          tft.setTextSize(2);
          tft.drawString("HBD", tft.width() / 2, tft.height() / 2);
        }
        else if (mode == 1) tft.pushImage(0, 0, HBD_W, HBD_H, hbd1);
        else if (mode == 2) tft.pushImage(0, 0, HBD_W, HBD_H, hbd2);
        else if (mode == 3) tft.pushImage(0, 0, HBD_W, HBD_H, hbd3);
      }
    }
  }

  // ----------------------------------------------------------
  // LED heartbeat (unchanged)
  // ----------------------------------------------------------
  digitalWrite(LED_PIN, HIGH);
  delay(20);
  digitalWrite(LED_PIN, LOW);
  delay(20);
}


