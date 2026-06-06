#include "timer.h"
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Global timer flags
volatile uint8_t timer1_overflow_flag = 0;

// Timer0 Initialization (8-bit)
void Timer0_Init(void) {
    // Set prescaler to 1024
    TCCR0B = (1 << CS02) | (1 << CS00);
    
    // Normal mode (overflow)
    TCCR0A = 0x00;
}

// Stop Timer0
void Timer0_Stop(void) {
    TCCR0B = 0x00;
}

// Read Timer0 value
uint8_t Timer0_Read(void) {
    return TCNT0;
}

// Set Timer0 value
void Timer0_Set(uint8_t value) {
    TCNT0 = value;
}

// Timer1 Initialization (16-bit)
void Timer1_Init(void) {
    // Set prescaler to 1024
    TCCR1B = (1 << CS12) | (1 << CS10);
    
    // Normal mode
    TCCR1A = 0x00;
}

// Stop Timer1
void Timer1_Stop(void) {
    TCCR1B = 0x00;
}

// Initialize Timer1 in Compare mode
void Timer1_Init_Compare(uint16_t compare_value) {
    // Clear Timer/Counter register
    TCNT1 = 0;
    
    // Set compare value
    OCR1A = compare_value;
    
    // CTC mode (Clear Timer on Compare)
    TCCR1B = (1 << WGM12);
    
    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

// Enable Timer1 Compare Match interrupt
void Timer1_Enable_Compare_Interrupt(void) {
    TIMSK1 = (1 << OCIE1A);
}

// Disable Timer1 Compare Match interrupt
void Timer1_Disable_Compare_Interrupt(void) {
    TIMSK1 = 0x00;
}

// Timer1 Compare Match Interrupt Handler
ISR(TIMER1_COMPA_vect) {
    timer1_overflow_flag = 1;
    Timer1_Compare_Callback();
}

// Timer1 Compare Callback (user-defined)
void Timer1_Compare_Callback(void) {
    // This function can be overridden by the user
    // Default: do nothing
}

// Delay milliseconds
void Delay_ms(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}

// Delay microseconds
void Delay_us(uint16_t us) {
    while (us--) {
        _delay_us(1);
    }
}
