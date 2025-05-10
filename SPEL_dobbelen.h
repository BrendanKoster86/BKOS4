void spel_dobbelen(String actie);
void bouw_dobbelsteen();
void dobbel_ogen(int x, int y, int w, int h, int getal, int oog_kleur);
void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur);
void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur, uint16_t steen_kleur);
void dobbel_ogen(int x, int y, int w, int h, int getal, uint16_t oog_kleur, uint16_t steen_kleur, int8_t stip_grootte);
void dobbelsteen_werken();
void dobbelstenen_werpen(int aantal);
void dobbelsteen_fix_unfix(int steen, int aantal);
void yahtzee_run_scherm_1();
void run_yahtzee();
void yahtzee_teken_stenen();
void yahtzee_schore_overzicht();


byte dobbelstenen = 0;
int dobbel_knoppen[6][7] = {{10, 30, 65, 65, 255, 255, 255}, {87, 30, 65, 65, 255, 255, 255}, {165, 30, 65, 65, 255, 255, 255}, {45, 117, 65, 65, 255, 255, 255}, {130, 117, 65, 65, 255, 255, 255}, {10, 195, 220, 65}};
int dobbel_stenen[12][12][4] = {{{87, 25, 65, 65}},
                                {{45, 25, 65, 65},{130,25,65,65}},
                                {{10,25,65,65},{87,25,65,65},{165,25,65,65}},
                                {{10, 25, 45, 45},{65, 25, 45, 45},{120, 25, 45, 45},{175, 25, 45, 45}},
                                {{10, 30, 40, 40},{55, 30, 40, 40},{100, 30, 40, 40},{145, 30, 40, 40},{190, 30, 40, 40}},
                                {}, {}, {},
                                {{10, 30, 40, 40},{55, 30, 40, 40},{100, 30, 40, 40},{145, 30, 40, 40},{190, 30, 40, 40}, {10, 75, 40, 40},{55, 75, 40, 40},{100, 75, 40, 40},{145, 75, 40, 40}},
                                {}, {},
                                {{10, 30, 40, 40},{55, 30, 40, 40},{100, 30, 40, 40},{145, 30, 40, 40},{190, 30, 40, 40}, {10, 75, 40, 40},{55, 75, 40, 40},{100, 75, 40, 40},{145, 75, 40, 40},{190, 75, 40, 40}, {10, 120, 40, 40},{55, 120, 40, 40}}};
int8_t dobbel_resultaat[5] = {}; 
bool dobbel_fix[5] = {false, false, false, false, false};

bool speel_yahtzee = false;
int yahtzee_scoreblad[12][19];
int pot_yahtzee_scoreblad[19];
int yahtzee_totaal_score[12];

int select_vak;
int vak_grootte = 20;

byte worp;