/*
  wiring_pulse.c - pulseIn() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/
/*
 * Modified  5 Mar  2017 by Yuuki Okamiya for RL78/G13
 * Modified 18 Mar  2017 by Nozomu Fujita for pulseInWait, pulseInCount
*/

#include "wiring_variant.h"

extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

static uint32_t countPulse(volatile uint8_t *port, uint8_t bit, uint8_t stateMask, unsigned long maxloops) {
	unsigned long width = 0;
    // wait for any previous pulse to end
    while ((*port & bit) == stateMask) {
        if (--maxloops == 0)
            return 0;
    }

    // wait for the pulse to start
    while ((*port & bit) != stateMask) {
        if (--maxloops == 0)
            return 0;
    }

    // wait for the pulse to stop
    while ((*port & bit) == stateMask) {
        if (++width == maxloops)
            return 0;
    }
    return width;
}

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
uint32_t pulseIn(pin_size_t pin, uint8_t state, uint32_t timeout)
{
    const PinTableType **pp;
    PinTableType *p;
    pp = &pinTablelist[pin];
    p = (PinTableType *)*pp;
   // unsigned long start;
   // unsigned long startMicros = micros();
    // cache the port and bit of the pin in order to speed up the
    // pulse width measuring loop and achieve finer resolution.  calling
    // digitalRead() instead yields much coarser resolution.
    //uint16_t port = digitalPinToPort(pin);
    //uint16_t bit = digitalPinToBitMask(pin);
    uint8_t  bit = p->mask;
    uint8_t stateMask = state ? bit : 0;

    // convert the timeout from microseconds to a number of times through
    // the initial loop; it takes (roughly) 18 clock cycles per iteration.
    uint32_t maxloops = microsecondsToClockCycles(timeout) / PULSEIN_CLOCK_CYCLE;

    uint32_t width = countPulse((volatile uint8_t*)p->portRegisterAddr, bit, stateMask, maxloops);

    // convert the reading to microseconds. The loop has been determined
    // to be 18 clock cycles long and have about 16 clocks between the edge
    // and the start of the loop. There will be some error introduced by
    // the interrupt handlers.
    if (width)
        return clockCyclesToMicroseconds(width * PULSEIN_CLOCK_CYCLE + 0);
    else
        return 0;
}
