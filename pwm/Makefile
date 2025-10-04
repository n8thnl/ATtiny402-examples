MCU = attiny402
F_CPU = 3333333
ATTINY_LIB = ${ATTINY_DFP_PATH}
ARDUINO_PORT = ${ARDUINO_COM_PORT}
UPDI_PORT = ${UPDI_COM_PORT}
HEX = main.hex

CC = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS = -B $(ATTINY_LIB)/gcc/dev/attiny402 -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
IFLAGS = -I $(ATTINY_LIB)/include -I../lib

# Source files
SRCS = main.c ../lib/uart.c
OBJS = $(SRCS:.c=.o)

all: main.hex

# Compile all .c files into .o
%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Link all object files into ELF
main.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Convert ELF to HEX
main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash-arduino: $(HEX)
	avrdude -p t402 -c jtag2updi -P $(ARDUINO_PORT) -U flash:w:$<:i

erase-updi:
	pymcuprog erase --device $(MCU) --tool uart --uart $(UPDI_PORT)

flash-updi: erase-updi $(HEX)
	pymcuprog write --device $(MCU) --tool uart --uart $(UPDI_PORT) --filename $(HEX)

clean:
	rm -f *.o *.elf *.hex
