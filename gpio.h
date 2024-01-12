#ifndef GPIO_H
#define	GPIO_H

#include <stdint.h>

void gpio_set_pin(uint8_t pin, uint8_t value);

void gpio_init(void);

#endif	/* GPIO_H */

