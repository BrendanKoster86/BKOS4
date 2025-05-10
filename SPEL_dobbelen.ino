void spel_dobbelen(String actie) {
  if (actie == "bouw") {
    homeknop_actief = false;
    homeknop_half_actief = false;
    slepen_toestaan = false;
    bouw_dobbelsteen();
  } else if (actie == "run") {
    if (speel_yahtzee) {
      run_yahtzee();
    } else {
      dobbelsteen_werken();
    }
  } if (actie == "naam") {
    item_naam = "Dobbelen";
  } else if (actie == "print") {
    spel_dobbelen("naam");
    tft.print(item_naam);
  } else if (actie == "icon_groot") {
    int x = getCursorX();
    int y = getCursorY();
    dobbel_ogen(x + 7, y + 7, 90, 90, 5, 0);
    setCursor(x + 10, y + 105);
  }
}

void bouw_dobbelsteen() {
  worp = 0;
  spel_scherm = 0;
  //fillScreen(tft.color565(0, 0, 0));
  // fillRect(0, 0, 240, home_knop[1], tft.color565(0, 0, 0)); 
  achtergrond(kleur_zwart);
  header_plaatsen();
  tft.setTextColor(kleur_donker);
  for (byte i = 0; i < 6; i++) {
    if (i == 5) {
      fillRect(dobbel_knoppen[i][0], dobbel_knoppen[i][1], dobbel_knoppen[i][2], dobbel_knoppen[i][3], kleur_wit);
      center_tekst(dobbel_knoppen[i][0] + dobbel_knoppen[i][2] / 2, dobbel_knoppen[i][1] + dobbel_knoppen[i][3] / 3, "Yahtzee", 3, kleur_zwart);
    } else {
      dobbel_ogen(dobbel_knoppen[i][0], dobbel_knoppen[i][1], dobbel_knoppen[i][2], dobbel_knoppen[i][3], i+1, 0);
    // fillRect(dobbel_knoppen[i][0], dobbel_knoppen[i][1], dobbel_knoppen[i][2], dobbel_knoppen[i][3], kleur_wit);
    // setCursor(dobbel_knoppen[i][0]+10, dobbel_knoppen[i][1]+10);
    // tft.println(i+1);
    }
  }
  ts_begin();
  // Keuze maken in het aantal dobbel stenen
  bool keuze = false;
  int x = 0;
  int y = 0;
  while ((not keuze) && (y < home_knop[1])) {
    ts_begin();
    if (ts_touched()) {
      x = touch_x();
      y = touch_y();
      for (byte i = 0; i < 6; i++) {
        if (((x >= dobbel_knoppen[i][0]-5) && (x <= dobbel_knoppen[i][0]+dobbel_knoppen[i][2]+5)) && ((y >= dobbel_knoppen[i][1]-5) && (y <= dobbel_knoppen[i][1]+dobbel_knoppen[i][3]+5))) {
          dobbelstenen = i;
          fillRect(dobbel_knoppen[i][0], dobbel_knoppen[i][1], dobbel_knoppen[i][2], dobbel_knoppen[i][3], tft.color565(120, 120, 120));
          keuze = true;
        }
      }
      while (ts_touched()) {
        delay(50);
        ts_begin();
      }
      scherm_touched = millis();
    }
    
    io();
  }
  if (dobbelstenen == 5) {
    achtergrond(kleur_zwart);
    header_plaatsen("Yahtzee");
    // fillRect(0,0,240, home_knop[1], tft.color565(0, 0, 0));
    for (byte i = 0; i < 5; i++) {
      fillRect(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1], dobbel_stenen[4][i][2], dobbel_stenen[4][i][3], tft.color565(255,255,255));
      if ((i >= 3)) {
        fillEllipse_afgekapt(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 - 12, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3] + dobbel_stenen[4][i][3]/3, 8, dobbel_stenen[4][i][3], kleur_blauw, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-3);
        fillCircle(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 - 12, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]/3- 4, 7, kleur_blauw);
        fillEllipse_afgekapt(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 + 12, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3] + dobbel_stenen[4][i][3]/3, 8, dobbel_stenen[4][i][3], kleur_oranje, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-3);
        fillCircle(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 + 12, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]/3- 4, 7, kleur_oranje);
      }
      if ((i >= 1)) {
        fillEllipse_afgekapt(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 - 6, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3] + dobbel_stenen[4][i][3]/3, 8, dobbel_stenen[4][i][3], kleur_groen, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-3);
        fillCircle(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 - 6, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]/3- 4, 7, kleur_groen);
        fillEllipse_afgekapt(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 + 6, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3] + dobbel_stenen[4][i][3]/3, 8, dobbel_stenen[4][i][3], kleur_rood, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-3);
        fillCircle(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2 + 6, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]/3- 4, 7, kleur_rood);
      }
      if ((i == 0) || (i == 2) || (i == 4)) {
        fillEllipse_afgekapt(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3] + dobbel_stenen[4][i][3]/3, 8, dobbel_stenen[4][i][3], kleur_zwart, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-3);
        fillCircle(dobbel_stenen[4][i][0] + dobbel_stenen[4][i][2] / 2, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]/3- 4, 7, kleur_zwart);
      }
      fillRect(dobbel_stenen[4][i][0]-4, dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3], dobbel_stenen[4][i][2]+8, dobbel_stenen[4][i][3]*2, kleur_zwart);
      fillRect(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1] + dobbel_stenen[4][i][3]-2, dobbel_stenen[4][i][2], 2, kleur_wit);
    }
    for (byte i = 5; i < 9; i++) {
      dobbel_ogen(dobbel_stenen[8][i][0], dobbel_stenen[8][i][1], dobbel_stenen[8][i][2], dobbel_stenen[8][i][3], i+1, kleur_zwart, kleur_wit);
    }
    for (byte i = 9; i < 11; i++) {
      fillRect(dobbel_stenen[11][i][0], dobbel_stenen[11][i][1], dobbel_stenen[11][i][2], dobbel_stenen[11][i][3], kleur_wit);
      center_tekst(dobbel_stenen[11][i][0] + dobbel_stenen[11][i][2]/2, dobbel_stenen[11][i][1] + 10, String(i+1), 3, kleur_zwart);
    }

    setCursor(10, 180);
    tft.setTextSize(2);
    tft.setTextColor(kleur_wit);
    tft.print("Aantal spelers?");

    keuze = false;

    while ((not keuze) && (y < home_knop[1])) {
      delay(50);
      ts_begin();
      if (ts_touched()) {
        x = touch_x();
        y = touch_y();
        delay(50);
        ts_begin();
        while (ts_touched()) {
          delay(50);
          ts_begin();
        }
        for (byte i = 0; i <= 11; i++) {
          if (((x >= dobbel_stenen[11][i][0]-5) && (x <= dobbel_stenen[11][i][0]+dobbel_stenen[11][i][2]+5)) && ((y >= dobbel_stenen[11][i][1]-5) && (y <= dobbel_stenen[11][i][1]+dobbel_stenen[11][i][3]+5))) {
            speler_cnt = i;
            fillRect(dobbel_stenen[11][i][0], dobbel_stenen[11][i][1], dobbel_stenen[11][i][2], dobbel_stenen[11][i][3], tft.color565(120, 120, 120));
            keuze = true;
          }
        }
        if (keuze) {
          speel_yahtzee = true;
          speler_actief = 0;
          for (byte i = 0; i <= speler_cnt; i++) {
            for (byte j = 0; j < 19; j++) {
              yahtzee_scoreblad[i][j] = -1;
            }
            yahtzee_totaal_score[i] = 0;
          }
          
        }
        scherm_touched = millis();
      
      }
      io();
    }


    
  }else {
    speel_yahtzee = false;
    fillRect(0,0,240, home_knop[1], tft.color565(0, 0, 0));
    for (byte i = 0; i <= dobbelstenen; i++) {
      drawRect(dobbel_stenen[dobbelstenen][i][0], dobbel_stenen[dobbelstenen][i][1], dobbel_stenen[dobbelstenen][i][2], dobbel_stenen[dobbelstenen][i][3], tft.color565(255,255,255));
      dobbel_fix[i] = false;
    }
    drawRect(30, 85, 180, 40, tft.color565(255,255,255));
    setCursor(60, 95);
    tft.setTextColor(tft.color565(255, 255, 255));
    tft.println("Werpen");
    tft.setTextColor(tft.color565(0, 0, 0));
    ts_begin();
  }
  scherm_touched = millis();
}

