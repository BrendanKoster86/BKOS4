#if ORIENTATIE == 1
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
    qr_bytes(137, 220, qr_brendanintechYT, 3, kleur_donker, kleur_licht);
    // qr(120, 200, "brendanintech", 2)//, kleur_donker, kleur_licht);
    // qr(120, 200, "http://www.youtube.com/@brendanintech", 2, kleur_donker, kleur_licht);
    tft.println("");
    io_detect();
    delay(5000);
  }
#elif ORIENTATIE == 0
  void BKOS_boot(){
    digitalWrite(TFT_BL, HIGH);
    delay(1000);
    bkos_logo(20, 10, kleur_donker);
    tft.setCursor(25, 95);
    tft.setTextSize(8);
    tft.setTextColor(kleur_licht);
    tft.println("BKos");
    tft.setTextSize(2);
    tft.println("  Boordcomputer OS");
    tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
    tft.println("        door");
    tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
    tft.println("   Brendan Koster");
    tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
    tft.print("  versie ");
    tft.println(BKOS_VERSIE);
    tft.setCursor(tft.getCursorX()+25, tft.getCursorY()+5);
    tft.println(MCU_TYPE);
    // tft.setTextSize(1);
    // tft.setTextColor(tft.color565(0, 0, 0));
    tft.setTextColor(tft.color565(255, 255, 255));
    qr_bytes(150, 10, qr_brendanintechYT, scherm_x(3), kleur_donker, kleur_licht);
    // qr(120, 200, "brendanintech", 2)//, kleur_donker, kleur_licht);
    // qr(120, 200, "http://www.youtube.com/@brendanintech", 2, kleur_donker, kleur_licht);
    tft.println("");
    io_detect();
    delay(5000);
  }
#endif