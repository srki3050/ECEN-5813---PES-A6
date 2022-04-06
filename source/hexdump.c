/*
 * File : Hexdump.c
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: Prints the hexdump functionality based on start address and length provided.
 * References: Inspired from Lecture 5 by professor howdy pierce.
 */
#include "hexdump.h"
#include "string.h"
#define STRIDE 16

static char int_to_hexchar(int x)
{
	if (x >=0 && x < 10)
		return '0' + x;
	else if (x >= 10 && x < 16)
		return 'A' + x - 10;
	else
		return '-';
}
char *hexdump(char *start,char *len){
	int address;
	int length;
	uint8_t *start_address;
	sscanf(start_address,"%x",&address);
	if(tolower(*(len+1))=='x'){
		sscanf(len,"%x",&length);
	}
	else{
		sscanf(len,"%d",&length);
	}
	start_address = (uint8_t *)atoi(start);
	if(len < 640){
		for(int i = 1;i <= length;i++){
			int j = 1;
			putchar(int_to_hexchar((((uint32_t)address & 0xF0000000)>>28)));
			putchar(int_to_hexchar((((uint32_t)address & 0x0F000000)>>24)));
			putchar(int_to_hexchar((((uint32_t)address & 0x00F00000)>>20)));
			putchar(int_to_hexchar((((uint32_t)address & 0x000F0000)>>16)));
			putchar('_');
			putchar(int_to_hexchar((((uint32_t)address & 0x0000F000)>>12)));
			putchar(int_to_hexchar((((uint32_t)address & 0x00000F00)>>8)));
			putchar(int_to_hexchar((((uint32_t)address & 0x000000F0)>>4)));
			putchar(int_to_hexchar((((uint32_t)address & 0x0000000F))));
			putchar(' ');
			if(i==(int)len) //check if i= length last byte to print
			{
				printf("%02x ",*(start_address)); //print last byte
				break;
			}
			while (j % STRIDE != 0)
			{

				printf("%02x ",*(start_address)); //print byte at address
				start_address++; //increment address
				address++; //increment add
				j++;//increment counter

			}
			length-=16; //decrement length
			start_address++; //increment for last address 16
			address++;
			printf("\r\n");
		}
		printf("\r\n");
	}
	else
	{
		printf("Please Enter a valid length\n\r");
	}
}
