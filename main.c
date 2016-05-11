/*-
 * Copyright (c) 2016, Michael Zhilin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);

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
