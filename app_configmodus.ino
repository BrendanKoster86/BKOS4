void configmodus(String actie) {
  if (actie == "bouw") {
    // Serial.println("Bouw");
    bouw_configmodus();
  } else if (actie == "run") {
    run_configmodus();
  } else if (actie == "naam") {
    item_naam = ("Config");
  } else if (actie == "print") {
    configmodus("naam");
    tft.print(item_naam);
  } else if (actie == "icon_groot") {
    int x = getCursorX() + 20;
    int y = getCursorY() + 25;
    setCursor(getCursorX(), getCursorY()+4);
    drawIcon10x10(x, y, icon_instellingen, kleur_donker, 3);
    tft.setTextColor(kleur_rood);
  } else if (actie == "icon_klein") {
    int x = getCursorX() + 20;
    int y = getCursorY() + 25;
    setCursor(getCursorX(), getCursorY()+4);
    drawIcon10x10(x, y, icon_instellingen, kleur_donker, 3);
    tft.setTextColor(kleur_rood);
  }
}

void bouw_configmodus() {

  // header_plaatsen("Schakelscherm");
  achtergrond(kleur_licht);

  aantal_knoppen = 7;
  
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
    knoppen_positie[i] = configmodus_knoppen_positie[i];
    knoppen_teken_positie[i] = configmodus_knoppen_positie[i];
    knoppen_tekst[i] = configmodus_knoppen_namen[i];
    knoppen_status[i] = exterieurscherm_status[i];
    knoppen_basiskleur[i] = exterieruscherm_knoppen_kleur;
    knoppen_tekst_kleur[i] = schakelscherm_knoppen_tekst_kleur;
    
  }
  

  alle_knoppen_plaatsen();

  
  exterieur_teken_boot(ext_x, ext_y, kleur_groen);
  exterieur_symbolen_verlichting(ext_x, ext_y);
  interieur_verlichting();
}

// void exterieur_teken_boot(int32_t x, int32_t y, uint32_t kleur){
//   tekenItem(x, y, kleur_groen, teken_boot, sizeof(teken_boot)/sizeof(int)/2);
//   tekenCircels(x, y, kleur_groen, circels_boot, sizeof(circels_boot)/sizeof(int)/3);
//   tekenTeksten(x, y, kleur_groen, teken_tekst_positie_boot, teken_tekst_boot, sizeof(teken_tekst_positie_boot)/sizeof(int)/3);
// }

// void exterieur_symbolen_verlichting(int32_t x, int32_t y){

//   int32_t ix;
//   int32_t iy;
//   bool gevonden;
//   // hek
//   ix = 0;
//   iy = 150;
//   for (int i = 0; i < io_knoppen_cnt; i++){
//     if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'h') && (io_namen[io_knoppen[i]][5] == 'e') && (io_namen[io_knoppen[i]][6] == 'k')) {
//       if (io_input[io_knoppen[i]] == 1) {
//         if (io_output[io_knoppen[i]] == 1) {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//         } else {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//         }
//       } else if (io_output[io_knoppen[i]] == 1) {
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//       } else {
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//       }
//     }
//   }

//   // top
//   ix = 67;
//   iy = 0;
//   gevonden = false;
//   for (int i = 0; i < io_knoppen_cnt; i++){
//     if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == '3') && (io_namen[io_knoppen[i]][5] == 'k') && (io_namen[io_knoppen[i]][6] == 'l')) {
//       if (io_input[io_knoppen[i]] == 1) {
//         if (io_output[io_knoppen[i]] == 1) {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//           gevonden = true;
//         } else {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
//         }
//       } else if (io_output[io_knoppen[i]] == 1) {
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_hek, sizeof(icon_30_HL_hek)/sizeof(byte));
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//         gevonden = true;
//       }
//     }
//   }
//   for (int i = 0; i < io_knoppen_cnt; i++){
//     if (!gevonden) {
//       if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'a') && (io_namen[io_knoppen[i]][5] == 'n') && (io_namen[io_knoppen[i]][6] == 'k') && (io_namen[io_knoppen[i]][7] == 'e') && (io_namen[io_knoppen[i]][8] == 'r')){
//         if (io_input[io_knoppen[i]] == 1){
//           if (io_output[io_knoppen[i]] == 1) {
//             drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
//           } else {
//             drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
//           }
//         } else if (io_output[io_knoppen[i]] == 1) {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
//         } else {
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_rond, sizeof(icon_30_HL_rond)/sizeof(byte));
//         }
//       }
//     }
//   }

