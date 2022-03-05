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
     if(!ball_seen) igitBot.fahre(0,0,0);

     else {
      int dir = 0;  //direction the bot is driving to
      int spd = 0;  //speed the bot is driving with
      int turn = 0; //additional turn the bot is making (accuracy, we never turn to the ball directly)

      //aspired situation: drive with max speed to ball right in front of bot
      if(ballDir == 0) {
        dir = 0;
        spd = MAX_SPEED;
      }
      
      else {
        int offset = side(ballDir_drivable) * ( 1 + abs(ballDir_drivable/3) );
        
        dir = ballDir_drivable + offset;
        
        if(ballDir == 8) dir = 3*drive_left_or_right(); //WHAT? could this be the error?
        dir = keep_direction_drivable(dir); //eliminating errors with dir
        
        spd = MAX_SPEED*0.85;

        /* DEBUGGING
        Serial.println("         ballDir: "+String(ballDir));
        Serial.println("ballDir_drivable: "+String(ballDir_drivable));
        Serial.println("          offset: "+String(offset));
        Serial.println("             dir: "+String(dir));
        Serial.println();
        */
      }
    
      if(goal_seen) turn = 2*goalDir;
      else          turn = -igitBot.kompass()/5;

      igitBot.fahre(dir,spd,turn);
    }
  
//switch case-sensitive version (works kinda good, numbers should be aspired as result of calc)
    
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

}
