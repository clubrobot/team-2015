
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../Header/ALLheader.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

/*Machine d'état*/
int UART_R[UART_BUFFER];
int UART_T[UART_BUFFER];

int flag_r = 0;
int flag_t = 0;

int cpt = 0;
int main()
{
	Init();

  /*Infinite loop*/
	while (1)
    {
		if(cpt%100 == 0)trace_printf("%d",cpt);
    }

}

void TIM14_IRQHandler()
{
	cpt++;					/*Compteur increase*/
	TIM14->SR &= 0xFFFE; 	/*reset status TIM14*/

}

void UART4_IRQHandler()
{
	if((UART4->SR & UART_FLAG_RXNE) == UART_FLAG_RXNE)
	{
		UART_R[flag_r++] = UART4->DR & USART_DR_DR;
	}

	if((UART4->SR & UART_FLAG_TXE) == UART_FLAG_TXE)
	{
		flag_t--;
		UART4->DR = UART_T[flag_t];
	}

	if((UART4->SR & UART_FLAG_TC) == UART_FLAG_TC)
	{
		flag_r = 0;
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
