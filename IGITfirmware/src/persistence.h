#pragma once
#include <EEPROM.h>

// neuen datentypen machen um weniger kopieren zu muessen
struct GameState {
  bool playing;
  int head;
  int signature;
};

void getGamestate(GameState *gamestate) { EEPROM.readBytes(0, gamestate, sizeof(GameState)); }

void setGamestate(GameState *gamestate) {
  EEPROM.writeBytes(0, gamestate, sizeof(GameState));
  EEPROM.commit();
}

void outputGamestate(GameState *gamestate) {
  getGamestate(gamestate);
  Serial.printf("heading %d, playing: %s, signature: %d\n", gamestate->head,
                gamestate->playing ? "playing" : "idle", gamestate->signature);
}
