#include "SPEL_boterkaaseneieren.h"
#include "SPEL_mijnveger.h"
#include "SPEL_dobbelen.h"

void spellen(String actie);
void spel_menu(String actie);

int spellen_cnt = 4;
void (*spellen_bibliotheek[])(String actie) = {spel_menu, spel_boterkaaseneieren, spel_mijnveger, spel_dobbelen};
int actief_spel = 0;

bool spel_actief;

byte speler_cnt = 0;
byte speler_actief = 0;
byte spel_scherm = 0;

#if RESOLUTIE == 3248 // 360 x 480
  int spel_speelveld[4] = {10, 50, 340, 340};
#else   // ili 9341  240 x 360
  int spel_speelveld[4] = {10, 50, 220, 220};
#endif