void yahtzee_mogelijke_scoren_berekenen() {
  for (int i = 0; i<19; i++){
    pot_yahtzee_scoreblad[i] = 0;
  }
  bool bovenste = true;
  bool onderste = true;
  bool een = false;
  bool twee = false;
  bool drie = false;
  bool vier = false;
  bool vijf = false;
  bool full = false;
  bool klein1234 = true;
  bool klein2345 = true;
  bool klein3456 = true;
  bool groot12345 = true;
  bool groot23456 = true;
  for (int i = 0; i < 6; i++) {
    for (int d = 0; d<5; d++) {
      if (dobbel_resultaat[d] == i+1) {
        pot_yahtzee_scoreblad[i] = pot_yahtzee_scoreblad[i] + i+1;
      }
    }
    if (yahtzee_scoreblad[speler_actief][i] > 0) {
      pot_yahtzee_scoreblad[6] = pot_yahtzee_scoreblad[6] + yahtzee_scoreblad[speler_actief][i];
    } else {
      bovenste = false;
    }
    if (pot_yahtzee_scoreblad[i] == (i+1) * 5) {
      vijf = true;
    } else if (pot_yahtzee_scoreblad[i] == (i+1) * 4) {
      vier = true;
    } else if (pot_yahtzee_scoreblad[i] == (i+1) * 3) {
      drie = true;
    } else if (pot_yahtzee_scoreblad[i] == (i+1) * 2) {
      twee = true;
    } else if (pot_yahtzee_scoreblad[i] == (i+1) * 1) {
      een = true;
    } else if (i == 0) {
      klein1234 = false;
      groot12345 = false;
    } else if (i == 1) {
      klein1234 = false;
      klein2345 = false;
      groot12345 = false;
      groot23456 = false;
    } else if (i == 2) {
      klein1234 = false;
      klein2345 = false;
      klein3456 = false;
      groot12345 = false;
      groot23456 = false;
    } else if (i == 3) {
      klein1234 = false;
      klein2345 = false;
      klein3456 = false;
      groot12345 = false;
      groot23456 = false;
    } else if (i == 4) {
      klein2345 = false;
      klein3456 = false;
      groot12345 = false;
      groot23456 = false;
    } else if (i == 5) {
      klein3456 = false;
      groot23456 = false;
    }
  }

  for (int i = 9; i < 16; i++){
    if (yahtzee_scoreblad[speler_actief][i] >= 0) {
      pot_yahtzee_scoreblad[16] = pot_yahtzee_scoreblad[16] + yahtzee_scoreblad[speler_actief][i];
    } else {
      onderste = false;
    }
  }

  // kans score berekenen
  for (int d = 0; d<5; d++) {
    pot_yahtzee_scoreblad[15] = pot_yahtzee_scoreblad[15] + dobbel_resultaat[d];
  }

  if ((drie) & (twee)) {
    full = true;
    pot_yahtzee_scoreblad[11] = 25;
  }
  if (vijf) {
    vier = true;
    pot_yahtzee_scoreblad[14] = 50;
  }
  if (vier) {
    drie = true;
    pot_yahtzee_scoreblad[10] = pot_yahtzee_scoreblad[15];
  }
  if (drie) {
    pot_yahtzee_scoreblad[9] = pot_yahtzee_scoreblad[15];
  }

  if ((klein1234) || (klein2345) || (klein3456)) {
    pot_yahtzee_scoreblad[12] = 30;
  }
  if ((groot12345) || (groot23456)) {
    pot_yahtzee_scoreblad[13] = 40;
  }

  if (pot_yahtzee_scoreblad[6] >= 63) {
    pot_yahtzee_scoreblad[7] = 35;
  }
  pot_yahtzee_scoreblad[8] = pot_yahtzee_scoreblad[6] + pot_yahtzee_scoreblad[7];
  pot_yahtzee_scoreblad[17] = pot_yahtzee_scoreblad[8];
  pot_yahtzee_scoreblad[18] = pot_yahtzee_scoreblad[16] + pot_yahtzee_scoreblad[17];

  if ((yahtzee_scoreblad[speler_actief][6] == -1) && (bovenste)) {
    yahtzee_scoreblad[speler_actief][6] = pot_yahtzee_scoreblad[6];
    yahtzee_scoreblad[speler_actief][7] = pot_yahtzee_scoreblad[7];
    yahtzee_scoreblad[speler_actief][8] = pot_yahtzee_scoreblad[8];
    yahtzee_scoreblad[speler_actief][17] = pot_yahtzee_scoreblad[17];
  }
  if ((yahtzee_scoreblad[speler_actief][16] == -1) && (onderste)) {
    yahtzee_scoreblad[speler_actief][16] = pot_yahtzee_scoreblad[16];
  }
  if ((yahtzee_scoreblad[speler_actief][18] == -1) && (bovenste) && (onderste)) {
    yahtzee_scoreblad[speler_actief][18] = pot_yahtzee_scoreblad[18];
  }
}

