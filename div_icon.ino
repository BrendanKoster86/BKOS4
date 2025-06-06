void drawIcon10x10(int x, int y, String icon[10], uint16_t kleur, int factor) {
  for (byte fx = 1; fx <= factor; fx++) {
    for (int i = 0; i < 10; i++) {
      for (byte fy = 1; fy <= factor; fy++) {
        for (int j = 0; j < 10; j++) {
          if (icon[i].indexOf(String(j)) > -1) {
            tft.drawPixel(scherm_x(x) + (j * factor - (fx -1)), scherm_y(y) + (i * factor - (fy -1)), kleur);
          }
        }
      }
    }
  }
}

void drawIcon10x10(int x, int y, String icon[10], uint16_t kleur) {
  drawIcon10x10(x, y, icon, kleur, 1);
  // for (int i = 0; i < 10; i++) {
  //   for (int j = 0; j < 10; j++) {
  //     if (icon[i].indexOf(String(j)) > -1) {
  //       tft.drawPixel(scherm_x(x) + j, scherm_y(y) + i, kleur);
  //     }
  //   }
  // }
}

void drawIconWifi10x10(int x, int y) {
  drawIconWifi10x10(x, y, true);
}

void drawIcon10x10(int x, int y, String icon[10], bool status) {
  drawIcon10x10(x, y, icon, status, 1);
}

void drawIcon10x10(int x, int y, String icon[10], bool status, int factor) {
  
  if (status) {
    drawIcon10x10(x, y, icon, kleur_wit, factor);
  } else {
    drawIcon10x10(x, y, icon, tft.color565(100, 100, 100), factor);
    drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0), factor);
  }
}

void drawIcon10x10(int x, int y, String icon[10], uint16_t kleur, bool status) {
  drawIcon10x10(x, y, icon, kleur);
  if (!status) {
    drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0));
  }
}

void drawIconWifi10x10(int x, int y, bool check) {
  if (!wifi__aangesloten) {
    drawIcon10x10(x, y, icon_wifi, tft.color565(75, 75, 75));
    drawIcon10x10(x, y, icon_kruis, tft.color565(160, 0, 0));
  } else {
    if (wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur_wit);  
      if (check) {
        wifi_check();
      }
    }
    if (!wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, tft.color565(100, 100, 100));
      drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0));
    }
  }
}

void drawIconWifi10x10(int x, int y, uint16_t kleur) {
  drawIconWifi10x10(x, y, kleur, true);
}
void drawIconWifi10x10(int x, int y, uint16_t kleur, bool check) {
  if (!wifi__aangesloten) {
    drawIcon10x10(x, y, icon_wifi, kleur);
    drawIcon10x10(x, y, icon_kruis, tft.color565(160, 0, 0));
  } else {
    if (wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur);  
      if ((check) & (millis() > laatste_wifi_check + 30000)) {
        wifi_check();
      }
    }
    if (!wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur);
      drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0));
    }
  }
}
