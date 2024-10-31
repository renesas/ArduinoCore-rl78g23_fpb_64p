#include "Arduino.h"
#include "pins_arduino.h"

extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    // cache the port and bit of the pin in order to speed up the
    // pulse width measuring loop and achieve finer resolution.  calling
    // digitalRead() instead yields much coarser resolution.
    const PinTableType **pp;
    PinTableType *p;
    pp = &pinTablelist[pin];
    p = (PinTableType *)*pp;
    unsigned long start;
    unsigned long startMicros = micros();
    if(state == HIGH)
    {
        // wait for any previous pulse to end
        while ((*p->portRegisterAddr & p->mask) != 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }

        // wait for the pulse to start
        while ((*p->portRegisterAddr & p->mask) == 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }

        start = micros();
        // wait for the pulse to stop
        while ((*p->portRegisterAddr & p->mask) > 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }
    }
    else
    {
        // wait for any previous pulse to end
        while ((*p->portRegisterAddr & p->mask) == 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }

        // wait for the pulse to start
        while ((*p->portRegisterAddr & p->mask) != 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }

        start = micros();
        // wait for the pulse to stop
        while ((*p->portRegisterAddr & p->mask) == 0)
        {
            if (micros() - startMicros > timeout)
                return 0;
        }
    }
    return micros() - start;
}

