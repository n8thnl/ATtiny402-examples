#ifndef __LIB_UART__
#define __LIB_UART__

#define F_CPU 3333333
#define USART0_BAUD_RATE(BAUD_RATE) ((float) (F_CPU * 64 / (16 * (float) BAUD_RATE)) + 0.5)

#ifdef __clang__
#include "avr_stubs.h"
#else
#include <avr/io.h>
#endif

#include <string.h>

void USART0_init(int rx_pin, int tx_pin, int baud_rate);
void USART0_sendChar(char c);
void USART0_sendString(char* str);

#endif
