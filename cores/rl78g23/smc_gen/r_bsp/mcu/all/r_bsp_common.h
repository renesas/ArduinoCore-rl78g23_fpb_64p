/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_common.h
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.03.2021 1.00     First Release
*         : 22.04.2021 1.10     Changed Minor version to 1.10
*         : 04.08.2021 1.12     Added include r_bsp_config.h.
*         : 29.10.2021 1.13     Added version check of smart configurator.
*         : 28.02.2022 1.20     Added PLLCLK,ADCLK to e_clock_mode_t.
*                               Added the following function.
*                                - R_BSP_ChangeClockSetting
*                               Changed to enable/disable for each API function.
*                               Changed the version of smart configurator to check to 1030.
*                               Changed to always determine the version of smart configurator.
*         : 31.05.2022 1.30     Added the following enumerated variable.
*                                - e_bsp_delay_units_t
*                               Added prototype of the following function
*                                - R_BSP_SoftwareDelay
***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include    <stdint.h>
#include    <stdbool.h>
#include    <stdio.h>
#include    <stddef.h>
#include    "r_bsp_config.h"

/*************************************************
 * Macro definitions
 *************************************************/
/* Multiple inclusion prevention macro */
#ifndef R_BSP_COMMON_H
#define R_BSP_COMMON_H

#if BSP_CFG_CONFIGURATOR_VERSION < 1030
#error "Make sure that the value of BSP_CFG_CONFIGURATOR_VERSION defined in r_config/r_bsp_config.h matches the version of Smart Configurator you are using. If they do not match, change the settings. If they match, you need to upgrade your Smart Configurator. Please upgrade Smart Configurator."
#endif

/* Interrupt disable/enable(assembler instruction) */
#define BSP_DI()            __DI()                      /* Interrupt disable */
#define BSP_EI()            __EI()                      /* Interrupt enable */

/* clock mode */
/* NOTE: 
 * n = this clock may not be available depending on the number of terminals. 
 * RL78 MCU supported clocks
 *
 * Clock  G23 F24 F23 G15
 * ------ --- --- --- ---
 * HIOCLK  X   X   X   X
 * SYSCLK  X   X   X   Xn
 * SXCLK   X   Xn  Xn
 * MIOCLK  X
 * LOCLK   X   X   X
 * PLLCLK      X   X
 * ADCLK       X   X
*/
typedef enum
{
    HIOCLK,     // High-speed on-chip oscillator
    SYSCLK,     // High-speed system clock
    SXCLK,      // Subsystem clock
    MIOCLK,     // Middle-speed on-chip oscillator
    LOCLK,      // Low-speed on-chip oscillator
    PLLCLK,     // PLL clock
    ADCLK       // A/D conversion clock
} e_clock_mode_t;

/* Error identification */
typedef enum
{
    BSP_OK,
    BSP_ARG_ERROR,
    BSP_ERROR1,
    BSP_ERROR2,
    BSP_ERROR3
} e_bsp_err_t;

/* Available delay units. */
typedef enum
{
    BSP_DELAY_SECS = 0,     /* Requested delay amount is in seconds. */
    BSP_DELAY_MILLISECS,    /* Requested delay amount is in milliseconds. */
    BSP_DELAY_MICROSECS     /* Requested delay amount is in microseconds. */
} e_bsp_delay_units_t;

/*************************************************
 * Function declaration
 *************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_StartClock (e_clock_mode_t mode);
e_bsp_err_t R_BSP_StopClock (e_clock_mode_t mode);
#endif

#if BSP_CFG_GET_FREQ_API_FUNCTIONS_DISABLE == 0
uint32_t R_BSP_GetFclkFreqHz (void);
#endif

#if BSP_CFG_SET_CLOCK_SOURCE_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_SetClockSource (e_clock_mode_t mode);
#endif

#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_ChangeClockSetting (e_clock_mode_t mode, uint8_t * set_values);
#endif

#if BSP_CFG_SOFTWARE_DELAY_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_SoftwareDelay (uint32_t delay, e_bsp_delay_units_t units);
#endif

#endif /* #define R_BSP_COMMON_H */

