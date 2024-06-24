#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x00;

	int state = 0;
	int buttonPressed = 0;

	while (1)
	{
		if (PINC & 0x01 && !buttonPressed) {
			state = (state + 1) % 2;
			buttonPressed = 1;
		}
		if (!(PINC & 0x01))
		{
			buttonPressed = 0;
		}

		if (state)
		_delay_ms(100);
		else
		_delay_ms(500);

		PORTD = PORTD ^ 0x01;
	}

	return 0;
}
