#define F_CPU 8000000UL  // Definieer de kloksnelheid van de microcontroller
#include <avr/io.h>       // AVR I/O-registers en -functies
#include <util/delay.h>   // Functies voor vertragingen
#include <avr/interrupt.h>// Interrupt-gerelateerde functies
#define BIT(x) (1 << (x)) // Macro om een bepaald bit in te stellen

#include <stdio.h> // Standaard input/output-bibliotheek

// Definieer de verschillende toestanden van de machine
typedef enum {
	START,
	S1,
	S2,
	S3,
	END
} State;

// Functieprototypes voor acties in elke toestand
void startAction(int input);
void s1Action(int input);
void s2Action(int input);
void s3Action(int input);
void endAction(int input);

State currentState = START; // Initialisatie van de huidige toestand als START

// Actie voor START-toestand
void startAction(int input) {
	// Als de input het 5e bit heeft ingesteld, ga naar S2
	if (input & BIT(5)) {
		currentState = S2;
	}
	// Als de input het 6e bit heeft ingesteld, ga naar S1
	else if (input & BIT(6)) {
		currentState = S1;
	}
}

// Actie voor S1-toestand
void s1Action(int input) {
	// Als de input het 7e bit heeft ingesteld, ga terug naar START
	if (input & BIT(7)) {
		currentState = START;
	}
	// Als de input het 5e bit heeft ingesteld, ga naar S2
	else if (input & BIT(5)) {
		currentState = S2;
	}
}

// Actie voor S2-toestand
void s2Action(int input) {
	// Als de input het 7e bit heeft ingesteld, ga terug naar START
	if (input & BIT(7)) {
		currentState = START;
	}
	// Als de input het 6e bit heeft ingesteld, ga naar S1
	else if (input & BIT(6)) {
		currentState = S1;
	}
	// Als de input het 5e bit heeft ingesteld, ga naar S3
	else if (input & BIT(5)) {
		currentState = S3;
	}
}

// Actie voor S3-toestand
void s3Action(int input) {
	// Als de input het 7e bit heeft ingesteld, ga terug naar START
	if (input & BIT(7)) {
		currentState = START;
	}
	// Als de input het 5e of 6e bit heeft ingesteld, ga naar END
	else if (input & BIT(5) || input & BIT(6)) {
		currentState = END;
	}
}

// Actie voor END-toestand
void endAction(int input) {
	// Als de input het 7e bit heeft ingesteld, ga terug naar START
	if (input & BIT(7)) {
		currentState = START;
	}
}

// Functie om de acties voor de huidige toestand uit te voeren op basis van de invoer
void doSwitch(int i) {
	PORTB = i; // Stel de output van poort B in op de invoerwaarde
	switch (currentState) {
		case START:
		startAction(i);
		break;
		case S1:
		s1Action(i);
		break;
		case S2:
		s2Action(i);
		break;
		case S3:
		s3Action(i);
		break;
		case END:
		endAction(i);
		break;
	}
}

int main() {
	// Stel de poorten A, B, D als uitgangen in en poort C als invoer
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRC = 0x00;

	int buttonPressed = 0; // Variabele om bij te houden of er een knop is ingedrukt
	while (1) {
		// Controleer of er een knop is ingedrukt en voer de bijbehorende actie uit
		if (PINC > 0 && !buttonPressed) {
			doSwitch(PINC);
			buttonPressed = 1; // Markeer dat er een knop is ingedrukt
		}
		// Reset de status van de knop als er geen knop meer wordt ingedrukt
		if (!(PINC > 0)) {
			buttonPressed = 0;
		}

		PORTA = currentState; // Gebruik poort A om de huidige toestand weer te geven op het bord
	}

	return 0;
}
