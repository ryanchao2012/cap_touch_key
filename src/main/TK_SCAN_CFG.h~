 /**************************************************************************************************************           
 *                                                                                                             *             
 * Copyright (c) 2011-2021 ENE Technology, Inc.                                                                *             
 * All rights reserved.                                                                                        *             
 *                                                                                                             *             
 * ENE Technology <www.ene.com.tw>                                                                             *             
 *                                                                                                             *             
 * EnE reserves the right to amend this code without notice at any time.                                       *             
 * EnE assumes no responsibility for any errors appeared in the code,                                          *             
 * and EnE disclaims any express or implied warranty, relating to sale                                         *             
 * and/or use of this code including liability or warranties relating                                          *             
 * to fitness for a particular purpose, or infringement of any patent,                                         *             
 *  copyright or other intellectual property right.                                                            *             
 *                                                                                                             *             
***************************************************************************************************************/             
                                                                                                                             
/***************************************************************************************************************             
* File Name    : TK_SCAN_CFG.h                                                                                 *
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *
* Description  : Scan parameter definition for project starting up !                                           *
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/  
#ifndef _SCAN_CFG_H
#define _SCAN_CFG_H
#include <TK_MCU_DEF.h>

//------Define for TK scaning-----------
#define TK_S0                           0x02                    //Parameter of charge time.
#define TK_S1                           0x03                 //Parameter of discharge time.

#if (DB_WATER_PROOF_ENABLE)
//For Water Proof
#define TK_WIN                          0x60
#else
//For normal mode
#define TK_WIN                          0x3A
#endif

//------Define for CS Filter------------
#define TK_S0_0                         TK_S0                   //CS Filter parameter 0.
#define TK_S1_0                         TK_S1
#define TK_WIN_0                        TK_WIN

#define TK_S0_1                         TK_S0                   //CS Filter parameter 1.
#define TK_S1_1                         TK_S1
#define TK_WIN_1                        TK_WIN

#define TK_S0_2                         TK_S0                   //CS Filter parameter 2.
#define TK_S1_2                         TK_S1
#define TK_WIN_2                        TK_WIN

//------Define for TK setup-------------
#if (DB_WATER_PROOF_ENABLE)
    #define CTM_BUTTON_ON_DBS_CNTS          1                       //TK  on-debounce times(by TK scan cycle).
    #define CTM_BUTTON_OFF_DBS_CNTS         1                       //TK off-debounce times(by TK scan cycle).
#else
    #define CTM_BUTTON_ON_DBS_CNTS          2                       //TK  on-debounce times(by TK scan cycle).
    #define CTM_BUTTON_OFF_DBS_CNTS         2                       //TK off-debounce times(by TK scan cycle).
#endif

//API=> drv_eft_debounce_setting(EFT_DBS_CNTS)
#define EFT_DBS_CNTS                    2                       //Set TK ON debounce times(by TK scan time) for EFT filter.


//------Finger Signal of TK-------------
#define TK0_F_SIGNAL                    1000L                   //TK0.
#define TK1_F_SIGNAL                    1000L                   //TK1.
#define TK2_F_SIGNAL                    1000L                   //TK2.

#if (DB_WATER_PROOF_ENABLE)
//For Water Proof
#define TK3_F_SIGNAL                    1800L                   //TK3.
#define TK4_F_SIGNAL                    2150L                   //TK4.
#define TK5_F_SIGNAL                    2450L                   //TK5.
#define TK6_F_SIGNAL                    2200L                   //TK6.
#define TK7_F_SIGNAL                    2350L                   //TK7.
#else
//For normal mode
#define TK3_F_SIGNAL                    1000L                   //TK3.
#define TK4_F_SIGNAL                    1000L                   //TK4.
#define TK5_F_SIGNAL                    1000L                   //TK5.
#define TK6_F_SIGNAL                    1000L                   //TK6.
#define TK7_F_SIGNAL                    1000L                   //TK7.
#endif

#define TK8_F_SIGNAL                    1000L                   //TK8.
#define TK9_F_SIGNAL                    1000L                   //TK9.
#define TK10_F_SIGNAL                   1000L                   //TK10.
#define TK11_F_SIGNAL                   1000L                   //TK11.
#define TK12_F_SIGNAL                   1000L                   //TK12.
#define TK13_F_SIGNAL                   1000L                   //TK13.
#define TK14_F_SIGNAL                   1000L                   //TK14.
#define TK15_F_SIGNAL                   1000L                   //TK15.
#define TK16_F_SIGNAL                   1000L                   //TK16.
#define TK17_F_SIGNAL                   1000L                   //TK17.
#define TK18_F_SIGNAL                   1000L                   //TK18.
#define TK19_F_SIGNAL                   1000L                   //TK19.
#define TK20_F_SIGNAL                   1000L                   //TK20.
#define TK21_F_SIGNAL                   1000L                   //TK21.
#define TK22_F_SIGNAL                   1000L                   //TK22.
#define TK23_F_SIGNAL                   1000L                   //TK23.
#define TK24_F_SIGNAL                   1000L                   //TK24, No used (it's the IC's internal dummy TK).
#define TK25_F_SIGNAL                   9000L                   //TK25, No used !
#define TK26_F_SIGNAL                   9000L                   //TK26, No used !
#define TK27_F_SIGNAL                   9000L                   //TK27, No used !
#define TK28_F_SIGNAL                   9000L                   //TK28, No used !


#endif  //_SCAN_CFG_H
