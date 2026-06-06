#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

// Timer0 Functions
void Timer0_Init(void);
void Timer0_Stop(void);
uint8_t Timer0_Read(void);
void Timer0_Set(uint8_t value);

// Timer1 Functions
void Timer1_Init(void);
void Timer1_Stop(void);
void Timer1_Init_Compare(uint16_t compare_value);
void Timer1_Enable_Compare_Interrupt(void);
void Timer1_Disable_Compare_Interrupt(void);

// Delay Functions
void Delay_ms(uint16_t ms);
void Delay_us(uint16_t us);

// Timer Callbacks
void Timer1_Compare_Callback(void);

#endif // TIMER_H
