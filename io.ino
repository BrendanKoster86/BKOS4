String io_code_naar_naam(byte code){
  if (code == 2) {
    return "8 bit Logische module";
  } else if (code == 50) {
    return "8 bit Hub";
  } else if (code == 51) {
    return "Analoge hub";
  } else if (code == 52) {
    return "uart hub";
  } else if (code == 66) {
    return "8 bit Communicatie";
  } else if (code == 130) {
    return "8 bit Schakelmodule";
  } else if (code == 3) {
    return "16 bit Logische module";
  } else if (code == 83) {
    return "16 bit Communicatie";
  } else if (code == 98) {
    return "8 bit Knoppen";
  } else if (code == 115) {
    return "16 bit Knoppen";
  } else if (code == 194) {
    return "8 bit Controller";
  } else if (code == 211) {
    return "16 bit Controller";
  } else if (code == 147) {
    return "16 bit Schakel module";
  } 
  return "";
}

# if IO_METHODE == 2
  /* In HARDWARE modus 2 wordt gebruik gemaakt van de CYD die niet beschikt over mijn communicatie poort.
   * Er zijn 2 oplossingen mogelijk om dit op te lossen. Beide zijn gebaseerd op seriele communicatie met AT tiny micro controller
   *   1. Een tussen module met enkel een ATtiny
   *   2. De eerste 74HC14 chip vervangen voor een 180 graden gedraaide ATtiny 44 of 84 die bij het eerste aparaat de omzetting doet
   * Er moet nog wat getest worden of het handig is om de standaard Serial.print() te gebruiken, of dat er beter een ander kanaal kan worden gebruikt.
   * Op het momnt heeft het eerste mijn voorkeur mocht dat lukken.
   */

  void io_boot() {
    // io_detect();
    Serial.print("AT+MODUS=n");
  }

  void io_detect() {
    /* Deze functie zorgt er vopor dat wordt gedetecteerd welke externe hardware overal is aangesloten.
     * Dit is een vrij complexe taak en zal zonder meer veel tweaken vragen.
     * Alle randapparatuur heeft een ID code ter grootte van 8 bit (1 byte) dat kan worden uitgelezen
     * Nog niet alles is uitgedacht en getest, maar op het moment is het handig uit te gaan van de volgende codes:
     *
     * ID  :   Naam                 |  Registratie  |   Omschrijving (primaire) doel
     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     *   2 : 8 bit logische module  |   8 sensoren  | Ontvangst logisch voltage sensoren (kan ook voor aansturen logisch voltage aparaten worden gebruikt)
     *  50 : 8 bit hub              |       -       | Schakelt tussen verschillende uitgangen. Bij deze moduele moeten alle uitgangen worden bekeken wat hier achter zit.
     *  51 : Analoge hub            |       -       | Schakelt analoog 1 poort van de MCU analoog door zodat een analoge input of output van een andere bijvoorbeeld sensor kan worden geregistreerd.
     *  52 : uart hub               |       -       | Schakelt direct 2 poorten van de MCU analoog door zodat bijvoorbeeld de uart naar een ander aparaat kan linken.
     *  66 : 8 bit communicatie     |       -       | Communicatie tussen 2 boordcomputers. Moet nog een protocol voor komen. Deze items overslaan in het overzicht.
     * 130 : 8 bit Schakel module   |   8 knoppen   | Aansturen aparaten (ook voor 12 volt sensoren te gebruiken)
     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     *   3 : 16 bit logische module |  16 sensoren
     *  83 : 16 bit communicatie    |       -       | Communicatie tussen 2 boordcomputers. Moet nog een protocol voor komen
     *  98 :  8 bit knoppen         |       -       | Aansturing van de boodcomputer met een 8 bit knoppen panneel... n.t.b. hoe dit gaat werken
     * 115 : 16 bit knoppen         |       -       | Aansturing van de boodcomputer met een 16 bit knoppen panneel... n.t.b. hoe dit gaat werken
     * 194 :  8 bit controller      |       -       | n.t.b. spel controller met 8 knoppen
     * 211 : 16 bit controller      |       -       | n.t.b. spel controller met 16 knoppen
     * 147 : 16 bit Schakel module  |  16 knoppen
     * 
     */
    int cnt = 0;
    int I;
    bool eind = false;
    bool verbonden = true;
    byte factor;
    char A;
    char L;
    // Stap 1 is uitzoeken hoeveel hardware er is aangesloten

    tft.println("  IO detectie");
    tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);

    // Serial.println();
    // Serial.println(Serial.available());

    unsigned long timeout = 5000;

    unsigned long laatste = millis();
    delay(100);
    // Start maken in communiceren met de Seriele module door het versie nummer op te vragen.
    // De verwachte response is een 'V' gevolgd door de versie aanduiding welk niet gespecificeerd is als 1 println statement.'
    Serial.print("AT+MODUS=d");
    Serial.println("");
    // Serial.println("IOV");
    while ((!Serial.available() > 0) && (laatste + timeout > millis())) {
      delay(50);
    }

    if (!Serial.available() > 0) {
      tft.setTextColor(kleur_rood);
      tft.println("  IO module niet (goed) aangesloten");
      tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
      verbonden = false;
      tft.setTextColor(kleur_wit);
    } else {
      if (Serial.read() == 'V') {
        tft.print("  Seriele moduele versie: ");
        while (Serial.available()) {
          A = Serial.read();
          tft.print(A);
        }
        tft.println();
        tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
      } else {
        tft.setTextColor(kleur_rood);
        tft.println("  Onverwachte reactie");
        tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
        verbonden = false;
        tft.setTextColor(kleur_wit);
      }

    }

    if (verbonden) {
      // Kijken hoeveel aparaten (met ID chip) zijn aangesloten door telkens 8 nullen te sturen. Zolang het antwoord een variatie is van 0 en 1 is er een aparaat aangesloten.
      // Beginnen om kenbaar te maken dat ik ID's verwacht door IOD (D van detectie) te sturen.
      // De verwacte eerste response is 'D'. Deze moet eerst komen als check dat begrepen is dat het om ID's gaat en niet in Inputs.
      Serial.print("IOD");
      laatste = millis();
      while ((!Serial.available() > 0) && (laatste + timeout > millis())) {
        delay(50);
      }
      if ((Serial.available()) && (Serial.read() == 'D')) {
        while (eind == false) {
          Serial.print("00000000");
          delay(100);
          eind = true;
          I = 0;
          laatste = millis();
          A = '2';
          factor = 1;

          while ((I < 8) && (laatste + timeout > millis())) {
            if (Serial.available() > 0) {
              while (Serial.available()) {
                L = A;
                A = Serial.read();
                if ((A == '0') || (A == '1')) {
                  laatste = millis();
                  I++;
                  if (((L == '0') & ( A == '1')) | ((L == '1') & ( A == '0'))) {
                    eind = false;
                  }
                  if (A == '1') {
                    io_detectie[cnt+1] = io_detectie[cnt+1] + factor;
                  }
                  factor = factor * 2;
                }
              }
            }
          }
          if (eind == false) {
            cnt ++;
          }
        }
      }
      Serial.println("");
      tft.print("  ");
      tft.print(cnt);
      tft.println(" aparaten gevonden:");
      tft.setCursor(tft.getCursorX(), tft.getCursorY()+5);
      tft.print("  ");
      io_detectie[0] = cnt;
      for (int i = 0; i < cnt; i++) {
        if (i > 0){
          tft.print(", ");
        }
        
        if (io_code_naar_naam(io_detectie[i+1]) != "") {
          tft.setTextColor(tft.color565(150, 150, 150));
          tft.print(io_detectie[i+1]);
          tft.print(" (");
          tft.setTextColor(kleur_wit);
          tft.print(io_code_naar_naam(io_detectie[i+1]));
          tft.setTextColor(tft.color565(150, 150, 150));
          tft.print(")");
          tft.setTextColor(kleur_wit);
        } else {
          tft.print(io_detectie[i+1]);
        }
      }
    }
  }

  void io() {
    Serial.println("");
    delay(10);
    // Serial.print("IO");
    char invoer;
    bool tmp_status;
    int i_uit;
    int i_in;

    // // TIJDELIJK VOOR DEBUGEN
    // fillRect(0, 0, 200, 60, kleur_zwart);
    // tft.setTextSize(1);
    // tft.setTextColor(kleur_wit);
    // tft.setCursor(20, 10);
    // tft.print("IO: ");

    while (Serial.available()){
      // Leeg maken van oude communicatie
      invoer = Serial.read();
      // tft.print(invoer);
    }
    // tft.print(" -- ");

    if (!io_actief){
      io_actief = true;
      for (int i = 0 ; i < io_cnt ; i++) {
          
        i_uit = io_cnt - (i+1);
        i_in = i;
        // tft.print(i);
        // tft.print('[');

        if ((io_output[i_uit] == 1) || (io_output[i_uit] == 2) || (io_output[i_uit] == 5)) { // 1 = aan, 2 = inv. uit, 5 = inv geblokkeerd
          Serial.print('1');
          // tft.print('1');
        } else { // 0 = uit, 3 = inv aan, 4 = geblokkeerd
          Serial.print('0');
          // tft.print('0');
        }
        delay(25);
        invoer = ' ';
        int r = 1;
        bool draaien = true;
        bool antwoord = false;
        while (draaien) {
          if (Serial.available()) {
            invoer = Serial.read();
            if ((invoer == '0') || (invoer == '1')){
              draaien = false;
              antwoord = true;
            } else {
              // tft.print(invoer);
              delay(5);
            }
          } else {
            // tft.print('.');
            delay(5*r);
          }
          r++;
          if (r >= 20) {
            if (!antwoord){
              if (Serial.available()){
                invoer = Serial.read();
                draaien = false;
                antwoord = true;
              }
            }
          }
        }
        
        if (antwoord){
          // invoer = Serial.read();
          // // DEBUG
          // tft.print(invoer);
          if (invoer == '1') {
            tmp_status = true;
          } else if (invoer == '0') {
            tmp_status = false;
          } else {
            tmp_status = false;
            // tft.print("!");
            while (Serial.available()){
              invoer = Serial.read();
              tft.print(invoer);
            }
          }
          // Controleren of de invoer is gewijzigd. Dit wel in de gewone volgorde omdat dit binnen komend signaal is.
          if (tmp_status != io_input[i_in]) {
            // Bij een wijziging vaststellen dat deze is gewijzigd en ook de aanpassing opslaan
            io_gewijzigd[i_in] = true;
            io_input[i_in] = tmp_status;
            // io_meeschakelen(i_in);
          }
        } else {
          // DEBUG
          // tft.print('?');
        }
        // tft.print(']');
      }
      delay(10);
      Serial.println("");
      
      io_gecheckt = millis();
      io_actief = false;
    }
  }

  void io_reset_alert(){

  }

