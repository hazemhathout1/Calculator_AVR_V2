/*
 * ECU_KEYPAD.h
 *
 *  Created on: Sep 6, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_KEYPAD_ECU_KEYPAD_H_
#define ECU_LAYER_KEYPAD_ECU_KEYPAD_H_
/*--------------------------INCLUDES-----------------------*/
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
#include <util/delay.h>

/*------------------------MACRO Declarations----------------*/
#define ECU_KEYPAD_ROWS		4
#define ECU_KEYPAD_COLUMNS	4

#define KEY_PRESSED			0x01
#define KEY_NOT_PRESSED		0x00
/*------------------------MACRO functions Declarations------------------*/


/*-------------------------Data Types Declarations---------------------------*/
typedef struct{
	Pin_Config_t keypad_row_pins[ECU_KEYPAD_ROWS];
	Pin_Config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus keypad_initialize(const keypad_t *_keypad_obj);
STD_ReturnStatus keypad_get_value(const keypad_t *_keypad_obj,uint8 *value,uint8 *Key_pressed);


#endif /* ECU_LAYER_KEYPAD_ECU_KEYPAD_H_ */
