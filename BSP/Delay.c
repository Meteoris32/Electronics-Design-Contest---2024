#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdio.h>

//CPUCLK_FREQ 32000000     32000000/1000 = 32000 ->1ms 
void delay_ms(uint32_t ms)
{
    while(ms--)
    {
        delay_cycles(CPUCLK_FREQ/1000);
    }
}

void delay_us(uint32_t us)
{
    while(us--)
    {
        delay_cycles(CPUCLK_FREQ/1000000);
    }
}