#include <avr/io.h>
#include <util/delay.h>

#define PORT_NUM 1      // PA<X> where X is the port number (i.e. PA1)

int main(void) {
    PORTA.DIR |= (1 << PORT_NUM);

    while (1) {
        PORTA.OUTTGL = (1 << PORT_NUM);
        _delay_ms(1000);
    }
}
