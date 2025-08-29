void exterieur(String actie);
void exterieur_teken_boot(int32_t x, int32_t y, uint32_t kleur);

int exterieurscherm_knoppen_positie[10][4] = {{165,30,65,40}, {165,80,65,40}, {165,130,65,40}, {165,180,65,40}, {10,230,40,40}, {60,230,40,40}, {110,230,40,40}};
char exterieur_knoppen_namen[][10] =          {"**haven  ",   "**zeilen ",   "**motor  ",    "**anker  ",    "**USB    ",   "**230    ",  "**I_licht"};
byte exterieurscherm_status[] = {1, 0, 0, 0, 0, 0, 0};

byte exterieur_licht_variant = 0;

int32_t ext_x = 25;
int32_t ext_y = 45;