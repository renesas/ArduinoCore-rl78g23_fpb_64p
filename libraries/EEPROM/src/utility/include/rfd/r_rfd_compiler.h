/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_compiler.h
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : Compiler dependent header file
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

#ifndef R_RFD_COMPILER_H
#define R_RFD_COMPILER_H

/* Compiler definition */
#define COMPILER_CC   (1)
#define COMPILER_IAR  (2)
#define COMPILER_LLVM (3)

#if defined (__llvm__)
    #define COMPILER COMPILER_LLVM
#elif defined (__CCRL__)
    #define COMPILER COMPILER_CC
#elif defined (__IAR_SYSTEMS_ICC__)
    #define COMPILER COMPILER_IAR
#else
    /* Unknown compiler error */
    #error  "Non-supported compiler."
#endif

/* Compiler dependent definition */
#if (COMPILER_CC == COMPILER)
    #define R_RFD_FAR_FUNC                           __far
    #define R_RFD_NO_OPERATION                       __nop
    #define R_RFD_DISABLE_INTERRUPT                  __DI
    #define R_RFD_ENABLE_INTERRUPT                   __EI
    #define R_RFD_GET_PSW_IE_STATE                   __get_psw
    #define R_RFD_IS_PSW_IE_ENABLE(u08_psw_ie_state) (0u != ((u08_psw_ie_state) & 0x80u))
#elif (COMPILER_IAR == COMPILER)
    #define R_RFD_FAR_FUNC                           __far_func
    #define R_RFD_NO_OPERATION                       __no_operation
    #define R_RFD_DISABLE_INTERRUPT                  __disable_interrupt
    #define R_RFD_ENABLE_INTERRUPT                   __enable_interrupt
    #define R_RFD_GET_PSW_IE_STATE                   __get_interrupt_state
    #define R_RFD_IS_PSW_IE_ENABLE(u08_psw_ie_state) (0u != ((u08_psw_ie_state) & 0x80u))
#elif (COMPILER_LLVM == COMPILER)
    #define R_RFD_FAR_FUNC                           __far
    #define R_RFD_NO_OPERATION                       __nop
    #define R_RFD_DISABLE_INTERRUPT                  __DI
    #define R_RFD_ENABLE_INTERRUPT                   __EI
    #define R_RFD_GET_PSW_IE_STATE                   (uint8_t)__builtin_rl78_pswie
    #define R_RFD_IS_PSW_IE_ENABLE(u08_psw_ie_state) (0u != (u08_psw_ie_state))
#else
    /* Unknown compiler error */
    #error  "Non-supported compiler."
#endif

#endif /* end of R_RFD_COMPILER_H */
