void ota_wifi_update() {
  ArduinoOTA.handle();
}


void ota_wifi_setup() {
  
  // // Configure the hostname
  // uint16_t maxlen = strlen("nameprefix") + 7;
  // char *fullhostname = new char[maxlen];
  // uint8_t mac[6];
  // WiFi.macAddress(mac);
  // snprintf(fullhostname, maxlen, "%s-%02x%02x%02x", "nameprefix", mac[3], mac[4], mac[5]);
  // ArduinoOTA.setHostname("fullhostname");
  // delete[] fullhostname;

  

  // connectToWiFi();

  // // Configure and start the WiFi station
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    tft.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // // Port defaults to 3232
  // // ArduinoOTA.setPort(3232); // Use 8266 port if you are working in Sloeber IDE, it is fixed there and not adjustable

  // // No authentication by default
  ArduinoOTA.setPassword("admin");

  // // Password can be set with it's md5 value as well
  // // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

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

  tft.println("OTA Initialized");
  tft.print("IP address: ");
  tft.println(WiFi.localIP());

}