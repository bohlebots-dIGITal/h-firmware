// Versuch: Implementierung EEPROM. Noch nicht getestet, kompiliert aber

#include <CAN.h>
#include <Pixy2I2C.h>
#include "bohlebots.h"
#include "variables.h"
#include "helper_functions.h"
#include "core_functions.h"
#include "debug_functions.h"
#include "my_eeprom.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) ;  // do nothing until there is a serial connection available.
  
  Serial.println("initialization of bot");
  igitBot.set_bot_type(4);  //our bot has four wheels
  igitBot.init(); //bb-header
  //igitBot.setze_kompass();  // sets kompass heading
  igitBot.led(0,1,GRUEN);
  igitBot.led(3,1,GELB);
  // für kompass-taster-lampe das gleiche
  Serial.println("bot initialized and compass heading set");

  pixy.init();
  Serial.println("pixy initialized");
  
  
  //if (!EEPROM.begin(EEPROM_SIZE)) Serial.println("failed to initialise EEPROM"); while(1);
  //eprom_init();
  //Serial.println("EEPROM initialized");
    
  Serial.println("init can");
  if (!CAN.begin(500E3)) {
    Serial.println("can bus initialization failed - doing nothing");
    while(1);
  }  // started CAN bus at 500 kbps
  else Serial.println("can bus started successfully.");

  
}

void loop() {
  
  getData();         //reads out data from hardware
  //writeEEPROM();
  if(play) action(); //process data and act based on that
  else igitBot.fahre(0,0,0);
  //tasterKram();
  debugOutput(25);   //prints important values (measured/calculated) to serial monitor every nth loop run
  
  igitBot.warte(10); //prevents that esp runs too fast for can, i2c, pixy, etc.
  //motorTest();
  
}
