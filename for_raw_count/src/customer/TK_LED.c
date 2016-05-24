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
* File Name    : TK_LED.c                                                                                      *             
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
#include "TK_LED.h"
#include <intrins.h>                    //for _nop_();


#if (SYS_LED_ENABLE)
/***************************************************************
Constant data & variables definitions                          *
***************************************************************/
void    ctm_show_key_value(U16 temp);
void    ctm_show_number(U16 temp);
void    ctm_show_SEG_pattern(U8 uc_pattern);
void    drv_led_show_sample(U8 sample_idx, U8 com_flag);
void    Set_OneIcon_Disp(U8 ComIdx, U8 BitIdx, BOOL OnOff);

code U8 code_led_duty_level_table[15] =
{
    LED_DUTY_LEVEL15,
    LED_DUTY_LEVEL14,
    LED_DUTY_LEVEL13,
    LED_DUTY_LEVEL12,
    LED_DUTY_LEVEL11,
    LED_DUTY_LEVEL10,
    LED_DUTY_LEVEL9,
    LED_DUTY_LEVEL8,
    LED_DUTY_LEVEL7,
    LED_DUTY_LEVEL6,
    LED_DUTY_LEVEL5,
    LED_DUTY_LEVEL4,
    LED_DUTY_LEVEL3,
    LED_DUTY_LEVEL2,
    LED_DUTY_LEVEL1
 };

code U8 code_7_seg_hex_signal_table[11] =
{
    D_NUMBER_0,
    D_NUMBER_1,
    D_NUMBER_2,
    D_NUMBER_3,
    D_NUMBER_4,
    D_NUMBER_5,
    D_NUMBER_6,
    D_NUMBER_7,
    D_NUMBER_8,
    D_NUMBER_9,
    D_BLANKING
 };


/***************************************************************
* Function Name: ctm_led_init                                  *
* Description  : Customer related code initial.                *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       :                                               *
***************************************************************/
void ctm_led_init()
{
    drv_led_init(LED_FREQ_HZ, LED_DUTY, LED_COM);               //Enable LED driver.
}


/***********************************************************************************
* Function Name: drv_led_show_sample                                               *
* Description  : LED Display  behavior processing for Customer                     *
* Arguments    : sample_idx, com_flag.                                             *
* Return Value : None                                                              *
* Remark       :                                                                   *
*  sample_idx=> if(com_flag.7 == 1) show sample of code_7_seg_hex_signal_table[]   *
*               else               put value of sample_idx into reg[LEDSEGC#]      *
*    com_flag=> bit7    : enable [show sample of code_7_seg_hex_signal_table],     *
*                         or put value of sample_idx into reg[LEDSEGC#]            *
*               bit0~2  : the number of reg[LEDSEGC#]                              *
***********************************************************************************/
void drv_led_show_sample(U8 sample_idx, U8 com_flag)
{
    U8 idx;
    idx = (com_flag & 0x07);
    if (com_flag & 0x80)
    {
        *(&LEDSEGC0 + idx)  = code_7_seg_hex_signal_table[sample_idx];              //选择使用 code_7_seg_hex_signal_table 里的表格数据
    }
    else
    {
        *(&LEDSEGC0 + idx)  = sample_idx;
    } 
    return;    
} 


/***************************************************************
* Function Name: ctm_show_key_valuern                          *
* Description  : Display Key no at DIG1 & DIG2.                *
* Arguments    : temp= current key no for display.             *
* Return Value : None                                          *
* Remark       : DIG[3:0] show "-temp-".                       *
***************************************************************/
void ctm_show_key_value(U16 temp)
{
    *(&LEDSEGC0 + COM_DIGIT0) = D_SEG_G;                        //"-"
    drv_led_show_sample((temp / 10) % 10, 0x80 | COM_DIGIT1);
    drv_led_show_sample((temp / 1 ) % 10, 0x80 | COM_DIGIT2);
    *(&LEDSEGC0 + COM_DIGIT3) = D_SEG_G;                        //"-"
}


/***************************************************************
* Function Name: ctm_show_SEG_pattern                          *
* Description  : LED Display behavior processing for Customer  *
* Arguments    : temp                                          *
* Return Value : None                                          *
* Remark       :     temp  输入123,数码管就显示123             *
***************************************************************/
void ctm_show_number(U16 temp)
{
    drv_led_show_sample((temp / 1000) % 10, 0x80|COM_DIGIT0);
    drv_led_show_sample((temp / 100) % 10, 0x80|COM_DIGIT1);
    drv_led_show_sample((temp / 10) % 10, 0x80|COM_DIGIT2);
    drv_led_show_sample((temp / 1) % 10, 0x80|COM_DIGIT3);
}


