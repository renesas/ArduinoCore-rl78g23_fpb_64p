/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD RL78 Type01) (Common)
    
    File Name       : sample_control_common.c
    Program Version : V1.20.00
    Device(s)       : RL78/G2x microcontroller
    Description     : Sample program for common flash control
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
#include "../include/eeprom_types.h"
#include "../include/eeprom_control_common.h"
#include "../include/eeprom_defines.h"
#include "../../include/r_rfd_common_control_api.h"

/**********************************************************************************************************************
 * Function name : Sample_CheckCFDFSeqEnd
 *********************************************************************************************************************/
#define  SAMPLE_START_SECTION_SMP_CMN
#include "../include/eeprom_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check the state of the code/data flash memory sequencer and result.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK             : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER : CF/DF sequencer error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_ERASE      : Erase action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_WRITE      : Write action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK : Blankcheck action error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_eeprom_ret_t Eeprom_CheckCFDFSeqEnd(void)
{
    /* Local variable definition */
	e_eeprom_ret_t l_e_sam_ret_value;
    uint8_t        l_u08_status_flag;
    
    /* Set local variables */
    l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    
    /* Sequencer busy loop step1 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep1())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Sequencer busy loop step2 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep2())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Action error check */
    R_RFD_GetSeqErrorStatus(&l_u08_status_flag);
    
    /* Check error status */
    if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_CFDF_SEQUENCER))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_ERASE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_ERASE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_WRITE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_WRITE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_BLANKCHECK))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK;
    }
    else
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    }
    
    /* Clear sequencer registers */
    R_RFD_ClearSeqRegister();
    
    return (l_e_sam_ret_value);
}

#define  SAMPLE_END_SECTION_SMP_CMN
#include "../include/eeprom_memmap.h"
/**********************************************************************************************************************
 End of function Sample_CheckCFDFSeqEnd
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : Sample_CheckExtraSeqEnd
 *********************************************************************************************************************/
#define  SAMPLE_START_SECTION_SMP_CMN
#include "../include/eeprom_memmap.h"
/*********************************************************************************************************************/
/**
 *  Check the state of the extra area sequencer and result.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK              : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_EXTRA_SEQUENCER : Extra area sequencer error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_ERASE       : Erase action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_WRITE       : Write action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK  : Blankcheck action error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_eeprom_ret_t Eeprom_CheckExtraSeqEnd(void)
{
    /* Local variable definition */
	e_eeprom_ret_t l_e_sam_ret_value;
    uint8_t        l_u08_status_flag;
    
    /* Set local variables */
    l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    
    /* Sequencer busy loop step1 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckExtraSeqEndStep1())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Sequencer busy loop step2 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckExtraSeqEndStep2())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Action error check */
    R_RFD_GetSeqErrorStatus(&l_u08_status_flag);
    
    /* Check error status */
    if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_EXTRA_SEQUENCER))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_EXTRA_SEQUENCER;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_ERASE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_ERASE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_WRITE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_WRITE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_BLANKCHECK))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK;
    }
    else
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    }
    
    /* Clear sequencer registers */
    R_RFD_ClearSeqRegister();
    
    return (l_e_sam_ret_value);
}

#define  SAMPLE_END_SECTION_SMP_CMN
#include "../include/eeprom_memmap.h"
/**********************************************************************************************************************
 End of function Sample_CheckExtraSeqEnd
 *********************************************************************************************************************/
