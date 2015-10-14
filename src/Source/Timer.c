/*
 * Timer.c
 *
 *  Created on: Oct 8, 2015
 *      Author: alexis
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/ALLheader.h"


int TIM14_Init()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

	/*Timer : 1s*/
	TIM14->PSC = 31999; /*Prescaler (Clock/(32000 - 1))*/
	TIM14->ARR = 999; /*count max*/
	TIM14->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN; /*counter enabled*/
	TIM14->DIER |= TIM_DIER_UIE; /*update interrupt enable*/

	return 1;
}