#else
  /* Wanneer er eigen hardware wordt gebruikt is mijn 10 pins seriele poort wel beschikbaar.
   * Dan kan er gelijk gebruik worden gemaakt van de standaard communicatie wat veel enorm vereenvoudigd.
   */
  
  void io_boot() {
    pinMode(HC_PCK, OUTPUT);
    pinMode(HC_SCK, OUTPUT);
    pinMode(HC_IN, INPUT);
    pinMode(HC_UIT, OUTPUT);
    pinMode(HC_ID, INPUT);
  }
  
  void io_detect() {
    /* Deze functie zorgt er vopor dat wordt gedetecteerd welke externe hardware overal is aangesloten.
     * Dit is een vrij complexe taak en zal zonder meer veel tweaken vragen.
     * Alle randapparatuur heeft een ID code ter grootte van 8 bit (1 byte) dat kan worden uitgelezen
     * Nog niet alles is uitgedacht en getest, maar op het moment is het handig uit te gaan van de volgende codes:
     *
     * ID  :   Naam                 |  Registratie  |   Omschrijving (primaire) doel
     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     *   2 : 8 bit logische module  |   8 sensoren  | Ontvangst logisch voltage sensoren (kan ook voor aansturen logisch voltage aparaten worden gebruikt)
     *  50 : 8 bit hub              |       -       | Schakelt tussen verschillende uitgangen. Bij deze moduele moeten alle uitgangen worden bekeken wat hier achter zit.
     *  51 : Analoge hub            |       -       | Schakelt analoog 1 poort van de MCU analoog door zodat een analoge input of output van een andere bijvoorbeeld sensor kan worden geregistreerd.
     *  52 : uart hub               |       -       | Schakelt direct 2 poorten van de MCU analoog door zodat bijvoorbeeld de uart naar een ander aparaat kan linken.
     *  66 : 8 bit communicatie     |       -       | Communicatie tussen 2 boordcomputers. Moet nog een protocol voor komen. Deze items overslaan in het overzicht.
     * 130 : 8 bit Schakel module   |   8 knoppen   | Aansturen aparaten (ook voor 12 volt sensoren te gebruiken)
     -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     *   3 : 16 bit logische module |  16 sensoren
     *  83 : 16 bit communicatie    |       -       | Communicatie tussen 2 boordcomputers. Moet nog een protocol voor komen
     *  98 :  8 bit knoppen         |       -       | Aansturing van de boodcomputer met een 8 bit knoppen panneel... n.t.b. hoe dit gaat werken
     * 115 : 16 bit knoppen         |       -       | Aansturing van de boodcomputer met een 16 bit knoppen panneel... n.t.b. hoe dit gaat werken
     * 194 :  8 bit controller      |       -       | n.t.b. spel controller met 8 knoppen
     * 211 : 16 bit controller      |       -       | n.t.b. spel controller met 16 knoppen
     * 147 : 16 bit Schakel module  |  16 knoppen
     * 
     */
    

  }

  void io() {

    if (io_actief == false) {

      io_actief = true;
  
      bool tmp_status;
      int i_uit;
      int i_in;
      // int i_in_ = 0;
      // int i_in__ = -1;
    
      // Paralelle klokslag geven
      digitalWrite(HC_PCK, LOW);
      delay(10);
      digitalWrite(HC_PCK, HIGH);
      // delay(10);
        
      // digitalWrite(HC_ID, LOW);
    
      // Nu het paralelle gedeelte geklokt heeft de data serieel uitsturen en uitlezen
      for (int i = 0 ; i < io_cnt ; i++) {
    
        // Seriele klok laag
        digitalWrite(HC_SCK, LOW);
        delay(1);
        
        i_uit = io_cnt - (i+1);
        i_in = i;
        
        // Gewenste object zenden (in omgekeerde volgorde)
        if ((io_output[i_uit] == 1) || (io_output[i_uit] == 2) || (io_output[i_uit] == 5)) { // 1 = aan, 2 = inv. uit, 5 = inv geblokkeerd
          digitalWrite(HC_UIT, HIGH);
        } else { // 0 = uit, 3 = inv aan, 4 = geblokkeerd
          digitalWrite(HC_UIT, LOW);
        }
        
        // Invoer lezen
        tmp_status = digitalRead(HC_IN);
        // Controleren of de invoer is gewijzigd. Dit wel in de gewone volgorde omdat dit binnen komend signaal is.
        if (tmp_status != io_input[i_in]) {
          // Bij een wijziging vaststellen dat deze is gewijzigd en ook de aanpassing opslaan
          io_gewijzigd[i_in] = true;
          io_input[i_in] = tmp_status;
          // io_meeschakelen(i_in);
        }
    
        delay(1);
        // Seriele klok hoog
        digitalWrite(HC_SCK, HIGH);
        delay(1);
      
      }
    
      // Paralelle klokslag geven
      digitalWrite(HC_PCK, LOW);
      delay(10);
      digitalWrite(HC_PCK, HIGH);

      io_actief = false;
      io_gecheckt = millis();
    
    }
  }

  void io_reset_alert(){

  }