void yahtzee_teken_scoreblad() {
  spel_scherm = 2;
  achtergrond(kleur_oranje);
  yahtzee_mogelijke_scoren_berekenen();
  tft.setTextSize(2);
  
  select_vak = -1;

  for (int i = 0; i < 5; i++) {
    if (dobbel_fix[i]) {
      dobbel_ogen(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1], dobbel_stenen[4][i][2], dobbel_stenen[4][i][3], dobbel_resultaat[i], 0);
    } else {
      dobbel_ogen(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1], dobbel_stenen[4][i][2], dobbel_stenen[4][i][3], dobbel_resultaat[i], 255);
    }
  }
  
  for (int i = 0; i < 7; i++) {
    if (i == 6) {
      drawRect(5, 75+i*vak_grootte, 60, vak_grootte, kleur_zwart);
      tft.setTextSize(1);
      setCursor(10, 75+i*vak_grootte + 4);
      tft.setTextColor(kleur_zwart);
      tft.print("SOM");
      tft.setTextSize(2);
    } else {
      dobbel_ogen(40, 75+i*vak_grootte, vak_grootte, vak_grootte, i+1, 0);
    }
    drawRect(65, 75+i*vak_grootte, 40, vak_grootte, kleur_zwart);
    if (yahtzee_scoreblad[speler_actief][i] == -1) {
      if (pot_yahtzee_scoreblad[i] >= 1) {
        tft.setTextColor(tft.color565(150, 150, 150));
        setCursor(75, 75+i*vak_grootte+2);
        tft.print(pot_yahtzee_scoreblad[i]);
      }
    } else if (yahtzee_scoreblad[speler_actief][i] == 0){
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(75, 75+i*vak_grootte+2);
      tft.print("-");
    } else{
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(75, 75+i*vak_grootte+2);
      tft.print(yahtzee_scoreblad[speler_actief][i]);
    }
  }

  for (int i = 7; i < 9; i++) {
    drawRect(5, 75+i*vak_grootte+3, 60, vak_grootte, kleur_zwart);
    tft.setTextSize(1);
    setCursor(10, 75+i*vak_grootte+3 + 4);
    tft.setTextColor(kleur_zwart);


    if (i == 7) {
      tft.print("BONUS");
    } else {
      tft.print("TOTAAL");
    }
    tft.setTextSize(2);
    drawRect(65, 75+i*vak_grootte+3, 40, vak_grootte, kleur_zwart);
    if (yahtzee_scoreblad[speler_actief][i] == -1) {
      if (pot_yahtzee_scoreblad[i] >= 1) {
        tft.setTextColor(tft.color565(150, 150, 150));
        setCursor(75, 75+i*vak_grootte+5);
        tft.print(pot_yahtzee_scoreblad[i]);
      }
    } else if (yahtzee_scoreblad[speler_actief][i] == 0){
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(75, 75+i*vak_grootte+5);
      tft.print("-");
    } else{
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(75, 75+i*vak_grootte+5);
      tft.print(yahtzee_scoreblad[speler_actief][i]);
    }
  }

  for (int i = 9; i < 18; i++) {
    drawRect(120, 75+(i - 9)*vak_grootte, 65, vak_grootte, kleur_zwart);
    tft.setTextSize(1);
    setCursor(125, 75+(i-9)*vak_grootte + 4);
    tft.setTextColor(kleur_zwart);
    if (i == 9) {
      tft.print("3 zelfde");
    } else if (i == 10) {
      tft.print("4 zelfde");
    } else if (i == 11) {
      tft.print("full house");
    } else if (i == 12) {
      tft.print("kleine str");
    } else if (i == 13) {
      tft.print("grote str");
    } else if (i == 14) {
      tft.print("YAHTZEE");
    } else if (i == 15) {
      tft.print("kans");
    } else if (i == 16) {
      tft.print("SOM");
    } else if (i == 17) {
      tft.print("boven");
    }
    tft.setTextSize(2);
    drawRect(185, 75+(i-9)*vak_grootte, 40, vak_grootte, kleur_zwart);
    if (yahtzee_scoreblad[speler_actief][i] == -1) {
      if (pot_yahtzee_scoreblad[i] >= 1) {
        tft.setTextColor(tft.color565(150, 150, 150));
        setCursor(190, 75+(i-9)*vak_grootte+5);
        tft.print(pot_yahtzee_scoreblad[i]);
      }
    } else if (yahtzee_scoreblad[speler_actief][i] == 0){
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(190, 75+(i-9)*vak_grootte+5);
      tft.print("-");
    } else{
      tft.setTextColor(tft.color565(0, 0, 0));
      setCursor(190, 75+(i-9)*vak_grootte+5);
      tft.print(yahtzee_scoreblad[speler_actief][i]);
    }
    
    
  }
  drawRect(120, 75+(18 - 9)*vak_grootte + 3, 65, vak_grootte, kleur_zwart);
  tft.setTextSize(1);
  setCursor(127, 75+(18-9)*vak_grootte + 5);
  tft.setTextColor(kleur_rood);
  tft.print("EINDTOTAAL");
  tft.setTextSize(2);
  drawRect(185, 75+9*vak_grootte+3, 40, vak_grootte, kleur_zwart);
  if (yahtzee_scoreblad[speler_actief][18] == -1) {
    if (pot_yahtzee_scoreblad[18] >= 1) {
      tft.setTextColor(kleur_passief_rood);
      setCursor(190, 75+(18-9)*vak_grootte+5);
      tft.print(pot_yahtzee_scoreblad[18]);
    }
  } else if (yahtzee_scoreblad[speler_actief][18] == 0){
    tft.setTextColor(kleur_actief_rood);
    setCursor(190, 75+(18-9)*vak_grootte+5);
    tft.print("-");
  } else {
    tft.setTextColor(kleur_actief_rood);
    setCursor(190, 75+(18-9)*vak_grootte+5);
    tft.print(yahtzee_scoreblad[speler_actief][18]);
  }

  fillRect(5, 265, 100, 40, tft.color565(200, 200, 200));
  drawRect(5, 265, 100, 40, tft.color565(100, 100, 100));
  tft.setTextColor(tft.color565(100, 100, 100));
  tft.setTextSize(2);
  setCursor(45, 277);
  tft.print("OK");

}

