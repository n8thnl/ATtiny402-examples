MCU = attiny402
F_CPU = 3333333 
ATTINY_LIB = ${ATTINY_DFP_PATH}
ARDUINO_PORT = ${ARDUINO_COM_PORT}

CC = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS = -B $(ATTINY_LIB)/gcc/dev/attiny402 -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
IFLAGS = -I $(ATTINY_LIB)/include

all: main.hex

main.elf: main.c
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $<

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: main.hex
	avrdude -p t402 -c jtag2updi -P $(ARDUINO_PORT) -U flash:w:$<:i

clean:
	rm -f *.elf *.hex

