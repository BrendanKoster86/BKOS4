#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

void ota_git_update();
bool checkForFirmwareUpdate();
void downloadAndApplyFirmware();

String BKOS_VERSIE_GIT = "";