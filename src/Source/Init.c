/*
 * Init.c
 *
 *  Created on: Oct 8, 2015
 *      Author: alexis
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/ALLheader.h"

int Init()
{
	CLK_Init();
	IO_Init();
	UART_Init();
	TIM14_Init();

	return 1;
}



