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
* File Name        : Config_Through.c    
* Component Version: 1.1.0
* Device(s)        : R7F100GLGxFB
* Description      : This module do the ELCL configuration to provide the Through.
* Creation Date    : 2023-04-14
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_Through.h"

/***********************************************************************************************************************
* Function Name: R_Config_Through_Create
* Description  : This function initializes the Config_Through.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_Through_Create(void)
{
    /* L1L0 Start */
    PFOE0&=0xFBU;
    ELISEL0=0x09U;
    ELL1SEL0=0x01U;
    ELL1LNK0=0x01U;
    PM5&=0xFDU;
    PMCE5|=0x02U;
    ELOSEL1=0x01U;
    /* L1L0 End */

    R_Config_Through_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_Through_Start
* Description  : This function starts the Config_Through.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_Through_Start(void)
{
    ELOENCTL|=0x02U;
}

/***********************************************************************************************************************
* Function Name: R_Config_Through_Stop
* Description  : This function stops the Config_Through.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_Through_Stop(void)
{
    ELOENCTL&=~0x02U;
}