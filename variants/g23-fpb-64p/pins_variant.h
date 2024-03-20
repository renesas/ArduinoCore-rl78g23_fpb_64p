/*
  Copyright (c) 2014-2016 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _PINS_VARIANT_H_
#define _PINS_VARIANT_H_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(32000000)	//!< CPUの動作周波数（RTOS未使用時に定義）
#endif

#define F_CPU (32 * 1000 * 1000L)

// G22, G23 :2 , G16:1, G24:3
#define MICROS_TIMER_DIVIDE_FACTOR ((uint32_t)2)

#define UART_CHANNEL 		0		// UART0(Serial0)
#define UART1_CHANNEL       1       // UART1(Serial1)
#define UART2_CHANNEL       2       // UART2(Serial2)

/* SPI(CSI) Definition */
#define USE_CSI      (1) // Set to '1' when Use SPI Hardware.

#if defined(USE_CSI) && USE_CSI

// #define CSI_CHANNEL0 (0) // USE CSI00 for SPI
// #define CSI_CHANNEL1 (1) // USE CSI01 for SPI
// #define CSI_CHANNEL2 (2) // USE CSI10 for SPI
#define CSI_CHANNEL3 (3) // USE CSI11 for SPI
// #define CSI_CHANNEL4 (4) // USE CSI20 for SPI
// #define CSI_CHANNEL5 (5) // USE CSI21 for SPI
// #define CSI_CHANNEL6 (6) // USE CSI30 for SPI
// #define CSI_CHANNEL7 (7) // USE CSI31 for SPI

#endif /* defined(USE_CSI) && USE_CSI */

/* IIC Definition */
#define IIC_CHANNEL0 (0)
#define IIC_CHANNEL1 (1)

#define CHECK_PINMODE_INHIBIT_RL78(p) (\
    (p) == 41 || /* P21(AVREFM) */\
    (p) == 14    /* P20(AVREFP) */)
#define CHECK_OUTPUT_INHIBIT_RL78(p) ((p) == 14 || (p) == 27 || (p) == 28 || (p) == 41)


#ifdef __cplusplus
extern "C"
{

// moved from wiring_private.h
#define FREQUENCY_MIN_VAL	(500)
#define FREQUENCY_MAX_VAL	(8000000)

#define TONE_CH_NUM				(7)

// #define TAU_OPERATION_CLOCK		(0xC000U)    /* operation clock set by PRS register */
// #define CK00_CK01_OPERATION		(0x000F)	/* Selection of operation clock CK00, CK01 */
// #define CK02_OPERATION			(0x0300)	/* Selection of operation clock CK02 */
// #define CK03_OPERATION			(0x3000)	/* Selection of operation clock CK03 */
// #define TIMEOUT_MAX_VAL			(65535)
// #define PULSE_INTERUPT			(1)

#define _4000_TAU_CLOCK_SELECT_CKM2       (0x4000U)    /* operation clock CK2 set by PRS register */
#define _0000_TAU_CKM2_FCLK_1             (0x0000U)    /* ckm2 - fCLK/2^1 */
#define _C000_TAU_CLOCK_SELECT_CKM3       (0xC000U)    /* operation clock CK3 set by PRS register */

}
#endif // __cplusplus

// tone_func

int8_t get_tone_channel(uint8_t tone_num);

typedef struct {
    void (*open)();
	void (*start)();
	void (*stop)();
	void (*get_width)(uint32_t * const width);
} pulse_in_func;
/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define NUM_DIGITAL_PINS            57
#define NUM_ANALOG_INPUTS           10
#define NUM_SWPWM_PINS              4
// #endif
#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)

#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)


#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

extern const uint8_t SS;
extern const uint8_t MOSI;
extern const uint8_t MISO;
extern const uint8_t SCK;

extern const uint8_t SS3;
extern const uint8_t MOSI3;
extern const uint8_t MISO3;
extern const uint8_t SCK3;

extern const uint8_t SS4;
extern const uint8_t MOSI4;
extern const uint8_t MISO4;
extern const uint8_t SCK4;

extern const uint8_t SS5;
extern const uint8_t MOSI5;
extern const uint8_t MISO5;
extern const uint8_t SCK5;
#define PIN_WIRE_SDA0        (48) // P61
#define PIN_WIRE_SCL0        (47) // P60
#define PIN_WIRE_SDA1        (50) // P63
#define PIN_WIRE_SCL1        (49) // P62

#define PIN_WIRE_SDA0_MASK   0x02 // P61
#define PIN_WIRE_SCL0_MASK   0x01 // P60
#define PIN_WIRE_SDA1_MASK   0x08 // P63
#define PIN_WIRE_SCL1_MASK   0x04 // P62
extern const uint8_t SDA0;
extern const uint8_t SCL0;
extern const uint8_t SDA1;
extern const uint8_t SCL1;
#define BUILTIN_LED1 16
#define BUILTIN_LED2 15
#define LED_BUILTIN  BUILTIN_LED1

#define LED_ON  LOW
#define LED_OFF HIGH

#define PIN_A0   (51)	/*A0 = ANI2 */
#define PIN_A1   (52)	/*A1 = ANI3 */
#define PIN_A2   (53)	/*A2 = ANI4 */
#define PIN_A3   (54)	/*A3 = ANI5 */
#define PIN_A4   (55)	/*A4 = ANI6 */
#define PIN_A5   (56)	/*A5 = ANI7 */
#define PIN_A6	(0)		/* ANI16(P03/RxD1) */
#define PIN_A7	(1)		/* ANI17(P02/TxD1) */
#define PIN_A8	(29)	/* ANI19(P120) (DIGITAL_PIN_29) */
#define PIN_A9	(40)	/* ANI18(P147) (DIGITAL_PIN_40) */
extern const uint8_t A0;
extern const uint8_t A1;
extern const uint8_t A2;
extern const uint8_t A3;
extern const uint8_t A4;
extern const uint8_t A5;
extern const uint8_t A6;
extern const uint8_t A7;
extern const uint8_t A8;
extern const uint8_t A9;

#define digitalPinToInterrupt(p)  (((p) == 4) ? 0 : (((p) == 6) ? 1 : (((p) == 7) ? 2 : (((p) == 11) ? 3 : (((p) == 12) ? 4 : (((p) == 13) ? 5 : (((p) == 26) ? 6 : NOT_AN_INTERRUPT)))))))

#ifdef __RL78__
/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/
#define ADDR_PORT_REG			0xFFFFFF00
#define ADDR_PORT_MODE_REG		0xFFFFFF20
#define ADDR_PORT_PULL_UP_REG	0xFFFF0030
#define	ADDR_PORT_IN_MODE_REG	0xFFFF0040
#define ADDR_PORT_OUT_MODE_REG	0xFFFF0050

/* Add for G23 */
#define ADDR_PORT_MODE_CONTROL_A_REG	0xFFFF0060
#define ADDR_PORT_MODE_CONTROL_T_REG	0xFFFF0260
#define ADDR_PORT_MODE_CONTROL_E_REG	0xFFFF0280
#define ADDR_PORT_OUT_CUR_CONTROL_REG	0xFFFF02A8
#define ADDR_PORT_DIG_INPUT_DIS_REG		0xFFFF02B0
/* Add for G23 */

#define ANALOG_PIN_0		2		// ANI2 (DIGITAL_PIN_51)
#define ANALOG_PIN_1		3		// ANI3 (DIGITAL_PIN_52)
#define ANALOG_PIN_2		4		// ANI4 (DIGITAL_PIN_53)
#define ANALOG_PIN_3		5		// ANI5 (DIGITAL_PIN_54)
#define ANALOG_PIN_4		6		// ANI6 (DIGITAL_PIN_55)
#define ANALOG_PIN_5		7		// ANI7 (DIGITAL_PIN_56)
/* add 2021.07.29 */
#define ANALOG_PIN_6		16		// ANI16(P03/RxD1) (DIGITAL_PIN_0)
#define ANALOG_PIN_7		17		// ANI17(P02/TxD1) (DIGITAL_PIN_1)
#define ANALOG_PIN_8		19		// ANI19(P120) (DIGITAL_PIN_29)
#define ANALOG_PIN_9		18		// ANI18(P147) (DIGITAL_PIN_40)

