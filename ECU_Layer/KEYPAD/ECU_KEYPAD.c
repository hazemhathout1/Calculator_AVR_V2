/*
 * ECU_KEYPAD.c
 *
 *  Created on: Sep 6, 2023
 *      Author: hazem
 */
#include "ECU_KEYPAD.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS]={
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'#','0','=','+'},
};

static const uint8 btn_values_int[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS]={
		{7,8,9,'/'},
		{4,5,6,'*'},
		{1,2,3,'-'},
		{'#',0,'=','+'},
};



/***
 *
 * @param _keypad_obj
 * @return
 */
STD_ReturnStatus keypad_initialize(const keypad_t *_keypad_obj)
{
	STD_ReturnStatus ret = E_OK;
	uint8 rows_counter=ZERO_INIT,columns_counter=ZERO_INIT;
	if(NULL==_keypad_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for(rows_counter=ZERO_INIT;rows_counter<ECU_KEYPAD_ROWS;rows_counter++)
		{
			ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
		}

		for(columns_counter=ZERO_INIT;columns_counter<ECU_KEYPAD_COLUMNS;columns_counter++)
		{
			ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
		}
	}
	return ret;
}


/***
 *
 * @param _keypad_obj
 * @param value
 * @return
 */
STD_ReturnStatus keypad_get_value(const keypad_t *_keypad_obj,uint8 *value,uint8 *Key_pressed)
{
	STD_ReturnStatus ret = E_NOT_OK;
	*Key_pressed=KEY_NOT_PRESSED;
	uint8 l_rows_counter=ZERO_INIT,l_columns_counter=ZERO_INIT,l_counter=ZERO_INIT;
	uint8 column_logic=ZERO_INIT;
	if((NULL==_keypad_obj)||(NULL==value))
	{
		ret = E_NOT_OK;
	}
	else
	{
		for(l_rows_counter=ZERO_INIT;l_rows_counter<ECU_KEYPAD_ROWS;l_rows_counter++)
		{
			//3ayzen nekhaly kol el rows 3aleha zero volt ela awel wahd bas 3shan ne-check 3aleh
			//fa el awel hankhaly kol el kolo zero ba3daha nekhaly 5volt 3ala R1 w hakaza
			for(l_counter=ZERO_INIT;l_counter<ECU_KEYPAD_ROWS;l_counter++){
						ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]),GPIO_LOW);
					}
			//ba3d ma khalet kolo zero, hakhaly wahd wahd be 5 volt bel tarteeb 3shan keda akhat l_rows_counter fel loop el bara
			ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]),GPIO_HIGH);
			_delay_ms(1);
			//columns Check
			for(l_columns_counter=ZERO_INIT;l_columns_counter<ECU_KEYPAD_COLUMNS;l_columns_counter++)
			{
				ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]),&column_logic);
				if(GPIO_HIGH==column_logic)
				{
					*value=btn_values_int[l_rows_counter][l_columns_counter];
					*Key_pressed=KEY_PRESSED;
				}
			}
		}
		ret = E_OK;
	}
	return ret;
}

