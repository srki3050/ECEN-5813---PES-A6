/* Name  		: Sricharan Kidambi S
 * File  		: app.c
 * Date	 		: 04/06/2022
 * Brief 		: application level programming
 */

#ifndef APP_H_
#define APP_H_

#include "stdio.h"
#include "command_processor.h"
#include "cbfifo.h"
#include "test_cbfifo.h"
/* Function : command_processor
 * Returns	: None
 * Arguments: None
 * Purpose	: this function should be called in the main while loop
 * 			  gets the characters and performs basic command processor operations
 */
void command_processor(char *name);

#endif /* APP_H_ */