/* Port define. */
#define PORT_0				0
#define PORT_1				1
#define PORT_2				2
#define PORT_3				3
#define PORT_4				4
#define PORT_5				5
#define PORT_6				6
#define PORT_7				7
#define PORT_8				8
#define PORT_9				9
#define PORT_10				10
#define PORT_11				11
#define PORT_12				12
#define PORT_13				13
#define PORT_14				14
#define PORT_15				15

/* Port of digital pin define. */
#define DIGITAL_PIN_0		PORT_0	/* P03	*/
#define DIGITAL_PIN_1		PORT_0	/* P02	*/
#define DIGITAL_PIN_2		PORT_4	/* P43	*/
#define DIGITAL_PIN_3		PORT_4	/* P42	*/
#define DIGITAL_PIN_4		PORT_7	/* P77	*/
#define DIGITAL_PIN_5		PORT_4	/* P41	*/
#define DIGITAL_PIN_6		PORT_3	/* P31	*/
#define DIGITAL_PIN_7		PORT_7	/* P76	*/
#define DIGITAL_PIN_8		PORT_7	/* P73	*/
#define DIGITAL_PIN_9		PORT_0	/* P06	*/
#define DIGITAL_PIN_10		PORT_0	/* P05	*/
#define DIGITAL_PIN_11		PORT_5	/* P51	*/
#define DIGITAL_PIN_12		PORT_5	/* P50	*/
#define DIGITAL_PIN_13		PORT_3	/* P30	*/
#define DIGITAL_PIN_14		PORT_2	/* P40(REF)	*/ // P20->P40
#define DIGITAL_PIN_15		PORT_5	/* P52	*/
#define DIGITAL_PIN_16		PORT_5	/* P53	*/
#define DIGITAL_PIN_17		PORT_5	/* P54	*/
#define DIGITAL_PIN_18		PORT_5	/* P55	*/
#define DIGITAL_PIN_19		PORT_7	/* P70	*/
#define DIGITAL_PIN_20		PORT_7	/* P71	*/
#define DIGITAL_PIN_21		PORT_7	/* P72	*/
#define DIGITAL_PIN_22		PORT_7	/* P74	*/
#define DIGITAL_PIN_23		PORT_7	/* P75	*/
#define DIGITAL_PIN_24		PORT_12	/* P121	*/
#define DIGITAL_PIN_25		PORT_12	/* P122	*/
#define DIGITAL_PIN_26		PORT_13	/* P137	*/
#define DIGITAL_PIN_27		PORT_12	/* P123	*/
#define DIGITAL_PIN_28		PORT_12	/* P124	*/
#define DIGITAL_PIN_29		PORT_12	/* P120	*/
#define DIGITAL_PIN_30		PORT_0	/* P04 	*/

#define DIGITAL_PIN_31		PORT_1	/* P17	*/
#define DIGITAL_PIN_32		PORT_1	/* P16	*/
#define DIGITAL_PIN_33		PORT_1	/* P15	*/
#define DIGITAL_PIN_34		PORT_1	/* P14	*/
#define DIGITAL_PIN_35		PORT_1	/* P13	*/
#define DIGITAL_PIN_36		PORT_1	/* P12	*/
#define DIGITAL_PIN_37		PORT_1	/* P11	*/
#define DIGITAL_PIN_38		PORT_1	/* P10	*/
#define DIGITAL_PIN_39		PORT_14	/* P146	*/
#define DIGITAL_PIN_40		PORT_14	/* P147	*/
#define DIGITAL_PIN_41		PORT_2	/* P21 	*/
#define DIGITAL_PIN_42		PORT_13	/* P130	*/
#define DIGITAL_PIN_43		PORT_0	/* P01 	*/
#define DIGITAL_PIN_44		PORT_0	/* P00 	*/
#define DIGITAL_PIN_45		PORT_14	/* P141	*/
#define DIGITAL_PIN_46		PORT_14	/* P140	*/

/* For SDAA0,SCLA0 */
#define DIGITAL_PIN_47		PORT_6	/* P60	*/
#define DIGITAL_PIN_48		PORT_6	/* P61	*/
/* For SDAA1,SCLA1 */
#define DIGITAL_PIN_49		PORT_6	/* P62	*/
#define DIGITAL_PIN_50		PORT_6	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_51		PORT_2	/* P22	*/
#define DIGITAL_PIN_52		PORT_2	/* P23	*/
#define DIGITAL_PIN_53		PORT_2	/* P24	*/
#define DIGITAL_PIN_54		PORT_2	/* P25	*/
#define DIGITAL_PIN_55		PORT_2	/* P26	*/
#define DIGITAL_PIN_56		PORT_2	/* P27	*/
/* For A0-A6 */


/* Bit Num of digital pin define */
#define DIGITAL_PIN_BIT_0	0x03	/* P03	*/
#define DIGITAL_PIN_BIT_1	0x02	/* P02	*/
#define DIGITAL_PIN_BIT_2	0x03	/* P43	*/
#define DIGITAL_PIN_BIT_3	0x02	/* P42	*/
#define DIGITAL_PIN_BIT_4	0x07	/* P77	*/
#define DIGITAL_PIN_BIT_5	0x01	/* P41	*/
#define DIGITAL_PIN_BIT_6	0x01	/* P31	*/
#define DIGITAL_PIN_BIT_7	0x06	/* P76	*/
#define DIGITAL_PIN_BIT_8	0x03	/* P73	*/
#define DIGITAL_PIN_BIT_9	0x06	/* P06	*/
#define DIGITAL_PIN_BIT_10	0x05	/* P05	*/
#define DIGITAL_PIN_BIT_11	0x01	/* P51	*/
#define DIGITAL_PIN_BIT_12	0x00	/* P50	*/
#define DIGITAL_PIN_BIT_13	0x00	/* P30	*/
#define DIGITAL_PIN_BIT_14	0x00	/* P40(REF)	*/ // P20->P40
#define DIGITAL_PIN_BIT_15	0x02	/* P52	*/
#define DIGITAL_PIN_BIT_16	0x03	/* P53	*/
#define DIGITAL_PIN_BIT_17	0x04	/* P54	*/
#define DIGITAL_PIN_BIT_18	0x05	/* P55	*/
#define DIGITAL_PIN_BIT_19	0x00	/* P70	*/
#define DIGITAL_PIN_BIT_20	0x01	/* P71	*/
#define DIGITAL_PIN_BIT_21	0x02	/* P72	*/
#define DIGITAL_PIN_BIT_22	0x04	/* P74	*/
#define DIGITAL_PIN_BIT_23	0x05	/* P75	*/
#define DIGITAL_PIN_BIT_24	0x01	/* P121	*/
#define DIGITAL_PIN_BIT_25	0x02	/* P122	*/
#define DIGITAL_PIN_BIT_26	0x07	/* P137	*/
#define DIGITAL_PIN_BIT_27	0x03	/* P123	*/
#define DIGITAL_PIN_BIT_28	0x04	/* P124	*/
#define DIGITAL_PIN_BIT_29	0x00	/* P120	*/
#define DIGITAL_PIN_BIT_30	0x04	/* P04 	*/

#define DIGITAL_PIN_BIT_31	0x07	/* P17	*/
#define DIGITAL_PIN_BIT_32	0x06	/* P16	*/
#define DIGITAL_PIN_BIT_33	0x05	/* P15	*/
#define DIGITAL_PIN_BIT_34	0x04	/* P14	*/
#define DIGITAL_PIN_BIT_35	0x03	/* P13	*/
#define DIGITAL_PIN_BIT_36	0x02	/* P12	*/
#define DIGITAL_PIN_BIT_37	0x01	/* P11	*/
#define DIGITAL_PIN_BIT_38	0x00	/* P10	*/
#define DIGITAL_PIN_BIT_39	0x06	/* P146	*/
#define DIGITAL_PIN_BIT_40	0x07	/* P147	*/
#define DIGITAL_PIN_BIT_41	0x01	/* P21 	*/
#define DIGITAL_PIN_BIT_42	0x00	/* P130	*/
#define DIGITAL_PIN_BIT_43	0x01	/* P01 	*/
#define DIGITAL_PIN_BIT_44	0x00	/* P00 	*/
#define DIGITAL_PIN_BIT_45	0x01	/* P141	*/
#define DIGITAL_PIN_BIT_46	0x00	/* P140	*/
                                
