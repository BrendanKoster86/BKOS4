/*
 * Code gekopieerd van TFT_eSPI om deze toe te kunnen passen voor het kleine scherm
 */

#if DP_DRIVER == 2
  void drawEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    
    tft.drawEllipse(x0, y0, rx, ry, color);
  }
  void fillEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    tft.fillEllipse(x0, y0, rx, ry, color);
  }
#elif DP_DRIVER == 3
  void drawEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    
    tft.drawEllipse(x0, y0, rx, ry, color);
  }
  void fillEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    tft.fillEllipse(x0, y0, rx, ry, color);
  }
#elif DP_DRIVER == 1
  void drawEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
  {
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;
  
    //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//    tft.inTransaction = true;
  
    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
      // These are ordered to minimise coordinate changes in x or y
      // drawPixel can then send fewer bounding box commands
      tft.drawPixel(x0 + x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 - y, color);
      tft.drawPixel(x0 + x, y0 - y, color);
      if (s >= 0) {
        s += fx2 * (1 - y);
        y--;
      }
      s += ry2 * ((4 * x) + 6);
    }
  
    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
      // These are ordered to minimise coordinate changes in x or y
      // drawPixel can then send fewer bounding box commands
      tft.drawPixel(x0 + x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 + y, color);
      tft.drawPixel(x0 - x, y0 - y, color);
      tft.drawPixel(x0 + x, y0 - y, color);
      if (s >= 0)
      {
        s += fy2 * (1 - x);
        x--;
      }
      s += rx2 * ((4 * y) + 6);
    }
  
//    tft.inTransaction = lockTransaction;
//    tft.end_tft_write();              // Does nothing if Sprite class uses this function
  }
  
  
  /***************************************************************************************
  ** Function name:           fillEllipse
  ** Description:             draw a filled ellipse
  ***************************************************************************************/
  void fillEllipse__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;
  
    //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//    tft.inTransaction = true;
  
    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
  
      if (s >= 0) {
        s += fx2 * (1 - y);
        y--;
      }
      s += ry2 * ((4 * x) + 6);
    }
  
    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
  
      if (s >= 0) {
        s += fy2 * (1 - x);
        x--;
      }
      s += rx2 * ((4 * y) + 6);
    }
  
//    tft.inTransaction = lockTransaction;
//    tft.end_tft_write();              // Does nothing if Sprite class uses this function
  }
#endif

// Om de schaling voor de handmatige elips goed te laten gaan en het consistent te houden maar even hier een verschalings functie gemaakt
void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
  fillEllipse__(scherm_x(x0), scherm_y(y0), scherm_x(rx), scherm_y(ry), color);
}
void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, uint16_t schaal) {
  fillEllipse__(scherm_x(x0, schaal), scherm_y(y0, schaal), scherm_x(rx, schaal), scherm_y(ry, schaal), color);
}
void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
  drawEllipse__(scherm_x(x0), scherm_y(y0), scherm_x(rx), scherm_y(ry), color);
}
void drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, uint16_t schaal) {
  drawEllipse__(scherm_x(x0, schaal), scherm_y(y0, schaal), scherm_x(rx, schaal), scherm_y(ry, schaal), color);
}


void fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, int16_t kap, uint16_t schaal) {
  fillEllipse_afgekapt(x0, y0, rx, ry, color, kap, schaal);
}

void fillEllipse_afgekapt(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, int16_t kap) {
  fillEllipse_afgekapt__(scherm_x(x0), scherm_y(y0), scherm_x(rx), scherm_y(ry), color, scherm_y(kap));
}
void fillEllipse_afgekapt(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, int16_t kap, uint16_t schaal) {
  fillEllipse_afgekapt__(scherm_x(x0, schaal), scherm_y(y0, schaal), scherm_x(rx, schaal), scherm_y(ry, schaal), color, scherm_y(kap, schaal));
}

void fillEllipse_afgekapt__(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color, int16_t kap) {
  if (rx<2) return;
  if (ry<2) return;
  int32_t x, y;
  int32_t rx2 = rx * rx;
  int32_t ry2 = ry * ry;
  int32_t fx2 = 4 * rx2;
  int32_t fy2 = 4 * ry2;
  int32_t s;

  //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//    tft.inTransaction = true;

  for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++) {
    if (y0 - y <= kap){
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
    }
    if (y0 - y <= kap){
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
    }
    if (s >= 0) {
      s += fx2 * (1 - y);
      y--;
    }
    s += ry2 * ((4 * x) + 6);
  
  }

  for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++) {
    if (y0 - y <= kap){
      tft.drawFastHLine(x0 - x, y0 - y, x + x + 1, color);
    }
    if (y0 + y <= kap){
      tft.drawFastHLine(x0 - x, y0 + y, x + x + 1, color);
    }
    if (s >= 0) {
      s += fy2 * (1 - x);
      x--;
    }
    s += rx2 * ((4 * y) + 6);
  }
}
