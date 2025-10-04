#include "uart.h"

void USART0_init(int rx_pin, int tx_pin, int baud_rate)
{
    PORTA.DIR &= ~rx_pin;
    PORTA.DIR |= tx_pin;

    USART0.BAUD = (uint16_t) USART0_BAUD_RATE(baud_rate);
    USART0.CTRLB |= USART_TXEN_bm;

    // todo: enable rx
}

void USART0_sendChar(char c)
{
    while (! (USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }
    USART0.TXDATAL = c;
}

void USART0_sendString(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        USART0_sendChar(str[i]);
    }
}