/* For SDAA0,SCLA0 */           
#define DIGITAL_PIN_BIT_47	0x00	/* P60	*/
#define DIGITAL_PIN_BIT_48	0x01	/* P61	*/
/* For SDAA1,SCLA1 */           
#define DIGITAL_PIN_BIT_49	0x02	/* P62	*/
#define DIGITAL_PIN_BIT_50	0x03	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_BIT_51	0x02	/* P22	*/
#define DIGITAL_PIN_BIT_52	0x03	/* P23	*/
#define DIGITAL_PIN_BIT_53	0x04	/* P24	*/
#define DIGITAL_PIN_BIT_54	0x05	/* P25	*/
#define DIGITAL_PIN_BIT_55	0x06	/* P26	*/
#define DIGITAL_PIN_BIT_56	0x07	/* P27	*/
/* For A0-A6 */

/* Bit mask of digital pin define. */
#define DIGITAL_PIN_MASK_0		0x08	/* P03	*/
#define DIGITAL_PIN_MASK_1		0x04	/* P02	*/
#define DIGITAL_PIN_MASK_2		0x08	/* P43	*/
#define DIGITAL_PIN_MASK_3		0x04	/* P42	*/
#define DIGITAL_PIN_MASK_4		0x80	/* P77	*/
#define DIGITAL_PIN_MASK_5		0x02	/* P41	*/
#define DIGITAL_PIN_MASK_6		0x02	/* P31	*/
#define DIGITAL_PIN_MASK_7		0x40	/* P76	*/
#define DIGITAL_PIN_MASK_8		0x08	/* P73	*/
#define DIGITAL_PIN_MASK_9		0x40	/* P06	*/
#define DIGITAL_PIN_MASK_10		0x20	/* P05	*/
#define DIGITAL_PIN_MASK_11		0x02	/* P51	*/
#define DIGITAL_PIN_MASK_12		0x01	/* P50	*/
#define DIGITAL_PIN_MASK_13		0x01	/* P30	*/
#define DIGITAL_PIN_MASK_14		0x01	/* P40(REF)	*/  // P20->P40
#define DIGITAL_PIN_MASK_15		0x04	/* P52	*/
#define DIGITAL_PIN_MASK_16		0x08	/* P53	*/
#define DIGITAL_PIN_MASK_17		0x10	/* P54	*/
#define DIGITAL_PIN_MASK_18		0x20	/* P55	*/
#define DIGITAL_PIN_MASK_19		0x01	/* P70	*/
#define DIGITAL_PIN_MASK_20		0x02	/* P71	*/
#define DIGITAL_PIN_MASK_21		0x04	/* P72	*/
#define DIGITAL_PIN_MASK_22		0x10	/* P74	*/
#define DIGITAL_PIN_MASK_23		0x20	/* P75	*/
#define DIGITAL_PIN_MASK_24		0x02	/* P121	*/
#define DIGITAL_PIN_MASK_25		0x04	/* P122	*/
#define DIGITAL_PIN_MASK_26		0x80	/* P137	*/
#define DIGITAL_PIN_MASK_27		0x08	/* P123	*/
#define DIGITAL_PIN_MASK_28		0x10	/* P124	*/
#define DIGITAL_PIN_MASK_29		0x01	/* P120	*/
#define DIGITAL_PIN_MASK_30		0x10	/* P04 	*/
                                        
#define DIGITAL_PIN_MASK_31		0x80	/* P17	*/
#define DIGITAL_PIN_MASK_32		0x40	/* P16	*/
#define DIGITAL_PIN_MASK_33		0x20	/* P15	*/
#define DIGITAL_PIN_MASK_34		0x10	/* P14	*/
#define DIGITAL_PIN_MASK_35		0x08 	/* P13	*/
#define DIGITAL_PIN_MASK_36		0x04	/* P12	*/
#define DIGITAL_PIN_MASK_37		0x02	/* P11	*/
#define DIGITAL_PIN_MASK_38		0x01	/* P10	*/
#define DIGITAL_PIN_MASK_39		0x40	/* P146	*/
#define DIGITAL_PIN_MASK_40		0x80	/* P147	*/
#define DIGITAL_PIN_MASK_41		0x02	/* P21 	*/
#define DIGITAL_PIN_MASK_42		0x01	/* P130	*/
#define DIGITAL_PIN_MASK_43		0x02	/* P01 	*/
#define DIGITAL_PIN_MASK_44		0x01	/* P00 	*/
#define DIGITAL_PIN_MASK_45		0x02	/* P141	*/
#define DIGITAL_PIN_MASK_46		0x01	/* P140	*/
                                        
/* For SDAA0,SCLA0 */                   
#define DIGITAL_PIN_MASK_47		0x01	/* P60	*/
#define DIGITAL_PIN_MASK_48		0x02	/* P61	*/
/* For SDAA1,SCLA1 */                   
#define DIGITAL_PIN_MASK_49		0x04	/* P62	*/
#define DIGITAL_PIN_MASK_50		0x08	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_MASK_51		0x04	/* P22	*/
#define DIGITAL_PIN_MASK_52		0x08	/* P23	*/
#define DIGITAL_PIN_MASK_53		0x10	/* P24	*/
#define DIGITAL_PIN_MASK_54		0x20	/* P25	*/
#define DIGITAL_PIN_MASK_55		0x40	/* P26	*/
#define DIGITAL_PIN_MASK_56		0x80	/* P27	*/
/* For A0-A6 */

/* Add for G23 PMCA & PMCT & PMCE */
#define DIGITAL_PIN_PMCA_0		0x08	/* P03	*/
#define DIGITAL_PIN_PMCA_1		0x04	/* P02	*/
#define DIGITAL_PIN_PMCA_2		0x00	/* P43	*/
#define DIGITAL_PIN_PMCA_3		0x00	/* P42	*/
#define DIGITAL_PIN_PMCA_4		0x00	/* P77	*/
#define DIGITAL_PIN_PMCA_5		0x00	/* P41	*/
#define DIGITAL_PIN_PMCA_6		0x00	/* P31	*/
#define DIGITAL_PIN_PMCA_7		0x00	/* P76	*/
#define DIGITAL_PIN_PMCA_8		0x00	/* P73	*/
#define DIGITAL_PIN_PMCA_9		0x00	/* P06	*/
#define DIGITAL_PIN_PMCA_10		0x00	/* P05	*/
#define DIGITAL_PIN_PMCA_11		0x00	/* P51	*/
#define DIGITAL_PIN_PMCA_12		0x00	/* P50	*/
#define DIGITAL_PIN_PMCA_13		0x00	/* P30	*/
#define DIGITAL_PIN_PMCA_14		0x01	/* P20(REF)	*/
#define DIGITAL_PIN_PMCA_15		0x00	/* P52	*/
#define DIGITAL_PIN_PMCA_16		0x00	/* P53	*/
#define DIGITAL_PIN_PMCA_17		0x00	/* P54	*/
#define DIGITAL_PIN_PMCA_18		0x00	/* P55	*/
#define DIGITAL_PIN_PMCA_19		0x00	/* P70	*/
#define DIGITAL_PIN_PMCA_20		0x00	/* P71	*/
#define DIGITAL_PIN_PMCA_21		0x00	/* P72	*/
#define DIGITAL_PIN_PMCA_22		0x00	/* P74	*/
#define DIGITAL_PIN_PMCA_23		0x00	/* P75	*/
#define DIGITAL_PIN_PMCA_24		0x00	/* P121	*/
#define DIGITAL_PIN_PMCA_25		0x00	/* P122	*/
#define DIGITAL_PIN_PMCA_26		0x00	/* P137	*/
#define DIGITAL_PIN_PMCA_27		0x00	/* P123	*/
#define DIGITAL_PIN_PMCA_28		0x00	/* P124	*/
#define DIGITAL_PIN_PMCA_29		0x01	/* P120	*/
#define DIGITAL_PIN_PMCA_30		0x00	/* P04 	*/
#define DIGITAL_PIN_PMCA_31		0x00	/* P17	*/
#define DIGITAL_PIN_PMCA_32		0x00	/* P16	*/
#define DIGITAL_PIN_PMCA_33		0x00	/* P15	*/
#define DIGITAL_PIN_PMCA_34		0x00	/* P14	*/
#define DIGITAL_PIN_PMCA_35		0x08 	/* P13	*/
#define DIGITAL_PIN_PMCA_36		0x00	/* P12	*/
#define DIGITAL_PIN_PMCA_37		0x00	/* P11	*/
#define DIGITAL_PIN_PMCA_38		0x00	/* P10	*/
#define DIGITAL_PIN_PMCA_39		0x00	/* P146	*/
#define DIGITAL_PIN_PMCA_40		0x80	/* P147	*/
#define DIGITAL_PIN_PMCA_41		0x02	/* P21 	*/
#define DIGITAL_PIN_PMCA_42		0x00	/* P130	*/
#define DIGITAL_PIN_PMCA_43		0x00	/* P01 	*/
#define DIGITAL_PIN_PMCA_44		0x00	/* P00 	*/
#define DIGITAL_PIN_PMCA_45		0x00	/* P141	*/
#define DIGITAL_PIN_PMCA_46		0x00	/* P140	*/
#define DIGITAL_PIN_PMCA_47		0x00	/* P60	*/
#define DIGITAL_PIN_PMCA_48		0x00	/* P61	*/
#define DIGITAL_PIN_PMCA_49		0x00	/* P62	*/
#define DIGITAL_PIN_PMCA_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PMCA_51		0x04	/* P22	*/
#define DIGITAL_PIN_PMCA_52		0x08	/* P23	*/
#define DIGITAL_PIN_PMCA_53		0x10	/* P24	*/
#define DIGITAL_PIN_PMCA_54		0x20	/* P25	*/
#define DIGITAL_PIN_PMCA_55		0x40	/* P26	*/
#define DIGITAL_PIN_PMCA_56		0x80	/* P27	*/
/* For A0-A6 */

