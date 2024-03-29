IGITBot igitBot = IGITBot();

Pixy2I2C pixy;

#define SPEED_PERCENT 100

bool ballVisible = false;
int ballDirection = 0;
int ballDir_drivable = 0;

bool goalVisible = false;
bool ownGoalVisible = false;
int goalDirection = 0;
int goalDist = 0;

bool play = false;
bool gotBall = false;

int lastBallDirections[5] = {0, 0, 0, 0, 0};

#define LIGHTBARRIER 35

GameState gamestate;

enum Direction { Right = 1, Left = -1 };

Direction goalSide;

elapsedMillis cornerTimer = 0;

bool kickOff = false;
elapsedMillis kickOffTimer = 0;
bool lastKickOffButton = false;

elapsedMillis signatureButtonTimer = 0;
bool lastSignatureButton = false;

#define KICK_TIME 20

// BluetoothSerial SerialBT;