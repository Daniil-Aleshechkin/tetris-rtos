#include "holdPiece.h"
#include "piece.h"
#include "usart_STM32.h"
#include "util_STM32.h"
#include "FreeRTOS.h"
#include "task.h"

# define mainPRINT_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
# define mainINPUT_READ_PRIORITY (tskIDLE_PRIORITY + 1)

TetrisGameState* state = nullptr;

int readCharacter;
int adcVal;
bool prevLeft;
int frames;

const int DAS_TIME = 60000;

void handleInput(int input);
void printNum(int num);
char getCharFromNum(int num);
void autoRepeat();
void handleDAS(int input, int currentFrame, int* dasState, int* dasFrame);
void autoRepeatMove(bool isLeft);

void vPrintTask(void* parameters);

void vPrintTask(void* parameters) {
	for(;;){

    //sendData(0x50);
    sendTetrisChars(printState(state));
    vTaskDelay(30);
	}
}

const int NONE_DAS = 0;
const int LEFT_DAS = 1;
const int RIGH_TDAS = 2;

void vInputTask(void* parameters) {
  int dasState = NONE_DAS;
  int dasFrame = -1;
  int input;
  int frame = 0;

  for(;;){
    //sendData(0x55);
		input = readData();
    
    handleInput(input);
    handleDAS(input, frame, &dasState, &dasFrame);
    
    frame++;
	}
}


void handleDAS(int input, int currentFrame, int* dasState, int* dasFrame) {
  bool isKeyUp = (input >> 7) & 0x1 == 1;

  switch (input & 0x7F)
  {
  case 0x34: // Left
    if (isKeyUp && *dasState == LEFT_DAS) {
      *dasState = NONE_DAS;
    } else if (!isKeyUp)
    {
      *dasFrame = currentFrame;
      *dasState = LEFT_DAS;
    }
    
    break;
  case 0x36:
    if (isKeyUp && *dasState == RIGH_TDAS) {
      *dasState = NONE_DAS;
    } else if (!isKeyUp)
    {
      *dasFrame = currentFrame;
      *dasState = RIGH_TDAS;
    }
    break;
  default:
    break;
  }

  switch (*dasState)
  {
  case LEFT_DAS:
    if (*dasFrame + DAS_TIME <= currentFrame) {
      autoRepeatMove(true);
    }
    break;
  case RIGH_TDAS:
  
    if (*dasFrame + DAS_TIME <= currentFrame) {
      autoRepeatMove(false);
    }
    break;
  default:
    break;
  }
}

int main() {
  usartInit();
  clockInit();

  state = getDefaultTetrisGameState();
  prevLeft = false;

  sendTetrisChars(printState(state));
  //sendData(0x55);
  
  xTaskCreate(vPrintTask, "Print", configMINIMAL_STACK_SIZE + 1000, NULL, mainPRINT_TASK_PRIORITY, NULL);
  xTaskCreate(vInputTask, "Input", configMINIMAL_STACK_SIZE, NULL, mainINPUT_READ_PRIORITY, NULL);
  vTaskStartScheduler();

  // while (true) {
  //   readCharacter = readData();
  //   // if (readCharacter != 0) {
      
  //   //   printNum(readCharacter);
  //   //   sendData('\n');
  //   // }

  //   handleInput(readCharacter);

  // }
  for (;;) {
    sendData(0x55);
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


void autoRepeatMove(bool isLeft) {
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
  movePiece(state, isLeft);
}

void handleInput(int input) {
  switch (input)
  {
  case 0x64:
    state = hardDropPiece(state);
    //sendTetrisChars(printState(state));
    break;
  case 0x34:
    state = movePiece(state, true);
    prevLeft = true;

    //sendTetrisChars(printState(state));
    break;
  case 0x36:
    state = movePiece(state, false);
    prevLeft = false;
    //sendTetrisChars(printState(state));
    break;
  case 0x38:
    state = rotatePiece(state, DEG_90);
    //sendTetrisChars(printState(state));
    break;
  case 0x71:
    state = rotatePiece(state, DEG_180);
    //sendTetrisChars(printState(state));
    break;
  case 0x77:
    state = rotatePiece(state, DEG_270);
    //sendTetrisChars(printState(state));
    break;
  case 0x72:
    state = reset(state);
  //  sendTetrisChars(printState(state));
    break;
  case 0x35:
    state = softDropPiece(state);
    // sendTetrisChars(printState(state));
    break;
  case 0x9:
    holdPiece(state->holdPiece, state->queue, state->piece);
//    sendTetrisChars(printState(state));
    break;
  case 0x20:
    autoRepeat();
    sendTetrisChars(printState(state));
  default:
    break;
  }
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
  /* This function will get called if a task overflows its stack.   If the
  parameters are corrupt then inspect pxCurrentTCB to find which was the
  offending task. */

  (void)pxTask;
  (void)pcTaskName;

  for (;;) {
    sendData(0x55);
  }
}