void yahtzee_run_score() {
  if (actieve_touch) {
    if ((ts_y > 30) && (ts_y < 70)) {
      yahtzee_teken_stenen();
    } else if (ts_x < 110) {
      for (int i = 0; i<6; i++) {
        if ((ts_y > 75 + i*vak_grootte) && (ts_y < 75 + (i+1) * vak_grootte)) {
          if (select_vak >= 0) {
            if (select_vak < 6) {
              fillRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_oranje);
              drawRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_zwart);
              tft.setTextColor(tft.color565(150, 150, 150));
              setCursor(75, 75+select_vak*vak_grootte+2);
              tft.setTextSize(2);
              if (pot_yahtzee_scoreblad[select_vak] > 0){
                tft.print(pot_yahtzee_scoreblad[select_vak]);
              }
            } else if (select_vak >= 9) {
              fillRect(185, 75+(select_vak - 9)*vak_grootte, 40, vak_grootte, kleur_oranje);
              drawRect(185, 75+(select_vak - 9)*vak_grootte, 40, vak_grootte, kleur_zwart);
              tft.setTextColor(tft.color565(150, 150, 150));
              setCursor(190, 75+(select_vak - 9)*vak_grootte+2);
              tft.setTextSize(2);
              if (pot_yahtzee_scoreblad[select_vak] > 0){
                tft.print(pot_yahtzee_scoreblad[select_vak]);
              }
            }
          
          }
          if (yahtzee_scoreblad[speler_actief][i] == -1) {
            select_vak = i;
            fillRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_zwart);
            drawRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_wit);
            tft.setTextColor(tft.color565(255, 255, 255));
            setCursor(75, 75+select_vak*vak_grootte+2);
            tft.setTextSize(2);
            tft.print(pot_yahtzee_scoreblad[select_vak]);   
          } else {
            select_vak = -1;
          }
        }
      }
    } else if (ts_x > 130) {
      for (int i = 0; i<7; i++) {
        if ((ts_y > 75 + i*vak_grootte) && (ts_y < 75 + (i+1) * vak_grootte)) {
          if (select_vak >= 0) {
            if (select_vak < 6) {
              fillRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_oranje);
              drawRect(65, 75+select_vak*vak_grootte, 40, vak_grootte, kleur_zwart);
              tft.setTextColor(tft.color565(150, 150, 150));
              setCursor(75, 75+select_vak*vak_grootte+2);
              tft.setTextSize(2);
              if (pot_yahtzee_scoreblad[select_vak] > 0){
                tft.print(pot_yahtzee_scoreblad[select_vak]);
              }      
            } else if (select_vak >= 9) {
              fillRect(185, 75+(select_vak - 9)*vak_grootte, 40, vak_grootte, kleur_oranje);
              drawRect(185, 75+(select_vak - 9)*vak_grootte, 40, vak_grootte, kleur_zwart);
              tft.setTextColor(tft.color565(150, 150, 150));
              setCursor(190, 75+(select_vak - 9)*vak_grootte+2);
              tft.setTextSize(2);
              if (pot_yahtzee_scoreblad[select_vak] > 0){
                tft.print(pot_yahtzee_scoreblad[select_vak]);
              }        
            }
          }
          if (yahtzee_scoreblad[speler_actief][i+9] == -1) {
            select_vak = i +9;
            fillRect(185, 75+i*vak_grootte, 40, vak_grootte, kleur_zwart);
            drawRect(185, 75+i*vak_grootte, 40, vak_grootte, kleur_wit);
            tft.setTextColor(tft.color565(255, 255, 255));
            setCursor(190, 75+i*vak_grootte+2);
            tft.setTextSize(2);
            tft.print(pot_yahtzee_scoreblad[select_vak]);   
          } else {
            select_vak = -1;
          }
        }
      }
    }

    if (select_vak == -1) {
      fillRect(5, 265, 100, 40, tft.color565(200, 200, 200));
      drawRect(5, 265, 100, 40, tft.color565(100, 100, 100));
      tft.setTextColor(tft.color565(100, 100, 100));
      tft.setTextSize(2);
      setCursor(45, 277);
      tft.print("OK");
    } else {
      fillRect(5, 265, 100, 40, kleur_actief_groen);
      drawRect(5, 265, 100, 40, kleur_passief_groen);
      tft.setTextColor(kleur_passief_groen);
      tft.setTextSize(2);
      setCursor(45, 277);
      tft.print("OK");
    }
    
    if ((ts_y > 240) && (ts_x < 120) && (select_vak >=0)){
      yahtzee_scoreblad[speler_actief][select_vak] = pot_yahtzee_scoreblad[select_vak];
      yahtzee_totaal_score[speler_actief] = 0;
      for (int i = 0; i < 6; i++) {
        if (yahtzee_scoreblad[speler_actief][i] >= 1) {
          yahtzee_totaal_score[speler_actief] = yahtzee_totaal_score[speler_actief] + yahtzee_scoreblad[speler_actief][i];
        }
      }
      if (yahtzee_totaal_score[speler_actief] >= 63) {
        yahtzee_totaal_score[speler_actief] = yahtzee_totaal_score[speler_actief] + 35;
      }
      for (int i = 9; i < 16; i++) {
        if (yahtzee_scoreblad[speler_actief][i] >= 1) {
          yahtzee_totaal_score[speler_actief] = yahtzee_totaal_score[speler_actief] + yahtzee_scoreblad[speler_actief][i];
        }
      }
      

      worp = 4;
      if (speler_actief == speler_cnt) {
        speler_actief = 0;
      } else {
        speler_actief++;
      }
      yahtzee_teken_stenen();
    }
  }
}


