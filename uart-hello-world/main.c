#include "uart.h"

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    USART0_init(PIN7_bm, PIN6_bm, 9600);

    while (1)
    {
        USART0_sendString("Hello World!\r\n");
        _delay_ms(500);
    }
}
