/* Name  		: Sricharan Kidambi S
 * File  		: uart.c
 * Date	 		: 04/06/2022
 * Brief 		: UART configuration and to create and Interrupt Based Approach.
 * References	: Dean ch 8 programming with UART serial Communication
 */
#include "UART.h"
#include "stddef.h"

#define UART_OVERSAMPLE_RATE (16)
#define SYS_CLOCK (24e6)

cbfifo_t cb_TX,cb_RX;

void UART0_Init(uint32_t baud_rate){
	uint16_t sbr;
	uint8_t temp;

	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;//Enable UART0 by setting bit 10-8 to 100
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;//Enable UART0 PORTA by setting the 9th bit to 1

	UART0->C2 &=~ UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//Select an FLL or PLL clock for UART0
	//SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	//Set this port to be transmitter
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	//Set this port to be receiver

	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));//We need a baud rate of 38400 with system clock 24MHz

	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr >> 8);

	UART0->BDL = UART0_BDL_SBR(sbr);

	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);//SET OVERSAMPLING TO 16 times

	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);//2 stop bits

	UART0->C1 = UART0_C1_LOOPS(0)|UART0_C1_M(0)|UART0_C1_PE(0);//8 BITS DATA with no parity

	UART0->C3 = UART0_C3_TXINV(0)|UART0_C3_ORIE(1)|UART0_C3_NEIE(1)|UART0_C3_FEIE(1)|UART0_C3_PEIE(1);

	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	UART0->C2 |= UART0_C2_TE(1) | UART0_C2_RE(1) | UART0_C2_RIE(1);

	NVIC_SetPriority(UART0_IRQn,2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	initialize(&cb_TX);
	initialize(&cb_RX);

	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

void UART0_IRQHandler(void){
	uint8_t byte;
	const uint8_t error_flags = UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK;
	if(UART0->S1 & error_flags){
		UART0->S1 |= error_flags;
		byte = UART0->D;
	}
	if(UART0->S1 & UART0_S1_RDRF_MASK){
		byte = UART0->D;
		enqueue(&cb_RX,&byte,1);
	}
	if(UART0->S1 & UART0_S1_TDRE_MASK){
		if(dequeue(&cb_TX,&byte,1))
			UART0->D = byte;
		else
			UART0->C2 &= ~UART0_C2_TIE_MASK;
	}

}
/*
 * System called function on calling anything to STDOUt (printf, puts);
 * Enqueues to transmission buffer
 * Returns - 0 if enqueued successfully, -1 otherwise
 */
int __sys_write(int handle, char *buf, int size){
	if(buf == NULL)
		return -1;
	while(bufferfull(&cb_TX) == 1);
	int nbytes;
	while(size)
	{
		nbytes = enqueue(&cb_TX,buf,size);
		if(nbytes == -1)
			return -1;
		size -= nbytes;
		UART0->C2 |= UART0_C2_TIE_MASK;
	}
	return 0;
}
/*
 * System called function on calling anything to STDOUt (scanf, gets);
 * dequeues from receiver buffer
 * Returns - the dequeued character if dequeued successfully, -1 otherwise
 */
int __sys_readc(void){
	char ch;
	while(bufferempty(&cb_RX) == 1);
	if(dequeue(&cb_RX,&ch,1)!=1){
		return -1;
	}
	return ch;
}
