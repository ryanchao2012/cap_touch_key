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
* File Name    : main.c                                                                                        *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the main's function.                                                     *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------
#include <TK_MCU_DEF.h>
#include <TK18_LIB_API.h>
#include <TK18_LIB_REG.h>
#include <TK18_LIB_HW.h>
#include <ctm_sample.h>
#include <stdio.h>  


/* deprecated
PAD1   [1]0x80  
PAD2   [1]0x40
PAD3   [1]0x20
PWRSW  [2]0x01
BUZZER    PWM0
*/

/* 
TOUCH_KEY  [2]0x01,   TK16, PIN12,
PC_STATUS           GPIO15, PIN11
BUZZER     PWM0
*/


volatile U16 touch_key;
//extern void drv_set_gpio(U8 gpio_num);
/***************************************************************
* Function Name: main                                          *
* Description  : This function implements main function.       *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       :                                               *
***************************************************************/
void main(void)
{
//	static U8 gpio28_status = 0;
    //Power on initial.
    drv_sfr_init();                                             // Power on initial.
    DISABLE_WDT();
    drv_ISP_Link();                                             //To check ISP is connected or not?
    TR0 = 0;                                                    //Stop Timer0.

    //Disable ISP CH. for normal operation, if it isn't connected with X-ANA !
    if (! (MISC_E51GRP == 0x89))
    {
        ISP_CH_DI();                                            //DIsable ISP BUS.
    }

    ctm_tk_init();                                              //Customer's TK initail.
    drv_tk_init();                                              //MCU's TK initial.

    //Setup TK function.
    drv_enable_noise_filter(ENABLE);                            //Enable  Noise filter.
    drv_enable_water_filter(DISABLE);                           //Disable Water filter.
    drv_enable_change_scan_freq(DISABLE,200);                   //Disable CS filter
    drv_enable_RF_filter(ENABLE);                              //Disable RF filter
    drv_enable_dummy_recover(DISABLE);
    knl_signal_fine_tune_config(FINE_TUNE_SIGNAL, FINE_TUNE_TIME);          //Config fine tune's parameter.
    knl_signal_process_config(STOP_TH, NOISE_STABLE_TH, NOISE_DBS_CNTS);    //Config signal process's parameter.
    drv_scan_setup_dummycount(TK_SCAN_DBS_CNTS);                //Set TK's scan debounce times.
    drv_eft_debounce_setting(EFT_DBS_CNTS);                     //Set TK ON debounce times for EFT filter.

    ctm_sample_init();                                          //Customer's code initail.
	ctm_timer_init();
	TR0 = 0;
	ET0 = 0;

    drv_wdt_init(WDT_PERIOD_MS);                                //Enable WDT & set overflow period time.
	
	// ucKNL_CurrOnStatus[1]: 0x80, 0x40, 0x20
	// ucKNL_CurrOnStatus[2]: 0x01, 0x02
    while(1)
    {
	
        drv_tk_fifo_process();                                  //Get TK's scan data.
        // TK scaning is finished ?
        if(drv_tk_multitask_process() == 0x80) {
			ctm_tk_handler();   //Customer's TK task processing.
			touch_key = ucKNL_CurrOnStatus[2] & 0xFF;
			touch_key = (touch_key << 8) | (ucKNL_CurrOnStatus[1] & 0xFF);
			
			check_touch_key(touch_key);
	
		}
		
		// debug_touch(touch_key);
		
        drv_wdt_clr();                                          //Clear WDT Timer !
    }
}



