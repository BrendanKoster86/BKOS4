void ota_wifi_update() {
  ArduinoOTA.handle();
}

void ota_wifi_setup(){
  ota_wifi_setup(true);
}

void ota_wifi_setup(bool displayed) {
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    tft.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setPassword("admin");

  ArduinoOTA
    .onStart([]() {
      String type;
      digitalWrite(TFT_BL, HIGH);
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      tft.println("Start updating " + type);
      updaten = true;
      tft.fillScreen(kleur_zwart);
      bkos_logo(10, 10, kleur_donker);
      tft.setCursor(300, 10);
      tft.setTextSize(3);
      tft.setTextColor(kleur_groen);
      tft.println("BKOS update");
      // unsigned int lastProgress = 0;
      // unsigned int actProgress = 0;
  
    })
    .onEnd([]() {
      tft.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      // actProgress = "%u%%\r", (progress / (total / 100));
      if (true){//(actProgress != lastProgress) {
          tft.fillRect(300, 120, 200, 200, kleur_zwart);
          tft.setCursor(350, 125);
          tft.printf("%u%%\r", (progress / (total / 100)));
          // lastProgress = actProgress;
        }
    })
    .onError([](ota_error_t error) {
      tft.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  if (displayed) {
    tft.println("OTA Initialized");
    tft.print("IP address: ");
    tft.println(WiFi.localIP());
  }

}