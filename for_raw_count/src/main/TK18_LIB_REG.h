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
* File Name    : TK18_LIB_REG.h                                                                                *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : H.W. reg definition.                                                                          *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/             

//------INCLUDE define------------------
#include <common.h>


/***************************************************************************************
* Description  : _SFR51_REG_H_ Macro definitions                                       *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _SFR51_REG_H_
#define _SFR51_REG_H_

sfr P0IE = 0x80;    //Changed 8051 feature for ENE Martial 8051
sfr P1IE = 0x90;    //Changed 8051 feature for ENE Martial 8051
sfr P2   = 0xA0;
sfr P3IE = 0xB0;    //Changed 8051 feature for ENE Martial 8051
sfr PSW  = 0xD0;
sfr ACC  = 0xE0;
sfr B    = 0xF0;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr PCON2= 0x86;
sfr PCON = 0x87;    //With add-on feature for ENE Martial 8051
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr IE   = 0xA8;
sfr IP   = 0xB8;
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr SCON2= 0x9A;    //New feature in ENE Martial 8051
sfr SCON3= 0x9B;    //New feature in ENE Martial 8051
sfr P0IF = 0xD8;    //New feature in ENE Martial 8051
sfr P1IF = 0xE8;    //New feature in ENE Martial 8051
sfr P3IF = 0xF8;    //New feature in ENE Martial 8051

sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;

sbit TF1  = 0x8F;
sbit TR1  = 0x8E;
sbit TF0  = 0x8D;
sbit TR0  = 0x8C;
sbit IE1  = 0x8B;
sbit IT1  = 0x8A;
sbit IE0  = 0x89;
sbit IT0  = 0x88;

sbit EA   = 0xAF;
sbit ES   = 0xAC;
sbit ET1  = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;

sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;

sbit SM0  = 0x9F;
sbit SM1  = 0x9E;

sbit REN  = 0x9C;
sbit TB8  = 0x9B;
sbit RB8  = 0x9A;
sbit TI   = 0x99;
sbit RI   = 0x98;

sbit P0IE7 = 0x87;
sbit P0IE6 = 0x86;
sbit P0IE5 = 0x85;
sbit P0IE4 = 0x84;
sbit P0IE3 = 0x83;
sbit P0IE2 = 0x82;
sbit P0IE1 = 0x81;
sbit P0IE0 = 0x80;

sbit P1IE7 = 0x97;
sbit P1IE6 = 0x96;
sbit P1IE5 = 0x95;
sbit P1IE4 = 0x94;
sbit P1IE3 = 0x93;
sbit P1IE2 = 0x92;
sbit P1IE1 = 0x91;
sbit P1IE0 = 0x90;

sbit P3IE7 = 0xB7;
sbit P3IE6 = 0xB6;
sbit P3IE5 = 0xB5;
sbit P3IE4 = 0xB4;
sbit P3IE3 = 0xB3;
sbit P3IE2 = 0xB2;
sbit P3IE1 = 0xB1;
sbit P3IE0 = 0xB0;

sbit P0IF7 = 0xDF;
sbit P0IF6 = 0xDE;
sbit P0IF5 = 0xDD;
sbit P0IF4 = 0xDC;
sbit P0IF3 = 0xDB;
sbit P0IF2 = 0xDA;
sbit P0IF1 = 0xD9;
sbit P0IF0 = 0xD8;

sbit P1IF7 = 0xEF;
sbit P1IF6 = 0xEE;
sbit P1IF5 = 0xED;
sbit P1IF4 = 0xEC;
sbit P1IF3 = 0xEB;
sbit P1IF2 = 0xEA;
sbit P1IF1 = 0xE9;
sbit P1IF0 = 0xE8;

sbit P3IF7 = 0xFF;
sbit P3IF6 = 0xFE;
sbit P3IF5 = 0xFD;
sbit P3IF4 = 0xFC;
sbit P3IF3 = 0xFB;
sbit P3IF2 = 0xFA;
sbit P3IF1 = 0xF9;
sbit P3IF0 = 0xF8;

sfr OP1_3 = 0xC1;
sfr OP1_2 = 0xC2;
sfr OP1_1 = 0xC3;
sfr OP1_0 = 0xC4;

sfr OP2_3 = 0xD1;
sfr OP2_2 = 0xD2;
sfr OP2_1 = 0xD3;
sfr OP2_0 = 0xD4;

sfr Q_3 = 0xE1;
sfr Q_2 = 0xE2;
sfr Q_1 = 0xE3;
sfr Q_0 = 0xE4;

sfr REM_3 = 0xf1;
sfr REM_2 = 0xf2;
sfr REM_1 = 0xf3;
sfr REM_0 = 0xf4;

sfr CON_OP  = 0xC0;
sbit OP2_ZERO_Flag = 0xC6;
sbit CON_STS = 0xC4;
sbit CLR_OP = 0xCF;
sbit CLR_Q  = 0xCE;

#endif  //_SFR51_REG_H_


/***************************************************************************************
* Description  : _SYS_REG_H_ Macro definitions                                         *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _SYS_REG_H_
#define _SYS_REG_H_    

#define SYS_BASE_ADDR   0xF000          //SYS reg. base address start from 0xF000H

#define PMU             ((unsigned char volatile xdata *) 0)        [0xF000]
#define TXDMUX          ((unsigned char volatile xdata *) 0)        [0xF001]
#define I2C_S_ADDR      ((unsigned char volatile xdata *) 0)        [0xF002]
#define I2C_S_CTRL      ((unsigned char volatile xdata *) 0)        [0xF003]
#define PUEN0           ((unsigned char volatile xdata *) 0)        [0xF004]
#define PUEN1           ((unsigned char volatile xdata *) 0)        [0xF005]
#define LVDATRM         ((unsigned char volatile xdata *) 0)        [0xF006]
#define LVDCTL          ((unsigned char volatile xdata *) 0)        [0xF007]
#define LVDSTA          ((unsigned char volatile xdata *) 0)        [0xF008]
#define SYSCLK          ((unsigned char volatile xdata *) 0)        [0xF009]                        
#define RXDMUX          ((unsigned char volatile xdata *) 0)        [0xF00D]
#define ISPCLK_MUX      ((unsigned char volatile xdata *) 0)        [0xF00E]
#define ISPDAT_MUX      ((unsigned char volatile xdata *) 0)        [0xF00F]
#define SYSMISC         ((unsigned char volatile xdata *) 0)        [0xF010]
#define MISC_E51EFEN    ((unsigned char volatile xdata *) 0)        [0xF011]
#define MISC_E51GRP     ((unsigned char volatile xdata *) 0)        [0xF012]
#define FWREG           ((unsigned char volatile xdata *) 0)        [0xF018]
#define MSKVER          ((unsigned char volatile xdata *) 0)        [0xF019]
#define PKGVER          ((unsigned char volatile xdata *) 0)        [0xF01A]
#define TRAPSTA         ((unsigned char volatile xdata *) 0)        [0xF01B]
#define CHIPIDH         ((unsigned char volatile xdata *) 0)        [0xF01C]
#define CHIPIDL         ((unsigned char volatile xdata *) 0)        [0xF01D]
#define MISC_MACPA      ((unsigned char volatile xdata *) 0)        [0xF02A]
#define CMP_PD          ((unsigned char volatile xdata *) 0)        [0xF02B]
#define MBIST           ((unsigned char volatile xdata *) 0)        [0xF02C]
#define ISPST           ((unsigned char volatile xdata *) 0)        [0xF02F]
#define OSC32PA         ((unsigned char volatile xdata *) 0)        [0xF030]
#define PWM_PUEN        ((unsigned char volatile xdata *) 0)        [0xF031]
#define SCANCLK_DIV     ((unsigned char volatile xdata *) 0)        [0xF032]
#define I2C_M_EN        ((unsigned char volatile xdata *) 0)        [0xF033]
#define MISC_REG0X34    ((unsigned char volatile xdata *) 0)        [0xF034]
#define ADC_CTL1        ((unsigned char volatile xdata *) 0)        [0xF035]
#define ADC_CTL2        ((unsigned char volatile xdata *) 0)        [0xF036]
#define ADC_PF          ((unsigned char volatile xdata *) 0)        [0xF037]
#define ADC_DAT0        ((unsigned char volatile xdata *) 0)        [0xF038]
#define ADC_DAT1        ((unsigned char volatile xdata *) 0)        [0xF039]  
#define ADC_CTL3        ((unsigned char volatile xdata *) 0)        [0xF03A]
#define MAC_OPT         ((unsigned char volatile xdata *) 0)        [0xF047]

#endif  //_SYS_REG_H_


/***************************************************************************************
* Description  : _REG_REG_H_ Macro definitions                                         *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _WDT_REG_H
#define _WDT_REG_H

#define WDT_BASE_ADDR   0xF100          //WDT reg. base address start from 0xF100H

#define WDTCFG          ((unsigned char volatile xdata *) 0)        [0xF100]
#define WDTPF           ((unsigned char volatile xdata *) 0)        [0xF101]    
#define WDTVAL          ((unsigned char volatile xdata *) 0)        [0xF102]

#endif  //_WDT_REG_H


/***************************************************************************************
* Description  : _GPIO_REG_H_ Macro definitions                                        *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _GPIO_REG_H
#define _GPIO_REG_H

#define GPIO_BASE_ADDR  0xF200          //GPIO reg. base address start from 0xF200H

#define  GPIOMD         ((unsigned char volatile xdata *) 0) [0xF200]       //GPIO 24~27 / PWM 0~3 mode select
#define  GPIOOE0        ((unsigned char volatile xdata *) 0) [0xF202]       //GPIO  0~7  output enable
#define  GPIOOE1        ((unsigned char volatile xdata *) 0) [0xF203]       //GPIO  8~15 output enable
#define  GPIOOE2        ((unsigned char volatile xdata *) 0) [0xF204]       //GPIO 16~23 output enable
#define  GPIOOE3        ((unsigned char volatile xdata *) 0) [0xF205]       //GPIO 24~31 output enable
#define  GPIOOE4        ((unsigned char volatile xdata *) 0) [0xF206]       //GPIO 32~35 output enable
#define  GPIODO0        ((unsigned char volatile xdata *) 0) [0xF207]       //GPIO  0~7  output data
#define  GPIODO1        ((unsigned char volatile xdata *) 0) [0xF208]       //GPIO  8~15 output data
#define  GPIODO2        ((unsigned char volatile xdata *) 0) [0xF209]       //GPIO 16~23 output data
#define  GPIODO3        ((unsigned char volatile xdata *) 0) [0xF20A]       //GPIO 24~31 output data
#define  GPIODO4        ((unsigned char volatile xdata *) 0) [0xF20B]       //GPIO 32~35 output data
#define  GPIOIE0        ((unsigned char volatile xdata *) 0) [0xF20C]       //GPIO  0~7  intput enable
#define  GPIOIE1        ((unsigned char volatile xdata *) 0) [0xF20D]       //GPIO  8~15 intput enable
#define  GPIOIE2        ((unsigned char volatile xdata *) 0) [0xF20E]       //GPIO 16~23 intput enable
#define  GPIOIE3        ((unsigned char volatile xdata *) 0) [0xF20F]       //GPIO 24~31 intput enable
#define  GPIOIE4        ((unsigned char volatile xdata *) 0) [0xF210]       //GPIO 32~35 intput enable
#define  GPIODI0        ((unsigned char volatile xdata *) 0) [0xF211]       //GPIO  0~7  input data
#define  GPIODI1        ((unsigned char volatile xdata *) 0) [0xF212]       //GPIO  8~15 input data
#define  GPIODI2        ((unsigned char volatile xdata *) 0) [0xF213]       //GPIO 16~23 input data
#define  GPIODI3        ((unsigned char volatile xdata *) 0) [0xF214]       //GPIO 24~31 input data
#define  GPIODI4        ((unsigned char volatile xdata *) 0) [0xF215]       //GPIO 32~35 input data
#define  PWMLN0         ((unsigned char volatile xdata *) 0) [0xF220]
#define  PWMDT0         ((unsigned char volatile xdata *) 0) [0xF221]
#define  PWMLN1         ((unsigned char volatile xdata *) 0) [0xF222]
#define  PWMDT1         ((unsigned char volatile xdata *) 0) [0xF223]
#define  PWMLN2         ((unsigned char volatile xdata *) 0) [0xF224]
#define  PWMDT2         ((unsigned char volatile xdata *) 0) [0xF225]
#define  PWMLN3         ((unsigned char volatile xdata *) 0) [0xF226]
#define  PWMDT3         ((unsigned char volatile xdata *) 0) [0xF227]
#define  GPIOE12_0      ((unsigned char volatile xdata *) 0) [0xF228]       //GPIO  0~7  STRH
#define  GPIOE12_1      ((unsigned char volatile xdata *) 0) [0xF229]       //GPIO  8~15 STRH
#define  GPIOE12_2      ((unsigned char volatile xdata *) 0) [0xF22A]       //GPIO 16~23 STRH
#define  GPIOE12_3      ((unsigned char volatile xdata *) 0) [0xF22B]       //GPIO 24~31 STRH
#define  GPIOE12_4      ((unsigned char volatile xdata *) 0) [0xF22C]       //GPIO 32~35 STRH
#define  PWMOD          ((unsigned char volatile xdata *) 0) [0xF22D]       //PWM 0~3 open-drain output control
#define  PWMCLK         ((unsigned char volatile xdata *) 0) [0xF22E]       //PWM clock select
#define  GPWUA0         ((unsigned char volatile xdata *) 0) [0xF230]
#define  GPWUA1         ((unsigned char volatile xdata *) 0) [0xF231]
#define  GPWUPF         ((unsigned char volatile xdata *) 0) [0xF232]       //GPWU pending flag of GPIO 0~1 & 32~33

#endif //_GPIO_REG_H


/***************************************************************************************
* Description  : _LED_REG_H_ Macro definitions                                         *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
#ifndef _LED_REG_H
#define _LED_REG_H

#define LED_BASE_ADDR   0xF300          //LED reg. base address start from 0xF300H

#define LEDSET          ((unsigned char volatile xdata *) 0) [0xF300]
#define LEDCLKDIV       ((unsigned char volatile xdata *) 0) [0xF301]
#define LEDPWM          ((unsigned char volatile xdata *) 0) [0xF302]
#define LEDCOMEN        ((unsigned char volatile xdata *) 0) [0xF303]
#define LEDSEGC0        ((unsigned char volatile xdata *) 0) [0xF304]
#define LEDSEGC1        ((unsigned char volatile xdata *) 0) [0xF305]
#define LEDSEGC2        ((unsigned char volatile xdata *) 0) [0xF306]
#define LEDSEGC3        ((unsigned char volatile xdata *) 0) [0xF307]
#define LEDSEGC4        ((unsigned char volatile xdata *) 0) [0xF308]
#define LEDSEGC5        ((unsigned char volatile xdata *) 0) [0xF309]
#define LEDSEGC6        ((unsigned char volatile xdata *) 0) [0xF30A]
#define LEDEXCOMEN      ((unsigned char volatile xdata *) 0) [0xF30B]
#define LEDSEGC7        ((unsigned char volatile xdata *) 0) [0xF30C]
#define LEDSEGC8        ((unsigned char volatile xdata *) 0) [0xF30D]
#define LEDSEGC9        ((unsigned char volatile xdata *) 0) [0xF30E]
#define LEDSEGC10       ((unsigned char volatile xdata *) 0) [0xF30F]
#define LEDSEGC11       ((unsigned char volatile xdata *) 0) [0xF310]
#define LEDSEGC12       ((unsigned char volatile xdata *) 0) [0xF311]
#define LEDSEGC13       ((unsigned char volatile xdata *) 0) [0xF312]


#endif  //_LED_REG_H


/***************************************************************************************
* Description  : _SCAN_REG_H_ Macro definitions                                        *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
#ifndef _SCAN_REG_H_
#define _SCAN_REG_H_

#define SCAN_BASE_ADDR  0xFA00          //SCAN reg. base address start from 0xFA00H

#define  CHGCYC         ((unsigned char volatile xdata *) 0) [0xFA00]       //
#define  TRNCYC         ((unsigned char volatile xdata *) 0) [0xFA01]       //
#define  IDLECYC        ((unsigned char volatile xdata *) 0) [0xFA02]       //
#define  COMPDEB        ((unsigned char volatile xdata *) 0) [0xFA03]       //
#define  COMPDEBCTRL    ((unsigned char volatile xdata *) 0) [0xFA04]       //
#define  SCANWIN        ((unsigned char volatile xdata *) 0) [0xFA05]       //
#define  WINCTRL        ((unsigned char volatile xdata *) 0) [0xFA06]       //
#define  SCANRESCTRL    ((unsigned char volatile xdata *) 0) [0xFA07]       //
#define  RSTCYC         ((unsigned char volatile xdata *) 0) [0xFA08]       //
#define  SETUPCYC       ((unsigned char volatile xdata *) 0) [0xFA09]       //
#define  SCAN_REG_X0A   ((unsigned char volatile xdata *) 0) [0xFA0A]       //
#define  REXTCTRL       ((unsigned char volatile xdata *) 0) [0xFA0B]       //
#define  SHIELDCTRL     ((unsigned char volatile xdata *) 0) [0xFA0C]       //
#define  SCANCTRL       ((unsigned char volatile xdata *) 0) [0xFA0D]       //
#define  PORTEN0        ((unsigned char volatile xdata *) 0) [0xFA17]       //~1A     port 0~24 scan enable
#define  PORTEN1        ((unsigned char volatile xdata *) 0) [0xFA18]       //~1A     port 0~24 scan enable
#define  PORTEN2        ((unsigned char volatile xdata *) 0) [0xFA19]       //~1A     port 0~24 scan enable
#define  PORTEN3        ((unsigned char volatile xdata *) 0) [0xFA1A]       //~1A     port 0~24 scan enable
#define  SHIELDEN0      ((unsigned char volatile xdata *) 0) [0xFA1B]       //~1E     port 0~24 shielding enable
#define  SHIELDEN1      ((unsigned char volatile xdata *) 0) [0xFA1C]       //~1E     port 0~24 shielding enable
#define  SHIELDEN2      ((unsigned char volatile xdata *) 0) [0xFA1D]       //~1E     port 0~24 shielding enable
#define  SHIELDEN3      ((unsigned char volatile xdata *) 0) [0xFA1E]       //~1E     port 0~24 shielding enable
#define  SCAN_REG_X1F   ((unsigned char volatile xdata *) 0) [0xFA1F]       //
#define  SCANMODEN      ((unsigned char volatile xdata *) 0) [0xFA20]       //
#define  INTEN          ((unsigned char volatile xdata *) 0) [0xFA22]       //        Interrupt enable
#define  PENDFLAG       ((unsigned char volatile xdata *) 0) [0xFA23]       //        pending flag
#define  FIFOST0        ((unsigned char volatile xdata *) 0) [0xFA35]       //        Scan FIFO status
#define  FIFOST1        ((unsigned char volatile xdata *) 0) [0xFA36]       //        port pointer
#define  CURRDRES0      ((unsigned char volatile xdata *) 0) [0xFA37]       //        current read scan result [7:0]
#define  CURRDRES1      ((unsigned char volatile xdata *) 0) [0xFA38]       //        current read scan result [15:0]
#define  CURRDRES2      ((unsigned char volatile xdata *) 0) [0xFA39]       //        current read scan result overflow

#endif //_SCAN_REG_H_


