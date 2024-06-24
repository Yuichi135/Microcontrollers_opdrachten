#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
	DDRA = 0xFF; // Zet alle pins op output op port A, B, C & D
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	int lookupTable[6] = {0b00000000, 0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b00000000};
	// Array waar elk element een 'frame' is in onze animatie

	while (1)
	{
		for (int i = 0; i < 6; i++) // Loop door de lookup table
		{
			PORTA = lookupTable[i]; // Toon de data binnen de lookuptable dmv de LED
			PORTB = lookupTable[(i + 1) % 6]; // Doe hetzelfde, maar dan met de volgende frame
			PORTC = lookupTable[(i + 2) % 6]; // Ditto
			PORTD = lookupTable[(i + 3) % 6]; // Ditto
			_delay_ms(200);
		}
	}

	return 0;
}