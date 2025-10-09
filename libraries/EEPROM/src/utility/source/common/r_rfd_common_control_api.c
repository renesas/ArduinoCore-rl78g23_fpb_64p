/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_common_control_api.c
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Common Flash Control program
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
#include "../../include/r_rfd_common_control_api.h"

#if (COMPILER_IAR == COMPILER)
    #include "intrinsics.h"
#endif

/**********************************************************************************************************************
 * Function name : R_RFD_CheckCFDFSeqEndStep1
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check whether the operation of the activated code/data flash memory sequencer has been completed.
 *  If completed, then clear the control register for code/data flash memory sequencer.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - R_RFD_ENUM_RET_STS_OK :   The operation of the code/data flash memory sequencer is completed
 *                  - R_RFD_ENUM_RET_STS_BUSY : The code/data flash memory sequencer is still being processed
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep1(void)
{
    /* Local variable definitions */
    e_rfd_ret_t l_e_ret_value;
    uint8_t     l_u08_fsasth_value;
    
    /* Set local variables */
    l_e_ret_value      = R_RFD_ENUM_RET_STS_OK;
    l_u08_fsasth_value = R_RFD_REG_U08_FSASTH;
    
    /* SQEND bit is valid */
    if (0u != (l_u08_fsasth_value & R_RFD_VALUE_U08_MASK1_FSASTH_SQEND))
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_OK;
        
        /* Set the value for FSSQ register */
        R_RFD_REG_U08_FSSQ = R_RFD_VALUE_U08_FSSQ_CLEAR;
    }
    /* SQEND bit is invalid */
    else
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_BUSY;
    }
    
    return (l_e_ret_value);
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_CheckCFDFSeqEndStep1
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_CheckExtraSeqEndStep1
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check whether the operation of the activated extra sequencer has been completed.
 *  If completed, then clear the control register for the extra sequencer.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - R_RFD_ENUM_RET_STS_OK :   The operation of the extra sequencer is completed
 *                  - R_RFD_ENUM_RET_STS_BUSY : The extra sequencer is still being processed
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckExtraSeqEndStep1(void)
{
    /* Local variable definitions */
    e_rfd_ret_t l_e_ret_value;
    uint8_t     l_u08_fsasth_value;
    
    /* Set local variables */
    l_e_ret_value      = R_RFD_ENUM_RET_STS_OK;
    l_u08_fsasth_value = R_RFD_REG_U08_FSASTH;
    
    /* ESQEND bit is valid */
    if (0u != (l_u08_fsasth_value & R_RFD_VALUE_U08_MASK1_FSASTH_ESQEND))
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_OK;
        
        /* Set the value for FSSE register */
        R_RFD_REG_U08_FSSE = R_RFD_VALUE_U08_FSSE_CLEAR;
    }
    /* ESQEND bit is invalid */
    else
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_BUSY;
    }
    
    return (l_e_ret_value);
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_CheckExtraSeqEndStep1
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_CheckCFDFSeqEndStep2
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check whether the code/data flash memory sequencer command has been completed 
 *  by clearing the control register for the code/data flash memory sequencer.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - R_RFD_ENUM_RET_STS_OK :   The command of code/data flash memory sequencer is completed
 *                  - R_RFD_ENUM_RET_STS_BUSY : The command is still being processed
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep2(void)
{
    /* Local variable definitions */
    e_rfd_ret_t l_e_ret_value;
    uint8_t     l_u08_fsasth_value;
    
    /* Set local variables */
    l_e_ret_value      = R_RFD_ENUM_RET_STS_OK;
    l_u08_fsasth_value = R_RFD_REG_U08_FSASTH;
    
    /* SQEND bit is invalid */
    if (0u == (l_u08_fsasth_value & R_RFD_VALUE_U08_MASK1_FSASTH_SQEND))
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_OK;
    }
    /* SQEND bit is valid */
    else
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_BUSY;
    }
    
    return (l_e_ret_value);
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_CheckCFDFSeqEndStep2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_CheckExtraSeqEndStep2
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check whether the extra sequencer command has been completed 
 *  by clearing the control register for the extra sequencer.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - R_RFD_ENUM_RET_STS_OK :   The command of extra sequencer is completed
 *                  - R_RFD_ENUM_RET_STS_BUSY : The command is still being processed
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckExtraSeqEndStep2(void)
{
    /* Local variable definitions */
    e_rfd_ret_t l_e_ret_value;
    uint8_t     l_u08_fsasth_value;
    
    /* Set local variables */
    l_e_ret_value      = R_RFD_ENUM_RET_STS_OK;
    l_u08_fsasth_value = R_RFD_REG_U08_FSASTH;
    
    /* ESQEND bit is invalid */
    if (0u == (l_u08_fsasth_value & R_RFD_VALUE_U08_MASK1_FSASTH_ESQEND))
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_OK;
    }
    /* ESQEND bit is valid */
    else
    {
        /* Set return value */
        l_e_ret_value = R_RFD_ENUM_RET_STS_BUSY;
    }
    
    return (l_e_ret_value);
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_CheckExtraSeqEndStep2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_GetSeqErrorStatus
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Get the error information occurred by the code/data flash memory sequencer command or the extra sequencer command.
 *  
 *  @param[out]     onp_u08_error_status : 
 *                    Pointer to the variable that stores error information
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_GetSeqErrorStatus(uint8_t __near * onp_u08_error_status)
{
    /* Local variable definitions */
    uint8_t l_u08_fsastl_value;
    
    /* Set local variables */
    l_u08_fsastl_value = R_RFD_REG_U08_FSASTL;
    
    /* Write to parameter */
    * onp_u08_error_status = l_u08_fsastl_value & R_RFD_VALUE_U08_MASK1_FSASTL_ERROR_FLAG;
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_GetSeqErrorStatus
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_ClearSeqRegister
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Clear the registers that control the code/data flash memory sequencer and extra sequencer.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_ClearSeqRegister(void)
{
    /* Local variable definitions */
    
    /* Set the value for FLRST register */
    R_RFD_REG_U08_FLRST = R_RFD_VALUE_U08_FLRST_ON;
    
    /* Wait one clock */
    R_RFD_NO_OPERATION();
    
    /* Set the value for FLRST register */
    R_RFD_REG_U08_FLRST = R_RFD_VALUE_U08_FLRST_OFF;
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_ClearSeqRegister
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_ForceStopSeq
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  Stop the code/data flash memory sequencer operation forcibly.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_ForceStopSeq(void)
{
    /* Local variable definitions */
    
    /* Set the value for FSSQ register FSSTP bit */
    R_RFD_REG_U01_FSSQ_FSSTP = R_RFD_VALUE_U01_FSSQ_FSSTP_ON;
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_ForceStopSeq
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_ForceReset
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"

#if (COMPILER_CC == COMPILER)
    #pragma inline_asm R_RFD_ForceReset
#endif
/*********************************************************************************************************************/
/**
 *  Reset the CPU.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_ForceReset(void)
{
    /* Set illegal instruction to request internal reset */
    #if (COMPILER_CC == COMPILER)
    .DB 255
    #elif (COMPILER_IAR == COMPILER)
    __asm("DC8 0xFF");
    #elif (COMPILER_LLVM == COMPILER)
    __asm(".byte 0xFF");
    #endif
}

#define  R_RFD_END_SECTION_RFD_CMN
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_ForceReset
 *********************************************************************************************************************/
