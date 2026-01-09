


// // Current firmware version
// const unsigned long updateCheckInterval = 5 * 60 * 1000;  // 5 minutes in milliseconds
// unsigned long lastUpdateCheck = 0;

void ota_git_update() {
  tft.println("\nStarting ESP32 OTA Update");

  connectToWiFi();
  delay(1000);
  tft.println("Device is ready.");
  tft.println("Current Firmware Version: " + String(BKOS_VERSIE));
  if (checkForFirmwareUpdate()) {
    tft.setCursor(0, 0);
    tft.println("BKOS update beschikbaar");
    tft.print("  ");
    tft.print(BKOS_VERSIE);
    tft.print(" > ");
    tft.println(BKOS_VERSIE_GIT);
    delay(5000);
    downloadAndApplyFirmware();
  } else {
    tft.setCursor(0, 0);
    tft.println("Gevonden op github:");
    tft.println(BKOS_VERSIE_GIT);
    delay(5000);
  }
}

// void loop() {
//   tft.println("Current Firmware Version: " + String(BKOS_VERSIE));
//   delay(3000);  // delay to prevent flooding serial
// }



bool checkForFirmwareUpdate() {
  tft.println("Checking for firmware update...");
  if (WiFi.status() != WL_CONNECTED) {
    tft.println("WiFi not connected");
    return false;
  }

  // Step 1: Fetch the latest version from GitHub
  BKOS_VERSIE_GIT = fetchLatestVersion();
  tft.setTextColor(tft.color565(255, 0, 0));
  tft.print("\n");
  tft.println(BKOS_VERSIE_GIT);
  tft.setTextColor(tft.color565(255, 255, 255));
  delay(5000);
  if (BKOS_VERSIE_GIT == "") {
    return false;
  }

  // Step 2: Compare versions
  if (BKOS_VERSIE_GIT != BKOS_VERSIE) {
    tft.print(BKOS_VERSIE_GIT);
    return true;
    // tft.println("New firmware available. Starting OTA update...");
    // downloadAndApplyFirmware();
  }
  return false;
}

String fetchLatestVersion() {
  HTTPClient http;
  http.begin(versionUrl);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String latestVersion = http.getString();
    tft.setCursor(0,0);
    tft.println(latestVersion);
    delay(2500);
    latestVersion.trim();  // Remove any extra whitespace
    http.end();
    return latestVersion;
  } else {
    tft.printf("Failed to fetch version. HTTP code: %d\n", httpCode);
    http.end();
    return "";
  }
}

void downloadAndApplyFirmware() {
  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(firmwareUrl);

  int httpCode = http.GET();
  tft.printf("HTTP GET code: %d\n", httpCode);

  if (httpCode == HTTP_CODE_OK) {
    int contentLength = http.getSize();
    tft.printf("Firmware size: %d bytes\n", contentLength);

    if (contentLength > 0) {
      WiFiClient* stream = http.getStreamPtr();
      if (startOTAUpdate(stream, contentLength)) {
        tft.println("OTA update successful, restarting...");
        delay(2000);
        ESP.restart();
      } else {
        tft.println("OTA update failed");
      }
    } else {
      tft.println("Invalid firmware size");
    }
  } else {
    tft.printf("Failed to fetch firmware. HTTP code: %d\n", httpCode);
  }
  http.end();
}


bool startOTAUpdate(WiFiClient* client, int contentLength) {
  tft.println("Initializing update...");
  if (!Update.begin(contentLength)) {
    tft.printf("Update begin failed: %s\n", Update.errorString());
    return false;
  }

  tft.println("Writing firmware...");
  size_t written = 0;
  int progress = 0;
  int lastProgress = 0;

  // Timeout variables
  const unsigned long timeoutDuration = 120*1000;  // 10 seconds timeout
  unsigned long lastDataTime = millis();

  while (written < contentLength) {
    if (client->available()) {
      uint8_t buffer[128];
      size_t len = client->read(buffer, sizeof(buffer));
      if (len > 0) {
        Update.write(buffer, len);
        written += len;

        // Calculate and print progress
        progress = (written * 100) / contentLength;
        if (progress != lastProgress) {
          tft.printf("Writing Progress: %d%%\n", progress);
          lastProgress = progress;
        }
      }
    }
    // Check for timeout
    if (millis() - lastDataTime > timeoutDuration) {
      tft.println("Timeout: No data received for too long. Aborting update...");
      Update.abort();
      return false;
    }

    yield();
  }
  tft.println("\nWriting complete");

  if (written != contentLength) {
    tft.printf("Error: Write incomplete. Expected %d but got %d bytes\n", contentLength, written);
    Update.abort();
    return false;
  }

  if (!Update.end()) {
    tft.printf("Error: Update end failed: %s\n", Update.errorString());
    return false;
  }

  tft.println("Update successfully completed");
  return true;
}