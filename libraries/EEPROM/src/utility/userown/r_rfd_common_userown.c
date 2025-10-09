/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_common_userown.c
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Common Flash Control userown program
**********************************************************************************************************************/

/**********************************************************************************************************************
    DISCLAIMER
    This software is supplied by Renesas Electronics Corporation and is only intended for use with
    Renesas products. No other uses are authorized. This software is owned by Renesas Electronics
    Corporation and is protected under all applicable laws, including copyright laws.
    THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
    TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR
    ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
    Renesas reserves the right, without notice, to make changes to this software and to discontinue the
    availability of this software. By using this software, you agree to the additional terms and conditions
    found by accessing the following link:
    http://www.renesas.com/disclaimer
    
    Copyright (C) 2020-2023 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "../include/r_rfd_common_userown.h"

#if (COMPILER_IAR == COMPILER)
    #include "intrinsics.h"
#endif

/**********************************************************************************************************************
 Static global variables
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_DATA
#include "../include/rfd/r_rfd_memmap.h"
    /* State enabled/disabled interrupts in PSW */
    static uint8_t sg_u08_psw_ie_state = R_RFD_VALUE_U08_INIT_VARIABLE;
#define  R_RFD_END_SECTION_RFD_DATA
#include "../include/rfd/r_rfd_memmap.h"

/**********************************************************************************************************************
 * Function name : R_RFD_HOOK_EnterCriticalSection
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Perform processing to enter critical section.
 *  Store the current state enabled/disabled interrupts and disable interrupts.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_HOOK_EnterCriticalSection(void)
{
    sg_u08_psw_ie_state = R_RFD_GET_PSW_IE_STATE();
    
    /* Disable interrupts */
    R_RFD_DISABLE_INTERRUPT();
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_HOOK_EnterCriticalSection
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_HOOK_ExitCriticalSection
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Perform processing to exit critical section.
 *  Restore the state enabled/disabled interrupts.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_HOOK_ExitCriticalSection(void)
{
    if (R_RFD_IS_PSW_IE_ENABLE(sg_u08_psw_ie_state))
    {
        /* Enable interrupts */
        R_RFD_ENABLE_INTERRUPT();
    }
    else
    {
        /* Keep state disabled interrupts */
        /* No operation */
    }
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_HOOK_ExitCriticalSection
 *********************************************************************************************************************/
