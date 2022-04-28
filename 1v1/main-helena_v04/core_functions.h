
void getData() {
  readCan();
  readPixy();
}

void action() {
  if(!ball_seen) igitBot.fahre(0,0,0);
  else {
    int dir = 0;
    int spd = 0;
    int turn = 0;

    if(ballDir == 0) {
      dir = 0;
      spd = MAX_SPEED;
    }
    else if(abs(ballDir) <= 6) {
      dir = 0;
      if(abs(ballDir) <= 2) dir = ((ballDir+1)/2) + (side(ballDir)*2);
      else                  dir = ((ballDir+1)/2) + (side(ballDir)*3);
      dir = keep_direction_drivable(dir);
      spd = MAX_SPEED*0.7;
    }
    else {
      dir = ((ballDir+1)/2) + (side(ballDir)*2);
      //if way you wanna drive is not the way you calculated => just flip the side
      if((dir / drive_left_or_right()) < 0) dir = -dir; 
      dir = keep_direction_drivable(dir);
      spd = MAX_SPEED*0.8;
    }
    /*switch(ballDir) {
      case -7: dir = -4; spd = 35; break;
      case -6: dir = -4; spd = 35; break;
      case -5: dir = -3; spd = 35; break;
      case -4: dir = -3; spd = 35; break;
      case -3: dir = -2; spd = 30; break;
      case -2: dir = -2; spd = 30; break;
      case -1: dir = -1; spd = 25; break;
      case  0: dir =  0; spd = 50; break;
      case  1: dir =  1; spd = 25; break;
      case  2: dir =  2; spd = 30; break;
      case  3: dir =  2; spd = 30; break;
      case  4: dir =  3; spd = 35; break;
      case  5: dir =  3; spd = 35; break;
      case  6: dir =  4; spd = 35; break;
      case  7: dir =  4; spd = 35; break;
      case  8: 
        dir = 2; //evaluate if to drive left or right based on comparison between cmps and pixy
        spd = 30; 
        break;
    }*/

    if(goal_seen) turn = goalDir;
    else          turn = -igitBot.kompass()/5;

    igitBot.fahre(dir,spd,turn);
  }
}
