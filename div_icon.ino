void drawIcon(int32_t x, int32_t y, int breedte, uint32_t kleur, byte icon_to_draw[250], int num_instructions) {
  int k = 0;
  int r = 0;
  int32_t _x = scherm_x(x);
  int32_t _y = scherm_y(y);
  bool teken = false;
  int f = 1;
  for (int i = 1; i < 10; i++) {
    
    if ((scherm_x(1) >= i) && (scherm_y(1) >= i)){
      f = i;
    }
  }
  
  for (int i = 0; i < num_instructions; i ++) {
    if (teken) {
      if (icon_to_draw[i] > 0) {
        for (int ln = 0; ln < f; ln++)
          tft.drawLine(_x+(k*f), _y+r+ln, _x+((k+icon_to_draw[i])*f), _y+r+ln, kleur);
      }
      teken = false;
    } else {
      teken = true;
    }
    k += icon_to_draw[i];
    if (k >= breedte) {
      r += f;
      k = 0;
    }
  }

}

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

void drawIconWifi10x10(int x, int y, int grootte) {
  drawIconWifi10x10(x, y, true, grootte);
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
  drawIconWifi10x10(x, y, check, 1);
}

void drawIconWifi10x10(int x, int y, bool check, int grootte) {
  if (!wifi__aangesloten) {
    drawIcon10x10(x, y, icon_wifi, tft.color565(75, 75, 75), grootte);
    drawIcon10x10(x, y, icon_kruis, tft.color565(160, 0, 0), grootte);
  } else {
    if (wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur_wit, grootte);  
      if (check) {
        wifi_check();
      }
    }
    if (!wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, tft.color565(100, 100, 100), grootte);
      drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0), grootte);
    }
  }
}

void drawIconWifi10x10(int x, int y, uint16_t kleur) {
  drawIconWifi10x10(x, y, kleur, true, 1);
}


void drawIconWifi10x10(int x, int y, uint16_t kleur, bool check) {
  drawIconWifi10x10(x, y, kleur, check, 1);
}

void drawIconWifi10x10(int x, int y, uint16_t kleur, bool check, int grootte) {
  if (!wifi__aangesloten) {
    drawIcon10x10(x, y, icon_wifi, kleur, grootte);
    drawIcon10x10(x, y, icon_kruis, tft.color565(160, 0, 0), grootte);
  } else {
    if (wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur, grootte);  
      if ((check) & (millis() > laatste_wifi_check + 30000)) {
        wifi_check();
      }
    }
    if (!wifi__verbonden) {
      drawIcon10x10(x, y, icon_wifi, kleur, grootte);
      drawIcon10x10(x, y, icon_streep, tft.color565(160, 0, 0), grootte);
    }
  }
}
