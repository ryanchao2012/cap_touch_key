//**********************************************************************************
//
//  Copyright (c) 2013-2019 ENE Technology, Inc.
//  All rights reserved.
//
//  EnE reserves the right to amend this code without notice at any time.
//  EnE assumes no responsibility for any errors appeared in the code,
//  and EnE disclaims any express or implied warranty, relating to sale
//  and/or use of this code including liability or warranties relating
//  to fitness for a particular purpose, or infringement of any patent,
//  copyright or other intellectual property right.
//
//
//**********************************************************************************

#include <intrins.h>  //for _nop_();
#include "Common.h"
#include "TK_I2C_Master.h"
#include "TK18_LIB_HW.h"
#include "TK18_LIB_REG.h"
#include "ctm_sample.h"

#if(HW_TK18_I2C_MASTER_SAMPLE == ENABLE)

#define STOP_N_RETRUN      //do { I2C_stop(); return 0;}while(0)
xdata U8 Cust_ADDR;

xdata volatile U8 ucI2C_MASTER_txrx[CTM_I2C_M_BUFFER];

void I2C_Wait()
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();

}

void Cust_I2C_SetAddress(U8 SetAddr)
{
	Cust_ADDR = SetAddr;
}

//U8 Cust_I2C_WriteByte(U16 Addr, U8 Data)
U8 Cust_I2C_WriteByte( U8 Data)
{
    U8 result = 1;    //  1= success


    I2C_start();
    if (I2C_write(Cust_ADDR|SMBUS_WR))		// chip address
    {
        _nop_();   // STOP_N_RETRUN;
    }
    
    if (I2C_write(Cust_WR1BYTE))	// CMD = 00	-- write 1 byte
    {
        _nop_();   // STOP_N_RETRUN;
    }

    if (I2C_write(Data))			// write 1 byte data
    {
        _nop_();   // STOP_N_RETRUN;
    }
    I2C_stop();
    
    return 1;
	
}

//U8 Cust_I2C_ReadByte(U16 Addr, U8 *p_data)
U8 Cust_I2C_ReadByte(U8 *p_data)
{

    I2C_start();
    if (I2C_write(Cust_ADDR|SMBUS_WR))		// TK18 chip address
    {
        _nop_();   // STOP_N_RETRUN;
    }

    if (I2C_write(Cust_RD1BYTE))	// CMD = 81	-- read 1 byte
    {
        _nop_();   // STOP_N_RETRUN;
    }

   SET_SDA_LOW;          
    I2C_start();				// re-start
    if (I2C_write(Cust_ADDR|SMBUS_RD))	// TK18 chip address (+1 for Read )
    {
        _nop_();   // STOP_N_RETRUN;
    }

    *p_data = I2C_read();  
    I2C_Send_ACK(1);			// Send NACK		

    I2C_stop();
    return 1;
	
}


U8 I2C_read(void)     //I2C host read ,& MSB-->LSB
{
    U8 i;
    U8 tmp;
    
    SET_SDA_INPUT_MODE;
    tmp = 0;
    //SET_SDA_HIGH;   //pull high  please use external pull high
        I2C_Wait();
        I2C_Wait();    
    
    for(i = 0;i < 8; i++)
    {
        I2C_Wait();
        SET_SCL_LOW;
        I2C_Wait();
        I2C_Wait();
        SET_SCL_HIGH;
        I2C_Wait();
        I2C_Wait();
        tmp <<= 1;
        IF_SDA_IS_HIGH
              tmp++;

    }
    SET_SCL_LOW;

    I2C_Wait();
    SET_SDA_OUTPUT_MODE;
    I2C_Wait();
    return tmp;		
		
}

U8 I2C_write(U8 tmp)		//I2C host write ,& MSB-->LSB
{
    U8 i;
    U8 ack;
    
    for(i = 0;i < 8; i++){
        SET_SCL_LOW;
        I2C_Wait();
        if (tmp & 0x80)
            SET_SDA_HIGH;
        else
            SET_SDA_LOW;
        tmp <<= 1;
        I2C_Wait();
        SET_SCL_HIGH;
        I2C_Wait();		
    }
    SET_SCL_LOW;
    I2C_Wait();
    
    ack = I2C_Check_ACK();  
    
    return ack;
    
}

//Start or re-start
void I2C_start(void)	
{
	 // First pull SDA and SCL to High
	 SET_SDA_HIGH;           //SDA:H->SCL:H->SDA:L->SCL:L  (START or re-start)
	 SET_SCL_HIGH;
	 I2C_Wait();
//   	 SET_SDA_HIGH;   //SCL:H->SDA:H->SDA:L->SCL:L  (STOP -> START) 
	 I2C_Wait();
   I2C_Wait();
   I2C_Wait();
   I2C_Wait();
	 // Pull SDA to low when SCL is high
	 SET_SDA_LOW;
	 I2C_Wait();
	 SET_SCL_LOW;	
	 I2C_Wait();
}


void I2C_stop(void)		
{
	// First pull SDA and SCL to low
	SET_SDA_LOW;				 
	I2C_Wait();
	SET_SCL_HIGH;	
 	I2C_Wait();
	 // Pull SDA to high when SCL is high
	SET_SDA_HIGH;
	I2C_Wait();

}

U8 I2C_Check_ACK()
{
    U8 ucAck;
    ucAck = 1;      // set default to NACK
	
    SET_SDA_INPUT_MODE;
    I2C_Wait();
    SET_SCL_HIGH;
    I2C_Wait();
    //slave respond ACK(0)
    IF_SDA_IS_LOW
        ucAck = 0;
    SET_SCL_LOW;
    I2C_Wait();
    SET_SDA_OUTPUT_MODE;
    I2C_Wait();
//    SET_SDA_HIGH; 
    return ucAck;
}

/* send ACK(0) or NACK(1) */
void I2C_Send_ACK(U8 ack)			 
{
	//SDA=ack;
	if (ack)
	    SET_SDA_HIGH;
	else	
	    SET_SDA_LOW;
	I2C_Wait();
	SET_SCL_HIGH;	
	I2C_Wait();
	SET_SCL_LOW;		
}

void I2C_Init()
{
//	SCL_MUX = 20;		//GPIO20 as I2C_SCL
//	SDA_MUX = 21;		//GPIO21 as I2C_SDA    
	
    SET_SDA_OUTPUT_MODE;
    SET_SCL_OUTPUT_MODE;
    SET_SCL_HIGH;
    SET_SDA_HIGH;
    
}


#endif


