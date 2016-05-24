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
***************************************************************************************************************/             
                                                                                                                             
/***************************************************************************************************************             
* File Name    : TK18_LIB_API.h                                                                                *             
* Version      :                                                                                               *             
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : API declaration.                                                                              *             
* Creation Date: 2014/04/22                                                                                    *             
***************************************************************************************************************/             

#ifndef _TK18_LIB_API_H_
#define _TK18_LIB_API_H_

#include <common.h>

/***************************************************************                                                         
Initial's API                                                  *                                                         
***************************************************************/                                                         
extern void drv_sfr_init(void);
extern void drv_tk_init(void);
extern void drv_wdt_init(U16 time_ms);    
extern void drv_led_init(U16 freq_Hz, U8 duty, U8 ledcomen);
extern void drv_serial_port_init(U32 baud_rate,U8 tx_gpio_number,U8 rx_gpio_number);
  
/***************************************************************                                                         
Functional API                                                 *                                                         
***************************************************************/                                                         
extern void drv_enable_noise_filter(U8 enable_disable);
extern void drv_enable_water_filter(U8 enable_disable);
extern void drv_enable_RF_filter(U8 enable_disable);
extern void drv_enable_dummy_recover(U8 enable_disable);
extern void drv_wdt_clr();

/***************************************************************                                                         
Touck Key's related API                                        *                                                         
***************************************************************/                                                         
extern void knl_signal_fine_tune_config(U8 the_value_be_eaten, U16 the_timeup_value_to_eat);
extern void knl_signal_process_config(S16 TimelineStopThreshold, S16 TimelineNoiseStableThreshold, U8 TimelineNoiseStableCounter);
extern U8   knl_get_button_status(U8 portnum);
extern U8   knl_get_button_event(U8 portnum);
extern U8   drv_if_water_on();
extern U8   drv_tk_process();
extern U8   drv_tk_multitask_process();
extern void drv_scan_setup_dummycount(U8 count);
extern void drv_ragfinetune_signal_config(U16 value, U8 onnum, U8 offnum);
extern void drv_cleaning_rag(U8 onnum);
//extern void drv_enable_change_scan_freq(U8 enable_disable);
extern void drv_enable_change_scan_freq(U8 enable_disable,U16 noise_th);
extern void drv_eft_debounce_setting(U8 count);
extern void drv_check_cover_onoff();
extern U8   drv_if_cleaning_rag_on();
/***************************************************************                                                         
Application's API                                              *                                                         
***************************************************************/                                                         
extern U16  drv_get_lib_version(); 
extern U8   knl_enable_sram_docheck(U8 enable_disable);
extern U8   drv_flash_write(unsigned char SRAM_Buffer[],U8 size);
extern U8   drv_flash_read(unsigned char SRAM_Buffer[], U8 size);
extern U8   drv_flash_page_write(unsigned char SRAM_Page_Buffer[],U8 page_no);
extern U8   drv_flash_page_read(unsigned char SRAM_Page_Buffer[],U8 page_no);
extern void drv_timer_init(U8 ucID, U16 uwElapse);
extern void drv_reload_timer0();
extern void drv_reload_timer1();
extern void drv_tk_fifo_process(void) reentrant;
extern void drv_simple_pwm_init(U8 pwm_num, U16 N_Hz, U8 high_duty);
extern void fw_test(U16 period);
#endif  //__TK18_LIB_API_H

