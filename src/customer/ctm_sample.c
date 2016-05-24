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
* File Name    : ctm_sample.c                                                                                  *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------
#include <TK_MCU_DEF.h>
#include <TK18_LIB_API.h>
#include <TK18_LIB_HW.h>
#include <TK18_LIB_REG.h>
#include <ctm_sample.h>
#include <stdio.h>
#include <TK_PWM.h>
#include <TK_GPIO.h>
#include <TK_I2C_Master.h>

/***************************************************************
Constant data & variables definitions                          *
***************************************************************/
#define DEBUG  0
//------Variable declaration------------
#if (DB_WATER_PROOF_ENABLE)
code U8 ucCTM_KeyTable[CTM_BUTTON_SIZE] = {CTM_BUTTON_MAPPING_TABLE};
xdata U8    max_key[2];
xdata S16   max_signal[2];
xdata U8    ucKNL_CurrOnStatus_buf[3];
#endif

static U8 led_level = 0;
U16     backlight_time;
U8      uc_ctm_Buzzer_timer;                                    //蜂鸣器的间隔时间
U16     ctm_timer_1ms_counter;
void    Ctm_Print_Data(U8 Position, U16 i);


#if (DEBUG)
void debug_touch(U16 key) {
	U8 i;
	U16 temp = key;
	
	GPIODO3 |=  0x20;  // Set GPIO29 output HIGH
	ctm_delay(50);
	GPIODO3 &= ~0x20;
	for(i = 0; i < 16; i++) {
		if((temp >> (15 - i)) & 0x01) {  GPIODO3 |=  0x20;  } // Set GPIO29 output HIGH
		else {  GPIODO3 &= ~0x20;  }
		ctm_delay(100);
	}
	GPIODO3 |=  0x20;  // Set GPIO29 output HIGH
	ctm_delay(50);
	GPIODO3 &= ~0x20;
	
}
#endif


void ctm_delay(U16 cycle) {
	U16 i = cycle;
	while(i--);
}


void check_touch_key(U16 key) {
	static BOOL touch_out_level = 1;
	static BOOL key_pressed = 0;
	static int keys[] = {KEY_PAD1, KEY_PAD2, KEY_PAD3};
	static int leds[] = {LED1, LED2, LED3};
	static int i = 0;
	
	static U8 temp = 0;
	if(key & KEY_PWRSW) {
		if(!(key & KEY_FINGER)) {
			if(touch_out_level) {
				drv_set_gpio(TOUCHOUT | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);
				touch_out_level = 0;
			}
		}
	} 
	
	else {
		if(!touch_out_level) {
			drv_set_gpio(TOUCHOUT | GPIO_PUSH_PULL | GPIO_ACTIVE_HIGH);
			touch_out_level = 1;
		}
		
		if(key != 0x00) {
			if(!key_pressed) {
				key_pressed = 1;
				Ctm_Beep_Set(BUZ_ON_TIME);
				ctm_delay(40);  // 40: ~1 mSec
				
				temp = key & 0xFF;
				Cust_I2C_WriteByte(temp);
				ctm_delay(40);  // 40: ~1 mSec
				
			}
			for(i = 0; i < 3; i++) {
				if(key & keys[i]) {
					if(~(led_level & (0x1 << i))) {
						drv_set_gpio(leds[i] | GPIO_PUSH_PULL | GPIO_ACTIVE_HIGH);
						led_level |= (0x1 << i);
					}						
				} else {
					if(led_level & (0x1 << i)) {
						drv_set_gpio(leds[i] | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);
						led_level &= ~(0x1 << i);
					}
				}
			}
			
		} 
		else { 
			key_pressed = 0;
			if(led_level) {
				for(i = 0; i < 3; i++) { drv_set_gpio(leds[i] | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);	}
				led_level = 0;
			}
		}
	}

}

/***************************************************************          
* Function Name: ctm_sample_init                               *          
* Description  : Customer related code initial.                *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/          
void ctm_sample_init()
{
#if (SYS_UART_ENABLE)    
    ctm_uart_init();
#endif
#if (SYS_ADC_ENABLE)
    ctm_adc_init();
#endif    
#if (SYS_GPIO_ENABLE)
    ctm_GPIO_init();
#endif
#if (SYS_LED_ENABLE)
    ctm_led_init();
#endif
#if (SYS_PWM_ENABLE)
    ctm_PWM_init();
#endif
#if(HW_TK18_I2C_MASTER_SAMPLE == ENABLE)
	I2C_Init();
	Cust_I2C_SetAddress(I2C_ADD_START);
#endif
/*	
    GPIOIE3 &= ~0x10; // Disable GPIO28 INPUT mode
	GPIOOE3 |=  0x10; // Enable GPIO28 OUTPUT mode
	GPIODO3 |=  0x10; // Set GPIO28 output LOW
*/	
}


