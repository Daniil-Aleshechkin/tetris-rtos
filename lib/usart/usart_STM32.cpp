#include <stm32f103xb.h>
#include "usart_STM32.h"
#include "piece.h"

enum Colors {
	RED,
	BLUE,
	YELLOW,
	PURPLE,
	GREEN,
	ORANGE,
	LIGHT_BLUE,
	GRAY,
	NONE
};

void usartInit(void) 
{
	//Enable Port A and USART clocks
			
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;		
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	
	
		GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
    GPIOA->CRL |= GPIO_CRL_CNF3_0; /* set floating input */
		
		GPIOA->CRL &= ~(GPIO_CRL_CNF2_0);
    GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2; /* alternate function output push pull 50mhz */


	USART2->CR1 |= USART_CR1_UE;
	USART2->BRR |= 0x18;
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;
}

void sendData(int data) {
		
		while((USART2->SR & USART_SR_TXE) == 0x0) {}
			
		USART2->DR = (data & 0xFF);
}

int readData(void) {
		if ((USART2->SR & USART_SR_RXNE) == USART_SR_RXNE) {
			return USART2->DR;
		}
		else  {
			return 0x0;
		}
}

int getColor(char boardPiece) {
	switch (boardPiece)
	{
	case 'I':
		return LIGHT_BLUE;
	case 'Z':
		return RED;
	case 'L':
		return ORANGE;
	case 'S':
		return GREEN;
	case 'J':
		return BLUE;
	case 'O':
		return YELLOW;
	case 'X':
		return GRAY;
	case 'T':
		return PURPLE;
	default:
		return NONE;
	}
}

void sendColor(int color) {
	switch (color)
	{
	case RED:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('1');
		sendData('m');
		break;
	case GREEN:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('2');
		sendData('m');
				
		break;
	case YELLOW:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('3');
		sendData('m');
		break;
	case BLUE:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('4');
		sendData('m');

		break;

	case ORANGE:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('1');
		sendData('m');
		
		break;

	case PURPLE:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('5');
		sendData('m');
		break;

	case LIGHT_BLUE:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('6');
		sendData('m');
		break;

	case GRAY:
		sendData(0x1B);
		sendData(0x5B);
		sendData('4');
		sendData('7');
		sendData('m');
			
		break;

	default:
		sendData(0x1B);
		sendData(0x5B);
		sendData('0');
		sendData('m');
		break;
	}
}


void sendTetrisChars(char** printedBoard) {
	int color = NONE;
	sendData(0x1B);
	sendData(0x5B);
	sendData('2');
	sendData('J');

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 21 ; j++) {
			int previousColor = color;

			color = getColor((int) printedBoard[i][j]);

			if (previousColor != color) {
				sendColor(color);
				//sendColor(RED);
			}

			if (color != NONE) {
				sendData(' ');

			} else {
				sendData((int) printedBoard[i][j]);
			}

		}
	}

	for (int i = 14; i < 23; i++) {
		for (int j = 0; j < 16; j++) {
			int previousColor = color;

			color = getColor((int) printedBoard[i][j]);

			if (previousColor != color) {
				sendColor(color);
				//sendColor(RED);
			}
			
			if (color != NONE) {
				sendData(' ');

			} else {
				sendData((int) printedBoard[i][j]);
			}

			
		}
	}

	freePrintedBytes(printedBoard);
}