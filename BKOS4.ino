#include <SPI.h>

// Selectie gebruikte hardware (tzt kijken of dit automatisch kan)
#define HARDWARE 2    // 0 : Raspberry pi pico (2) + ESP8266 s01
                      // 1 : Raspberry pi pico (2)W
                      // 2 : ESP32-2432s028r (CYD, Cheap Yellow Display)
                      // 3 : ESP32 VROOM     (38 pin versie)
                      // 4 : ESP32-8048S043C_I  (4,3 inch versie van de CYD), Kies "ESP32S3 Dev Module" als MCU
                      // 5 : ESP32-8048S070C_I  (4,3 inch versie van de CYD), Kies "ESP32S3 Dev Module" als MCU

// #define scherm_ili 9341  //  9341  of  9488
#define RESOLUTIE 2432   //  2432  of  3248 4880

#define ORIENTATIE 1 // 1 staand, 0 liggend

int SCRIPT_RESOLUTIE = 2432;

#include "hardware.h"
#include "diverse.h"
#include "BKOS.h"

void setup() {
  Serial.begin(9600);
  delay(50);
 
  // Note: The Adafruit librarys is not setting the backlight on, so we need to do that in code', flash size: 16mb, PSRAM: OPI PSRAM
  tft_setup();
  
  tft.fillScreen(kleur_zwart);
  // sd_setup();
  ts_setup();


  BKOS_boot();
  digitalWrite(TFT_BL, HIGH);

  scherm_touched = millis();
}


void loop(void) {
  if (scherm_actief) {
    ts_begin();
    if (ts_touched()) {
      scherm_touched = millis();
      actieve_touch = true;
      ts_x = touch_x();
      ts_y = touch_y();
      // fillCircle(ts_x, ts_y, 10, kleur_wit);
    } else {
      actieve_touch = false;
    }

    if ((millis() > scherm_touched + scherm_timer*1000) || (millis() < scherm_touched)) {
      scherm_actief = false;
      digitalWrite(TFT_BL, LOW);
    } else {
      app_uitvoeren();
    }
  } else {
    ts_begin();
    if (ts_touched()) {
      ts_begin();
      while (ts_touched()) {
        delay(50);
        ts_begin();
      }
      digitalWrite(TFT_BL, HIGH);
      scherm_actief = true;
      scherm_touched = millis();
      
    }
    
  }
  delay(50);
}