/*
 * Copyright 2009 Pete Morici
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define MMC_IS_PRESENT()	(!(PIND & _BV(PIND1)))
#define LED_ON()		(PORTD |= _BV(PD4))
#define LED_OFF()		(PORTD &= ~_BV(PD4))

int main(int argc, char **argv) {

	/* disable the watch dog timer */
	MCUSR &= ~_BV(WDRF);
	wdt_disable();

	/* setup card presence input */
	DDRD &= ~_BV(DDD1);
	PORTD &= ~_BV(PD1);

	/* setup interrupt */
	EICRA |= _BV(ISC10);
	EICRA &= ~_BV(ISC11);
	EIMSK |= _BV(INT1);

	/* setup LED in correct state */
	DDRD |= _BV(DDD4);
	if (MMC_IS_PRESENT()) { LED_ON(); }
	else { LED_OFF(); }

	sei();	/* enable interrupts */
	while(1) { sleep_mode(); }

	return 0;
}

/* Interrupt routine */
ISR(INT1_vect) {
	if (MMC_IS_PRESENT()) { LED_ON(); }
	else { LED_OFF(); }
	return;
}