/***************************************************************          
* Function Name: ctm_show_SEG_pattern                          *          
* Description  : Display pattern at 7SEG LED.                  *
* Arguments    : uc_pattern= current pattern for display.      *
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/  
void ctm_show_SEG_pattern(U8 uc_pattern)
{
    if (uc_pattern == PATTERN_G)                                //Display "-" to all 7-SEG digital.
    {  
        drv_led_show_sample(D_SEG_G, COM_DIGIT0);
        drv_led_show_sample(D_SEG_G, COM_DIGIT1);
        drv_led_show_sample(D_SEG_G, COM_DIGIT2);
        drv_led_show_sample(D_SEG_G, COM_DIGIT3);
    }
    else if (uc_pattern == PATTERN_DISP_ALL)                    //Fill all LED display.
    {
        drv_led_show_sample(LED_ALLON, COM_DIGIT0);
        drv_led_show_sample(LED_ALLON, COM_DIGIT1);
        drv_led_show_sample(LED_ALLON, COM_DIGIT2);
        drv_led_show_sample(LED_ALLON, COM_DIGIT3);

    }
    else if (uc_pattern == PATTERN_CLR_ALL)                     //Clear all LED display.
    {
        drv_led_show_sample(LED_ALLOFF, COM_DIGIT0);
        drv_led_show_sample(LED_ALLOFF, COM_DIGIT1);
        drv_led_show_sample(LED_ALLOFF, COM_DIGIT2);
        drv_led_show_sample(LED_ALLOFF, COM_DIGIT3);
    }
    else if (uc_pattern == PATTERN_CLR_DIGIT)     
    {
        drv_led_show_sample(D_BLANKING, 0x80|COM_DIGIT0);       //Clear all 7-SEG digital.
        drv_led_show_sample(D_BLANKING, 0x80|COM_DIGIT1);
        drv_led_show_sample(D_BLANKING, 0x80|COM_DIGIT2);
        drv_led_show_sample(D_BLANKING, 0x80|COM_DIGIT3);
    }
}


/***************************************************************
* Function Name: LED_Display                                   *
* Description  : Display all LED status!                       *
* Arguments    : None.                                         *
* Return Value : None.                                         *
* Remark       : 25mS is coming in !                           *
***************************************************************/
void LED_Display(void)
{
    U8 temp = 0;
    U8 key_idx, led_idx;

    //Fan-out control for LED display.
    if (backlight_time >= 6000/1)
    {
        if (backlight_time >= 8000/1)
            backlight_time = 8000/1;                            //Set LED backlight time = 8000*1mS= 8Sec.
        temp = (backlight_time-6000)/150;
        temp += 1;
    }
    temp = code_led_duty_level_table[temp];
    drv_led_init(LED_FREQ_HZ, temp, LEDCOMEN);                  //LED duty level control.

    //Display TK No. & status while any TKs are pressed.
    if(ucKNL_CurrOnStatus[0] || ucKNL_CurrOnStatus[1] || ucKNL_CurrOnStatus[2])
    {
        backlight_time = 0;
        drv_led_init(LED_FREQ_HZ, LED_DUTY_LEVEL15, LED_COM);
        temp = 0;
        if( Is_one_button_on(TK4) )
        {
            key_idx = KEY3;
            led_idx = LED1;
            temp ++;
        }

        if( Is_one_button_on(TK3) )
        {
            key_idx = KEY1;
            led_idx = LED4;
            temp ++;
        }

        if( Is_one_button_on(TK6) )
        {
            key_idx = KEY2;
            led_idx = LED2;
            temp ++;
        }

        if( Is_one_button_on(TK7) )
        {
            key_idx = KEY4;
            led_idx = LED3;
            temp ++;
        }

        if( Is_one_button_on(TK5) )
        {
            key_idx = KEY5;
            led_idx = LED5;
            temp ++;
        }

        //Single key ?
        if( temp == 1)
        {
            Set_OneIcon_Disp(COM_LED, LED1, OFF);
            Set_OneIcon_Disp(COM_LED, LED2, OFF);
            Set_OneIcon_Disp(COM_LED, LED3, OFF);
            Set_OneIcon_Disp(COM_LED, LED4, OFF);
            Set_OneIcon_Disp(COM_LED, LED5, OFF);

            ctm_show_key_value(key_idx);
            Set_OneIcon_Disp(COM_LED, led_idx, ON);
        }
    }
    else
    {
        Set_OneIcon_Disp(COM_LED, LED1, OFF);
        Set_OneIcon_Disp(COM_LED, LED2, OFF);
        Set_OneIcon_Disp(COM_LED, LED3, OFF);
        Set_OneIcon_Disp(COM_LED, LED4, OFF);
        Set_OneIcon_Disp(COM_LED, LED5, OFF);

        //Display ADC status while no any TKs are pressed.
        if(adc_avg_value == AD_VALUE_NULL)
        {
            ctm_show_number(0);
        }
        else
        {
            ctm_show_number(adc_avg_value);
        }
    }
}


/***************************************************************          
* Function Name: Set_OneIcon_Disp                              *
* Description  : LED    one Icon Disp                          *
* Arguments    : ComIdx, BitIdx,                               *
* Return Value : None                                          *
* Remark       :   led_reg.ledseg[]                            *          
***************************************************************/  
void Set_OneIcon_Disp(U8 ComIdx, U8 BitIdx, BOOL OnOff)
{
    if(OnOff)
    {
        set_bit(*( &LEDSEGC0 + ComIdx), BitIdx);
    }
    else
    {
        clr_bit(*( &LEDSEGC0 + ComIdx), BitIdx);
    }
}


#endif


