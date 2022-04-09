#pragma once
#include <EEPROM.h>

struct GameState {
  bool playing;
  int head;
};

void getGamestate(GameState *gamestate) { EEPROM.readBytes(0, gamestate, sizeof(GameState)); }

void setGamestate(GameState *gamestate) {
  EEPROM.writeBytes(0, gamestate, sizeof(GameState));
  EEPROM.commit();
}

void outputGamestate(GameState *gamestate) {
  getGamestate(gamestate);
  Serial.printf("heading %d, playing: %s\n", gamestate->head,
                gamestate->playing ? "playing" : "idle");
}
