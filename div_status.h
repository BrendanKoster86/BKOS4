bool sd_connect = false;
bool scherm_bouwen = true;
bool scherm_actief = true;

bool wifi__aangesloten = false;
bool wifi__verbonden = false;

long laatste_wifi_check = millis();

void wifi_check();