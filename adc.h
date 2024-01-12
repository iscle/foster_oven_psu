#ifndef ADC_H
#define	ADC_H

#include <stdint.h>

#define ADC_INT_REF_MV 1100
#define ADC_RESOLUTION 10

#define ADC_IN3_CHANNEL     2
#define ADC_RT1_CHANNEL     5
#define ADC_CIBO_CHANNEL    6
#define ADC_CAMERA_CHANNEL  7
#define ADC_INT_REF_CHANNEL 14

uint16_t adc_get_int_ref(void);
uint16_t adc_get_in3(void);
uint16_t adc_get_rt1(void);
uint16_t adc_get_cibo(void);
uint16_t adc_get_camera(void);

void adc_loop(void);
void adc_init(void);

#endif	/* ADC_H */

