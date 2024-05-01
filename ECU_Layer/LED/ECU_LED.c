/*
 * ECU_LED.c
 *
 *  Created on: Aug 23, 2023
 *      Author: hazem
 */
#include "ECU_LED.h"
/***
 *
 * @param led
 * @return
 */
STD_ReturnStatus led_initialize(const led_t *led)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==led)
	{
		ret= E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={.port=led->port_name,.pin=led->pin,.direction=DIRECTION_OUTPUT,.logic=led->led_status};
		gpio_pin_initialize(&pin_obj);
	}

	return ret;
}

/***
 *
 * @param led
 * @return
 */
STD_ReturnStatus led_turn_on(const led_t *led)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==led)
	{
		ret= E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={.port=led->port_name,.pin=led->pin,.direction=DIRECTION_OUTPUT,.logic=led->led_status};
		gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
	}

	return ret;
}



/***
 *
 * @param led
 * @return
 */
STD_ReturnStatus led_turn_off(const led_t *led)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==led)
	{
		ret= E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={.port=led->port_name,.pin=led->pin,.direction=DIRECTION_OUTPUT,.logic=led->led_status};
		gpio_pin_write_logic(&pin_obj,GPIO_LOW);
	}

	return ret;
}

/***
 *
 * @param led
 * @return
 */
STD_ReturnStatus led_turn_toggle(const led_t *led)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==led)
	{
		ret= E_NOT_OK;
	}
	else
	{
		Pin_Config_t pin_obj={.port=led->port_name,.pin=led->pin,.direction=DIRECTION_OUTPUT,.logic=led->led_status};
		gpio_pin_toggle_logic(&pin_obj);
	}

	return ret;
}




