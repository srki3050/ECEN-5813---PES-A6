/*
 * File : command_processor.h
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: Prototype for Basic Interactive commands Session Enabled in this file.
 * References: Inspired from Lecture Videos by professor howdy pierce.
 */
#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_
#include "stdio.h"
#include "string.h"
#include "cbfifo.h"
#include "uart.h"
#include "stdbool.h"
typedef void (*command_handler_t)(int, char *argv[]);

typedef struct{
	const char *name;
	command_handler_t handler;
	//const char *help_string;
}command_table_t;
/* Stores the input data to a character buffer for command processing.
 *
 */
char *accumulate();
/*
 * Lexicalisation based on ' '(SPACE), '\r' (CR), '\n (NL)
 */
void process_command(char *input);

#endif /* COMMAND_PROCESSOR_H_ */
