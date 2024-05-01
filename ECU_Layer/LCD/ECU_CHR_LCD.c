/*
 * ECU_CHR_LCD.c
 *
 *  Created on: Sep 7, 2023
 *      Author: hazem
 */

#include "ECU_CHR_LCD.h"

static STD_ReturnStatus lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command);
static STD_ReturnStatus lcd_4bit_send_enable(const chr_lcd_4bit_t *lcd);
static STD_ReturnStatus lcd_8bit_send_enable(const chr_lcd_8bit_t *lcd);
static STD_ReturnStatus lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
static STD_ReturnStatus lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);




STD_ReturnStatus lcd_4bit_initialize(const chr_lcd_4bit_t *lcd)
{
	STD_ReturnStatus ret = E_OK;
	uint8 l_data_pins_counter = ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_initialize(&(lcd->lcd_rs));
		ret = gpio_pin_initialize(&(lcd->lcd_en));
		for(l_data_pins_counter=ZERO_INIT;l_data_pins_counter<4;l_data_pins_counter++)
		{
			ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
		}
		_delay_ms(40);
//		//ret = lcd_4bit_send_command(lcd,0x20);
//		//ret = lcd_4bit_send_command(lcd,0x20);
//		ret = lcd_4bit_send_command(lcd,0x80);
//		_delay_us(50);
//		ret = lcd_4bit_send_command(lcd,0x00);
//		ret = lcd_4bit_send_command(lcd,0xC0);
//		_delay_us(50);
//		ret = lcd_4bit_send_command(lcd,0x00);
//		ret = lcd_4bit_send_command(lcd,0x10);
//		_delay_ms(3);
//		ret = lcd_4bit_send_command(lcd,0x00);
//		ret = lcd_4bit_send_command(lcd,0x40);
//		_delay_ms(2);
//		ret = lcd_4bit_send_command(lcd,0x80);
	    lcd_send_4bits(lcd, 0x03);  // Send 0x03 command (Function Set - 8-bit mode)
	    lcd_4bit_send_enable(lcd);

	    // Delay for at least 4.1ms or follow the LCD module datasheet recommendations

	    lcd_send_4bits(lcd, 0x03);  // Send 0x03 command (Function Set - 8-bit mode)
	    lcd_4bit_send_enable(lcd);

	    // Delay for at least 100μs or follow the LCD module datasheet recommendations

	    lcd_send_4bits(lcd, 0x03);  // Send 0x03 command (Function Set - 8-bit mode)
	    lcd_4bit_send_enable(lcd);

	    // Switch to 4-bit mode
	    lcd_send_4bits(lcd, 0x02);  // Send 0x02 command (Function Set - 4-bit mode)
	    lcd_4bit_send_enable(lcd);

	    // Configure the LCD module
	    lcd_4bit_send_command(lcd, 0x28);  // 0x28 command (Function Set - 4-bit mode, 2 lines, 5x8 dots)
	    lcd_4bit_send_command(lcd, 0x0C);  // 0x0C command (Display On/Off - Display on, Cursor off, Blink off)
	    lcd_4bit_send_command(lcd, 0x06);  // 0x06 command (Entry Mode Set - Increment cursor, No display shift)
	    lcd_4bit_send_command(lcd, 0x01);  // 0x01 command (Clear Display)

	    // Delay for at least 1.5ms or follow the LCD module datasheet recommendations
	    _delay_ms(3);
	    // LCD module is now initialized and ready to use
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
		ret = lcd_send_4bits(lcd,command>>4);
		ret = lcd_4bit_send_enable(lcd);
		ret = lcd_send_4bits(lcd,command);
		ret = lcd_4bit_send_enable(lcd);
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
		ret = lcd_send_4bits(lcd,data>>4);
		ret = lcd_4bit_send_enable(lcd);
		ret = lcd_send_4bits(lcd,data);
		ret = lcd_4bit_send_enable(lcd);
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_4bit_set_cursor(lcd,row,column);
		lcd_4bit_send_char_data(lcd,data);
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8* str)
{
	STD_ReturnStatus ret = E_OK;
	if((NULL==lcd)||(NULL==str))
	{
		ret = E_NOT_OK;
	}
	else
	{
		while(*str)
		{
			ret = lcd_4bit_send_char_data(lcd,*str++);
		}
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8* str){

	STD_ReturnStatus ret = E_OK;
	if((NULL==lcd)||(NULL==str))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = lcd_4bit_set_cursor(lcd,row,column);
		while(*str)
		{
			ret = lcd_4bit_send_char_data(lcd,*str++);
		}
	}
	return ret;
}


