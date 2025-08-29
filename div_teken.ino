void tekenItem(int32_t x, int32_t y, uint32_t kleur, int item_to_draw[250][2], int num_instructions) {
  bool teken = false;
  int laatste_punt[2] = {-1, -1};

  // int16_t _x;
  // int16_t _y;

  for (int i = 0; i < num_instructions; i ++) {
    if ((item_to_draw[i][0] == laatste_punt[0]) && (item_to_draw[i][1] == laatste_punt[1])) {
      if (teken) {
        teken = false;
      } else {
        teken = true;
      }
    } else if (teken) {
      tft.drawLine(scherm_x(x+laatste_punt[0]), scherm_y(y+laatste_punt[1]), scherm_x(x+item_to_draw[i][0]), scherm_y(y+item_to_draw[i][1]), kleur);
    }
    laatste_punt[0] = item_to_draw[i][0];
    laatste_punt[1] = item_to_draw[i][1];
  }
}

void tekenCircels(int32_t x, int32_t y, uint32_t kleur, int circle_to_draw[250][3], int num_instructions) {
  for (int i = 0; i < num_instructions; i ++) {
    tft.drawCircle(scherm_x(x+circle_to_draw[i][0]), scherm_y(y+circle_to_draw[i][1]), circle_to_draw[i][2], kleur);
  }
}

void tekenTeksten(int32_t x, int32_t y, uint32_t kleur, int tekst_positie[20][3], String teksten[20], int num_instructions) {
  for (int i = 0; i < num_instructions; i ++) {
    center_tekst(x + tekst_positie[i][0], y + tekst_positie[i][1], teksten[i], 1.5, kleur);
  }
}