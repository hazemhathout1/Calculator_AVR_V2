/*
 * MCAL_EEPROM.C
 *
 *  Created on: Sep 20, 2023
 *      Author: hazem
 */


#include "MCAL_EEPROM.h"


STD_ReturnStatus Data_EEPROM_WriteByte(uint8 bAdd,uint8 bData)
{
	STD_ReturnStatus ret = E_OK;
    while((EECR & 0x02) == 1) ;           // CHECK EEWE BIT
    while((SPMCR & 0x01 )== 1);          // CHECK SPMEN BIT
    EEARH=0x00;                       // SET ADDRESS MSB BYTE
    EEARL = bAdd ;                 // SET LSB BYTE OF ADDRESS
    EEDR = bData ;                     // WRITE data to be written to EEPROM
    EECR = 0x04 ;                       // SET EEMWE BIT
    EECR = 0x06;                        // SET EEMWE & EEWE BITS
    while((EECR & 0x04) == 1);           // CHECK EEMWE IS CLRED
    _delay_ms(10);
	return ret;
}
STD_ReturnStatus Data_EEPROM_ReadByte(uint16 bAdd,uint8 *bData)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==bData)
	{
		ret = E_NOT_OK;
	}
	else
	{

	}
	return ret;
}
