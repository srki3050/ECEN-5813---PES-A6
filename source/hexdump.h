/*
 * File : Hexdump.h
 * Name : Sricharan Kidambi. S
 * Date : 04/06/2022
 * Brief: prototype to Print the hexdump functionality based on start address and length provided.
 * References: Inspired from Lecture 5 by professor howdy pierce.
 */
#ifndef HEXDUMP_H_
#define HEXDUMP_H_
#include "stdint.h"
#include "stddef.h"

char *hexdump(char *start,char *len);

#endif /* HEXDUMP_H_ */
