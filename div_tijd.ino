#ifdef ESP32

  void internet_tijd(){
    timeClient.begin();
    timeClient.update();
  }

  String tijd() {
    return tijd("HM");
  }

  String tijd(String wat){
    timeClient.update();
    if (wat == "HM"){
      String uit = timeClient.getFormattedTime();
      uit = uit.substring(0, 5);
      return uit;
    }
    return "..:..";
  }

#else

  void internet_tijd() {
    return;
  }

  String tijd() {
    return tijd("HM");
  }

  String tijd(String wat) {
    /* Deze functie update de laatste wifi ontvangen tijd met de verstreken mili secondes en corrigeerd deze naar de tijdzonde.
    Vervolgens wordt een String van de tijd terug gegeven om elders te kunnen gebruiken */

    long mili_buffer = millis();
    seconde = seconde + ((mili_buffer - tijd_millis) / 1000);
    if ((tijdzone == "GMT") || (tijdzone.substring(0, tijdzone.length()-1) == "GMT")) {
      uur++;
      tijdzone = "GMT +1";
    }
    tijd_millis = mili_buffer;
    int buffer = seconde / 60;
    minuut = minuut + buffer;
    seconde = seconde - buffer * 60;
    buffer = minuut / 60;
    uur = uur + buffer;
    minuut = minuut - buffer * 60;
    buffer = uur / 60;
    uur = uur - buffer * 60;

    while (uur >= 24) {
      dag++; // Dag is plus 1. Omdat dit aan het einde van de maand niet klopt gaat het niet perfect, maar dit wordt gereset zodra er een app wordt verstuurd.
      uur -= 24;
      dagnm = ""; // Nog een functie maken om de dagnaam te veranderen. Voor nu omdat deze niet meer klopt weg halen
    }

    String response;
    if (wat.indexOf("H") > -1) {
      response += String(uur) + ":";
      if (wat.indexOf("M") > -1) {
        if (String(minuut).length() == 1) {
          response += "0";
        }
        response += String(minuut) + ":";
        if (wat.indexOf("S") > -1) {
          if (String(seconde).length() == 1) {
            response += "0";
          }
          response += String(seconde) + ":";
        }
      }
      response = response.substring(0, response.length()-1);
      if (wat.indexOf("Z") > -1) {
        // response += " " + tijdzone;
      } else if (wat.indexOf("uur") > -1) {
        response += " uur";
      }
    }
    
    return response;
  }

  long millis_wekker(int H, int M) {
    /* Deze functie op welke millis() het een gewenste tijd is om een timer te kunnen zetten... erg handig (denk ik)*/

    // Tijd aanroepen zodat ook de tijdzone wordt gecorrigeerd
    tijd();

    // Tijd bepalen tot de triger sinds de laatste meting
    int sec = 60 - seconde;
    int min = 60 - minuut + M - 1; // Oorspronkelijk nog -1, maar omdat het bericht nu 1 minuut te vroeg verstuurd werd deze verwijderd.
    int hr = 24 - uur + H - 1;
    
    // Correctie voor een volle minuut, uur of dag
    while (sec >= 60) {
      sec -= 60;
      min++;
    }
    while (min >= 60) {
      min -= 60;
      hr++;
    }
    while (hr >= 24) {
      hr -= 24;
    }

    // Omzetten in te verstrijken milli seconden
    return tijd_millis + (hr * 3600000) + (min * 60000) + (sec * 1000);
  }

  long millis_timer(int H, int M, int S) {
    /* Deze heel eenvoudige functie zet een millis timer voor over een bepaalde tijd */
    return millis() + (H * 3600000) + (M * 60000) + (S * 1000);
  }

  String tijd_tot_millis(long invoer) {
    long tijd = invoer - millis();
    int sec = tijd / 1000;
    if (sec < 60) {
      return String(sec) + " seconde";
    }
    
    int min = sec / 60;
    sec = sec - min * 60;
    if (sec < 0) {
      sec += 60;
      min--;
    }
    if (min < 60) {
      return String(min) + " minuten, " + String(sec) + " seconde";
    }

    int uur = min / 60;
    min = min - uur * 60;
    if (uur < 24) {
      return String(uur) + " uur, " + String(min) + " minuten";
    }

    int dag = uur / 24;
    uur = uur - dag * 24;
    return String(dag) + " dagen, " + String(uur) + " uur";
  }

#endif