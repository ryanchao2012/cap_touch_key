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
* File Name    : TK18_LIB_HW.h                                                                                 *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : H.W. definition.                                                                              *             
* Creation Date: 2015/04/24                                                                                    *
***************************************************************************************************************/             

//------INCLUDE define------------------
#include <common.h>
#include <TK18_LIB_REG.h>


/***************************************************************************************
* Description  : _CTM_VERSION_H_ Macro definitions                                     *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _CTM_VERSION_H_
#define _CTM_VERSION_H_

//------CUSTOMER_VERSION define---------
// A[Tiger-bit + Customer ID] B[Project ID] C[Major ID] D[Minor ID] E[Fine tune ID]
// Customer ID : will be given from PM.
// Project ID  : for same customer with different projects
// Major ID    : FW code major change happened
// Minor ID    : FW code minor change happened
// Fine tune ID: Will be modified by fine tune or MP tool.
#define CUSTOMER_VERSION                0x03, 0x00, 0x00, 0x01, 0x00

#endif  //_CTM_VERSION_H_


/***************************************************************************************
* Description  : _SYS_HW_H_ Macro & variable definitions                               *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _SYS_HW_H_
#define _SYS_HW_H_

//------ISP/SMBUS define----------------
#define ISP_CH_EI()                     ( I2C_S_CTRL |=  (1 << 4) )
#define ISP_CH_DI()                     ( I2C_S_CTRL &= ~(1 << 4) )
extern  void drv_ISP_Link(void);

//------SYS CLOCK define----------------
#define SYS_CLOCK_USING_14MHZ           0x04            //sys clock as 14 Mhz.
#define SYS_CLOCK_USING_7MHZ            0x00            //sys clock as  7 Mhz.
#define SYS_CLOCK_SETTING               SYS_CLOCK_USING_14MHZ

#endif  //_SYS_HW_H_


/***************************************************************************************
* Description  : _TIMER_HW_H Macro & variable definitions                              *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _TIMER_HW_H
#define _TIMER_HW_H

//------Variable declaration------------
extern xdata volatile U8        ucCOM_Timer1_Counter;
extern xdata volatile U8        uc_knl_timer0_1ms_counter;
extern xdata volatile U8        ctm_timer_125uS_counter;
extern void  ctm_timer_init(void);

#endif  //_TIMER_HW_H


/***************************************************************************************
* Description  : _SCAN_HW_H Macro & variable definitions                               *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _SCAN_HW_H_
#define _SCAN_HW_H_

#define TOOL_DEFINE_ADDRESS_RAWCNT                      0x8000
#define TOOL_DEFINE_ADDRESS_BACKUP                      0x8040
#define TOOL_DEFINE_ADDRESS_FWSIGNAL                    0x8080
#define TOOL_DEFINE_ADDRESS_BTNTABLE                    0x80E9
//------Variables define----------------
#define DRV_SCAN_MAX_PORTS              29              //Total TK port is 29 (28TK + one dummy port).
#define REAL_BUTTON_SIZE                (CTM_BUTTON_SIZE+(CTM_DUMMY_PORTNUM != 0xFF))

//------Finger Rate define--------------
#define RATE5                           1/20            //Rate:   5% to finger signal.
#define RATE10                          2/20            //Rate:  10% to finger signal.
#define RATE15                          3/20            //Rate:  15% to finger signal.
#define RATE20                          4/20            //Rate:  20% to finger signal.
#define RATE25                          5/20            //Rate:  25% to finger signal.
#define RATE30                          6/20            //Rate:  30% to finger signal.
#define RATE35                          7/20            //Rate:  35% to finger signal.
#define RATE40                          8/20            //Rate:  40% to finger signal.
#define RATE45                          9/20            //Rate:  45% to finger signal.
#define RATE50                          10/20           //Rate:  50% to finger signal.
#define RATE55                          11/20           //Rate:  55% to finger signal.
#define RATE60                          12/20           //Rate:  60% to finger signal.
#define RATE65                          13/20           //Rate:  65% to finger signal.
#define RATE70                          14/20           //Rate:  70% to finger signal.
#define RATE75                          15/20           //Rate:  75% to finger signal.
#define RATE80                          16/20           //Rate:  80% to finger signal.
#define RATE85                          17/20           //Rate:  85% to finger signal.
#define RATE90                          18/20           //Rate:  90% to finger signal.
#define RATE95                          19/20           //Rate:  95% to finger signal.
#define RATE100                         20/20           //Rate: 100% to finger signal.

//------Function declaration------------
extern xdata volatile   U8              ucCTM_ButtonTable[];
extern xdata volatile   U16             uwREG_RawCnt[];
extern xdata volatile   U16             uwREG_RawCnt_Backup[];
extern xdata volatile   S16             swKNL_SignalArray[];

extern xdata volatile   U8              ucKNL_CurrOnStatus[4];
extern xdata volatile   U8              ucKNL_PreOnStatus[4];
extern xdata volatile   U8              ucKNL_PosTriStatus[4];
extern xdata volatile   U8              ucKNL_NegTriStatus[4];
extern xdata volatile   U8              ucKNL_CurrBtnOnFlag;
extern xdata volatile   U8              ucKNL_PreBtnOnFlag;
extern xdata volatile   U8              ucKNL_WaterSts[4];
extern xdata volatile   U8              ucKNL_Button_Size;
extern void ctm_tk_init(void);

#endif //_SCAN_HW_H_


/***************************************************************************************
* Description  : _GPIO_HW_H Macro & variable definitions                               *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _GPIO_HW_H
#define _GPIO_HW_H

//----------GPIO I/O define-------------
#define     GPIO00_07_HI_DRV            GPIOE12_0
#define     GPIO08_15_HI_DRV            GPIOE12_1
#define     GPIO16_23_HI_DRV            GPIOE12_2
#define     GPIO24_31_HI_DRV            GPIOE12_3
#define     GPIO32_35_HI_DRV            GPIOE12_4

#define     GPIO00_07_WAY_OUT           GPIOOE0
#define     GPIO00_07_OUT               GPIODO0
#define     GPIO00_07_WAY_IN            GPIOIE0
#define     GPIO00_07_IN                GPIODI0

#define     GPIO08_15_WAY_OUT           GPIOOE1
#define     GPIO08_15_OUT               GPIODO1
#define     GPIO08_15_WAY_IN            GPIOIE1
#define     GPIO08_15_IN                GPIODI1

#define     GPIO16_23_WAY_OUT           GPIOOE2
#define     GPIO16_23_OUT               GPIODO2
#define     GPIO16_23_WAY_IN            GPIOIE2
#define     GPIO16_23_IN                GPIODI2

#define     GPIO24_31_WAY_OUT           GPIOOE3
#define     GPIO24_31_OUT               GPIODO3
#define     GPIO24_31_WAY_IN            GPIOIE3
#define     GPIO24_31_IN                GPIODI3

#define     GPIO32_35_WAY_OUT           GPIOOE4
#define     GPIO32_35_OUT               GPIODO4
#define     GPIO32_35_WAY_IN            GPIOIE4
#define     GPIO32_35_IN                GPIODI4

//--- GPIO 00-07 output high define ----
#define     GPIO_00_SET                 GPIODO0 |= 0x01     //GPIO  0(TK0)  output high.
#define     GPIO_01_SET                 GPIODO0 |= 0x02     //GPIO  1(TK1)  output high.
#define     GPIO_02_SET                 GPIODO0 |= 0x04     //GPIO  2(TK2)  output high.
#define     GPIO_03_SET                 GPIODO0 |= 0x08     //GPIO  3(TK3)  output high.
#define     GPIO_04_SET                 GPIODO0 |= 0x10     //GPIO  4(TK4)  output high.
#define     GPIO_05_SET                 GPIODO0 |= 0x20     //GPIO  5(TK5)  output high.
#define     GPIO_06_SET                 GPIODO0 |= 0x40     //GPIO  6(TK6)  output high.
#define     GPIO_07_SET                 GPIODO0 |= 0x80     //GPIO  7(TK7)  output high.

//--- GPIO 08-15 output high define ----
#define     GPIO_08_SET                 GPIODO1 |= 0x01     //GPIO  8(TK8)  output high.
#define     GPIO_09_SET                 GPIODO1 |= 0x02     //GPIO  9(TK9)  output high.
#define     GPIO_10_SET                 GPIODO1 |= 0x04     //GPIO 10(TK10) output high.
#define     GPIO_11_SET                 GPIODO1 |= 0x08     //GPIO 11(TK11) output high.
#define     GPIO_12_SET                 GPIODO1 |= 0x10     //GPIO 12(TK12) output high.
#define     GPIO_13_SET                 GPIODO1 |= 0x20     //GPIO 13(TK13) output high.
#define     GPIO_14_SET                 GPIODO1 |= 0x40     //GPIO 14(TK14) output high.
#define     GPIO_15_SET                 GPIODO1 |= 0x80     //GPIO 15(TK15) output high.

//--- GPIO 16-23 output high define ----
#define     GPIO_16_SET                 GPIODO2 |= 0x01     //GPIO 16(TK16) output high.
#define     GPIO_17_SET                 GPIODO2 |= 0x02     //GPIO 17(TK17) output high.
#define     GPIO_18_SET                 GPIODO2 |= 0x04     //GPIO 18(TK18) output high.
#define     GPIO_19_SET                 GPIODO2 |= 0x08     //GPIO 19(TK19) output high.
#define     GPIO_20_SET                 GPIODO2 |= 0x10     //GPIO 20(TK20) output high.
#define     GPIO_21_SET                 GPIODO2 |= 0x20     //GPIO 21(TK21) output high.
#define     GPIO_22_SET                 GPIODO2 |= 0x40     //GPIO 22(TK22) output high.
#define     GPIO_23_SET                 GPIODO2 |= 0x80     //GPIO 23(TK23) output high.

//--- GPIO 24-31 output high define ----
#define     GPIO_24_SET                 GPIODO3 |= 0x01     //GPIO 24(PWM0) output high.
#define     GPIO_25_SET                 GPIODO3 |= 0x02     //GPIO 25(PWM1) output high.
#define     GPIO_26_SET                 GPIODO3 |= 0x04     //GPIO 26(PWM2) output high.
#define     GPIO_27_SET                 GPIODO3 |= 0x08     //GPIO 27(PWM3) output high.
#define     GPIO_28_SET                 GPIODO3 |= 0x10     //GPIO 28(AD0)  output high.
#define     GPIO_29_SET                 GPIODO3 |= 0x20     //GPIO 29(AD1)  output high.
#define     GPIO_30_SET                 GPIODO3 |= 0x40     //GPIO 30(AD2)  output high.
#define     GPIO_31_SET                 GPIODO3 |= 0x80     //GPIO 31(AD3)  output high.

//--- GPIO 32-35 output high define ----
#define     GPIO_32_SET                 GPIODO4 |= 0x01     //GPIO 32(TXD)  output high.
#define     GPIO_33_SET                 GPIODO4 |= 0x02     //GPIO 33(RXD)  output high.
#define     GPIO_34_SET                 GPIODO4 |= 0x04     //GPIO 34       output high.
#define     GPIO_35_SET                 GPIODO4 |= 0x08     //GPIO 35       output high.
                                        
//--- GPIO 00-07 output low  define ----
#define     GPIO_00_CLR                 GPIODO0 &= ~0x01    //GPIO  0(TK0)  output low.
#define     GPIO_01_CLR                 GPIODO0 &= ~0x02    //GPIO  1(TK1)  output low.
#define     GPIO_02_CLR                 GPIODO0 &= ~0x04    //GPIO  2(TK2)  output low.
#define     GPIO_03_CLR                 GPIODO0 &= ~0x08    //GPIO  3(TK3)  output low.
#define     GPIO_04_CLR                 GPIODO0 &= ~0x10    //GPIO  4(TK4)  output low.
#define     GPIO_05_CLR                 GPIODO0 &= ~0x20    //GPIO  5(TK5)  output low.
#define     GPIO_06_CLR                 GPIODO0 &= ~0x40    //GPIO  6(TK6)  output low.
#define     GPIO_07_CLR                 GPIODO0 &= ~0x80    //GPIO  7(TK7)  output low.

//--- GPIO 08-15 output low  define ----
#define     GPIO_08_CLR                 GPIODO1 &= ~0x01    //GPIO  8(TK8)  output low.
#define     GPIO_09_CLR                 GPIODO1 &= ~0x02    //GPIO  9(TK9)  output low.
#define     GPIO_10_CLR                 GPIODO1 &= ~0x04    //GPIO 10(TK10) output low.
#define     GPIO_11_CLR                 GPIODO1 &= ~0x08    //GPIO 11(TK11) output low.
#define     GPIO_12_CLR                 GPIODO1 &= ~0x10    //GPIO 12(TK12) output low.
#define     GPIO_13_CLR                 GPIODO1 &= ~0x20    //GPIO 13(TK13) output low.
#define     GPIO_14_CLR                 GPIODO1 &= ~0x40    //GPIO 14(TK14) output low.
#define     GPIO_15_CLR                 GPIODO1 &= ~0x80    //GPIO 15(TK15) output low.

//--- GPIO 16-23 output low  define ----
#define     GPIO_16_CLR                 GPIODO2 &= ~0x01    //GPIO 16(TK16) output low.
#define     GPIO_17_CLR                 GPIODO2 &= ~0x02    //GPIO 17(TK17) output low.
#define     GPIO_18_CLR                 GPIODO2 &= ~0x04    //GPIO 18(TK18) output low.
#define     GPIO_19_CLR                 GPIODO2 &= ~0x08    //GPIO 19(TK19) output low.
#define     GPIO_20_CLR                 GPIODO2 &= ~0x10    //GPIO 20(TK20) output low.
#define     GPIO_21_CLR                 GPIODO2 &= ~0x20    //GPIO 21(TK21) output low.
#define     GPIO_22_CLR                 GPIODO2 &= ~0x40    //GPIO 22(TK22) output low.
#define     GPIO_23_CLR                 GPIODO2 &= ~0x80    //GPIO 23(TK23) output low.

//--- GPIO 24-31 output low  define ----
#define     GPIO_24_CLR                 GPIODO3 &= ~0x01    //GPIO 24(PWM0) output low.
#define     GPIO_25_CLR                 GPIODO3 &= ~0x02    //GPIO 25(PWM1) output low.
#define     GPIO_26_CLR                 GPIODO3 &= ~0x04    //GPIO 26(PWM2) output low.
#define     GPIO_27_CLR                 GPIODO3 &= ~0x08    //GPIO 27(PWM3) output low.
#define     GPIO_28_CLR                 GPIODO3 &= ~0x10    //GPIO 28(AD0)  output low.
#define     GPIO_29_CLR                 GPIODO3 &= ~0x20    //GPIO 29(AD1)  output low.
#define     GPIO_30_CLR                 GPIODO3 &= ~0x40    //GPIO 30(AD2)  output low.
#define     GPIO_31_CLR                 GPIODO3 &= ~0x80    //GPIO 31(AD3)  output low.

//--- GPIO 32-35 output low  define ----
#define     GPIO_32_CLR                 GPIODO4 &= ~0x01    //GPIO 32(TXD)  output low.
#define     GPIO_33_CLR                 GPIODO4 &= ~0x02    //GPIO 33(RXD)  output low.
#define     GPIO_34_CLR                 GPIODO4 &= ~0x04    //GPIO 34       output low.
#define     GPIO_35_CLR                 GPIODO4 &= ~0x08    //GPIO 35       output low.

//--- GPIO 00-07 PIN TEST define -------
#define     GPIO_00_TEST                (GPIODI0 & 0x01)    //TEST GPIO  0(TK0)  pin status.
#define     GPIO_01_TEST                (GPIODI0 & 0x02)    //TEST GPIO  1(TK1)  pin status.
#define     GPIO_02_TEST                (GPIODI0 & 0x04)    //TEST GPIO  2(TK2)  pin status.
#define     GPIO_03_TEST                (GPIODI0 & 0x08)    //TEST GPIO  3(TK3)  pin status.
#define     GPIO_04_TEST                (GPIODI0 & 0x10)    //TEST GPIO  4(TK4)  pin status.
#define     GPIO_05_TEST                (GPIODI0 & 0x20)    //TEST GPIO  5(TK5)  pin status.
#define     GPIO_06_TEST                (GPIODI0 & 0x40)    //TEST GPIO  6(TK6)  pin status.
#define     GPIO_07_TEST                (GPIODI0 & 0x80)    //TEST GPIO  7(TK7)  pin status.

//--- GPIO 08-15 PIN TEST define -------
#define     GPIO_08_TEST                (GPIODI1 & 0x01)    //TEST GPIO  8(TK8)  pin status.
#define     GPIO_09_TEST                (GPIODI1 & 0x02)    //TEST GPIO  9(TK9)  pin status.
#define     GPIO_10_TEST                (GPIODI1 & 0x04)    //TEST GPIO 10(TK10) pin status.
#define     GPIO_11_TEST                (GPIODI1 & 0x08)    //TEST GPIO 11(TK11) pin status.
#define     GPIO_12_TEST                (GPIODI1 & 0x10)    //TEST GPIO 12(TK12) pin status.
#define     GPIO_13_TEST                (GPIODI1 & 0x20)    //TEST GPIO 13(TK13) pin status.
#define     GPIO_14_TEST                (GPIODI1 & 0x40)    //TEST GPIO 14(TK14) pin status.
#define     GPIO_15_TEST                (GPIODI1 & 0x80)    //TEST GPIO 15(TK15) pin status.

//--- GPIO 16-23 PIN TEST define -------
#define     GPIO_16_TEST                (GPIODI2 & 0x01)    //TEST GPIO 16(TK16) pin status.
#define     GPIO_17_TEST                (GPIODI2 & 0x02)    //TEST GPIO 17(TK17) pin status.
#define     GPIO_18_TEST                (GPIODI2 & 0x04)    //TEST GPIO 18(TK18) pin status.
#define     GPIO_19_TEST                (GPIODI2 & 0x08)    //TEST GPIO 19(TK19) pin status.
#define     GPIO_20_TEST                (GPIODI2 & 0x10)    //TEST GPIO 20(TK20) pin status.
#define     GPIO_21_TEST                (GPIODI2 & 0x20)    //TEST GPIO 21(TK21) pin status.
#define     GPIO_22_TEST                (GPIODI2 & 0x40)    //TEST GPIO 22(TK22) pin status.
#define     GPIO_23_TEST                (GPIODI2 & 0x80)    //TEST GPIO 23(TK23) pin status.

//--- GPIO 24-31 PIN TEST define -------
#define     GPIO_24_TEST                (GPIODI3 & 0x01)    //TEST GPIO 24(PWM0) pin status.
#define     GPIO_25_TEST                (GPIODI3 & 0x02)    //TEST GPIO 25(PWM1) pin status.
#define     GPIO_26_TEST                (GPIODI3 & 0x04)    //TEST GPIO 26(PWM2) pin status.
#define     GPIO_27_TEST                (GPIODI3 & 0x08)    //TEST GPIO 27(PWM3) pin status.
#define     GPIO_28_TEST                (GPIODI3 & 0x10)    //TEST GPIO 28(AD0)  pin status.
#define     GPIO_29_TEST                (GPIODI3 & 0x20)    //TEST GPIO 29(AD1)  pin status.
#define     GPIO_30_TEST                (GPIODI3 & 0x40)    //TEST GPIO 30(AD2)  pin status.
#define     GPIO_31_TEST                (GPIODI3 & 0x80)    //TEST GPIO 31(AD3)  pin status.

//--- GPIO 32-35 PIN TEST define -------
#define     GPIO_32_TEST                (GPIODI4 & 0x01)    //TEST GPIO 32(TXD)  pin status.
#define     GPIO_33_TEST                (GPIODI4 & 0x02)    //TEST GPIO 33(RXD)  pin status.
#define     GPIO_34_TEST                (GPIODI4 & 0x04)    //TEST GPIO 34       pin status.
#define     GPIO_35_TEST                (GPIODI4 & 0x08)    //TEST GPIO 35       pin status.

//--- GPIO 00-07 I/P define ------------
#define     GPIO_00_IN                  GPIO00_07_WAY_OUT &= ~0x01; GPIO00_07_WAY_IN |= 0x01        //Config GPIO  0(TK0)  as input port.
#define     GPIO_01_IN                  GPIO00_07_WAY_OUT &= ~0x02; GPIO00_07_WAY_IN |= 0x02        //Config GPIO  1(TK1)  as input port.
#define     GPIO_02_IN                  GPIO00_07_WAY_OUT &= ~0x04; GPIO00_07_WAY_IN |= 0x04        //Config GPIO  2(TK2)  as input port.
#define     GPIO_03_IN                  GPIO00_07_WAY_OUT &= ~0x08; GPIO00_07_WAY_IN |= 0x08        //Config GPIO  3(TK3)  as input port.
#define     GPIO_04_IN                  GPIO00_07_WAY_OUT &= ~0x10; GPIO00_07_WAY_IN |= 0x10        //Config GPIO  4(TK4)  as input port.
#define     GPIO_05_IN                  GPIO00_07_WAY_OUT &= ~0x20; GPIO00_07_WAY_IN |= 0x20        //Config GPIO  5(TK5)  as input port.
#define     GPIO_06_IN                  GPIO00_07_WAY_OUT &= ~0x40; GPIO00_07_WAY_IN |= 0x40        //Config GPIO  6(TK6)  as input port.
#define     GPIO_07_IN                  GPIO00_07_WAY_OUT &= ~0x80; GPIO00_07_WAY_IN |= 0x80        //Config GPIO  7(TK7)  as input port.

//--- GPIO 08-15 I/P define ------------
#define     GPIO_08_IN                  GPIO08_15_WAY_OUT &= ~0x01; GPIO08_15_WAY_IN |= 0x01        //Config GPIO  8(TK8)  as input port.
#define     GPIO_09_IN                  GPIO08_15_WAY_OUT &= ~0x02; GPIO08_15_WAY_IN |= 0x02        //Config GPIO  9(TK9)  as input port.
#define     GPIO_10_IN                  GPIO08_15_WAY_OUT &= ~0x04; GPIO08_15_WAY_IN |= 0x04        //Config GPIO 10(TK10) as input port.
#define     GPIO_11_IN                  GPIO08_15_WAY_OUT &= ~0x08; GPIO08_15_WAY_IN |= 0x08        //Config GPIO 11(TK11) as input port.
#define     GPIO_12_IN                  GPIO08_15_WAY_OUT &= ~0x10; GPIO08_15_WAY_IN |= 0x10        //Config GPIO 12(TK12) as input port.
#define     GPIO_13_IN                  GPIO08_15_WAY_OUT &= ~0x20; GPIO08_15_WAY_IN |= 0x20        //Config GPIO 13(TK13) as input port.
#define     GPIO_14_IN                  GPIO08_15_WAY_OUT &= ~0x40; GPIO08_15_WAY_IN |= 0x40        //Config GPIO 14(TK14) as input port.
#define     GPIO_15_IN                  GPIO08_15_WAY_OUT &= ~0x80; GPIO08_15_WAY_IN |= 0x80        //Config GPIO 15(TK15) as input port.

//--- GPIO 16-23 I/P define ------------
#define     GPIO_16_IN                  GPIO16_23_WAY_OUT &= ~0x01; GPIO16_23_WAY_IN |= 0x01        //Config GPIO 16(TK16) as input port.
#define     GPIO_17_IN                  GPIO16_23_WAY_OUT &= ~0x02; GPIO16_23_WAY_IN |= 0x02        //Config GPIO 17(TK17) as input port.
#define     GPIO_18_IN                  GPIO16_23_WAY_OUT &= ~0x04; GPIO16_23_WAY_IN |= 0x04        //Config GPIO 18(TK18) as input port.
#define     GPIO_19_IN                  GPIO16_23_WAY_OUT &= ~0x08; GPIO16_23_WAY_IN |= 0x08        //Config GPIO 19(TK19) as input port.
#define     GPIO_20_IN                  GPIO16_23_WAY_OUT &= ~0x10; GPIO16_23_WAY_IN |= 0x10        //Config GPIO 20(TK20) as input port.
#define     GPIO_21_IN                  GPIO16_23_WAY_OUT &= ~0x20; GPIO16_23_WAY_IN |= 0x20        //Config GPIO 21(TK21) as input port.
#define     GPIO_22_IN                  GPIO16_23_WAY_OUT &= ~0x40; GPIO16_23_WAY_IN |= 0x40        //Config GPIO 22(TK22) as input port.
#define     GPIO_23_IN                  GPIO16_23_WAY_OUT &= ~0x80; GPIO16_23_WAY_IN |= 0x80        //Config GPIO 23(TK23) as input port.

//--- GPIO 24-31 I/P define ------------
#define     GPIO_24_IN                  GPIO24_31_WAY_OUT &= ~0x01; GPIO24_31_WAY_IN |= 0x01        //Config GPIO 24(PWM0) as input port.
#define     GPIO_25_IN                  GPIO24_31_WAY_OUT &= ~0x02; GPIO24_31_WAY_IN |= 0x02        //Config GPIO 25(PWM1) as input port.
#define     GPIO_26_IN                  GPIO24_31_WAY_OUT &= ~0x04; GPIO24_31_WAY_IN |= 0x04        //Config GPIO 26(PWM2) as input port.
#define     GPIO_27_IN                  GPIO24_31_WAY_OUT &= ~0x08; GPIO24_31_WAY_IN |= 0x08        //Config GPIO 27(PWM3) as input port.
#define     GPIO_28_IN                  GPIO24_31_WAY_OUT &= ~0x10; GPIO24_31_WAY_IN |= 0x10        //Config GPIO 28(AD0)  as input port.
#define     GPIO_29_IN                  GPIO24_31_WAY_OUT &= ~0x20; GPIO24_31_WAY_IN |= 0x20        //Config GPIO 29(AD1)  as input port.
#define     GPIO_30_IN                  GPIO24_31_WAY_OUT &= ~0x40; GPIO24_31_WAY_IN |= 0x40        //Config GPIO 30(AD2)  as input port.
#define     GPIO_31_IN                  GPIO24_31_WAY_OUT &= ~0x80; GPIO24_31_WAY_IN |= 0x80        //Config GPIO 31(AD3)  as input port.

//--- GPIO 32-35 I/P define ------------
#define     GPIO_32_IN                  GPIO32_35_WAY_OUT &= ~0x01; GPIO32_35_WAY_IN |= 0x01        //Config GPIO 32(TXD)  as input port.
#define     GPIO_33_IN                  GPIO32_35_WAY_OUT &= ~0x02; GPIO32_35_WAY_IN |= 0x02        //Config GPIO 33(RXD)  as input port.
#define     GPIO_34_IN                  GPIO32_35_WAY_OUT &= ~0x04; GPIO32_35_WAY_IN |= 0x04        //Config GPIO 34       as input port.
#define     GPIO_35_IN                  GPIO32_35_WAY_OUT &= ~0x08; GPIO32_35_WAY_IN |= 0x08        //Config GPIO 35       as input port.

//--- GPIO 00-07 O/P define ------------
#define     GPIO_00_OUT                 GPIO00_07_WAY_IN &= ~0x01; GPIO00_07_WAY_OUT |= 0x01        //Config GPIO  0(TK0)  as output port.
#define     GPIO_01_OUT                 GPIO00_07_WAY_IN &= ~0x02; GPIO00_07_WAY_OUT |= 0x02        //Config GPIO  1(TK1)  as output port.
#define     GPIO_02_OUT                 GPIO00_07_WAY_IN &= ~0x04; GPIO00_07_WAY_OUT |= 0x04        //Config GPIO  2(TK2)  as output port.
#define     GPIO_03_OUT                 GPIO00_07_WAY_IN &= ~0x08; GPIO00_07_WAY_OUT |= 0x08        //Config GPIO  3(TK3)  as output port.
#define     GPIO_04_OUT                 GPIO00_07_WAY_IN &= ~0x10; GPIO00_07_WAY_OUT |= 0x10        //Config GPIO  4(TK4)  as output port.
#define     GPIO_05_OUT                 GPIO00_07_WAY_IN &= ~0x20; GPIO00_07_WAY_OUT |= 0x20        //Config GPIO  5(TK5)  as output port.
#define     GPIO_06_OUT                 GPIO00_07_WAY_IN &= ~0x40; GPIO00_07_WAY_OUT |= 0x40        //Config GPIO  6(TK6)  as output port.
#define     GPIO_07_OUT                 GPIO00_07_WAY_IN &= ~0x80; GPIO00_07_WAY_OUT |= 0x80        //Config GPIO  7(TK7)  as output port.

//--- GPIO 08-15 O/P define ------------
#define     GPIO_08_OUT                 GPIO08_15_WAY_IN &= ~0x01; GPIO08_15_WAY_OUT |= 0x01        //Config GPIO  8(TK8)  as output port.
#define     GPIO_09_OUT                 GPIO08_15_WAY_IN &= ~0x02; GPIO08_15_WAY_OUT |= 0x02        //Config GPIO  9(TK9)  as output port.
#define     GPIO_10_OUT                 GPIO08_15_WAY_IN &= ~0x04; GPIO08_15_WAY_OUT |= 0x04        //Config GPIO 10(TK10) as output port.
#define     GPIO_11_OUT                 GPIO08_15_WAY_IN &= ~0x08; GPIO08_15_WAY_OUT |= 0x08        //Config GPIO 11(TK11) as output port.
#define     GPIO_12_OUT                 GPIO08_15_WAY_IN &= ~0x10; GPIO08_15_WAY_OUT |= 0x10        //Config GPIO 12(TK12) as output port.
#define     GPIO_13_OUT                 GPIO08_15_WAY_IN &= ~0x20; GPIO08_15_WAY_OUT |= 0x20        //Config GPIO 13(TK13) as output port.
#define     GPIO_14_OUT                 GPIO08_15_WAY_IN &= ~0x40; GPIO08_15_WAY_OUT |= 0x40        //Config GPIO 14(TK14) as output port.
#define     GPIO_15_OUT                 GPIO08_15_WAY_IN &= ~0x80; GPIO08_15_WAY_OUT |= 0x80        //Config GPIO 15(TK15) as output port.

//--- GPIO 16-23 O/P define ------------
#define     GPIO_16_OUT                 GPIO16_23_WAY_IN &= ~0x01; GPIO16_23_WAY_OUT |= 0x01        //Config GPIO 16(TK16) as output port.
#define     GPIO_17_OUT                 GPIO16_23_WAY_IN &= ~0x02; GPIO16_23_WAY_OUT |= 0x02        //Config GPIO 17(TK17) as output port.
#define     GPIO_18_OUT                 GPIO16_23_WAY_IN &= ~0x04; GPIO16_23_WAY_OUT |= 0x04        //Config GPIO 18(TK18) as output port.
#define     GPIO_19_OUT                 GPIO16_23_WAY_IN &= ~0x08; GPIO16_23_WAY_OUT |= 0x08        //Config GPIO 19(TK19) as output port.
#define     GPIO_20_OUT                 GPIO16_23_WAY_IN &= ~0x10; GPIO16_23_WAY_OUT |= 0x10        //Config GPIO 20(TK20) as output port.
#define     GPIO_21_OUT                 GPIO16_23_WAY_IN &= ~0x20; GPIO16_23_WAY_OUT |= 0x20        //Config GPIO 21(TK21) as output port.
#define     GPIO_22_OUT                 GPIO16_23_WAY_IN &= ~0x40; GPIO16_23_WAY_OUT |= 0x40        //Config GPIO 22(TK22) as output port.
#define     GPIO_23_OUT                 GPIO16_23_WAY_IN &= ~0x80; GPIO16_23_WAY_OUT |= 0x80        //Config GPIO 23(TK23) as output port.

//--- GPIO 24-31 O/P define ------------
#define     GPIO_24_OUT                 GPIO24_31_WAY_IN &= ~0x01; GPIO24_31_WAY_OUT |= 0x01        //Config GPIO 24(PWM0) as output port.
#define     GPIO_25_OUT                 GPIO24_31_WAY_IN &= ~0x02; GPIO24_31_WAY_OUT |= 0x02        //Config GPIO 25(PWM1) as output port.
#define     GPIO_26_OUT                 GPIO24_31_WAY_IN &= ~0x04; GPIO24_31_WAY_OUT |= 0x04        //Config GPIO 26(PWM2) as output port.
#define     GPIO_27_OUT                 GPIO24_31_WAY_IN &= ~0x08; GPIO24_31_WAY_OUT |= 0x08        //Config GPIO 27(PWM3) as output port.
#define     GPIO_28_OUT                 GPIO24_31_WAY_IN &= ~0x10; GPIO24_31_WAY_OUT |= 0x10        //Config GPIO 28(AD0)  as output port.
#define     GPIO_29_OUT                 GPIO24_31_WAY_IN &= ~0x20; GPIO24_31_WAY_OUT |= 0x20        //Config GPIO 29(AD1)  as output port.
#define     GPIO_30_OUT                 GPIO24_31_WAY_IN &= ~0x40; GPIO24_31_WAY_OUT |= 0x40        //Config GPIO 30(AD2)  as output port.
#define     GPIO_31_OUT                 GPIO24_31_WAY_IN &= ~0x80; GPIO24_31_WAY_OUT |= 0x80        //Config GPIO 31(AD3)  as output port.

//--- GPIO 32-35 O/P define ------------
#define     GPIO_32_OUT                 GPIO32_35_WAY_IN &= ~0x01; GPIO32_35_WAY_OUT |= 0x01        //Config GPIO 32(TXD)  as output port.
#define     GPIO_33_OUT                 GPIO32_35_WAY_IN &= ~0x02; GPIO32_35_WAY_OUT |= 0x02        //Config GPIO 33(RXD)  as output port.
#define     GPIO_34_OUT                 GPIO32_35_WAY_IN &= ~0x04; GPIO32_35_WAY_OUT |= 0x04        //Config GPIO 34       as output port.
#define     GPIO_35_OUT                 GPIO32_35_WAY_IN &= ~0x08; GPIO32_35_WAY_OUT |= 0x08        //Config GPIO 35       as output port.

#endif //_GPIO_HW_H


/***************************************************************************************
* Description  : _WDT_HW_H Macro & variable definitions                                *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _WDT_HW_H
#define _WDT_HW_H

#define DISABLE_WDT() do{WDTCFG = DISABLE;}while(0)

#endif  //_WDT_HW_H


/***************************************************************************************
* Description  : _PWM_HW_H Macro & variable definitions                                *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _PWM_HW_H
#define _PWM_HW_H

//----------PWM CH. define ------------
#define     PWM_CH0                     0                       //PWM0
#define     PWM_CH1                     1                       //PWM1
#define     PWM_CH2                     2                       //PWM2
#define     PWM_CH3                     3                       //PWM3
#define     PWM0_EN()                   GPIOMD |=  0x01
#define     PWM0_DIS()                  GPIOMD &= ~0x01
#define     PWM1_EN()                   GPIOMD |=  0x02
#define     PWM1_DIS()                  GPIOMD &= ~0x02
#define     PWM2_EN()                   GPIOMD |=  0x04
#define     PWM2_DIS()                  GPIOMD &= ~0x04
#define     PWM3_EN()                   GPIOMD |=  0x08
#define     PWM3_DIS()                  GPIOMD &= ~0x08
#define     PWM_EN(PORT)                GPIOMD |=  (1 << PORT)
#define     PWM_DIS(PORT)               GPIOMD &= ~(1 << PORT)

#endif  //_PWM_HW_H


/***************************************************************************************
* Description  : _LED_HW_H Macro & variable definitions                                *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _LED_HW_H
#define _LED_HW_H

#endif  //_LED_HW_H


/***************************************************************************************
* Description  : _UART_HW_H Macro & variable definitions                               *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _UART_HW_H
#define _UART_HW_H

#endif  //_UART_HW_H


/***************************************************************************************
* Description  : _ADC_HW_H Macro & variable definitions                                *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _ADC_HW_H
#define _ADC_HW_H

#endif  //_ADC_HW_H



