#ifndef UART_H
#define UART_H

#include <stdint.h>

// UART Initialization
void UART_Init(uint32_t baud_rate);

// UART Send and Receive
void UART_Send_Char(char ch);
char UART_Receive_Char(void);

// UART String Operations
void UART_Send_String(const char *str);
void UART_Receive_String(char *buffer, uint8_t max_length);

// UART Data Type Operations
void UART_Send_Integer(int16_t num);
void UART_Send_Float(float num, uint8_t decimal_places);

// UART Status Check
uint8_t UART_Data_Available(void);

#endif // UART_H
