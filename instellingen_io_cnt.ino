void bouw_instellingen_io_cnt() {
  // bouw_nummeriek("Aantal IO?");
}

void instellingen_io_cnt_aanpassen_naar(int cnt_nieuw) {
  beeld_melding("Even geduld a.u.b.", "aantal io poorten wordt aangepast");
  ts.begin();
  delay(500);
  SD.begin(SD_CS);
  delay(50);
  SD.begin(SD_CS);
  delay(50);
  if (SD.begin(SD_CS)) {
    // sd_save_io(cnt_nieuw);
    // sd_io();
    delay(50);
    // start_io();
  } else {
    beeld_melding("ERROR", "De SD kaart kan niet worden bereikt.");
  }
}

void run_instellingen_io_cnt() {
  if (nummeriek_actief == true) {
    run_nummeriek();
  } else {
    String vraag = "IO cnt op " + String(nummeriek_invoer);
    if (beeld_vraag(vraag, "er wordt gereset", "nee", "ja") == 1) {
      instellingen_io_cnt_aanpassen_naar(nummeriek_invoer);
    } else {
      beeld_melding("nee?");
    }
    naar_io_instellingen();
    
  }
  
}
