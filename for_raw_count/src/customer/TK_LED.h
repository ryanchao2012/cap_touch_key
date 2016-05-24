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
* File Name    : TK_LED.h                                                                                      *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/04/24                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------



/***************************************************************************************
* Description  : LED & parameter definitions for user.                                 *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _TK_LED_H
#define _TK_LED_H

//------HW LED COM bit define-----------
#define COM0                            BIT0
#define COM1                            BIT1
#define COM2                            BIT2
#define COM3                            BIT3
#define COM4                            BIT4
#define COM5                            BIT5
#define COM6                            BIT6

//------LED scan pulse's duty define----
#define LED_DUTY_LEVEL1                 1               //Level 1  duty= ( 1/15)*100= 7.
#define LED_DUTY_LEVEL2                 2               //Level 2  duty= ( 2/15)*100= 13.
#define LED_DUTY_LEVEL3                 3               //Level 3  duty= ( 3/15)*100= 20.
#define LED_DUTY_LEVEL4                 4               //Level 4  duty= ( 4/15)*100= 27.
#define LED_DUTY_LEVEL5                 5               //Level 5  duty= ( 5/15)*100= 33.
#define LED_DUTY_LEVEL6                 6               //Level 6  duty= ( 6/15)*100= 40.
#define LED_DUTY_LEVEL7                 7               //Level 7  duty= ( 7/15)*100= 47.
#define LED_DUTY_LEVEL8                 8               //Level 8  duty= ( 8/15)*100= 53.
#define LED_DUTY_LEVEL9                 9               //Level 9  duty= ( 9/15)*100= 60.
#define LED_DUTY_LEVEL10                10              //Level 10 duty= (10/15)*100= 67.
#define LED_DUTY_LEVEL11                11              //Level 11 duty= (11/15)*100= 73.
#define LED_DUTY_LEVEL12                12              //Level 12 duty= (12/15)*100= 80.
#define LED_DUTY_LEVEL13                13              //Level 13 duty= (13/15)*100= 87.
#define LED_DUTY_LEVEL14                14              //Level 14 duty= (14/15)*100= 93.
#define LED_DUTY_LEVEL15                15              //Level 15 duty= (15/15)*100= 100.

//------Variable declaration------------
extern void ctm_led_init();
extern void ctm_show_led();


enum
{
    NTC_NORMAL = 0,
    NTC_OPEN = 1,
    NTC_SHORT,
    NTC_OU,
};

//------Define for LED display----------
enum
{
    PATTERN_G = 0,
    PATTERN_E1,
    PATTERN_E2,
    PATTERN_E3,
    PATTERN_OU,
    PATTERN_DISP_ALL,
    PATTERN_CLR_ALL,
    PATTERN_CLR_DIGIT,
};
 
enum
{
    LED1 = 3,
    LED2 = 1,
    LED3 = 0,
    LED4 = 2,
    LED5 = 4,
};

#define COM_DIGIT0                      0x01            //DIG0's COM offset.
#define COM_DIGIT1                      0x02            //DIG1's COM offset.
#define COM_DIGIT2                      0x03            //DIG2's COM offset.
#define COM_DIGIT3                      0x00            //DIG3's COM offset.
#define COM_LED                         0x06            //Single LED's COM offset.

#define LED_DEBUG                       7
#define D_D                             (1 << 4)
#define D_E                             (1 << 3)
#define D_F                             (1 << 1)
#define D_A                             (1 << 0)
#define D_B                             (1 << 2)
#define D_C                             (1 << 6)
#define D_G                             (1 << 7)
#define D_P                             (1 << 5)

#define D_NUMBER_0                      (D_A|D_B|D_C|D_D|D_E|D_F)
#define D_NUMBER_1                      (D_C|D_B)
#define D_NUMBER_2                      (D_A|D_B|D_D|D_E|D_G)
#define D_NUMBER_3                      (D_A|D_B|D_C|D_D|D_G)
#define D_NUMBER_4                      (D_B|D_C|D_F|D_G)
#define D_NUMBER_5                      (D_A|D_C|D_D|D_F|D_G)
#define D_NUMBER_6                      (D_A|D_C|D_D|D_E|D_F|D_G)
#define D_NUMBER_7                      (D_A|D_B|D_C)
#define D_NUMBER_8                      (D_A|D_B|D_C|D_D|D_E|D_F|D_G)
#define D_NUMBER_9                      (D_A|D_B|D_C|D_D|D_F|D_G)
#define D_CHAR_E                        (D_A|D_D|D_E|D_F|D_G)
#define D_SEG_G                         (D_G)
#define D_BLANKING                      0
#define LED_ALLOFF                      0
#define LED_ALLON                       0xFF

#endif  //_TK_LED_H


