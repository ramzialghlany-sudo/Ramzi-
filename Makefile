# Makefile for AVR Project

# Microcontroller
MCU = atmega328p
F_CPU = 16000000UL

# Programmer
PROGRAMMER = usbtiny
PORT = /dev/ttyUSB0

# Compiler
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c99
LDFLAGS = -mmcu=$(MCU)

# Source files
SRCS = src/main.c src/adc.c src/lcd.c src/uart.c src/timer.c
OBJS = $(SRCS:.c=.o)
TARGET = main

# Rules
all: $(TARGET).hex $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$<:i

verify: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:v:$<:i

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).bin

.PHONY: all program verify clean
