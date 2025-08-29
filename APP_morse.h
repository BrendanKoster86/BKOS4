bool morse_actief = false;

int morse_delay_lang = 1000;
int morse_delay_kort = 150;
int morse_delay_letter = 750;
int morse_delay_woord = 1750;

void app_morse(String);
void bouw_morse();
void run_morse();

int aantal_morse_woorden = 3;

int morse_knoppen_positie[5][4] = {{10,80,220,40}, {10,130,220,40}, {10,180,220,40}, {10,230,220,40}, {10,280,220,40}};
char morse_woorden[5][11] = {"SOS       ", "Paard     ", "Westerly  "};

char morse_woord[11];


#define cnt_morse_pooorten   8
int morse_poorten[cnt_morse_pooorten] {0, 1, 2, 3, 4, 5, 6, 7};