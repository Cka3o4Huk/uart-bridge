CC=avr-gcc
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega328
F_CPU=16000000UL

OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

PORT=/dev/cuaU0
BAUD=57600
PROTOCOL=arduino
PART=$(MCU)
AVRDUDE=avrdude -F -V

RM=rm -f

.PHONY: all
all: main.hex

main.hex: main.elf
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom main.elf main.hex

main.elf: main.s
	$(CC) $(CFLAGS) -s -o main.elf main.s

main.s: main.c
	$(CC) $(CFLAGS) -S -o main.s main.c

.PHONY: clean
clean:
	$(RM) main.elf main.hex main.s

.PHONY: upload
upload: main.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) -b $(BAUD) -U flash:w:main.hex

