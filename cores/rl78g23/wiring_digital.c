/*
  wiring_digital.c - digital input and output functions
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

  Modified 28 September 2010 by Mark Sproul

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/
/*
 * Modified  4 Mar  2017 by Yuuki Okamiya for RL78/G13
*/

#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_variant.h"
#include "wiring_private.h"
#include "api/Common.h"
#include "pintable.h"

#define PMPUPIMPOM_CHECK_ENABLE		/* Do not change invalid bits */

extern bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS];
extern volatile SwPwm g_SwPwm[NUM_SWPWM_PINS];
extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

/**********************************************************************************************************************
 * Function Name: pintable setting
 * Description  : Set the pintable.
 * Arguments    : pin  - pin number
 *              : pp   - pin table
 * Return Value : -
 *********************************************************************************************************************/

/**
 * PWM STOP~
 *
 * @param[in] u8Timer Timer Number of PWM
 *
 * @return Nothing
 *
 * @attention Nothing
 ***************************************************************************/
void _turnOffPwmPin(uint8_t u8Pin)
{
	unsigned int u16TMR0x;

	uint8_t u8Timer = 0xFF;
	if (u8Pin < NUM_DIGITAL_PINS) {
		g_u8AnalogWriteAvailableTable[u8Pin] = false;
	}
	if (u8Timer == SWPWM_PIN)
	{
		int i;

		for (i = 0; i < NUM_SWPWM_PINS; i++) {
			if (g_SwPwm[i].valid) {
				if (g_SwPwm[i].pin == u8Pin) {
					g_SwPwm[i].valid = false;
				} else {
					break;
				}
			}
		}
		if (i >= NUM_SWPWM_PINS) {			// SoftwarePWM�̐ݒ�Ȃ�
			_stopTimerChannel(SW_PWM_TIMER);
		}
	}
	else
	{
		switch (u8Timer) {
		case 1:
			u16TMR0x = TMR01;
			break;
		case 2:
			u16TMR0x = TMR02;
			break;
		case 3:
			u16TMR0x = TMR03;
			break;
		case 4:
			u16TMR0x = TMR04;
			break;
		case 5:
			u16TMR0x = TMR05;
			break;
		case 6:
			u16TMR0x = TMR06;
			break;
		case 7:
			u16TMR0x = TMR07;
			break;
		default:
			u16TMR0x = PWM_MASTER_MODE;
			break;
		}
		if (u16TMR0x == PWM_SLAVE_MODE) {
			_stopTimerChannel(u8Timer);
		}
	}
}

/**********************************************************************************************************************
 * Function Name: pinmode setting
 * Description  : Set the port register.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
// void pinMode(uint8_t pin, uint8_t u8Mode)
void pinMode(pin_size_t pin, PinMode u8Mode)
{
	if (pin < NUM_DIGITAL_PINS) {
		//PinTableType pin_tbl;
		//p = (PinTableType*)&pin_tbl;
		//getPinTable(pin,p);

        const PinTableType **pp;
		PinTableType *p;
        pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;

#ifdef PMPUPIMPOM_CHECK_ENABLE
		if (0 != p->pm){
#endif
			switch (u8Mode) {
				 case OUTPUT:
					*p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);
					break;
				 case INPUT:
					*p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);
					break;
				 default:
					 break;
			}
#ifdef PMPUPIMPOM_CHECK_ENABLE
		}
#endif

		/* clear pmca register when analog pin */
		if (0!=p->pmca)
		{
			*p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
		}

		/* clear pmct register when touch pin */
		if (0!=p->pmct)
		{
			*p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
		}

		/* clear pmce register when ELCL pin */
#if defined(G23_FPB)
		if (0!=p->pmce)
		{
			*p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
		}
#endif // G23_FPB
		/* clear ccde register */
#if defined(G23_FPB)
		if (0!=p->ccde)
		{
			*p->portOutCurControlRegisterAddr &= (unsigned long)~(p->ccde);
		}
