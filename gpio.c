#include "gpio.h"
#include <avr/io.h>

/* Relays:
 * PB0 - Out N
 * PB1 - Out 2
 * PB2 - Out 3
 * PB3 - Out 4
 * PB4 - Out 5
 * PB5 - Out 6
 * PD4 - Out 7
 * PD5 - Out 8
 * PD6 - Out 9
 * PD7 - Out 10
 */

/* USART
 * PD0 - RxD
 * PD1 - TxD
 */

void gpio_set_pin(uint8_t pin, uint8_t value) {
    if (pin >= 1 && pin <= 6) {
        if (value) {
            PORTB |= 1 << (pin - 1);
        } else {
            PORTB &= ~(1 << (pin - 1));
        }
        return;
    }
    
    if (pin >= 7 && pin <= 10) {
        if (value) {
            PORTD |= 1 << (pin - 7 + 4);
        } else {
            PORTD &= ~(1 << (pin - 7 + 4));
        }
        return;
    }
}

void gpio_init(void) {
    /* DIR Registers Initialization */
    DDRB = (1 << DDB5) | (1 << DDB4) | (1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
    DDRD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5) | (1 << DDD4) | (1 << DDD1);

    /* OUT Registers Initialization */
    PORTD = (1 << PORTD1);
}
