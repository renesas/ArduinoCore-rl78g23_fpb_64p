/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
  wiring_pulse.c - pulseIn() function


***********************************************************************************************************************/

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

