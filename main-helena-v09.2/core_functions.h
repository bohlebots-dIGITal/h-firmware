//important:
//ballDir | ball directions (IR) are from -7 to 8 -> 16 directions
//dir     | driving directions (motor) are from -3 to 4 -> 8 directions

void getData() {
  readCan();
  readPixy();
  readTaster(); 
  readLightbarrier();
}

void action() {
  int dir = 0;
  int spd = 0;
  int turn = 0;
  
  int whatWeWorkWith = ballDir;
  if (!ball_seen) whatWeWorkWith = lastBallDirection;

  //aspired situation: drive with max speed to ball right in front of bot
  switch (abs(whatWeWorkWith)) {
    case  0: dir =  0; spd = 100; break;
    case  1: dir =  2; spd =  60; break;
    case  2: dir =  2; spd =  50; break;
    case  3: dir =  3; spd =  80; break;
    case  4: dir =  4; spd =  80; break;
    case  5: dir =  4; spd = 100; break;
    case  6: dir =  4; spd = 100; break;
    case  7: dir =  4; spd = 100; break;
    case  8: dir = -2; spd = 100; break;
  }
  
  if (whatWeWorkWith < 0) dir = -dir;
  //left or right einbauen

  //solange man der bot das tor sieht oder den ball nicht in der schale hat steht er nicht in der ecke
  if (goal_seen  || !gotBall) corner_timer = 0; 

  if (goal_seen) turn = goalDir; // wenn Pixy tor sieht in torrichtung drehen
  
  if (corner_timer > 1000) {  //bot steht  in der ecke
    if (goalSide == Right) turn =  7;
    else                   turn = -7;
    spd = 0;
    dir = 0;
    //dir:0, spd:0, turn:+/-7 => bot dreht sich auf der stelle richtung tor
  }
  ///////////////////////////////////////////////////////////////////////////
  // der folgende block hatte kein else um sich herum und wurde daher immer 
  // ausgefuehrt, dadurch wurden die fahre-werte des eckenprogramms sofort 
  // wieder ueberschrieben
  ///////////////////////////////////////////////////////////////////////////
  else { //tor wird nicht gesehen aber nicht in der ecke 
    spd = 40;
    if(whatWeWorkWith == 0) turn = 0;
    else turn = (-igitBot.kompass()/5)/*-(side(dir*2)*10)*/;
  }

  igitBot.fahre(dir,(spd*MAX_SPEED)/100,turn);
  if (ball_seen) {
     lastBallDirection = ballDir;
  }
}
