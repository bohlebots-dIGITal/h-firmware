// TODO: determine distance to goal
#include "persistence.h"

// returns  0 if direction is in front of or behind bot
// returns  1 if direction is to the right of bot
// returns -1 if direction is to the left  of bot
int side(const int &d) {
  if (d % 4 == 0)
    return 0;
  if (d > 0)
    return 1;
  if (d < 0)
    return -1;

  return 0; // um compiler warnings zu vermeiden (wird nie erreicht)
}

int sign(const int &d) {
  // returns the VORZEICHÖÖÖN
  if (d == 0)
    return 1;
  return d / abs(d);
}

int drive_left_or_right() {
  // returns 1 for driving right
  // returns -1 for driving left

  if (!goalVisible)
    return 1; // no goal => we have to choose one way and right is the german
              // way

  int cmps = igitBot.compass();
  int c_side = 1;
  if (cmps != 0)
    c_side = cmps / abs(cmps); // every negative becomes -1 and every positive 1

  int g_side = 1;
  if (goalDirection != 0)
    g_side =
        goalDirection /
        abs(goalDirection); // every negative becomes -1 and every positive 1

  // at the sides with a centered goal => compass decides the way to drive
  // otherwise use the pixy to determine which way around
  if (abs(goalDirection) <= 30 && abs(cmps) >= 15)
    return c_side;
  else
    return g_side;
}

void readCan() {
  CAN.beginPacket(0x03, 1, true);
  CAN.endPacket();

  while (!CAN.parsePacket())
    delayMicroseconds(1);

  while (CAN.available()) {
    int irData = CAN.read();
    ballDirection = (irData / 16) - 7;
    ballDir_drivable =
        (ballDirection + side(ballDirection)) /
        2; // bohlebots header just has directions -3 to 4 as drivable
    int zone = irData % 16;

    if (zone < 1)
      ballVisible = false;
    else
      ballVisible = true;
  }
}

void readPixy() {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks == 0) {
    // pixy does not see anything
    goalVisible = false;
    return;
  }
  // if goal seen
  // the goal we are striking at is always signature 1
  if (pixy.ccc.blocks[0].m_signature == 1) {
    // signature 1 = goal we score on
    goalVisible = true;
    goalDirection = (pixy.ccc.blocks[0].m_x - 158) / 4; // ERFAHRUNG
    goalDist = pixy.ccc.blocks[0].m_y;

    if (goalDirection > 0) {
      goalSide = Right;
    } else {
      goalSide = Left;
    }
    // Serial.println("dist: "+String(goalDist));
  }

  // goal not seen
  else {
    goalVisible = false;
    // wire stuff is in pixy2 example
    Wire.beginTransmission(0x27);
    Wire.write(255 - 2);
    Wire.endTransmission();
  }
}

void readTaster() {
  if (igitBot.button(0, 1)) {
    gamestate.playing = true;
    set_gamestate(&gamestate);
    igitBot.led(0, 1, AUS);
    igitBot.led(0, 2, RED);
  }
  if (igitBot.button(0, 2)) {
    gamestate.playing = false;
    set_gamestate(&gamestate);
    igitBot.led(0, 1, GREEN);
    igitBot.led(0, 2, AUS);
  }
  if (igitBot.button(3, 1)) {
    igitBot.setCompass();
    gamestate.head = head;
    set_gamestate(&gamestate);
  }
  if (igitBot.button(3, 2)) {
    Serial.println("button 2");
  }
}

void readLightbarrier() { gotBall = (analogRead(LIGHTBARRIER) > 2000); }

int average(int arr[], size_t size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}
