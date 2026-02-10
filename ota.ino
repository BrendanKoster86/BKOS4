void ota_setup(){
  ota_setup(false);
}

void ota_setup(bool displayed){
  connectToWiFi(displayed);
  ota_git_update();
  ArduinoOTA.setHostname("BKOS4");
  ota_wifi_setup(displayed);
}

void connectToWiFi(){
  connectToWiFi(false);
}

void connectToWiFi(bool displayed) {
  
  WiFi.mode(WIFI_STA);
  
  if (WiFi.status() != WL_CONNECTED) {
    uint16_t limiet = millis()+5000;
    WiFi.begin();
    while ((WiFi.status() != WL_CONNECTED) && (millis() < limiet)) {
      delay(500);
    }
  }

  // WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    if (displayed){
      tft.print(".");
    }
  }
  wifi__verbonden = true;
  // tft.println("\nWiFi connected");
  // tft.println("IP address: " + WiFi.localIP().toString());
}

void disconnectWiFi() {
  WiFi.disconnect();
  wifi__verbonden = false;
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    wifi__verbonden = false;
  } else {
    wifi__verbonden = true;
  }
}