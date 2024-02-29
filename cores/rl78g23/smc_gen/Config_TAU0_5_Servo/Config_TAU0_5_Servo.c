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
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_TAU0_5_Servo.c
* Component Version: 1.4.0
* Device(s)        : R7F100GLGxFB
* Description      : This file implements device driver for Config_TAU0_5_Servo.
* Creation Date    : 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_TAU0_5_Servo.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_5_Servo_Create
* Description  : This function initializes the TAU0 channel 5 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_5_Servo_Create(void)
{
    TPS0 &= _FF0F_TAU_CKM1_CLEAR;
    TPS0 |= _0050_TAU_CKM1_FCLK_5;
    /* Stop channel 5 */
    TT0 |= _0020_TAU_CH5_STOP_TRG_ON;
    /* Mask channel 5 interrupt */
    TMMK05 = 1U;    /* disable INTTM05 interrupt */
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
    /* Set INTTM05 low priority */
    TMPR105 = 1U;
    TMPR005 = 1U;
    /* TAU05 used as interval timer */
    TMR05 = _8000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_TRIGGER_SOFTWARE | 
            _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR05 = _4E1F_TAU_TDR05_VALUE;
    TOM0 &= (uint16_t)~_0020_TAU_CH5_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_ENABLE;
    
    R_Config_TAU0_5_Servo_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_5_Servo_Start
* Description  : This function starts the TAU0 channel 5 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_5_Servo_Start(void)
{
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
    TMMK05 = 0U;    /* enable INTTM05 interrupt */
    TS0 |= _0020_TAU_CH5_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_5_Servo_Stop
* Description  : This function stops the TAU0 channel 5 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_5_Servo_Stop(void)
{
    TT0 |= _0020_TAU_CH5_STOP_TRG_ON;
    /* Mask channel 5 interrupt */
    TMMK05 = 1U;    /* disable INTTM05 interrupt */
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
