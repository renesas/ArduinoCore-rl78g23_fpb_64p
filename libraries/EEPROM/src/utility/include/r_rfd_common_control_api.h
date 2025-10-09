/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD RL78 Type01)
    
    File Name       : r_rfd_common_control_api.h
    Program Version : V1.20
    Device(s)       : RL78/G2x microcontroller
    Description     : API definition of Common Flash Control
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

#ifndef R_RFD_COMMON_CONTROL_API_H
#define R_RFD_COMMON_CONTROL_API_H

#include "rfd/r_rfd.h"

/**********************************************************************************************************************
 For Common Flash Control Component
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Prototype declaration
 *********************************************************************************************************************/

extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep1(void);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckExtraSeqEndStep1(void);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep2(void);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckExtraSeqEndStep2(void);
extern R_RFD_FAR_FUNC void        R_RFD_GetSeqErrorStatus(uint8_t __near * onp_u08_error_status);
extern R_RFD_FAR_FUNC void        R_RFD_ClearSeqRegister(void);
extern R_RFD_FAR_FUNC void        R_RFD_ForceStopSeq(void);
extern R_RFD_FAR_FUNC void        R_RFD_ForceReset(void);

#endif /* end of R_RFD_COMMON_CONTROL_API_H */
