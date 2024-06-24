#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void setup() {
	DDRD = 0xF0;

	EICRA |= 0x0B; // INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03; // Enable INT1 & INT0
	
	sei(); // Enable global interrupt
}

int main(void)
{
	setup();

	while (1)
	{
		PORTD ^= (1<<7);
		_delay_ms(500);
	}
}

ISR( INT0_vect ) {
	PORTD |= (1<<5);
}

ISR( INT1_vect ) {
	PORTD &= ~(1<<5);
}