void yahtzee_teken_stenen() {
  // fillRect(0, 0, SX_MAX, home_knop[1], kleur_geel);
  achtergrond(kleur_geel);
  header_plaatsen("Yahtzee");
  if (worp == 4) {
    worp = 0;
  }
  if (worp == 0) {
    for (int i = 0; i < 5; i++) {
      dobbel_resultaat[i] = 0;
      dobbel_fix[i] = false;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (dobbel_fix[i]) {
      dobbel_ogen(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1], dobbel_stenen[4][i][2], dobbel_stenen[4][i][3], dobbel_resultaat[i], 0);
    } else {
      dobbel_ogen(dobbel_stenen[4][i][0], dobbel_stenen[4][i][1], dobbel_stenen[4][i][2], dobbel_stenen[4][i][3], dobbel_resultaat[i], 255);
    }
  }
  fillEllipse(20, 195, 8, 40, kleur_wit);
  fillCircle(20, 150, 7, kleur_wit);
  fillRect(5, 180, 60, 60, kleur_geel);
  setCursor(35, 150);
  if (RESOLUTIE == 2432) {
    tft.setTextSize(3);
  } else if (RESOLUTIE == 3248) {
    tft.setTextSize(4);
  } else if (RESOLUTIE == 4864) {
    tft.setTextSize(5);
  }
  tft.print(speler_actief + 1);
  dobbel_ogen(60, 145, 30, 30, 3 - worp, 255);
  fillRect(10, 85, 105, 40, kleur_zwart);
  drawRect(10, 85, 105, 40, kleur_wit);
  fillRect(125, 85, 105, 40, kleur_actief_groen);
  drawRect(125, 85, 105, 40, kleur_rood);
  setCursor(30, 95);
  tft.setTextColor(tft.color565(255, 255, 255));
  tft.println("Werp");
  setCursor(133, 95);
  tft.setTextColor(kleur_rood);
  tft.println("Score");
  if (RESOLUTIE == 2432) {
    tft.setTextSize(2);
  } else if (RESOLUTIE == 3248) {
    tft.setTextSize(3);
  } else if (RESOLUTIE == 4864) {
    tft.setTextSize(4);
  }
  tft.println();
  for (int i = 0; i <= speler_cnt; i++){
    if (i == speler_actief){
      tft.setTextColor(kleur_wit);
    } else {
      tft.setTextColor(tft.color565(120, 120, 120));
    }
    setCursor(120, getCursorY());
    tft.print(i + 1);
    tft.print(" : ");
    tft.println(yahtzee_totaal_score[i]);
  }
  tft.setTextColor(tft.color565(0, 0, 0));

  fillRect(10, 200, 50, 75, kleur_wit);
  drawRect(10, 200, 50, 75, kleur_zwart);
  drawLine(13, 220, 57, 220, kleur_zwart);
  drawLine(13, 230, 57, 230, kleur_zwart);
  drawLine(13, 240, 57, 240, kleur_zwart);
  drawLine(13, 250, 57, 250, kleur_zwart);
  drawLine(13, 260, 57, 260, kleur_zwart);


  spel_scherm = 1;
}

