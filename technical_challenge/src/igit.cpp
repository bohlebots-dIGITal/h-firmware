#include "igit.h"

#include <Arduino.h>
// #include <BluetoothSerial.h>
#include <Pixy2I2C.h>
#include <elapsedMillis.h>

IGITBot bot;
bool playing;
Pixy2I2C pixy;
// BluetoothSerial SerialBT;
int lastSide = 1;

void follow_line();

void setup() {
  bot.setBotType(4);
  bot.init();

  // SerialBT.begin("dIGITal line follower");

  pixy.init();
  Serial.println(pixy.changeProg("line"));

  bot.led(0, 1, GREEN);
  bot.led(0, 2, RED);
}

void loop() {
  if (bot.button(0, 1)) {
    playing = true;
  } else if (bot.button(0, 2)) {
    playing = false;
  }

  if (playing) {
    bot.led(3, 1, BLUE);
    follow_line();
    // circle();
  } else {
    bot.led(3, 1, OFF);
    bot.drive(0, 0, 0);
  }

  bot.wait(1);
}

void circle() { bot.drive(4, 60, 10); }

void follow_line() {
  int8_t i;
  char buf[128];

  bot.led(3, 2, pixy.line.numVectors > 0 ? MAGENTA : OFF);

  pixy.line.getMainFeatures();
  if (pixy.line.numVectors > 0) {
    bot.drive(0, 55, (pixy.line.vectors[0].m_x0 - (78 / 2)) * 0.9);
    // SerialBT.printf("%d\n", pixy.line.vectors[0].m_x0 - (78 / 2));

    // rotate 1pi
    // ((sadf + 3) % 8) - 3

    lastSide = pixy.line.vectors[0].m_x0 > 0 ? 1 : -1;
  } else {
    bot.drive(0, 30, 6);
  }
}