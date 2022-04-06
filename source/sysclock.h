/* 
 * sysclock.h - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 */
/* Name  		: Sricharan Kidambi S
 * File  		: Sysclock.h
 * Date	 		: 04/06/2022
 * Brief 		: prototype for System clock (24MHz) generation.
 * References	: This file was provided by Howdy pierce at the start of the assignment.
 */
#ifndef _SYSCLOCK_H_
#define _SYSCLOCK_H_

#define SYSCLOCK_FREQUENCY (24000000U)

/*
 * Initializes the system clock. You should call this first in your
 * program.
 */
void sysclock_init();

#endif  // _SYSCLOCK_H_
