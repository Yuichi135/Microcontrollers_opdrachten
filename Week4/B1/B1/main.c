#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BIT(x)(1<<(x))

void setupADC()
{
	DDRF &= ~(1<<PF0); // PORTF.0 input ADC
	DDRA = 0xFF; // PORTA outputs for displaying ADC value (LSB)
	DDRB = 0xFF; // PORTB outputs for displaying ADC value (MSB)
	
	ADCSRA = 0;
	ADCSRA |= 0b10000000; // Schakel de ADC-module in
	ADCSRA |= 0b00100000; // Activeer freerun-modus
	ADCSRA |= 0b00000110; // Stel de prescaler-bits in op een prescaler van 64

	ADMUX = 0;
	ADMUX |= 0b01000000; // Selecteer voltage selection AVCC with external capacitor at AREF pin
	ADMUX |= 0b00100000; // Stel ADLAR (ADC left adjust result) in op 1
	ADMUX |= 0b00000001; // Selecteer kanaal 1 (ADC1)
}

int main(void)
{
	setupADC();
	while (1)
	{
		//// ADC Start Conversion
		ADCSRA |= (1<<ADSC);
		
		// Display
		PORTA = ADCL;
		PORTB = ADCH;
	}
}