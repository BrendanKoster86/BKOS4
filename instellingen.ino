void instellingen(String actie) {
  if (actie == "bouw") {
    bouw_instellingen();
  } else if (actie == "run") {
    run_instellingen();
  } else if (actie == "naam") {
    item_naam = "Instellingen";
  } else if (actie == "print") {
    instellingen("naam");
    tft.print(item_naam);
  } else if (actie == "icon_klein") {
    int x = getCursorX() + 20;
    int y = getCursorY() + 25;
    setCursor(getCursorX(), getCursorY()+4);
    drawIcon10x10(x, y, icon_instellingen, kleur_donker, 3);
    tft.setTextColor(kleur_rood);
  }
}

void bouw_instellingen() {

  bouw_instellingen(false);

}

void bouw_instellingen(bool overlay) {

  delete[]knoppen_teken_positie;
  delete[]knoppen_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst_kleur;
  
  
  aantal_knoppen = instellingen_mean_knoppen_cnt;
  knoppen_teken_positie = new int*[instellingen_mean_knoppen_cnt];
  knoppen_positie = new int*[instellingen_mean_knoppen_cnt];
  knoppen_basiskleur = new uint16_t*[instellingen_mean_knoppen_cnt];
  knoppen_tekst = new char*[instellingen_mean_knoppen_cnt];
  knoppen_tekst_kleur = new uint16_t*[instellingen_mean_knoppen_cnt];
  knoppen_status = instellingen_main_status;
  
  for (int i=0 ; i<instellingen_mean_knoppen_cnt ; i++) {
    knoppen_teken_positie[i] = instellingen_mean_knoppen_positie[i];
    knoppen_positie[i] = instellingen_mean_knoppen_positie[i];
    knoppen_basiskleur[i] = instellingen_mean_knoppen_kleur[i];
    knoppen_tekst[i] = instellingen_mean_knoppen_tekst[i];
    knoppen_tekst_kleur[i] = instellingen_mean_knoppen_tekstkleur[i];
    
  }
  
  header_plaatsen("Instellingen");
  if (overlay) {
    overligger(kleur_zwart, instellingen_overlay_hoogte, instellingen_overlay_dicht_tot);
  } else {
    achtergrond(kleur_zwart, true);
  }

  drawIconWifi10x10(10, 34);
  tft.setTextColor(kleur_wit);
  tft.setTextSize(1);
  tft.setCursor(25, 35);
  if (wifi__aangesloten) {
    if (wifi__verbonden) {
      // tft.print(wifi__ssid + "  -  " + wifi__ip);
    } else {
      tft.print("WiFi niet verbonden");
    }
  } else {
    tft.print("Wifi adapter niet aangesloten");
  }

  alle_knoppen_plaatsen();

  // // bouw_io_instellingen(0);
  // header_plaatsen("Instellingen");
  // achtergrond(tft.color565(0, 0, 0), false);
  // center_tekst(120, 100, "Nog niet gemaakt", 2, tft.color565(255, 255, 255));
  // center_tekst(120, 150, "Tik om terug te gaan", 1, tft.color565(255, 255, 255));
}


void instellingen_restart() {
  beeld_vraag("Helaas","De reset functie werkt nog niet", "ok");
  scherm_bouwen=true;
}

void instellingen_sd_reset() {
  
  byte druk;

  if (false) { //(info_snaam.length() > 2) {
    druk = beeld_vraag("SD kaart kopie", "Wilt u een kopie maken van de SD?", "JA", "NEE");
    if (druk == 0){
      beeld_melding("SD kopie maken", "Even geduld a.u.b.  . . .");

      delay(1000);
      // sd_maken();
      delay(1000);
    }
  } else {
    druk = beeld_vraag("schone SD", "Wilt u SD kaart inrichten?", "JA", "NEE");
    if (druk == 0){
      beeld_melding("schone SD", "Even geduld a.u.b.  . . .");

      delay(1000);
      // blanco_sd_maken();
      delay(1000);
    }
  }

  scherm_bouwen = true;

}

void instellingen_leven() {
  // beeld_vraag("Volgende update:", tijd_tot_millis(timer_statusupdate), "ok");
  scherm_bouwen = true;
}

void run_instellingen() {
  int druk;
  if (ts_touched()) {
    int x = touch_x();
    int y = touch_y();

    druk = klik(x, y);

    while (ts_touched()) {
      ts.begin();
    }

    ts.begin();

    if (druk > -1) {
      instellingen_mean_knoppen_functies[druk]();
    }

    if (y > home_knop[1]) {
      if (actieve_app == 9) {
        actieve_app = 0;
      }
      scherm_bouwen = true;
    }
  }
  ts.begin(); 
}

void loop_instellingen() {
  
  while (! scherm_bouwen) {
    if (scherm_actief) {
      if ((millis() > h_klok_millis + 20000) || (millis() < h_klok_millis)) {
        klok_update();
      }
    }

    io();
    ts.begin();
    run_instellingen();
  }
}