//important:
//ballDir | ball directions (IR) are from -7 to 8 -> 16 directions
//dir     | driving directions (motor) are from -3 to 4 -> 8 directions

void getData() {
  readCan();
  readPixy();
  readTaster(); 
}

void action() {
     //only drive if ball seen
     if(!ball_seen) igitBot.fahre(4,40,0);

     else {
      int dir = 0;  //direction the bot is driving to
      int spd = 0;  //speed the bot is driving with
      int turn = 0; //additional turn the bot is making (accuracy, we never turn to the ball directly)

      //aspired situation: drive with max speed to ball right in front of bot
      switch(abs(ballDir)) {
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
      if(ballDir < 0) dir = -dir;
      //left or right einbauen
    
      if(goal_seen) turn = goalDir;
      else {
        if(ballDir == 0) turn = 0;
        else turn = (-igitBot.kompass()/5)/*-(side(dir*2)*10)*/;
      }
      

      igitBot.fahre(dir,(spd*MAX_SPEED)/100,turn);
    }
}
