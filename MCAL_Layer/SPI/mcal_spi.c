/*
 * mcal_spi.c
 *
 *  Created on: Oct 9, 2023
 *      Author: hazem
 */
#include "mcal_spi.h"


STD_ReturnStatus SPI_MasterInit(const SPI_t *_SPI)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPI_MOSI_OUTPUT();
		SPI_SS_OUTPUT();
		SPI_SCK_OUTPUT();
		SPI_MISO_INPUT();
		//SPI_SS_HIGH();
		SPI_SETDORD_LSB();
		SPI_SetMaster();
		SPI_SetCLKFreq(_SPI->Device_Frequency);
		SPI_ENABLE();
	}
	return ret;
}



STD_ReturnStatus SPI_SlaveInit(const SPI_t *_SPI)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPI_MOSI_INPUT();
		SPI_SCK_INPUT();
		SPI_SS_INPUT();
		SPI_MISO_OUTPUT();
		SPI_SetSlave();
		SPI_ENABLE();
		SPI_SetCLKFreq(_SPI->Device_Frequency);
	}
	return ret;
}
STD_ReturnStatus SPI_SetMode(const SPI_t *_SPI,SPI_Modes_t _Mode)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(_Mode)
		{
		case SPI_Master: SPI_SetMaster();break;
		case SPI_Slave:  SPI_SetSlave();break;
		}
	}
	return ret;
}


STD_ReturnStatus SPI_MasterTransmit(const SPI_t *_SPI,uint8 Data)
{
	STD_ReturnStatus ret = E_OK;
	uint8 BUFFER;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPI_StartTransmission(Data);
		while(!(SPSR & (1<<SPIF)));
		BUFFER=SPDR;//Clear SPIF After first transmission
	}
	return ret;
}



STD_ReturnStatus SPI_MasterRecieve(const SPI_t *_SPI,uint8 *Data)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPDR=0xff;
		while(!(SPSR & (1<<SPIF)));
		*Data=SPDR;
	}
	return ret;
}


STD_ReturnStatus SPI_SlaveTransmit(const SPI_t *_SPI,uint8 Data)
{
	STD_ReturnStatus ret = E_OK;
	uint8 BUFFER;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPI_StartTransmission(Data);
		while(!(SPSR & (1<<SPIF)));
		BUFFER=SPDR;//Clear SPIF After first transmission
	}
	return ret;
}


STD_ReturnStatus SPI_SlaveRecieve(const SPI_t *_SPI,uint8* Data)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		while(!(SPSR & (1<<SPIF)));
		*Data=SPDR;
	}
	return ret;
}


STD_ReturnStatus SPI_Transieve(const SPI_t *_SPI,uint8 Send_Data,uint8* Ret_Data)
{
	STD_ReturnStatus ret = E_OK;
	if(_SPI==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPI_StartTransmission(Send_Data);
		while(!(SPSR & (1<<SPIF)));
		*Ret_Data=SPDR;
	}
	return ret;
}
