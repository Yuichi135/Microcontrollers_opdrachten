#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../../Week2/B5/B5/LCD_library.h"
#define BIT(x)(1<<(x))

int main( void ) {
	DDRD = 0xFF; // Zet port D en A op output
	DDRB = 0x00; // Zet port B op input
	DDRA = 0xFF;
	PORTA = 0;

	int i = 1; // om de counter bij te houden

	init();

	int prev = 0;

	while (1) {
		if (PINB & 1) { // Verhoog counter als de knop is ingedrukt
			i++;
		}
		char string[10];

		PORTA = i;
		_delay_ms(50);

		if (i == prev) // Om onnodige displays te voorkomen
		continue;

		sprintf(string, "%i", i); // Reformat int naar string
		display_text(string); // Display string
		prev = i;

	}
	return 0;

}