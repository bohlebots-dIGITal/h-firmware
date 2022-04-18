// prototype functions
void getOutOfCorner();
bool isInCorner();

// ballDirection | ball directions (IR) are from -7 to 8 -> 16 directions
// direction     | driving directions (motor) are from -3 to 4 -> 8 directions

void getData() {
  readCan();
  readPixy();
  readButton();
  readLightbarrier();
}

void action() {
  int direction = 0;
  int speed = 0;
  int turn = 0;
  bool shouldKick =
      (gotBall && goalDirection == 0);  // only kick if goal is straight forward and bot
  // has ball

  int whatWeWorkWith = ballDirection;

  // drive around enemy at start of game - bot has to be turned for it to work
  if (kickOff) {
    kickOff = false;
    igitBot.drive(0, 100, goalDirection / -2);
    igitBot.wait(500);
  } 
  else {
    // aspired situation: drive with max speed to ball right in front of bot
    // clang-format off
  switch (abs(whatWeWorkWith)) {
    case 0: direction = 0; speed = 100;  break;
    case 1: direction = 2; speed = 50;   break; 
    case 2: direction = 2; speed = 50;   break;
    case 3: direction = 2; speed = 50;   break;
    case 4: direction = 3; speed = 60;   break;
    case 5: direction = 3; speed = 80;   break;
    case 6: direction = 4; speed = 80;   break;
    case 7: direction = 4; speed = 80;   break;
    case 8: direction = -2; speed = 100; break;
  }
    // clang-format on

    if (whatWeWorkWith < 0) direction = -direction;
    /* CORNER-SPECIFIC THINGS (eCkEnPrOgRaMm) */

    // solange der bot das tor sieht ~~(oder den ball nicht in der schale hat
    // steht er nicht in der ecke
    if (goalVisible) {
      cornerTimer = 0;
      turn = goalDirection;  // wenn Pixy tor sieht in torrichtung drehen
    } else {
      if (isInCorner()) {
        getOutOfCorner();
      } else {
        turn = -igitBot.compass() / 5;
      }
    }

    igitBot.drive(direction, (speed * SPEED_PERCENT) / 100, turn);
    if (shouldKick) {
      igitBot.kick(KICK_TIME);
    }
  }
}

void getOutOfCorner() {
  if (goalDirection > 0) { //in linker ecke
    if (igitBot.compass() > -20) {
      igitBot.drive(0, 0, side(goalDirection) * 15);
    } else {
      igitBot.drive(0, 55, side(goalDirection) * 15);
    }
  } else {
    if (igitBot.compass() < 20) {
      igitBot.drive(0, 0, side(goalDirection) * 15);
    } else {
      igitBot.drive(0, 55, side(goalDirection) * 15);
    }
  }
}

bool isInCorner() { return (ballDirection == 0 && cornerTimer > 1000 && gotBall); }