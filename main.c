#include "usart.h"
#include "adc.h"
#include <stdio.h>

void cpu_init(void);

int main(void) {
    cpu_init();
    usart_init();
    adc_init();
    
    printf("Starting main loop!\n");
    while (1) {
        adc_loop();
    }
}
