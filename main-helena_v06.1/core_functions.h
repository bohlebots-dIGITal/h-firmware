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

      //if ball is in front half of bot
      else if(abs(ballDir) <= 4) {
        //if ball is in front quarter of bot
        if(abs(ballDir) <= 2) dir = ((ballDir+1)/2)             +            (side(ballDir)*1);
        //                        dividing (correctly rounded)    offset between ballDir and driving dir to drive behind ball
        else                  dir = ((ballDir+1)/2)             +            (side(ballDir)*2);
        
        dir = keep_direction_drivable(dir); //eliminating errors with dir
        spd = MAX_SPEED*0.85; //dont drive as fast for better accuracy
      }
//I DONT GET IT
      //if ball is in back half of bot
      else {
        dir = ((ballDir+1)/2) + (side(ballDir)*2);
        
        //side returns 0 if ballDir is 8 so bot would drive dir 4
        if(ballDir == 8) dir = 3; //WHAT? could this be the error?
        //if way you wanna drive is not the way you calculated => just flip the side
        if(abs(dir) > 2 && (dir*drive_left_or_right()) < 0) 
          //dir = -dir; 
          dir = dir-5;
        
        dir = keep_direction_drivable(dir); //eliminating errors with dir
        spd = MAX_SPEED*0.8; //drive a lil faster to get behind ball quicker (its in the back so kinda far away)
      }
    
  
      if(goal_seen) turn = goalDir;
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