//   // stoom
//   ix = 75;
//   iy = 75;
//   for (int i = 0; i < io_knoppen_cnt; i++){
//     if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 's') && (io_namen[io_knoppen[i]][5] == 't') && (io_namen[io_knoppen[i]][6] == 'o') && (io_namen[io_knoppen[i]][7] == 'o') && (io_namen[io_knoppen[i]][8] == 'm')) {
//       if (io_input[io_knoppen[i]] == 1){
//         if (io_output[io_knoppen[i]] == 1) {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_wit, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
//         } else {
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
//         }
//       } else if (io_output[io_knoppen[i]] == 1) {
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_grijs, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
//       } else {
//       drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_stoom, sizeof(icon_30_HL_stoom)/sizeof(byte));
//       }
//     }
//   }

//   // boordlichten
//   ix = 80;
//   iy = 143;
//   for (int i = 0; i < io_knoppen_cnt; i++){
//     if ((io_namen[io_knoppen[i]][0] == '*') && (io_namen[io_knoppen[i]][1] == '*') && (io_namen[io_knoppen[i]][2] == 'L') && (io_namen[io_knoppen[i]][3] == '_') && (io_namen[io_knoppen[i]][4] == 'n') && (io_namen[io_knoppen[i]][5] == 'a') && (io_namen[io_knoppen[i]][6] == 'v') && (io_namen[io_knoppen[i]][7] == 'i')) {
//       if (io_input[io_knoppen[i]] == 1){
//         if (io_output[io_knoppen[i]] == 1) {
//           drawIcon(x+ix - 15, y+iy-23 , 30, kleur_actief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_actief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//         } else {
//           drawIcon(x+ix - 15, y+iy-23 , 30, kleur_oranje, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//           drawIcon(x+ix - 15, y+iy-15 , 30, kleur_oranje, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//         }
//       } else if (io_output[io_knoppen[i]] == 1) {
//         drawIcon(x+ix - 15, y+iy-23 , 30, kleur_passief_rood, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//         drawIcon(x+ix - 15, y+iy-15 , 30, kleur_passief_groen, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//       } else {
//       drawIcon(x+ix - 15, y+iy-23 , 30, kleur_zwart, icon_30_HL_bb, sizeof(icon_30_HL_bb)/sizeof(byte));
//       drawIcon(x+ix - 15, y+iy-15 , 30, kleur_zwart, icon_30_HL_sb, sizeof(icon_30_HL_sb)/sizeof(byte));
//       }
//     }
//   }
// }

void run_configmodus() {
  int druk;
  if (actieve_touch) {
    druk = klik(ts_x, ts_y);

    if (druk > -1){
      exterieurscherm_schakel(druk);
      knop_plaatsen(druk);
      io_wijziging = true;
    }

    while (ts_touched()) {
      ts_begin();
    }

    if (ts_y >= home_knop[1]) {
      actieve_app = 0;
      scherm_bouwen = true;
    } else if (ts_y < 30) {
      klik_header(ts_x, ts_y);
    }
  }
  if (io_runned) {
    io_runned = false;
    exterieur_symbolen_verlichting(ext_x, ext_y);
  }
  
  ts_begin(); 
}

// void exterieurscherm_schakel(int knop) {
//   if (knop > 3) {
//     if (charstrip(exterieur_knoppen_namen[knop]) == "**I_licht") {
//       interieur_verlichting(true);
//       exterieurscherm_status[knop] = interieur_licht_variant;
//       knoppen_status[knop] = interieur_licht_variant;
//       // knop_plaatsen(knop);
//     } else {
//       if (knoppen_status[knop] == 0) {
//         // uit wordt aan
//         knoppen_status[knop] = 1;
//         exterieurscherm_status[knop] = 1;
//         for (int i = 0; i < io_knoppen_cnt; i++){
//           int j = 0;
//           bool fl = false;
//           bool stp = false;
//           while (!stp){
//             if (io_namen[io_knoppen[i]][j] == knoppen_tekst[knop][j]) {
//               stp = false;
//             } else {
//               fl = true;
//               stp = true;
//             }
//             if (j >= 9){
//               stp = true;
//             }
//             j++;
//           }
//           if (!fl) {
//             if ((io_output[io_knoppen[i]] == 0) || (io_output[io_knoppen[i]] == 1)){
//               io_output[io_knoppen[i]] = 1;
//             } else if ((io_output[io_knoppen[i]] == 2) || (io_output[io_knoppen[i]] == 3)){
//               io_output[io_knoppen[i]] = 3;
//             }
//           }
//         }
//       } else{
//         // aan wordt uit
//         knoppen_status[knop] = 0;
//         exterieurscherm_status[knop] = 0;
//         for (int i = 0; i < io_knoppen_cnt; i++){
//           int j = 0;
//           bool fl = false;
//           bool stp = false;
//           while (!stp){
//             if (io_namen[io_knoppen[i]][j] == knoppen_tekst[knop][j]) {
//               stp = false;
//             } else {
//               fl = true;
//               stp = true;
//             }
//             if (j >= 9){
//               stp = true;
//             }
//             j++;
//           }
//           if (!fl) {
//             if ((io_output[io_knoppen[i]] == 0) || (io_output[io_knoppen[i]] == 1)){
//               io_output[io_knoppen[i]] = 0;
//             } else if ((io_output[io_knoppen[i]] == 2) || (io_output[io_knoppen[i]] == 3)){
//               io_output[io_knoppen[i]] = 2;
//             }
//           }
//         }
//       }
//     }
//     // knop_plaatsen(knop);
//   } else {
//     for (int i = 0; i < 4; i++) {
//       if (i == knop) {
//         if (knoppen_status[i] == 1) {
//           exterieur_licht_variant++;
//         } else {
//           knoppen_status[i] = 1;
//           exterieurscherm_status[i] = 1;
//           exterieur_licht_variant = 0;
//         }
//       } else {
//         knoppen_status[i] = 0;
//         exterieurscherm_status[i] = 0;
//       }
//       knop_plaatsen(i);
//     }
//     if (knop == 0) {
//       exterieur_verlichting_uit();
//       interieur_verlichting();
//     } else if (knop == 1) {
//       exterieur_zeilverlichting();
//       interieur_verlichting();
//     } else if (knop == 2) {
//       exterieur_motorverlichting();
//       interieur_verlichting();
//     } else if (knop == 3) {
//       exterieur_ankerverlichting();
//       interieur_verlichting();
//     }
    
