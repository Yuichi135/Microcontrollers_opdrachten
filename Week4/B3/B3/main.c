#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BIT(x)(1<<(x))

void adcInit( void ) {
	ADMUX = 0b11100010;            // AREF=2,56 V, result left adjusted, channel1 at pin PF2
	ADCSRA = 0b10000110;        // ADC-enable, no interrupt, no free running, division by 64
}

int main( void ) {
	DDRF = 0x00;                    // set PORTF for input (ADC)
	DDRA = 0xFF;                    // set PORTA for output
	adcInit();                        // initialize ADC

	init();

	while (1) {
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & (1 << ADSC) ) ;        // Wait for completion
		PORTA = ADCH;                    // Show ADC

		wait(500);                        // every 500 ms (busy waiting)
	}
}

