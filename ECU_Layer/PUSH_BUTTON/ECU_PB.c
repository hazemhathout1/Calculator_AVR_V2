/*
 * ECU_PB.c
 *
 *  Created on: Aug 23, 2023
 *      Author: hazem
 */
#include "ECU_PB.h"



/***
 *
 * @param btn
 * @return
 */
STD_ReturnStatus button_initialize(const button_t *btn)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==btn)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_direction_initialize(&(btn->button_pin));
	}


	return ret;
}


/***
 *
 * @param btn
 * @param btn_state
 * @return
 */
STD_ReturnStatus button_read_state(const button_t *btn,button_status_t *btn_state)
{
	STD_ReturnStatus ret=E_NOT_OK;
	Logic_t pin_logic_status=GPIO_LOW;
	if((NULL==btn)||(NULL==btn_state))
	{
		ret = E_NOT_OK;
	}
	else
	{
		gpio_pin_read_logic(&(btn->button_pin),&pin_logic_status);
		if(BUTTON_ACTIVE_HIGH == btn->button_connection)
		{
			if(GPIO_HIGH==pin_logic_status)
			{
				*btn_state=BUTTON_PRESSED;
			}
			else
			{
				*btn_state=BUTTON_RELEASED;
			}
		}
		else if(BUTTON_ACTIVE_LOW == btn->button_connection)
		{
			if(GPIO_LOW==pin_logic_status)
			{
				*btn_state=BUTTON_PRESSED;
			}
			else
			{
				*btn_state=BUTTON_RELEASED;
			}
		}
		ret = E_OK;
	}


	return ret;
}


