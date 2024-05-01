/*
 * ECU_DC_Motor.c
 *
 *  Created on: Sep 4, 2023
 *      Author: hazem
 */
/*--------------------------INCLUDES-----------------------*/
#include "ECU_DC_Motor.h"

/*-------------------------Data Types Declarations---------------------------*/
static Pin_Config_t motor_pin1;	//-->3shan hanstakhdmhom fi kol l functions fa msh lazm a3od a-declare them kol mara
static Pin_Config_t motor_pin2;


/***
 *
 * @param _dc_motor
 * @return
 */
STD_ReturnStatus dc_motor_initialize(const dc_motor_t *_dc_motor)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==_dc_motor)
	{
		ret=E_NOT_OK;
	}
	else
	{


		gpio_pin_initialize(&(_dc_motor->dc_motor_pin[0]));
		gpio_pin_initialize(&(_dc_motor->dc_motor_pin[1]));
	}
	return ret;
}

/***
 *
 * @param _dc_motor
 * @return
 */
STD_ReturnStatus dc_motor_move_right(const dc_motor_t *_dc_motor)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==_dc_motor)
	{
		ret=E_NOT_OK;
	}
	else
	{
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_HIGH);
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_LOW);
	}
	return ret;
}


/***
 *
 * @param _dc_motor
 * @return
 */
STD_ReturnStatus dc_motor_move_left(const dc_motor_t *_dc_motor)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==_dc_motor)
	{
		ret=E_NOT_OK;
	}
	else
	{
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_LOW);
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_HIGH);
	}
	return ret;
}

/***
 *
 * @param _dc_motor
 * @return
 */
STD_ReturnStatus dc_motor_stop(const dc_motor_t *_dc_motor)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==_dc_motor)
	{
		ret=E_NOT_OK;
	}
	else
	{
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_LOW);
		gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_LOW);
	}
	return ret;
}

