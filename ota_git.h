void ota_git_update();
// void ota_git_update(bool displayed);
bool checkForFirmwareUpdate();
// bool checkForFirmwareUpdate(bool displayed);
void downloadAndApplyFirmware();
void downloadAndApplyFirmware(byte BKOS);

String BKOS_VERSIE_GIT = "";
String BKOS_GIT_ALLOWED = "";
bool update_ready;


