/*
  HardwareUart.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 7 March 2013 by masahiko.nagata.cj@renesas.com
  Modified 30 June 2013 by yuuki.okamiya.yn@renesas.com
  Modified 13 Mar 2018 by yuuki.okamiya.yn@renesas.com
*/
/*
 * FIXME: Temporary: Debug Display Mode
 *    Remove this macro definition and macro use later,
 *    if `Serial.write()` is fixed to work.
 */
/* #define DEBUGDISP_MODE */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

extern "C" {
    uint32_t R_BSP_GetFclkFreqHz(void);
    void Set_Char_Serial_from_buf(uint8_t chn);
}

#include "Arduino.h"
// #include "platform.h"


extern "C" {
    #include "pintable.h"
    extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];
}

extern "C" {
#if ( UART_CHANNEL == 0 )
    #include "Config_UART0.h"
#endif /* ( UART_CHANNEL == 0 ) */
#if ( UART1_CHANNEL == 1 )
    #include "Config_UART1.h"
#endif /* ( UART1_CHANNEL == 1 ) */
#if ( UART2_CHANNEL == 2 )
    #include "Config_UART2.h"
#endif /* ( UART2_CHANNEL == 2 ) */


};

#if ( UART_CHANNEL == 0 ) /* ( UART_CHANNEL == 2 ) */
#define URT_RXDx     RXD0
#define URT_TXDx     TXD0
#define URT_PERx     PER0.per0
#define URT_SAUxEN   SAU0EN             /* :PER0.2  */
#define URT_SPSx     SPS0
#define URT_STx      ST0
#define URT_MKxx     MK0H.mk0h
#define URT_IFxx     IF0H.if0h
#define URT_PR1xx    PR10H.pr10h
#define URT_PR0xx    PR00H.pr00h
#define URT_STMKx    STMK0              /* :MK0H.5  */
#define URT_STIFx    STIF0              /* :IF0H.5  */
#define URT_SRMKx    SRMK0              /* :MK0H.6  */
#define URT_SRIFx    SRIF0              /* :IF0H.6  */
#define URT_SREMKx   SREMK0             /* :MK0H.7  */
#define URT_SREIFx   SREIF0             /* :IF0H.7  */
#define URT_STPR1x   STPR10             /* :PR10H.5 */
#define URT_STPR0x   STPR00             /* :PR00H.5 */
#define URT_SRPR1x   SRPR10             /* :PR10H.6 */
#define URT_SRPR0x   SRPR00             /* :PR00H.6 */
#define URT_SREPR1x  SREPR10            /* :PR10H.7 */
#define URT_SREPR0x  SREPR00            /* :PR00H.7 */
#define URT_SMRx0    SMR00
#define URT_SCRx0    SCR00
#define URT_SDRx0    SDR00
#define URT_NFENx    NFEN0
#define URT_SNFENxx  SNFEN00            /* :NFEN0.0 */
#define URT_SIRx1    SIR01
#define URT_SMRx1    SMR01
#define URT_SCRx1    SCR01
#define URT_SDRx1    SDR01
#define URT_SOx      SO0.so0
#define URT_SOxx     SO00               /* :SO0.0   */
#define URT_SOLx     SOL0
#define URT_SOLxx    SOL00              /* :SOL0.0  */
#define URT_SOEx     SOE0
#define URT_SOExx    SOE00              /* :SOE0.0  */
#define URT_SSx      SS0
#define URT_SSxx     SS00               /* :SS0.0   */
#define URT_SSRx     SSR00
#define URT_Px       P1
#define URT_PMx      PM1
#define URT_TXD_Px   0x04
#define URT_RXD_Px   0x02
#endif /* ( UART_CHANNEL == 2 ) */

