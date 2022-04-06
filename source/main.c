/* Name  		: Sricharan Kidambi S
 * File  		: uart.c
 * Date	 		: 04/06/2022
 * Brief 		: Application Entry Point
 * References	: Initialize the functions, such as baud rate of UART module, the main loop performing
 * 				  The command processing based on the character being typed.
 */
#include "app.h"
#include "sysclock.h"
#include "UART.h"
#include "stdio.h"

#define REQUIRED_BAUD_RATE 38400
int main(void)
{
  sysclock_init();
  UART0_Init(REQUIRED_BAUD_RATE);
  // TODO: initialize the UART here
  printf("Welcome to Breakfast Serial\r\n");
  char name[MAX_SIZE];	//Store the incoming string in this Buffer.
  while(1){
	  command_processor(name);
  }
  return 0 ;
}
