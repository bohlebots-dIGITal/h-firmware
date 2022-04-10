#include <EEPROM.h>
byte flashByte[4] = {0, 0, 0, 0};

void readEEPROM() {
  for (int i = 0; i < 4; i++) {
    flashByte[i] = (byte(EEPROM.read(i)));
    Serial.print(String(flashByte[i]) + ", ");
    Serial.println("");
  }
}

void writeFlash() {
  flashByte[0] = gamestate.playing;
  flashByte[1] = gamestate.head / 256;  // highbyte
  flashByte[2] = gamestate.head % 256;  // lowbyte
  flashByte[3] = 0;                     // noch nicht benutzt

  for (int i = 0; i < 4; i++) {
    Serial.print(String(flashByte[i]) + ", ");
    Serial.println("");
    EEPROM.write(i, flashByte[i]);
  }
  EEPROM.commit();
}

void flash_init() {
  readEEPROM();
  if (flashByte[0] == 1) {
    gamestate.playing = true;                            // Stürmer soll sofort loslegen
    gamestate.head = flashByte[1] * 265 + flashByte[2];  //  hightbyte,lowbyte
    // flashByte[3] wird noch nicht benutzt
  }
}
