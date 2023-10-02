

/**
 * main.c
 */
#include <stdio.h>
#include "clock.h"
#include "gpio.h"
#include "dma.h"
#include "adc0.h"
#include "tm4c123gh6pm.h"
#include "uart0.h"

uint16_t trash;

void aoaAdc0InterruptHandler(void)
{
    /*trash = ADC0_SSFIFO0_R;
    trash = ADC0_SSFIFO0_R;
    trash = ADC0_SSFIFO0_R;
    trash = ADC0_SSFIFO0_R;
    trash = ADC0_SSFIFO0_R;
    trash = ADC0_SSFIFO0_R;
    */

    if( 0 == (dmaControlBlockMem[14].controlWord & 0x3)) {
        putsUart0("complete\n");
    }

    UDMA_SWREQ_R = (1 << 14);
    ADC0_ISC_R = 0x1;
}

int main(void)
{
    initSystemClockTo40Mhz();
    initAdc0();
    initDma();
    initUart0();
    setUart0BaudRate(115200, 40e6);

    UDMA_SWREQ_R = (1 << 14);

    putsUart0("start dma\n");

    while(1)
    {
        if(ADC0_OSTAT_R & ADC_OSTAT_OV0) {
            ADC0_OSTAT_R = ADC_OSTAT_OV0;
            putsUart0("ADC0 overflow \n");
        }
    }

	return 0;
}
