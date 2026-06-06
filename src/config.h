#ifndef CONFIG_H
#define CONFIG_H

// Microcontroller Configuration
#define F_CPU 16000000UL  // 16 MHz clock

// UART Configuration
#define UART_BAUD 9600
#define UART_BUFFER_SIZE 64

// ADC Configuration
#define ADC_REFERENCE AVCC  // Reference voltage
#define ADC_PRESCALER 128   // Clock prescaler

// LCD Configuration
#define LCD_DATA_PORT PORTD
#define LCD_CTRL_PORT PORTB
#define LCD_RS 0  // Register Select
#define LCD_RW 1  // Read/Write
#define LCD_EN 2  // Enable

// Timer Configuration
#define TIMER_PRESCALER 1024
#define TIMER_COMPARE_VALUE 15625  // 1 second at 16MHz with 1024 prescaler

#endif // CONFIG_H
