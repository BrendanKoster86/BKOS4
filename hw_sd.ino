#if HARDWARE == 2
  #if RESOLUTIE == 2432
    bool sd_begin(){
      return SD.begin();
      // return SD.begin(SS, spi_sd);
    }
    void sd_setup(){
      sd_begin();
      // spi_sd.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    }
  #else
    bool sd_begin(){
      return SD.begin(SD_CS);
    }
    void sd_setup(){
      sd_begin();
    }
  #endif
#else
  bool sd_begin(){
    return SD.begin(SD_CS);
  }
  void sd_setup(){
    sd_begin();
  }
#endif 