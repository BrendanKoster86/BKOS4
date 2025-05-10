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
    // De verwachte response is een 'V' gevolgd door de versie aanduiding welk niet gespecificeerd is als 1 println statement.
    Serial.println("");
    Serial.println("IOV");
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
    Serial.print("IO");
    

  }

  void io_reset_alert(){

  }

#else
  /* Wanneer er eigen hardware wordt gebruikt is mijn 10 pins seriele poort wel beschikbaar.
   * Dan kan er gelijk gebruik worden gemaakt van de standaard communicatie wat veel enorm vereenvoudigd.
   */
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

  }

  void io_reset_alert(){

  }

#endif