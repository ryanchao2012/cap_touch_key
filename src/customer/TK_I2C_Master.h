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
//                                                                                 
//**********************************************************************************
#ifndef _TK_I2C_MASTER_H
#define _TK_I2C_MASTER_H

#include "common.h"
#include "Ctm_sample.h"

#if(HW_TK18_I2C_MASTER_SAMPLE == ENABLE)



//GPIO21 as I2C_SDA --> GPIO28
#define SET_SDA_OUTPUT_MODE		do {GPIOIE3 &= ~0x10; GPIOOE3 |= 0x10;}while(0)
#define SET_SDA_INPUT_MODE		do {GPIOOE3 &= ~0x10; GPIOIE3 |= 0x10;}while(0)
#define SET_SDA_HIGH			   do {GPIODO3 |= 0x10;}while(0)
#define SET_SDA_LOW				do {GPIODO3 &= ~0x10;}while(0)
#define IF_SDA_IS_HIGH			if ((GPIODI3 & 0x10) == 0x10)
#define IF_SDA_IS_LOW			if ((GPIODI3 & 0x10) == 0x00)
//GPIO20 as I2C_SCL --> GPIO29
#define SET_SCL_OUTPUT_MODE		do {GPIOIE3 &= ~0x20; GPIOOE3 |= 0x20;}while(0)
#define SET_SCL_HIGH			          do {GPIODO3 |= 0x20;}while(0)
#define SET_SCL_LOW				          do {GPIODO3 &= ~0x20;}while(0)



#define I2C_ADD_START           0xAA
#define I2C_ADD_CMD71			0x71

#define   Cust_SETADDR              I2C_ADD_CMD71	// set address cmd
#define   Cust_WR1BYTE              0x55	// write 1 byte cmd
#define   Cust_RD1BYTE	            0x31	// read 1 byte cmd
#define   SMBUS_WR                     0
#define   SMBUS_RD                     1

#define CTM_I2C_M_BUFFER      32

extern xdata volatile U8 ucI2C_MASTER_txrx[CTM_I2C_M_BUFFER];



extern void I2C_Init();
extern void I2C_start(void);
extern U8 I2C_write(U8 tmp);
extern U8 I2C_Check_ACK();
extern U8 I2C_read(void);
extern void I2C_Send_ACK(U8 ack);
extern void I2C_stop(void);
extern void Cust_I2C_SetAddress(U8 SetAddr);

//extern U8 Cust_I2C_WriteByte(U16 Addr, U8 Data);
//extern U8 Cust_I2C_ReadByte(U16 Addr, U8 *p_data);
//extern U8 Cust_I2C_ReadWord(U16 Addr, U8 *p_data);
//extern U8 Cust_I2C_WriteBlock(U16 usAddr, U8 ucLength, U8 *pWriteArray);
//extern U8 Cust_I2C_ReadBlock(U16 usAddr, U8 ucLength, U8 *p_data);
extern U8 Cust_I2C_WriteByte( U8 Data);
extern U8 Cust_I2C_ReadByte( U8 *p_data);
extern U8 Cust_I2C_ReadWord(U8 *p_data);
extern U8 Cust_I2C_WriteBlock(U8 ucLength, U8 *pWriteArray);
extern U8 Cust_I2C_ReadBlock(U8 ucLength, U8 *p_data);

#endif        // #if HW_TK18_I2C_MASTER_SAMPLE



#endif      // _TK_I2C_MASTER_H
