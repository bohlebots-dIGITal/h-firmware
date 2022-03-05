
void debug_SerialOutput() {
  Serial.println("//////////////////////////////////////////////");
  Serial.println("sees ball: "+String(ball_seen));
  Serial.println("ballDir:   "+String(ballDir));
  Serial.println();
  Serial.println("sees goal: "+String(goal_seen));
  Serial.println("goalDir:   "+String(goalDir));
  Serial.println();
  Serial.println("cmps:      "+String(igitBot.kompass()));
  Serial.println("//////////////////////////////////////////////");
  Serial.println();
}

int debug_cnt = 0;

void debugOutput(const int& n) {
  //prints out debug info every n loop runs
  if (n <= 0) return;
  ++debug_cnt;
  if (debug_cnt >= n) {
    debug_SerialOutput();
    debug_cnt = 0;
  }
}
