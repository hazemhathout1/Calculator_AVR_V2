/*
 * MCAL_GPIO.c
 *
 *  Created on: Aug 20, 2023
 *      Author: hazem
 */
#include "MCAL_GPIO.h"


volatile uint8 *DDR_register[]={&DDRA,&DDRB,&DDRC,&DDRD};
volatile uint8 *PORT_register[]={&PORTA,&PORTB,&PORTC,&PORTD};
volatile uint8 *PIN_register[]={&PINA,&PINB,&PINC,&PIND};

/***
 *
 * @param _pin_config
 * @return
 */
STD_ReturnStatus gpio_pin_direction_initialize(const Pin_Config_t *_pin_config){
	STD_ReturnStatus ret=E_OK;
	if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1)
	{
		ret=E_NOT_OK;
	}
	else
	{
		switch(_pin_config->direction)
		{
		case DIRECTION_OUTPUT:		SET_BIT(*DDR_register[_pin_config->port],_pin_config->pin);break;
		case DIRECTION_INPUT: 		CLR_BIT(*DDR_register[_pin_config->port],_pin_config->pin);break;
		}
	}
	return ret;
}


/***
 *
 * @param _pin_config
 * @param direction_status
 * @return
 */
STD_ReturnStatus gpio_pin_get_direction_status(const Pin_Config_t *_pin_config,direction_t *direction_status)
{
	STD_ReturnStatus ret=E_OK;
		if(NULL==_pin_config || NULL==direction_status ||_pin_config->pin > PORT_PIN_MAX_NUMBER-1)
		{
			ret=E_NOT_OK;
		}
		else
		{
			*direction_status=READ_BIT(*DDR_register[_pin_config->direction],_pin_config->pin);
		}
		return ret;
}


/***
 *
 * @param _pin_config
 * @param logic
 * @return
 */
STD_ReturnStatus gpio_pin_write_logic(const Pin_Config_t *_pin_config,Logic_t logic)
{
	STD_ReturnStatus ret=E_OK;
		if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1)
		{
			ret=E_NOT_OK;
		}
		else
		{
			switch(logic)
			{
			case GPIO_HIGH:			SET_BIT(*PORT_register[_pin_config->port],_pin_config->pin);break;
			case GPIO_LOW:			CLR_BIT(*PORT_register[_pin_config->port],_pin_config->pin);break;
			}
		}
		return ret;
}


/***
 *
 * @param _pin_config
 * @param logic
 * @return
 */
STD_ReturnStatus gpio_pin_read_logic(const Pin_Config_t *_pin_config,Logic_t *logic)
{
	STD_ReturnStatus ret=E_OK;
		if(NULL==_pin_config|| NULL== logic||_pin_config->pin > PORT_PIN_MAX_NUMBER-1)
		{
			ret=E_NOT_OK;
		}
		else
		{
			*logic=READ_BIT(*PIN_register[_pin_config->port],_pin_config->pin);
		}
		return ret;
}


/***
 *
 * @param _pin_config
 * @return
 */
STD_ReturnStatus gpio_pin_toggle_logic(const Pin_Config_t *_pin_config)
{
	STD_ReturnStatus ret=E_OK;
		if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1)
		{
			ret=E_NOT_OK;
		}
		else
		{
			TOGGLE_BIT(*PORT_register[_pin_config->port],_pin_config->pin);
		}
		return ret;
}



/***
 *
 *
 * @param _pin_config
 * @return
 */
STD_ReturnStatus gpio_pin_initialize(const Pin_Config_t *_pin_config)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==_pin_config)
	{
		ret=E_NOT_OK;
	}
	else
	{
		ret= gpio_pin_direction_initialize(_pin_config);
		ret= gpio_pin_write_logic(_pin_config,_pin_config->logic);
	}

	return ret;
}




/***
 *
 * @param port
 * @param direction
 * @return
 */
STD_ReturnStatus gpio_port_direction_initialize(port_index_t port,uint8 direction)
{
	STD_ReturnStatus ret=E_OK;
	if(port>PORT_MAX_NUMBER-1)
	{
		ret=E_NOT_OK;
	}
	else
	{
		*DDR_register[port]=direction;
	}

	return ret;
}
STD_ReturnStatus gpio_port_get_direction_status(port_index_t port,uint8 *direction_status)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==direction_status && port>PORT_MAX_NUMBER-1)
	{
		ret=E_NOT_OK;
	}
	else
	{
		*direction_status=*DDR_register[port];
	}

	return ret;
}


/***
 *
 * @param port
 * @param logic
 * @return
 */
STD_ReturnStatus gpio_port_write_logic(port_index_t port,uint8 logic)
{
	STD_ReturnStatus ret=E_OK;
	if(port>PORT_MAX_NUMBER-1)
		{
			ret=E_NOT_OK;
		}
		else
		{
			*PORT_register[port]=logic;
		}

	return ret;
}
STD_ReturnStatus gpio_port_read_logic(port_index_t port,Logic_t *logic)
{
	STD_ReturnStatus ret=E_OK;
	if(NULL==logic && port>PORT_MAX_NUMBER-1)
	{
		ret=E_NOT_OK;
	}
	else
	{
		*logic=*PORT_register[port];
	}

	return ret;
}


/***
 *
 * @param port
 * @return
 */
STD_ReturnStatus gpio_port_toggle_logic(port_index_t port)
{
	STD_ReturnStatus ret=E_OK;
	if(port>PORT_MAX_NUMBER-1)
	{
		ret=E_NOT_OK;
	}
	else
	{
		*PORT_register[port]^=0xff;
	}


	return ret;
}
