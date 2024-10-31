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
