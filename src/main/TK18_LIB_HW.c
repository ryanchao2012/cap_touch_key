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
* File Name    : TK18_LIB_HW.c                                                                                 *             
* Version      : Lib v300                                                                                      *
* Device(s)    : ENE TK18 serial MCU.                                                                          *             
* Description  : H.W. related function code.                                                                   *             
* Creation Date: 2015/02/06                                                                                    *
***************************************************************************************************************/             
 
//------INCLUDE define------------------
#include <TK_MCU_DEF.h>
#include <TK18_LIB_API.h>
#include <TK18_LIB_REG.h>
#include <TK18_LIB_HW.h>
#include <ctm_sample.h>

/***************************************************************************************
* Description  : System related functions & constant data definitions                  *
* Creation Date: 2015/02/06                                                            *
* Remark       : Constant data location from code-address 0x1000)                      *
***************************************************************************************/
code U8 code_date_str[12]           = __DATE__;                 //0x1000
code U8 code_time_str[8]            = __TIME__;                 //0x100C ~ 0x1013
code U8 code_ap_modify_time[4]      = {0};                      //0x1014 ~ 0x1017
code U8 code_fw_function_ctrl[8]    = {0};                      //0x1018 ~ 0x101F
code U8 code_ctm_ver[5]             = {CUSTOMER_VERSION};       //0x1020 ~ 0x1024

/***************************************************************************************
* <<<Important!!!>>>                                                                   *
* Do not modify the following global variables, otherwise LIB can't work.              *
*                                                                                      *
***************************************************************************************/
code U16 code_dummy_crazy_th = 0;

xdata volatile U16      uwREG_RawCnt[REAL_BUTTON_SIZE]           _at_    TOOL_DEFINE_ADDRESS_RAWCNT;
xdata volatile U16      uwREG_RawCnt_Backup[REAL_BUTTON_SIZE]    _at_    TOOL_DEFINE_ADDRESS_BACKUP;
xdata volatile S16      swKNL_SignalArray[REAL_BUTTON_SIZE]      _at_    TOOL_DEFINE_ADDRESS_FWSIGNAL;
xdata volatile U8       ucCTM_ButtonTable[REAL_BUTTON_SIZE]      _at_    TOOL_DEFINE_ADDRESS_BTNTABLE;
xdata volatile S16      raw_count_fh1_offset[REAL_BUTTON_SIZE];              
xdata volatile S16      raw_count_fh2_offset[REAL_BUTTON_SIZE];
xdata volatile U16      uwKNL_PreRawCount[REAL_BUTTON_SIZE];
xdata volatile U8       ucPortHigh[REAL_BUTTON_SIZE];
xdata volatile U8       knl_acc_counter[REAL_BUTTON_SIZE];
xdata volatile U8       ucKNL_ButtonOnOffDBS[REAL_BUTTON_SIZE];
xdata volatile U32      uw_knl_swIIR_rawcnt[REAL_BUTTON_SIZE];
xdata volatile U8       uc_knl_swIIR_ptr[REAL_BUTTON_SIZE]; 
#if (DRV_ENABLE_COVER_FILTER)
xdata volatile U16      uwREG_RawCnt_Saved[REAL_BUTTON_SIZE]; 
#endif 

/***************************************************************
* Function Name: drv_ISP_Link                                  *
* Description  : To connect X-ANA with ISP interface           *
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/    
void drv_ISP_Link(void)
{
    drv_timer_init(TIMER0, 1000);                               // Enable & Start Timer0 Int. period is 1mS.
    uc_knl_timer0_1ms_counter = 0;

    //delay 100mS to connect X-ANA with ISP
    while(uc_knl_timer0_1ms_counter < 100)
    {
        //ISP CH. is connected with X-ANA ?
        if (MISC_E51GRP == 0x89)
        {
            return;
        }
    }

#if (USER_ISP_CH_ENABLE)
    //customer also can switch ISP CH. to any GPIO as you wish.
    if (! (MISC_E51GRP == 0x89))
    {
        ISPCLK_MUX = USER_ISP_CLK_CH;                           //Switch CLK ISP CH. to user defined
        ISPDAT_MUX = USER_ISP_DAT_CH;                           //Switch DAT ISP CH. to user defined.
        uc_knl_timer0_1ms_counter = 0;

        //delay 100mS to connect X-ANA with ISP
        while(uc_knl_timer0_1ms_counter < 100)
        {
            //ISP CH. is connected with X-ANA ?
            if (MISC_E51GRP == 0x89)
            {
                return;
            }
        }
    }
#endif
}


/***************************************************************************************
* Description  : TIMER related functions & constant data definitions                   *
* Creation Date: 2015/02/06                                                            *
***************************************************************************************/
xdata volatile U8       ucCOM_Timer1_Counter;     
xdata volatile U8       uc_knl_timer0_1ms_counter;
xdata volatile U8       ctm_timer_125uS_counter;


