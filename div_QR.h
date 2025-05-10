// #include <QRCodeGenerator.h>
// #include <QRCodeGFX.h>

// QRCodeGFX qrcode(tft);

// void qr(uint16_t sx, uint16_t sy, const char* inhoud, byte px_size);

// void qr(uint16_t sx, uint16_t sy, String inhoud, byte px_size, uint16_t kleur1, uint16_t kleur2);
// void qr_(uint16_t sx, uint16_t sy, String inhoud, byte px_size, uint16_t kleur1, uint16_t kleur2);

void qr_bytes_(uint16_t sx, uint16_t sy, byte item[], byte px_size, uint16_t kleur1, uint16_t kleur2);
void qr_bytes(uint16_t sx, uint16_t sy, byte item[], byte px_size, uint16_t kleur1, uint16_t kleur2);

byte qr_brendanintechYT[] = {29, 254, 65, 179, 248, 130, 216, 66, 8, 186, 114, 154, 232, 186, 208, 98, 232, 186, 47, 34, 232, 130, 167, 66, 8, 254, 170, 171, 248, 0, 13, 40, 0, 251, 235, 13, 80, 44, 65, 29, 208, 155, 88, 81, 96, 181, 242, 243, 200, 94, 209, 201, 128, 164, 174, 41, 208, 47, 167, 81, 120, 77, 12, 191, 128, 91, 171, 141, 0, 177, 65, 191, 0, 150, 249, 80, 112, 185, 178, 191, 184, 162, 113, 47, 176, 0, 207, 152, 144, 254, 231, 218, 160, 130, 44, 232, 184, 186, 203, 79, 248, 186, 128, 169, 128, 186, 152, 80, 48, 130, 146, 237, 104, 254, 209, 191, 224};