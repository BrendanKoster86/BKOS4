// Includeer hier de header files van de aanwezige apps
#include "BKOS_HOME.h"
#include "BKOS_SCHAKEL.h"

#include "ota.h"
#include "wifimanager.h"

#include "APP_exterieur.h"
#include "APP_spellen.h"
#include "APP_morse.h"

#include "app_configmodus.h"



// Geef aan hoeveel apps er zijn
int app_cnt = 8;
// Zet in de lijst hieronder de apps. De eerste positie is gereserveerd voor het thuisscherm, de eerste 8 daarna worden getoont op het thuisscherm
void (*apps[])(String actie) = {thuisscherm, schakelscherm, exterieur, app_morse, spellen, configmodus, update_center, wifimanager_app};
// Het indexnummer van de app waarin wordt opgestart (als standaard, via de instellingen op de SD kaart kan dit worden overschreven.)
int actieve_app = 2;

String item_naam;
bool homeknop_actief = false;
bool homeknop_half_actief = false;

// APP INSTRUCTIES
/* 
 * De hoofd void van een app moet een String parameter "actie" hebben
 * Deze actie kan zijn:
     * bouw       :   Bouw de app
     * run        :   Draai de app
     * naam       :   tft.print(<naam van de app>)
     * icon_groot :   Teken instructies voor een icon. Vanaf de cursor positie heb je vanaf x en y plus 3 een vrij vlak van 98 bij 95 pixels (bij 320 x 240)
     * icon_klein :   Teken instructies voor een icon. Vanaf de cursor positie heb je vanaf x en y plus 2 ee crij vlak van 61 bij 45 pixels (bij 320 x 240)
 */



void app_uitvoeren();