#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// LCD Initialization
void LCD_Init(void);

// LCD Commands
void LCD_Send_Command(uint8_t cmd);
void LCD_Send_Data(uint8_t data);

// LCD Display Functions
void LCD_Clear(void);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Write_String(const char *str);
void LCD_Write_Char(char ch);
void LCD_Write_Integer(int16_t num);
void LCD_Write_Float(float num, uint8_t decimal_places);

// LCD Control
void LCD_Cursor_On(void);
void LCD_Cursor_Off(void);
void LCD_Display_On(void);
void LCD_Display_Off(void);

#endif // LCD_H
