/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_typedefs.h
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Renesas standard types definitions
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

#ifndef R_TYPEDEFS_H
#define R_TYPEDEFS_H

/*********************************************************************************************************************
 * standard types definitions
 *********************************************************************************************************************/

/* Compilers must have __STDC_VERSION__ due to requirement in language standard */
#if ((defined __STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#include <stdint.h>
#include <stdbool.h>
#else
typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef signed short       int16_t;
typedef unsigned short     uint16_t;
typedef signed long        int32_t;
typedef unsigned long      uint32_t;
typedef unsigned char      rBool_t;

#define bool               rBool_t
#define false              (0)
#define true               (1)

// #define INT8_MIN           (-128)
// #define INT16_MIN          (-32768)
// #define INT32_MIN          (-2147483647 - 1)

// #define INT8_MAX           (127)
// #define INT16_MAX          (32767)
// #define INT32_MAX          (2147483647)

// #define UINT8_MAX          (255u)
// #define UINT16_MAX         (65535u)
// #define UINT32_MAX         (4294967295u)

#endif    /* ((defined __STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) */
#endif    /* #ifndef R_TYPEDEFS_H   */