/***************************************************************
* Function Name: Ctm_Beep_Set                                  *
* Description  : Set buzzer on time & enable it.               *
* Arguments    : BuzOnTime_mS                                  *
* Return Value : None                                          *
* Remark       :                                               *
***************************************************************/
void Ctm_Beep_Set(U8 BuzOnTime_mS)
{
    uc_ctm_Buzzer_timer = BuzOnTime_mS;
    BUZZER_EN();
	ET0 = 1;
	TR0 = 1;
}


#if (DB_WATER_PROOF_ENABLE)
/***************************************************************
* Function Name: Get_Max_Key_id                                *
* Description  : Get current MAX FW signal 's TK               *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       : max_key[2] & max_signal[2] will be update.    *
***************************************************************/          
void Get_Max_Key_id(void)
{
    U8  i,temp;
    S16 tmp_signal;
    max_key[0] = 0;
    max_key[1] = 0;
    max_signal[0] = max_signal[1] = 0;
    for(i=0; i<CTM_BUTTON_SIZE; i++)
    {
        temp  = i;                                              //swKNL_SignalArray index for the TK of CTM_BUTTON_MAPPING_TABLE.
        //uwDRV_Button_Signal
        tmp_signal = swKNL_SignalArray[temp];
        if(tmp_signal > max_signal[1])
        {
            max_signal[1] = tmp_signal;
            max_key[1] = i;
        }
        if(tmp_signal > max_signal[0])
        {
            max_signal[1] = max_signal[0];
            max_signal[0] = tmp_signal;
            max_key[1] = max_key[0];
            max_key[0] = i;
        }
    }
    //防止比不出大小，人为给个第二大值
    if(max_key[0] == max_key[1])
    {
        ++max_key[1];
        if(max_key[1] >= CTM_BUTTON_SIZE )
        {
            max_key[1] = 0;
        }
    }
}               
#endif


#if (DB_WATER_PROOF_ENABLE)
/***************************************************************
* Function Name: Clr_Signal_data                               *
* Description  : Reset all TK's FW signal.                     *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       :                                               *          
***************************************************************/          
void Clr_Signal_data(void)
{
    U8 i;
    for(i=0; i<CTM_BUTTON_SIZE; i++)
    {
        swKNL_SignalArray[i] = 0;
    }
    ucKNL_CurrOnStatus[0] = 0;
    ucKNL_CurrOnStatus[1] = 0;
    ucKNL_CurrOnStatus[2] = 0;
}
#endif


/***************************************************************
* Function Name: Get_Key_number                                *
* Description  : To check how many TK are pressed ?            *
* Arguments    : None                                          *
* Return Value : cnt= Numbers of totally actived-TK.           *
* Remark       :                                               *          
***************************************************************/          
U8 Get_Key_number(void)
{
    U8 cnt = 0;
    U8 i;

    for(i=0; i < DRV_SCAN_MAX_PORTS; i++)
    {
        if(ucKNL_CurrOnStatus[IDX(i)] & BIT_N(i))
        {
            cnt++;
        }
    }
    return cnt;
}


