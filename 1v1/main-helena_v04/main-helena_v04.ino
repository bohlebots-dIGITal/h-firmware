
#include <CAN.h>
#include <Pixy2I2C.h>
#include "bohlebots.h"
#include "variables.h"
#include "helper_functions.h"
#include "core_functions.h"
#include "debug_functions.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) ;  // do nothing until there is a serial connection available.
  
  Serial.println("initialization of bot");
  igitBot.set_bot_type(4);  // four wheels
  igitBot.init();
  igitBot.setze_kompass();  // sets kompass heading
  Serial.println("bot initialized and compass heading set");

  pixy.init();
  Serial.println("pixy initialized");
    
    
  Serial.println("init can");
  if (!CAN.begin(500E3)) {
    Serial.println("can bus initialization failed - doing nothing");
    while(1);
  }  // started CAN bus at 500 kbps
  else Serial.println("can bus started successfully.");
}

void loop() {
  getData();
  action();
  debugOutput(20);   //prints every important value to serial monitor every nth loop run
  igitBot.warte(10); //prevents that esp runs to fast for can, i2c, pixy, etc.
}
