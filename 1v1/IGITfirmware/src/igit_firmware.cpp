// clang-format off
#include "persistence.h"
#include <CAN.h>
#include <Pixy2I2C.h>
// #include "BluetoothSerial.h"
#include "igit.h"
#include "variables.h"
#include "helper_functions.h"
#include "core_functions.h"
#include "debug_functions.h"
// clang-format on

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;  // we dont seem to need that
  //  do nothing until there is a serial connection available.

  // SerialBT.begin("dIGITal");
  // SerialBT.println("lollololo");

  Serial.println("initialization of bot");
  igitBot.setBotType(4);  // our bot has four wheels
  igitBot.init();

  Serial.println("bot initialized and compass heading set");

  pixy.init();
  Serial.println("pixy initialized");

  EEPROM.begin(1000);
  getGamestate(&gamestate);  // do we still need that?
  head = gamestate.head;

  Serial.println("init can");
  if (!CAN.begin(500E3)) {
    Serial.println("can bus initialization failed - doing nothing");
    while (1)
      ;
  }  // started CAN bus at 500 kbps
  else
    Serial.println("can bus started successfully.");

  pinMode(LIGHTBARRIER, INPUT);
  pinMode(KICKER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // rainbow
  int colors[] = {RED, YELLOW, GREEN, CYAN, BLUE};
  if (!gamestate.playing) {
    for (int j = 0; j < 2; j++) {
      for (int i = 0; i < 5; i++) {
        igitBot.led(0, 1, colors[i]);
        igitBot.led(0, 2, colors[i]);
        igitBot.led(3, 1, colors[i]);
        igitBot.led(3, 2, colors[i]);
        igitBot.wait(70);
      }
    }
  }
  igitBot.led(0, 1, OFF);
  igitBot.led(0, 2, OFF);
  igitBot.led(3, 1, OFF);
  igitBot.led(3, 2, OFF);

  igitBot.resetLEDs();

  igitBot.wait(1);  //

  // if (!EEPROM.begin(EEPROM_SIZE)) Serial.println("EEPROM FAILED!!!");
}

void loop() {
  getData();  // reads out data from hardware
  if (gamestate.playing) {
    igitBot.statusLEDs(ballVisible, gotBall, goalVisible, isInCorner());
    action();  // process data and act based on that
  } else
    igitBot.drive(0, 0, 0);

  debugOutput(20);  // prints important values (measured/calculated) to serial
  // monitor every nth loop run

  igitBot.wait(10);  // prevents that esp runs too fast for can, i2c, pixy, etc.
}
