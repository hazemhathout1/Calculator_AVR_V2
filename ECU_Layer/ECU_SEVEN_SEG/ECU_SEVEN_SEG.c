/*
 * ECU_SEVEN_SEG.C
 *
 *  Created on: Sep 5, 2023
 *      Author: hazem
 */

#include "ECU_SEVEN_SEG.h"


STD_ReturnStatus seven_segment_initialize(const segment_t *seg)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==seg)
	{
		ret = E_NOT_OK;
	}
	else
	{
	gpio_pin_initialize(&(seg->segment_pins[0]));
	gpio_pin_initialize(&(seg->segment_pins[1]));
	gpio_pin_initialize(&(seg->segment_pins[2]));
	gpio_pin_initialize(&(seg->segment_pins[3]));
	gpio_pin_initialize(&(seg->segment_pins[4]));
	gpio_pin_initialize(&(seg->segment_pins[5]));
	gpio_pin_initialize(&(seg->segment_pins[6]));
	}
	return ret;
}
STD_ReturnStatus seven_segment_write_number(const segment_t *seg,uint8 num)
{
	STD_ReturnStatus ret = E_OK;
	if((NULL==seg)&&(num>9))
	{
		ret = E_NOT_OK;
	}
	else
	{
		gpio_pin_write_logic(&(seg->segment_pins[0]),CommCathArr[num]&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[1]),(CommCathArr[num]>>1)&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[2]),(CommCathArr[num]>>2)&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[3]),(CommCathArr[num]>>3)&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[4]),(CommCathArr[num]>>4)&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[5]),(CommCathArr[num]>>5)&0x01);
		gpio_pin_write_logic(&(seg->segment_pins[6]),(CommCathArr[num]>>6)&0x01);
	}
	return ret;
}
