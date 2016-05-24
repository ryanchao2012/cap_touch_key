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
* File Name    : TK_ADC.c                                                                                      *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* C51 Tools    : Keil C51 uVision V2.xx~V4.xx                                                                  *             
* Description  : This file implements the customer's function.                                                 *             
* Creation Date: 2015/04/24                                                                                    *
***************************************************************************************************************/

//------INCLUDE define------------------
#include <stdio.h>  
#include "TK_MCU_DEF.h"
#include "TK18_LIB_API.h"
#include "TK18_LIB_HW.h"
#include "TK18_LIB_REG.h"
#include "ctm_sample.h"
#include "TK_ADC.h"
#include <intrins.h>        //for _nop_();


#if (SYS_ADC_ENABLE)
/***************************************************************
Constant data & variables definitions                          *
***************************************************************/
//------Variable declaration------------
xdata U16   curr_adc_value = AD_VALUE_NULL;
xdata U16   adc_avg_value;
U16     Get_ADC(void);


/***************************************************************          
* Function Name: ctm_adc_init                                  *          
* Description  : Customer related code initial.                *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/         
void ctm_adc_init()
{
    //initial AD1
    P0IE4 = 0;                                                  //Disable TK18's ADC interrupt.
    ADC_CTL3 =  0x10;
    ADC_CTL1 =  0x03;                                           //ADC power-on initial enable, interrupt enabe
    ADC_CTL2 =  ADC1_EN + SELECT_ADC1 ;                         //Enable AD1, select ch1
    ADC_CTL2 |= ADC_CONVERT;                                    //Start convert first time
}


/***************************************************************
* Function Name: ADC_Proccess                                  *
* Description  : ADC adjust processing & display it.           *
* Arguments    :                                               *
* Return Value :                                               *
* Remark       : 25mS is coming in !                           *
***************************************************************/
void ADC_Process(void)
{
    static xdata U8  uc_ctm_adc_scna_period_timer;              //得到的AD采样值
    U16 temp;

    //Update ADC scan-period time.
    uc_ctm_adc_scna_period_timer += 1;
    if (uc_ctm_adc_scna_period_timer >= 2)                      //if 50mS(=25mS*2) is coming! then start to adjust ADC.
    {
        uc_ctm_adc_scna_period_timer = 0;
        ADC_CTL2 |= ADC_CONVERT;                                //Start convert first time

        //ADC adjustment is finished ?
        if (ADC_PF == 0x01)
        {
            ADC_PF = 0x01;                                      // clear pending flag
            if((( ADC_CTL2 & 0x0E) >> 1) == ADC1)                //判断为AD1 通道的数据
            {
                temp = (((U16) ADC_DAT0) << 8) | ADC_DAT1;
                temp &= 0x3FF;
                curr_adc_value = temp;                          //有效为变为10位AD
            }
            ADC_CTL2 &= ~0x01;                                  //disable ad 转换
            adc_avg_value = Get_ADC();
        }
    }
}


/***************************************************************
* Function Name: Get_ADC                                       *
* Description  : get current adc value                         *
* Arguments    :                                               *
* Return Value :                                               *
* Remark       : processed adc value                           *
***************************************************************/
U16 Get_ADC(void)
{
    U32 temp;
    U8  i;
    static BOOL first_ad = 0;
    static xdata U16 value = 0;
    static xdata U8  ad_cnt = 0;
    static xdata U16 ad_value[AD_REHEAT_CNT] = {0};

    if(curr_adc_value == AD_VALUE_NULL)
    {
        return AD_VALUE_NULL;
    }
    else
    {
        if(first_ad == 0)
        {
            first_ad = 1;
            value = curr_adc_value >> 2;
        }
        else
        {
            ad_value[ad_cnt] = curr_adc_value >> 2;             //adjust ADC result from 10-bit to 8-bit data.
            ad_cnt++;

            if(ad_cnt > AD_REHEAT_CNT)
            {
                ad_cnt = 0;
                temp = 0;
                for(i = 0;i < AD_REHEAT_CNT;i++)
                {
                    temp += ad_value[i];
                }
                value = (temp/AD_REHEAT_CNT);
            }           
        }
        return value;
    }
}



/***************************************************************
* Function Name: ctm_adc_interrupt                             *
* Description  : Int. P0I.4(0063h), ADC ISR, address is 0x0C   *
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       : curr_adc_value be updated !                   *
***************************************************************/          
void ctm_adc_interrupt(void) interrupt 0x0C using 1
{

}

#endif