STD_ReturnStatus lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 _char[],uint8 mem_pos)
{
	STD_ReturnStatus ret = E_OK;
	uint8 lcd_counter = ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret =  lcd_4bit_send_command(lcd,_LCD_CGRAM_START+(mem_pos*8));//mem_pos is the position addres oin cgram(1~8)
		for(lcd_counter=ZERO_INIT;lcd_counter<=7;++lcd_counter)
		{
			ret = lcd_4bit_send_char_data(lcd,_char[lcd_counter]);
		}
		ret = lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
	}
	return ret;
}

STD_ReturnStatus lcd_4bit_send_int(const chr_lcd_4bit_t *lcd,uint8 Num)
{
	if(Num!=0)
	{
		lcd_4bit_send_int(lcd,Num/10);
		lcd_4bit_send_char_data(lcd,(Num%10)+48);
	}
}

STD_ReturnStatus lcd_4bit_send_int_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint32 Num)
{
	lcd_4bit_set_cursor(lcd,row,column);
	if(Num!=0)
	{
		lcd_4bit_send_int(lcd,Num/10);
		lcd_4bit_send_char_data(lcd,(Num%10)+48);
	}
}
STD_ReturnStatus lcd_8bit_initialize(const chr_lcd_8bit_t *lcd)
{
	STD_ReturnStatus ret = E_OK;
	uint8 l_data_pins_counter = ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_initialize(&(lcd->lcd_rs));
		ret = gpio_pin_initialize(&(lcd->lcd_en));
		for(l_data_pins_counter=0;l_data_pins_counter<8;l_data_pins_counter++)
		{
			gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
		}
		_delay_ms(40);
		ret = lcd_8bit_send_command(lcd,0x38);
		_delay_ms(1);
		ret = lcd_8bit_send_command(lcd,0x0C);
		_delay_ms(2);
		//ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
		ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
		_delay_ms(2);
		//ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
		//ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
		//ret = lcd_8bit_send_command(lcd, _LCD_CURSER_OFF_DISPLAY_ON);
		//ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
		ret = lcd_8bit_send_command(lcd,0x80);
		//ret = lcd_8bit_send_command(lcd,0x04);
	}
	return ret;
}
STD_ReturnStatus lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command)
{
	STD_ReturnStatus ret = E_OK;
	uint8 l_pin_counter=ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
		for(l_pin_counter=0;l_pin_counter<8;++l_pin_counter)
		{
			ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (command>>l_pin_counter) & (uint8)0x01);
		}
		ret = lcd_8bit_send_enable(lcd);
	}
	return ret;
}
STD_ReturnStatus lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data)
{
	STD_ReturnStatus ret = E_OK;
	uint8 l_pin_counter=ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
		for(l_pin_counter=ZERO_INIT;l_pin_counter<8;++l_pin_counter)
		{
			ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (data>>l_pin_counter) & (uint8)0x01);
		}
		ret = lcd_8bit_send_enable(lcd);
	}
	return ret;
}


