//überprüft von Jannis

#include "persistence.h"
#include <CAN.h>
#include <Pixy2I2C.h>
#include "bohlebots.h"
#include "variables.h"
#include "helper_functions.h"
#include "core_functions.h"
#include "debug_functions.h"

void setup()
{
  Serial.begin(115200);
  while (!Serial); // do nothing until there is a serial connection available.

  //EEPROM.begin(sizeof(GameState));

  Serial.println("initialization of bot");
  igitBot.set_bot_type(4); // our bot has four wheels
  igitBot.init();          // bb-header
  // igitBot.setze_kompass();  // mittlerweile über Knopfdruck
  
  Serial.println("bot initialized and compass heading set");

  pixy.init();
  Serial.println("pixy initialized");

  get_gamestate(&gamestate);
  //head = gamestate.head; 

  

  Serial.println("init can");
  if (!CAN.begin(500E3))
  {
    Serial.println("can bus initialization failed - doing nothing");
    while (1)
      ;
  } // started CAN bus at 500 kbps
  else
    Serial.println("can bus started successfully.");

  pinMode(LIGHTBARRIER, INPUT);

  // rainbow
  int colors[7] = {ROT, GELB, GRUEN, CYAN, BLAU, MAGENTA, WEISS};
  for (int i = 0; i < 10; i++) {
    igitBot.led(0, 1, i < 7 ? colors[i] : AUS);
    igitBot.led(0, 2, i-1 > 0 && i < 8 ? colors[i-1] : AUS);
    igitBot.led(3, 1, i-2 > 0 && i < 9 ? colors[i-2] : AUS);
    igitBot.led(3, 1, i-3 > 0 ? colors[i-3] : AUS);
    delay(100);
  }

  igitBot.led(0, 1, GRUEN);
  igitBot.led(3, 1, MAGENTA); //magenta cuz we dont want to irritate the other bots
  // für kompass-taster-lampe das gleiche
}

void loop()
{

  getData(); // reads out data from hardware 
  if (gamestate.playing)
    action(); // process data and act based on that
  else
    igitBot.fahre(0, 0, 0);
 
 debugOutput(25); // prints important values (measured/calculated) to serial monitor every nth loop run

  igitBot.warte(10); // prevents that esp runs too fast for can, i2c, pixy, etc.
  // tasterKram();
  // motorTest();
}
