/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

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
*/

#include <Arduino.h>
#include "utilities.h"
extern "C" {
    #include "r_smc_entry.h"
}

extern "C" {
//    #include "Config_ITL013.h"
}

/* This declaration is used to force the constant in
 * r_cg_vect_table.c to be linked to the static library (*.a). */
extern const unsigned char Option_Bytes[];
void * p_force_link = (void * )Option_Bytes;

int main(void)
{
/******************************************************/
    interrupts();                /* Enable Interrupt */
    _readResetFlag();           /* Read causes of reset */

/* Start Interval Timer */
    R_Config_ITL000_Create();    /* Create 1ms Interval Timer */
    R_Config_ITL000_Start();    /* Start 1ms Interval Timer */
    R_ITL_Start_Interrupt();    /* Start ITL Interrupt */

    R_Config_TAU0_6_Micros_Create();
    R_Config_TAU0_6_Micros_Start();

    /* Start RTC Timer */
//    R_Config_RTC_Start();    /*//KAD Start RTC Timer */

/* Power Off unused Peripheral */
/* SERIAL ARRAY UNIT (SAU) */
#if !defined(UART_CHANNEL) & (UART1_CHANNEL == 0) & !defined(CSI_CHANNEL)
    R_SAU0_Set_Reset();
    R_SAU0_Set_PowerOff();
#endif
#if !defined(UART1_CHANNEL) || UART1_CHANNEL == 0
    R_Config_UART1_Stop();
#endif
// 2023/03/02 temporary removal by KAD
// #if !defined(CSI_CHANNEL)
//    R_Config_CSI20_Stop();
// #endif
#if !defined(UART2_CHANNEL) || (UART2_CHANNEL == 0)
    R_SAU1_Set_Reset();
    R_SAU1_Set_PowerOff();
#endif

/* IICA UNIT(IICA*) */
#if !defined(IIC_CHANNEL0) | (IIC_CHANNEL0!=0)
    R_IICA0_Set_Reset();
    R_IICA0_Set_PowerOff();
#endif
#if (IIC_CHANNEL1!=1)
// 2023/02/28 comment out by KAD
//    R_IICA1_Set_Reset();
//    R_IICA1_Set_PowerOff();
#endif

/* RTC */
#if !defined(RTC_ON) | (RTC_ON!=0)
    R_RTC_Set_PowerOff();
#endif

#if WDT_EN==1
    R_Config_WDT_Start();
#endif

    setPowerManagementMode(PM_NORMAL_MODE);

    SOE0 &= 0xf3;
    SO0 |= 0x08;
// 2022/11/18 added by KAD for safety reason for G22, These pins are not available
#if defined(G22_FPB)
    /* P26,P25,P24,P23,P22 */
    PMCA2 &= 0x83;  /* 0 : Use Digital IO */
    PMCT2 &= 0x83;  /* 0 : Use Digital IO */
    PM2 &= 0x83;    /* 0 : Use Output Mode */
    P2 &= 0x83;     /* 0 : Use Output Low  */

    /* P30 */
    PMCT3 &= 0xFE;  /* 0 : Use Digital IO */
    PM3 &= 0xFE;    /* 0 : Use Output Mode */
    P3 &= 0xFE;     /* 0 : Use Output Low  */

#endif
/******************************************************/
    
    setup();
    
    for (;;) {
        loop();
// 2023/02/22
//        execCyclicHandler();

    }
    return 0;
}

/**
 * Finish Function
 *
 * RLduino78 Framework finish
 *  *
 * @return None
 *
 * @attention No return
 ***************************************************************************/
#include <stdlib.h>

void abort(void)
{
    for(;;);
}

void exit(int) __attribute__ ((weak, alias ("abort")));

#include <exception>

