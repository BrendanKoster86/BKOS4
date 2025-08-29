void exterieur(String actie) {
  if (actie == "bouw") {
    // Serial.println("Bouw");
    bouw_exterieur();
  } else if (actie == "run") {
    run_exterieur();
  } else if (actie == "naam") {
    item_naam = ("Exterieur");
  } else if (actie == "print") {
    exterieur("naam");
    tft.print(item_naam);
  } else if (actie == "icon_groot") {
    int x = getCursorX();
    int y = getCursorY();
    fillRect(x+3, y+3, 98, 95, kleur_zwart);      // Vlak waarbinnen een (groot) icon getekent mag worden 
    drawLine(x+20, y+14, x+20, y+80, kleur_wit);
    drawLine(x+20, y+47, x+25, y+19, kleur_wit);
    drawLine(x+20, y+14, x+60, y+14, kleur_wit);
    drawLine(x+25, y+19, x+65, y+19, kleur_wit);
    drawLine(x+20, y+14, x+25, y+19, kleur_wit);
    drawLine(x+60, y+14, x+65, y+19, kleur_wit);
    drawLine(x+20, y+80, x+60, y+80, kleur_wit);
    drawLine(x+60, y+80, x+60, y+47, kleur_wit);
    drawLine(x+60, y+47, x+65, y+19, kleur_wit);
    drawLine(x+20, y+47, x+60, y+47, tft.color565(100, 100, 100));
    drawLine(x+42, y+42, x+45, y+25, kleur_wit);
    setCursor(x+35, y+53);
    tft.setTextSize(2);
    tft.setTextColor(kleur_wit);
    tft.print(0);
    tft.setTextColor(kleur_donker);
    tft.setTextSize(1.5);
    setCursor(x+5, y+105);
  }
}

void bouw_exterieur() {

  // header_plaatsen("Schakelscherm");
  achtergrond(kleur_licht);

  if (io_knoppen_cnt < 10) {
    aantal_knoppen = io_knoppen_cnt;
  } else {
    aantal_knoppen = 10;
  }
  
  delete[]knoppen_positie;
  delete[]knoppen_teken_positie;
  delete[]knoppen_tekst;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst_kleur;
  delete[]knoppen_status;

  
  knoppen_positie = new int*[aantal_knoppen];
  knoppen_teken_positie = new int*[aantal_knoppen];
  knoppen_tekst = new char*[aantal_knoppen];
  knoppen_basiskleur = new uint16_t*[aantal_knoppen];
  knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
  knoppen_status = new byte[aantal_knoppen];


  for (int i  = 0 ; i < aantal_knoppen ; i++) {
    knoppen_positie[i] = exterieurscherm_knoppen_positie[i];
    knoppen_teken_positie[i] = exterieurscherm_knoppen_positie[i];
    knoppen_tekst[i] = exterieur_knoppen_namen[i];
    knoppen_status[i] = exterieurscherm_status[i];
    knoppen_basiskleur[i] = schakelscherm_knoppen_kleur;
    knoppen_tekst_kleur[i] = schakelscherm_knoppen_tekst_kleur;
    
  }
  
  alle_knoppen_plaatsen();

  
  exterieur_teken_boot(ext_x, ext_y, kleur_groen);
  exterieur_symbolen_verlichting(ext_x, ext_y);

}

void exterieur_teken_boot(int32_t x, int32_t y, uint32_t kleur){
  tekenItem(x, y, kleur_groen, teken_boot, sizeof(teken_boot)/sizeof(int)/2);
  tekenCircels(x, y, kleur_groen, circels_boot, sizeof(circels_boot)/sizeof(int)/3);
  tekenTeksten(x, y, kleur_groen, teken_tekst_positie_boot, teken_tekst_boot, sizeof(teken_tekst_positie_boot)/sizeof(int)/3);
}

