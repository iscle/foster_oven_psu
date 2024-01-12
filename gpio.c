#include "gpio.h"
#include <avr/io.h>

void gpio_init(void) {
    /* DIR Registers Initialization */
    DDRB = 0x3F;
    DDRC = 0x00;
    DDRD = 0xF2;

    /* OUT Registers Initialization */
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x02;

    /* PINxCTRL registers Initialization */
    PINB = 0x00;
    PINC = 0x00;
    PIND = 0x00;
}
