/*
 * UART.c
 *
 *  Created on: Oct 13, 2015
 *      Author: alexis
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/ALLheader.h"


int UART_Init()
{
	RCC->APB1ENR |= RCC_APB1ENR_UART4EN;

	UART4->CR1 |= 0x000000E0; /*Interrupt reception/transmission enable TCIE TXEIE RXNEIE*/
	return 1;
}



