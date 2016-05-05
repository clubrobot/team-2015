/*
* com.c
 *
 *  Created on: 17 mars 2016
 *      Author: Alexis
 */

#include "com.h"
extern int tempo_servo;
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

	case 'f' :
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

		GPIOA->MODER |= 0x800;//function secondaire
		GPIOA->AFR[0] |=0x200000;
		TIM2->PSC=48; //Clk 1Mhz
		TIM2->ARR =21500; //period 22ms
		TIM2->CCR1 =1500; //high during 2ms
		TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
		TIM2->CCER |= TIM_CCER_CC1E;
		TIM2->BDTR |= TIM_BDTR_MOE;
		TIM2->CR1 |= TIM_CR1_CEN; //DIR LOW
		TIM2->EGR |= TIM_EGR_UG;
		strcpy(tab_R,"Servo1\n");
		Len = strlen(tab_R);
		break;

	case 'g' :
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

		GPIOA->MODER |= 0x800;//function secondaire
		GPIOA->AFR[0] |=0x200000;
		TIM2->PSC=48; //Clk 1Mhz
		TIM2->ARR =22000; //period 22ms
		TIM2->CCR1 =2000; //high during 2ms
		TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
		TIM2->CCER |= TIM_CCER_CC1E;
		TIM2->BDTR |= TIM_BDTR_MOE;
		TIM2->CR1 |= TIM_CR1_CEN; //DIR LOW
		TIM2->EGR |= TIM_EGR_UG;
		strcpy(tab_R,"Servo2\n");
		Len = strlen(tab_R);
		break;

	case 'h' :
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

		GPIOA->MODER |= 0x800;//function secondaire
		GPIOA->AFR[0] |=0x200000;
		TIM2->PSC=48; //Clk 1Mhz
		TIM2->ARR =21000; //period 22ms
		TIM2->CCR1 =1000; //high during 2ms
		TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
		TIM2->CCER |= TIM_CCER_CC1E;
		TIM2->BDTR |= TIM_BDTR_MOE;
		TIM2->CR1 |= TIM_CR1_CEN; //DIR LOW
		TIM2->EGR |= TIM_EGR_UG;
		strcpy(tab_R,"Servo3\n");
		Len = strlen(tab_R);
		break;

	default :

		strcpy(tab_R,"Error\n");
		Len = strlen(tab_R);
		break;
	}

	return Len;
}
