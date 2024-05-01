/*
  * ECU_LAYER_INIT.c
 *
 *  Created on: Sep 6, 2023
 *      Author: hazem
 */

#include "ECU_LAYER_INIT.h"






keypad_t keypad1={
		.keypad_row_pins[0].port=PORTD_INDEX,
		.keypad_row_pins[0].pin=PIN0,
		.keypad_row_pins[0].direction=DIRECTION_OUTPUT,
		.keypad_row_pins[0].logic=GPIO_LOW,
		.keypad_row_pins[1].port=PORTD_INDEX,
		.keypad_row_pins[1].pin=PIN1,
		.keypad_row_pins[1].direction=DIRECTION_OUTPUT,
		.keypad_row_pins[1].logic=GPIO_LOW,
		.keypad_row_pins[2].port=PORTC_INDEX,
		.keypad_row_pins[2].pin=PIN0,
		.keypad_row_pins[2].direction=DIRECTION_OUTPUT,
		.keypad_row_pins[2].logic=GPIO_LOW,
		.keypad_row_pins[3].port=PORTD_INDEX,
		.keypad_row_pins[3].pin=PIN3,
		.keypad_row_pins[3].direction=DIRECTION_OUTPUT,
		.keypad_row_pins[3].logic=GPIO_LOW,
		.keypad_columns_pins[0].port=PORTD_INDEX,
		.keypad_columns_pins[0].pin=PIN4,
		.keypad_columns_pins[0].direction=DIRECTION_INPUT,
		.keypad_columns_pins[0].logic=GPIO_LOW,
		.keypad_columns_pins[1].port=PORTD_INDEX,
		.keypad_columns_pins[1].pin=PIN5,
		.keypad_columns_pins[1].direction=DIRECTION_INPUT,
		.keypad_columns_pins[1].logic=GPIO_LOW,
		.keypad_columns_pins[2].port=PORTD_INDEX,
		.keypad_columns_pins[2].pin=PIN6,
		.keypad_columns_pins[2].direction=DIRECTION_INPUT,
		.keypad_columns_pins[2].logic=GPIO_LOW,
		.keypad_columns_pins[3].port=PORTD_INDEX,
		.keypad_columns_pins[3].pin=PIN7,
		.keypad_columns_pins[3].direction=DIRECTION_INPUT,
		.keypad_columns_pins[3].logic=GPIO_LOW,
};


chr_lcd_4bit_t lcd1={
		.lcd_rs.port=PORTB_INDEX,
		.lcd_rs.pin=PIN4,
		.lcd_rs.direction=DIRECTION_OUTPUT,
		.lcd_rs.logic=GPIO_LOW,
		.lcd_en.port=PORTB_INDEX,
		.lcd_en.pin=PIN5,
		.lcd_en.direction=DIRECTION_OUTPUT,
		.lcd_en.logic=GPIO_LOW,
		.lcd_data[0].port=PORTB_INDEX,
		.lcd_data[0].pin=PIN0,
		.lcd_data[0].direction=DIRECTION_OUTPUT,
		.lcd_data[0].logic=GPIO_LOW,
		.lcd_data[1].port=PORTB_INDEX,
		.lcd_data[1].pin=PIN1,
		.lcd_data[1].direction=DIRECTION_OUTPUT,
		.lcd_data[1].logic=GPIO_LOW,
		.lcd_data[2].port=PORTB_INDEX,
		.lcd_data[2].pin=PIN2,
		.lcd_data[2].direction=DIRECTION_OUTPUT,
		.lcd_data[2].logic=GPIO_LOW,
		.lcd_data[3].port=PORTB_INDEX,
		.lcd_data[3].pin=PIN3,
		.lcd_data[3].direction=DIRECTION_OUTPUT,
		.lcd_data[3].logic=GPIO_LOW
};

chr_lcd_8bit_t lcd2={
		.lcd_rs.port=PORTD_INDEX,
		.lcd_rs.pin=PIN0,
		.lcd_rs.direction=DIRECTION_OUTPUT,
		.lcd_rs.logic=GPIO_LOW,
		.lcd_en.port=PORTD_INDEX,
		.lcd_en.pin=PIN2,
		.lcd_en.direction=DIRECTION_OUTPUT,
		.lcd_en.logic=GPIO_LOW,
		.lcd_data[0].port=PORTB_INDEX,
		.lcd_data[0].pin=PIN0,
		.lcd_data[0].direction=DIRECTION_OUTPUT,
		.lcd_data[0].logic=GPIO_LOW,
		.lcd_data[1].port=PORTB_INDEX,
		.lcd_data[1].pin=PIN1,
		.lcd_data[1].direction=DIRECTION_OUTPUT,
		.lcd_data[1].logic=GPIO_LOW,
		.lcd_data[2].port=PORTB_INDEX,
		.lcd_data[2].pin=PIN2,
		.lcd_data[2].direction=DIRECTION_OUTPUT,
		.lcd_data[2].logic=GPIO_LOW,
		.lcd_data[3].port=PORTB_INDEX,
		.lcd_data[3].pin=PIN3,
		.lcd_data[3].direction=DIRECTION_OUTPUT,
		.lcd_data[3].logic=GPIO_LOW,
		.lcd_data[4].port=PORTB_INDEX,
		.lcd_data[4].pin=PIN4,
		.lcd_data[4].direction=DIRECTION_OUTPUT,
		.lcd_data[4].logic=GPIO_LOW,
		.lcd_data[5].port=PORTB_INDEX,
		.lcd_data[5].pin=PIN5,
		.lcd_data[5].direction=DIRECTION_OUTPUT,
		.lcd_data[5].logic=GPIO_LOW,
		.lcd_data[6].port=PORTB_INDEX,
		.lcd_data[6].pin=PIN6,
		.lcd_data[6].direction=DIRECTION_OUTPUT,
		.lcd_data[6].logic=GPIO_LOW,
		.lcd_data[7].port=PORTB_INDEX,
		.lcd_data[7].pin=PIN7,
		.lcd_data[7].direction=DIRECTION_OUTPUT,
		.lcd_data[7].logic=GPIO_LOW
};

void ecu_layer_initialize()
{
	STD_ReturnStatus ret = E_NOT_OK;
	ret = lcd_4bit_initialize(&lcd1);
	ret = keypad_initialize(&keypad1);
	//ret = lcd_8bit_initialize(&lcd2);
}

void welcome_message()
{
	for(uint8 i=0;i<=2;i++)
	{
		lcd_4bit_send_string_pos(&lcd1,1,3, "Calculator");
		_delay_ms(200);
		lcd_4bit_send_string_pos(&lcd1,1,3, "           ");
		_delay_ms(100);
	}
}