/***************************************************************          
* Function Name: ctm_tk_handler                                *          
* Description  : TK behavior processing for Customer           *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/      
void ctm_tk_handler()
{
    U8  temp;
//    static  BOOL    KeyRelease = 0;
#if (DB_WATER_PROOF_ENABLE)
    static  U16     holding_key_cnt = 0;
    static  U8      max_key_buf = 0xff;
    static  U8      max_key_change = 0;
    static  U8      no_water_times = 0;
    static  U8      water_flow = 0;
    Get_Max_Key_id();
#endif
    temp = Get_Key_number();

//------For Water Proof only---------->>
#if (DB_WATER_PROOF_ENABLE)
    if(ucKNL_CurrOnStatus[0])
    {
        if(max_key[0] != max_key_buf)
        {
            max_key_change = 0;
            max_key_buf = max_key[0];
            return;
        }
        else
        {
            ++max_key_change;
            if(max_key_change >= SAME_KEY_DEBOUNCE_TIME)
            {
                if(temp >= 2)
                {
                    no_water_times = 0;
                    max_key_change = 0;
                    if(water_flow == 0)
                    {
                        water_flow = 1;
                        Clr_Signal_data();
                        return;
                    }
                }
                else
                {
                    ++no_water_times;
                    if(no_water_times >= NO_WATER_DEBOUNCE_TIME)
                    {
                        no_water_times = 0;
                        if(water_flow)
                        {
                            water_flow = 0;
                        }
                    }
                }
                max_key_change = SAME_KEY_DEBOUNCE_TIME;
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        max_key_buf = 0xff;
        max_key_change = 0;
        no_water_times = 0;
    }

    if(ucKNL_CurrOnStatus[0])
    {
        ++holding_key_cnt;
        if(holding_key_cnt >= 20000/20)
        {
            holding_key_cnt = 0;
            Clr_Signal_data();
        }
        if(ucKNL_CurrOnStatus_buf[0] == 0)
        {
            //TK4 & TK7 signal compare
            if((ucKNL_CurrOnStatus[0] & (1 << TK4)) &&
              (ucKNL_CurrOnStatus[0] & (1 << TK7)) &&
              (((ucCTM_KeyTable[max_key[0]]) == TK4) || ((ucCTM_KeyTable[max_key[0]]) == TK7))
              )
            {
                if((TK7_MAX_THRESHOLD + swKNL_SignalArray[TK4_MAPPING_ADDR]) < (TK4_MAX_THRESHOLD + swKNL_SignalArray[TK7_MAPPING_ADDR]))
                {
                    ucKNL_CurrOnStatus_buf[0] = 1 << TK7;
                }
                else
                {
                    ucKNL_CurrOnStatus_buf[0] = 1 << TK4;
                }
            }

            //TK3 & TK6 signal compare
            else if((ucKNL_CurrOnStatus[0] & (1 << TK3)) &&
              (ucKNL_CurrOnStatus[0] & (1 << TK6)) &&
              (((ucCTM_KeyTable[max_key[0]]) == TK3) || ((ucCTM_KeyTable[max_key[0]]) == TK6))
              )
            {
                if((TK6_MAX_THRESHOLD + swKNL_SignalArray[TK3_MAPPING_ADDR]) < (TK3_MAX_THRESHOLD + swKNL_SignalArray[TK6_MAPPING_ADDR]))
                {
                    ucKNL_CurrOnStatus_buf[0] = 1 << TK6;
                }
                else
                {
                    ucKNL_CurrOnStatus_buf[0] = 1 << TK3;
                }
            }
            else
            {

                //TK5 & TK7 signal compare
                if( (ucKNL_CurrOnStatus[0] & (1 << TK5)) &&
                    (ucKNL_CurrOnStatus[0] & (1 << TK7)) &&
                    (((ucCTM_KeyTable[max_key[0]]) == TK5) || ((ucCTM_KeyTable[max_key[0]]) == TK7)) )
                {
                    if((TK7_MAX_THRESHOLD + swKNL_SignalArray[TK5_MAPPING_ADDR]) < (TK5_MAX_THRESHOLD + swKNL_SignalArray[TK7_MAPPING_ADDR]))
                    {
                        ucKNL_CurrOnStatus_buf[0] = 1 << TK7;
                    }
                    else
                    {
                        ucKNL_CurrOnStatus_buf[0] = 1 << TK5;
                    }
                }
                else
                {
                    //TK3 & TK4 signal compare
                    if( (ucKNL_CurrOnStatus[0] & (1 << TK3)) &&
                        (ucKNL_CurrOnStatus[0] & (1 << TK4)) &&
                        (((ucCTM_KeyTable[max_key[0]]) == TK3) || ((ucCTM_KeyTable[max_key[0]]) == TK4)) )
                    {
                        if((TK4_MAX_THRESHOLD + swKNL_SignalArray[TK3_MAPPING_ADDR]) < (TK3_MAX_THRESHOLD + swKNL_SignalArray[TK4_MAPPING_ADDR]))
                        {
                            ucKNL_CurrOnStatus_buf[0] = 1 << TK4;
                        }
                        else
                        {
                            ucKNL_CurrOnStatus_buf[0] = 1 << TK3;
                        }
                    }
                    else
                    {
                        ucKNL_CurrOnStatus_buf[0]  = (1 << ucCTM_KeyTable[max_key[0]]);
                    }
                }
            }
        }
    }
    else
    {
        holding_key_cnt = 0;
        ucKNL_CurrOnStatus_buf[0] = 0;
    }
#endif
//------For Water Proof only----------<<
/*
    if(ucKNL_CurrOnStatus[1])
    {
        if(KeyRelease == 0)
        {
            KeyRelease = 1;
            Ctm_Beep_Set(BUZ_ON_TIME);
        }
    }
    else
    {
        KeyRelease = 0;
    }
*/
}


#if (0)
extern  code U8  code_ctm_Button_table[];
/***************************************************************
* Function Name: Ctm_Print_Data                                *
* Description  : Printing current data                         *
* Arguments    : None.                                         *
* Return Value : None.                                         *
* Remark       : This function is just for debugging.          *
***************************************************************/
void Ctm_Print_Data(U8 Position, U16 i)
{
    U8  j;
    if (MISC_E51GRP == 0x89)                                    //连接 X-ISP 的时候才能够打印出来
    {
        if(drv_get_lib_version() >= 0x300)
        {
            for(j = 0; j < CTM_BUTTON_SIZE; j++)
            {
                if(code_ctm_Button_table[j] == Position)
                {
                    break;
                }
            }
            if(j >= CTM_BUTTON_SIZE)
            {
                if(Position == 24)
                {
                    swKNL_SignalArray[CTM_BUTTON_SIZE] =  i;
                }
            }
            else
            {
                swKNL_SignalArray[j] =  i;                      //从第 j 个RAWCNT buffer 打印出来 ，注意仅使用于打印在没有用到的button处
            }
        }
        else
        {
            swKNL_SignalArray[Position] =  i;
        }
    }
}
#endif



