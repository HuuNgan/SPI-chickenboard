#include <HC595/HC595.h>
#include <msp430.h>
#include <Basic_Config/Basic_config.h>
#include <SPI/SPI.h>
#include <stdint.h>

#define delay 200000            // 0.2s
uint8_t i = 0xFF;
uint8_t n=1;


void display1(void);
void display2(void);
void display3(void);
void display4(void);


/**
 * main.c
 */
void main(void)
{
	Config_stop_WDT();	// stop watchdog timer
	Config_Clocks();
	Config_SPI_A();
	Config_HC595();
	
	while(1)
	{
	    if ((n>0)&&(n<6))           display1();
	    else if ((n>5)&&(n<11))     display2();
	    else if ((n>10)&&(n<16))    display3();
	    else if ((n>15)&&(n<21))    display4();
	    else if (n>20)              n = 1;
	}

}


void display1(void)
{
    i=0xAA;
    Send_byte_A(i, 3);
    P1OUT &=~ latch;
    P1OUT |= latch;
    __delay_cycles(delay);
    i = ~i;
    Send_byte_A(i, 3);
    P1OUT &=~ latch;
    P1OUT |= latch;
    __delay_cycles(delay);
    n++;
}

void display2(void)
{
    i = 0xFF;
    while(n<11)
    {
        if(i!=0)
        {
            Send_byte_A(i, 3);
            P1OUT &=~ latch;
            P1OUT |= latch;
            __delay_cycles(delay);
            i=i<<1;
        }
        else
        {
            Send_byte_A(i, 3);
            P1OUT &=~ latch;
            P1OUT |= latch;
            __delay_cycles(delay);
            i=0xFF;
            n++;
        }
    }
}

void display3(void)
{
    i=1;
    int a;
    while ((i!=0)&&(i<=128))
    {
        a = ~i;
        Send_byte_A(a, 3);
        P1OUT &=~ latch;
        P1OUT |= latch;
        i = i<<1;
        __delay_cycles(delay);
    }
    n++;
}

void display4(void)
{
    i=1;
    while ((i!=0)&&(i<=128))
    {
        Send_byte_A(i, 3);
        P1OUT &=~ latch;
        P1OUT |= latch;
        i = i<<1;
        __delay_cycles(delay);
    }
    n++;
}
