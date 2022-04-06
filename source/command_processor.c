/*
 * File : command_processor.c
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: Basic Interactive commands Session Enabled in this file.
 * References: Inspired from Lecture Videos by professor howdy pierce.
 */
#include "command_processor.h"
#define SPACE_CHARACTER 0x20
/*********************************/
static void handle_author(int argc,char *argv[]);

static void handle_hexdump(int argc,char *argv[]);

static const command_table_t commands[] = {
		{"author",handle_author},
		{"dump",handle_hexdump},
};

static const int num_commands = (sizeof(commands))/(sizeof(command_table_t));

static void handle_author(int argc,char *argv[]){
	printf("Sricharan Kidambi \r\n");
}

static void handle_hexdump(int argc,char *argv[]){
	hexdump(argv[1],argv[2]);
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
	for(int i =0;i < num_commands;i++){
		if(strcasecmp(argv[0],commands[i].name)==0){
			commands[i].handler(argc,argv);
			break;
		}
	}
}

char *accumulate(char *name){
  char ch;
  int i = 0;
  char backup_buffer[256];
	while(ch != 0x0D){
		while(bufferempty(&cb_RX) == 1);
		dequeue(&cb_RX,&ch,1);
		backup_buffer[i++] = ch;
		putchar(ch);
		if(ch == 0x08){
			printf("\b");
			i--;
		}
		if(ch==0x0D){
			printf("\r");
			break;
		}
		if(ch == 0x0A){
			printf("\n");
			break;
		}
	}
	backup_buffer[i] = '\0';
	__builtin_memcpy(name,backup_buffer,256);
	return (char *)name;
}
