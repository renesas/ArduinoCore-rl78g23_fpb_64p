/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

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
  
  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
*/
/*
 * Mar 1st 2017 : Modified for RL78/G13 by Yuuki Okamiya.
 */

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "utilities.h"
#include "wiring_private.h"
#include "api/Common.h"
#include "r_smc_entry.h"
#include "platform.h"



/* 1108 Ueeda add */

typedef struct {
    void (*begin)();
    void (*mode)(uint8_t interruptNum, PinStatus mode);
    void (*start)();
    void (*stop)(uint8_t interruptNum);
} Interrupts_func;

Interrupts_func Int_func =
{
    .begin  = (void*)R_Config_INTC_Create,
    .mode = (void*)R_Config_INTC_Create_Mode,
    .start = (void*)R_Config_INTC_INTP_Start,
    .stop = (void*)R_Config_INTC_INTP_Stop
};

static bool IsFirst = true;

// void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode)

//void attachInterrupt(pin_size_t interruptNum, voidFuncPtr userFunc, int mode)

void attachInterrupt(pin_size_t interruptNum, voidFuncPtr userFunc, PinStatus p_mode)
{
	uint8_t mode = (uint8_t)p_mode;
	if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        g_afInterruptFuncTable[interruptNum] = userFunc;
        if(IsFirst){
            Int_func.begin();
            IsFirst = false;
        }
        Int_func.mode(interruptNum, mode);
        Int_func.start();
    }
}

void detachInterrupt(uint8_t interruptNum) {

    if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        Int_func.stop(interruptNum);
        g_afInterruptFuncTable[interruptNum] = NULL;
    }
}

// INTERRUPT HANDLERS *********************************************************/
// NMI and IRQ interrupt handlers. Note that all of these are declared in
// interrupts_handlers.h but defined here for clarity.

// ***************************************************************************/
INTERRUPT void external_interrupt_0(void)
{
    if (g_afInterruptFuncTable[0] != NULL) {
        (*g_afInterruptFuncTable[0])();
    }
}

INTERRUPT void external_interrupt_1(void)
{
    if (g_afInterruptFuncTable[1] != NULL) {
        (*g_afInterruptFuncTable[1])();
    }
}

INTERRUPT void external_interrupt_2(void)
{
    if (g_afInterruptFuncTable[2] != NULL) {
        (*g_afInterruptFuncTable[2])();
    }
}

