#include <avr/io.h>

int main(void) {
	/*
	 * D0 - RX from PC
	 * D1 - TX to PC
	 * D2 - Power for router
	 * D3 - RX from router
	 * D4 - TX to router
	 */
	DDRD 	= 0b11110110;
	DDRB 	= 0b11111111;
	PORTB 	= 0b00000000;
	PORTD 	= 0b00000100; // power for router

	/* Disable UART RX and TX */
	UCSR0B &= ~_BV(RXEN0) && ~_BV(TXEN0);

	while (1) {
		switch (PIND & 0b00001001) {
		case 0b1001:
			PORTD |= 0b00010010;
			break;
		case 0b1000:
			PORTD |= 0b00000010;
			PORTD &= 0b11101111;
			break;
		case 0b0001:
			PORTD |= 0b00010000;
			PORTD &= 0b11111101;
			break;
		default:
			PORTD &= 0b11101101;
			break;
		}
	}

	return 1;
}
