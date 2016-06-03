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
* File Name    : TK_MCU_DEF.h                                                                                  *
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : Macro & parameter definition for project starting up !                                        *
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/             

//------INCLUDE define------------------
#include <common.h>
#include <TK_SCAN_CFG.h>
//#include <TK18_LIB_REG.h>


/***************************************************************************************
* Description  : Touch Key's Macro & parameter definitions for user.                   *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _USER_TK_H
#define _USER_TK_H

#define DB_WATER_PROOF_ENABLE           TRUE                    //DemoBoard's water proof function is enable ? TRUE or FALSE.
//#define DB_WATER_PROOF_ENABLE           FALSE                   //DemoBoard's water proof function is enable ? TRUE or FALSE.

//------Define for Threshold-Rate-------
#define FINGER_RATE                     RATE40
#define WATER_RATE                      RATE25
#define IIR_RATE                        RATE15

//------Define for RF filter------------
#define DRV_RF_DUMMY_THRESHOLD          100                     //
#define DRV_RF_DUMMY_DEBOUNCE           3

//------Define for Cover checking-------
#define DRV_COVER_MAX_BUTTON_TRIGGER    4                       //
#define DRV_COVER_REBASE_CYCLE          100                     //

//------Define for IIR Noise Filter-----
#define DRV_IIR_NOISE_TH_NORMAL         250                     //
#define DRV_IIR_NOISE_TH_WATER_ON       500                     //

//------Define for Water Filter---------
#define DRV_WATER_MAX_COUNTER           5                       //Set scan cycle times to check WATER.

#if (DB_WATER_PROOF_ENABLE)
//For Water Proof
//------Define for TK setup-------------
#define CTM_BUTTON_MAPPING_TABLE        TK13,TK14,TK16     //Fill the active TK's number to this table.
#define CTM_BUTTON_SIZE                 3
#define CTM_DUMMY_PORTNUM               TK24                    //0xFF: disable
//------Define for Shielding setup------
#define CTM_SHIELDING_SIZE              3                       //Set number of Shielding port.
#define CTM_SHIELDING_TABLE             TK13,TK14,TK16     //Fill the active Shielding TK's number to this table.
#else
//For normal mode
//------Define for TK setup-------------
#define CTM_BUTTON_MAPPING_TABLE        TK13,TK14,TK16     //Fill the active TK's number to this table.
#define CTM_BUTTON_SIZE                 3
#define CTM_DUMMY_PORTNUM               TK24                    //0xFF: disable
//------Define for Shielding setup------
#define CTM_SHIELDING_SIZE              0                       //Set number of Shielding port.
#endif

#define CTM_OFF_THRESHOLD_RATE          1                       //% of Finger TH, 0: 40, 1: 50, 2: 60, 3:70

#endif  //_USER_TK_H


/***************************************************************************************
* Description  : Touch Key API's Macro & parameter definitions                         *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _TK_API_H
#define _TK_API_H

//API=> drv_wdt_init(WDT_PERIOD_MS)
#define WDT_PERIOD_MS                   1280                    //Set WDT overflow's period time(mS).

//API=> drv_led_init(LED_FREQ_HZ, LED_DUTY, LED_COM)
#define LED_FREQ_HZ                     1000                    //set LED frame freq.
#define LED_DUTY                        LED_DUTY_LEVEL15        //set LED scan pulse duty.
#define LED_COM                         COM0|COM1|COM2|COM3|COM6


//API=> drv_serial_port_init(BAUD_RATE, TX_GPIO_CH, TX_GPIO_CH)
#define BAUD_RATE                       115200                  //Set UART's baud-rate(bps).
#define TX_GPIO_CH                      GPIO32                  //Set TXD CH's GPIO number.
#define RX_GPIO_CH                      GPIO33                  //Set RXD CH's GPIO number.

//API=> knl_signal_fine_tune_config(FINE_TUNE_SIGNAL, FINE_TUNE_TIME)
#if (DB_WATER_PROOF_ENABLE)
//For Water Proof
#define FINE_TUNE_SIGNAL                250                     //Set fine tune's signal(FW_Signal)
#define FINE_TUNE_TIME                  4                       //Set fine tune's period times(by TK scan cycle).
#else
//For normal mode
#define FINE_TUNE_SIGNAL                25                      //Set fine tune's signal(FW_Signal)
#define FINE_TUNE_TIME                  15                      //Set fine tune's period times(by TK scan cycle).
#endif

//API=> knl_signal_process_config(STOP_TH, NOISE_STABLE_TH, NOISE_DBS_CNTS)
#define STOP_TH                         300                     //Set threshold to stop process noise.
#define NOISE_STABLE_TH                 75                      //Set threshold to process stable noise.
#define NOISE_DBS_CNTS                  50                      //Set debounce times(by TK scan cycle) to process stable noise.

//API=> drv_scan_setup_dummycount(TK_SCAN_DBS_CNTS)
#define TK_SCAN_DBS_CNTS                10                      //Set TK's scan debounce times(by TK scan cycle).

//API=> drv_ragfinetune_signal_config(RAG_FINE_TUNE_SIGNAL, RAG_ON_NUM, RAG_OFF_NUM)
//      drv_cleaning_rag(RAG_ON_NUM)
#define RAG_FINE_TUNE_SIGNAL            100                     //Set rag fine tune's signal(FW_Signal)
#define RAG_ON_NUM                      4                       //Set number of rag on.
#define RAG_OFF_NUM                     0                       //Set number of rag off.

//API=> drv_timer_init(TIMER0, TIMER0_PERIOD_US)
//      drv_timer_init(TIMER1, TIMER1_PERIOD_US)
#define TIMER0                          0                       //TIMER 0 CH.
#define TIMER0_PERIOD_US                1000                    //Set TIMER0 int. period time(uS).
#define TIMER1                          1                       //TIMER 1 CH.
#define TIMER1_PERIOD_US                10000                   //Set TIMER1 int. period time(uS).

//API=> drv_simple_pwm_init(PWM_CH, PWM_FREQ_HZ, PWM_DUTY)
#define PWM_CH                          PWM_CH0                 //Set PWM CH.
#define PWM_FREQ_HZ                     2400                    //Set PWM Freq.(Hz), range is 250~20000.
#define PWM_DUTY                        50                      //Set PWM pulse's duty, range is 1~100.

#endif  //_TK_API_H


/***************************************************************************************
* Description  : System function's Macro & parameter definitions                       *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _SYS_FUN_H
#define _SYS_FUN_H

#define DRV_ENABLE_COVER_FILTER         FALSE                   //Cover filter function is enable ? TRUE or FALSE.

#define FW_TEST_ENABLE                  FALSE                   //FW. test function is enable ? TRUE or FALSE.

#define SYS_UART_ENABLE                 FALSE                   //System UART function is enable ? TRUE or FALSE.

#define SYS_GPIO_ENABLE                 TRUE                    //System GPIO function is enable ? TRUE or FALSE.

#define SYS_ADC_ENABLE                  FALSE                   //System ADC  function is enable ? TRUE or FALSE.

#define SYS_LED_ENABLE                  FALSE                   //System LED  function is enable ? TRUE or FALSE.

#define SYS_PWM_ENABLE                  TRUE                    //System PWM  function is enable ? TRUE or FALSE.

//------Define for USER ISP-CH----------
#define USER_ISP_CH_ENABLE              FALSE                   //USER ISP-CH function is enable ? TRUE or FALSE.
#define USER_ISP_CLK_CH                 GPIO24                  //USER ISP CLK CH.
#define USER_ISP_DAT_CH                 GPIO25                  //USER ISP DAT CH.

#endif  //_SYS_FUN_H


