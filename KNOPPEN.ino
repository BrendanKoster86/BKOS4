void knop_plaatsen(int knop_nummer) {
  knop_plaatsen(knop_nummer, false);
}

void knop_plaatsen(int knop_nummer, bool tekst) {
  fillRoundRect(knoppen_teken_positie[knop_nummer][0], knoppen_teken_positie[knop_nummer][1], knoppen_teken_positie[knop_nummer][2], knoppen_teken_positie[knop_nummer][3], 5, knoppen_basiskleur[knop_nummer][knoppen_status[knop_nummer]]);
  // tft.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)
  if ((knoppen_tekst[knop_nummer][0] == '*') && (knoppen_tekst[knop_nummer][1] == '*')){
    if ((knoppen_tekst[knop_nummer][2] == 'U') && (knoppen_tekst[knop_nummer][3] == 'S') && (knoppen_tekst[knop_nummer][4] == 'B')){
      // USB
      // drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 7, knoppen_teken_positie[knop_nummer][1]+10, 15, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]], icon_15_usb, sizeof(icon_15_usb)/sizeof(byte));
      drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_zwart, icon_30_usb, sizeof(icon_30_usb)/sizeof(byte));
    } else if ((knoppen_tekst[knop_nummer][2] == '2') && (knoppen_tekst[knop_nummer][3] == '3') && (knoppen_tekst[knop_nummer][4] == '0')){
      // 230 volt AC
      // drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 7, knoppen_teken_positie[knop_nummer][1]+10, 15, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]], icon_15_230, sizeof(icon_15_230)/sizeof(byte));
      if (knoppen_status[knop_nummer] == 1) {
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_geel, icon_30_230, sizeof(icon_30_230)/sizeof(byte));
      } else {
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_oranje, icon_30_230, sizeof(icon_30_230)/sizeof(byte));
      }
    } else if ((knoppen_tekst[knop_nummer][2] == 't') && (knoppen_tekst[knop_nummer][3] == 'v')){
      // TB
      drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]], icon_30_tv, sizeof(icon_30_tv)/sizeof(byte));
    } else if ((knoppen_tekst[knop_nummer][2] == 'L') && (knoppen_tekst[knop_nummer][3] == '_') && (knoppen_tekst[knop_nummer][4] == 'n') && (knoppen_tekst[knop_nummer][5] == 'a') && (knoppen_tekst[knop_nummer][6] == 'v') && (knoppen_tekst[knop_nummer][7] == 'i')){
      // Navigatie verlichting
      if (knoppen_status[knop_nummer] == 1){
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_actief_rood, icon_30_L_navi_1, sizeof(icon_30_L_navi_1)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_actief_groen, icon_30_L_navi_2, sizeof(icon_30_L_navi_2)/sizeof(byte));
      } else {
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_passief_rood, icon_30_L_navi_1, sizeof(icon_30_L_navi_1)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_passief_groen, icon_30_L_navi_2, sizeof(icon_30_L_navi_2)/sizeof(byte));
      }
    } else if ((knoppen_tekst[knop_nummer][2] == 'L') && (knoppen_tekst[knop_nummer][3] == '_') && (knoppen_tekst[knop_nummer][4] == '3') && (knoppen_tekst[knop_nummer][5] == 'k') && (knoppen_tekst[knop_nummer][6] == 'l') && (knoppen_tekst[knop_nummer][7] == ' ')){
      // 3 kleuren verlichting
      if (knoppen_status[knop_nummer] == 1){
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_actief_rood, icon_30_L_3kl_1, sizeof(icon_30_L_3kl_1)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_actief_groen, icon_30_L_3kl_2, sizeof(icon_30_L_3kl_2)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_wit, icon_30_L_3kl_3, sizeof(icon_30_L_3kl_2)/sizeof(byte));
      } else {
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_passief_rood, icon_30_L_3kl_1, sizeof(icon_30_L_3kl_1)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_passief_groen, icon_30_L_3kl_2, sizeof(icon_30_L_3kl_2)/sizeof(byte));
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_zwart, icon_30_L_3kl_3, sizeof(icon_30_L_3kl_3)/sizeof(byte));
      }
    } else if ((knoppen_tekst[knop_nummer][2] == 'L') && (knoppen_tekst[knop_nummer][3] == '_') && (knoppen_tekst[knop_nummer][4] == 's') && (knoppen_tekst[knop_nummer][5] == 't') && (knoppen_tekst[knop_nummer][6] == 'o') && (knoppen_tekst[knop_nummer][7] == 'o') && (knoppen_tekst[knop_nummer][8] == 'm')){
      // stoomlicht
      if (knoppen_status[knop_nummer] == 1){
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_wit, icon_30_L_stoom, sizeof(icon_30_L_stoom)/sizeof(byte));
      } else {
        drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, (knoppen_teken_positie[knop_nummer][1]+5), 30, kleur_zwart, icon_30_L_stoom, sizeof(icon_30_L_stoom)/sizeof(byte));
      }
    } else if ((knoppen_tekst[knop_nummer][2] == 'L') && (knoppen_tekst[knop_nummer][3] == '_') && (knoppen_tekst[knop_nummer][4] == 'a') && (knoppen_tekst[knop_nummer][5] == 'n') && (knoppen_tekst[knop_nummer][6] == 'k') && (knoppen_tekst[knop_nummer][7] == 'e') && (knoppen_tekst[knop_nummer][8] == 'r')){
      // Ankerlicht
      if (knoppen_status[knop_nummer] == 1){
        fillCircle((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2), (knoppen_teken_positie[knop_nummer][1]+knoppen_teken_positie[knop_nummer][3]/2), 15, kleur_wit);
        fillCircle((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2), (knoppen_teken_positie[knop_nummer][1]+knoppen_teken_positie[knop_nummer][3]/2), 2, kleur_zwart);
        // drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_wit, icon_30_L_anker, sizeof(icon_30_L_anker)/sizeof(byte));
      } else {
        fillCircle((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2), (knoppen_teken_positie[knop_nummer][1]+knoppen_teken_positie[knop_nummer][3]/2), 15, kleur_zwart);
        fillCircle((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2), (knoppen_teken_positie[knop_nummer][1]+knoppen_teken_positie[knop_nummer][3]/2), 2, kleur_wit);
        // drawIcon((knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2) - 15, knoppen_teken_positie[knop_nummer][1]+5, 30, kleur_zwart, icon_30_L_anker, sizeof(icon_30_L_anker)/sizeof(byte));
      }
    }  else {
      center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+10, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
    }
  // } else if ((tekst)) & (!knoppen_tekst2[knop_nummer] != "          ")) {
  //   center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+5, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  //   center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+20, knoppen_tekst2[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  } else {
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+10, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  }
  // tft.setCursor(scherm_x(knoppen_teken_positie[knop_nummer][0] * 2), scherm_y(knoppen_teken_positie[knop_nummer][1] * 2));
  // tft.println(knoppen_tekst[knop_nummer]);
  
}