#if ( UART1_CHANNEL == 1 )
#define URT1_RXDx     RXD1
#define URT1_TXDx     TXD1
#define URT1_PERx     PER0.per0
#define URT1_SAUxEN   SAU0EN            /* :PER0.2  */
#define URT1_SPSx     SPS0
#define URT1_STx      ST0
#define URT1_MKxx     MK1L.mk1l
#define URT1_IFxx     IF1L.if1l
#define URT1_PR1xx    PR11L.pr11l
#define URT1_PR0xx    PR01L.pr01l
#define URT1_STMKx    STMK1             /* :MK1L.0  */
#define URT1_STIFx    STIF1             /* :IF1L.0  */
#define URT1_SRMKx    SRMK1             /* :MK1L.1  */
#define URT1_SRIFx    SRIF1             /* :IF1L.1  */
#define URT1_SREMKx   SREMK1            /* :MK1L.2  */
#define URT1_SREIFx   SREIF1            /* :IF1L.2  */
#define URT1_STPR1x   STPR11            /* :PR11L.0 */
#define URT1_STPR0x   STPR01            /* :PR01L.0 */
#define URT1_SRPR1x   SRPR11            /* :PR11L.1 */
#define URT1_SRPR0x   SRPR01            /* :PR01L.1 */
#define URT1_SREPR1x  SREPR11           /* :PR11L.2 */
#define URT1_SREPR0x  SREPR01           /* :PR01L.2 */
#define URT1_SMRx0    SMR02
#define URT1_SCRx0    SCR02
#define URT1_SDRx0    SDR02
#define URT1_NFENx    NFEN0
#define URT1_SNFENxx  SNFEN10           /* :NFEN0.2 */
#define URT1_SIRx1    SIR03
#define URT1_SMRx1    SMR03
#define URT1_SCRx1    SCR03
#define URT1_SDRx1    SDR03
#define URT1_SOx      SO0.so0
#define URT1_SOxx     SO02              /* :SO0.2   */
#define URT1_SOLx     SOL0.sol0
#define URT1_SOLxx    SOL02             /* :SOL0.2  */
#define URT1_SOEx     SOE0
#define URT1_SOExx    SOE02             /* :SOE0.2  */
#define URT1_SSx      SS0
#define URT1_SSxx     SS02              /* :SS0.2   */
#define URT1_SSRx     SSR02
#define URT1_Px       P0
#define URT1_PMx      PM0
#ifdef GRCOTTON
#define URT1_TXD_Px   0x04
#define URT1_RXD_Px   0x08
#define URT1_PMCx     PMC0.pmc0
#else /* GRCOTTON */
#define URT1_TXD_Px   0x01
#define URT1_RXD_Px   0x02
#endif /* GRCOTTON */
#endif /* ( UART1_CHANNEL == 1 ) */
#if ( UART2_CHANNEL == 2 )
#define URT2_RXDx     RXD2
#define URT2_TXDx     TXD2
#define URT2_PERx     PER0.per0
#define URT2_SAUxEN   SAU1EN            /* :PER0.3  */
#define URT2_SPSx     SPS1
#define URT2_STx      ST1
#define URT2_MKxx     MK0H.mk0h
#define URT2_IFxx     IF0H.if0h
#define URT2_PR1xx    PR10H.pr10h
#define URT2_PR0xx    PR00H.pr00h
#define URT2_STMKx    STMK2             /* :MK0H.0  */
#define URT2_STIFx    STIF2             /* :IF0H.0  */
#define URT2_SRMKx    SRMK2             /* :MK0H.1  */
#define URT2_SRIFx    SRIF2             /* :IF0H.1  */
#define URT2_SREMKx   SREMK2            /* :MK0H.2  */
#define URT2_SREIFx   SREIF2            /* :IF0H.2  */
#define URT2_STPR1x   STPR12            /* :PR10H.0 */
#define URT2_STPR0x   STPR02            /* :PR00H.0 */
#define URT2_SRPR1x   SRPR12            /* :PR10H.1 */
#define URT2_SRPR0x   SRPR02            /* :PR00H.1 */
#define URT2_SREPR1x  SREPR12           /* :PR10H.2 */
#define URT2_SREPR0x  SREPR02           /* :PR00H.2 */
#define URT2_SMRx0    SMR10
#define URT2_SCRx0    SCR10
#define URT2_SDRx0    SDR10
#define URT2_NFENx    NFEN0
#define URT2_SNFENxx  SNFEN20           /* :NFEN0.4 */
#define URT2_SIRx1    SIR11
#define URT2_SMRx1    SMR11
#define URT2_SCRx1    SCR11
#define URT2_SDRx1    SDR11
#define URT2_SOx      SO1.so1
#define URT2_SOxx     SO10              /* :SO1.0   */
#define URT2_SOLx     SOL1.sol1
#define URT2_SOLxx    SOL10             /* :SOL1.0  */
#define URT2_SOEx     SOE1
#define URT2_SOExx    SOE10             /* :SOE1.0  */
#define URT2_SSx      SS1
#define URT2_SSxx     SS10              /* :SS1.0   */
#define URT2_SSRx     SSR10
#define URT2_Px       P1
#define URT2_PMx      PM1
#define URT2_TXD_Px   0x08
#define URT2_RXD_Px   0x10
#endif /* ( UART2_CHANNEL == 2 ) */

#if ( UART_CHANNEL == 0 ) /* ( UART_CHANNEL == 2 ) */
#define URT_SFR_RXDx         0xfff12    /* RXD0.rxd0       */
#define URT_SFR_TXDx         0xfff10    /* TXD0.txd0       */
#define URT_SFR2_PERx        0xf00f0    /* PER0.per0       */
#define URT_SFR2_BIT_SAUxEN  2          /* SAU0EN :PER0.2  */
#define URT_SFR2_SPSx        0xf0126    /* SPS0.sps0       */
#define URT_SFR2_STx         0xf0124    /* ST0.st0         */
#define URT_SFR2_BIT_STxx0   0          /* ST00   :ST0.0   */
#define URT_SFR2_BIT_STxx1   1          /* ST01   :ST0.1   */
#define URT_SFR_MKxx         0xfffe5    /* MK0H.mk0h       */
#define URT_SFR_IFxx         0xfffe1    /* IF0H.if0h       */
#define URT_SFR_PR1xx        0xfffed    /* PR10H.pr10h     */
#define URT_SFR_PR0xx        0xfffe9    /* PR00H.pr00h     */
#define URT_SFR_BIT_STMKx    5          /* STMK0  :MK0H.5  */
#define URT_SFR_BIT_STIFx    5          /* STIF0  :IF0H.5  */
#define URT_SFR_BIT_SRMKx    6          /* SRMK0  :MK0H.6  */
#define URT_SFR_BIT_SRIFx    6          /* SRIF0  :IF0H.6  */
#define URT_SFR_BIT_SREMKx   7          /* SREMK0 :MK0H.7  */
#define URT_SFR_BIT_SREIFx   7          /* SREIF0 :IF0H.7  */
#define URT_SFR_BIT_STPR1x   5          /* STPR10 :PR10H.5 */
#define URT_SFR_BIT_STPR0x   5          /* STPR00 :PR00H.5 */
#define URT_SFR_BIT_SRPR1x   6          /* SRPR10 :PR10H.6 */
#define URT_SFR_BIT_SRPR0x   6          /* SRPR00 :PR00H.6 */
#define URT_SFR_BIT_SREPR1x  7          /* SREPR10:PR10H.7 */
#define URT_SFR_BIT_SREPR0x  7          /* SREPR00:PR00H.7 */
#define URT_SFR2_SMRx0       0xf0110    /* SMR00.smr00     */
#define URT_SFR2_SCRx0       0xf0118    /* SCR00.scr00     */
#define URT_SFR_SDRx0        0xfff10    /* SDR00.sdr00     */
#define URT_SFR2_NFENx       0xf0070    /* NFEN0.nfen0     */
#define URT_SFR2_BIT_SNFENxx 0          /* SNFEN00:NFEN0.0 */
#define URT_SFR2_SIRx1       0xf010a    /* SIR01.sir01     */
#define URT_SFR2_SMRx1       0xf0112    /* SMR01.smr01     */
#define URT_SFR2_SCRx1       0xf011a    /* SCR01.scr01     */
#define URT_SFR2_SDRx1       0xfff12    /* SDR01.sdr01     */
#define URT_SFR2_SOx         0xf0128    /* SO0.so0         */
#define URT_SFR2_BIT_SOxx    0          /* SO00   :SO0.0   */
#define URT_SFR2_SOLx        0xf0134    /* SOL0.sol0       */
#define URT_SFR2_BIT_SOLxx   0          /* SOL00  :SOL0.0  */
#define URT_SFR2_SOEx        0xf012a    /* SOE0.soe0       */
#define URT_SFR2_BIT_SOExx   0          /* SOE00  :SOE0.0  */
#define URT_SFR2_SSx         0xf0122    /* SS0.ss0         */
#define URT_SFR2_BIT_SSxx0   0          /* SS00   :SS0.0   */
#define URT_SFR2_BIT_SSxx1   1          /* SS01   :SS0.1   */
#endif /* ( UART_CHANNEL == 2 ) */

