/* 
 * sysclock.c - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 *
 * See section 24 of the KL25Z Reference Manual to understand this code
 *
 * Inspired by https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/

 */
/* Name  		: Sricharan Kidambi S
 * File  		: Sysclock.c
 * Date	 		: 04/06/2022
 * Brief 		: System clock (24MHz) generation.
 * References	: This file was provided by Howdy pierce at the start of the assignment.
 */

#include "MKL25Z4.h"
#include "sysclock.h"


void
sysclock_init()
{
  // Corresponds to FEI mode as shown in sec 24.4.1 

  // Select PLL/FLL as clock source 
  MCG->C1 &= ~(MCG_C1_CLKS_MASK); //0xC0U - 11000000, hence negating bit 6 and bit 7 selects the PLL/FLL source
  MCG->C1 |= MCG_C1_CLKS(0);//0x00;
	
  // Use internal reference clock as source for the FLL
  MCG->C1 |= MCG_C1_IREFS(1);//(1 << 2) & 4 = 2, turning bit 2 on selects the slow internal reference clock.

  // Select the FLL (by setting "PLL select" to 0)
  MCG->C6 &= ~(MCG_C6_PLLS_MASK); // negating with value 01000000 .i.e 6th bit to 0. selects FLL clock
  MCG->C6 |= MCG_C6_PLLS(0);//0x00;

  // Select 24 MHz - see table for MCG_C4[DMX32]
  MCG->C4 &= ~(MCG_C4_DRST_DRS_MASK & MCG_C4_DMX32_MASK);//0x60, negating 5th and 6th bit to 0, - low range clock
  MCG->C4 |= MCG_C4_DRST_DRS(0);//0x00
  MCG->C4 |= MCG_C4_DMX32(1);//turning the 7th bit to 1. by this point 7-5th bit = 100
  //24MHz system clock generated.
}

