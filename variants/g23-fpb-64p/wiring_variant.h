/*
  wiring_variant.h - Internal header file.
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

  $Id: wiring.h 239 2007-01-12 17:58:39Z mellis $
*/
/*
  Modified 13 July 2014 by Nozomu Fujita for GR-SAKURA
  Modified 1  Mar  2017 by Yuuki Okamiya for RL78/G13
*/

#ifndef WiringVariante_h
#define WiringVariante_h

#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"
#include "utilities.h"

#ifdef __cplusplus
extern "C"{
#endif

#define ANALOG_ADPC_OFFSET	4
#define ANALOG_PIN_START_NUMBER	(38)
#define MAX_CYCLIC_HANDLER 		(8)
#define EXTERNAL_NUM_INTERRUPTS (7)

/* PWM defines. */
#define PWM_MIN			0
#define PWM_MAX			255

/* External interrupt define. */

#define EXTERNAL_INTERRUPT_0	4
#define EXTERNAL_INTERRUPT_1	6
#define EXTERNAL_INTERRUPT_2	7
#define EXTERNAL_INTERRUPT_3    11
#define EXTERNAL_INTERRUPT_4    12
#define EXTERNAL_INTERRUPT_5    13
#define EXTERNAL_INTERRUPT_6    26

#define	PWM_CH_NUM	(6)

#define FREQUENCY_MIN_VAL	(500)
#define FREQUENCY_MAX_VAL	(8000000)

/* pulseIn define. */
#define PULSEIN_CLOCK_CYCLE 41


#ifdef __cplusplus
} // extern "C"
#endif

// extern uint32_t R_BSP_GetFclkFreqHz(void);

#endif /* WiringVariante_h */