void run_yahtzee() {
  if (spel_scherm == 0) {
    yahtzee_teken_stenen();
  } else if (spel_scherm == 1) {
    yahtzee_run_scherm_1();
  } else if (spel_scherm == 2) {
    yahtzee_run_score();
  }

}

void yahtzee_schore_overzicht() {
  if (spel_scherm != 3) {
    spel_scherm = 3;
    vak_grootte = 15;
    int vak_breedte;
    if (speler_cnt < 5) {
      vak_breedte = 32;
    } else if (speler_cnt == 5) {
      vak_breedte = 29;
    } else if (speler_cnt == 6) {
      vak_breedte = 25;
    } else if (speler_cnt == 7) {
      vak_breedte = 22;
    } else if (speler_cnt == 8) {
      vak_breedte = 19;
    } else if (speler_cnt == 9) {
      vak_breedte = 18;
    } else if (speler_cnt == 10) {
      vak_breedte = 16;
    } else {
      vak_breedte = 15;
    }
    int tmp;
    header_plaatsen();
    achtergrond(kleur_licht);
    int y_plus = 28 + vak_grootte;
    int x_plus = 70;
    for (int s = 0; s <= speler_cnt; s++){
      fillRect(x_plus + s*(vak_breedte -1), y_plus - vak_grootte+1 , vak_breedte, vak_grootte, kleur_donker);
      drawRect(x_plus + s*(vak_breedte -1), y_plus - vak_grootte+1 , vak_breedte, vak_grootte, kleur_licht);
      // setCursor(x_plus + s*(vak_grootte -1)+2, y_plus - vak_grootte + 5 );
      // tft.setTextColor(kleur_licht);
      center_tekst(x_plus + s*(vak_breedte -1)+2 + vak_breedte/2, y_plus - vak_grootte + 5, String(s+1), 1, kleur_licht);
    }
    for (int i = 0; i < 19; i++) {
      if (i < 6) {
        dobbel_ogen(55, y_plus + i*(vak_grootte -1), vak_grootte, vak_grootte, i+1, kleur_licht, kleur_donker, 1);
      } else {
        if (i == 7) {
          y_plus++;
        } else if (i == 9) {
          y_plus = y_plus + 4;
        } else if (i == 16) {
          y_plus++;
        } else if (i == 18) {
          y_plus++;
        } 
        drawRect(5, y_plus + i*(vak_grootte -1), 65, vak_grootte, kleur_donker);
        setCursor(7, y_plus + i*(vak_grootte -1) + 2);
        tft.setTextColor(kleur_donker);
        tft.setTextSize(1);
        if (i == 6) {
          tft.print("SOM");
        } else if (i == 7) {
          tft.print("BONUS");
        } else if (i == 8) {
          tft.print("TOTAAL");
        } else if (i == 9) {
          tft.print("3 zelfde");
        } else if (i == 10) {
          tft.print("4 zelfde");
        } else if (i == 11) {
          tft.print("Full house");
        } else if (i == 12) {
          tft.print("kleine str");
        } else if (i == 13) {
          tft.print("grote str");
        } else if (i == 14) {
          tft.print("YAHTZEE");
        } else if (i == 15) {
          tft.print("kans");
        } else if (i == 16) {
          tft.print("SOM");
        } else if (i == 17) {
          tft.print("BOVEN");
        } else if (i == 18) {
          tft.print("TOTAAL");
        } 
      }
      for (int s = 0; s <= speler_cnt; s++) {
        drawRect(x_plus + s*(vak_breedte -1), y_plus + i*(vak_grootte -1), vak_breedte, vak_grootte, kleur_donker);
        setCursor(x_plus + s*(vak_breedte -1)+2, y_plus + i*(vak_grootte -1)+2);
        tft.setTextColor(kleur_donker);
        if (yahtzee_scoreblad[s][i] == 0) {
          tft.print("=");
        } else if (yahtzee_scoreblad[s][i] > 0) {
          tft.print(yahtzee_scoreblad[s][i]);
        } else if (i == 6) {
          tmp = 0;
          for (int t = 0; t < 6; t++) {
            if (yahtzee_scoreblad[s][t] > 0) {
              tmp = tmp + yahtzee_scoreblad[s][t];
            }
          }
          if (tmp > 1) {
            tft.setTextColor(tft.color565(150, 150, 150));
            tft.print(tmp);
            if (tmp >= 63) {
              drawRect(x_plus + s*(vak_breedte -1), y_plus + (i+1)*(vak_grootte -1), vak_breedte, vak_grootte, kleur_donker);
              setCursor(x_plus + s*(vak_breedte -1)+2, y_plus + (i+1)*(vak_grootte -1)+2);
              tft.print(35);
              drawRect(x_plus + s*(vak_breedte -1), y_plus + (i+2)*(vak_grootte -1)+2, vak_breedte, vak_grootte, kleur_donker);
              setCursor(x_plus + s*(vak_breedte -1)+2, y_plus + (i+2)*(vak_grootte -1)+4);
              tft.print(tmp+35);
            }
            tft.setTextColor(kleur_donker);
          }
        } else if (i == 16) {
          tmp = 0;
          for (int t = 9; t < 16; t++) {
            if (yahtzee_scoreblad[s][t] > 0) {
              tmp = tmp + yahtzee_scoreblad[s][t];
            }
          }
          if (tmp > 1) {
            tft.setTextColor(tft.color565(150, 150, 150));
            tft.print(tmp);
          }
          tft.setTextColor(kleur_donker);
        } else if (i == 17) {
          tmp = 0;
          for (int t = 0; t < 6; t++) {
            if (yahtzee_scoreblad[s][t] > 0) {
              tmp = tmp + yahtzee_scoreblad[s][t];
            }
          }
          if (tmp > 0) {
            tft.setTextColor(tft.color565(150, 150, 150));
            if (tmp >= 63) {
              tmp = tmp+35;
            }
            tft.print(tmp);
          }
          tft.setTextColor(kleur_donker);
        } else if (i == 18) {
          tmp = 0;
          for (int t = 0; t < 6; t++) {
            if (yahtzee_scoreblad[s][t] > 0) {
              tmp = tmp + yahtzee_scoreblad[s][t];
            }
          }
          if (tmp >= 63) {
            tmp = tmp+35;
          }
          for (int t = 9; t < 16; t++) {
            if (yahtzee_scoreblad[s][t] > 0) {
              tmp = tmp + yahtzee_scoreblad[s][t];
            }
          }
          if (tmp >= 1) {
            tft.setTextColor(tft.color565(150, 150, 150));
            tft.print(tmp);
          }
          tft.setTextColor(kleur_donker);
        }
      }

    }
    vak_grootte = 20;
    while (ts_touched()) {
      delay(50);
      ts_begin();
    }
  }

  if (actieve_touch) {
    while (ts_touched()) {
      delay(50);
      ts_begin();
    }
    yahtzee_teken_stenen();
  }
}

