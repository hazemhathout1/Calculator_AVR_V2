/*
 * mcal_spi.h
 *
 *  Created on: Oct 9, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_SPI_MCAL_SPI_H_
#define MCAL_LAYER_SPI_MCAL_SPI_H_
/*---------------------------INCLUDES------------------------*/
#include "../01-GPIO/MCAL_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/*------------------------MACRO Declarations----------------*/


/*------------------------MACRO functions Declarations------------------*/
#define SPI_MOSI_OUTPUT()		(SET_BIT(DDRB,PIN5))
#define SPI_MOSI_INPUT()		(CLR_BIT(DDRB,PIN5))
#define SPI_MISO_OUTPUT()		(SET_BIT(DDRB,PIN6))
#define SPI_MISO_INPUT()		(CLR_BIT(DDRB,PIN6))
#define SPI_SCK_INPUT()			(CLR_BIT(DDRB,PIN7))
#define SPI_SCK_OUTPUT()		(SET_BIT(DDRB,PIN7))
#define SPI_SS_INPUT()			(CLR_BIT(DDRB,PIN4))
#define SPI_SS_OUTPUT()			(SET_BIT(DDRB,PIN4))
#define SPI_SS_HIGH()			(SET_BIT(PORTB,PIN4))
#define SPI_SETDORD_LSB()		(SET_BIT(SPCR,DORD))

#define SPI_SetMaster()			(SET_BIT(SPCR,MSTR))
#define SPI_SetSlave()			(CLR_BIT(SPCR,MSTR))
#define SPI_ENABLE()			(SET_BIT(SPCR,SPE))
#define SPI_DISABLE()			(CLR_BIT(SPCR,SPE))
#define SPI_StartTransmission(Data) (SPDR=Data);
#define SPI_SetCLKFreq(CLOCK)	(SPCR|=CLOCK)





/*-------------------------Data Types Declarations---------------------------*/
typedef enum{
	SPI_Master,
	SPI_Slave
}SPI_Modes_t;

typedef enum{
	SPI_CLOCK_4,
	SPI_CLOCK_16,
	SPI_CLOCK_64,
	SPI_CLOCK_128,
	SPI_CLOCK_2,
	SPI_CLOCK_8,
	SPI_CLOCK_32
}SCK_FREQUENCY;

typedef struct{
	SPI_Modes_t Device_Mode;
	SCK_FREQUENCY Device_Frequency;
}SPI_t;



/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus SPI_MasterInit(const SPI_t *_SPI);
STD_ReturnStatus SPI_SlaveInit(const SPI_t *_SPI);
STD_ReturnStatus SPI_SetMode(const SPI_t *_SPI,SPI_Modes_t _Mode);
STD_ReturnStatus SPI_MasterTransmit(const SPI_t *_SPI,uint8 Data);
STD_ReturnStatus SPI_MasterRecieve(const SPI_t *_SPI,uint8 *Data);
STD_ReturnStatus SPI_SlaveTransmit(const SPI_t *_SPI,uint8 Data);
STD_ReturnStatus SPI_SlaveRecieve(const SPI_t *_SPI,uint8* Data);
STD_ReturnStatus SPI_Transieve(const SPI_t *_SPI,uint8 Send_Data,uint8* Ret_Data);

#endif /* MCAL_LAYER_SPI_MCAL_SPI_H_ */
