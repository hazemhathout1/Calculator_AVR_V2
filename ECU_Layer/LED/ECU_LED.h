/*
 * ECU_LED.h
 *
 *  Created on: Aug 23, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_LED_ECU_LED_H_
#define ECU_LAYER_LED_ECU_LED_H_
/* Section : Includes */
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
#include "ECU_LED_cgf.h"

/* Section : Data Type Definitions */
typedef enum{
	LED_OFF,
	LED_ON
}led_status;

typedef struct{
	uint8 port_name : 3;
	uint8 pin : 3;
	uint8 led_status : 1;
}led_t;



/*Section : User defined Functions */
STD_ReturnStatus led_initialize(const led_t *led);
STD_ReturnStatus led_turn_on(const led_t *led);
STD_ReturnStatus led_turn_off(const led_t *led);
STD_ReturnStatus led_turn_toggle(const led_t *led);




#endif /* ECU_LAYER_LED_ECU_LED_H_ */
