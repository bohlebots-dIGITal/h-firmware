
BohleBots igitBot = BohleBots();

Pixy2I2C pixy;

#define MAX_SPEED 60

boolean ball_seen = false;
int ballDir = 0;
int ballDir_drivable = 0;

boolean goal_seen = false;
int goalDir = 0;
int goalDist = 0;

boolean play = false;
boolean gotBall = false;

#define EEPROM_SIZE 64
#define LIGHTBARRIER 35
