/*
 * MCAL_EEPROM.h
 *
 *  Created on: Sep 20, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_03_EEPROM_MCAL_EEPROM_H_
#define MCAL_LAYER_03_EEPROM_MCAL_EEPROM_H_

/*---------------------------INCLUDES------------------------*/
#include "../01-GPIO/MCAL_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/*------------------------MACRO Declarations----------------*/


/*------------------------MACRO functions Declarations------------------*/
#define Read_GIEBit()		(READ_BIT(SREG,SREG_I))

/*-------------------------Data Types Declarations---------------------------*/


/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus Data_EEPROM_WriteByte(uint8 bAdd,uint8 bData);
STD_ReturnStatus Data_EEPROM_ReadByte(uint16 bAdd,uint8 *bData);

#endif /* MCAL_LAYER_03_EEPROM_MCAL_EEPROM_H_ */
