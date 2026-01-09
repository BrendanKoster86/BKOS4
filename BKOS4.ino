#include <SPI.h>

// Selectie gebruikte hardware (tzt kijken of dit automatisch kan)
#define HARDWARE 5    // 0 : Raspberry pi pico (2) + ESP8266 s01
                      // 1 : Raspberry pi pico (2)W
                      // 2 : ESP32-2432s028r (CYD, Cheap Yellow Display), kies "ESP32 WROOM DA Module"
                      // 3 : ESP32 VROOM     (38 pin versie) 
                      // 4 : ESP32-8048S043C_I  (4,3 inch versie van de CYD), Kies "ESP32S3 Dev Module" als MCU
                      // 5 : ESP32-8048S070C_I  (7,0 inch versie van de CYD), Kies "ESP32S3 Dev Module" als MCU

// #define scherm_ili 9341  //  9341  of  9488
#define RESOLUTIE 4880   //  2432  of  3248 4880

#define ORIENTATIE 0 // 1 staand, 0 liggend

#define use_freeRTOS 1  // 1 voor het gebruik fan freeRTOS

const unsigned long ota_git_interval = 5 * 60 * 1000;  // 5 minuten in milliseconds
unsigned long ota_git_check = 0;
const unsigned long ota_wifi_interval = 3  * 1000;  // 5 seconde in milliseconds
unsigned long ota_wifi_check = 0;

int SCRIPT_RESOLUTIE = 2432;
bool io_now = false;

#include "hardware.h"
#include "diverse.h"
#include "BKOS.h"

// void ioLoop();
// void guiLoop();

void setup() {
  Serial.begin(9600);
  delay(5000);
 
  // Note: The Adafruit librarys is not setting the backlight on, so we need to do that in code', flash size: 16mb, PSRAM: OPI PSRAM
  tft_setup();
  
  tft.fillScreen(kleur_zwart);
  delay(1000);
  BKOS_boot();
  delay(1000);
  
  digitalWrite(TFT_BL, HIGH);

  scherm_touched = millis();

  ota_setup();
  delay(15000);

#if use_freeRTOS == 1
  tft.println("");
  tft.println("start ioTask");
  // delay(500);
  xTaskCreatePinnedToCore(ioTask,
    "IO",
    2048,
    NULL,
    1,
    NULL,
    1);

  tft.println("startwifiTask");
  delay(500);
  xTaskCreatePinnedToCore(wifiTask,
    "WIFI",
    20480,
    NULL,
    1,
    NULL,
    1);
  
  tft.println("done");
  tft.println("exit setup");
  
#endif
}


void wifiLoop() {
  if (millis() > ota_git_check + ota_git_interval) {
    ota_wifi_update();
    // ota_git_update();
    ota_git_check = millis();
  } else if (millis() > ota_wifi_check + ota_wifi_interval){
    ota_wifi_update();
    ota_wifi_check = millis();
  }
}


void ioLoop(){
  if (io_now || (io_gecheckt + (io_timer)) < millis()) {
    io_now = false;
    io();
    delay(50);
    io();
  }
}

void guiLoop(){
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
      if (millis() > klok_getekend + 5000) {
        // klok_update();
        header_plaatsen();
      }
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
}


#if use_freeRTOS == 1

void ioTask(void* parameters){
  for (;;) {
    ioLoop();
    delay(50);
  }
}

void wifiTask(void* parameters){
  for (;;) {
    wifiLoop();
    delay(50);
  }
}

void guiTask(void* parameters){
  for (;;){
    guiLoop();
    delay(50);
  }
}

void loop() {
  guiLoop();
  // if (io_now) {
  //   if (io_actief){
  //     tft.fillCircle(15, 15, 12, tft.color565(0,0,255));
  //   } else {
  //     tft.fillCircle(15, 15, 12, tft.color565(255,0,0));
  //   }
  // } else if (io_actief) {
  //   tft.fillCircle(15, 15, 12, tft.color565(255, 0,255));
  // } else {
  //   tft.fillCircle(15, 15, 12, tft.color565(0, 255,0));
  // }
  delay(50);
}



#else
void loop(void) {
  ioLoop();
  guiLoop();
  wifiLoop();
  delay(50);
}
#endif