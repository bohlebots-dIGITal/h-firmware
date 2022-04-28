
int keep_direction_drivable(const int& d) {
  //bot is circular build with drivable directions from -3 to 4
  //==> -4 corresponds to 4
  //     6 corresponds to -2
  //     for example
  if (d >= -3 && d <= 4) return d;
  if (d < -3) return d + 8;
  if (d > 4) return d - 8;
}

int side(const int& d) {
  //returns  0 if direction is in front of or behind bot
  //returns  1 if direction is to the right of bot 
  //returns -1 if direction is to the left  of bot 
  if (d % 4 == 0) return  0;
  if (d > 0)      return  1;
  if (d < 0)      return -1;
}

int drive_left_or_right() {
  //returns 1 for driving right
  //returns -1 for driving left

  if(!goal_seen) return 1; //no goal => we have to choose one way and right is the german way
  
  int cmps = igitBot.kompass();
  int c = 1;
  if(cmps != 0) c = cmps/abs(cmps); //every negative becomes -1 and every positive 1

  int g = 1;
  if(goalDir != 0) g = goalDir/abs(goalDir);

  if(abs(goalDir) <= 30) return c;
  else                   return g;
}

void readCan() {
  CAN.beginPacket(0x03, 1, true);
  CAN.endPacket();

  while(!CAN.parsePacket()) delayMicroseconds(1);
  
  while(CAN.available()) {
    int irData = CAN.read();
    ballDir = (irData / 16) - 7;
    int zone = irData % 16;
    if (zone < 1)  ball_seen = false;
    else           ball_seen = true;
  }
}

void readPixy() {
  pixy.ccc.getBlocks();
  if(pixy.ccc.numBlocks == 0) { 
    //pixy does not see anything
    goal_seen = false;
    return;
  }

  //the goal we are striking at is always signature 1
  if(pixy.ccc.blocks[0].m_signature  == 1) { 
    //signature 1 = goal we score on
    goal_seen = true;
    goalDir   = (pixy.ccc.blocks[0].m_x-158)/4;  // ERFAHRUNG
  }
  else { 
    //pixy sees something else
    goal_seen = false;
    //wire stuff is in pixy2 example
    Wire.beginTransmission(0x27);
    Wire.write(255 - 2);
    Wire.endTransmission();
  }
}
