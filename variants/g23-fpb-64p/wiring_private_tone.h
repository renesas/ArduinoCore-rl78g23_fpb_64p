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

#ifndef WiringPrivateTone_h
#define WiringPrivateTone_h

#ifdef __cplusplus
extern "C"{
#endif

#define FREQUENCY_MIN_VAL	(500)
#define FREQUENCY_MAX_VAL	(8000000)

#define TONE_CH_NUM				(7)

#define TAU_OPERATION_CLOCK		(0xC000U)    /* operation clock set by PRS register */
#define CK00_CK01_OPERATION		(0x000F)	/* Selection of operation clock CK00, CK01 */
#define CK02_OPERATION			(0x0300)	/* Selection of operation clock CK02 */
#define CK03_OPERATION			(0x3000)	/* Selection of operation clock CK03 */
#define TIMEOUT_MAX_VAL			(65535)
#define PULSE_INTERUPT			(1)

#define _4000_TAU_CLOCK_SELECT_CKM2       (0x4000U)    /* operation clock CK2 set by PRS register */
#define _0000_TAU_CKM2_FCLK_1             (0x0000U)    /* ckm2 - fCLK/2^1 */
#define _C000_TAU_CLOCK_SELECT_CKM3       (0xC000U)    /* operation clock CK3 set by PRS register */

typedef struct {
    void (*open)();
	void (*start)();
	void (*stop)();
} tone_func;



#ifdef __cplusplus
} // extern "C"
#endif


/* tone pin set */
extern volatile unsigned short *g_tone_period_reg[TONE_CH_NUM];
extern volatile unsigned short *g_timer_tone_mode_reg[TONE_CH_NUM];
extern volatile unsigned short *g_timer_tone_clock_select_reg;
extern const uint8_t  tone_channel_table[TONE_CH_NUM];

//#include "Config_TAU0_1_Square_Wave.h"
extern "C"{
void R_Config_TAU0_1_Square_Wave_Create(void);
void R_Config_TAU0_1_Square_Wave_Start(void);
void R_Config_TAU0_1_Square_Wave_Stop(void);
void R_Config_TAU0_1_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_2_Square_Wave_Create(void);
void R_Config_TAU0_2_Square_Wave_Start(void);
void R_Config_TAU0_2_Square_Wave_Stop(void);
void R_Config_TAU0_2_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_3_Square_Wave_Create(void);
void R_Config_TAU0_3_Square_Wave_Start(void);
void R_Config_TAU0_3_Square_Wave_Stop(void);
void R_Config_TAU0_3_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_4_Square_Wave_Create(void);
void R_Config_TAU0_4_Square_Wave_Start(void);
void R_Config_TAU0_4_Square_Wave_Stop(void);
void R_Config_TAU0_4_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_5_Square_Wave_Create(void);
void R_Config_TAU0_5_Square_Wave_Start(void);
void R_Config_TAU0_5_Square_Wave_Stop(void);
void R_Config_TAU0_5_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_6_Square_Wave_Create(void);
void R_Config_TAU0_6_Square_Wave_Start(void);
void R_Config_TAU0_6_Square_Wave_Stop(void);
void R_Config_TAU0_6_Square_Wave_Create_UserInit(void);
void R_Config_TAU0_7_Square_Wave_Create(void);
void R_Config_TAU0_7_Square_Wave_Start(void);
void R_Config_TAU0_7_Square_Wave_Stop(void);
void R_Config_TAU0_7_Square_Wave_Create_UserInit(void);
}

extern tone_func tone_ch[TONE_CH_NUM];

#endif
