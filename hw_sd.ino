#if HARDWARE == 2
  #if RESOLUTIE == 2432
    bool sd_begin(){
      // return SD.begin();
      // return SD.begin(SD_CS, spi_sd, 80000000);
    }
    void sd_setup(){
      // pinMode(SD_CS, OUTPUT);
      // spi_sd.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
      // sd_begin();
    }
  #else
    bool sd_begin(){
      // return SD.begin(SD_CS);
    }
    void sd_setup(){
      // sd_begin();
    }
  #endif
#else
  bool sd_begin(){
    return SD.begin(SD_CS);
  }
  void sd_setup(){
    // sd_begin();
  }
#endif 

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    // Serial.printf("Listing directory: %s\n", dirname);

    // File root = fs.open(dirname);
    // if(!root){
    //     Serial.println("Failed to open directory");
    //     return;
    // }
    // if(!root.isDirectory()){
    //     Serial.println("Not a directory");
    //     return;
    // }

    // File file = root.openNextFile();
    // while(file){
    //     if(file.isDirectory()){
    //         Serial.print("  DIR : ");
    //         Serial.println(file.name());
    //         if(levels){
    //             listDir(fs, file.path(), levels -1);
    //         }
    //     } else {
    //         Serial.print("  FILE: ");
    //         Serial.print(file.name());
    //         Serial.print("  SIZE: ");
    //         Serial.println(file.size());
    //     }
    //     file = root.openNextFile();
    // }
}

void readFile(fs::FS &fs, const char * path){
    // Serial.printf("Reading file: %s\n", path);

    // File file = fs.open(path);
    // if(!file){
    //     Serial.println("Failed to open file for reading");
    //     return;
    // }

    // Serial.print("Read from file: ");
    // while(file.available()){
    //     Serial.write(file.read());
    // }
    // file.close();
}

void sd_lees() {
  // sd_setup();
  // Serial.println("TESTEN SD functionaliteit");
  // // if (!sd_begin()){
  // //   Serial.println("Geen SD kaart gevonden");
  // //   return;
  // // }
  // // uint8_t cardType = SD.cardType();
  // // Serial.println(cardType);
  // // if(cardType == CARD_MMC){
  // //     Serial.println("MMC");
  // // } else if(cardType == CARD_SD){
  // //     Serial.println("SDSC");
  // // } else if(cardType == CARD_SDHC){
  // //     Serial.println("SDHC");
  // // } else {
  // //     Serial.println("UNKNOWN");
  // // }

  // // uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  // // Serial.printf("SD Card Size: %lluMB\n", cardSize);

  // // listDir(SD, "/", 0);
  // // listDir(SD, "/BKOS", 0);
  // readFile(SD, "/BKOS/io.cfg");

  // SD.end();
  // digitalWrite(SD_CS, HIGH);

  // ts_begin();
}