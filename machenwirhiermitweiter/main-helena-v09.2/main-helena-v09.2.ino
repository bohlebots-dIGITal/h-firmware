// clang-format off
#include "persistence.h"
#include <CAN.h>
#include <Pixy2I2C.h>
#include "igit.h"
#include "variables.h"
#include "helper_functions.h"
#include "core_functions.h"
#include "debug_functions.h"
// clang-format on

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; // do nothing until there is a serial connection available.

  // EEPROM.begin(sizeof(GameState));

  Serial.println("initialization of bot");
  igitBot.setBotType(4); // our bot has four wheels
  igitBot.init();        // bb-header
  // igitBot.setCompass();  // mittlerweile über Knopfdruck

  Serial.println("bot initialized and compass heading set");

  pixy.init();
  Serial.println("pixy initialized");

  get_gamestate(&gamestate);
  // head = gamestate.head;

  Serial.println("init can");
  if (!CAN.begin(500E3)) {
    Serial.println("can bus initialization failed - doing nothing");
    while (1)
      ;
  } // started CAN bus at 500 kbps
  else
    Serial.println("can bus started successfully.");

  pinMode(LIGHTBARRIER, INPUT);

  // rainbow
  int colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 7; i++) {
      igitBot.led(0, 1, colors[i]);
      igitBot.led(0, 2, colors[i]);
      igitBot.led(3, 1, colors[i]);
      igitBot.led(3, 2, colors[i]);
      igitBot.wait(200);
    }
  }
  igitBot.led(0, 1, AUS);
  igitBot.led(0, 2, AUS);
  igitBot.led(3, 1, AUS);
  igitBot.led(3, 2, AUS);

  igitBot.led(0, 1, GREEN);
  igitBot.led(3, 1,
              MAGENTA); // magenta cuz we dont want to irritate the other bots
  // für kompass-button-lampe das gleiche
}

void loop() {

  getData(); // reads out data from hardware
  if (gamestate.playing)
    action(); // process data and act based on that
  else
    igitBot.fahre(0, 0, 0);

  debugOutput(25); // prints important values (measured/calculated) to serial
                   // monitor every nth loop run

  igitBot.wait(10); // prevents that esp runs too fast for can, i2c, pixy, etc.
}
