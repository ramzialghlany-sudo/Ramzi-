#include "uart.h"
#include "config.h"
#include <avr/io.h>
#include <stdio.h>

// Initialize UART
void UART_Init(uint32_t baud_rate) {
    uint16_t ubrr = (F_CPU / (16UL * baud_rate)) - 1;
    
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable transmitter and receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Send single character
void UART_Send_Char(char ch) {
    // Wait for transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Send character
    UDR0 = ch;
}

// Receive single character
char UART_Receive_Char(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    
    // Return received character
    return UDR0;
}

// Send string
void UART_Send_String(const char *str) {
    while (*str) {
        UART_Send_Char(*str++);
    }
}

// Receive string
void UART_Receive_String(char *buffer, uint8_t max_length) {
    uint8_t count = 0;
    char ch;
    
    while (count < max_length - 1) {
        ch = UART_Receive_Char();
        
        if (ch == '\r' || ch == '\n') {
            break;
        }
        
        buffer[count++] = ch;
    }
    
    buffer[count] = '\0';  // Null terminate
}

// Send integer
void UART_Send_Integer(int16_t num) {
    char buffer[10];
    sprintf(buffer, "%d", num);
    UART_Send_String(buffer);
}

// Send float
void UART_Send_Float(float num, uint8_t decimal_places) {
    char buffer[20];
    char format[10];
    sprintf(format, "%%.%df", decimal_places);
    sprintf(buffer, format, num);
    UART_Send_String(buffer);
}

// Check if data is available
uint8_t UART_Data_Available(void) {
    return (UCSR0A & (1 << RXC0));
}
