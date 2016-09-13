/*
 * ultra_functions.h
 *
 *  Created on: Apr 19, 2016
 *      Author: alexis
 */

#ifndef APPLICATION_USER_ULTRA_FUNCTIONS_H_
#define APPLICATION_USER_ULTRA_FUNCTIONS_H_

#include "stm32f0xx.h"

struct sensor
{
	unsigned int distance;
	unsigned int edgetime;
	unsigned int overflow;
	unsigned int newdistance;
};

void init();
void send_distance();
void delay_ms(__IO uint32_t nCount);
void init_tim();
void init_PWM();

#endif /* APPLICATION_USER_ULTRA_FUNCTIONS_H_ */