/***************************************************************          
* Function Name: ctm_timer_init                                *          
* Description  : TIMER 0 & 1 initial.                          *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       :                                               *          
***************************************************************/          
void ctm_timer_init(void)
{
    drv_timer_init(TIMER0, TIMER0_PERIOD_US);                   // Set Timer0 Int. period & START it !
///FW. test function ?
#if (FW_TEST_ENABLE)
    drv_timer_init(TIMER1, TIMER1_PERIOD_US);                   // Set Timer1 Int. period & START it !
#endif


}


/***************************************************************          
* Function Name: com_timer0_interrupt                          *          
* Description  : Int. TF0(000Bh), timer0 ISR, address is 0x01  *          
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       : Using WK reg. BANK#1                          *          
***************************************************************/          
void com_timer0_interrupt(void) interrupt 0x01 using 1
    {
        drv_reload_timer0();                                        //reload timer0.
        uc_knl_timer0_1ms_counter++;                                //DO NOT delete this line otherwise drv_ISP_Link() can't work.
    
        ctm_timer_1ms_counter++;                                    //Update 1mS time counter.
 //       backlight_time++;                                           //Update back-light time.
    
        //Update Buzzer on time!
        if (uc_ctm_Buzzer_timer)
        {
            uc_ctm_Buzzer_timer--;
            if ( !(uc_ctm_Buzzer_timer) ) {
                BUZZER_DI();                                        //Turn off buzzer
				ET0 = 0;
				TR0 = 0;
			}
        }
    }



/***************************************************************          
* Function Name: com_timer1_interrupt                          *          
* Description  : Int. TF1(001Bh), timer1 ISR, address is 0x03  *
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       : Using WK reg. BANK#1                          *          
***************************************************************/          
void com_timer1_interrupt(void) interrupt 0x03 using 1   
{
    drv_reload_timer1();                                        //reload timer1.
    ucCOM_Timer1_Counter++;                                     //DO NOT delete this line otherwise fw_test() can't work

}


