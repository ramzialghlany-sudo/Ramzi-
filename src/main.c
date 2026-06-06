#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "adc.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"

// Global variables
volatile uint16_t adc_value = 0;
volatile uint8_t timer_tick = 0;

// Function to convert ADC value to temperature (LM35 sensor)
// For LM35: Output = 10mV per °C
float Convert_ADC_to_Temperature(uint16_t adc_value) {
    // ADC reference is 5V, 10-bit resolution
    // Voltage = (adc_value / 1024) * 5
    // Temperature = Voltage / 0.01 = (adc_value / 1024) * 500
    return (adc_value * 0.4884765625);  // (5 * 100) / 1024
}

// Timer1 Compare Callback - called every 1 second
void Timer1_Compare_Callback(void) {
    timer_tick = 1;
}

// Initialize System
void System_Init(void) {
    // Initialize peripherals
    UART_Init(UART_BAUD);
    ADC_Init();
    LCD_Init();
    Timer1_Init_Compare(TIMER_COMPARE_VALUE);
    Timer1_Enable_Compare_Interrupt();
    
    // Enable global interrupts
    sei();
    
    // Initial LCD display
    LCD_Clear();
    LCD_Set_Cursor(0, 0);
    LCD_Write_String("Temperature");
    LCD_Set_Cursor(1, 0);
    LCD_Write_String("System Ready");
    _delay_ms(2000);
    
    // UART startup message
    UART_Send_String("\r\n=== AVR Temperature Monitor ===\r\n");
    UART_Send_String("Microcontroller: ATmega328P\r\n");
    UART_Send_String("Clock: 16 MHz\r\n");
    UART_Send_String("UART: 9600 baud\r\n");
    UART_Send_String("ADC Channel: 0 (A0)\r\n");
    UART_Send_String("System initialized...\r\n\r\n");
    
    LCD_Clear();
}

// Main Program
int main(void) {
    System_Init();
    
    float temperature = 0.0;
    uint32_t sample_count = 0;
    
    while (1) {
        // Wait for timer tick (1 second)
        if (timer_tick) {
            timer_tick = 0;
            sample_count++;
            
            // Read ADC value from channel 0
            adc_value = ADC_Read_Channel(0);
            
            // Convert to temperature
            temperature = Convert_ADC_to_Temperature(adc_value);
            
            // Display on LCD
            LCD_Clear();
            LCD_Set_Cursor(0, 0);
            LCD_Write_String("Temp: ");
            LCD_Write_Float(temperature, 1);
            LCD_Write_String("C");
            
            LCD_Set_Cursor(1, 0);
            LCD_Write_String("ADC: ");
            LCD_Write_Integer(adc_value);
            
            // Send via UART
            UART_Send_String("Sample #");
            UART_Send_Integer(sample_count);
            UART_Send_String(" | ADC: ");
            UART_Send_Integer(adc_value);
            UART_Send_String(" | Temp: ");
            UART_Send_Float(temperature, 2);
            UART_Send_String("C\r\n");
            
            // Check for user input
            if (UART_Data_Available()) {
                char cmd = UART_Receive_Char();
                
                switch (cmd) {
                    case 'c':
                    case 'C':
                        // Clear display command
                        LCD_Clear();
                        UART_Send_String("Display cleared\r\n");
                        break;
                        
                    case 'r':
                    case 'R':
                        // Reset counter
                        sample_count = 0;
                        UART_Send_String("Counter reset\r\n");
                        break;
                        
                    case 's':
                    case 'S':
                        // Send status
                        UART_Send_String("System Status: OK\r\n");
                        break;
                        
                    default:
                        UART_Send_String("Unknown command\r\n");
                        break;
                }
            }
        }
    }
    
    return 0;
}
