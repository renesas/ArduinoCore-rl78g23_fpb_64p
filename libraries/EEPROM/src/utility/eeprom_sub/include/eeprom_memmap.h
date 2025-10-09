/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : sample_memmap.h
    Program Version : V1.20.00
    Device(s)       : RL78/G2x microcontroller
    Description     : Sample memory map header file
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

#include "../../include/rfd/r_rfd_compiler.h"

#if (COMPILER_CC == COMPILER)
    /* Section definition for Common Component */
    #if defined (SAMPLE_START_SECTION_SMP_CMN)
        #undef  SAMPLE_START_SECTION_SMP_CMN
        #pragma section text SMP_CMN
    #elif defined (SAMPLE_END_SECTION_SMP_CMN)
        #undef  SAMPLE_END_SECTION_SMP_CMN
        #pragma section
    /* Section definition for Code Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_CF)
        #undef  SAMPLE_START_SECTION_SMP_CF
        #pragma section text SMP_CF
    #elif defined (SAMPLE_END_SECTION_SMP_CF)
        #undef  SAMPLE_END_SECTION_SMP_CF
        #pragma section
    /* Section definition for Data Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_DF)
        #undef  SAMPLE_START_SECTION_SMP_DF
        #pragma section text SMP_DF
    #elif defined (SAMPLE_END_SECTION_SMP_DF)
        #undef  SAMPLE_END_SECTION_SMP_DF
        #pragma section
    /* Section definition for Extra Area Component */
    #elif defined (SAMPLE_START_SECTION_SMP_EX)
        #undef  SAMPLE_START_SECTION_SMP_EX
        #pragma section text SMP_EX
    #elif defined (SAMPLE_END_SECTION_SMP_EX)
        #undef  SAMPLE_END_SECTION_SMP_EX
        #pragma section
    #endif  /* Section definition for CCRL*/
#elif (COMPILER_IAR == COMPILER)
    /* Section definition for Common Component */
    #if defined (SAMPLE_START_SECTION_SMP_CMN)
        #undef  SAMPLE_START_SECTION_SMP_CMN
        #pragma location = "SMP_CMN"
    #elif defined (SAMPLE_END_SECTION_SMP_CMN)
        #undef  SAMPLE_END_SECTION_SMP_CMN
    /* Section definition for Code Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_CF)
        #undef  SAMPLE_START_SECTION_SMP_CF
        #pragma location = "SMP_CF"
    #elif defined (SAMPLE_END_SECTION_SMP_CF)
        #undef  SAMPLE_END_SECTION_SMP_CF
    /* Section definition for Data Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_DF)
        #undef  SAMPLE_START_SECTION_SMP_DF
        #pragma location = "SMP_DF"
    #elif defined (SAMPLE_END_SECTION_SMP_DF)
        #undef  SAMPLE_END_SECTION_SMP_DF
    /* Section definition for Extra Area Component */
    #elif defined (SAMPLE_START_SECTION_SMP_EX)
        #undef  SAMPLE_START_SECTION_SMP_EX
        #pragma location = "SMP_EX"
    #elif defined (SAMPLE_END_SECTION_SMP_EX)
        #undef  SAMPLE_END_SECTION_SMP_EX
    #endif  /* Section definition for IAR */
#elif (COMPILER_LLVM == COMPILER)
    /* Section definition for Common Component */
    #if defined (SAMPLE_START_SECTION_SMP_CMN)
        #undef  SAMPLE_START_SECTION_SMP_CMN
        #pragma clang section text="SMP_CMN"
    #elif defined (SAMPLE_END_SECTION_SMP_CMN)
        #undef  SAMPLE_END_SECTION_SMP_CMN
//        #pragma clang section text=".text"
    /* Section definition for Code Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_CF)
        #undef  SAMPLE_START_SECTION_SMP_CF
        #pragma clang section text="SMP_CF"
    #elif defined (SAMPLE_END_SECTION_SMP_CF)
        #undef  SAMPLE_END_SECTION_SMP_CF
        #pragma clang section text=".text"
    /* Section definition for Data Flash Component */
    #elif defined (SAMPLE_START_SECTION_SMP_DF)
        #undef  SAMPLE_START_SECTION_SMP_DF
        #pragma clang section text="SMP_DF"
    #elif defined (SAMPLE_END_SECTION_SMP_DF)
        #undef  SAMPLE_END_SECTION_SMP_DF
        #pragma clang section text=".text"
    /* Section definition for Extra Area Component */
    #elif defined (SAMPLE_START_SECTION_SMP_EX)
        #undef  SAMPLE_START_SECTION_SMP_EX
        #pragma clang section text="SMP_EX"
    #elif defined (SAMPLE_END_SECTION_SMP_EX)
        #undef  SAMPLE_END_SECTION_SMP_EX
        #pragma clang section text=".text"
    #endif  /* Section definition for LLVM */
#endif /* end of section definitions for each compiler */
