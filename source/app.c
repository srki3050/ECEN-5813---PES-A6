/* Name  		: Sricharan Kidambi S
 * File  		: app.c
 * Date	 		: 04/06/2022
 * Brief 		: application level programming
 */
#include "app.h"

void command_processor(char *name){
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
