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
* File Name    : common.h                                                                                      * 
* Version      :                                                                                               * 
* Device(s)    : ENE TK18 serial MCU.                                                                          * 
* Description  : Data type & common symbol definition.                                                         * 
* Creation Date: 2014/09/08                                                                                    *
***************************************************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

//------INCLUDE define------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***************************************************************                                                         
Data type definitions                                          *                                                     
***************************************************************/                                                         
#ifndef BOOL
#define BOOL     bit
#endif

typedef unsigned char U8;
typedef unsigned short int U16;
typedef unsigned long U32;

typedef idata unsigned char iU8;
typedef idata unsigned short int iU16;
typedef idata unsigned long iU32;

typedef idata signed char iS8;
typedef idata signed short int iS16;
typedef idata signed long iS32;

typedef signed char S8;
typedef signed short int S16;
typedef signed long S32;

typedef volatile unsigned char vU8;
typedef volatile unsigned short int vU16;
typedef volatile unsigned long vU32;

typedef volatile signed char vS8;
typedef volatile signed short int vS16;
typedef volatile signed long vS32;

typedef union _WORD_COUNT
{
    vU16 count16;    
    vU8 count8[2];    
}WORD_COUNT, *P_WORD_COUNT;

#define BYTE        unsigned char
#define WORD        unsigned int


#define PXBYTE      unsigned char xdata *
#define PXWORD      unsigned int  xdata *

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define ABS(X)    ((X>=0) ? (X) : (-X)) 

//#define COUNTOF( array )    (sizeof(array) / sizeof((array)[0]))

typedef void (*lpVOIDFunction) (void *);
typedef void (*FUNCTION_PTR_V_V)(void);


/***************************************************************                                                         
Common symbol definitions                                      *                                                         
***************************************************************/                                                         
#ifndef ON 
#define ON              1
#endif 

#ifndef OFF
#define OFF             0
#endif

#ifndef TRUE
#define TRUE            1
#endif 

#ifndef FALSE
#define FALSE           0
#endif

#ifndef false
#define false           0
#endif

#ifndef true
#define true            1
#endif

#ifndef NULL
#define NULL            1
#endif

#ifndef DISABLE
#define DISABLE         0
#endif

#ifndef ENABLE
#define ENABLE          1
#endif

#ifndef NO
#define NO              0
#endif

#ifndef YES
#define YES             1
#endif

#ifndef NULL_POSITION
#define NULL_POSITION   0xFFFF
#endif

//------BIT index define----------------
#ifndef BIT0
#define BIT0            0x01
#endif

#ifndef BIT1
#define BIT1            0x02
#endif

#ifndef BIT2
#define BIT2            0x04
#endif

#ifndef BIT3
#define BIT3            0x08
#endif

#ifndef BIT4
#define BIT4            0x10
#endif

#ifndef BIT5
#define BIT5            0x20
#endif

#ifndef BIT6
#define BIT6            0x40
#endif

#ifndef BIT7
#define BIT7            0x80
#endif

#ifndef BIT8
#define BIT8            0x0100
#endif

#ifndef BIT9
#define BIT9            0x0200
#endif

#ifndef BIT10
#define BIT10           0x0400
#endif

#ifndef BIT11
#define BIT11           0x0800
#endif

#ifndef BIT12
#define BIT12           0x1000
#endif

#ifndef BIT13
#define BIT13           0x2000
#endif

#ifndef BIT14
#define BIT14           0x4000
#endif

#ifndef BIT15
#define BIT15           0x8000
#endif

#ifndef BIT16
#define BIT16           0x010000
#endif

#ifndef BIT17
#define BIT17           0x020000
#endif

#ifndef BIT18
#define BIT18           0x040000
#endif

#ifndef BIT19
#define BIT19           0x080000
#endif

#ifndef BIT20
#define BIT20           0x100000
#endif

#ifndef BIT21
#define BIT21           0x200000
#endif

#ifndef BIT22
#define BIT22           0x400000
#endif

#ifndef BIT23
#define BIT23           0x800000
#endif

#ifndef BIT24
#define BIT24           0x01000000
#endif

#ifndef BIT25
#define BIT25           0x02000000
#endif

#ifndef BIT26
#define BIT26           0x04000000
#endif

#ifndef BIT27
#define BIT27           0x08000000
#endif

#ifndef BIT28
#define BIT28           0x10000000
#endif

#ifndef BIT29
#define BIT29           0x20000000
#endif

#ifndef BIT30
#define BIT30           0x40000000
#endif

#ifndef BIT31
#define BIT31           0x80000000
#endif

//------MASK bit define-----------------
#define MSK_1_BIT       0x0001
#define MSK_2_BIT       0x0003
#define MSK_3_BIT       0x0007
#define MSK_4_BIT       0x000F
#define MSK_5_BIT       0x001F
#define MSK_6_BIT       0x003F
#define MSK_7_BIT       0x007F
#define MSK_8_BIT       0x00FF
#define MSK_9_BIT       0x01FF
#define MSK_10_BIT      0x03FF
#define MSK_11_BIT      0x07FF
#define MSK_12_BIT      0x0FFF
#define MSK_13_BIT      0x1FFF
#define MSK_14_BIT      0x3FFF
#define MSK_15_BIT      0x7FFF
#define MSK_16_BIT      0xFFFF

//------GPIO No. define-----------------
enum
{
    GPIO0 = 0,
    GPIO1,
    GPIO2,
    GPIO3,
    GPIO4,
    GPIO5,
    GPIO6,
    GPIO7,
    GPIO8,
    GPIO9,
    GPIO10,
    GPIO11,
    GPIO12,
    GPIO13,
    GPIO14,
    GPIO15,
    GPIO16,
    GPIO17,
    GPIO18,
    GPIO19,
    GPIO20,
    GPIO21,
    GPIO22,
    GPIO23,
    GPIO24,
    GPIO25,
    GPIO26,
    GPIO27,
    GPIO28,
    GPIO29,
    GPIO30,
    GPIO31,
    GPIO32,
    GPIO33,
    GPIO34,
    GPIO35,
};

//------TK CH. define-------------------
enum
{
    TK0 = 0,
    TK1,
    TK2,
    TK3,
    TK4,
    TK5,
    TK6,
    TK7,
    TK8,
    TK9,
    TK10,
    TK11,
    TK12,
    TK13,
    TK14,
    TK15,
    TK16,
    TK17,
    TK18,
    TK19,
    TK20,
    TK21,
    TK22,
    TK23,
    TK24,
    TK25,
    TK26,
    TK27,
    TK28,
};

enum
{
    MP0 = 0,
    MP1,
    MP2,
    MP3,
    MP4,
    MP5,
    MP6,
    MP7,
    MP8,
    MP9,
    MP10,
    MP11,
    MP12,
    MP13,
    MP14,
    MP15,
    MP16,
    MP17,
    MP18,
    MP19,
    MP20,
    MP21,
    MP22,
    MP23,
    MP24,
    MP25,
    MP26,
    MP27,
    MP28,
};

//------Global define-------------------
#define IDX(a)                          (((a) & 0x3F) >> 3)
#define BIT_N(a)                        (0x01 << ((a) & 0x07))
#define clr_bit(sfr, bit)               (sfr &= ~(1 << bit))
#define set_bit(sfr, bit)               (sfr |=  (1 << bit))
#define reverse_bit(sfr, bit)           (sfr ^=  (1 << bit))
#define check_bit(sfr, bit)             (sfr &   (1 << bit))

#endif //_COMMON_H_