#endif // G23_FPB

		if (g_u8AnalogWriteAvailableTable[pin]) {
			_turnOffPwmPin(pin);	/* PWM setting cancel */
		}
		if (!(*p->portModeRegisterAddr & p->mask)) {
			if (*p->portRegisterAddr & p->mask) {
				if (u8Mode == INPUT) {
					u8Mode = INPUT_PULLUP;
				} else if (u8Mode == INPUT_TTL) {
					u8Mode = INPUT_TTL_PULLUP;
				}
			}
		}

		switch (u8Mode) {
		case INPUT:
		case INPUT_PULLUP:
		case INPUT_TTL:
		case INPUT_TTL_PULLUP:
			if (0 != p->pu){
				if (u8Mode == INPUT_PULLUP || u8Mode == INPUT_TTL_PULLUP) {
					*p->portPullUpRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* Enable Pullup Reg */
				} else {
					*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* Disable Pullup Reg */
				}
			}
			if (0 != p->pim){
				if (u8Mode == INPUT_TTL || u8Mode == INPUT_TTL_PULLUP) {
					*p->portInputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set TTL Input */
				} else {
					*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Onput */
				}
			}
			if (0 != p->pm){
				*p->portModeRegisterAddr |= (unsigned long)(1U << p->bit); 			/* set Input Mode */
			}
			if (0 != p->pom){
				*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
			}
#if defined(G23_FPB)
			if (0 != p->pdidis){
				*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
			}
#endif // G23_FPB
			break;
		case OUTPUT:
		case OUTPUT_OPENDRAIN:
// 2023/03/02
//          if((pin==27) || (pin==28) || (pin==41))
			if(CHECK_OUTPUT_INHIBIT_RL78(pin))
            {
                break;
            }
			if (u8Mode == OUTPUT_OPENDRAIN) {
				if (0 != p->pom){
					*p->portOutputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch OpenDrain output */
				}
#if defined(G23_FPB)
				if (0 != p->pdidis){
					*p->portDigInputDisRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch Input disable */
				}
#endif // G23_FPB
			} else {
				if (0 != p->pom){
					*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
				}
#if defined(G23_FPB)
				if (0 != p->pdidis){
					*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
				}
#endif // G23_FPB
			}
			if (0 != p->pm){
				*p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* set Output Mode */
			}
			if (0 != p->pu){
				*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* Disable Pullup Reg */
			}
			if (0 != p->pim){
				*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Input */
			}
			*p->portRegisterAddr &= (unsigned long)~(0x1 << p->bit);			/* clear Port */
			break;
		default:
			break;
		}
	}
}

/**********************************************************************************************************************
 * Function Name: pin output
 * Description  : Perform port output
 * Arguments    : pin  - pin number
 *              : pp   - output value
 * Return Value : -
 *********************************************************************************************************************/
// void digitalWrite(uint8_t pin, uint8_t val)
void digitalWrite(pin_size_t pin, PinStatus val)
{
    const PinTableType ** pp;
    PinTableType * p;
	if (pin < NUM_DIGITAL_PINS) {
	    pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;
        {
            /* When Output Mode  */
            if (val == LOW) {
                *p->portRegisterAddr &= ~p->mask;       /* Write "0" to Port */
            } else {
                *p->portRegisterAddr |= p->mask;        /* Write "1" to Port */
            }
        }
    }
}

/**********************************************************************************************************************
 * Function Name: pin input
 * Description  : Perform port input
 * Arguments    : pin  - pin number
 * Return Value : input value
 *********************************************************************************************************************/
// int digitalRead(uint8_t pin)
PinStatus digitalRead(pin_size_t pin){
	if (pin < NUM_DIGITAL_PINS) {
		//PinTableType* p;
		//PinTableType pin_tbl;
		//p =(PinTableType*)&pin_tbl;
		//getPinTable(pin,p);

		const PinTableType ** pp;
		PinTableType * p;
		pp = &pinTablelist[pin];
		p = (PinTableType *)*pp;
		if (*p->portRegisterAddr & p->mask) {

			return HIGH;
		}
	}
	return LOW;

}

#ifdef __RL78__
/**********************************************************************************************************************
 * Function Name: disable input pin
 * Description  : Prohibits the input of the specified pin.
 * Arguments    : pin   - pin number
 * Return Value : -
 *********************************************************************************************************************/
void DisableDigitalInput(uint8_t pin)
{

	if (pin < NUM_DIGITAL_PINS) {
		//PinTableType *p;
		//PinTableType pin_tbl;
		//p = (PinTableType*)&pin_tbl;
        //getPinTable(pin,p);

		const PinTableType ** pp;
		PinTableType * p;
		pp = &pinTablelist[pin];
		p = (PinTableType *)*pp;
#if defined(G23_FPB)
		if (0 != p->pdidis){	/* can be changed */
			*p->portDigInputDisRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* Input disable */
		}
#endif // G23_FPB
	}
}

/**********************************************************************************************************************
 * Function Name: enable input pin
 * Description  : Allows the input of the specified pin.
 * Arguments    : pin   - pin number
 * Return Value : -
 *********************************************************************************************************************/
void EnableDigitalInput(uint8_t pin)
{

	if (pin < NUM_DIGITAL_PINS) {
		//PinTableType *p;
		//PinTableType pin_tbl;
		//p = (PinTableType*)&pin_tbl;
        //getPinTable(pin,p);

		const PinTableType ** pp;
		PinTableType * p;
		pp = &pinTablelist[pin];
		p = (PinTableType *)*pp;
#if defined(G23_FPB)
		if (0 != p->pdidis){	/* can be changed */
			*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
		}
#endif // G23_FPB
	}
}
#endif /*__RL78__*/