#define DIGITAL_PIN_PMCT_0		0x00	/* P03	*/
#define DIGITAL_PIN_PMCT_1		0x00	/* P02	*/
#define DIGITAL_PIN_PMCT_2		0x00	/* P43	*/
#define DIGITAL_PIN_PMCT_3		0x00	/* P42	*/
#define DIGITAL_PIN_PMCT_4		0x80	/* P77	*/
#define DIGITAL_PIN_PMCT_5		0x00	/* P41	*/
#define DIGITAL_PIN_PMCT_6		0x02	/* P31	*/
#define DIGITAL_PIN_PMCT_7		0x40	/* P76	*/
#define DIGITAL_PIN_PMCT_8		0x08	/* P73	*/
#define DIGITAL_PIN_PMCT_9		0x40	/* P06	*/
#define DIGITAL_PIN_PMCT_10		0x20	/* P05	*/
#define DIGITAL_PIN_PMCT_11		0x00	/* P51	*/
#define DIGITAL_PIN_PMCT_12		0x01	/* P50	*/
#define DIGITAL_PIN_PMCT_13		0x01	/* P30	*/
#define DIGITAL_PIN_PMCT_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_PMCT_15		0x00	/* P52	*/
#define DIGITAL_PIN_PMCT_16		0x00	/* P53	*/
#define DIGITAL_PIN_PMCT_17		0x00	/* P54	*/
#define DIGITAL_PIN_PMCT_18		0x00	/* P55	*/
#define DIGITAL_PIN_PMCT_19		0x01	/* P70	*/
#define DIGITAL_PIN_PMCT_20		0x02	/* P71	*/
#define DIGITAL_PIN_PMCT_21		0x04	/* P72	*/
#define DIGITAL_PIN_PMCT_22		0x10	/* P74	*/
#define DIGITAL_PIN_PMCT_23		0x20	/* P75	*/
#define DIGITAL_PIN_PMCT_24		0x00	/* P121	*/
#define DIGITAL_PIN_PMCT_25		0x00	/* P122	*/
#define DIGITAL_PIN_PMCT_26		0x00	/* P137	*/
#define DIGITAL_PIN_PMCT_27		0x00	/* P123	*/
#define DIGITAL_PIN_PMCT_28		0x00	/* P124	*/
#define DIGITAL_PIN_PMCT_29		0x00	/* P120	*/
#define DIGITAL_PIN_PMCT_30		0x00	/* P04 	*/
#define DIGITAL_PIN_PMCT_31		0x00	/* P17	*/
#define DIGITAL_PIN_PMCT_32		0x00	/* P16	*/
#define DIGITAL_PIN_PMCT_33		0x00	/* P15	*/
#define DIGITAL_PIN_PMCT_34		0x00	/* P14	*/
#define DIGITAL_PIN_PMCT_35		0x00 	/* P13	*/
#define DIGITAL_PIN_PMCT_36		0x00	/* P12	*/
#define DIGITAL_PIN_PMCT_37		0x00	/* P11	*/
#define DIGITAL_PIN_PMCT_38		0x00	/* P10	*/
#define DIGITAL_PIN_PMCT_39		0x00	/* P146	*/
#define DIGITAL_PIN_PMCT_40		0x00	/* P147	*/
#define DIGITAL_PIN_PMCT_41		0x00	/* P21 	*/
#define DIGITAL_PIN_PMCT_42		0x00	/* P130	*/
#define DIGITAL_PIN_PMCT_43		0x00	/* P01 	*/
#define DIGITAL_PIN_PMCT_44		0x00	/* P00 	*/
#define DIGITAL_PIN_PMCT_45		0x00	/* P141	*/
#define DIGITAL_PIN_PMCT_46		0x00	/* P140	*/
#define DIGITAL_PIN_PMCT_47		0x00	/* P60	*/
#define DIGITAL_PIN_PMCT_48		0x00	/* P61	*/
#define DIGITAL_PIN_PMCT_49		0x00	/* P62	*/
#define DIGITAL_PIN_PMCT_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PMCT_51		0x04	/* P22	*/
#define DIGITAL_PIN_PMCT_52		0x08	/* P23	*/
#define DIGITAL_PIN_PMCT_53		0x10	/* P24	*/
#define DIGITAL_PIN_PMCT_54		0x20	/* P25	*/
#define DIGITAL_PIN_PMCT_55		0x40	/* P26	*/
#define DIGITAL_PIN_PMCT_56		0x80	/* P27	*/
/* For A0-A6 */

