/********************************************************************************
 * Project: Tetris RTOS for STM32
 * 
 * Description: This firmware implements a real-time operating system (RTOS) version of the classic Tetris game, designed to run on an STM32 microcontroller. 
 * It showcases multitasking capabilities, using FreeRTOS for task management, handling user input, updating game state, and refreshing the display in real-time. 
 * The unique challenge of this project was to efficiently manage system resources and ensure smooth gameplay, even as the game's complexity increases. 
 * The implementation required careful attention to task prioritization, synchronization, and real-time input handling, making it a compelling example of an embedded system with RTOS.
 * 
 * Development Environment: The project is developed using the GNU arm-none-eabi toolkit
 * 
 * Compiler: ARM GCC 13.2.90.20231008-git
 * The project relies on specific features and optimizations available in this version of the ARM GCC compiler, ensuring compatibility and performance on the target hardware.
 * 
 * Libraries: FreeRTOS V202212.01, providing the multitasking kernel. STM32 CMSIS Library for hardware abstraction.
 * 
 * Other Tools: ST-Link for flashing and debugging the microcontroller. usbipd-win for USB over IP, facilitating communication between the WSL environment and the STM32 board.
 * 
 * CPU Configuration: STM32F103xB; The microcontroller is configured for a 24 MHz system clock, with all peripheral clocks appropriately divided. 
 * Specific attention is paid to USART and GPIO configurations to support game input and display output.
 * 
 * Build Instructions: Use the provided Makefile for building the project. Run 'cmake -DPROJECT_NAME=firmware -DCMAKE_BUILD_TYPE=Debug -DDUMP_ASM=OFF' to generate the make file. Then run `make all` to compile the firmware and `st-flash --reset write ./firmware.bin 0x08000000` to flash it to the STM32 board. 
 * Ensure `usbipd` is correctly set up if using WSL to connect to the device.
 *********************************************************************************/

#include "holdPiece.h"
#include "piece.h"
#include "usart_STM32.h"
#include "util_STM32.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "cli.h"
#include "semphr.h"
#include "com_14646_matrix.h"
#include <stm32f103xb.h>

# define mainPRINT_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
# define mainINPUT_READ_PRIORITY (tskIDLE_PRIORITY + 1)

static struct pixel red = {false, true, false};
static struct pixel blue = {false, false, true};
static struct pixel green = {true, false, false};
static struct pixel nothing = {false, false, false};

bool CLI_ENABLED = false;

TetrisGameState* state = nullptr;
SemaphoreHandle_t xState;

QueueHandle_t xCLIQueue;

int readCharacter;
int adcVal;
bool prevLeft;
int frames;

int DAS_TIME = 1000;
int ARR_TIME = 0;
bool DAS_ENABLED = true;

void handleInput(int input);
void printNum(int num);
char getCharFromNum(int num);
void autoRepeat();
void handleDAS(int input, int currentFrame, int* dasState, int* dasFrame);
void handleExtraSoftDrop(int input, bool* isSoftDropping);
void autoRepeatMove(bool isLeft);

void vPrintTask(void* parameters);

void vPrintTask(void* parameters) {
	static int offset = 0;
  
  for(;;){
    if (!CLI_ENABLED) {
      
      if (xSemaphoreTake(xState, portMAX_DELAY)) {
          __disable_irq();
          refreshDisplay();
          __enable_irq();
          
          displayState(state);
          //sendTetrisChars(printState(state));
          xSemaphoreGive(xState);
      }

    } else {
       __enable_irq();
    }

    vTaskDelay(2);
	}
}

const int NONE_DAS = 0;
const int LEFT_DAS = 1;
const int RIGH_TDAS = 2;

void vInputTask(void* parameters) {
  int dasState = NONE_DAS;
  int dasFrame = -1;
  bool isSoftDropping = false;

  int input;
  int frame = 0;

  for(;;){
		input = readData();
    //sendData(0x55);
    //vTaskDelay(2);
    if (CLI_ENABLED) {
      if (input != 0x00) {
        xQueueSend(xCLIQueue, &input, 0);
      }
      
      continue;
    }

    if (xSemaphoreTake(xState, portMAX_DELAY)) {
      handleInput(input);
      if (DAS_ENABLED) {
        handleDAS(input, frame, &dasState, &dasFrame);    
        handleExtraSoftDrop(input, &isSoftDropping);
      }

      xSemaphoreGive(xState);
    }
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
      if (ARR_TIME == 0) {
        autoRepeatMove(true);
      } else if ((*dasFrame + DAS_TIME - currentFrame) % ARR_TIME == 0) {
        movePiece(state, true);
      }
    }
    break;
  case RIGH_TDAS:
  
    if (*dasFrame + DAS_TIME <= currentFrame) {
       if (ARR_TIME == 0) {
        autoRepeatMove(false);
      } else if ((*dasFrame + DAS_TIME - currentFrame) % ARR_TIME == 0) {
        movePiece(state, false);
      }
    }
    break;
  default:
    break;
  }
}

void handleExtraSoftDrop(int input, bool* isSoftDropping) {
  bool isKeyUp = (input >> 7) & 0x1 == 1;

  if ((input & 0x7F) == 0x35) {
    if (isKeyUp) {
      *isSoftDropping = false;
    } else {
      *isSoftDropping = true;
    }
  }

  if (*isSoftDropping) {
    state = softDropPiece(state);
  }
}

int main() {
  usartInit();
  displayInit();
  clockInit();

  bufferPixel(red, 2, 6);
	//bufferPixel(green, 2, 5);
	//bufferPixel(green, 2, 4);
	//bufferPixel(red, 5, 6);
	//bufferPixel(green, 5, 5);
//	bufferPixel(green, 5, 4);
	
	//bufferPixel(blue, 1, 2);
	//bufferPixel(blue, 2, 1);
	//bufferPixel(blue, 3, 1);
	//bufferPixel(blue, 4, 1);
	//bufferPixel(blue, 5, 1);
	//bufferPixel(blue, 6, 2);
  state = getDefaultTetrisGameState();
  prevLeft = false;

  xCLIQueue = xQueueCreate(1000, sizeof(char));
  xState = xSemaphoreCreateMutex();

  sendData(0x1B);
	sendData(0x5B);
	sendData('?');
	sendData('2');
	sendData('5');
	sendData('l');

  sendData(0x1B);
  sendData(0x5B);
  sendData('?');
  sendData('2');
  sendData('5');
  sendData('l');
  
  sendData(0x1B);
  sendData(0x5B);
  sendData('?');
  sendData('1');
  sendData('2');
  sendData('l');


  sendTetrisChars(printState(state));
  sendData(0x55);
  
  xTaskCreate(vPrintTask, "Print", configMINIMAL_STACK_SIZE + 1000, NULL, mainPRINT_TASK_PRIORITY, NULL);
  xTaskCreate(vInputTask, "Input", configMINIMAL_STACK_SIZE, NULL, mainINPUT_READ_PRIORITY, NULL);
  xTaskCreate(vCLITask, "CLI", configMINIMAL_STACK_SIZE + 200, NULL, mainCLI_TASK_PRIORITY, NULL);
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
    sendData(0x45);
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
    break;
  case 0x70:
    clearScrean();
    CLI_ENABLED = true;
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