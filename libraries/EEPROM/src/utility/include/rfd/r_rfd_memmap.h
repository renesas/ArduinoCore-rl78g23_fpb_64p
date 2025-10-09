/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_memmap.h
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Memory map header file
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

#include "r_rfd_compiler.h"

#if (COMPILER_CC == COMPILER)
    /* Section definition for Common Component */
    #if defined (R_RFD_START_SECTION_RFD_CMN)
        #undef  R_RFD_START_SECTION_RFD_CMN
        #pragma section text RFD_CMN
    #elif defined (R_RFD_END_SECTION_RFD_CMN)
        #undef  R_RFD_END_SECTION_RFD_CMN
        #pragma section
    /* Section definition for Code Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_CF)
        #undef  R_RFD_START_SECTION_RFD_CF
        #pragma section text RFD_CF
    #elif defined (R_RFD_END_SECTION_RFD_CF)
        #undef  R_RFD_END_SECTION_RFD_CF
        #pragma section
    /* Section definition for Data Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_DF)
        #undef  R_RFD_START_SECTION_RFD_DF
        #pragma section text RFD_DF
    #elif defined (R_RFD_END_SECTION_RFD_DF)
        #undef  R_RFD_END_SECTION_RFD_DF
        #pragma section
    /* Section definition for Extra Area Component */
    #elif defined (R_RFD_START_SECTION_RFD_EX)
        #undef  R_RFD_START_SECTION_RFD_EX
        #pragma section text RFD_EX
    #elif defined (R_RFD_END_SECTION_RFD_EX)
        #undef  R_RFD_END_SECTION_RFD_EX
        #pragma section
    /* Section definition for Global Data for Common Component */
    #elif defined (R_RFD_START_SECTION_RFD_DATA)
        #undef  R_RFD_START_SECTION_RFD_DATA
        #pragma section data RFD_DATA
    #elif defined (R_RFD_END_SECTION_RFD_DATA)
        #undef  R_RFD_END_SECTION_RFD_DATA
        #pragma section
    #endif  /* Section definition for CCRL */
#elif (COMPILER_IAR == COMPILER)
    /* Section definition for Common Component */
    #if defined (R_RFD_START_SECTION_RFD_CMN)
        #undef  R_RFD_START_SECTION_RFD_CMN
        #pragma location = "RFD_CMN"
    #elif defined (R_RFD_END_SECTION_RFD_CMN)
        #undef  R_RFD_END_SECTION_RFD_CMN
    /* Section definition for Code Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_CF)
        #undef  R_RFD_START_SECTION_RFD_CF
        #pragma location = "RFD_CF"
    #elif defined (R_RFD_END_SECTION_RFD_CF)
        #undef  R_RFD_END_SECTION_RFD_CF
    /* Section definition for Data Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_DF)
        #undef  R_RFD_START_SECTION_RFD_DF
        #pragma location = "RFD_DF"
    #elif defined (R_RFD_END_SECTION_RFD_DF)
        #undef  R_RFD_END_SECTION_RFD_DF
    /* Section definition for Extra Area Component */
    #elif defined (R_RFD_START_SECTION_RFD_EX)
        #undef  R_RFD_START_SECTION_RFD_EX
        #pragma location = "RFD_EX"
    #elif defined (R_RFD_END_SECTION_RFD_EX)
        #undef  R_RFD_END_SECTION_RFD_EX
    /* Section definition for Global Data for Common Component */
    #elif defined (R_RFD_START_SECTION_RFD_DATA)
        #undef  R_RFD_START_SECTION_RFD_DATA
        #pragma location = "RFD_DATA"
    #elif defined (R_RFD_END_SECTION_RFD_DATA)
        #undef  R_RFD_END_SECTION_RFD_DATA
    #endif  /* Section definition for IAR */
#elif (COMPILER_LLVM == COMPILER)
    /* Section definition for Common Component */
    #if defined (R_RFD_START_SECTION_RFD_CMN)
        #undef  R_RFD_START_SECTION_RFD_CMN
        #pragma clang section text="RFD_CMN"
    #elif defined (R_RFD_END_SECTION_RFD_CMN)
        #undef  R_RFD_END_SECTION_RFD_CMN
        #pragma clang section text=".text"
    /* Section definition for Code Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_CF)
        #undef  R_RFD_START_SECTION_RFD_CF
        #pragma clang section text="RFD_CF"
    #elif defined (R_RFD_END_SECTION_RFD_CF)
        #undef  R_RFD_END_SECTION_RFD_CF
        #pragma clang section text=".text"
    /* Section definition for Data Flash Component */
    #elif defined (R_RFD_START_SECTION_RFD_DF)
        #undef  R_RFD_START_SECTION_RFD_DF
        #pragma clang section text="RFD_DF"
    #elif defined (R_RFD_END_SECTION_RFD_DF)
        #undef  R_RFD_END_SECTION_RFD_DF
        #pragma clang section text=".text"
    /* Section definition for Extra Area Component */
    #elif defined (R_RFD_START_SECTION_RFD_EX)
        #undef  R_RFD_START_SECTION_RFD_EX
        #pragma clang section text="RFD_EX"
    #elif defined (R_RFD_END_SECTION_RFD_EX)
        #undef  R_RFD_END_SECTION_RFD_EX
        #pragma clang section text=".text"
    /* Section definition for Global Data for Common Component */
    #elif defined (R_RFD_START_SECTION_RFD_DATA)
        #undef  R_RFD_START_SECTION_RFD_DATA
        #pragma clang section data="RFD_DATA"
    #elif defined (R_RFD_END_SECTION_RFD_DATA)
        #undef  R_RFD_END_SECTION_RFD_DATA
        #pragma clang section data=".data"
    #endif  /* Section definition for LLVM */
#endif /* end of section definitions for each compiler */
