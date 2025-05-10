void spellen(String actie) {
  if (actief_spel == 0) {
    if (actie == "naam") {
      item_naam = "Spellen";
    } else if (actie == "print") {
      spellen("naam");
      tft.print(item_naam);
    } else if (actie == "icon_klein") {
      int x = getCursorX();
      int y = getCursorY();
      // tft.fillRect(x+2, y+2, 61, 45, kleur_oranje);
      drawLine(x+10, y+10, x+10, y+37, kleur_zwart);
      drawLine(x+10, y+10, x+33, y+3, kleur_zwart);
      drawLine(x+56, y+10, x+33, y+3, kleur_zwart);
      drawLine(x+56, y+10, x+56, y+37, kleur_zwart);
      drawLine(x+33, y+50, x+56, y+37, kleur_zwart);
      drawLine(x+33, y+50, x+10, y+37, kleur_zwart);
      drawLine(x+33, y+50, x+33, y+17, kleur_zwart);
      drawLine(x+10, y+10, x+33, y+17, kleur_zwart);
      drawLine(x+56, y+10, x+33, y+17, kleur_zwart);
      // 1 (top)
      fillCircle(x+33, y+10, 1, kleur_zwart);
      // 5 (rechts)
      fillCircle(x+45, y+29, 1, kleur_zwart);
      fillCircle(x+51, y+19, 1, kleur_zwart);
      fillCircle(x+51, y+34, 1, kleur_zwart);
      fillCircle(x+39, y+40, 1, kleur_zwart);
      fillCircle(x+39, y+23, 1, kleur_zwart);
      // 3 links
      fillCircle(x+21, y+28, 1, kleur_zwart);
      fillCircle(x+27, y+22, 1, kleur_zwart);
      fillCircle(x+15, y+34, 1, kleur_zwart);

      setCursor(x+3, y+52);
    } else {
      if (actie == "bouw") {
        homeknop_actief = false;
        homeknop_half_actief = false;
        slepen_toestaan = false;
      }
      spellen_bibliotheek[actief_spel](actie);
    }

  } else {
    if (actie == "bouw") {
      if (actief_spel == 0) {
        homeknop_actief = false;
        homeknop_half_actief = false;
        slepen_toestaan = false;
      } else {
        homeknop_actief = false;
        homeknop_half_actief = true;
      }
    }
    spellen_bibliotheek[actief_spel](actie);
    if (actie == "bouw") {
      if (homeknop_half_actief) {
        halve_2eknop_plaatsen("Spellen");
      }
    } else if ((actie == "run") and (actieve_touch) and (ts_y >= home_knop[1]) & (ts_x > (home_knop[2] / 2))) {
      actief_spel = 0;
      scherm_bouwen = true;
    }
  }
}

void spel_menu(String actie){
  if (actie == "bouw") {
    achtergrond(kleur_oranje);
    alle_spel_knoppen_plaatsen();
  } else if (actie == "run") {
    if (actieve_touch) {

      int druk = klik_spel(ts_x, ts_y);

      if ((druk > -1) & (druk < app_cnt)) {
        actief_spel = druk + 1;
        scherm_bouwen = true;
      }
    }
  }
}

int klik_spel(int x, int y) {
  if (spellen_cnt < 6) {
    for (byte i = 0; i < spellen_cnt -1; i++) {
      if ((x >= keuzescherm_knoppen_4[i][0]) && (x <= keuzescherm_knoppen_4[i][0]+keuzescherm_knoppen_4[i][2]) && (y >= keuzescherm_knoppen_4[i][1]) && (y <= keuzescherm_knoppen_4[i][1]+keuzescherm_knoppen_4[i][3])) {
        return i;
      }
    }
  } else if (spellen_cnt < 8) {
    for (byte i = 0; i < spellen_cnt -1; i++) {
      if ((x >= keuzescherm_knoppen_6[i][0]) && (x <= keuzescherm_knoppen_6[i][0]+keuzescherm_knoppen_6[i][2]) && (y >= keuzescherm_knoppen_6[i][1]) && (y <= keuzescherm_knoppen_6[i][1]+keuzescherm_knoppen_6[i][3])) {
        return i;
      }
    }
  } else {
    for (byte i = 0; i < spellen_cnt -1; i++) {
      if ((x >= keuzescherm_knoppen_8[i][0]) && (x <= keuzescherm_knoppen_8[i][0]+keuzescherm_knoppen_8[i][2]) && (y >= keuzescherm_knoppen_8[i][1]) && (y <= keuzescherm_knoppen_8[i][1]+keuzescherm_knoppen_8[i][3])) {
        return i;
      }
    }
  }
  return -1;
}


void spel_knop_plaatsen(int model, int knop_nummer){
  if (model == 8) {
    fillRoundRect(keuzescherm_knoppen_8[knop_nummer][0], keuzescherm_knoppen_8[knop_nummer][1], keuzescherm_knoppen_8[knop_nummer][2], keuzescherm_knoppen_8[knop_nummer][3], 5, kleur_licht);
    tft.setTextSize(1.5);
    tft.setTextColor(kleur_donker);
    setCursor(keuzescherm_knoppen_8[knop_nummer][0], keuzescherm_knoppen_8[knop_nummer][1]);
    if (knop_nummer <= 1) {
      spellen_bibliotheek[knop_nummer+1]("icon_groot");
    } else {
      spellen_bibliotheek[knop_nummer+1]("icon_klein");
    }
  } else if (model == 6) {
    fillRoundRect(keuzescherm_knoppen_6[knop_nummer][0], keuzescherm_knoppen_6[knop_nummer][1], keuzescherm_knoppen_6[knop_nummer][2], keuzescherm_knoppen_6[knop_nummer][3], 5, kleur_licht);
    tft.setTextSize(1.5);
    tft.setTextColor(kleur_donker);
    setCursor(keuzescherm_knoppen_6[knop_nummer][0], keuzescherm_knoppen_6[knop_nummer][1]);
    if (knop_nummer <= 1) {
      spellen_bibliotheek[knop_nummer+1]("icon_groot");
    } else {
      spellen_bibliotheek[knop_nummer+1]("icon_middel");
    }
  } else if (model == 4) {
    fillRoundRect(keuzescherm_knoppen_4[knop_nummer][0], keuzescherm_knoppen_4[knop_nummer][1], keuzescherm_knoppen_4[knop_nummer][2], keuzescherm_knoppen_4[knop_nummer][3], 5, kleur_licht);
    tft.setTextSize(1.5);
    tft.setTextColor(kleur_donker);
    setCursor(keuzescherm_knoppen_4[knop_nummer][0], keuzescherm_knoppen_4[knop_nummer][1]);
    spellen_bibliotheek[knop_nummer+1]("icon_groot");
  }
  spellen_bibliotheek[knop_nummer+1]("print");
}


void alle_spel_knoppen_plaatsen(){
  int model;
  if (spellen_cnt <= 5) {
    model = 4;
  } else if (spellen_cnt <= 7) {
    model = 6;
  } else {
    model = 8;
  }

  for (byte i = 0; i < spellen_cnt-1; i++) {
    spel_knop_plaatsen(model, i);
  }
}