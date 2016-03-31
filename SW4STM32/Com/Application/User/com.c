/*
* com.c
 *
 *  Created on: 17 mars 2016
 *      Author: Alexis
 */

#include "com.h"

uint16_t UART_PIO(uint8_t *Buf, uint8_t *tab_R)
{

	uint16_t Len = 0;
	GPIOA->MODER |= 0x40;

	switch(Buf[0] & 0xFF)
	{

	case '1' :

		GPIOA->ODR |= 0x08;
		strcpy(tab_R,"Test1\n");
		Len = strlen(tab_R);
		break;

	case '2' :

		GPIOA->ODR &= ~0x08;
		strcpy(tab_R,"Test2\n");
		Len = strlen(tab_R);
		break;

	default :

		strcpy(tab_R,"Error\n");
		Len = strlen(tab_R);
		break;
	}

	return Len;
}
