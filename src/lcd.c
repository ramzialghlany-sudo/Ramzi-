#include "lcd.h"
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Private function declarations
static void LCD_Pulse_EN(void);
static void LCD_Write_Nibble(uint8_t nibble);
static void LCD_Write_Byte(uint8_t byte, uint8_t mode);

// Initialize LCD
void LCD_Init(void) {
    // Set data port as output
    DDRD = 0xFF;  // Port D as output for data
    DDRB = 0xFF;  // Port B as output for control
    
    _delay_ms(20);
    
    // Initialize in 4-bit mode
    LCD_Write_Nibble(0x03);
    _delay_ms(5);
    LCD_Write_Nibble(0x03);
    _delay_us(100);
    LCD_Write_Nibble(0x03);
    _delay_ms(5);
    
    // Set to 4-bit mode
    LCD_Write_Nibble(0x02);
    _delay_us(100);
    
    // Configure display
    LCD_Send_Command(0x28);  // 4-bit mode, 2 lines
    LCD_Send_Command(0x0C);  // Display ON, Cursor OFF
    LCD_Send_Command(0x01);  // Clear display
    _delay_ms(2);
    LCD_Send_Command(0x06);  // Entry mode set
}

// Send command to LCD
void LCD_Send_Command(uint8_t cmd) {
    LCD_Write_Byte(cmd, 0);  // 0 for command
}

// Send data to LCD
void LCD_Send_Data(uint8_t data) {
    LCD_Write_Byte(data, 1);  // 1 for data
}

// Clear LCD display
void LCD_Clear(void) {
    LCD_Send_Command(0x01);
    _delay_ms(2);
}

// Set cursor position
void LCD_Set_Cursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (0x40 + col);
    LCD_Send_Command(0x80 | address);
}

// Write string to LCD
void LCD_Write_String(const char *str) {
    while (*str) {
        LCD_Send_Data(*str++);
    }
}

// Write character to LCD
void LCD_Write_Char(char ch) {
    LCD_Send_Data(ch);
}

// Write integer to LCD
void LCD_Write_Integer(int16_t num) {
    char buffer[10];
    sprintf(buffer, "%d", num);
    LCD_Write_String(buffer);
}

// Write float to LCD
void LCD_Write_Float(float num, uint8_t decimal_places) {
    char buffer[20];
    char format[10];
    sprintf(format, "%%.%df", decimal_places);
    sprintf(buffer, format, num);
    LCD_Write_String(buffer);
}

// Enable cursor
void LCD_Cursor_On(void) {
    LCD_Send_Command(0x0E);
}

// Disable cursor
void LCD_Cursor_Off(void) {
    LCD_Send_Command(0x0C);
}

// Turn display ON
void LCD_Display_On(void) {
    LCD_Send_Command(0x0C);
}

// Turn display OFF
void LCD_Display_Off(void) {
    LCD_Send_Command(0x08);
}

// Private: Pulse Enable pin
static void LCD_Pulse_EN(void) {
    PORTB |= (1 << LCD_EN);
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN);
    _delay_us(100);
}

// Private: Write nibble (4-bit)
static void LCD_Write_Nibble(uint8_t nibble) {
    PORTD = (PORTD & 0x0F) | ((nibble & 0x0F) << 4);
    LCD_Pulse_EN();
}

// Private: Write byte to LCD
static void LCD_Write_Byte(uint8_t byte, uint8_t mode) {
    // Set RS (Register Select) pin
    if (mode) {
        PORTB |= (1 << LCD_RS);   // Data mode
    } else {
        PORTB &= ~(1 << LCD_RS);  // Command mode
    }
    
    // Clear RW pin (write mode)
    PORTB &= ~(1 << LCD_RW);
    
    // Send high nibble
    LCD_Write_Nibble(byte >> 4);
    
    // Send low nibble
    LCD_Write_Nibble(byte);
    
    _delay_us(100);
}
