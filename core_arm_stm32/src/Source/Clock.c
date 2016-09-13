/*
 * Clock.c
 *
 *  Created on: Oct 8, 2015
 *      Author: alexis
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/ALLheader.h"

int CLK_Init()
{
	/*Clock : 32MHz with HSI + PLL*/
		RCC->CFGR &= ~RCC_CFGR_SW; /*HSI source clock*/
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); /*Wait HSI*/
		RCC->CR &= ~RCC_CR_PLLON; /*PLL disable*/
		while((RCC->CR & RCC_CR_PLLRDY) != 0); /*Wait PLL lock*/
		RCC->CFGR &= ~RCC_CFGR_SWS_PLL; /*PLL source*/
		RCC->PLLCFGR |= RCC_PLLP_DIV8; /*PLL * 8*/
		RCC->CR |= RCC_CR_PLLON; /*PLL enable*/
		while((RCC->CR & RCC_CR_PLLRDY) == 0); /*wait PLL lock*/
		RCC->CFGR |= RCC_CFGR_SW_PLL; /*PLL source*/
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); /*Wait PLL*/

		if((RCC->CFGR & RCC_CFGR_SWS) == (RCC_CFGR_SWS_PLL))return 1;
		else return 0;
}