#define DIGITAL_PIN_PMCE_0		0x00	/* P03	*/
#define DIGITAL_PIN_PMCE_1		0x00	/* P02	*/
#define DIGITAL_PIN_PMCE_2		0x00	/* P43	*/
#define DIGITAL_PIN_PMCE_3		0x00	/* P42	*/
#define DIGITAL_PIN_PMCE_4		0x00	/* P77	*/
#define DIGITAL_PIN_PMCE_5		0x00	/* P41	*/
#define DIGITAL_PIN_PMCE_6		0x00	/* P31	*/
#define DIGITAL_PIN_PMCE_7		0x00	/* P76	*/
#define DIGITAL_PIN_PMCE_8		0x00	/* P73	*/
#define DIGITAL_PIN_PMCE_9		0x00	/* P06	*/
#define DIGITAL_PIN_PMCE_10		0x00	/* P05	*/
#define DIGITAL_PIN_PMCE_11		0x02	/* P51	*/
#define DIGITAL_PIN_PMCE_12		0x01	/* P50	*/
#define DIGITAL_PIN_PMCE_13		0x00	/* P30	*/
#define DIGITAL_PIN_PMCE_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_PMCE_15		0x00	/* P52	*/
#define DIGITAL_PIN_PMCE_16		0x00	/* P53	*/
#define DIGITAL_PIN_PMCE_17		0x00	/* P54	*/
#define DIGITAL_PIN_PMCE_18		0x00	/* P55	*/
#define DIGITAL_PIN_PMCE_19		0x00	/* P70	*/
#define DIGITAL_PIN_PMCE_20		0x00	/* P71	*/
#define DIGITAL_PIN_PMCE_21		0x00	/* P72	*/
#define DIGITAL_PIN_PMCE_22		0x00	/* P74	*/
#define DIGITAL_PIN_PMCE_23		0x00	/* P75	*/
#define DIGITAL_PIN_PMCE_24		0x00	/* P121	*/
#define DIGITAL_PIN_PMCE_25		0x00	/* P122	*/
#define DIGITAL_PIN_PMCE_26		0x00	/* P137	*/
#define DIGITAL_PIN_PMCE_27		0x00	/* P123	*/
#define DIGITAL_PIN_PMCE_28		0x00	/* P124	*/
#define DIGITAL_PIN_PMCE_29		0x00	/* P120	*/
#define DIGITAL_PIN_PMCE_30		0x00	/* P04 	*/
#define DIGITAL_PIN_PMCE_31		0x80	/* P17	*/
#define DIGITAL_PIN_PMCE_32		0x40	/* P16	*/
#define DIGITAL_PIN_PMCE_33		0x20	/* P15	*/
#define DIGITAL_PIN_PMCE_34		0x10	/* P14	*/
#define DIGITAL_PIN_PMCE_35		0x08 	/* P13	*/
#define DIGITAL_PIN_PMCE_36		0x04	/* P12	*/
#define DIGITAL_PIN_PMCE_37		0x02	/* P11	*/
#define DIGITAL_PIN_PMCE_38		0x01	/* P10	*/
#define DIGITAL_PIN_PMCE_39		0x00	/* P146	*/
#define DIGITAL_PIN_PMCE_40		0x00	/* P147	*/
#define DIGITAL_PIN_PMCE_41		0x00	/* P21 	*/
#define DIGITAL_PIN_PMCE_42		0x00	/* P130	*/
#define DIGITAL_PIN_PMCE_43		0x02	/* P01 	*/
#define DIGITAL_PIN_PMCE_44		0x00	/* P00 	*/
#define DIGITAL_PIN_PMCE_45		0x00	/* P141	*/
#define DIGITAL_PIN_PMCE_46		0x00	/* P140	*/
#define DIGITAL_PIN_PMCE_47		0x01	/* P60	*/
#define DIGITAL_PIN_PMCE_48		0x02	/* P61	*/
#define DIGITAL_PIN_PMCE_49		0x00	/* P62	*/
#define DIGITAL_PIN_PMCE_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PMCE_51		0x00	/* P22	*/
#define DIGITAL_PIN_PMCE_52		0x00	/* P23	*/
#define DIGITAL_PIN_PMCE_53		0x00	/* P24	*/
#define DIGITAL_PIN_PMCE_54		0x00	/* P25	*/
#define DIGITAL_PIN_PMCE_55		0x00	/* P26	*/
#define DIGITAL_PIN_PMCE_56		0x00	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin CCDE */
#define DIGITAL_PIN_CCDE_0		0x00	/* P03	*/
#define DIGITAL_PIN_CCDE_1		0x00	/* P02	*/
#define DIGITAL_PIN_CCDE_2		0x00	/* P43	*/
#define DIGITAL_PIN_CCDE_3		0x00	/* P42	*/
#define DIGITAL_PIN_CCDE_4		0x00	/* P77	*/
#define DIGITAL_PIN_CCDE_5		0x00	/* P41	*/
#define DIGITAL_PIN_CCDE_6		0x00	/* P31	*/
#define DIGITAL_PIN_CCDE_7		0x00	/* P76	*/
#define DIGITAL_PIN_CCDE_8		0x00	/* P73	*/
#define DIGITAL_PIN_CCDE_9		0x00	/* P06	*/
#define DIGITAL_PIN_CCDE_10		0x00	/* P05	*/
#define DIGITAL_PIN_CCDE_11		0x04	/* P51	*/
#define DIGITAL_PIN_CCDE_12		0x08	/* P50	*/
#define DIGITAL_PIN_CCDE_13		0x00	/* P30	*/
#define DIGITAL_PIN_CCDE_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_CCDE_15		0x00	/* P52	*/
#define DIGITAL_PIN_CCDE_16		0x00	/* P53	*/
#define DIGITAL_PIN_CCDE_17		0x00	/* P54	*/
#define DIGITAL_PIN_CCDE_18		0x00	/* P55	*/
#define DIGITAL_PIN_CCDE_19		0x00	/* P70	*/
#define DIGITAL_PIN_CCDE_20		0x00	/* P71	*/
#define DIGITAL_PIN_CCDE_21		0x00	/* P72	*/
#define DIGITAL_PIN_CCDE_22		0x00	/* P74	*/
#define DIGITAL_PIN_CCDE_23		0x00	/* P75	*/
#define DIGITAL_PIN_CCDE_24		0x00	/* P121	*/
#define DIGITAL_PIN_CCDE_25		0x00	/* P122	*/
#define DIGITAL_PIN_CCDE_26		0x00	/* P137	*/
#define DIGITAL_PIN_CCDE_27		0x00	/* P123	*/
#define DIGITAL_PIN_CCDE_28		0x00	/* P124	*/
#define DIGITAL_PIN_CCDE_29		0x00	/* P120	*/
#define DIGITAL_PIN_CCDE_30		0x00	/* P04 	*/
#define DIGITAL_PIN_CCDE_31		0x02	/* P17	*/
#define DIGITAL_PIN_CCDE_32		0x01	/* P16	*/
#define DIGITAL_PIN_CCDE_33		0x00	/* P15	*/
#define DIGITAL_PIN_CCDE_34		0x00	/* P14	*/
#define DIGITAL_PIN_CCDE_35		0x00 	/* P13	*/
#define DIGITAL_PIN_CCDE_36		0x00	/* P12	*/
#define DIGITAL_PIN_CCDE_37		0x00	/* P11	*/
#define DIGITAL_PIN_CCDE_38		0x00	/* P10	*/
#define DIGITAL_PIN_CCDE_39		0x00	/* P146	*/
#define DIGITAL_PIN_CCDE_40		0x00	/* P147	*/
#define DIGITAL_PIN_CCDE_41		0x00	/* P21 	*/
#define DIGITAL_PIN_CCDE_42		0x00	/* P130	*/
#define DIGITAL_PIN_CCDE_43		0x00	/* P01 	*/
#define DIGITAL_PIN_CCDE_44		0x00	/* P00 	*/
#define DIGITAL_PIN_CCDE_45		0x00	/* P141	*/
#define DIGITAL_PIN_CCDE_46		0x00	/* P140	*/
#define DIGITAL_PIN_CCDE_47		0x10	/* P60	*/
#define DIGITAL_PIN_CCDE_48		0x20	/* P61	*/
#define DIGITAL_PIN_CCDE_49		0x40	/* P62	*/
#define DIGITAL_PIN_CCDE_50		0x80	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_CCDE_51		0x00	/* P22	*/
#define DIGITAL_PIN_CCDE_52		0x00	/* P23	*/
#define DIGITAL_PIN_CCDE_53		0x00	/* P24	*/
#define DIGITAL_PIN_CCDE_54		0x00	/* P25	*/
#define DIGITAL_PIN_CCDE_55		0x00	/* P26	*/
#define DIGITAL_PIN_CCDE_56		0x00	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin PDIDIS */
#define DIGITAL_PIN_PDIDIS_0	0x08	/* P03	*/
#define DIGITAL_PIN_PDIDIS_1	0x04	/* P02	*/
#define DIGITAL_PIN_PDIDIS_2	0x00	/* P43	*/
#define DIGITAL_PIN_PDIDIS_3	0x04	/* P42	*/
#define DIGITAL_PIN_PDIDIS_4	0x00	/* P77	*/
#define DIGITAL_PIN_PDIDIS_5	0x00	/* P41	*/
#define DIGITAL_PIN_PDIDIS_6	0x00	/* P31	*/
#define DIGITAL_PIN_PDIDIS_7	0x00	/* P76	*/
#define DIGITAL_PIN_PDIDIS_8	0x00	/* P73	*/
#define DIGITAL_PIN_PDIDIS_9	0x00	/* P06	*/
#define DIGITAL_PIN_PDIDIS_10	0x00	/* P05	*/
#define DIGITAL_PIN_PDIDIS_11	0x00	/* P51	*/
#define DIGITAL_PIN_PDIDIS_12	0x01	/* P50	*/
#define DIGITAL_PIN_PDIDIS_13	0x00	/* P30	*/
#define DIGITAL_PIN_PDIDIS_14	0x00	/* P20(REF)	*/
#define DIGITAL_PIN_PDIDIS_15	0x00	/* P52	*/
#define DIGITAL_PIN_PDIDIS_16	0x00	/* P53	*/
#define DIGITAL_PIN_PDIDIS_17	0x00	/* P54	*/
#define DIGITAL_PIN_PDIDIS_18	0x20	/* P55	*/
#define DIGITAL_PIN_PDIDIS_19	0x00	/* P70	*/
#define DIGITAL_PIN_PDIDIS_20	0x02	/* P71	*/
#define DIGITAL_PIN_PDIDIS_21	0x04	/* P72	*/
#define DIGITAL_PIN_PDIDIS_22	0x10	/* P74	*/
#define DIGITAL_PIN_PDIDIS_23	0x00	/* P75	*/
#define DIGITAL_PIN_PDIDIS_24	0x00	/* P121	*/
#define DIGITAL_PIN_PDIDIS_25	0x00	/* P122	*/
#define DIGITAL_PIN_PDIDIS_26	0x80	/* P137	*/
#define DIGITAL_PIN_PDIDIS_27	0x00	/* P123	*/
#define DIGITAL_PIN_PDIDIS_28	0x00	/* P124	*/
#define DIGITAL_PIN_PDIDIS_29	0x01	/* P120	*/
#define DIGITAL_PIN_PDIDIS_30	0x10	/* P04 	*/
#define DIGITAL_PIN_PDIDIS_31	0x80	/* P17	*/
#define DIGITAL_PIN_PDIDIS_32	0x00	/* P16	*/
#define DIGITAL_PIN_PDIDIS_33	0x20	/* P15	*/
#define DIGITAL_PIN_PDIDIS_34	0x10	/* P14	*/
#define DIGITAL_PIN_PDIDIS_35	0x08 	/* P13	*/
#define DIGITAL_PIN_PDIDIS_36	0x04	/* P12	*/
#define DIGITAL_PIN_PDIDIS_37	0x02	/* P11	*/
#define DIGITAL_PIN_PDIDIS_38	0x01	/* P10	*/
#define DIGITAL_PIN_PDIDIS_39	0x00	/* P146	*/
#define DIGITAL_PIN_PDIDIS_40	0x00	/* P147	*/
#define DIGITAL_PIN_PDIDIS_41	0x00	/* P21 	*/
#define DIGITAL_PIN_PDIDIS_42	0x00	/* P130	*/
#define DIGITAL_PIN_PDIDIS_43	0x00	/* P01 	*/
#define DIGITAL_PIN_PDIDIS_44	0x01	/* P00 	*/
#define DIGITAL_PIN_PDIDIS_45	0x00	/* P141	*/
#define DIGITAL_PIN_PDIDIS_46	0x00	/* P140	*/
#define DIGITAL_PIN_PDIDIS_47	0x00	/* P60	*/
#define DIGITAL_PIN_PDIDIS_48	0x00	/* P61	*/
#define DIGITAL_PIN_PDIDIS_49	0x00	/* P62	*/
#define DIGITAL_PIN_PDIDIS_50	0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PDIDIS_51	0x00	/* P22	*/
#define DIGITAL_PIN_PDIDIS_52	0x00	/* P23	*/
#define DIGITAL_PIN_PDIDIS_53	0x00	/* P24	*/
#define DIGITAL_PIN_PDIDIS_54	0x00	/* P25	*/
#define DIGITAL_PIN_PDIDIS_55	0x00	/* P26	*/
#define DIGITAL_PIN_PDIDIS_56	0x00	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin PM */
#define DIGITAL_PIN_PM_0		0x08	/* P03	*/
#define DIGITAL_PIN_PM_1		0x04	/* P02	*/
#define DIGITAL_PIN_PM_2		0x08	/* P43	*/
#define DIGITAL_PIN_PM_3		0x04	/* P42	*/
#define DIGITAL_PIN_PM_4		0x80	/* P77	*/
#define DIGITAL_PIN_PM_5		0x02	/* P41	*/
#define DIGITAL_PIN_PM_6		0x02	/* P31	*/
#define DIGITAL_PIN_PM_7		0x40	/* P76	*/
#define DIGITAL_PIN_PM_8		0x08	/* P73	*/
#define DIGITAL_PIN_PM_9		0x40	/* P06	*/
#define DIGITAL_PIN_PM_10		0x20	/* P05	*/
#define DIGITAL_PIN_PM_11		0x02	/* P51	*/
#define DIGITAL_PIN_PM_12		0x01	/* P50	*/
#define DIGITAL_PIN_PM_13		0x01	/* P30	*/
#define DIGITAL_PIN_PM_14		0x01	/* P20(REF)	*/
#define DIGITAL_PIN_PM_15		0x04	/* P52	*/
#define DIGITAL_PIN_PM_16		0x08	/* P53	*/
#define DIGITAL_PIN_PM_17		0x10	/* P54	*/
#define DIGITAL_PIN_PM_18		0x20	/* P55	*/
#define DIGITAL_PIN_PM_19		0x01	/* P70	*/
#define DIGITAL_PIN_PM_20		0x02	/* P71	*/
#define DIGITAL_PIN_PM_21		0x04	/* P72	*/
#define DIGITAL_PIN_PM_22		0x10	/* P74	*/
#define DIGITAL_PIN_PM_23		0x20	/* P75	*/
#define DIGITAL_PIN_PM_24		0x02	/* P121	*/
#define DIGITAL_PIN_PM_25		0x04	/* P122	*/
#define DIGITAL_PIN_PM_26		0x00	/* P137	*/
#define DIGITAL_PIN_PM_27		0x00	/* P123	*/
#define DIGITAL_PIN_PM_28		0x00	/* P124	*/
#define DIGITAL_PIN_PM_29		0x01	/* P120	*/
#define DIGITAL_PIN_PM_30		0x10	/* P04 	*/
#define DIGITAL_PIN_PM_31		0x80	/* P17	*/
#define DIGITAL_PIN_PM_32		0x40	/* P16	*/
#define DIGITAL_PIN_PM_33		0x20	/* P15	*/
#define DIGITAL_PIN_PM_34		0x10	/* P14	*/
#define DIGITAL_PIN_PM_35		0x08 	/* P13	*/
#define DIGITAL_PIN_PM_36		0x04	/* P12	*/
#define DIGITAL_PIN_PM_37		0x02	/* P11	*/
#define DIGITAL_PIN_PM_38		0x01	/* P10	*/
#define DIGITAL_PIN_PM_39		0x40	/* P146	*/
#define DIGITAL_PIN_PM_40		0x80	/* P147	*/
#define DIGITAL_PIN_PM_41		0x02	/* P21 	*/
#define DIGITAL_PIN_PM_42		0x00	/* P130	*/
#define DIGITAL_PIN_PM_43		0x02	/* P01 	*/
#define DIGITAL_PIN_PM_44		0x01	/* P00 	*/
#define DIGITAL_PIN_PM_45		0x02	/* P141	*/
#define DIGITAL_PIN_PM_46		0x01	/* P140	*/
#define DIGITAL_PIN_PM_47		0x01	/* P60	*/
#define DIGITAL_PIN_PM_48		0x02	/* P61	*/
#define DIGITAL_PIN_PM_49		0x04	/* P62	*/
#define DIGITAL_PIN_PM_50		0x08	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PM_51		0x04	/* P22	*/
#define DIGITAL_PIN_PM_52		0x08	/* P23	*/
#define DIGITAL_PIN_PM_53		0x10	/* P24	*/
#define DIGITAL_PIN_PM_54		0x20	/* P25	*/
#define DIGITAL_PIN_PM_55		0x40	/* P26	*/
#define DIGITAL_PIN_PM_56		0x80	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin PU */
#define DIGITAL_PIN_PU_0		0x08	/* P03	*/
#define DIGITAL_PIN_PU_1		0x04	/* P02	*/
#define DIGITAL_PIN_PU_2		0x08	/* P43	*/
#define DIGITAL_PIN_PU_3		0x04	/* P42	*/
#define DIGITAL_PIN_PU_4		0x80	/* P77	*/
#define DIGITAL_PIN_PU_5		0x02	/* P41	*/
#define DIGITAL_PIN_PU_6		0x02	/* P31	*/
#define DIGITAL_PIN_PU_7		0x40	/* P76	*/
#define DIGITAL_PIN_PU_8		0x08	/* P73	*/
#define DIGITAL_PIN_PU_9		0x40	/* P06	*/
#define DIGITAL_PIN_PU_10		0x20	/* P05	*/
#define DIGITAL_PIN_PU_11		0x02	/* P51	*/
#define DIGITAL_PIN_PU_12		0x01	/* P50	*/
#define DIGITAL_PIN_PU_13		0x01	/* P30	*/
#define DIGITAL_PIN_PU_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_PU_15		0x04	/* P52	*/
#define DIGITAL_PIN_PU_16		0x08	/* P53	*/
#define DIGITAL_PIN_PU_17		0x10	/* P54	*/
#define DIGITAL_PIN_PU_18		0x20	/* P55	*/
#define DIGITAL_PIN_PU_19		0x01	/* P70	*/
#define DIGITAL_PIN_PU_20		0x02	/* P71	*/
#define DIGITAL_PIN_PU_21		0x04	/* P72	*/
#define DIGITAL_PIN_PU_22		0x10	/* P74	*/
#define DIGITAL_PIN_PU_23		0x20	/* P75	*/
#define DIGITAL_PIN_PU_24		0x02	/* P121	*/
#define DIGITAL_PIN_PU_25		0x04	/* P122	*/
#define DIGITAL_PIN_PU_26		0x00	/* P137	*/
#define DIGITAL_PIN_PU_27		0x00	/* P123	*/
#define DIGITAL_PIN_PU_28		0x00	/* P124	*/
#define DIGITAL_PIN_PU_29		0x01	/* P120	*/
#define DIGITAL_PIN_PU_30		0x10	/* P04 	*/
#define DIGITAL_PIN_PU_31		0x80	/* P17	*/
#define DIGITAL_PIN_PU_32		0x40	/* P16	*/
#define DIGITAL_PIN_PU_33		0x20	/* P15	*/
#define DIGITAL_PIN_PU_34		0x10	/* P14	*/
#define DIGITAL_PIN_PU_35		0x08 	/* P13	*/
#define DIGITAL_PIN_PU_36		0x04	/* P12	*/
#define DIGITAL_PIN_PU_37		0x02	/* P11	*/
#define DIGITAL_PIN_PU_38		0x01	/* P10	*/
#define DIGITAL_PIN_PU_39		0x40	/* P146	*/
#define DIGITAL_PIN_PU_40		0x80	/* P147	*/
#define DIGITAL_PIN_PU_41		0x00	/* P21 	*/
#define DIGITAL_PIN_PU_42		0x00	/* P130	*/
#define DIGITAL_PIN_PU_43		0x02	/* P01 	*/
#define DIGITAL_PIN_PU_44		0x01	/* P00 	*/
#define DIGITAL_PIN_PU_45		0x02	/* P141	*/
#define DIGITAL_PIN_PU_46		0x01	/* P140	*/
#define DIGITAL_PIN_PU_47		0x00	/* P60	*/
#define DIGITAL_PIN_PU_48		0x00	/* P61	*/
#define DIGITAL_PIN_PU_49		0x00	/* P62	*/
#define DIGITAL_PIN_PU_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PU_51		0x00	/* P22	*/
#define DIGITAL_PIN_PU_52		0x00	/* P23	*/
#define DIGITAL_PIN_PU_53		0x00	/* P24	*/
#define DIGITAL_PIN_PU_54		0x00	/* P25	*/
#define DIGITAL_PIN_PU_55		0x00	/* P26	*/
#define DIGITAL_PIN_PU_56		0x00	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin PIM */
#define DIGITAL_PIN_PIM_0		0x08	/* P03	*/
#define DIGITAL_PIN_PIM_1		0x00	/* P02	*/
#define DIGITAL_PIN_PIM_2		0x00	/* P43	*/
#define DIGITAL_PIN_PIM_3		0x00	/* P42	*/
#define DIGITAL_PIN_PIM_4		0x00	/* P77	*/
#define DIGITAL_PIN_PIM_5		0x02	/* P41	*/
#define DIGITAL_PIN_PIM_6		0x00	/* P31	*/
#define DIGITAL_PIN_PIM_7		0x00	/* P76	*/
#define DIGITAL_PIN_PIM_8		0x00	/* P73	*/
#define DIGITAL_PIN_PIM_9		0x00	/* P06	*/
#define DIGITAL_PIN_PIM_10		0x00	/* P05	*/
#define DIGITAL_PIN_PIM_11		0x00	/* P51	*/
#define DIGITAL_PIN_PIM_12		0x00	/* P50	*/
#define DIGITAL_PIN_PIM_13		0x00	/* P30	*/
#define DIGITAL_PIN_PIM_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_PIM_15		0x00	/* P52	*/
#define DIGITAL_PIN_PIM_16		0x00	/* P53	*/
#define DIGITAL_PIN_PIM_17		0x00	/* P54	*/
#define DIGITAL_PIN_PIM_18		0x20	/* P55	*/
#define DIGITAL_PIN_PIM_19		0x00	/* P70	*/
#define DIGITAL_PIN_PIM_20		0x02	/* P71	*/
#define DIGITAL_PIN_PIM_21		0x00	/* P72	*/
#define DIGITAL_PIN_PIM_22		0x00	/* P74	*/
#define DIGITAL_PIN_PIM_23		0x00	/* P75	*/
#define DIGITAL_PIN_PIM_24		0x00	/* P121	*/
#define DIGITAL_PIN_PIM_25		0x00	/* P122	*/
#define DIGITAL_PIN_PIM_26		0x00	/* P137	*/
#define DIGITAL_PIN_PIM_27		0x00	/* P123	*/
#define DIGITAL_PIN_PIM_28		0x00	/* P124	*/
#define DIGITAL_PIN_PIM_29		0x00	/* P120	*/
#define DIGITAL_PIN_PIM_30		0x10	/* P04 	*/
#define DIGITAL_PIN_PIM_31		0x80	/* P17	*/
#define DIGITAL_PIN_PIM_32		0x40	/* P16	*/
#define DIGITAL_PIN_PIM_33		0x20	/* P15	*/
#define DIGITAL_PIN_PIM_34		0x10	/* P14	*/
#define DIGITAL_PIN_PIM_35		0x08 	/* P13	*/
#define DIGITAL_PIN_PIM_36		0x00	/* P12	*/
#define DIGITAL_PIN_PIM_37		0x02	/* P11	*/
#define DIGITAL_PIN_PIM_38		0x01	/* P10	*/
#define DIGITAL_PIN_PIM_39		0x00	/* P146	*/
#define DIGITAL_PIN_PIM_40		0x00	/* P147	*/
#define DIGITAL_PIN_PIM_41		0x00	/* P21 	*/
#define DIGITAL_PIN_PIM_42		0x00	/* P130	*/
#define DIGITAL_PIN_PIM_43		0x02	/* P01 	*/
#define DIGITAL_PIN_PIM_44		0x00	/* P00 	*/
#define DIGITAL_PIN_PIM_45		0x00	/* P141	*/
#define DIGITAL_PIN_PIM_46		0x00	/* P140	*/
#define DIGITAL_PIN_PIM_47		0x00	/* P60	*/
#define DIGITAL_PIN_PIM_48		0x00	/* P61	*/
#define DIGITAL_PIN_PIM_49		0x00	/* P62	*/
#define DIGITAL_PIN_PIM_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_PIM_51		0x00	/* P22	*/
#define DIGITAL_PIN_PIM_52		0x00	/* P23	*/
#define DIGITAL_PIN_PIM_53		0x00	/* P24	*/
#define DIGITAL_PIN_PIM_54		0x00	/* P25	*/
#define DIGITAL_PIN_PIM_55		0x00	/* P26	*/
#define DIGITAL_PIN_PIM_56		0x00	/* P27	*/
/* For A0-A6 */

