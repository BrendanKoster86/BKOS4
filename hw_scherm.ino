void tft_begin(){
  tft.begin();
}

void tft_setup(){
  // SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  pinMode(TFT_BL, OUTPUT);
  tft_begin();
  tft.setRotation(ROTATIE);
  
  digitalWrite(TFT_BL, HIGH);
  delay(50);
}

