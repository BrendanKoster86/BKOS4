void knop_plaatsen(int knop_nummer) {
  knop_plaatsen(knop_nummer, "tekst");
}

void knop_plaatsen(int knop_nummer, bool tekst) {
  fillRoundRect(knoppen_teken_positie[knop_nummer][0], knoppen_teken_positie[knop_nummer][1], knoppen_teken_positie[knop_nummer][2], knoppen_teken_positie[knop_nummer][3], 5, knoppen_basiskleur[knop_nummer][knoppen_status[knop_nummer]]);
  // tft.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)
  if ((tekst)){// & (!knoppen_tekst2[knop_nummer] == "          ")) {
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+5, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+20, knoppen_tekst2[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  } else {
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+10, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  }
  setCursor(knoppen_teken_positie[knop_nummer][0] + knoppen_tekst_positie[knop_nummer][0], knoppen_teken_positie[knop_nummer][1] + knoppen_tekst_positie[knop_nummer][1]);
  tft.println(knoppen_tekst[knop_nummer]);
}


void alle_knoppen_plaatsen() {
  alle_knoppen_plaatsen("cijfer");
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
