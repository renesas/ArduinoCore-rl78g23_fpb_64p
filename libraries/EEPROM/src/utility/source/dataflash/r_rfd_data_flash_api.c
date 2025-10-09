/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_data_flash_api.c
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Data Flash Control program
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
#include "../../include/r_rfd_data_flash_api.h"

/**********************************************************************************************************************
 * Function name : R_RFD_EraseDataFlashReq
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  This command starts the code/data flash memory sequencer.
 *  Start the code/data flash memory sequencer and erase the specified block in the data flash memory.
 *  
 *  @param[in]      i_u08_block_number : 
 *                    Erase block number
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_EraseDataFlashReq(uint8_t i_u08_block_number)
{
    /* Local variable definitions */
    uint16_t l_u16_low_addr;
    uint8_t  l_u08_high_addr;
    
    /* Calculate and set local variables */
    /* This expression (actual 16-bit address) never exceeds the range of casting uint16_t */
    l_u16_low_addr  = R_RFD_VALUE_U16_DATA_FLASH_ADDR_LOW 
                      + (((uint16_t)i_u08_block_number) << R_RFD_VALUE_U08_DATA_FLASH_SHIFT_LOW_ADDR);
    l_u08_high_addr = R_RFD_VALUE_U08_DATA_FLASH_ADDR_HIGH;
    
    /* Set the value for FLARS register */
    R_RFD_REG_U08_FLARS = R_RFD_VALUE_U08_FLARS_USER_AREA;
    
    /* Set the value for FLAPH/L register */
    R_RFD_REG_U16_FLAPL = l_u16_low_addr;
    R_RFD_REG_U08_FLAPH = l_u08_high_addr;
    
    /* Set the value for FLSEDH/L register */
    R_RFD_REG_U16_FLSEDL = l_u16_low_addr | R_RFD_VALUE_U16_DATA_FLASH_BLOCK_ADDR_END;
    R_RFD_REG_U08_FLSEDH = l_u08_high_addr;
    
    /* Set the value for FSSQ register */
    R_RFD_REG_U08_FSSQ = R_RFD_VALUE_U08_FSSQ_ERASE;
}

#define  R_RFD_END_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_EraseDataFlashReq
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_WriteDataFlashReq
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  This command starts the code/data flash memory sequencer.
 *  Start the code/data flash memory sequencer and write the data (1 byte) to the specified address 
 *  in the data flash memory.
 *  
 *  @param[in]      i_u32_start_addr : 
 *                    Write start address
 *  @param[in]      inp_u08_write_data : 
 *                    Write data pointer
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_WriteDataFlashReq(uint32_t i_u32_start_addr, 
                                            uint8_t __near * inp_u08_write_data)
{
    /* Local variable definitions */
    
    /* Set the value for FLARS register */
    R_RFD_REG_U08_FLARS = R_RFD_VALUE_U08_FLARS_USER_AREA;
    
    /* Set the value for FLAPH/L register */
    R_RFD_REG_U16_FLAPL = (uint16_t)(i_u32_start_addr & R_RFD_VALUE_U16_MASK1_16BIT);
    R_RFD_REG_U08_FLAPH = (uint8_t)((i_u32_start_addr >> R_RFD_VALUE_U08_SHIFT_16BIT) & R_RFD_VALUE_U08_MASK1_8BIT);
    
    /* Set the value for FLWL register */
    R_RFD_REG_U16_FLWL = (uint16_t)(* inp_u08_write_data);
    
    /* Set the value for FSSQ register */
    R_RFD_REG_U08_FSSQ = R_RFD_VALUE_U08_FSSQ_WRITE;
}

#define  R_RFD_END_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_WriteDataFlashReq
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function name : R_RFD_BlankCheckDataFlashReq
 *********************************************************************************************************************/
#define  R_RFD_START_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/*********************************************************************************************************************/
/**
 *  This command starts the code/data flash memory sequencer.
 *  Start the code/data flash memory sequencer and start blankcheck the specified address and length
 *  in the data flash memory.
 *  
 *  @param[in]      i_u32_start_addr :
 *                    Blankcheck start address
 *  @param[in]      i_u16_blankcheck_length :
 *                    Blankcheck length (greater than zero)
 *  @return         ---
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC void R_RFD_BlankCheckDataFlashReq(uint32_t i_u32_start_addr,
                                                 uint16_t i_u16_blankcheck_length)
{
    /* Local variable definitions */
    uint32_t l_u32_end_addr;
    
    /* Calculate and set local variables */
    l_u32_end_addr = (i_u32_start_addr + (uint32_t)i_u16_blankcheck_length) - 1u;
    
    /* Set the value for FLARS register */
    R_RFD_REG_U08_FLARS = R_RFD_VALUE_U08_FLARS_USER_AREA;
    
    /* Set the value for FLAPH/L register */
    R_RFD_REG_U16_FLAPL = (uint16_t)(i_u32_start_addr & R_RFD_VALUE_U16_MASK1_16BIT);
    R_RFD_REG_U08_FLAPH = (uint8_t)((i_u32_start_addr >> R_RFD_VALUE_U08_SHIFT_16BIT) & R_RFD_VALUE_U08_MASK1_8BIT);
    
    /* Set the value for FLSEDH/L register */
    R_RFD_REG_U16_FLSEDL = (uint16_t)(l_u32_end_addr & R_RFD_VALUE_U16_MASK1_16BIT);
    R_RFD_REG_U08_FLSEDH = (uint8_t)((l_u32_end_addr >> R_RFD_VALUE_U08_SHIFT_16BIT) & R_RFD_VALUE_U08_MASK1_8BIT);
    
    /* Set the value for FSSQ register */
    R_RFD_REG_U08_FSSQ = R_RFD_VALUE_U08_FSSQ_BLANKCHECK_DF;
}

#define  R_RFD_END_SECTION_RFD_DF
#include "../../include/rfd/r_rfd_memmap.h"
/**********************************************************************************************************************
 End of function R_RFD_BlankCheckDataFlashReq
 *********************************************************************************************************************/
