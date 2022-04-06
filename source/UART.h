/* Name  		: Sricharan Kidambi S
 * File  		: uart.h
 * Date	 		: 04/06/2022
 * Brief 		: System clock (24MHz) generation.
 * References	: Prototype for UART configuration to create an Interrupt Based Approach.
 */
#ifndef UART_H_
#define UART_H_

#include "MKL25Z4.h"
#include "cbfifo.h"
void UART0_Init(uint32_t baud_rate);

extern cbfifo_t cb_TX,cb_RX;

void UART0_IRQHandler(void);
#endif /* UART_H_ */
