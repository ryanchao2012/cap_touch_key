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
* File Name    : TK_GPIO.h                                                                                     *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------



/***************************************************************************************
* Description  : GPIO parameter definitions for user.                                  *
* Creation Date: 2014/12/15                                                            *
***************************************************************************************/
#ifndef _TK_GPIO_H
#define _TK_GPIO_H

//------GPIO type define----------------
#define GPIO_PUSH_PULL                  (0x00<<6)       //Push-pull type.
#define GPIO_OPEN_DRAIN                 (0x01<<6)       //Open-drain type.     
#define GPIO_ACTIVE_LOW                 (0x00<<7)       //Active-low.
#define GPIO_ACTIVE_HIGH                (0x01<<7)       //Active-High.

//------GPIO output setting-------------
//bit0~5: GPIOxx index (GPIO00 ~ GPIO35 index).
//bit6  : Output type  (0= Push-Pull / 1= Open-Drain).
//bit7  : Active level (0= Active-low/ 1= Active-high).          
#define CTM_DIRECT_TABLE                (GPIO14 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO15 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO16 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO17 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO18 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO19 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO22 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW), \
                                        (GPIO23 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW)
#define INDICATE_PIN                    (GPIO33 | GPIO_OPEN_DRAIN | GPIO_ACTIVE_LOW)       //Indicate output setting

//------Variable declaration------------
extern void ctm_GPIO_init();
extern void drv_set_gpio(U8 gpio_num);



#endif  //_TK_GPIO_H