STD_ReturnStatus lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
	STD_ReturnStatus ret = E_OK;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_8bit_set_cursor(lcd,row,column);
		ret = lcd_8bit_send_char_data(lcd,data);
	}
	return ret;
}
STD_ReturnStatus lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8* str)
{
	STD_ReturnStatus ret = E_OK;
	if((NULL==lcd)||(NULL==str))
	{
		ret = E_NOT_OK;
	}
	else
	{
		while(*str)
		{
			ret = lcd_8bit_send_char_data(lcd,*str++);
		}
	}
	return ret;
}
STD_ReturnStatus lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8* str)
{
	STD_ReturnStatus ret = E_OK;
	if((NULL==lcd)||(NULL==str))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = lcd_8bit_set_cursor(lcd,row,column);
		while(*str)
		{
			ret = lcd_8bit_send_char_data(lcd,*str++);
		}
	}
	return ret;
}
STD_ReturnStatus lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 _char[],uint8 mem_pos)
{
	STD_ReturnStatus ret = E_OK;
	uint8 lcd_counter = ZERO_INIT;
	if(NULL==lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret =  lcd_8bit_send_command(lcd,_LCD_CGRAM_START+(mem_pos*8));//mem_pos is the position addres oin cgram(1~8)
		for(lcd_counter=ZERO_INIT;lcd_counter<=7;++lcd_counter)
		{
			ret = lcd_8bit_send_char_data(lcd,_char[lcd_counter]);
		}
		ret = lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
	}
	return ret;
}


STD_ReturnStatus convert_byte_to_string(uint8 value,uint8 *str)
{
	//since max of 8bits is 255 then we need 3 digits plus null terminator
	STD_ReturnStatus ret = E_OK;
	if(str==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		memset(str,'\n',4);
		sprintf(str,"%i",value);
	}
	return ret;
}
STD_ReturnStatus convert_string_to_byte(uint8 *value,uint8 *str)
{
	STD_ReturnStatus ret = E_OK;
	if(str==NULL||NULL==value)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*value=0;
	    for (uint8 i = 0; str[i] != '\0'; i++) {
	        *value = *value* 10 + (str[i] - 48);
	    }
	}
	return ret;
}


STD_ReturnStatus convert_short_to_string(uint16 value,uint8 *str)
{
	STD_ReturnStatus ret = E_OK;
	if(str==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		memset(str,'\n',6);
		sprintf(str,"%i",value);
	}
	return ret;
}
STD_ReturnStatus convert_int_to_string(uint32 value,uint8 *str)
{
	STD_ReturnStatus ret = E_OK;
	if(str==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		memset(str,'\n',11);
		sprintf(str,"%i",value);
	}
	return ret;
}

static STD_ReturnStatus lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command)
{
	STD_ReturnStatus ret = E_OK;
	ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
	ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
	ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
	ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
	return ret;
}

static STD_ReturnStatus lcd_4bit_send_enable(const chr_lcd_4bit_t *lcd)
{
	STD_ReturnStatus ret = E_OK;
	ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
	_delay_ms(5);
	ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
	return ret;
}


static STD_ReturnStatus lcd_8bit_send_enable(const chr_lcd_8bit_t *lcd)
{
	STD_ReturnStatus ret = E_OK;
	ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
	_delay_ms(5);
	ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
	return ret;
}

static STD_ReturnStatus lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column)
{
	STD_ReturnStatus ret = E_OK;
	column--;
	switch(row)
	{
	case ROW1 : ret = lcd_8bit_send_command(lcd,0x80+column);break;
	case ROW2 : ret = lcd_8bit_send_command(lcd,0xC0+column);break;
	default : ;
	}
	return ret;
}
static STD_ReturnStatus lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column)
{
	STD_ReturnStatus ret = E_OK;
	column--;
	switch(row)
	{
	case ROW1 : ret = lcd_4bit_send_command(lcd,0x80+column);break;
	case ROW2 : ret = lcd_4bit_send_command(lcd,0xC0+column);break;
	default : ;
	}
	return ret;
}
