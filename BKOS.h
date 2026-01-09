#include <string.h>
#include <EEPROM.h>
#include "io.h"
#include "KNOPPEN.h"
#include "BKOS_kleuren.h"
#include "BKOS_logo.h"
#include "BKOS_header.h"
#include "instellingen.h"
#include "apps.h"
#include "info.h"
#include "ota.h"

#define BKOS_VERSIE "4.T260107"

void BKOS_boot();

unsigned int klok_getekend = 0;

#if HARDWARE == 5

#else
  const char* firmwareUrl = "https://github.com/ittipu/esp32_firmware/releases/download/esp32_firmware/firmware.ino.bin";
  const char* versionUrl = "https://raw.githubusercontent.com/ittipu/esp32_firmware/refs/heads/main/version.txt";
#endif
