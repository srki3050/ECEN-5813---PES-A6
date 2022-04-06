/*
 * File : command_processor.c
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: Basic Interactive commands Session Enabled in this file.
 * References: Inspired from Lecture Videos by professor howdy pierce.
 * 			   https://canvas.colorado.edu/courses/79904/pages/lecture-videos-and-supporting-files Page 27 and Page 28
 */
#include "command_processor.h"
#define SPACE_CHARACTER 0x20
#define BACK_SPACE 0x08
#define CARRIAGE_RETURN 0x0D
#define NEW_LINE 0x0A
/* Function		:	handle_author
 * Purpose		:	display the author name is the command typed is author
 * return type 	: 	static void
 * Parameters	:	argc (holds the count of arguments passed), argv (holding the array of strings)
 */
static void handle_author(int argc,char *argv[]);
/* Function 	: handle hexdump
 * Purpose 		: display the hex dump feature of data within the specified address range (see. hexdump.c)
 * return type	: static void
 * Parameters	: argc (holds the count of arguments passed), argv (holding the array of strings)
 */
static void handle_hexdump(int argc,char *argv[]);
/* Function 	: handle help
 * Purpose 		: to display the menu box specified. Prints the third element of the command_table_t data structure
 * return type	: static void
 * Parameters	: argc (holds the count of arguments passed), argv (holding the array of strings)
 */
static void handle_help(int argc,char *argv[]);
/* Function 	: parse_data
 * Purpose 		: To redirect the current statements to its respective functions via the function pointer
 * return type	: static void
 * Parameters	: argc (holds the count of arguments passed), argv (holding the array of strings)
 */
static void handle_other(int argc,char *argv[]);
/* Function 	: parse_data
 * Purpose 		: Just to check whether command table is scalable
 * return type	: static void
 * Parameters	: argc (holds the count of arguments passed), argv (holding the array of strings)
 */
static void parse_data(int argc,char *argv[]);
/* Function : Print Unknown command
 * Purpose  : This function is solely defined to let the user know that the given command is not in the list.
 * 			  a boolean variable is declared and is checking is the command is present. if not it prints the
 * 			  error message stating commands are unknown.
 * returns	: None
 * Parameters: argc (holds the count of arguments passed), argv (holding the array of strings)
 *
 */
static void print_unknown_command(int argc,char *argv[]);

static const command_table_t commands[] = {
		{"author",handle_author,"\r\nAuthor Prints the name of the Author's name\r\n"},
		{"dump",handle_hexdump,"prints the hexdump functionality if a legal start address and length is specified\r\n"},
		{"help",handle_help,"prints the description of all the possible commands entered\r\n"},
		{"other",handle_other,"Just to check whether command table is scalable\r\n"},
};

static const int num_commands = sizeof(commands)/sizeof(command_table_t);

static void handle_author(int argc,char *argv[]){
	printf("Sricharan Kidambi \r\n");
}

static void handle_hexdump(int argc,char *argv[]){
	hexdump(argv[1],argv[2]);
}

static void handle_help(int argc,char *argv[]){
	for(int i =0;i < num_commands;i++){
			printf("%s", commands[i].help_string);
	}
}
static void handle_other(int argc,char *argv[]){
	printf("Yes,Command table is scalable\r\n");
}
static void parse_data(int argc,char *argv[]){
	for(int i =0;i < num_commands;i++){
		if(strcasecmp(argv[0],commands[i].name)==0){
			commands[i].handler(argc,argv);
			break;
		}
	}
}

static void print_unknown_command(int argc,char *argv[]){
	bool command_present = false;
	for(int i =0;i < num_commands;i++){
		if(strcasecmp(argv[0],commands[i].name)==0){
			command_present = true;
			break;
		}
	}
	if(command_present == false){
		printf("Unknown Command :%s\r\n",argv[0]);
	}
}

void process_command(char *input){
	char *p = input;
	char *end;
	for(end = input;*end != '\0';end++);
	bool in_token = false;
	char *argv[10];
	int argc = 0;
	__builtin_memset(argv,0,sizeof(argv));
	for(p = input;p < end;p++){
		if(in_token){
			if((*p == SPACE_CHARACTER)||(*p == '\r')||(*p == '\0')){
				*p = 0;
				in_token = false;
			}
			else{
				argv[argc] = p;
			}
		}
		else{
			if((*p == SPACE_CHARACTER)||(*p == '\r')||(*p == '\0')){
				*p = 0;
			}
			else{
				argv[argc] = p;
				argc++;
				in_token = true;
			}
		}
	}
	argv[argc] = NULL;
	if(argc == 0)
		return;
	parse_data(argc,argv);
	print_unknown_command(argc,argv);
}

char *accumulate(char *name){
  char ch;
  int i = 0;
  char backup_buffer[MAX_SIZE];
	while(ch != 0x0D){
		while(bufferempty(&cb_RX) == 1);
		dequeue(&cb_RX,&ch,1);
		backup_buffer[i++] = ch;
		if(ch == BACK_SPACE){
			i-=1;
		}
		if(ch == CARRIAGE_RETURN){
			printf("\r");
			break;
		}
		if(ch == NEW_LINE){
			printf("\n");
			break;
		}
		putchar(ch);
	}
	backup_buffer[i] = '\0';
	__builtin_memcpy(name,backup_buffer,sizeof(backup_buffer));
	return (char *)name;
}
