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
* File Name    : TK_UART.c                                                                                     *             
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
#include "TK_UART.h"
#include <intrins.h>        //for _nop_();


/***************************************************************
Constant data & variables definitions                          *
***************************************************************/


//------Variable declaration------------



#if (SYS_UART_ENABLE)
/***************************************************************
* Function Name: ctm_uart_init                                 *
* Description  : Initial UART H.W.                             *
* Arguments    : None                                          *          
* Return Value : None                                          *                                                 
* Remark       :                                               *  
***************************************************************/
void ctm_uart_init()
{
    drv_serial_port_init(BAUD_RATE, TX_GPIO_CH, RX_GPIO_CH);    //Set Baud-Rate, TX CH &  RX CH.
//using interrupt
    TI = 0;
    ES = 1;
//using polling
//  ES = 0;
//  TI = 1;
    
    ctm_uart_start_TX();                                        //TXD start !
}

/***************************************************************
* Function Name: ctm_uart_TX_sample                            *
* Description  : TX processing                                 *
* Arguments    : None                                          *          
* Return Value : None                                          *                                                 
* Remark       :                                               *  
***************************************************************/
code U8 uart_sample_data[6] = {'H','E','L','L','O','!'};
xdata U8 uart_ptr;
void ctm_uart_TX_sample()
{
    if(uart_ptr)
    {
        SBUF = uart_sample_data[uart_ptr++];
        if(uart_ptr >= 6)
            uart_ptr = 0;
    }
}

/***************************************************************
* Function Name: ctm_uart_start_TX                             *
* Description  : TX start                                      *
* Arguments    : None                                          *          
* Return Value : None                                          *                                                 
* Remark       :                                               *  
***************************************************************/
void ctm_uart_start_TX()
{
//using interrupt
    SBUF = uart_sample_data[uart_ptr++];
//using polling
//  putchar( uart_sample_data[0]);
//  putchar( uart_sample_data[1]);
//  putchar( uart_sample_data[2]);
//  putchar( uart_sample_data[3]);
}

/***************************************************************
* Function Name: com_uart_interrupt                            *
* Description  : Int. RI/TI(0023h), UART ISR, address is 0x04  *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       : Using WK reg. BANK#1                          *
***************************************************************/
void com_uart_interrupt(void) interrupt 0x04 using 1
{
    //TXD ISR processing !
    if(TI)
    {
        TI = 0;
        ctm_uart_TX_sample();
    }

    //RXD ISR processing !
    if(RI)
    {
        RI = 0;
    }
}

#endif