//   }
//   knop_plaatsen(knop);
//   exterieur_symbolen_verlichting(ext_x, ext_y);
//   io_now = true;
//   // io();
//   // exterieur_symbolen_verlichting(ext_x, ext_y);
//   // delay(50);
//   // io();
//   // exterieur_symbolen_verlichting(ext_x, ext_y);
// }

// void exterieur_verlichting_uit(){
//   for (int knop = 0; knop < io_knoppen_cnt; knop++){
//     if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
//       if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//         io_output[io_knoppen[knop]] = 0;
//       } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//         io_output[io_knoppen[knop]] = 2;
//       }
//     }
//   }
// }

// void exterieur_zeilverlichting(){
//   bool aan_uit;
//   for (int knop = 0; knop < io_knoppen_cnt; knop++){
//     if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
//       aan_uit = false;
//       if (exterieur_licht_variant > 1) {
//         exterieur_licht_variant = 0;
//       }
//       if (exterieur_licht_variant == 0) {
//         // Enkel de 3 kleurenlamp aan ( **L_3kl)
//         if ((io_namen[io_knoppen[knop]][4] == '3') && (io_namen[io_knoppen[knop]][5] == 'k') && (io_namen[io_knoppen[knop]][6] == 'l')){
//           aan_uit = true;
//         }
//       } else if (exterieur_licht_variant == 1) {
//         // navigatie verlichting en heklicht aan (**L_navi  & **L_hek)
//         if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
//           aan_uit = true;
//         }
//       } 
      
//       if (aan_uit) {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 1;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 3;
//         }
//       } else {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 0;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 2;
//         }
//       }
//     }
//   }
// }

// void exterieur_motorverlichting(){
//   bool aan_uit;
//   for (int knop = 0; knop < io_knoppen_cnt; knop++){
//     if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
//       aan_uit = false;
//       if (exterieur_licht_variant > 2) {
//         exterieur_licht_variant = 0;
//       }
//       if (exterieur_licht_variant == 0) {
//         // ankerlicht en navigatie verlichting (**L_anker en **L_navi)
//         if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 'a') && (io_namen[io_knoppen[knop]][5] == 'n') && (io_namen[io_knoppen[knop]][6] == 'k') && (io_namen[io_knoppen[knop]][7] == 'e') && (io_namen[io_knoppen[knop]][8] == 'r')){
//           aan_uit = true;
//         }
//       } else if (exterieur_licht_variant == 1) {
//         // navigatie verlichting, stoomlicht en heklicht aan (**L_navi, **L_stoom  & **L_hek)
//         if ((io_namen[io_knoppen[knop]][4] == 'n') && (io_namen[io_knoppen[knop]][5] == 'a') && (io_namen[io_knoppen[knop]][6] == 'v') && (io_namen[io_knoppen[knop]][7] == 'i')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
//           aan_uit = true;
//         }
//       }  else if (exterieur_licht_variant == 2) {
//         // 3 kleurenlicht en stoomlicht aan (**L_3kl & **L_stoom)
//         if ((io_namen[io_knoppen[knop]][4] == '3') && (io_namen[io_knoppen[knop]][5] == 'k') && (io_namen[io_knoppen[knop]][6] == 'l')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
//           aan_uit = true;
//         }
//       } 
      
//       if (aan_uit) {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 1;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 3;
//         }
//       } else {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 0;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 2;
//         }
//       }
//     }
//   }
// }

