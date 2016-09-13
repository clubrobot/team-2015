/*
 * IO.h
 *
 *  Created on: Oct 8, 2015
 *      Author: alexis
 */

#ifndef IO_H_
#define IO_H_

/*
 * Port avec UART :
 * 					-PAO UART4_TX
 * 					-PA1 UART4_RX
 *
 * 					-PC10 UART4_TX
 * 					-PC11 UART4_RX
 *
 * 					-PC12 UART5_TX
 * 					-PD2 UART5_RX
 *
 * 		Alternate Function UART4/5 --> AF8
 */

int IO_Init();


#endif /* IO_H_ */
