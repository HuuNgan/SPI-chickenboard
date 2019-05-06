/*
 * HC595.c
 *
 *  Created on: Feb 24, 2019
 *      Author: HuuNgan
 */

#include <HC595/HC595.h>

void Config_HC595(void)
{
    P1SEL &=~ latch;
    P1SEL2 &=~ latch;       //Chosing GPIO

    P1DIR |= latch;         //Set as Output Pin
}


