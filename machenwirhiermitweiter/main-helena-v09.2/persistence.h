// aka EEPROM
#pragma once
#include <EEPROM.h>

struct GameState {
  bool playing;
  int head;
};

void get_gamestate(GameState *gamestate) {
  EEPROM.readBytes(0, gamestate, sizeof(GameState));
}

void set_gamestate(GameState *gamestate) {
  EEPROM.writeBytes(0, gamestate, sizeof(GameState));
}

void output_gamestate(GameState *gamestate) {
  get_gamestate(gamestate);
  Serial.printf("heading %d, playing: %s\n", gamestate->head,
                gamestate->playing ? "playing" : "idle");
}
