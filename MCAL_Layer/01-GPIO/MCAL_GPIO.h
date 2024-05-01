/*
 * MCAL_GPIO.h
 *
 *  Created on: Aug 20, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_01_GPIO_MCAL_GPIO_H_
#define MCAL_LAYER_01_GPIO_MCAL_GPIO_H_

/* Section : Includes */
#include <stddef.h>
//#include "include/avr/eeprom.h"
#include "MCAL_STD_TYPES.h"
#include "MCAL_GPIO_Private.h"
#include "util/delay.h"


/* Section : Macro Declarations*/



/* Section : Macro Function Declarations */

#define PORT_PIN_MAX_NUMBER 8

#define PORT_MAX_NUMBER 4


/* Macro Functions Declarations */
#define HWREG8(_x)			(*((volatile uint8 *)(_x)))//to set Registers of 8bit MCU
#define SET_BIT(Reg,BIT) 	(Reg|=(1<<BIT))

#define TOGGLE_BIT(Reg,BIT) Reg^=(1<<BIT)

#define READ_BIT(Reg,BIT) (Reg>>BIT)&(1)

#define CLR_BIT(Reg,BIT) Reg&=(~(1<<BIT))


/* Section : Data type Declarations */
typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}Pin_Index_t;


typedef enum{
	GPIO_LOW,
	GPIO_HIGH
}Logic_t;

typedef enum{
	DIRECTION_INPUT=0,
	DIRECTION_OUTPUT
}direction_t;


typedef enum{
	PORTA_INDEX=0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}port_index_t;



//4 ports {0..3}->in binary=11, then mmkn ahgezlaha 2 bits bas
//8 pins {0..7}->in binary=111, then ha7gezlaha 3 bits
typedef struct{
	uint8 port:2;/* @ref : port_index_t	 */
	uint8 pin:3;/* @ref : Pin_Index_t	 */
	uint8 direction:1;/* @ref : direction_t 	 */
	uint8 logic:1;
}Pin_Config_t;//el object men ay config le ay pin dlw2ty ba2a 7bits, ya3ny lw 3ayz a-access 32 pins of MCU then 7x32=224bits=28byte bas
//bos fel korasa lw kona 3amalnaha bel tare2a el 3adeya kant hatakhod kam byte



/* Section : Function Declarations */
STD_ReturnStatus gpio_pin_direction_initialize(const Pin_Config_t *_pin_config);
STD_ReturnStatus gpio_pin_get_direction_status(const Pin_Config_t *_pin_config,direction_t *direction_status);
STD_ReturnStatus gpio_pin_write_logic(const Pin_Config_t *_pin_config,Logic_t logic);
STD_ReturnStatus gpio_pin_read_logic(const Pin_Config_t *_pin_config,Logic_t *logic);
STD_ReturnStatus gpio_pin_toggle_logic(const Pin_Config_t *_pin_config);
STD_ReturnStatus gpio_pin_initialize(const Pin_Config_t *_pin_config);



STD_ReturnStatus gpio_port_direction_initialize(port_index_t port,uint8 direction);
STD_ReturnStatus gpio_port_get_direction_status(port_index_t port,uint8 *direction_status);
STD_ReturnStatus gpio_port_write_logic(port_index_t port,uint8 logic);
STD_ReturnStatus gpio_port_read_logic(port_index_t port,Logic_t *logic);
STD_ReturnStatus gpio_port_toggle_logic(port_index_t port);





#endif /* MCAL_LAYER_01_GPIO_MCAL_GPIO_H_ */