void exterieur_symbolen_verlichting(int32_t x, int32_t y){

  int32_t ix;
  int32_t iy;
  bool gevonden;
  // hek
  ix = 0;
  iy = 150;
  for (int i = 0; i < io_knoppen_cnt; i++){
    if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'h') && (io_namen[io_knoppen[i]][5] == 'e') && (io_namen[io_knoppen[i]][6] == 'k')) {
      if (io_input[io_knoppen[i]] == 1) {
        if (io_output[io_knoppen[i]] == 1) {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
        } else {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
        }
      } else if (io_output[io_knoppen[i]] == 1) {
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
      } else {
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
      }
    }
  }

  // top
  ix = 67;
  iy = 0;
  gevonden = false;
  for (int i = 0; i < io_knoppen_cnt; i++){
    if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == '3') && (io_namen[io_knoppen[i]][5] == 'k') && (io_namen[io_knoppen[i]][6] == 'l')) {
      if (io_input[io_knoppen[i]] == 1) {
        if (io_output[io_knoppen[i]] == 1) {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
          gevonden = true;
        } else {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
        }
      } else if (io_output[io_knoppen[i]] == 1) {
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
        gevonden = true;
      }
    }
  }
  for (int i = 0; i < io_knoppen_cnt; i++){
    if (!gevonden) {
      if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'a') && (io_namen[io_knoppen[i]][5] == 'n') && (io_namen[io_knoppen[i]][6] == 'k') && (io_namen[io_knoppen[i]][7] == 'e') && (io_namen[io_knoppen[i]][8] == 'r')){
        if (io_input[io_knoppen[i]] == 1){
          if (io_output[io_knoppen[i]] == 1) {
            drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
          } else {
            drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
          }
        } else if (io_output[io_knoppen[i]] == 1) {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
        } else {
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
        }
      }
    }
  }

  // stoom
  ix = 75;
  iy = 75;
  for (int i = 0; i < io_knoppen_cnt; i++){
    if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 's') && (io_namen[io_knoppen[i]][5] == 't') && (io_namen[io_knoppen[i]][6] == 'o') && (io_namen[io_knoppen[i]][7] == 'o') && (io_namen[io_knoppen[i]][8] == 'm')) {
      if (io_input[io_knoppen[i]] == 1){
        if (io_output[io_knoppen[i]] == 1) {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
        } else {
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
        }
      } else if (io_output[io_knoppen[i]] == 1) {
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
      } else {
      drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
      }
    }
  }

  // boordlichten
  ix = 80;
  iy = 143;
  for (int i = 0; i < io_knoppen_cnt; i++){
    if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'n') && (io_namen[io_knoppen[i]][5] == 'a') && (io_namen[io_knoppen[i]][6] == 'v') && (io_namen[io_knoppen[i]][7] == 'i')) {
      if (io_input[io_knoppen[i]] == 1){
        if (io_output[io_knoppen[i]] == 1) {
          drawIcon(x+ix - 15, y+iy-23 , 30, kleur_actief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
        } else {
          drawIcon(x+ix - 15, y+iy-23 , 30, kleur_oranje, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
          drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
        }
      } else if (io_output[io_knoppen[i]] == 1) {
        drawIcon(x+ix - 15, y+iy-23 , 30, kleur_passief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
        drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
      } else {
      drawIcon(x+ix - 15, y+iy-23 , 30, kleur_zwart, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
      drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
      }
    }
  }
}

void run_exterieur() {
  ts_begin();
  int druk;
  if (ts_touched()) {
      
    int x = touch_x();
    int y = touch_y();
    
    druk = klik(x, y);

    if (druk > -1){
      exterieurscherm_schakel(druk);
      
      io_wijziging = true;
    }

    while (ts_touched()) {
      ts_begin();
    }

    if (y >= home_knop[1]) {
      actieve_app = 0;
      scherm_bouwen = true;
    } else if (y < 30) {
      klik_header(x, y);
    }

    
  }
  ts_begin(); 
}

void exterieurscherm_schakel(int knop) {
  if (knop > 3) {
    if (knoppen_status[knop] == 0) {
      // uit wordt aan
      knoppen_status[knop] = 1;
      exterieurscherm_status[knop] = 1;
      for (int i = 0; i < io_knoppen_cnt; i++){
        int j = 0;
        bool fl = false;
        bool stp = false;
        while (!stp){
          if (io_namen[io_knoppen[i]][j] == knoppen_tekst[knop][j]) {
            stp = false;
          } else {
            fl = true;
            stp = true;
          }
          if (j >= 9){
            stp = true;
          }
          j++;
        }
        if (!fl) {
          if ((io_output[io_knoppen[i]] == 0) || (io_output[io_knoppen[i]] == 1)){
            io_output[io_knoppen[i]] = 1;
          } else if ((io_output[io_knoppen[i]] == 2) || (io_output[io_knoppen[i]] == 3)){
            io_output[io_knoppen[i]] = 3;
          }
        }
      }
    } else{
      // aan wordt uit
      knoppen_status[knop] = 0;
      exterieurscherm_status[knop] = 0;
      for (int i = 0; i < io_knoppen_cnt; i++){
        int j = 0;
        bool fl = false;
        bool stp = false;
        while (!stp){
          if (io_namen[io_knoppen[i]][j] == knoppen_tekst[knop][j]) {
            stp = false;
          } else {
            fl = true;
            stp = true;
          }
          if (j >= 9){
            stp = true;
          }
          j++;
        }
        if (!fl) {
          if ((io_output[io_knoppen[i]] == 0) || (io_output[io_knoppen[i]] == 1)){
            io_output[io_knoppen[i]] = 0;
          } else if ((io_output[io_knoppen[i]] == 2) || (io_output[io_knoppen[i]] == 3)){
            io_output[io_knoppen[i]] = 2;
          }
        }
      }
    }
    knop_plaatsen(knop);
  } else {
    for (int i = 0; i < 4; i++) {
      if (i == knop) {
        if (knoppen_status[i] == 1) {
          exterieur_licht_variant++;
        } else {
          knoppen_status[i] = 1;
          exterieurscherm_status[i] = 1;
          exterieur_licht_variant = 0;
        }
      } else {
        knoppen_status[i] = 0;
        exterieurscherm_status[i] = 0;
      }
      knop_plaatsen(i);
    }
    if (knop == 0) {
      exterieur_verlichting_uit();
    } else if (knop == 1) {
      exterieur_zeilverlichting();
    } else if (knop == 2) {
      exterieur_motorverlichting();
    } else if (knop == 3) {
      exterieur_ankerverlichting();
    }
  }
  exterieur_symbolen_verlichting(ext_x, ext_y);
  io();
  exterieur_symbolen_verlichting(ext_x, ext_y);
  delay(50);
  io();
  exterieur_symbolen_verlichting(ext_x, ext_y);
}

void exterieur_verlichting_uit(){
  for (int knop = 0; knop < io_knoppen_cnt; knop++){
    if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
      if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
        io_output[io_knoppen[knop]] = 0;
      } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
        io_output[io_knoppen[knop]] = 2;
      }
    }
  }
}

