/*
 * ultra_functions.c
 *
 *  Created on: Apr 19, 2016
 *      Author: alexis
 */

#include "ultra_functions.h"
#include "usbd_cdc_if.h"

// Variables globales
static unsigned int time = 0;

static struct sensor sensor1;
static struct sensor sensor2;
static struct sensor sensor3;
static struct sensor sensor4;

uint8_t tab_distance[256];
extern tempo_servo;

void delay_ms(__IO uint32_t nCount)
{
	volatile uint32_t delay = nCount * 1028;
	for( ; delay != 0; delay--);
}

void init_tim()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

	TIM14->PSC = 47999; //Prescaler (Clock/(32000 - 1))
	TIM14->ARR = 999; //count max
	TIM14->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;// | TIM_CR1_URS;
	TIM14->DIER = TIM_DIER_UIE;



	//NVIC->ISER[0] |= 1 << 19; //interrupt enable on TIM14--> IRQn = 19
}

void init_PWM()
{
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
}

/*void init()
{

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
	//RCC->CR &= ~RCC_CR_HSEON; //disable HSE (For PF0 & PF1)
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM14EN;;
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;


	// 10 us * fréquence d'horloge / diviseur d'horloge
	//interruption levée tous les 10us (correspond à la durée minimale du trigger)
	TIM16->ARR = 480;

	//On recommence le burst tous les 5000 interruptions
	TIM16->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN | TIM_CR1_URS;
	TIM16->DIER = TIM_DIER_UIE;

	TIM14->PSC = 3199; //Prescaler (Clock/(32000 - 1))
	TIM14->ARR = 999; //count max
	TIM14->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN | TIM_CR1_URS;
	TIM14->DIER = TIM_DIER_UIE;


	GPIOB->MODER |= 0x08;
	// TIM2_CHAN_1 en mode capture (PA0)
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM2->CCMR1 |= TIM_CCMR1_IC1F_0*3;
	TIM2->CCER |= TIM_CCER_CC1P;
	TIM2->CCER |= TIM_CCER_CC1NP;
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->DIER |= TIM_DIER_CC1IE;

	// TIM2_CHAN_2 en mode capture (PA1)
	TIM2->CCMR1 |= TIM_CCMR1_CC2S_0;
	TIM2->CCMR1 |= TIM_CCMR1_IC2F_0*3;
	TIM2->CCER |= TIM_CCER_CC2P;
	TIM2->CCER |= TIM_CCER_CC2NP;
	TIM2->CCMR1 &= ~TIM_CCMR1_IC2PSC;
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->DIER |= TIM_DIER_CC2IE;

	// TIM2_CHAN_3 en mode capture (PA2)
	TIM2->CCMR2 |= TIM_CCMR2_CC3S_0;
	TIM2->CCMR2 |= TIM_CCMR2_IC3F_0*3;
	TIM2->CCER |= TIM_CCER_CC3P;
	TIM2->CCER |= TIM_CCER_CC3NP;
	TIM2->CCMR2 &= ~TIM_CCMR2_IC3PSC;
	TIM2->CCER |= TIM_CCER_CC3E;
	TIM2->DIER |= TIM_DIER_CC3IE;

	// TIM2_CHAN_4 en mode capture (PA3)
	TIM2->CCMR2 |= TIM_CCMR2_CC4S_0;
	TIM2->CCMR2 |= TIM_CCMR2_IC4F_0*3;
	TIM2->CCER |= TIM_CCER_CC4P;
	TIM2->CCER |= TIM_CCER_CC4NP;
	TIM2->CCMR2 &= ~TIM_CCMR2_IC4PSC;
	TIM2->CCER |= TIM_CCER_CC4E;
	TIM2->DIER |= TIM_DIER_CC4IE;


	NVIC->ISER[0] |= 1 << 15; //interrupt enable on TIM2--> IRQn = 15
	NVIC->ISER[0] |= 1 << 21; //interrupt enable on TIM16--> IRQn = 21

	NVIC->ISER[0] |= 1 << 19; //interrupt enable on TIM14--> IRQn = 19
}
//echo durera jusqu'à 30ms
//distance(cm) = echo(us)/58  (voir doc ultrasons)

void send_distance()
{
	if(sensor1.newdistance == 1)
	{
		tab_distance[0] = 0x01;
		tab_distance[1] = sensor1.distance;
		CDC_Transmit_FS(tab_distance,2);
		sensor1.newdistance = 0;
	}
	if(sensor2.newdistance == 1)
	{
		tab_distance[0] = 0x02;
		tab_distance[1] = sensor2.distance;
		CDC_Transmit_FS(tab_distance,2);
		sensor2.newdistance = 0;
	}
	if(sensor3.newdistance == 1)
	{
		tab_distance[0] = 0x03;
		tab_distance[1] = sensor3.distance;
		CDC_Transmit_FS(tab_distance,2);
		sensor3.newdistance = 0;
	}
	if(sensor4.newdistance == 1)
	{
		tab_distance[0] = 0x04;
		tab_distance[1] = sensor4.distance;
		CDC_Transmit_FS(tab_distance,2);
		sensor4.newdistance = 0;
	}

}

/*void TIM16_IRQHandler()
{
	if( time == 0 )
	{
		GPIOA->MODER |= GPIO_MODER_MODER0_0;
		GPIOA->ODR |= GPIO_ODR_0;
	}
	else if( time < 5000 )	// 50 ms / 10 us
	{
		GPIOA->ODR &= ~GPIO_ODR_0;
		GPIOA->MODER &= ~GPIO_MODER_MODER0_0;
		GPIOA->MODER |= GPIO_MODER_MODER0_1;
		GPIOA->AFR[0] |= 0x02;
	}
	else if( time == 5000 )
	{
		GPIOA->MODER |= GPIO_MODER_MODER1_0;
		GPIOA->ODR |= GPIO_ODR_1;
	}
	else if( time < 10000 )
	{
		GPIOA->ODR &= ~GPIO_ODR_1;
		GPIOA->MODER &= ~GPIO_MODER_MODER1_0;
		GPIOA->MODER |= GPIO_MODER_MODER1_1;
		GPIOA->AFR[0] |= 0x02 << 4;
	}
	else if( time == 10000 )
	{
		GPIOA->MODER |= GPIO_MODER_MODER2_0;
		GPIOA->ODR |= GPIO_ODR_2;
	}
	else if( time < 15000 )
	{
		GPIOA->ODR &= ~GPIO_ODR_1;
		GPIOA->MODER &= ~GPIO_MODER_MODER1_0;
		GPIOA->MODER |= GPIO_MODER_MODER1_1;
		GPIOA->AFR[0] |= 0x02 << 8;
	}
	else if( time == 15000 )
	{
		GPIOA->MODER |= GPIO_MODER_MODER3_0;
		GPIOA->ODR |= GPIO_ODR_3;
	}
	else if( time < 20000 )
	{
		GPIOA->ODR &= ~GPIO_ODR_1;
		GPIOA->MODER &= ~GPIO_MODER_MODER1_0;
		GPIOA->MODER |= GPIO_MODER_MODER1_1;
		GPIOA->AFR[0] |= 0x02 << 12;
	}
	time = ( time + 1 ) % 20000;

	TIM16->SR &= ~0x1;
}

void TIM2_IRQHandler()
{
	unsigned long echo;
	if((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		sensor1.overflow++;
		sensor2.overflow++;
		sensor3.overflow++;
		sensor4.overflow++;
		TIM2->SR &= ~TIM_SR_UIF;
	}
	else if((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
	{
		if((GPIOA->ODR & GPIO_ODR_0) == GPIO_ODR_0)
		{
			sensor1.edgetime = ((TIM2->CCR1) & TIM_CCR1_CCR1);
			sensor1.overflow = 0;
		}
		else
		{
			echo = ((TIM2->CCR1) & TIM_CCR1_CCR1) - sensor1.edgetime + 0x10000 * sensor1.overflow;
			sensor1.distance = echo / 2824; // 2 / 34000 (cm/s) * fréquence de l'horloge / diviseur de l'horloge
			sensor1.newdistance = 1;
		}
		TIM2->SR &= ~TIM_SR_CC1IF;
	}
	else if((TIM2->SR & TIM_SR_CC2IF) == TIM_SR_CC2IF)
	{
		if((GPIOA->ODR & GPIO_ODR_1) == GPIO_ODR_1)
		{
			sensor2.edgetime = ((TIM2->CCR2) & TIM_CCR2_CCR2);
			sensor2.overflow = 0;
		}
		else
		{
			echo = ((TIM2->CCR2) & TIM_CCR2_CCR2) - sensor2.edgetime + 0x10000 * sensor2.overflow;
			sensor2.distance = echo / 2824; // 2 / 34000 (cm/s) * fréquence de l'horloge / diviseur de l'horloge
			sensor2.newdistance = 1;
		}
		TIM2->SR &= ~TIM_SR_CC1IF;
	}
	else if((TIM2->SR & TIM_SR_CC3IF) == TIM_SR_CC3IF)
	{
		if((GPIOA->ODR & GPIO_ODR_2) == GPIO_ODR_2)
		{
			sensor3.edgetime = ((TIM2->CCR3) & TIM_CCR3_CCR3);
			sensor3.overflow = 0;
		}
		else
		{
			echo = ((TIM2->CCR3) & TIM_CCR3_CCR3) - sensor3.edgetime + 0x10000 * sensor3.overflow;
			sensor3.distance = echo / 2824; // 2 / 34000 (cm/s) * fréquence de l'horloge / diviseur de l'horloge
			sensor3.newdistance = 1;
		}
		TIM2->SR &= ~TIM_SR_CC1IF;
	}
	else if((TIM2->SR & TIM_SR_CC4IF) == TIM_SR_CC4IF)
	{

		if((GPIOA->ODR & GPIO_ODR_3) == GPIO_ODR_3)
		{
			sensor4.edgetime = ((TIM2->CCR4) & TIM_CCR4_CCR4);
			sensor4.overflow = 0;
		}
		else
		{
			echo = ((TIM2->CCR4) & TIM_CCR4_CCR4) - sensor4.edgetime + 0x10000 * sensor4.overflow;
			sensor4.distance = echo / 2824; // 2 / 34000 (cm/s) * fréquence de l'horloge / diviseur de l'horloge
			sensor4.newdistance = 1;
		}
		TIM2->SR &= ~TIM_SR_CC1IF;
	}
}


void TIM14_IRQHandler()
{
	GPIOB->ODR ^= 0x02;
	TIM14->SR &= ~0x1;
}

/*

void init()
{
	TIM16->MODE = COMPTE_JUSQU_A_TIM16_ARR_PUIS_SE_RESET_ET_LEVE_UNE_INTERRUPTION;
	TIM16->ARR = 480; // 10 us * fréquence d'horloge / diviseur d'horloge

	TIM1->MODE = CAPTURE_FRONTS_MONTANT_ET_DESCENDANT_SUR_P1_ET_INTERRUPTION_OVERFLOW;
	TIM2->MODE = CAPTURE_FRONTS_MONTANT_ET_DESCENDANT_SUR_P2_ET_INTERRUPTION_OVERFLOW;
	TIM3->MODE = CAPTURE_FRONTS_MONTANT_ET_DESCENDANT_SUR_P3_ET_INTERRUPTION_OVERFLOW;
	TIM4->MODE = CAPTURE_FRONTS_MONTANT_ET_DESCENDANT_SUR_P4_ET_INTERRUPTION_OVERFLOW;
}

interrupt TIM16_RESET()
{
	if( time == 0 )
	{
		GPIOA->MODER |= 0x01;
		GPIOA->OUT |= 0x01;
	}
	else if( time < 5000 )	// 50 ms / 10 us
	{
		GPIOA->OUT &= ~0x01;
		GPIOA->MODER &= ~0x01;
	}
	else if( time == 5000 )
	{
		GPIOA->MODER |= 0x04;
		GPIOA->OUT |= 0x02;

	}
	else if( time < 10000 )
	{
		GPIOA->OUT &= ~0x04;
		GPIOA->MODER &= ~0x02;
	}
	else if( time == 10000 )
	{
		GPIOA->MODER |= 0x10;
		GPIOA->OUT |= 0x04;
	}
	else if( time < 15000 )
	{
		GPIOA->OUT &= ~0x10;
		GPIOA->MODER &= ~0x04;
	}
	else if( time == 15000 )
	{
		GPIOA->MODER |= 0x40;
		GPIOA->OUT |= 0x08;
	}
	else if( time < 20000 )
	{
		GPIOA->OUT &= ~0x40;
		GPIOA->MODER &= ~0x08;
	}
	time = ( time + 1 ) % 20000;
}

interrupt TIM1_RISING()
{
	sensor1.edgetime = ((TIM1->TIM_ARR) & TIM_ARR);
	sensor1.overflow = 0;
}

interrupt TIM1_FALLING()
{
	unsigned long echo = ((TIM1->TIM_ARR) & TIM_ARR) - sensor1.edgetime + 0x10000 * sensor1.overflow;
	sensor1.distance = echo / 2824; // 2 / 34000 (cm/s) * fréquence de l'horloge / diviseur de l'horloge
}

interrupt TIM1_OVERFLOW()
{
	if((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		sensor1.overflow++;
		TIM2->SR &= ~TIM_SR_UIF;
	}
}

 */
