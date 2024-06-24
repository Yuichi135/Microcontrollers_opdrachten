#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../../Week2/B5/B5/LCD_library.h"
#define BIT(x)(1<<(x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}

// Initialize ADC:
void adcInit( void ) {
	ADMUX = 0b11100010;            // AREF=2,56 V, result left adjusted, channel1 at pin PF2
	ADCSRA = 0b10000110;        // ADC-enable, no interrupt, no free running, division by 64
}


// Main program: Counting on T1
int main( void ) {
	DDRF = 0x00;                    // set PORTF for input (ADC)
	DDRA = 0xFF;                    // set PORTA for output
	adcInit();                        // initialize ADC

	init();

	while (1) {
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & (1 << ADSC) ) ;        // Wait for completion
		PORTA = ADCH;                    // Show ADC

		char buffer[50];
		sprintf(buffer, "Het is graden", PORTA);
		display_text(buffer);

		wait(500);                        // every 500 ms (busy waiting)
	}
}