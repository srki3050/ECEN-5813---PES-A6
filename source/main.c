/* Name  		: Sricharan Kidambi S
 * File  		: uart.c
 * Date	 		: 04/06/2022
 * Brief 		: Application Entry Point
 * References	: Initialize the functions, such as baud rate of UART module, the main loop performing
 * 				  The command processing based on the character being typed.
 */
#include "sysclock.h"
#include "UART.h"
#include "stdio.h"
#include "command_processor.h"
#include "cbfifo.h"
#include "test_cbfifo.h"

#define REQUIRED_BAUD_RATE 38400
int main(void)
{
  sysclock_init();
  UART0_Init(REQUIRED_BAUD_RATE);
  // TODO: initialize the UART here
  printf("Welcome to Breakfast Serial\r\n");
  char name[MAX_SIZE];	//Store the incoming string in this Buffer.
  while(1){
	  char c = getchar();
	  if(c == '?'){
		  printf("%c ",c);
		  accumulate(name);
		  printf("\r\n");
		  process_command(name);
	  }
	  else{
		  putchar(c);
		  printf("\r\n");
	  }
  }
  return 0 ;
}
