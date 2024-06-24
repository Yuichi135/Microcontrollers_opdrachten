#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BIT(x)(1<<(x))


uint8_t hihi[] = {
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111,
	0b01110111,
	0b01111100,
	0b00111001,
	0b01011110,
	0b01111011,
	0b01110001,
	0x79
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

void display( int digit ){
	int i = hihi[digit];

	if (digit > 15 || digit < 0)
	i = hihi[16];

	PORTD = i;
}

int main( void ) {
	DDRD = 0xFF;
	DDRC = 0x00;
	DDRA = 0xFF;

	PORTA = 0;

	int i = 1;

	while (1)
	{
		if ((PINC & 0x03) == 0x03)
		{
			i = 0;
		}
		else if (PINC & 1)
		{
			i++;
		} else if (PINC & BIT(1))
		{
			i--;
		}

		display(i);
		wait(100);
	}
}