#endif

void io_schakel(int knop) {
  if (io_output[io_knoppen[knop]] == 0) {
    // uit wordt aan
    io_output[io_knoppen[knop]] = 1;
    knoppen_status[knop] = 1;
  } else if (io_output[io_knoppen[knop]] == 1) {
    // aan wordt uit
    io_output[io_knoppen[knop]] = 0;
    knoppen_status[knop] = 0;
  } else if (io_output[io_knoppen[knop]] == 2) {
    // uit wordt aan (maar dan voor de omgekeerde schakeling)
    io_output[io_knoppen[knop]] = 3;
    knoppen_status[knop] = 1;
  } else if (io_output[io_knoppen[knop]] == 3) {
    // aan wordt uit (maar dan voor de omgekeerde schakeling)
    io_output[io_knoppen[knop]] = 2;
    knoppen_status[knop] = 0;
  }
  knop_plaatsen(knop);
  io();
  delay(50);
  io();
}

int io_output_status(byte output) {
  /* Deze functie zet de io_output (0 - 5) om in de weer te geven status (0 - 2) */
  
  if (output == 0) {
    return 0;
  } else if (output == 1) {
    return 1;
  } else if (output == 2) {
    return 0;
  } else if (output == 3) {
    return 1;
  } else if (output == 4) {
    return 2;
  } else if (output == 5) {
    return 2;
  }
  return 99;
}

