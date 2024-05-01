/*
 * ECU_RELAY.c
 *
 *  Created on: Sep 3, 2023
 *      Author: hazem
 */
#include "ECU_RELAY.h"

STD_ReturnStatus relay_initialize(const relay_t *_relay)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL == _relay)
	{
		ret = E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={
				.port= _relay->relay_port,
				.pin=_relay->relay_pin,
				.direction=DIRECTION_OUTPUT,
				.logic=_relay->relay_status
		};
		gpio_pin_initialize(&pin_obj);
	}

	return ret;
}



STD_ReturnStatus relay_turn_on(const relay_t *_relay)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL == _relay)
	{
		ret = E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={
				.port= _relay->relay_port,
				.pin=_relay->relay_pin,
				.direction=DIRECTION_OUTPUT,
				.logic=_relay->relay_status
		};
		gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
	}


	return ret;
}
STD_ReturnStatus relay_turn_off(const relay_t *_relay)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL == _relay)
	{
		ret = E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={
				.port= _relay->relay_port,
				.pin=_relay->relay_pin,
				.direction=DIRECTION_OUTPUT,
				.logic=_relay->relay_status
		};
		gpio_pin_write_logic(&pin_obj,GPIO_LOW);
	}


	return ret;
}




STD_ReturnStatus relay_toggle(const relay_t *_relay)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL == _relay)
	{
		ret = E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={
				.port= _relay->relay_port,
				.pin=_relay->relay_pin,
				.direction=DIRECTION_OUTPUT,
				.logic=_relay->relay_status
		};
		gpio_pin_toggle_logic(&pin_obj);
	}


	return ret;
}
