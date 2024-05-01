/*
 * ECU_SEVEN_SEG.h
 *
 *  Created on: Sep 5, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_ECU_SEVEN_SEG_ECU_SEVEN_SEG_H_
#define ECU_LAYER_ECU_SEVEN_SEG_ECU_SEVEN_SEG_H_

/*--------------------------INCLUDES-----------------------*/
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
#include "ECU_SEVEN_SEG_CNFG.h"


/*------------------------MACRO Declarations----------------*/
static uint8 CommCathArr[10]={
		0b00111111, //Zero
		0b00000110, //One
		0b01011011, //Two
		0b01001111, //Three
		0b01100110, //Four
		0b01101101, //Five
		0b01111101, //Six
		0b00000111, //Seven
		0b11111111, //Eight
		0b01101111  //Nine
};


/*------------------------MACRO functions Declarations------------------*/


/*-------------------------Data Types Declarations---------------------------*/
typedef enum{
	SEGMENT_COMMON_ANODE,
	SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
	Pin_Config_t segment_pins[7];
	segment_type_t segment_type;
}segment_t;

/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus seven_segment_initialize(const segment_t *seg);
STD_ReturnStatus seven_segment_write_number(const segment_t *seg,uint8 num);

/*-----------------------------Objects-----------------------*/


#endif /* ECU_LAYER_ECU_SEVEN_SEG_ECU_SEVEN_SEG_H_ */
