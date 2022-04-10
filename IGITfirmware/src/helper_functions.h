// TODO: determine distance to goal
#include "persistence.h"

// returns  0 if direction is in front of or behind bot
// returns  1 if direction is to the right of bot
// returns -1 if direction is to the left  of bot
int side(const int &d) {
  if (d % 4 == 0) return 0;
  if (d > 0) return 1;
  if (d < 0) return -1;

  return 0;  // um compiler warnings zu vermeiden (wird nie erreicht)
}

int sign(const int &d) {
  // returns the VORZEICHÖÖÖN
  if (d == 0) return 1;
  return d / abs(d);
}

void readCan() {
  CAN.beginPacket(0x03, 1, true);
  CAN.endPacket();

  while (!CAN.parsePacket()) delayMicroseconds(1);

  while (CAN.available()) {
    int irData = CAN.read();
    ballDirection = (irData / 16) - 7;
    ballDir_drivable = (ballDirection + side(ballDirection)) /
                       2;  // bohlebots header just has directions -3 to 4 as drivable
    int zone = irData % 16;

    if (zone < 1)
      ballVisible = false;
    else
      ballVisible = true;
  }
}

void readPixy() {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks == 0) {
    // pixy does not see anything
    goalVisible = false;
    return;
  }
  if (pixy.ccc.blocks[0].m_signature == gamestate.signature) {
    // signature 1 = goal we score on
    goalVisible = true;
    // goalDirection = (pixy.ccc.blocks[0].m_x - 158) / 4;  // ERFAHRUNG
    goalDirection = -(pixy.ccc.blocks[0].m_x - 158) / 2;
    goalDist = pixy.ccc.blocks[0].m_y;

    if (goalDirection > 0) {
      goalSide = Right;
    } else {
      goalSide = Left;
    }

    // Serial.println("dist: "+String(goalDist));
  }
  // goal not seen
  else {
    goalVisible = false;
    // wire stuff is in pixy2 example
    Wire.beginTransmission(0x27);
    Wire.write(255 - 2);
    Wire.endTransmission();
  }
}

void readButton() {
  KeyCode keyCode = igitBot.keyCode();
  // Serial.printf("keycode %s (%d) received\n", keyCodeToString(keyCode), keyCode);

  switch (keyCode) {
    case SetPlay: {
      GameState oldGameState;
      getGamestate(&oldGameState);

      gamestate.playing = true;
      if (oldGameState.playing != gamestate.playing) {
        setGamestate(&gamestate);
        outputGamestate(&gamestate);
      }
      igitBot.allLEDs(OFF);
      break;
    }

    case SetIdle: {
      GameState oldGameState;
      getGamestate(&oldGameState);

      gamestate.playing = false;
      if (oldGameState.playing != gamestate.playing) {
        setGamestate(&gamestate);
        outputGamestate(&gamestate);
      }
      igitBot.resetLEDs();
      break;
    }
    case SetCompass: {
      igitBot.setCompass();
      gamestate.head = head;

      GameState oldGameState;
      getGamestate(&oldGameState);

      if (oldGameState.head != gamestate.head) {
        setGamestate(&gamestate);
        outputGamestate(&gamestate);
      }
      break;
    }
    case KickTest: {
      igitBot.kick(KICK_TIME);
      break;
    }
    case ToggleKickOff: {
      if (kickOffTimer > 30 && !lastKickOffButton) {
        kickOff = !kickOff;
        igitBot.led(0, 1, kickOff ? GREEN : RED);
        kickOffTimer = 0;
        lastKickOffButton = true;
      }
      break;
    }
    case KeyCode::ToggleSignature: {
      if (signatureButtonTimer > 30 && !lastSignatureButton) {
        if (gamestate.signature == 1) {
          gamestate.signature = 2;
        } else {
          gamestate.signature = 1;
        }
        setGamestate(&gamestate);

        signatureButtonTimer = 0;
        lastSignatureButton = true;
      }
    }
    case KeyCode::Shift: {
      igitBot.led(0, 1, kickOff ? GREEN : RED);
      igitBot.led(3, 1, CYAN);
      igitBot.led(0, 2, gamestate.signature == 1 ? YELLOW : BLUE);
      igitBot.led(3, 2, WHITE);
      break;
    }

    default:
      if (!gamestate.playing) {
        igitBot.resetLEDs();
      }
      break;
  }

  if (keyCode != KeyCode::ToggleKickOff) {
    lastKickOffButton = false;
  }

  if (keyCode != KeyCode::ToggleSignature) {
    lastSignatureButton = false;
  }
}

void readLightbarrier() { gotBall = (analogRead(LIGHTBARRIER) > 2000); }

int average(int arr[], size_t size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}
