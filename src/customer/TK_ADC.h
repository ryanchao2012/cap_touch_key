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
* File Name    : TK_ADC.h                                                                                      *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------



/***************************************************************************************
* Description  : Touch Key's ADC definitions for user.                                 *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _TK_ADC_H
#define _TK_ADC_H

//----------ADC CH. define ------------
#define     ADC0                        0x00
#define     ADC1                        0x01
#define     ADC2                        0x02
#define     ADC3                        0x03
#define     ADC4                        0x04
#define     ADC5                        0x05
#define     ADC0_EN                     0x10
#define     ADC1_EN                     0x20
#define     ADC2_EN                     0x40
#define     ADC3_EN                     0x80
#define     ADC4_EN                     0x01
#define     ADC5_EN                     0x02
#define     ADC03_ALL_EN                (ADC0_EN | ADC1_EN | ADC2_EN | ADC3_EN)
#define     ADC45_ALL_EN                (ADC4_EN | ADC5_EN )
#define     SELECT_ADC0                 (ADC0 << 1)
#define     SELECT_ADC1                 (ADC1 << 1)
#define     SELECT_ADC2                 (ADC2 << 1)
#define     SELECT_ADC3                 (ADC3 << 1)
#define     SELECT_ADC4                 (ADC4 << 1)
#define     SELECT_ADC5                 (ADC5 << 1)
#define     ADC_CONVERT                 0x01

//------Variable declaration------------
extern void ctm_adc_init();
//extern void ctm_ADC_Sample();

#endif  //_TK_ADC_H

