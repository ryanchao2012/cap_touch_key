/***************************************************************************************************************             
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
 **************************************************************************************************************/             
                                                                                                                             
/***************************************************************************************************************             
* File Name    : TK_BTN.c                                                                                      *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------

#include <stdio.h>  
#include "TK_MCU_DEF.h"
#include "TK18_LIB_API.h"
#include "TK18_LIB_HW.h"
#include "TK18_LIB_REG.h"
#include "ctm_sample.h"
#include "TK_BTN.h"
#include "TK_LED.h"
#include <intrins.h>        //for _nop_();


/***************************************************************
Constant data & variables definitions                          *
***************************************************************/

//------Variable declaration------------

//The Button initial control by  "  void drv_tk_init(void); "
// Please refer to TKxx_LIB_API.h
//




