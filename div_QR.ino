void qr_bytes(uint16_t sx, uint16_t sy, byte item[], byte px_size, uint16_t kleur1, uint16_t kleur2) {
  qr_bytes_(scherm_x(sx), scherm_y(sy), item, px_size, kleur1, kleur2);
}

void qr_bytes_(uint16_t sx, uint16_t sy, byte item[], byte px_size, uint16_t kleur1, uint16_t kleur2) {
  int i = 1;
  byte t;
  byte factor = 128;
  for (int y = 0; y < item[0]; y++) {
    for (int x = 0; x < item[0]; x++) {
      if (factor == 128) {
        t = item[i];
      }
      
      if (t >= factor) {
        tft.fillRect(sx+x*px_size, sy+y*px_size, px_size, px_size, kleur1);
        t = t-factor;
      } else {
        tft.fillRect(sx+x*px_size, sy+y*px_size, px_size, px_size, kleur2);
      }
      if (factor == 1) {
        i++;
        factor = 128;
      } else {
        factor = factor / 2;
      }

    }
    i++;
    factor = 128;
  }
}

// void qr(uint16_t sx, uint16_t sy, const char* inhoud, byte px_size) { //, uint16_t kleur1, uint16_t kleur2) {
//   qrcode.setScale(px_size);
//   qrcode.draw(inhoud, scherm_x(sx), scherm_y(sy)); //, px_size, kleur1, kleur2);
// }


// void qr(uint16_t sx, uint16_t sy, const char* inhoud, byte px_size, uint16_t kleur1, uint16_t kleur2) {
//   qr(scherm_x(sx), scherm_y(sy), inhoud, px_size, kleur1, kleur2);
// }

// void qr_(uint16_t sx, uint16_t sy, const char* inhoud, byte px_size, uint16_t kleur1, uint16_t kleur2) {
//   Serial.println('.');
//   delay(1000);

//   QRCode qrcode;
//   uint8_t qrcodeData[qrcode_getBufferSize(3)];
//   Serial.println('.');
//   delay(1000);
//   qrcode_initText(&qrcode, qrcodeData, 3, 0, inhoud);

//   Serial.println('.');
//   delay(1000);
//   digitalWrite(TFT_BL, HIGH);
//   for (uint8_t y = 0; y < qrcode.size; y++) {
//     for (uint8_t x = 0; x < qrcode.size; x++) {
//       if (qrcode_getModule(&qrcode, x, y)) {
//         Serial.print("   ");
//         tft.fillRect(sx+x*px_size, sy+y*px_size, px_size, px_size, kleur2);
//       } else {
//         Serial.print("\u2588\u2588");
//         tft.fillRect(sx+x*px_size, sy+y*px_size, px_size, px_size, kleur1);
//       }
//     }
//     digitalWrite(TFT_BL, HIGH);
//     Serial.println("  ");
//   }
// }