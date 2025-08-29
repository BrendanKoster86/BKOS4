// #include "morse.h"



void app_morse(String actie) {
  if (actie == "bouw") {
    homeknop_actief = false;
    homeknop_half_actief = false;
    slepen_toestaan = false;
    bouw_morse();
  } else if (actie == "run") {
    run_morse();
  } if (actie == "naam") {
    item_naam = "Morse";
  } else if (actie == "print") {
    app_morse("naam");
    tft.print(item_naam);
  } else if (actie == "icon_klein") {
    int x = getCursorX();
    int y = getCursorY();
    setCursor(x + 10, y + 20);
    tft.setTextSize(3);
    tft.print("._.._");
    // dobbel_ogen(x + 7, y + 7, 90, 90, 5, 0);
    setCursor(x + 10, y + 50);
  } else if (actie == "icon_groot") {
    int x = getCursorX();
    int y = getCursorY();
    setCursor(x + 10, y + 50);
    tft.setTextSize(5);
    tft.print("._.._");
    // dobbel_ogen(x + 7, y + 7, 90, 90, 5, 0);
    setCursor(x + 10, y + 105);
  }
}



void bouw_morse() {
  achtergrond(kleur_zwart);
  header_plaatsen("Morse");
  tft.setTextColor(kleur_donker);
  setCursor(20, 50);
  tft.setTextSize(2);
  tft.print("Kies woord");
  
  aantal_knoppen = aantal_morse_woorden;

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
    knoppen_positie[i] = morse_knoppen_positie[i];
    knoppen_teken_positie[i] = morse_knoppen_positie[i];
    knoppen_tekst[i] = morse_woorden[i];
    knoppen_status[i] = 0;
    knoppen_basiskleur[i] = schakelscherm_knoppen_kleur;
    knoppen_tekst_kleur[i] = schakelscherm_knoppen_tekst_kleur;
    
  }
  
  alle_knoppen_plaatsen();
  morse_woord[0] = 'P';
  morse_woord[1] = 'a';
  morse_woord[2] = 'a';
  morse_woord[3] = 'r';
  morse_woord[4] = 'd';
  // int gedrukt = -1;
  // while (gedrukt == -1){
  //   Serial.print('.');
  //   if (ts_touched()){

  //     while (ts_touched()){
  //       ts_begin();
  //       delay(50);
  //     }

  //     int x = touch_x();
  //     int y = touch_y();
      
  //     gedrukt = klik(x, y);
      
  //     for (int i = 0 ; i < 10; i++){
  //       morse_woord[i] = morse_woorden[gedrukt][i];
  //     }
  //   } 
  //   ts_begin();
  //   delay(50);
  // }

  digitalWrite(TFT_BL, LOW);
  morse_actief = true;

  while (ts_touched()){
    ts_begin();
    delay(50);
  }

}

void run_morse() {
  if (morse_woord == "Paard     "){
    morse_woord_paard();
  } else if (morse_woord == "SOS       "){
    morse_woord_sos();
  } else if (morse_woord == "Westerly  "){
    morse_woord_westerly();
  } else {
    morse_woord_paard();
  }
  morse_wacht(morse_delay_woord);
  scherm_touched = millis();

  if (!morse_actief){
    digitalWrite(TFT_BL, HIGH);
    actieve_app = 0;
    scherm_bouwen = true;
  }

}

void morse_woord_paard(){
  morse_p();
  morse_a();
  morse_a();
  morse_r();
  morse_d();
}

void morse_woord_sos(){
  morse_s();
  morse_o();
  morse_s();
}

void morse_woord_westerly(){
  morse_w();
  morse_e();
  morse_s();
  morse_t();
  morse_e();
  morse_r();
  morse_l();
  morse_y();
}

void morse_aan(){
  for (int i = 0; i < cnt_morse_pooorten; i++) {
    io_output[morse_poorten[i]] = 1;
  }
  io();
}
 void morse_uit(){
  for (int i = 0; i < cnt_morse_pooorten; i++) {
    io_output[morse_poorten[i]] = 0;
  }
  io();
 }

void morse_wacht(int tijd) {
  int einde = millis() + tijd;
  while ((millis() < einde) && (morse_actief)) {
    if (ts_touched()){
      morse_actief = false;
    }
    delay(50);
  }
}

void morse_lang(){
  morse_aan();
  morse_wacht(morse_delay_lang);
  morse_uit();
  morse_wacht(morse_delay_kort);
}

void morse_kort(){
  morse_aan();
  morse_wacht(morse_delay_kort);
  morse_uit();
  morse_wacht(morse_delay_kort);
}

void morse_a(){
  morse_kort();
  morse_lang();
  morse_wacht(morse_delay_letter);
}

void morse_d(){
  morse_lang();
  morse_kort();
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_e(){
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_l(){
  morse_kort();
  morse_lang();
  morse_kort();
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_p(){
  morse_kort();
  morse_lang();
  morse_lang();
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_r(){
  morse_kort();
  morse_lang();
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_s(){
  morse_kort();
  morse_kort();
  morse_kort();
  morse_wacht(morse_delay_letter);
}

void morse_t(){
  morse_lang();
  morse_wacht(morse_delay_letter);
}

void morse_o(){
  morse_lang();
  morse_lang();
  morse_lang();
  morse_wacht(morse_delay_letter);
}

void morse_w(){
  morse_kort();
  morse_lang();
  morse_lang();
  morse_wacht(morse_delay_letter);
}

void morse_y(){
  morse_lang();
  morse_kort();
  morse_lang();
  morse_lang();
  morse_wacht(morse_delay_letter);
}