#if ( UART1_CHANNEL == 1 )
#define URT1_SFR_RXDx         0xfff46   /* RXD1.rxd1       */
#define URT1_SFR_TXDx         0xfff44   /* TXD1.txd1       */
#define URT1_SFR2_PERx        0xf00f0   /* PER0.per0       */
#define URT1_SFR2_BIT_SAUxEN  2         /* SAU0EN :PER0.2  */
#define URT1_SFR2_SPSx        0xf0126   /* SPS0.sps0       */
#define URT1_SFR2_STx         0xf0124   /* ST0.st0         */
#define URT1_SFR2_BIT_STxx0   2         /* ST02   :ST0.2   */
#define URT1_SFR2_BIT_STxx1   3         /* ST03   :ST0.3   */
#define URT1_SFR_MKxx         0xfffe6   /* MK1L.mk1l       */
#define URT1_SFR_IFxx         0xfffe2   /* IF1L.if1l       */
#define URT1_SFR_PR1xx        0xfffee   /* PR11L.pr11l     */
#define URT1_SFR_PR0xx        0xfffea   /* PR01L.pr01l     */
#define URT1_SFR_BIT_STMKx    0         /* STMK1  :MK1L.0  */
#define URT1_SFR_BIT_STIFx    0         /* STIF1  :IF1L.0  */
#define URT1_SFR_BIT_SRMKx    1         /* SRMK1  :MK1L.1  */
#define URT1_SFR_BIT_SRIFx    1         /* SRIF1  :IF1L.1  */
#define URT1_SFR_BIT_SREMKx   2         /* SREMK1 :MK1L.2  */
#define URT1_SFR_BIT_SREIFx   2         /* SREIF1 :IF1L.2  */
#define URT1_SFR_BIT_STPR1x   0         /* STPR11 :PR11L.0 */
#define URT1_SFR_BIT_STPR0x   0         /* STPR01 :PR01L.0 */
#define URT1_SFR_BIT_SRPR1x   1         /* SRPR11 :PR11L.1 */
#define URT1_SFR_BIT_SRPR0x   1         /* SRPR01 :PR01L.1 */
#define URT1_SFR_BIT_SREPR1x  2         /* SREPR11:PR11L.2 */
#define URT1_SFR_BIT_SREPR0x  2         /* SREPR01:PR01L.2 */
#define URT1_SFR2_SMRx0       0xf0114   /* SMR02.smr02     */
#define URT1_SFR2_SCRx0       0xf011c   /* SCR02.scr02     */
#define URT1_SFR_SDRx0        0xfff44   /* SDR02.sdr02     */
#define URT1_SFR2_NFENx       0xf0070   /* NFEN0.nfen0     */
#define URT1_SFR2_BIT_SNFENxx 2         /* SNFEN10:NFEN0.2 */
#define URT1_SFR2_SIRx1       0xf010e   /* SIR03.sir03     */
#define URT1_SFR2_SMRx1       0xf0116   /* SMR03.smr03     */
#define URT1_SFR2_SCRx1       0xf011e   /* SCR03.scr03     */
#define URT1_SFR2_SDRx1       0xfff46   /* SDR03.sdr03     */
#define URT1_SFR2_SOx         0xf0128   /* SO0.so0         */
#define URT1_SFR2_BIT_SOxx    2         /* SO02   :SO0.2   */
#define URT1_SFR2_SOLx        0xf0134   /* SOL0.sol0       */
#define URT1_SFR2_BIT_SOLxx   2         /* SOL02  :SOL0.2  */
#define URT1_SFR2_SOEx        0xf012a   /* SOE0.soe0       */
#define URT1_SFR2_BIT_SOExx   2         /* SOE02  :SOE0.2  */
#define URT1_SFR2_SSx         0xf0122   /* SS0.ss0         */
#define URT1_SFR2_BIT_SSxx0   2         /* SS02   :SS0.2   */
#define URT1_SFR2_BIT_SSxx1   3         /* SS03   :SS0.3   */
#endif /* ( UART1_CHANNEL == 1 ) */
#if ( UART2_CHANNEL == 2 )
#define URT2_SFR_RXDx         0xfff4a   /* RXD2.rxd2       */
#define URT2_SFR_TXDx         0xfff48   /* TXD2.txd2       */
#define URT2_SFR2_PERx        0xf00f0   /* PER0.per0       */
#define URT2_SFR2_BIT_SAUxEN  3         /* SAU1EN :PER0.3  */
#define URT2_SFR2_SPSx        0xf0166   /* SPS1.sps1       */
#define URT2_SFR2_STx         0xf0164   /* ST1.st1         */
#define URT2_SFR2_BIT_STxx0   0         /* ST10   :ST1.0   */
#define URT2_SFR2_BIT_STxx1   1         /* ST11   :ST1.1   */
#define URT2_SFR_MKxx         0xfffe5   /* MK0H.mk0h       */
#define URT2_SFR_IFxx         0xfffe1   /* IF0H.if0h       */
#define URT2_SFR_PR1xx        0xfffed   /* PR10H.pr10h     */
#define URT2_SFR_PR0xx        0xfffe9   /* PR00H.pr00h     */
#define URT2_SFR_BIT_STMKx    0         /* STMK2  :MK0H.0  */
#define URT2_SFR_BIT_STIFx    0         /* STIF2  :IF0H.0  */
#define URT2_SFR_BIT_SRMKx    1         /* SRMK2  :MK0H.1  */
#define URT2_SFR_BIT_SRIFx    1         /* SRIF2  :IF0H.1  */
#define URT2_SFR_BIT_SREMKx   2         /* SREMK2 :MK0H.2  */
#define URT2_SFR_BIT_SREIFx   2         /* SREIF2 :IF0H.2  */
#define URT2_SFR_BIT_STPR1x   0         /* STPR12 :PR10H.0 */
#define URT2_SFR_BIT_STPR0x   0         /* STPR02 :PR00H.0 */
#define URT2_SFR_BIT_SRPR1x   1         /* SRPR12 :PR10H.1 */
#define URT2_SFR_BIT_SRPR0x   1         /* SRPR02 :PR00H.1 */
#define URT2_SFR_BIT_SREPR1x  2         /* SREPR12:PR10H.2 */
#define URT2_SFR_BIT_SREPR0x  2         /* SREPR02:PR00H.2 */
#define URT2_SFR2_SMRx0       0xf0150   /* SMR10.smr10     */
#define URT2_SFR2_SCRx0       0xf0158   /* SCR10.scr10     */
#define URT2_SFR_SDRx0        0xfff48   /* SDR10.sdr10     */
#define URT2_SFR2_NFENx       0xf0070   /* NFEN0.nfen0     */
#define URT2_SFR2_BIT_SNFENxx 4         /* SNFEN20:NFEN0.4 */
#define URT2_SFR2_SIRx1       0xf014a   /* SIR11.sir11     */
#define URT2_SFR2_SMRx1       0xf0152   /* SMR11.smr11     */
#define URT2_SFR2_SCRx1       0xf015a   /* SCR11.scr11     */
#define URT2_SFR_SDRx1        0xfff4a   /* SDR11.sdr11     */
#define URT2_SFR2_SOx         0xf0168   /* SO1.so1         */
#define URT2_SFR2_BIT_SOxx    0         /* SO10   :SO1.0   */
#define URT2_SFR2_SOLx        0xf0174   /* SOL1.sol1       */
#define URT2_SFR2_BIT_SOLxx   0         /* SOL10  :SOL1.0  */
#define URT2_SFR2_SOEx        0xf016a   /* SOE1.soe1       */
#define URT2_SFR2_BIT_SOExx   0         /* SOE10  :SOE1.0  */
#define URT2_SFR2_SSx         0xf0162   /* SS1.ss1         */
#define URT2_SFR2_BIT_SSxx0   0         /* SS10   :SS1.0   */
#define URT2_SFR2_BIT_SSxx1   1         /* SS11   :SS1.1   */
#endif /* ( UART2_CHANNEL == 2 ) */

