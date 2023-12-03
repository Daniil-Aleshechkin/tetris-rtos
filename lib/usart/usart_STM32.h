#ifndef USART_STM32
#define USART_STM32

void usartInit(void);
void sendData(int);
int readData(void);
void sendTetrisChars(char** printedBoard);

#endif