/* Define Digital Pin POM */
#define DIGITAL_PIN_POM_0		0x08	/* P03	*/
#define DIGITAL_PIN_POM_1		0x04	/* P02	*/
#define DIGITAL_PIN_POM_2		0x00	/* P43	*/
#define DIGITAL_PIN_POM_3		0x04	/* P42	*/
#define DIGITAL_PIN_POM_4		0x00	/* P77	*/
#define DIGITAL_PIN_POM_5		0x00	/* P41	*/
#define DIGITAL_PIN_POM_6		0x00	/* P31	*/
#define DIGITAL_PIN_POM_7		0x00	/* P76	*/
#define DIGITAL_PIN_POM_8		0x00	/* P73	*/
#define DIGITAL_PIN_POM_9		0x00	/* P06	*/
#define DIGITAL_PIN_POM_10		0x00	/* P05	*/
#define DIGITAL_PIN_POM_11		0x00	/* P51	*/
#define DIGITAL_PIN_POM_12		0x01	/* P50	*/
#define DIGITAL_PIN_POM_13		0x00	/* P30	*/
#define DIGITAL_PIN_POM_14		0x00	/* P20(REF)	*/
#define DIGITAL_PIN_POM_15		0x00	/* P52	*/
#define DIGITAL_PIN_POM_16		0x00	/* P53	*/
#define DIGITAL_PIN_POM_17		0x00	/* P54	*/
#define DIGITAL_PIN_POM_18		0x20	/* P55	*/
#define DIGITAL_PIN_POM_19		0x00	/* P70	*/
#define DIGITAL_PIN_POM_20		0x02	/* P71	*/
#define DIGITAL_PIN_POM_21		0x04	/* P72	*/
#define DIGITAL_PIN_POM_22		0x10	/* P74	*/
#define DIGITAL_PIN_POM_23		0x00	/* P75	*/
#define DIGITAL_PIN_POM_24		0x00	/* P121	*/
#define DIGITAL_PIN_POM_25		0x00	/* P122	*/
#define DIGITAL_PIN_POM_26		0x00	/* P137	*/
#define DIGITAL_PIN_POM_27		0x00	/* P123	*/
#define DIGITAL_PIN_POM_28		0x00	/* P124	*/
#define DIGITAL_PIN_POM_29		0x01	/* P120	*/
#define DIGITAL_PIN_POM_30		0x10	/* P04 	*/
#define DIGITAL_PIN_POM_31		0x80	/* P17	*/
#define DIGITAL_PIN_POM_32		0x00	/* P16	*/
#define DIGITAL_PIN_POM_33		0x20	/* P15	*/
#define DIGITAL_PIN_POM_34		0x10	/* P14	*/
#define DIGITAL_PIN_POM_35		0x08 	/* P13	*/
#define DIGITAL_PIN_POM_36		0x04	/* P12	*/
#define DIGITAL_PIN_POM_37		0x02	/* P11	*/
#define DIGITAL_PIN_POM_38		0x01	/* P10	*/
#define DIGITAL_PIN_POM_39		0x00	/* P146	*/
#define DIGITAL_PIN_POM_40		0x00	/* P147	*/
#define DIGITAL_PIN_POM_41		0x00	/* P21 	*/
#define DIGITAL_PIN_POM_42		0x00	/* P130	*/
#define DIGITAL_PIN_POM_43		0x00	/* P01 	*/
#define DIGITAL_PIN_POM_44		0x01	/* P00 	*/
#define DIGITAL_PIN_POM_45		0x00	/* P141	*/
#define DIGITAL_PIN_POM_46		0x00	/* P140	*/
#define DIGITAL_PIN_POM_47		0x00	/* P60	*/
#define DIGITAL_PIN_POM_48		0x00	/* P61	*/
#define DIGITAL_PIN_POM_49		0x00	/* P62	*/
#define DIGITAL_PIN_POM_50		0x00	/* P63	*/

