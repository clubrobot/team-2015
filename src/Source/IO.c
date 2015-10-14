/*
 * IO.c
 *
 *  Created on: Oct 9, 2015
 *      Author: alexis
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/ALLheader.h"


int IO_Init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	/*UART pour PC10-11*/
	GPIOC->MODER |= 0x00C00000; /*Alternation Function*/
	GPIOC->OSPEEDR |= 0x00C00000; /*High Speed*/
	GPIOC->AFR[1] |= 0x00008800; /*UART4*/

	return 1;
}


