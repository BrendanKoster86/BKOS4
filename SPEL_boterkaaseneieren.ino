void spel_boterkaaseneieren(String actie) {
  if (actie == "bouw") {
    bouw_spel_boterkaaseneieren();
  } else if (actie == "run") {
    run_spel_boterkaaseneieren();
  } if (actie == "naam") {
    item_naam = "Boter Kaas en Eieren";
  } else if (actie == "print") {
    spel_boterkaaseneieren("naam");
    tft.print(item_naam);
  } else if (actie == "icon_groot") {
    int x = getCursorX();
    int y = getCursorY();
    drawLine(x+33, y+5, x+33, y+95, kleur_donker);
    drawLine(x+66, y+5, x+66, y+95, kleur_donker);
    drawLine(x+5, y+33, x+95, y+33, kleur_donker);
    drawLine(x+5, y+66, x+95, y+66, kleur_donker);
    setCursor(x + 10, y + 72);
    tft.setTextSize(2);
    tft.print("x");
    setCursor(x + 43, y + 10);
    tft.print("o");
    tft.setTextSize(1.5);
    setCursor(x + 3, y + 105);
  }
}

void bouw_spel_boterkaaseneieren() {
  header_plaatsen("Boter kaas en eieren");
  achtergrond(kleur_licht);
  spel_boterkaaseneieren_veld();
}

void spel_boterkaaseneieren_veld() {
  fillRect(spel_speelveld[0]-4 , spel_speelveld[1]-4, spel_speelveld[2]+8, spel_speelveld[3]+8, kleur_donker);
  drawRect(spel_speelveld[0]-6 , spel_speelveld[1]-6, spel_speelveld[2]+12, spel_speelveld[3]+12, kleur_donker);
  drawLine(spel_speelveld[0] + spel_speelveld[2]/3, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2]/3, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
  drawLine(spel_speelveld[0] + spel_speelveld[2]/3 * 2, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2]/3 * 2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
  drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]/3, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]/3, kleur_licht);
  drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]/3 * 2, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]/3 * 2, kleur_licht);
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] > 0) {
      spel_boterkaaseneieren_teken_symbool(i);
    }
  }
}

void spel_boterkaaseneieren_teken_symbool(int hokje) {
  if (hokje <= 2) {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * (hokje * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1], "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * (hokje * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1], "o", 8, kleur_licht);
    }
  } else if (hokje <= 5) {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 3) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] / 3, "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 3) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] / 3, "o", 8, kleur_licht);
    }
  } else {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 6) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] - spel_speelveld[3] / 3, "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 6) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] - spel_speelveld[3] / 3, "o", 8, kleur_licht);
    }
  }
}

void spel_boterkaaseneieren_beurt_computer() {
  if (spel_boterkaaseneieren_winnen() < 9) {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_winnen());
  } else if (spel_boterkaaseneieren_verlies_voorkomen() < 9) {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_verlies_voorkomen());
  } else {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_willekeurig());
  }
}

int spel_boterkaaseneieren_winnen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    if ((o_cnt == 2) && (x_cnt == 0)) {
      for (int j = 0; j < 9; j++) {
        if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
          if (spel_boterkaaseneieren_status[j] == 2) {
            o_cnt++;
          } else {
            return j;
          } 
        }
      }
    }
  }
  return 9;
}

int spel_boterkaaseneieren_verlies_voorkomen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    if ((o_cnt == 0) && (x_cnt == 2)) {
      for (int j = 0; j < 9; j++) {
        if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
          if (spel_boterkaaseneieren_status[j] == 1) {
            x_cnt++;
          } else {
            return j;
          } 
        }
      }
    }
  }
  return 9;
}

int spel_boterkaaseneieren_willekeurig() {
  byte cnt = 0;
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      cnt++;
    }
  }
  int keuze = random(cnt);

  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      cnt--;
      if (cnt <= keuze) {
        return i;
      }
    }
  }
  return 10;
}

