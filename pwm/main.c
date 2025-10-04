#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

// Calculated values for ~1kHz PWM at 50% duty cycle with Prescaler /4
#define PWM_PERIOD_VAL    832    // PER = (3333333 / 4 / 1000) - 1
#define PWM_DUTY_50_VAL   416    // CMP0 = 832 * 0.5
#define PWM_DUTY_75_VAL   624    // CPM0 = 832 * 0.75
#define PWM_DUTY_90_VAL   748

void TCA0_init(void) {
    // 1. Set the PWM output pin (PA3 for WO0) as output
    // VPORTA is used for direct port access in modern tinyAVRs
    VPORTA.DIR |= PIN3_bm;

    // 2. Configure the multiplexer to output TCA0's WO0 to PA3
    // PORTMUX.CTRLC has the register for TCA0/TCA1 output routing
    // Use the default position (WO0 on PA3) - this is often the default
    // and might not be strictly necessary if the default is PA3.
    // However, it's good practice. For ATtiny402, TCA0_WO0 defaults to PA3.
    // This example assumes TCA0_WO0 is the pin being used.
    // Consult the datasheet's I/O pin-out and PORTMUX register details for your specific part.

    // 3. Set the Period (TOP) value
    TCA0.SINGLE.PER = PWM_PERIOD_VAL;

    // 4. Set the Compare (Duty Cycle) value for Channel 0
    TCA0.SINGLE.CMP0 = PWM_DUTY_90_VAL;

    // 5. Configure the Waveform Generation Mode and Output Enable
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm     // Enable Compare Channel 0 Output (WO0)
                      | TCA_SINGLE_WGMODE_SINGLESLOPE_gc; // Single-Slope PWM mode

    // 6. Set the clock prescaler and enable the timer
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm    // Enable TCA0
                      | TCA_SINGLE_CLKSEL_DIV4_gc; // Set clock prescaler to CLK_PER/4
}


int main(void) {

    USART0_init(PIN7_bm, PIN6_bm, 9600);

    TCA0_init();

    volatile uint16_t cnt;
    char cnt_str[10];

    while (1) {
        cnt = TCA0.SINGLE.CNT;
        sprintf(cnt_str, "%d\r\n", cnt);

        USART0_sendString(cnt_str);
        _delay_ms(500);
    }
}
