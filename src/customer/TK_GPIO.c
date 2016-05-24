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
* File Name    : TK_GPIO.c                                                                                     *             
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
#include "TK_GPIO.h"
#include "ctm_sample.h"


/***************************************************************
Constant data & variables definitions                          *
***************************************************************/

//------Variable declaration------------


#if (SYS_GPIO_ENABLE)
/***************************************************************
* Function Name: drv_set_gpio                                  *          
* Description  : GPIO output status implements !               *          
* Arguments    : U8 gpio_num                                   *          
*                bit0~5: GPIO0 ~ GPIO35 index.                 *
*                bit6  : 0= Push-Pull , 1= Open-Drain.         *
*                bit7  : 0= Active-low, 1= Active-high.        *
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/  
void drv_set_gpio(U8 gpio_num)
{
    U8 idx, bitN;

    idx = ((gpio_num & 0x3F) >> 3);                             //Get byte index.
    bitN = (0x01 << (gpio_num & 0x07));                         //Get bit  index.

    //Implements for Open-Drain type's output !
    if (gpio_num & GPIO_OPEN_DRAIN)
    {
        *( &GPIODO0 + (idx) ) &= ~bitN;                         //Preset Output buffer= Low.
        if (gpio_num & GPIO_ACTIVE_HIGH)
        {
            *( &GPIOOE0 + (idx) ) &= ~bitN;                     //Disable OE.
        }
        else
        {
            *( &GPIOOE0 + (idx) ) |= bitN;                      //Enable  OE.
        }
    }else
    //Implements for Push-Pull type's output!
    {                         
        if (gpio_num & GPIO_ACTIVE_HIGH)
        {
            *( &GPIODO0 +(idx) ) |= bitN;                       //Output High.
        }
        else
        {
            *( &GPIODO0 +(idx) ) &= ~bitN;                      //Output Low.
        }
        *( &GPIOOE0 + (idx) ) |= bitN;                          //Enable OE.
    }
}                              

/***************************************************************          
* Function Name: ctm_GPIO_init                                 *          
* Description  : Customer related code initial.                *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/
void ctm_GPIO_init()
{
	
	drv_set_gpio(LED1 | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);
	drv_set_gpio(LED2 | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);
	drv_set_gpio(LED3 | GPIO_PUSH_PULL | GPIO_ACTIVE_LOW);
	drv_set_gpio(TOUCHOUT | GPIO_PUSH_PULL | GPIO_ACTIVE_HIGH);
	
}


/***************************************************************
* Function Name: ctm_gpw_interrupt                             *
* Description  : Int. P0I.1(004Bh), GPW ISR, address is 0x09   *
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       : Using WK reg. BANK#1                          *
***************************************************************/          
void ctm_gpw_interrupt(void) interrupt 0x09 using 1
{

}
#endif

