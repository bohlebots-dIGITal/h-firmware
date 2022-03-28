
void debug_SerialOutput() {
  Serial.printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n"
                "ball visible:   %s\n"
                "ball direction: %02d\n"
                "got ball:       %s\n\n"
                "goal visible:   %s\n"
                "goal direction: %s\n"
                "compass:        %s\n\n"
                "goal side:      %s\n"
                "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n",
                ballVisible, ballDirection, gotBall, goalVisible, goalDirection,
                igitBot.compass(), goalSide);
}

int debug_count = 0;

void debugOutput(const int &n) {
  // prints out debug info every n loop runs
  if (n <= 0)
    return;
  ++debug_count;
  if (debug_count >= n) {
    debug_SerialOutput();
    debug_count = 0;
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
