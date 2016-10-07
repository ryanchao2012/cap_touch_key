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
* File Name    : ctm_sample.h                                                                                  *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : Macro & variables definition for customer !                                                   *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/             
                                                                            
//------INCLUDE define------------------
#include <TK_MCU_DEF.h>

/***************************************************************
Macro & variables definitions                                  *
***************************************************************/

// ----- Ryan Added @ 2015/10/27 ---------
#define                        LED1     (GPIO25)
#define                        LED2     (GPIO17)
#define                        LED3     (GPIO18)
//#define                   PC_STATUS     (GPIO19)
#define                   PC_STATUS     (GPIO15)

#define                    TOUCHOUT     (GPIO0)
#define                   TOUCH_KEY     (0x0100)
//#define                    KEY_PAD1     (0x0080)
//#define                    KEY_PAD2     (0x0040)
//#define                    KEY_PAD3     (0x0020)
//#define                  KEY_FINGER     (KEY_PAD1)
#define   HW_TK18_I2C_MASTER_SAMPLE     (ENABLE)

// -------------- Above ------------------

#define TK3_MAX_THRESHOLD               1350u           //KEY1 max. finger signal in water.
#define TK4_MAX_THRESHOLD               1400u           //KEY3 max. finger signal in water.
#define TK5_MAX_THRESHOLD               1500u           //KEY5 max. finger signal in water.
#define TK6_MAX_THRESHOLD               1250u           //KEY2 max. finger signal in water.
#define TK7_MAX_THRESHOLD               1300u           //KEY4 max. finger signal in water.

#define NO_WATER_DEBOUNCE_TIME          10
#define SAME_KEY_DEBOUNCE_TIME          3

#define TK3_MAPPING_ADDR                0
#define TK4_MAPPING_ADDR                1
#define TK5_MAPPING_ADDR                2
#define TK6_MAPPING_ADDR                3
#define TK7_MAPPING_ADDR                4

#define KEY1                            1
#define KEY2                            2
#define KEY3                            3
#define KEY4                            4
#define KEY5                            5

#define BUZZER_EN()                     PWM_EN(PWM_CH)
#define BUZZER_DI()                     PWM_DIS(PWM_CH)
#define BUZ_ON_TIME                     100              //Buzzer on time(mS).

#define AD_REHEAT_CNT                   40              //ADC value average times.
#define AD_VALUE_NULL                   0xFFFF


//------Function declaration------------

// ----- Ryan Added @ 2015/10/27 ---------
extern void debug_touch(U16 key);
extern void Ctm_Beep_Set(U8 BuzOnTime_mS);
extern void ctm_delay(U16 cycle);
extern void check_touch_key(U16 key);
// -------------- Above ------------------

extern U16  backlight_time;
extern U16  ctm_timer_1ms_counter;
extern U8   uc_ctm_Buzzer_timer;
extern xdata U16   adc_avg_value;
extern	code U8 code_7_seg_hex_signal_table[];

extern void ctm_sample_init();
extern void ctm_tk_handler();
extern void ADC_Process();
extern void LED_Display();
extern	void ctm_show_SEG_pattern(U8 uc_pattern);