/* For A0-A5 */
#define DIGITAL_PIN_POM_51		0x00	/* P22	*/
#define DIGITAL_PIN_POM_52		0x00	/* P23	*/
#define DIGITAL_PIN_POM_53		0x00	/* P24	*/
#define DIGITAL_PIN_POM_54		0x00	/* P25	*/
#define DIGITAL_PIN_POM_55		0x00	/* P26	*/
#define DIGITAL_PIN_POM_56		0x00	/* P27	*/
/* For A0-A6 */

///* Bit mask of digital pin define. */
//#define DIGITAL_PIN_MASK_0	0x02	// P11
//#define DIGITAL_PIN_MASK_1	0x04	// P12
//#define DIGITAL_PIN_MASK_2	0x01	// P30
//#define DIGITAL_PIN_MASK_3	0x40	// P16
//#define DIGITAL_PIN_MASK_4	0x02	// P31
//#define DIGITAL_PIN_MASK_5	0x20	// P15
//#define DIGITAL_PIN_MASK_6	0x01	// P10
//#define DIGITAL_PIN_MASK_7	0x01	// P00
//#define DIGITAL_PIN_MASK_8	0x02	// P01
//#define DIGITAL_PIN_MASK_9	0x08	// P13
//#define DIGITAL_PIN_MASK_10	0x10	// P14
//#define DIGITAL_PIN_MASK_11	0x04	// P72
//#define DIGITAL_PIN_MASK_12	0x02	// P71
//#define DIGITAL_PIN_MASK_13	0x01	// P70
//#define DIGITAL_PIN_MASK_14	0x04	// P22
//#define DIGITAL_PIN_MASK_15	0x08	// P23
//#define DIGITAL_PIN_MASK_16	0x10	// P24
//#define DIGITAL_PIN_MASK_17	0x20	// P25
//#define DIGITAL_PIN_MASK_18	0x40	// P25
//#define DIGITAL_PIN_MASK_19	0x80	// P27
//#define DIGITAL_PIN_MASK_20	0x80	// P147
//#define DIGITAL_PIN_MASK_21	0x01	// P120
//#define DIGITAL_PIN_MASK_22	0x80	// P17
//#define DIGITAL_PIN_MASK_23	0x02	// P51
//#define DIGITAL_PIN_MASK_24	0x01	// P50
//#define DIGITAL_PIN_MASK_25	0x80	// P137
//#define DIGITAL_PIN_MASK_26	0x01	// P140
//#define DIGITAL_PIN_MASK_27	0x02	// P41
//#define DIGITAL_PIN_MASK_28	0x08	// P73
//#define DIGITAL_PIN_MASK_29	0x10	// P74
//#define DIGITAL_PIN_MASK_30	0x20	// P75
#endif

