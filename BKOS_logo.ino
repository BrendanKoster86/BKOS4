void bkos_logo(int32_t x, int32_t y, uint32_t kleur) {
  int k = 0;
  int r = 0;
  bool teken = false;
  for (int i = 0; i < sizeof(bkos_logo_200_75)/sizeof(byte); i ++) {
    if (teken) {
      if (bkos_logo_200_75[i] > 0) {
        tft.drawLine(x+k, y+r, x+k+bkos_logo_200_75[i], y+r, kleur);
      }
      teken = false;
    } else {
      teken = true;
    }
    k += bkos_logo_200_75[i];
    if (k >= 200) {
      r += 1;
      k = 0;
    }
  }

}