/***************************************************************************************
* Description  : Touch Key related functions & constant data definitions               *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/
//---Parameter table for CS Filter------
code U8 code_scan_parameter_mask = 3;
code U8 code_scan_parameter_table[3][3] =
{
//  S0          S1          ScanWin
    TK_S0_0,    TK_S1_0,    TK_WIN_0,       // (S0_Value+S1_Value) + 2 = 9
    TK_S0_1,    TK_S1_1,    TK_WIN_1,       // (S0_Value+S1_Value) + 2 = 11
    TK_S0_2,    TK_S1_2,    TK_WIN_2,       // (S0_Value+S1_Value) + 2 = 13
};

//---Constant data for RF Filter--------
code U8  code_RF_dummy_threshold =      DRV_RF_DUMMY_THRESHOLD;
code U8  code_RF_dummy_debounce  =      DRV_RF_DUMMY_DEBOUNCE;

//---Constant data for Cover checking---
code U8  code_COVER_max_btn_trigger =   DRV_COVER_MAX_BUTTON_TRIGGER;
code U16 code_COVER_rebase_cycle    =   DRV_COVER_REBASE_CYCLE;

//---Constant data for IIR Filter-------
code U16 code_IIR_NOISE_TH_NORMAL   =   DRV_IIR_NOISE_TH_NORMAL;
code U16 code_IIR_NOISE_TH_WATER_ON =   DRV_IIR_NOISE_TH_WATER_ON;

//---Constant data for WATER Filter-----
code U8  code_WATER_MAX_COUNTER =       DRV_WATER_MAX_COUNTER;

//---Constant data for TK setup---------
code U8  code_ctm_Button_table[] =      {CTM_BUTTON_MAPPING_TABLE};
code U8  code_on_debounce_times  =      CTM_BUTTON_ON_DBS_CNTS;
code U8  code_off_debounce_times =      CTM_BUTTON_OFF_DBS_CNTS;
code U8  code_dummy_port_num     =      CTM_DUMMY_PORTNUM;
code U8  code_off_threshold_rate =      CTM_OFF_THRESHOLD_RATE;

//---Constant data for shielding setup--
#if (CTM_SHIELDING_SIZE != 0)
code U8  code_ctm_Shielding_table[CTM_SHIELDING_SIZE] = {CTM_SHIELDING_TABLE};
#else
code U8  code_ctm_Shielding_table[1] =  0xFF;
#endif
code U8  code_ctm_Shielding_Size =      CTM_SHIELDING_SIZE;
code U16 code_uw_fh_max_value = 500;

//---Initial table for SCAN reg. 0xFA00~0xFA1F------------------
code U8 code_scan_init_table[0x20] =                               
{
//  FA00,   FA01,   FA02,   FA03,   FA04,   FA05,   FA06,   FA07,
    TK_S0,  TK_S1,  0x00,   0x00,   0x55,   TK_WIN, 0x00,   0x55,
//  FA08,   FA09,   FA0A,   FA0B,   FA0C,   FA0D,   FA0E,   FA0F,
    0xFF,   0xFF,   0x00,   0x01,   0x02,   0x00,   0xFF,   0xFF,
//  FA10,   FA11,   FA12,   FA13,   FA14,   FA15,   FA16,   FA17,
    0xFF,   0xFF,   0xFF,   0xFF,   0xFF,   0xFF,   0xFF,   0x00,
//  FA18,   FA19,   FA1A,   FA1B,   FA1C,   FA1D,   FA1E,   FA1F
    0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0x00,   0xFF
};

//---Finger Threshold table for all TK port--------------------- 
code S16 code_uwKNL_1stThreshold[DRV_SCAN_MAX_PORTS] =                      
{
//  TK0                             TK1                             TK2                             TK3
    (TK0_F_SIGNAL*FINGER_RATE),     (TK1_F_SIGNAL*FINGER_RATE),     (TK2_F_SIGNAL*FINGER_RATE),     (TK3_F_SIGNAL*FINGER_RATE),
//  TK4                             TK5                             TK6                             TK7
    (TK4_F_SIGNAL*FINGER_RATE),     (TK5_F_SIGNAL*FINGER_RATE),     (TK6_F_SIGNAL*FINGER_RATE),     (TK7_F_SIGNAL*FINGER_RATE),
//  TK8                             TK9                             TK10                            TK11
    (TK8_F_SIGNAL*FINGER_RATE),     (TK9_F_SIGNAL*FINGER_RATE),     (TK10_F_SIGNAL*FINGER_RATE),    (TK11_F_SIGNAL*FINGER_RATE),
//  TK12                            TK13                            TK14                            TK15
    (TK12_F_SIGNAL*FINGER_RATE),    (TK13_F_SIGNAL*FINGER_RATE),    (TK14_F_SIGNAL*FINGER_RATE),    (TK15_F_SIGNAL*FINGER_RATE),
//  TK16                            TK17                            TK18                            TK19
    (TK16_F_SIGNAL*FINGER_RATE),    (TK17_F_SIGNAL*FINGER_RATE),    (TK18_F_SIGNAL*FINGER_RATE),    (TK19_F_SIGNAL*FINGER_RATE),
//  TK20                            TK21                            TK22                            TK23
    (TK20_F_SIGNAL*FINGER_RATE),    (TK21_F_SIGNAL*FINGER_RATE),    (TK22_F_SIGNAL*FINGER_RATE),    (TK23_F_SIGNAL*FINGER_RATE),
//  DUMMY                           TK25                            TK26                            TK27  
    (TK24_F_SIGNAL*FINGER_RATE),    (TK25_F_SIGNAL*FINGER_RATE),    (TK26_F_SIGNAL*FINGER_RATE),    (TK27_F_SIGNAL*FINGER_RATE),
//  TK28    
    (TK28_F_SIGNAL*FINGER_RATE)
};

//---Noise Threshold table for all TK port----------------------
code S16 code_fast_IIR_threshold[DRV_SCAN_MAX_PORTS] =
{ 
//  TK0                             TK1                             TK2                             TK3
    (TK0_F_SIGNAL*IIR_RATE),        (TK1_F_SIGNAL*IIR_RATE),        (TK2_F_SIGNAL*IIR_RATE),        (TK3_F_SIGNAL*IIR_RATE),
//  TK4                             TK5                             TK6                             TK7
    (TK4_F_SIGNAL*IIR_RATE),        (TK5_F_SIGNAL*IIR_RATE),        (TK6_F_SIGNAL*IIR_RATE),        (TK7_F_SIGNAL*IIR_RATE),
//  TK8                             TK9                             TK10                            TK11
    (TK8_F_SIGNAL*IIR_RATE),        (TK9_F_SIGNAL*IIR_RATE),        (TK10_F_SIGNAL*IIR_RATE),       (TK11_F_SIGNAL*IIR_RATE),
//  TK12                            TK13                            TK14                            TK15
    (TK12_F_SIGNAL*IIR_RATE),       (TK13_F_SIGNAL*IIR_RATE),       (TK14_F_SIGNAL*IIR_RATE),       (TK15_F_SIGNAL*IIR_RATE),
//  TK16                            TK17                            TK18                            TK19
    (TK16_F_SIGNAL*IIR_RATE),       (TK17_F_SIGNAL*IIR_RATE),       (TK18_F_SIGNAL*IIR_RATE),       (TK19_F_SIGNAL*IIR_RATE),
//  TK20                            TK21                            TK22                            TK23
    (TK20_F_SIGNAL*IIR_RATE),       (TK21_F_SIGNAL*IIR_RATE),       (TK22_F_SIGNAL*IIR_RATE),       (TK23_F_SIGNAL*IIR_RATE),
//  DUMMY                           TK25                            TK26                            TK27
    (TK24_F_SIGNAL*IIR_RATE),       (TK25_F_SIGNAL*IIR_RATE),       (TK26_F_SIGNAL*IIR_RATE),       (TK27_F_SIGNAL*IIR_RATE),
//  TK28    
    (TK28_F_SIGNAL*IIR_RATE)
};

//---Water Threshold table for all TK port----------------------
code S16 code_check_water_threshold[DRV_SCAN_MAX_PORTS] =
{
//  TK0                             TK1                             TK2                             TK3
    (TK0_F_SIGNAL*WATER_RATE),      (TK1_F_SIGNAL*WATER_RATE),      (TK2_F_SIGNAL*WATER_RATE),      (TK3_F_SIGNAL*WATER_RATE),
//  TK4                             TK5                             TK6                             TK7
    (TK4_F_SIGNAL*WATER_RATE),      (TK5_F_SIGNAL*WATER_RATE),      (TK6_F_SIGNAL*WATER_RATE),      (TK7_F_SIGNAL*WATER_RATE),
//  TK8                             TK9                             TK10                            TK11
    (TK8_F_SIGNAL*WATER_RATE),      (TK9_F_SIGNAL*WATER_RATE),      (TK10_F_SIGNAL*WATER_RATE),     (TK11_F_SIGNAL*WATER_RATE),
//  TK12                            TK13                            TK14                            TK15
    (TK12_F_SIGNAL*WATER_RATE),     (TK13_F_SIGNAL*WATER_RATE),     (TK14_F_SIGNAL*WATER_RATE),     (TK15_F_SIGNAL*WATER_RATE),
//  TK16                            TK17                            TK18                            TK19
    (TK16_F_SIGNAL*WATER_RATE),     (TK17_F_SIGNAL*WATER_RATE),     (TK18_F_SIGNAL*WATER_RATE),     (TK19_F_SIGNAL*WATER_RATE),
//  TK20                            TK21                            TK22                            TK23
    (TK20_F_SIGNAL*WATER_RATE),     (TK21_F_SIGNAL*WATER_RATE),     (TK22_F_SIGNAL*WATER_RATE),     (TK23_F_SIGNAL*WATER_RATE),
//  DUMMY                           TK25                            TK26                            TK27
    (TK24_F_SIGNAL*WATER_RATE),     (TK25_F_SIGNAL*WATER_RATE),     (TK26_F_SIGNAL*WATER_RATE),     (TK27_F_SIGNAL*WATER_RATE),
//  TK28    
    (TK28_F_SIGNAL*WATER_RATE)
};

xdata volatile U16 uwLib_version;                               //To save current Lib's version.
/***************************************************************
* Function Name: ctm_tk_init                                   *
* Description  : Customer's TK initail.                        *
* Arguments    : None                                          *
* Return Value : None                                          *
* Remark       :                                               *
***************************************************************/
void ctm_tk_init(void)
{
    U8 i;
    uwLib_version = drv_get_lib_version();                      //Get API's version.
    //Get active TK port's number.
    for(i=0; i < sizeof(code_ctm_Button_table); i++)
        ucCTM_ButtonTable[i] = code_ctm_Button_table[i];
    ucKNL_Button_Size = sizeof(code_ctm_Button_table);          //get TK size.;
}

/***************************************************************************************
* Description  : LVDA related functions & constant data definitions                    *
* Creation Date: 2014/09/08                                                            *
***************************************************************************************/

/***************************************************************
* Function Name: ctm_lvda_interrupt                            *
* Description  : Int. P0I.3(005Bh), LVD ISR, address is 0x0B   *
* Arguments    : None                                          *          
* Return Value : None                                          *          
* Remark       : Using WK reg. BANK#1                          *
***************************************************************/ 
void ctm_lvda_interrupt(void) interrupt 0x0B using 1
{
    
}

