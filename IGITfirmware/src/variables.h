IGITBot igitBot = IGITBot();

Pixy2I2C pixy;

#define MAX_SPEED 50

bool ballVisible = false;
int ballDirection = 0;
int ballDir_drivable = 0;

bool goalVisible = false;
int goalDirection = 0;
int goalDist = 0;

bool play = false;
bool gotBall = false;

int lastBallDirections[5] = {0, 0, 0, 0, 0};

#define LIGHTBARRIER 35

GameState gamestate;

enum Direction { Right, Left };

Direction goalSide;

elapsedMillis cornerTimer = 0;

#define KICK_TIME 20