#define SWPWM_PIN			0xE0

#define PWM_PIN_3			3		// TO4
#define PWM_PIN_5			5		// TO7
#define PWM_PIN_6			6		// TO3
#define PWM_PIN_9			9		// TO6
#define PWM_PIN_10			10		// TO5
#define PWM_PIN_11			11		// TO2

#define TONE_PIN_3			3		// TO4
#define TONE_PIN_5			5		// TO7
#define TONE_PIN_6			6		// TO3
#define TONE_PIN_9			9		// TO6
#define TONE_PIN_10			10		// TO5
#define TONE_PIN_11			11		// TO2 -> ELCL


/* 1006 Nhu add */
/* Define Serial Port Number */
#define SERIAL_TXD0			36 // P12
#define SERIAL_RXD0			37 // P11

#define SERIAL_TXD1			1  // P02
#define SERIAL_RXD1			0  // P03

#define SERIAL_TXD2			35 // P13
#define SERIAL_RXD2			34 // P14
/* Define Serial Port Number */


/* Define Firmata library */
#define TOTAL_ANALOG_PINS       NUM_ANALOG_INPUTS //6
#define TOTAL_PINS              NUM_DIGITAL_PINS // 14 digital + 6 analog + 6 reserved + 10 internal used + 2 I2C + 3 SPI
#define TOTAL_PORTS             15 //P00 - P147
#define VERSION_BLINK_PIN       BUILTIN_LED1
#define PIN_SERIAL0_RX          37
#define PIN_SERIAL0_TX          36
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define PIN_SERIAL2_RX          34
#define PIN_SERIAL2_TX          35
#if defined(UART_CHANNEL)
#define IS_PIN_SERIAL0(p)        ((p) == PIN_SERIAL0_RX || (p) == PIN_SERIAL0_TX )
#else
#define IS_PIN_SERIAL0(p)        (0)
#endif

#if defined(UART1_CHANNEL)
#define IS_PIN_SERIAL1(p)        ((p) == PIN_SERIAL1_RX || (p) == PIN_SERIAL1_TX)
#else
#define IS_PIN_SERIAL1(p)        (0)
#endif

#if defined(UART2_CHANNEL)
#define IS_PIN_SERIAL2(p)        ((p) == PIN_SERIAL2_RX || (p) == PIN_SERIAL2_TX)
#else
#define IS_PIN_SERIAL2(p)        (0)
#endif

// #define IS_PIN_SERIAL1(p)        (0)
// #define IS_PIN_SERIAL2(p)        ((p) == PIN_SERIAL2_RX || (p) == PIN_SERIAL2_TX)

#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < NUM_DIGITAL_PINS && (!(IS_PIN_SERIAL(p))) && !((p) == 14) && !((p) == 27) && !((p) == 28) && !((p) == 41) )
#define IS_PIN_ANALOG(p)        ((p) >= 51 && (p) < 57)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 47 || (p) == 48 || (p) == 49 || (p) == 50)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        (IS_PIN_SERIAL0(p) || IS_PIN_SERIAL1(p) || IS_PIN_SERIAL2(p))
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 51)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)
#define ANALOG_TO_PIN(p)        ((p) + 51)
/* Define Firmata library */

#endif // #variant