void yahtzee_run_scherm_1() {
  if (actieve_touch) {
    if ((ts_x <= 119) && (ts_y >= 75) && (ts_y <= 135)) {
      if (worp < 3){
        dobbelstenen_werpen(5);
        dobbel_ogen(60, 145, 30, 30, 3 - worp, kleur_wit, kleur_zwart, 3);
      }
    } else if ((ts_x >= 121) && (ts_y >= 75) && (ts_y <= 135)) {
      yahtzee_teken_scoreblad();
    } else if ((ts_x >= 10) && (ts_x <= 60) && (ts_y >= 200) && (ts_y <= 275)) {
      yahtzee_schore_overzicht();
    } else {
      for (byte i = 0; i <= 4; i++) {
        if (((ts_x >= dobbel_stenen[4][i][0]-5) && (ts_x <= dobbel_stenen[4][i][0]+dobbel_stenen[4][i][2]+5)) && ((ts_y >= dobbel_stenen[4][i][1]-5) && (ts_y <= dobbel_stenen[4][i][1]+dobbel_stenen[4][i][3]+5))) {
          dobbelsteen_fix_unfix(i, 5);
        }
      }
    }
  }
}

void dobbel_ogen(int x, int y, int w, int h, int getal, int oog_kleur_) {
  uint16_t oog_kleur = tft.color565(oog_kleur_, oog_kleur_, oog_kleur_);
  uint16_t steen_kleur;
  if (oog_kleur_ == 0) {
    steen_kleur = tft.color565(255, 255, 255);
  } else {
    steen_kleur = tft.color565(0, 0, 0);
  }
  dobbel_ogen(x, y, w, h, getal, oog_kleur, steen_kleur);
}

