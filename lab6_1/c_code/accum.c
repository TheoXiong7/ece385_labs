//mb_blink.c
//
//Provided boilerplate "LED Blink" code for ECE 385
//First released in ECE 385, Fall 2023 distribution
//
//Note: you will have to refer to the memory map of your MicroBlaze
//system to find the proper address for the LED GPIO peripheral.
//
//Modified on 7/25/23 Zuofu Cheng

#include <stdio.h>
#include <xparameters.h>
#include <xil_types.h>
#include <sleep.h>

#include "platform.h"

volatile uint32_t* led_gpio_data = 0x40000000;
volatile uint32_t* switch_gpio = 0x40010000;
volatile uint32_t* btn_gpio = 0x40020000;


int main()
{
    init_platform();
    uint16_t sum = 0;

    uint32_t last_val = 0;

	while (1)
	{
		uint32_t cur_val = !(*btn_gpio & 0x01);

		if ((last_val != cur_val) && cur_val) {
			sum += *switch_gpio;
			xil_printf("Accumulated %u!!!!!\n", sum);
			xil_printf("%u pressed\n", *btn_gpio);
		}
		*led_gpio_data = sum;
		last_val = cur_val;
	}

    cleanup_platform();

    return 0;
}
