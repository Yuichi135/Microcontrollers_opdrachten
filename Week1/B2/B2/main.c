#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	DDRA = 0XFF;
	while (1)
	{
		PORTD = 0b00000011;
		_delay_ms(50);
		PORTD = 0b00000000;
		_delay_ms(50);
	}
	return 0;
}

