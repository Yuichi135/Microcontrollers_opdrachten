#include <avr/io.h>
#include "LCD_library.h"


int main(void)
{
	DDRD = 0xFF;
	
	init();
	
	display_text("ball");
	
	_delay_ms(1000);
	
	int i = 0;
	char str[10];
	
	while (1) {
		i++;
		PORTD ^= (1 << 7);
		
		sprintf(str, "%i", i);
		display_text(str);
		
		_delay_ms(1000);
	}
	
	return 1;
}