void io_set_defaults(){
  delete[]io_objecten;
  delete[]io_object_ruimte;
  delete[]io_output;
  delete[]io_input;
  delete[]io_gewijzigd;
  delete[]io_open_alert;
  delete[]io_namen;
  delete[]io_sd;
  delete[]io_events;
  
  int cnt = 24;
  io_knoppen_cnt = 10;
  // int cnt = 8;
  // io_knoppen_cnt = 4;
  io_cnt = cnt;
  io_objecten = new byte[cnt];
  io_object_ruimte = new byte[cnt];
  io_output = new byte[cnt];
  io_input = new bool[cnt];
  io_gewijzigd = new bool[cnt];
  io_open_alert = new bool[cnt];
  io_alert = new byte[cnt];
  io_namen = new char*[cnt];
  io_knoppen = new int[io_knoppen_cnt];
  
  for (int i = 0 ; i < io_cnt ; i++) {
    io_namen[i] = new char[11];
  }
  io_events = new byte***[io_cnt];
  for (int i = 0; i < io_cnt; i++) {
    io_object_ruimte[i] = 255;
    io_events[i] = new byte**[2];
    for (int j = 0; j < 2; j++) {
      io_events[i][j] = new byte*[2];
      for (int k = 0; k < 2; k++) {
        io_events[i][j][k] = new byte[10];
        for (int l = 0; l < 10; l++) {
          io_events[i][j][k][l] = 255;
        }
      }
    }
  }
  
  for (int nr = 0; nr < cnt; nr++){
    io_objecten[nr] = 0;
    io_output[nr] = 0;
    io_input[nr] = 0;
    io_alert[nr] = 3;
    io_namen[nr] = "?         ";

    if (nr < 3) {
      io_objecten[nr] = 3;
      io_knoppen[nr] = nr;
      
    }
    if (nr == 0){
      io_namen[nr] = "**USB    ";
    } else if (nr == 1) {
      io_namen[nr] = "**230    ";
    } else if (nr == 14){
      io_knoppen[3] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_hek";
    } else if (nr == 16){
      io_knoppen[4] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_anker";
    } else if (nr == 17){
      io_knoppen[5] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_navi ";
    } else if (nr == 18){
      io_knoppen[6] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_3kl  ";
    } else if (nr == 19){
      // io_objecten[nr] = 3;
      io_namen[nr] = "**I_licht";
    } else if (nr == 20){
      io_knoppen[7] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_dek  ";
    } else if (nr == 22){
      io_knoppen[8] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**L_stoom";
    } else if (nr == 23){
      io_knoppen[9] = nr;
      io_objecten[nr] = 3;
      io_namen[nr] = "**tv     ";
    }
  }
}