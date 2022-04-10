// prototype functions
void getOutOfCorner();
bool isInCorner();
int directionBehindBall(int *);

// ballDirection | ball directions (IR) are from -7 to 8 -> 16 directions
// direction     | driving directions (motor) are from -3 to 4 -> 8 directions

void getData() {
  readCan();
  readPixy();
  readButton();
  readLightbarrier();
}

void altAction() {
  int speed = 0;
  int direction = directionBehindBall(&speed);

  if (ballVisible) {
    if (kickOff) {
      // nur effektiv wenn bot seitlich gestellt wird, damit er eine kurve um
      // den gegner macht
      kickOff = false;
      igitBot.drive(0, 75, goalDirection / -2);
      igitBot.wait(500);
    }

    else {
      if (isInCorner()) {
        getOutOfCorner();
      } else {
        if (gotBall) {
          if (goalDirection < 10 && goalDirection > -10 && gotBall && goalVisible) {
            // bot ist mit ball zum Tor gerichtet
            igitBot.drive(0, SPEED_PERCENT, 0);
            igitBot.kick(KICK_TIME);
          } else {
            // bot hat ball, guckt aber nicht direkt zum tor oder ist weit weg
            igitBot.drive(0, 60, goalDirection / -2);
          }
        } else {
          // ball nicht in Ballschale
          igitBot.drive(directionBehindBall(nullptr), 30, igitBot.compass() / -5);
        }
      }
    }
  } else {
    // ball wird nicht gesehen
    igitBot.drive(0, 0, goalDirection / -1);
  }
}

void action() {
  int direction = 0;
  int speed = 0;
  int turn = 0;
  // bool shouldKick = false;

  // shouldKick = (gotBall && goalDirection == 0); //only kick if goal is straight forward and bot
  // has ball

  int whatWeWorkWith = ballDirection;
  // if ball is invisible take the average of the last n directions the ball was
  // if (!ballVisible) {
  //   whatWeWorkWith =
  //       average(lastBallDirections, sizeof(lastBallDirections) / sizeof(lastBallDirections[0]));
  // }

  // aspired situation: drive with max speed to ball right in front of bot
  // clang-format off
  switch (abs(whatWeWorkWith)) {
    case 0: direction = 0; speed = 100;  break;
    case 1: direction = 2; speed = 60;   break; // works this better??
    case 2: direction = 2; speed = 50;   break;
    case 3: direction = 2; speed = 60;   break;
    case 4: direction = 3; speed = 60;   break;
    case 5: direction = 3; speed = 80;   break;
    case 6: direction = 4; speed = 80;   break;
    case 7: direction = 4; speed = 80;   break;
    case 8: direction = -2; speed = 100; break;
  }
  // clang-format on

  if (whatWeWorkWith < 0) direction = -direction;
  // left or right einbauen

  /* CORNER-SPECIFIC THINGS (eCkEnPrOgRaMm) */

  // solange der bot das tor sieht ~~(oder den ball nicht in der schale hat
  // steht er nicht in der ecke
  if (goalVisible) {
    cornerTimer = 0;
    turn = goalDirection;  // wenn Pixy tor sieht in torrichtung drehen
  } else {
    if (isInCorner()) {
      getOutOfCorner();
    }
    // if (cornerTimer > 1000 && abs(igitBot.compass()) < 20) {  // steht in ecke
    //   if (goalSide == Right)
    //     turn = 7;
    //   else
    //     turn = -7;
    //   speed = 0;
    //   direction = 0;
    //   // direction:0, spd:0, turn:+/-7 => bot dreht sich auf der stelle richtung tor
    // } else {  // nicht in ecke aber tor wird nicht gesehen
    //   // speed = 40;
    //   if (whatWeWorkWith == 0)
    //     turn = 0;
    //   else
    //     turn = (-igitBot.compass() / 5) /*-(side(direction*2)*10)*/;
    // }
  }

  igitBot.drive(direction, (speed * SPEED_PERCENT) / 100, turn);
  /*
    if (shouldKick) {
      igitBot.kick(KICK_TIME);
    }
    */
  if (ballVisible) {
    // shift all array values left by one cell
    size_t lastValuesLength = sizeof(lastBallDirections) / sizeof(int);

    for (int i = 1; i < lastValuesLength; i++) {
      lastBallDirections[i - 1] = lastBallDirections[i];
    }

    // set the most rightest value to the current ball direction
    lastBallDirections[lastValuesLength - 1] = ballDirection;
  }
}

void getOutOfCorner() {
  if (goalDirection > 0) {
    if (igitBot.compass() > -20) {
      igitBot.drive(0, 0, side(goalDirection) * -15);
    } else {
      igitBot.drive(0, 55, side(goalDirection) * -15);
    }
  } else {
    if (igitBot.compass() < 20) {
      igitBot.drive(0, 0, side(goalDirection) * -15);
    } else {
      igitBot.drive(0, 55, side(goalDirection) * -15);
    }
  }
}

bool isInCorner() { return (ballDirection == 0 && cornerTimer > 1000); }

Direction sideOfBot() {
  if (gotBall) {
    if (igitBot.compass() != 0) {
      return igitBot.compass() < 0 ? Direction::Left : Direction::Right;
    } else {
      return Direction::Front;
    }
  } else {
    if (goalDirection != 0)
      return goalDirection < 0 ? Direction::Left : Direction::Right;
    else
      Direction::Front;
  }
}

int directionBehindBall(int *speed) {
  *speed = 50;
  // if (ballDirection != lastBallDirection) {
  //   lastBallDirection = ballDirection;
  //   sameBallDirection = 0;
  // }
  switch (ballDirection) {
    case 0:
      *speed = 50;
      return 0;

    case 1:
      *speed = 45;
      return 2;
    case -1:
      *speed = 45;
      return -2;

    case 2:
      *speed = 40;
      return 4;
    case -2:
      *speed = 40;
      return -4;

    case 3:
      *speed = 40;
      return 4;
    case -3:
      *speed = 40;
      return -4;

    case 4:
      *speed = 40;
      return 4;
    case -4:
      *speed = 40;
      return -4;

    case 5:
      *speed = 50;
      return 6;
    case -5:
      *speed = 50;
      return -6;

    case 6:
      *speed = 60;
      return 8;
    case -6:
      *speed = 60;
      return 8;

    case 7:
      *speed = 50;
      return -6;
    case -7:
      *speed = 50;
      return 6;

    case 8:
      *speed = 60;
      switch (sideOfBot()) {
        case Direction::Right:
          // links über mitte fahren
          return -6;
        case Direction::Left:
          // rechts über mitte fahren
          return 6;
      }
  }
}