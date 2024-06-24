#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
	DDRA = 0xff;

	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			PORTA = 1 << i;
			_delay_ms(50);
		}
	}

	return 0;
}