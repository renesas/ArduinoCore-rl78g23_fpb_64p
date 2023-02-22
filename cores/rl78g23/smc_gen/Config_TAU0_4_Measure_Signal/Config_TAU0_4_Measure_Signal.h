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
* Copyright (C) 2021, 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_TAU0_4_Measure_Signal.h
* Component Version: 1.2.0
* Device(s)        : R7F100GLGxFB
* Description      : This file implements device driver for Config_TAU0_4_Measure_Signal.
* Creation Date    : 
***********************************************************************************************************************/

#ifndef CFG_Config_TAU0_4_Measure_Signal_H
#define CFG_Config_TAU0_4_Measure_Signal_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_tau.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_TAU0_4_Measure_Signal_Create(void);
void R_Config_TAU0_4_Measure_Signal_Start(void);
void R_Config_TAU0_4_Measure_Signal_Stop(void);
void R_Config_TAU0_4_Measure_Signal_Get_PulseWidth(uint32_t * const width);
void R_Config_TAU0_4_Measure_Signal_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
void R_Config_TAU0_1_Servo_Stop(void);
void R_Config_TAU0_2_Servo_Stop(void);
void R_Config_TAU0_3_Servo_Stop(void);
void R_Config_TAU0_4_Servo_Stop(void);
void R_Config_TAU0_5_Servo_Stop(void);
void R_Config_TAU0_6_Servo_Stop(void);
void R_Config_TAU0_7_Servo_Stop(void);
/* End user code. Do not edit comment generated here */
#endif
