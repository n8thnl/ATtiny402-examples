#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

volatile uint16_t last_tick = 0;
volatile uint16_t ticks = 0;

int main(void) {

    USART0_init(PIN7_bm, PIN6_bm, 9600);

    PORTA.DIRCLR = PIN2_bm | PIN7_bm;

    PORTA.PIN2CTRL |= PORT_ISC_RISING_gc;  // Trigger on falling edge
    PORTA.INTFLAGS = PIN2_bm;    // Enable interrupt with low priority

    // --- Setup timer TCA0 as a 1ms system tick
    TCA0.SINGLE.PER = 3332; // 20 MHz / 20000 = 1 kHz = 1ms
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    sei();

    while (1) {
        ;
    }
}

ISR(TCA0_OVF_vect) {
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
    ticks++;  // 1 ms tick (depends on prescaler setup)
}

ISR(PORTA_PORT_vect) {
    PORTA.INTFLAGS = PIN2_bm;

    uint16_t now = ticks;
    if ((uint16_t)(now - last_tick) < 2) { // 20 ms debounce window
        return; // Ignore bounce
    }
    last_tick = now;

    // encoder docs: https://www.sameskydevices.com/product/resource/ring23.pdf
    if (PORTA.IN & PIN7_bm) {
        USART0_sendString("clockwise\r\n");
    } else {
        USART0_sendString("counter-clockwise\r\n");
    }
}
