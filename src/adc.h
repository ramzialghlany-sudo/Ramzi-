#ifndef ADC_H
#define ADC_H

#include <stdint.h>

// ADC Initialization
void ADC_Init(void);

// ADC Channel Selection and Reading
void ADC_Select_Channel(uint8_t channel);
uint16_t ADC_Read(void);
uint16_t ADC_Read_Channel(uint8_t channel);

// ADC Conversion Complete Check
uint8_t ADC_Is_Conversion_Complete(void);

#endif // ADC_H
