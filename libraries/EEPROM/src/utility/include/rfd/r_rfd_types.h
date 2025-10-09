/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_types.h
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Type definitions header file
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

#ifndef R_RFD_TYPES_H
#define R_RFD_TYPES_H

/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/

/**
 * @struct bitf08_rfd_t
 * RFD bit field definition
 */
typedef struct bitf08_rfd
{
    unsigned char no0:1;
    unsigned char no1:1;
    unsigned char no2:1;
    unsigned char no3:1;
    unsigned char no4:1;
    unsigned char no5:1;
    unsigned char no6:1;
    unsigned char no7:1;
} bitf08_rfd_t;

/**
 * @enum e_rfd_flash_memory_mode_t
 * RFD flash mode definition
 */
typedef enum e_rfd_flash_memory_mode
{
    R_RFD_ENUM_FLASH_MODE_UNPROGRAMMABLE   = 0x00u,
    R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING = 0x01u,
    R_RFD_ENUM_FLASH_MODE_DATA_PROGRAMMING = 0x02u
} e_rfd_flash_memory_mode_t;

/**
 * @enum e_rfd_df_access_t
 * RFD data flash access control
 */
typedef enum e_rfd_df_access
{
    R_RFD_ENUM_DF_ACCESS_DISABLE = 0x00u,
    R_RFD_ENUM_DF_ACCESS_ENABLE  = 0x01u
} e_rfd_df_access_t;

/**
 * @enum e_rfd_boot_cluster_t
 * Boot cluster
 */
typedef enum e_rfd_boot_cluster
{
    R_RFD_ENUM_BOOT_CLUSTER_1 = 0x00u,
    R_RFD_ENUM_BOOT_CLUSTER_0 = 0x01u
} e_rfd_boot_cluster_t;

/**
 * @enum e_rfd_fsw_mode_t
 * Flash shield window mode
 */
typedef enum e_rfd_fsw_mode
{
    R_RFD_ENUM_FSW_MODE_INSIDE  = 0x00u,
    R_RFD_ENUM_FSW_MODE_OUTSIDE = 0x01u
} e_rfd_fsw_mode_t;

/**
 * @enum e_rfd_protect_t
 * Protect control
 */
typedef enum e_rfd_protect
{
    R_RFD_ENUM_PROTECT_ON  = 0x00u,
    R_RFD_ENUM_PROTECT_OFF = 0x01u
} e_rfd_protect_t;

/**
 * @enum e_rfd_ret_t
 * RFD operation status definition
 */
typedef enum e_rfd_ret
{
    R_RFD_ENUM_RET_STS_OK              = 0x00u,
    R_RFD_ENUM_RET_STS_BUSY            = 0x01u,
    R_RFD_ENUM_RET_ERR_PARAMETER       = 0x10u,
    R_RFD_ENUM_RET_ERR_MODE_MISMATCHED = 0x11u
} e_rfd_ret_t;

#endif /* end of R_RFD_TYPES_H */