void spel_boterkaaseneieren_zet(int speler, int zet) {
  if (spel_boterkaaseneieren_status[zet] == 0) {
    spel_boterkaaseneieren_status[zet] = speler;
    spel_boterkaaseneieren_teken_symbool(zet);
    if (speler == 1) {
      speler_actief = 2;
    } else {
      speler_actief = 1;
    }
  }
}

void spel_boterkaaseneieren_isergewonnen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    
    if ((o_cnt == 3) || (x_cnt == 3)) {
      if (i < 3) {
        drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1), spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1), kleur_licht);
        drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)-1, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)-1, kleur_licht);
        drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)+1, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)+1, kleur_licht);
      } else if (i < 6) {
        drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1), spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1), spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)-1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)-1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)+1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)+1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      } else if (i == 6) {
        drawLine(spel_speelveld[0], spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0]+1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]-1, kleur_licht);
        drawLine(spel_speelveld[0], spel_speelveld[1]+1, spel_speelveld[0] + spel_speelveld[2]-1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0], spel_speelveld[1]+2, spel_speelveld[0] + spel_speelveld[2]-2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      } else {
        drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1], spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0] + spel_speelveld[2]-1, spel_speelveld[1], spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]-1, kleur_licht);
        drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1]+1, spel_speelveld[0]+1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1]+2, spel_speelveld[0]+2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      }
      delay(500);
      gewaasd_scherm();
      if (x_cnt == 3) {
        center_tekst(120, 170, "GEWONNEN!", 4, kleur_actief_groen);
      } else {
        center_tekst(120, 170, "GAME OVER", 4, kleur_actief_rood);
      }
      delay(1000);
      spel_boterkaaseneieren_nieuwspel();
    }
  }
  int leeg = 0;
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      leeg ++;
    }
  }
  if (leeg == 0) {
    delay(500);
    gewaasd_scherm();
    center_tekst(120, 170, "gelijk spel", 4, kleur_actief_groen);
    delay(1000);
    spel_boterkaaseneieren_nieuwspel();
  }

}

void spel_boterkaaseneieren_nieuwspel() {
  for (int i = 0; i < 9; i++) {
    spel_boterkaaseneieren_status[i] = 0;
  }
  speler_actief = 0;
  bouw_spel_boterkaaseneieren();
}

void spel_boterkaaseneieren_klik(int x, int y) {
  int hokje = 0;
  byte y_stapjes = spel_speelveld[3] / 3;
  byte x_stapjes = spel_speelveld[2] / 3;
  if (y < spel_speelveld[1] + y_stapjes) {
    hokje = hokje; // niks doen, bovenste rij
  } else if (y < spel_speelveld[1] + y_stapjes * 2) {
    hokje = hokje + 3; // 2e rij
  } else {
    hokje = hokje + 6; // 3e rij
  }

  if (x < spel_speelveld[0] + x_stapjes) {
    hokje = hokje; // niks doen, linker kolom
  } else if (x < spel_speelveld[0] + x_stapjes * 2) {
    hokje = hokje + 1; // middelste kolom
  } else {
    hokje = hokje + 2; // rechter kolom
  }

  spel_boterkaaseneieren_zet(1, hokje);

}

void spel_boterkaaseneieren_beurt_speler() {
  if (actieve_touch) {
    spel_boterkaaseneieren_klik(ts_x, ts_y);
  }

}

void run_spel_boterkaaseneieren() {
  digitalWrite(TFT_BL, HIGH);
  spel_boterkaaseneieren_isergewonnen();
  if (speler_actief == 1) {
    // speler is aan de beurt
    spel_boterkaaseneieren_beurt_speler();
  } else if (speler_actief == 2) {
    // computer aan de beurt
    spel_boterkaaseneieren_beurt_computer();
  } else {
    // Nog geen speler gekozen? dan wordt nu een speler gekozen
    speler_actief = random(1, 3);
  }
}
