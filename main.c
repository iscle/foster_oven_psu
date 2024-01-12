#include "cpu.h"
#include "usart.h"
#include "adc.h"
#include "gpio.h"
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>

int main(void) {
    cpu_init();
    usart_init();
    adc_init();
    
    printf("Starting main loop!\n");
    
    gpio_set_pin(1, 1);
    
    while (1) {
        adc_loop();
        _delay_ms(1000);
        gpio_set_pin(9, 1);
        _delay_ms(1000);
        gpio_set_pin(9, 0);
    }
}
