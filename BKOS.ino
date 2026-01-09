// #if ORIENTATIE == 1
void BKOS_boot(){
  digitalWrite(TFT_BL, HIGH);
  delay(1000);
  bkos_logo(scherm_x(120) - 100, 10, kleur_donker);
  tft.setCursor(scherm_x(120) - 95, 95);
  tft.setTextSize(8);
  tft.setTextColor(kleur_licht);
  tft.println("BKos");
  tft.setTextSize(2);
  tft.setCursor(scherm_x(120) - 95, tft.getCursorY() + 5);
  tft.println("Boordcomputer OS");
  tft.setCursor(scherm_x(120) - 95, tft.getCursorY() + 5);
  tft.println("      door");
  tft.setCursor(scherm_x(120) - 95, tft.getCursorY() + 5);
  tft.println(" Brendan Koster");
  tft.setCursor(scherm_x(120) - 95, tft.getCursorY() + 5);
  tft.print("  versie ");
  tft.println(BKOS_VERSIE);
  tft.setCursor(scherm_x(120) - 95, tft.getCursorY() + 5);
  tft.println(MCU_TYPE);
  tft.setTextSize(1);
  tft.setTextColor(tft.color565(0, 0, 0));
  tft.setTextColor(tft.color565(255, 255, 255));
  if (ORIENTATIE == 1) {
    qr_bytes(137, 220, qr_brendanintechYT, 3, kleur_donker, kleur_licht);
  } else if (ORIENTATIE == 0) {
    qr_bytes(150, 10, qr_brendanintechYT, scherm_x(3), kleur_donker, kleur_licht);
  }

  tft.setTextColor(tft.color565(0, 0, 110));
  char c = ' ';
  while (Serial.available()) {
    c = Serial.read();
    // tft.print(c);
    if (!Serial.available()){
      delay(20);
    }
  }
  // tft.println("");
  if (RESOLUTIE == 4880) {
    tft.setCursor(0, 0);
  }
  tft.setTextColor(tft.color565(255, 255, 255));

  tft.print("  AT S?  ");
  Serial.println("AT S?");
  tft.setTextColor(tft.color565(0, 110, 0));
  unsigned int laatste = millis();
  while (c != '\n' && millis() < laatste + 5000) {
    if (Serial.available()){
      c = Serial.read();
      tft.print(c);
    }
  }
  if (c == '\n') {
    tft.println("");
  } else {
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.println("Helaas, niks gevonden");
  }
  tft.setTextColor(tft.color565(255, 255, 255));

  io_boot();
  io_set_defaults();
  // qr(120, 200, "brendanintech", 2)//, kleur_donker, kleur_licht);
  // qr(120, 200, "http://www.youtube.com/@brendanintech", 2, kleur_donker, kleur_licht);
  tft.println("");
  // io_detect();
  // sd_lees();
  delay(1000); // Kleine vertraging waarin het opstartschemr blijft staan, wel zo mooi
  ts_setup();
}
// #elif ORIENTATIE == 0
//   void BKOS_boot(){
//     digitalWrite(TFT_BL, HIGH);
//     delay(1000);
//     bkos_logo(20, 10, kleur_donker);
//     tft.setCursor(25, 95);
//     tft.setTextSize(8);
//     tft.setTextColor(kleur_licht);
//     tft.println("BKos");
//     tft.setTextSize(2);
//     tft.println("  Boordcomputer OS");
//     tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
//     tft.println("        door");
//     tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
//     tft.println("   Brendan Koster");
//     tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
//     tft.print("  versie ");
//     tft.println(BKOS_VERSIE);
//     tft.setCursor(tft.getCursorX()+25, tft.getCursorY()+5);
//     tft.println(MCU_TYPE);
//     // tft.setTextSize(1);
//     // tft.setTextColor(tft.color565(0, 0, 0));
//     tft.setTextColor(tft.color565(255, 255, 255));
//     qr_bytes(150, 10, qr_brendanintechYT, scherm_x(3), kleur_donker, kleur_licht);
//     // qr(120, 200, "brendanintech", 2)//, kleur_donker, kleur_licht);
//     // qr(120, 200, "http://www.youtube.com/@brendanintech", 2, kleur_donker, kleur_licht);
//     tft.println("");
//     io_detect();
//     delay(5000);
//   }
// #endif