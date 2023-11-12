#include "holdPiece.h"
#include "piece.h"
#include "usart_STM32.h"
#include "util_STM32.h"

TetrisGameState* state = nullptr;
int readCharacter;
int adcVal;
bool prevLeft;

void handleInput(int input);
void printNum(int num);
char getCharFromNum(int num);
void autoRepeat();

int main() {
  usartInit();
  clockInit();

  state = getDefaultTetrisGameState();
  prevLeft = false;

  sendTetrisChars(printState(state));
  while (true) {
    readCharacter = readData();
    // if (readCharacter != 0) {
      
    //   printNum(readCharacter);
    //   sendData('\n');
    // }

    handleInput(readCharacter);

  }
  
}



char getCharFromNum(int num) {
  if (num < 10) {return (char)(num+48);}
  else {
    return (char)(num-10+65);
  }
}

void printNum(int num ) {
  sendData(getCharFromNum(num / 256));
  sendData(getCharFromNum((num % 256)/ 16));
  sendData(getCharFromNum(num% 16));
}

void autoRepeat() {
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
  movePiece(state, prevLeft);
}

void handleInput(int input) {
  switch (input)
  {
  case 0x64:
    state = hardDropPiece(state);
    sendTetrisChars(printState(state));
    break;
  case 0x34:
    state = movePiece(state, true);
    prevLeft = true;

    sendTetrisChars(printState(state));
    break;
  case 0x36:
    state = movePiece(state, false);
    prevLeft = false;
    sendTetrisChars(printState(state));
    break;
  case 0x38:
    state = rotatePiece(state, DEG_90);
    sendTetrisChars(printState(state));
    break;
  case 0x71:
    state = rotatePiece(state, DEG_180);
    sendTetrisChars(printState(state));
    break;
  case 0x77:
    state = rotatePiece(state, DEG_270);
    sendTetrisChars(printState(state));
    break;
  case 0x72:
    state = reset(state);
    sendTetrisChars(printState(state));
    break;
  case 0x35:
    state = softDropPiece(state);
    sendTetrisChars(printState(state));
    break;
  case 0x9:
    holdPiece(state->holdPiece, state->queue, state->piece);
    sendTetrisChars(printState(state));
    break;
  case 0x20:
    autoRepeat();
    sendTetrisChars(printState(state));
  default:
    break;
  }
}