// void exterieur_ankerverlichting(){
//   bool aan_uit;
//   for (int knop = 0; knop < io_knoppen_cnt; knop++){
//     if ((io_namen[io_knoppen[knop]][0] == '*') && (io_namen[io_knoppen[knop]][1] == '*') && (io_namen[io_knoppen[knop]][2] == 'L') && (io_namen[io_knoppen[knop]][3] == '_')){
//       aan_uit = false;
//       if (exterieur_licht_variant > 1) {
//         exterieur_licht_variant = 0;
//       }
//       if (exterieur_licht_variant == 0) {
//         // Enkel het ankerlicht aan ( **L_anker)
//         if ((io_namen[io_knoppen[knop]][4] == 'a') && (io_namen[io_knoppen[knop]][5] == 'n') && (io_namen[io_knoppen[knop]][6] == 'k') && (io_namen[io_knoppen[knop]][7] == 'e') && (io_namen[io_knoppen[knop]][8] == 'r')){
//           aan_uit = true;
//         }
//       } else if (exterieur_licht_variant == 1) {
//         // stoomlicht en heklicht aan (**L_stoom  & **L_hek)
//         if ((io_namen[io_knoppen[knop]][4] == 's') && (io_namen[io_knoppen[knop]][5] == 't') && (io_namen[io_knoppen[knop]][6] == 'o') && (io_namen[io_knoppen[knop]][7] == 'o') && (io_namen[io_knoppen[knop]][8] == 'm')){
//           aan_uit = true;
//         } else if ((io_namen[io_knoppen[knop]][4] == 'h') && (io_namen[io_knoppen[knop]][5] == 'e') && (io_namen[io_knoppen[knop]][6] == 'k')){
//           aan_uit = true;
//         }
//       }   
      
//       if (aan_uit) {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 1;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 3;
//         }
//       } else {
//         if ((io_output[io_knoppen[knop]] == 0) || (io_output[io_knoppen[knop]] == 1)){
//           io_output[io_knoppen[knop]] = 0;
//         } else if ((io_output[io_knoppen[knop]] == 2) || (io_output[io_knoppen[knop]] == 3)){
//           io_output[io_knoppen[knop]] = 2;
//         }
//       }
//     }
//   }
// }

// void interieur_verlichting() {
//   interieur_verlichting(false);
// }

// void interieur_verlichting(bool schakelen) {
//   if (schakelen) {
//     interieur_licht_variant ++;
//   }
//   if (interieur_licht_variant >= 4) {
//     interieur_licht_variant = 0;
//   }
//   // tft.fillRect(10, 30, 100, 30, kleur_zwart);
//   // tft.setTextColor(kleur_wit);
//   // tft.setCursor(10, 31);
//   // tft.print(interieur_licht_variant);

//   int wit = 0;
//   int rood = 0;

//   if (interieur_licht_variant == 0) {
//     wit = 0;
//     rood = 0;
//   } else if (interieur_licht_variant == 1) {
//     wit = 1;
//     rood = 0;
//   } else if (interieur_licht_variant == 2) {
//     wit = 0;
//     rood = 1;
//   } else if (interieur_licht_variant == 3) {
//     for (int i = 0; i < sizeof(exterieurscherm_status); i++) {
//       if (exterieurscherm_status[i] == 1) {
//         if (charstrip(exterieur_knoppen_namen[i]) == "**haven") {
//           // tft.print("haven");
//           wit = 1;
//           rood = 0;
//         } else if (charstrip(exterieur_knoppen_namen[i]) == "**zeilen") {
//           // tft.print("zeilen");
//           wit = 0;
//           rood = 1;
//         } else if (charstrip(exterieur_knoppen_namen[i]) == "**motor") {
//           // tft.print("motor");
//           wit = 0;
//           rood = 1;
//         } else if (charstrip(exterieur_knoppen_namen[i]) == "**anker") {
//           // tft.print("anker");
//           wit = 1;
//           rood = 0;
//         // } else {
//         //   tft.print(i);
//         //   tft.print("[");
//         //   tft.print(charstrip(exterieur_knoppen_namen[i]));
//         //   tft.print("]");
//         }
//       }
//     }
//   }

//   for (int knop = 0; knop < io_knoppen_cnt; knop++){
//     if (io_namen[io_knoppen[knop]] == "**IL_wit "){
//       io_output[io_knoppen[knop]] = wit;
//     } else if (io_namen[io_knoppen[knop]] == "**IL_rood"){
//       io_output[io_knoppen[knop]] = rood;
//     }
//   }
// }


// String charstrip(char invoer[]) {
//   String uitvoer = "";
//   for (int i = 0; i < 10; i++){
//     if (invoer[i] != ' '){
//       uitvoer += invoer[i];
//     }
//   }
//   uitvoer.trim();
//   return uitvoer;
// }