void alle_knoppen_plaatsen() {
  alle_knoppen_plaatsen(false);
}
void alle_knoppen_plaatsen(bool tekst) {
  for (byte i = 0; i < aantal_knoppen; i++) {
    knop_plaatsen(i, tekst);
  }
}

int klik(int x, int y) {
  for (byte i = 0; i < aantal_knoppen; i++) {
    if ((x >= knoppen_positie[i][0]) && (x <= knoppen_positie[i][0]+knoppen_positie[i][2]) && (y >= knoppen_positie[i][1]) && (y <= knoppen_positie[i][1]+knoppen_positie[i][3])) {
      return i;
    }
  }
  return -1;
}


void homeknop_plaatsen() {
  fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_home_knop);
  center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_home_tekst);
  homeknop_actief = true;
  homeknop_half_actief = false;
}

void halve_homeknop_plaatsen() {
  fillRect(home_knop[0], home_knop[1], home_knop[2]/2 -4, home_knop[3], kleur_home_knop);
  center_tekst(home_knop[0] + home_knop[2]/4 - 2, home_knop[1] + 10, "Home", 2, kleur_home_tekst);
  
  fillRect(home_knop[0] + home_knop[2]/2 -4, home_knop[1], 8 , home_knop[3], kleur_home_tekst);
}

void halve_2eknop_plaatsen(String tekst) {
  fillRect(home_knop[0] + home_knop[2]/2 + 4, home_knop[1], home_knop[2]/2 -4, home_knop[3], kleur_home_knop);
  center_tekst(home_knop[0] + home_knop[2]/2 + 4 + home_knop[2]/4 - 2, home_knop[1] + 10, tekst, 2, kleur_home_tekst);
}




void homeknop_plaatsen(bool invert) {
  if (invert) {
    fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_licht);
    center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_donker);
  } else {
    fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_donker);
    center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_licht);
  }
  homeknop_actief = true;
  homeknop_half_actief = false;
}
