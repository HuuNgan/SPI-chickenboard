#include <msp430g2553.h>
#include "Basic_config.h"
#include "SPI.h"

#define DIG1    BIT0        //P1.0
#define DIG2    BIT7        //P2.7
#define DIG3    BIT6        //P2.6
#define DIG4    BIT5        //P2.5
#define latch   BIT5        //P1.5

int i=0;
int b[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    Config_SPI_A();

    P2SEL &=~ (DIG2 + DIG3 + DIG4);
    P2SEL2 &=~ (DIG2 + DIG3 + DIG4);
    P1SEL &=~ (DIG1 + latch);
    P1SEL2 &=~ (DIG1 + latch);

    P1DIR |= (DIG1 + latch) ;
    P2DIR |= (DIG2 + DIG3 + DIG4);
    P1OUT &=~ DIG1;
    P2OUT |= (DIG2 + DIG3 + DIG4);


    while(1)
    {
        Send_byte_A(b[i], 1000);

        P1OUT |= latch;
        P1OUT &=~ latch;

        __delay_cycles(500000);

        i++;
        if(i==10)
        {
            i = 0;
        }
    }
}

