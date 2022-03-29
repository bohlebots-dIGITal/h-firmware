
void debug_SerialOutput() {
  Serial.printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n"
                "ball visible:               %s\n"
                "ball direction:             %02d\n"
                "last ball directions (avg): %d\n"
                "last ball directions:       [ %02d %02d %02d %02d %02d ]\n"
                "got ball:                   %s\n\n"

                "goal visible:               %s\n"
                "goal direction:             %d\n"
                "compass:                    %d\n\n"

                "goal side:                  %d\n"
                "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n",
                ballVisible ? "true" : "false", ballDirection,
                average(lastBallDirections, 5), lastBallDirections[0],
                lastBallDirections[1], lastBallDirections[2],
                lastBallDirections[3], lastBallDirections[4],
                gotBall ? "true" : "false", goalVisible ? "true" : "false",
                goalDirection, igitBot.compass(), goalSide);
}

int debugCount = 0;

void debugOutput(const int &n) {
  // prints out debug info every n loop runs
  if (n <= 0)
    return;
  ++debugCount;
  if (debugCount >= n) {
    debug_SerialOutput();
    debugCount = 0;
  }
}

void tasterKram() {
  for (int i = 0; i < 8; ++i) {
    if (igitBot.button(i, 1)) {
      Serial.printf("button ( %d, 1 ) pressed\n", i);
      igitBot.led(i, 1, GREEN);
    } else
      igitBot.led(i, 1, AUS);

    if (igitBot.button(i, 2)) {
      Serial.printf("button ( %d, 2 ) pressed\n", i);
      igitBot.led(i, 2, RED);
    } else
      igitBot.led(i, 2, AUS);
  }
}

void motorTest() {
  igitBot.motor(1, 50);
  igitBot.motor(2, 0);
  igitBot.motor(3, 0);
  igitBot.motor(4, 0);
  delay(5000);
  igitBot.motor(1, 0);
  igitBot.motor(2, 50);
  igitBot.motor(3, 0);
  igitBot.motor(4, 0);
  delay(5000);
  igitBot.motor(1, 0);
  igitBot.motor(2, 0);
  igitBot.motor(3, 50);
  igitBot.motor(4, 0);
  delay(5000);
  igitBot.motor(1, 0);
  igitBot.motor(2, 0);
  igitBot.motor(3, 0);
  igitBot.motor(4, 50);
  delay(10000);
}
