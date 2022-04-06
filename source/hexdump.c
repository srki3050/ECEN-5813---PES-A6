/*
 * File : Hexdump.c
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: Prints the hexdump functionality based on start address and length provided.
 * References: https://cuboulder.zoom.us/rec/play/LJDJOrUqF0pR5j5Y7qVGKxTS7Gic8lw3VUG14L
 * 			   -YH53VwRnyJAMKd6McTHrC9bfhdS5Eya4g9iQWn40O.N8FOlEG-X_rxjqFz?startTime=1643127721000 timestamp 1:00:00
 * 			   atoi function - https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
 * 			   sscanf function - https://www.educative.io/edpresso/how-to-read-data-using-sscanf-in-c
 * 			   Discussed with Swapnil Ghonge to move the pointer in hexdump programming
 */
#include "hexdump.h"

#define STRIDE 16
#define MAX_ALLOWED_LENGTH 640

static char int_to_hexchar(int x)
{
	if (x >=0 && x < 10)
		return '0' + x;
	else if (x >= 10 && x < 16)
		return 'A' + x - 10;
	else
		return '-';
}

void hexdump(char* start_address, char* no_of_bytes)
{
	int address_start;			//integer to store parsed_address
	int parsed_length;			//integer to store parsed_length
	uint8_t* start_location; 	//address in uint8_t
	//Address is parsed as an integer (atoi can also be used, but using sscanf() because it was a required element for the assignment
	sscanf(start_address,"%x",&address_start);
	if(tolower(*(no_of_bytes+1))=='x')
		sscanf(no_of_bytes,"%x",&parsed_length);
	else
		sscanf(no_of_bytes,"%d",&parsed_length);

	start_location = (uint8_t*)atoi(start_address); //store address
	//check if parsed_length is within limits (0-640)
	if(parsed_length<=MAX_ALLOWED_LENGTH)
	{
		for(int i =1;i<=parsed_length; i++)
		{
			int j =1;
			//At this scenario, we need to print the address "0000_0000"
			putchar(int_to_hexchar((((uint32_t)address_start & 0xF0000000)>>28)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x0F000000)>>24)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x00F00000)>>20)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x000F0000)>>16)));
			putchar('_');
			putchar(int_to_hexchar((((uint32_t)address_start & 0x0000F000)>>12)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x00000F00)>>8)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x000000F0)>>4)));
			putchar(int_to_hexchar((((uint32_t)address_start & 0x0000000F))));
			putchar(' ');
			//Return to a new line if this is the last element
			if(i==(int)parsed_length)
			{
				printf("%02x ",*(start_location)); //print last byte
				break;
			}
			//Until then, print the addresses
			while (j % STRIDE != 0)
			{
				printf("%02x ",*(start_location));
				start_location++;
				address_start++;
				j++;
			}
			parsed_length-=STRIDE;
			start_location++;
			address_start++;
			printf("\r\n");
		}
	}
	else
		printf("Please Enter a valid length\n\r");
}
