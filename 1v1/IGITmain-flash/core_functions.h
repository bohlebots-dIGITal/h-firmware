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
  bool shouldKick = false;

  shouldKick = (gotBall && goalDirection == 0); 

  int whatWeWorkWith = ballDirection;
  // if ball is invisible take the average of the last n directions the ball was
  if (!ballVisible) {
    whatWeWorkWith =
        average(lastBallDirections, sizeof(lastBallDirections) / sizeof(lastBallDirections[0]));
  }

  // aspired situation: drive with max speed to ball right in front of bot
  // clang-format off
  switch (abs(whatWeWorkWith)) {
    case 0: direction = 0; speed = 100; break;
    case 1: direction = 2; speed = 60; break;
    case 2: direction = 2; speed = 50; break;
    case 3: direction = 3; speed = 80; break;
    case 4: direction = 4; speed = 80; break;
    case 5: direction = 4; speed = 100; break;
    case 6: direction = 4; speed = 100; break;
    case 7: direction = 4; speed = 100; break;
    case 8: direction = -2; speed = 100; break;
  }
  // clang-format on

  if (whatWeWorkWith < 0) direction = -direction;
  // left or right einbauen

  /* CORNER-SPECIFIC THINGS (eCkEnPrOgRaMm) */

  // solange man der bot das tor sieht ~~(oder den ball nicht in der schale hat
  // steht er nicht in der ecke
  if (goalVisible) {
    cornerTimer = 0;
    turn = goalDirection;  // wenn Pixy tor sieht in torrichtung drehen
  } else {
    if (cornerTimer > 1000) {  // steht in ecke
      if (goalSide == Right)
        turn = 7;
      else
        turn = -7;
      speed = 0;
      direction = 0;
      // direction:0, spd:0, turn:+/-7 => bot dreht sich auf der stelle richtung tor
    } else {  // nicht in ecke aber tor wird nicht gesehen
      // speed = 40;
      if (whatWeWorkWith == 0)
        turn = 0;
      else
        turn = (-igitBot.compass() / 5) /*-(side(direction*2)*10)*/;
    }
  }

  igitBot.fahre(direction, (speed * MAX_SPEED) / 100, turn);

  if (shouldKick) {
    igitBot.kick(KICK_TIME);
  }
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
