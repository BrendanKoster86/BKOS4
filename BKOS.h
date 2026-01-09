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
  const char* firmwareUrl = "https://github.com/BrendanKoster86/BKOS4/blob/main/build/esp32.esp32.esp32s3/BKOS4.ino.bin";
  const char* versionUrl = "https://raw.githubusercontent.com/BrendanKoster86/BKOS4/blob/main/firmware/versie5.txt";
#else
  const char* firmwareUrl = "https://github.com/BrendanKoster86/BKOS4/blob/main/firmware/firmware.ino.bin";
  const char* versionUrl = "https://raw.githubusercontent.com/BrendanKoster86/BKOS4/blob/main/firmware/versie.txt";
#endif