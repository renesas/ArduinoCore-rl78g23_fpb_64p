/*
  wiring_private.h - Internal header file.
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

#ifndef WiringPrivate_h
#define WiringPrivate_h

#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"
#include "utilities.h"
#include "wiring_variant.h"

#ifdef __cplusplus
extern "C"{
#endif
fInterruptFunc_t g_afInterruptFuncTable[EXTERNAL_NUM_INTERRUPTS] __attribute__((weak));

#define CYCLE_VALUE	(0)
#define TAU_OPERATION_CLOCK		(0xC000U)    /* operation clock set by PRS register */
#define CK00_CK01_OPERATION		(0x000F)	/* Selection of operation clock CK00, CK01 */
#define CK02_OPERATION			(0x0300)	/* Selection of operation clock CK02 */
#define CK03_OPERATION			(0x3000)	/* Selection of operation clock CK03 */
#define TIMEOUT_MAX_VAL			(65535)
#define PULSE_INTERUPT			(1)

#define MICROSEC_OVFL_FLAG   (TMIF01)
#define MICROSEC_TIMER_CNT      (TCR01)
typedef struct {
    uint8_t valid:1;
    uint8_t pin:7;
    uint8_t value;
    volatile uint8_t* port;
    uint8_t mask;
    uint8_t newValue;
} SwPwm;

typedef struct {
    void (*open)();
    void (*open_slave)();
    void (*start)();
    void (*start_slave)();
    void (*stop_slave)();
    void (*enable_interrupt)();
    uint16_t cycle;

} Pwm_func;

int8_t get_pwm_channel(uint8_t pwm_num);
int8_t get_analog_channel(uint8_t analog_num);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* WiringPrivate_h */

