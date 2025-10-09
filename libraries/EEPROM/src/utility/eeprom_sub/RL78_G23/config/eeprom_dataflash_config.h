/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD RL78 Type01) (Data Flash)
    
    File Name       : sample_dataflash_config.h
    Program Version : V1.20.00
    Device(s)       : RL78/G23 microcontroller
    Description     : Sample user configurable parameters file
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
    
    Copyright (C) 2021-2024 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

#ifndef SAMPLE_DATAFLASH_CONFIG_H
#define SAMPLE_DATAFLASH_CONFIG_H

/**********************************************************************************************************************
  User configurable parameters
**********************************************************************************************************************/
/**** The calculation parameter for the CPU clock frequency inputted into a flash sequencer. ****/
#define L_MCLK_FREQ_1MHz  (1000000uL)
#define L_MCLK_ROUNDUP_VALUE (999999uL)

/**** Address to write ****/

/* It should be the head address of the flash block. */

// #define DF_WRITE_ADDRESS     (0x000F1000uL)

/**** Data length to write ****/
/* Don't across the boundary of the flash block. */

#define DF_WRITE_DATA_LENGTH_1 (1u)

#endif /* end of SAMPLE_DATAFLASH_CONFIG_H */
