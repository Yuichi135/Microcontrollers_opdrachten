#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
	DDRD = 0xFF; // of 0b11111111, zet alles op output
	// Set PORTA for input
	DDRC = 0x00; // of 0b00000000, zet alles op input
	while (1)
	{
		// Check of de drukknop is ingedrukt op PINC0
		if (PINC & 0x01) // Mask with 0b0000001, bit0
		{
			// Laat de LED op D0 knipperen
			PORTD = 0x01;
			_delay_ms(50);
			PORTD = 0;
			_delay_ms(50);
		}
		else // LED D0 uit
		{
			PORTD = 0x00;
		}
	}

	return 0;
}