/*
 * this next line disables the entire HardwareUart.cpp,
 * this is so I can support Attiny series and any other chip without a uart
 */

#include "HardwareUart.h"

/*
 * Define constants and variables for buffering incoming serial data.  We're
 * using a ring buffer (I think), in which head is the index of the location
 * to which to write the next incoming character and tail is the index of the
 * location from which to read.
 */
// #define SERIAL_BUFFER_SIZE 256

void serialEventRun(void)
{

}

fInterruptFunc_t uart_receive_callback_table[3] __attribute__((weak));
fInterruptFunc_t uart_transmit_callback_table[3] __attribute__((weak));

// Constructors ////////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: HardwareUart::HardwareUart
 * Description  : Constructor
 * Arguments    : rxen - UART channel
 * Return Value : void
 *********************************************************************************************************************/
HardwareUart::HardwareUart(uint8_t rxen)
{
    _urt_channel   = rxen;
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    _rx_buf_size    = 0;
    _tx_buf_size    = 0;
    _rx_buffer      = 0;
    _tx_buffer      = 0;
    transmitting    = 0;
    receive_buffer  = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: HardwareUart::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::begin(unsigned long baud)
{
    begin(baud, SERIAL_8N1);
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::begin(unsigned long baud, uint16_t config){
    begin(baud, config, SERIAL_BUFFER_SIZE, SERIAL_BUFFER_SIZE);
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : rx_buf - receive  buffer size
 *              : tx_buf - transmit buffer size
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::begin(unsigned long baud, int rx_buf, int tx_buf){
    begin(baud, SERIAL_8N1, rx_buf, tx_buf);
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 *              : rx_buf - receive  buffer size
 *              : tx_buf - transmit buffer size
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::begin(unsigned long baud, uint16_t config, int rx_buf, int tx_buf)
{
    /* Initialize Unit */
    /* begin executed. end call */
    if ((0 != _rx_buffer) || (0 != _tx_buffer)){
        return;
    }
    if ((1 == rx_buf) || (1 == tx_buf)){
        return;
    }
#if defined(FEW_RAM_MODEL) && (FEW_RAM_MODEL == 1)
    _rx_buffer = base_rx_buffer;
    _tx_buffer = base_tx_buffer;
#else
    _rx_buffer = (uint8_t *)malloc((size_t)(rx_buf * (int)sizeof(uint8_t)));
    if (0 == _rx_buffer){
        _rx_buf_size = 0;
        _tx_buf_size = 0;
        return;
    }
    _tx_buffer = (uint8_t *)malloc((size_t)(tx_buf * (int)sizeof(uint8_t)));
    if (0 == _tx_buffer){
        free((uint8_t *)_rx_buffer);
        _rx_buffer = 0;
        _rx_buf_size = 0;
        _tx_buf_size = 0;
        return;
    }
#endif

    _rx_buf_size = rx_buf;
    _tx_buf_size = tx_buf;
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;

    switch (_urt_channel)
    {
        case 0:
#if (UART_CHANNEL==0)
            R_Config_UART0_Create();
            Set_Baudrate(baud);
            Set_SerialPort(SERIAL_TXD0,SERIAL_RXD0);
            Set_Config(config);
            R_Config_UART0_Start();
            R_Config_UART0_Receive((uint8_t * const)&receive_buffer,1);
#endif /* UART_CHANNEL==0 */
            break;
        case 1:
#if (UART1_CHANNEL==1)
            R_Config_UART1_Create();
            Set_Baudrate(baud);
            Set_SerialPort(SERIAL_TXD1,SERIAL_RXD1);
            Set_Config(config);
            R_Config_UART1_Start();
            R_Config_UART1_Receive((uint8_t * const)&receive_buffer,1);
#endif /* UART1_CHANNEL==1 */
            break;
        case 2:
#if (UART2_CHANNEL==2)
            R_Config_UART2_Create();
            Set_Baudrate(baud);
            Set_SerialPort(SERIAL_TXD2,SERIAL_RXD2);
            Set_Config(config);
            R_Config_UART2_Start();
            R_Config_UART2_Receive((uint8_t * const)&receive_buffer,1);
#endif /* UART2_CHANNEL==2 */
            break;
        case 3:
            break;
        default :
            /* Do nothing */
            break;
    }
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::end
 * Description  : Terminate the serial port processing.
 * Arguments    : -
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::end()
{
    switch (_urt_channel)
    {
    case 0:
#if (UART_CHANNEL == 0 )
        R_Config_UART0_Stop();
#endif /* (UART_CHANNEL == 0 ) */
        break;
    case 1:
#if (UART1_CHANNEL == 1 )
        R_Config_UART1_Stop();
#endif /* (UART1_CHANNEL == 1 ) */
        break;
    case 2:
#if (UART2_CHANNEL == 2 )
        R_Config_UART2_Stop();
#endif /* (UART2_CHANNEL == 2 ) */
        break;
    case 3:
        break;
        }
#if defined(FEW_RAM_MODEL) && (FEW_RAM_MODEL == 1)
    _rx_buffer = 0;
    _tx_buffer = 0;
#else
    if(_rx_buffer!= 0)
    {
        free((uint8_t *)_rx_buffer);
        _rx_buffer = 0;
    }
    if(_tx_buffer!= 0)
    {
        free((uint8_t *)_tx_buffer);
        _tx_buffer = 0;
    }
#endif
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    _rx_buf_size = 0;
    _tx_buf_size = 0;
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::available
 * Description  : Get the number of readable data bytes of received data.
 * Arguments    : -
 * Return Value : size of readable data
 *********************************************************************************************************************/
int HardwareUart::available(void)
{
    int head = 0;
    int tail = 0;
    noInterrupts();
    head = _rx_buffer_head;
    tail = _rx_buffer_tail;
    interrupts();
    if (head >= tail) return head - tail;
    return (_rx_buf_size - tail + head );
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::peek
 * Description  : Read received data by 1 byte and do not change the buffer position.
 * Arguments    : -
 * Return Value : -1    - no read data
 *              : other - read data
 *********************************************************************************************************************/
int HardwareUart::peek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    return _rx_buffer[_rx_buffer_tail];
  }
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::read
 * Description  : Read received data by 1 byte and advance the buffer position by 1 byte.
 * Arguments    : -
 * Return Value : -1    - no read data
 *              : other - read data
 *********************************************************************************************************************/
int HardwareUart::read(void)
{
    /* if the head isn't ahead of the tail, we don't have any characters */
    noInterrupts();
    if (_rx_buffer_head == _rx_buffer_tail) {
        interrupts();
        return -1;
    }
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (_rx_buffer_tail + 1) % _rx_buf_size;
    interrupts();

    return c;
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::flush
 * Description  : Wait for all data transmission in the transmission buffer to be completed.
 * Arguments    : -
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::flush()
{
  /* buffer is none */
  if (0 == _tx_buf_size || 0 == _tx_buffer){
    return;
  }
  if (_urt_channel == 0) {
    while (SSR00 & (_0040_SAU_UNDER_EXECUTE | _0020_SAU_VALID_STORED)) {  /* check TSF00 and BFF00 */
      ;
    }
  }
  else if (_urt_channel == 1) {
    while (SSR02 & (_0040_SAU_UNDER_EXECUTE | _0020_SAU_VALID_STORED)) {  /* check TSF02 and BFF02 */
      ;
    }
  }
#if ( UART2_CHANNEL == 2 )
  else if (_urt_channel == 2) {
    while (SSR10 & (_0040_SAU_UNDER_EXECUTE | _0020_SAU_VALID_STORED)) {  /* check TSF10 and BFF10 */

      ;
    }
  }
#endif /* ( UART2_CHANNEL == 2 ) */

  while(_tx_buf_size-1!=availableForWrite())
  {
    NOP();
  }
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::UART_Send
 * Description  : Transmit data to the target serial port (actual implementation of write operation).
 * Arguments    : c - transmission data
 * Return Value : -1    - write failed with the transmission buffer overflow
 *              : other - written data size
 *********************************************************************************************************************/
size_t HardwareUart::UART_Send(uint8_t c)
{
    MD_STATUS err = MD_OK;
    int i;
    uint8_t isp;
    size_t ret = 0;

    /* buffer is none */
    if (0 == _tx_buf_size){
        return ret;
    }

    isp = (uint8_t)GET_PSW_ISP();

    noInterrupts();
    if(_tx_buffer_tail == _tx_buffer_head){
        /* Unsent */
        //int head = (_tx_buffer_head + 1);
        i = (_tx_buffer_head + 1) % _tx_buf_size;
        _tx_buffer[_tx_buffer_head] = c;
        _tx_buffer_head = i;
        interrupts();

        switch (_urt_channel)
        {
            case 0:
                if((SSR00 & _0020_SAU_VALID_STORED) != 0)/*BFF00*/
                {
                    return 0;
                }
                err = R_Config_UART0_Send((uint8_t * const)&c,1);
                break;
            case 1:
                if((SSR02 & _0020_SAU_VALID_STORED) != 0)/*BFF02*/
                {
                    return 0;
                }
                err = R_Config_UART1_Send((uint8_t * const)&c,1);
                break;
            case 2:
#if ( UART2_CHANNEL == 2 )
                if((SSR10 & _0020_SAU_VALID_STORED) != 0)/*BFF10*/
                {
                    return 0;
                }
                err = R_Config_UART2_Send((uint8_t * const)&c,1);
#endif /* ( UART2_CHANNEL == 2 ) */
                break;
            case 3:
                break;
        }
    }
    else
    {
        /* only buffer copy during transmission process */
        i = (_tx_buffer_head + 1) % _tx_buf_size;
        if(i == _tx_buffer_tail)
        {
            /* buffer over */
            if(ISP_LEVEL_3 == isp)
            {
                /* When called from main program(setup() or loop() */
                interrupts();
                while(i == _tx_buffer_tail)
                {
                    ;
                }
                noInterrupts();
            }
            else
            {
                /* When called from interuupt function (ex. callback routine for periodic processing */
                switch (_urt_channel)
                {
                    case 0:
        #if ( UART_CHANNEL == 0 )
                        while((SSR00 & _0020_SAU_VALID_STORED) != 0)/*BFF00*/
                        {
                            ;
                        }
                        STIF0 = 0;
        #endif /* ( UART_CHANNEL == 0 ) */
                        break;
                    case 1:
        #if ( UART1_CHANNEL == 1 )
                        while((SSR02 & _0020_SAU_VALID_STORED) != 0)/*BFF02*/
                        {
                            ;
                        }
                        STIF1 = 0;
        #endif /* ( UART1_CHANNEL == 1 ) */
                        break;
                    case 2:
        #if ( UART2_CHANNEL == 2 )
                        while((SSR10 & _0020_SAU_VALID_STORED) != 0)/*BFF10*/
                        {
                            ;
                        }
                        STIF2 = 0;
        #endif /* ( UART2_CHANNEL == 2 ) */
                        break;
                    case 3:
                        break;
                }
                Set_Char_Serial_from_buf(_urt_channel);
                if(0 != uart_transmit_callback_table[_urt_channel])
                {
                    (*uart_transmit_callback_table[_urt_channel])();
                }
            }
        }
        _tx_buffer[_tx_buffer_head] = c;
        _tx_buffer_head = i;
        interrupts();
    }
    if(err == MD_OK){
        return 1;
    }
    return ret;
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::write
 * Description  : Transmit data to the target serial port.
 * Arguments    : c - transmission data
 * Return Value : -1    - write failed with the transmission buffer overflow
 *              : other - written data size
 *********************************************************************************************************************/

size_t HardwareUart::write(uint8_t c)
{
    size_t err = 0;
    err = UART_Send(c);
    return err;
}


/**********************************************************************************************************************
 * Function Name: HardwareUart::availableForWrite
 * Description  : Get the number of available transmit buffer space for write.
 * Arguments    : -
 * Return Value : size of transmit buffer free space
 *********************************************************************************************************************/
int HardwareUart::availableForWrite(void)
{
  int head = 0;
  int tail = 0;
  noInterrupts();
  head = _tx_buffer_head;
  tail = _tx_buffer_tail;
  interrupts();
  if (head >= tail) return _tx_buf_size - 1 - head + tail;
  return (tail - head - 1);
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::availableForRead
 * Description  : Get the number of available receive buffer space for read.
 * Arguments    : -
 * Return Value : size of receive buffer free space
 *********************************************************************************************************************/
int HardwareUart::availableForRead(void)
{
  int head = 0;
  int tail = 0;
  noInterrupts();
  head = _rx_buffer_head;
  tail = _rx_buffer_tail;
  interrupts();
  if (head >= tail) return _rx_buf_size - 1 - head + tail;
  return (tail - head - 1);

}

HardwareUart::operator bool() {
    return true;
}

/* Load Send data from Send Buffer & Start New Send Function */
/**********************************************************************************************************************
 * Function Name: HardwareUart::load_char
 * Description  : Extract 1 byte from the transmit buffer and send it.
 *              : Called from the transmission complete interrupt handler.
 *              : Unavailable for the other purpose.
 * Arguments    :  -
 * Return Value :  -
 *********************************************************************************************************************/
void HardwareUart::load_char(void){
    int i = (_tx_buffer_tail + 1) % _tx_buf_size;
    _tx_buffer_tail = i;
    if (i != _tx_buffer_head) {
        uint8_t send_buffer  = _tx_buffer[i];
        switch (_urt_channel)
        {
        case 0:
#if (UART_CHANNEL == 0)
            R_Config_UART0_Send((uint8_t * const)&send_buffer,1);
#endif /* (UART_CHANNEL == 0) */
            break;
        case 1:
#if (UART1_CHANNEL == 1)
            R_Config_UART1_Send((uint8_t * const)&send_buffer,1);
#endif /* (UART1_CHANNEL == 1) */
            break;
        case 2:
#if (UART2_CHANNEL == 2)
            R_Config_UART2_Send((uint8_t * const)&send_buffer,1);
#endif /* (UART2_CHANNEL == 2) */
            break;
        case 3:
            break;
        }
    }
}


/* Store Received data to Receive Buffer & Start New Receive Function */
/**********************************************************************************************************************
 * Function Name: HardwareUart::store_char
 * Description  : Store 1 byte of the last received data in the receive buffer
 *              : and continue the receive process for the following bytes.
 *              : Called from the receive complete interrupt handler.
 *              : Unavailable for the other purpose.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void HardwareUart::store_char(void){
    store_char(receive_buffer);
    receive_buffer = 0;
    switch (_urt_channel)
    {
    case 0:
    #if (UART_CHANNEL == 0)
        R_Config_UART0_Receive((uint8_t * const)&receive_buffer,1);
    #endif /* (UART_CHANNEL == 0) */
        break;
    case 1:
    #if (UART1_CHANNEL == 1)
        R_Config_UART1_Receive((uint8_t * const)&receive_buffer,1);
    #endif /* (UART1_CHANNEL == 1) */
        break;
    case 2:
    #if (UART2_CHANNEL == 2)
        R_Config_UART2_Receive((uint8_t * const)&receive_buffer,1);
    #endif /* (UART2_CHANNEL == 2) */
        break;
        break;
    }
}

/**********************************************************************************************************************
 * Function Name: HardwareUart::store_char
 * Description  : Store 1 byte of the last received data in the receive buffer
 *              : and continue the receive process for the following bytes.
 *              : Make sure to disable interrupts before calling this from outside of the interrupt handler.
 * Arguments    : c - byte to store
 * Return Value : -
 *********************************************************************************************************************/
void HardwareUart::store_char(unsigned char c){
  int i = (_rx_buffer_head + 1) % _rx_buf_size;
  if (i != _rx_buffer_tail) {
    _rx_buffer[_rx_buffer_head] = c;
    _rx_buffer_head = i;
  }
}

/* Add for RL78/G23 */
/**********************************************************************************************************************
 * Function Name: HardwareUart::Set_Baudrate
 * Description  : Set baud rate for the serial port.
 * Arguments    : baudrate - baud rate
 *              :            { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::Set_Baudrate(unsigned long baudrate)
{
    uint32_t fclk_frequency;
    uint32_t  peri_clk    ;
    uint8_t  sdr     ;
    uint16_t tmp_sdr ;
    uint8_t  prs = 0U;
    fclk_frequency = R_BSP_GetFclkFreqHz();

    peri_clk    = (fclk_frequency) ; /* SPSmk0\[3:0] = 0x0 */

    tmp_sdr = (uint16_t)(((peri_clk/baudrate) >> 1) -1) ;
    while(0x007F<tmp_sdr)
    {
        prs++;
        peri_clk = (peri_clk >> 1);
        tmp_sdr  = (uint16_t)(((peri_clk/baudrate) >> 1) -1) ;
    }

    sdr     = (uint8_t)(tmp_sdr & 0x007F) ;

    switch (_urt_channel)
    {
        case 0:
#if ( UART_CHANNEL == 0 )
            SPS0 &= (_00F0_SAU_CK00_CLEAR) ;
            SPS0 |=  prs ;
            SDR00 = ((uint16_t)sdr) << 9 ;
            SDR01 = ((uint16_t)sdr) << 9 ;
#endif /* ( UART_CHANNEL == 0 ) */
            break;
        case 1:
#if ( UART1_CHANNEL == 1 )
            SPS0 &= (_000F_SAU_CK01_CLEAR) ;
            SPS0 |= ((uint16_t)prs << 4);
            SDR02 = ((uint16_t)sdr) << 9 ;
            SDR03 = ((uint16_t)sdr) << 9 ;
#endif /* ( UART1_CHANNEL == 1 ) */
            break;
        case 2:
#if ( UART2_CHANNEL == 2 )
            SPS1 &= (_00F0_SAU_CK00_CLEAR) ;
            SPS1 |= prs ;
            SDR10 = ((uint16_t)sdr) << 9 ;
            SDR11 = ((uint16_t)sdr) << 9 ;
#endif /* ( UART2_CHANNEL == 2 ) */
            break;
        case 3:
            break;
        default :
            /* Do nothing */
            break;
    }
}

#ifdef __RL78__
/**********************************************************************************************************************
 * Function Name: HardwareUart::Set_Config
 * Description  : Set the serial data length, parity, and stop bit.
 * Arguments    : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::Set_Config(uint16_t config )
{
    uint16_t converted_config = 0;

    switch(config)
    {
        case SERIAL_7N1:
        case SERIAL_8N1:
        case SERIAL_7N2:
        case SERIAL_8N2:
        case SERIAL_7E1:
        case SERIAL_8E1:
        case SERIAL_7E2:
        case SERIAL_8E2:
        case SERIAL_7O1:
        case SERIAL_8O1:
        case SERIAL_7O2:
        case SERIAL_8O2:
            /* Do nothing */
            break;
        default:
            config = SERIAL_8N1;
            break;
    }
    if(SERIAL_DATA_7 == (SERIAL_DATA_MASK & config))
    {
        converted_config |= _0002_SAU_LENGTH_7;
    }
    else
    {
        /* All other settings are treated as SERIAL_DATA_8(default). */
        converted_config |= _0003_SAU_LENGTH_8;
    }

    if(SERIAL_STOP_BIT_2 == (SERIAL_STOP_BIT_MASK & config))
    {
        converted_config |= _0020_SAU_STOP_2;
    }
    else
    {
        /* All other settings are treated as SERIAL_STOP_BIT_1(default). */
        converted_config |= _0010_SAU_STOP_1;
    }

    if(SERIAL_PARITY_EVEN == (SERIAL_PARITY_MASK & config))
    {
        converted_config |= _0200_SAU_PARITY_EVEN;
    }
    else if(SERIAL_PARITY_ODD == (SERIAL_PARITY_MASK & config))
    {
        converted_config |= _0300_SAU_PARITY_ODD;
    }
    else
    {
        /* All other settings are treated as SERIAL_PARITY_NONE(default). */
        converted_config |= _0000_SAU_PARITY_NONE;
    }

    switch (_urt_channel)
    {
        /* Rewriting prohibited when SEmn = 1 / Set_Config is called between R_Config_UART0_Create () and R_Config_UART0_Start (), so SEmn = 0*/
        case 0:
        {
        /* SCR00 16bit*/
#if ( UART_CHANNEL == 0 )
        unsigned short SCR00data=_8000_SAU_TRANSMISSION |_0000_SAU_INTSRE_MASK |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB | converted_config;
        /* When sending, _0000_SAU_INTSRE_MASK :EOCmn = 0*/
        unsigned short SCR01data=_4000_SAU_RECEPTION |_0400_SAU_INTSRE_ENABLE |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB | converted_config;
        /* _0400_SAU_INTSRE_ENABLE: EOCmn = 1 Allow the occurrence of the error interrupt INTSREx */

        /* SLCmn1: 0 SLCmn0: 1 when receiving XXXXXXXXXX01XXXX*/
        SCR01data &= ~(_0020_SAU_STOP_2);
        SCR01data |= _0010_SAU_STOP_1;

        SCR00 = SCR00data;
        SCR01 = SCR01data;
#endif /* ( UART_CHANNEL == 0 ) */
        }
        break;

        case 1:
        {
#if ( UART1_CHANNEL == 1 )
        unsigned short SCR02data=_8000_SAU_TRANSMISSION| _0000_SAU_INTSRE_MASK |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB |converted_config;
        unsigned short SCR03data=_4000_SAU_RECEPTION| _0400_SAU_INTSRE_ENABLE |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB |converted_config;
        /* SLCmn1: 0 SLCmn0: 1 when receiving XXXXXXXXXX01XXXX*/
        SCR03data &= ~(_0020_SAU_STOP_2);
        SCR03data |= _0010_SAU_STOP_1;

        SCR02 = SCR02data;
        SCR03 = SCR03data;
#endif /* ( UART1_CHANNEL == 1 ) */
        }
        break;
        case 2:
        {
#if ( UART2_CHANNEL == 2 )
            unsigned short SCR10data=_8000_SAU_TRANSMISSION| _0000_SAU_INTSRE_MASK |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB |converted_config;
            unsigned short SCR11data=_4000_SAU_RECEPTION| _0400_SAU_INTSRE_ENABLE |_0004_SAU_SCRMN_INITIALVALUE |_0080_SAU_LSB |converted_config;
            /* SLCmn1: 0 SLCmn0: 1 when receiving XXXXXXXXXX01XXXX*/
            SCR11data &= ~(_0020_SAU_STOP_2);
            SCR11data |= _0010_SAU_STOP_1;
            SCR10 = SCR10data;
            SCR11 = SCR11data;
#endif /* ( UART2_CHANNEL == 2 ) */
        }
        break;
        case 3:
        {

        }
        break;
    }
}
/**********************************************************************************************************************
 End of function Set_Config
 *********************************************************************************************************************/
#endif /* __RL78__ */

/**********************************************************************************************************************
 * Function Name: HardwareUart::Set_SerialPort
 * Description  : Set serial port pins for the target port.
 * Arguments    : txd_pin - transmit pin no.
 *              : rxd_pin - receive  pin no.
 * Return Value : void
 *********************************************************************************************************************/
void HardwareUart::Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin)
{
    //PinTableType* p;
    //PinTableType pin_tbl;
    //p = (PinTableType*)&pin_tbl;


    const PinTableType ** pp;
    PinTableType * p;

    /* Set RxD pin */
    //getPinTable(rxd_pin,p);
    pp = &pinTablelist[rxd_pin];
    p = (PinTableType *)*pp;
    /* Set PM Register for Input */
    *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);

#if defined(G22_FPB) || defined(G23_FPB)
    /* Set PMCA Register */
    if (0!=p->pmca){
      *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
    }
#endif // defined(G22_FPB) || defined(G23_FPB)

    /* Set PMCT Register */
#if defined(G22_FPB) || defined(G23_FPB)
    if (0!=p->pmct){
      *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }
#endif // defined(G22_FPB) || defined(G23_FPB)

    /* Set PMCE Register for Output */
#if defined(G23_FPB)
    if (0!=p->pmce){
      *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }
#endif // G23_FPB
    /* Set CCDE Register for Digital InOut */
#if defined(G23_FPB)
    if (0!=p->ccde){
      CCDE &= (uint8_t)~(p->ccde);
    }
#endif // G23_FPB
#if defined(G16_FPB)
    if (0!=p->pmc){
      *p->portModeControlRegisterAddr &= (unsigned long)~(p->pmc);
    }
#endif // defined(G16_FPB)

    /* Set TxD pin */
    //getPinTable(txd_pin,p);
    pp = &pinTablelist[txd_pin];
    p = (PinTableType *)*pp;
    /* Set PMCE Register t */
#if defined(G23_FPB)
    if (0!=p->pmce){
      *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }
#endif // G23_FPB

    /* Set P Register for Set "H" Output Port*/
    *p->portRegisterAddr |= (unsigned long)(0x1 << p->bit);

    /* Set PM Register for Output */
    *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);

    /* Set PMCA Register */
#if defined(G22_FPB) || defined(G23_FPB)
    if (0!=p->pmca){
      *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
    }
#endif // defined(G22_FPB) || defined(G23_FPB)

    /* Set PMCT Register */
#if defined(G22_FPB) || defined(G23_FPB)
    if (0!=p->pmct){
      *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }
#endif // defined(G22_FPB) || defined(G23_FPB)

    /* Set PMCE Register t */
#if defined(G23_FPB)
    if (0!=p->pmce){
      *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }
#endif // G23_FPB
    /* Set CCDE Register for Digital InOut */
#if defined(G23_FPB)
    if (0!=p->ccde){
      CCDE &= (uint8_t)~(p->ccde);
    }
#endif // G23_FPB

#if defined(G16_FPB)
    if (0!=p->pmc){
      *p->portModeControlRegisterAddr &= (unsigned long)~(p->pmc);
    }
#endif // G16_FPB
}

void HardwareUart::setReceiveCallback(void (*userFunc)(void))
{
    uart_receive_callback_table[_urt_channel] = userFunc;
}
void HardwareUart::setTransmitCallback(void (*userFunc)(void))
{
    uart_transmit_callback_table[_urt_channel] = userFunc;
}

extern "C" {
/**********************************************************************************************************************
 * Function Name: Set_Char_Serial_to_buf
 * Description  : Store the received data in the buffer.
 *              : Called from the receive interrupt handler.
 * Arguments    : chn - UART channel
 * Return Value : void
 *********************************************************************************************************************/
void Set_Char_Serial_to_buf(uint8_t chn)
{
    switch (chn)
    {
        case 0:
#if (UART_CHANNEL == 0)
            Serial.store_char();
#endif /* (UART_CHANNEL == 0) */
            break;
        case 1:
#if (UART1_CHANNEL == 1)
            Serial1.store_char();
#endif /* (UART1_CHANNEL == 1) */
            break;
        case 2:
#if (UART2_CHANNEL == 2)
            Serial2.store_char();
#endif /* (UART2_CHANNEL == 2) */
            break;
        case 3:
            break;
    }
}

/**********************************************************************************************************************
 * Function Name: Set_Char_Serial_from_buf
 * Description  : Load write data from the buffer.
 * Arguments    : chn  - UART_CHANNEL
 * Return Value : void         -
 *********************************************************************************************************************/

void Set_Char_Serial_from_buf(uint8_t chn)
{
    switch (chn)
    {
        case 0:
#if (UART_CHANNEL == 0)
            Serial.load_char();
#endif /* (UART_CHANNEL == 0) */
            break;
        case 1:
#if (UART1_CHANNEL == 1)
            Serial1.load_char();
#endif /* (UART1_CHANNEL == 1) */
            break;
        case 2:
#if (UART2_CHANNEL == 2)
            Serial2.load_char();
#endif /* (UART2_CHANNEL == 2) */
            break;
        case 3:
            break;
    }
}

}

// Preinstantiate Objects //////////////////////////////////////////////////////

#if ( UART_CHANNEL == 0 )
  HardwareUart Serial(0);
#endif /* ( UART_CHANNEL == 0 ) */
#if ( UART1_CHANNEL == 1 )
    HardwareUart Serial1(1);
#endif /* ( UART1_CHANNEL == 1 ) */
#if ( UART2_CHANNEL == 2 )
    HardwareUart Serial2(2);
#endif /* ( UART2_CHANNEL == 2 ) */


