void ota_setup(){
  connectToWiFi();
  ota_git_update();
  ArduinoOTA.setHostname("BKOS4");
  ota_wifi_setup();
}

void connectToWiFi() {
  tft.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    tft.print(".");
  }
  tft.println("\nWiFi connected");
  tft.println("IP address: " + WiFi.localIP().toString());
}