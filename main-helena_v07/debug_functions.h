
void debug_SerialOutput() {
  Serial.println("//////////////////////////////////////////////");
  Serial.println("BALL:");
  Serial.println("       sees ball: "+String(ball_seen));
  Serial.println("         ballDir: "+String(ballDir));
  Serial.println("ballDir_drivable: "+String(ballDir_drivable));
  Serial.println();
  Serial.println("ORIENTATION:");
  Serial.println("       sees goal: "+String(goal_seen));
  Serial.println("         goalDir: "+String(goalDir));
  Serial.println("            cmps: "+String(igitBot.kompass()));
  Serial.println();
  Serial.println("ALGORITHMIC:");
  Serial.println(" left_or_right(): "+String(drive_left_or_right()));
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

void tasterKram(){
  for(int i=0; i<8; ++i) {
    if(igitBot.taster(i,1)) {
      Serial.println("you pressed taster("+String(i)+",1)");
      igitBot.led(i,1,GRUEN);
    }
    else igitBot.led(i,1,AUS);
    
    if(igitBot.taster(i,2)) {
      Serial.println("you pressed taster("+String(i)+",2)");
      igitBot.led(i,2,ROT);
    }
    else igitBot.led(i,2,AUS);
  }
}