void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur) {
  int8_t stip_grootte = 3;
  if (oog_kleur == kleur_licht) {
    dobbel_ogen(x, y, w, h, getal, oog_kleur, stip_grootte, kleur_donker);
  } else if (oog_kleur == kleur_donker) {
    dobbel_ogen(x, y, w, h, getal, oog_kleur, stip_grootte, kleur_licht);
  } else if (oog_kleur == kleur_zwart) {
    dobbel_ogen(x, y, w, h, getal, oog_kleur, stip_grootte, kleur_wit);
  } else {
    dobbel_ogen(x, y, w, h, getal, oog_kleur, stip_grootte, kleur_zwart);
  }
}

void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur, uint16_t steen_kleur) {
  int8_t stip_grootte = 3;
  dobbel_ogen(x, y, w, h, getal, oog_kleur, steen_kleur, stip_grootte);
}

void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur, uint16_t steen_kleur, int8_t stip_grootte) {

  fillRect(x, y, w, h, steen_kleur);
  drawRect(x, y, w, h, oog_kleur);
  int8_t rand = 5;
  if (getal == 1) {
    fillCircle(x+w/2, y+h/2, stip_grootte, oog_kleur);
  } else if (getal == 2) {
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
  } else if (getal == 3) {
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/2, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
  } else if (getal == 4) {
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
  } else if (getal == 5) {
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/2, y+h/2, stip_grootte, oog_kleur);
  } else if (getal == 6) {
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
  } else if (getal == 7) {
    fillCircle(x+w/2, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
  } else if (getal == 8) {
    fillCircle(x+w/2, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/2, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
  } else if (getal == 9) {
    fillCircle(x+w/2, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w/2, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/2, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h-h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/2, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h/rand, stip_grootte, oog_kleur);
    fillCircle(x+w-w/rand, y+h-h/rand, stip_grootte, oog_kleur);
  }
}

void dobbelstenen_werpen(int aantal) {
  for (byte i = 0 ; i < aantal; i++) {
    if (not dobbel_fix[i]) {
      dobbel_resultaat[i] = random(6)+1;
      dobbel_ogen(dobbel_stenen[aantal -1][i][0], dobbel_stenen[aantal -1][i][1], dobbel_stenen[aantal -1][i][2], dobbel_stenen[aantal -1][i][3], dobbel_resultaat[i], 255);
    }
  }
  worp ++;
}

void dobbelsteen_fix_unfix(int steen, int aantal) {
  if (dobbel_fix[steen]) {
    dobbel_fix[steen] = false;
    dobbel_ogen(dobbel_stenen[aantal -1][steen][0], dobbel_stenen[aantal -1][steen][1], dobbel_stenen[aantal -1][steen][2], dobbel_stenen[aantal -1][steen][3], dobbel_resultaat[steen], 255);
  } else {
    dobbel_fix[steen] = true;
    dobbel_ogen(dobbel_stenen[aantal -1][steen][0], dobbel_stenen[aantal -1][steen][1], dobbel_stenen[aantal -1][steen][2], dobbel_stenen[aantal -1][steen][3], dobbel_resultaat[steen], 0);
  }
}

void dobbelsteen_werken() {
  if (ts_touched()) {
    int x = touch_x();
    int y = touch_y();
    if (y < home_knop[1]) {
      if ((x >= 20) && (x <= 220) && (y >= 75) && (y <= 135)) {
        dobbelstenen_werpen(dobbelstenen + 1);
      } else {
        for (byte i = 0; i <= dobbelstenen; i++) {
          if (((x >= dobbel_stenen[dobbelstenen][i][0]-5) && (x <= dobbel_stenen[dobbelstenen][i][0]+dobbel_stenen[dobbelstenen][i][2]+5)) && ((y >= dobbel_stenen[dobbelstenen][i][1]-5) && (y <= dobbel_stenen[dobbelstenen][i][1]+dobbel_stenen[dobbelstenen][i][3]+5))) {
            dobbelsteen_fix_unfix(i, dobbelstenen + 1);
          }
        }
      }
      scherm_touched = millis();
    }
  
  }
}