void exterieur_zeilverlichting(){
  bool aan_uit;
  for (int knop = 0; knop < io_knoppen_cnt; knop++){
    if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
      aan_uit = false;
      if (exterieur_licht_variant > 1) {
        exterieur_licht_variant = 0;
      }
      if (exterieur_licht_variant == 0) {
        // Enkel de 3 kleurenlamp aan ( **L_3kl)
        if ((io_namen[io_knoppen[knop]][4] == '3') && (io_namen[io_knoppen[knop]][5] == 'k') && (io_namen[io_knoppen[knop]][6] == 'l')){
          aan_uit = true;
        }
      } else if (exterieur_licht_variant == 1) {
        // navigatie verlichting en heklicht aan (**L_navi  & **L_hek)
        if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
          aan_uit = true;
        }
      } 
      
      if (aan_uit) {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 1;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 3;
        }
      } else {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 0;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 2;
        }
      }
    }
  }
}

void exterieur_motorverlichting(){
  bool aan_uit;
  for (int knop = 0; knop < io_knoppen_cnt; knop++){
    if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
      aan_uit = false;
      if (exterieur_licht_variant > 2) {
        exterieur_licht_variant = 0;
      }
      if (exterieur_licht_variant == 0) {
        // ankerlicht en navigatie verlichting (**L_anker en **L_navi)
        if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 'a') && (io_namen[io_knoppen[knop]][5] == 'n') && (io_namen[io_knoppen[knop]][6] == 'k') && (io_namen[io_knoppen[knop]][7] == 'e') && (io_namen[io_knoppen[knop]][8] == 'r')){
          aan_uit = true;
        }
      } else if (exterieur_licht_variant == 1) {
        // navigatie verlichting, stoomlicht en heklicht aan (**L_navi, **L_stoom  & **L_hek)
        if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
          aan_uit = true;
        }
      }  else if (exterieur_licht_variant == 2) {
        // 3 kleurenlicht en stoomlicht aan (**L_3kl & **L_stoom)
        if ((io_namen[io_knoppen[knop]][4] == '3') && (io_namen[io_knoppen[knop]][5] == 'k') && (io_namen[io_knoppen[knop]][6] == 'l')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
          aan_uit = true;
        }
      } 
      
      if (aan_uit) {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 1;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 3;
        }
      } else {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 0;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 2;
        }
      }
    }
  }
}

void exterieur_ankerverlichting(){
  bool aan_uit;
  for (int knop = 0; knop < io_knoppen_cnt; knop++){
    if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
      aan_uit = false;
      if (exterieur_licht_variant > 1) {
        exterieur_licht_variant = 0;
      }
      if (exterieur_licht_variant == 0) {
        // Enkel het ankerlicht aan ( **L_anker)
        if ((io_namen[io_knoppen[knop]][4] == 'a') && (io_namen[io_knoppen[knop]][5] == 'n') && (io_namen[io_knoppen[knop]][6] == 'k') && (io_namen[io_knoppen[knop]][7] == 'e') && (io_namen[io_knoppen[knop]][8] == 'r')){
          aan_uit = true;
        }
      } else if (exterieur_licht_variant == 1) {
        // stoomlicht en heklicht aan (**L_stoom  & **L_hek)
        if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
          aan_uit = true;
        } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
          aan_uit = true;
        }
      }   
      
      if (aan_uit) {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 1;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 3;
        }
      } else {
        if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
          io_output[io_knoppen[knop]] = 0;
        } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
          io_output[io_knoppen[knop]] = 2;
        }
      }
    }
  }
}

