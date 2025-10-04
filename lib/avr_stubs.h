#ifndef AVR_STUBS_REAL_H
#define AVR_STUBS_REAL_H

#include <stdint.h>

// Make clangd understand _SFR_IO8 macro
#ifdef __clang__
#define _SFR_IO8(io_addr) (*(volatile uint8_t*)(io_addr))
#endif

// GPIO Registers
#define PORTA _SFR_IO8(0x00)
#define PINA  _SFR_IO8(0x01)
#define DDRA  _SFR_IO8(0x02)

#define PORTB _SFR_IO8(0x03)
#define PINB  _SFR_IO8(0x04)
#define DDRB  _SFR_IO8(0x05)

// USART0 Registers
#define USART0_DATA    _SFR_IO8(0x0C)
#define USART0_STATUS  _SFR_IO8(0x0D)
#define USART0_CTRLA   _SFR_IO8(0x0E)
#define USART0_CTRLB   _SFR_IO8(0x0F)
#define USART0_CTRLC   _SFR_IO8(0x10)
#define USART0_BAUD    _SFR_IO8(0x11)

// USART0 bits (for convenience)
#define USART_RXC0  7
#define USART_TXC0  6
#define USART_DRE0  5
#define USART_RXEN0 4
#define USART_TXEN0 3
#define USART_CSZ00 1
#define USART_CSZ01 2

#endif
