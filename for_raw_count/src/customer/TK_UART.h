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
* File Name    : TK_UART.h                                                                                     *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------



/***************************************************************************************
* Description  : UART parameter definitions for user.                                  *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _TK_UART_H
#define _TK_UART_H

//------Variable declaration------------
extern void ctm_uart_TX_sample();
extern void ctm_uart_init();
extern void ctm_uart_start_TX();

#endif  //_TK_UART_H

