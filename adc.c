#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>

static uint8_t adc_channels[] = {
    ADC_INT_REF_CHANNEL, // Always keep at position 0
    ADC_IN3_CHANNEL,
    ADC_RT1_CHANNEL,
    ADC_CIBO_CHANNEL,
    ADC_CAMERA_CHANNEL,
};
static const unsigned int adc_channels_count = sizeof(adc_channels) / sizeof(*adc_channels);
static unsigned int current_adc_channel_idx = 0;

static bool measure_adc = false;

static uint16_t int_ref = 0;
static uint16_t in3 = 0;
static uint16_t rt1 = 0;
static uint16_t cibo = 0;
static uint16_t camera = 0;

ISR(ADC_vect) {
    uint16_t result = (ADCL | ADCH << 8);
    
    switch (adc_channels[current_adc_channel_idx]) {
        case ADC_INT_REF_CHANNEL:
            printf("INT_REF ADC result: %u\n", result);
            int_ref = result;
            break;
        case ADC_IN3_CHANNEL:
            printf("IN3 ADC result: %u\n", result);
            in3 = result;
            break;
        case ADC_RT1_CHANNEL:
            printf("RT1 ADC result: %u\n", result);
            rt1 = result;
            break;
        case ADC_CIBO_CHANNEL:
            printf("CIBO ADC result: %u\n", result);
            cibo = result;
            break;
        case ADC_CAMERA_CHANNEL:
            printf("CAMERA ADC result: %u\n", result);
            camera = result;
            break;
    }
    
    current_adc_channel_idx = (current_adc_channel_idx + 1) % adc_channels_count;
    
    // Clear interrupt flag
    ADCSRA |= (1 << ADIF);
    measure_adc = true;
}

uint16_t adc_get_int_ref(void) {
    cli();
    uint16_t value = int_ref;
    sei();
    return value;
}

uint16_t adc_get_in3(void) {
    cli();
    uint16_t value = in3;
    sei();
    return value;
}

uint16_t adc_get_rt1(void) {
    cli();
    uint16_t value = rt1;
    sei();
    return value;
}

uint16_t adc_get_cibo(void) {
    cli();
    uint16_t value = cibo;
    sei();
    return value;
}

uint16_t adc_get_camera(void) {
    cli();
    uint16_t value = camera;
    sei();
    return value;
}

void adc_loop(void) {
    if (measure_adc) {
        measure_adc = false;
        ADMUX &= ~0x0f;
        ADMUX |= adc_channels[current_adc_channel_idx] & 0x0f;
        _delay_us(500);
        ADCSRA |= (1 << ADSC);
    }
}

void adc_init(void) {
    // Reference = AVCC with external capacitor at AREF pin
    // Analog channel = 1.1V (VBG)
    ADMUX = (1 << REFS0) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1);
    
    // ADC enable = 1
    // ADC interrupt enable = 1
    // ADC prescaler = 128 (62500 Hz)
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
    measure_adc = true;
}