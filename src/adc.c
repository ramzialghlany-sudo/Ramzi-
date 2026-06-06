#include "adc.h"
#include "config.h"
#include <avr/io.h>

// Initialize ADC
void ADC_Init(void) {
    // Set reference voltage to AVCC
    ADMUX = (1 << REFS0);
    
    // Enable ADC and set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Select ADC Channel
void ADC_Select_Channel(uint8_t channel) {
    channel &= 0x07;  // Ensure channel is 0-7
    ADMUX = (ADMUX & 0xF8) | channel;
}

// Read ADC Value (blocking)
uint16_t ADC_Read(void) {
    // Start conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion complete
    while (ADCSRA & (1 << ADSC));
    
    // Return ADC value (10-bit)
    return ADC;
}

// Read from specific channel
uint16_t ADC_Read_Channel(uint8_t channel) {
    ADC_Select_Channel(channel);
    return ADC_Read();
}

// Check if conversion is complete
uint8_t ADC_Is_Conversion_Complete(void) {
    return !(ADCSRA & (1 << ADSC));
}
