/*
 * ECU_RELAY.h
 *
 *  Created on: Sep 3, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_RELAY_ECU_RELAY_H_
#define ECU_LAYER_RELAY_ECU_RELAY_H_

/*---------------------Includes-----------------*/
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
#include "ECY_RELAY_CFG.h"


/*---------------------Macro Definitions-------------------*/
#define RELAY_ON_STATUS  0x01u
#define RELAY_OFF_STATUS 0x00u


/*---------------------Macro Function Declarations-----------------*/


/*---------------------Data {type Declarations-----------------*/
typedef struct{
	uint8 relay_port : 4;
	uint8 relay_pin : 3;
	uint8 relay_status : 1;
}relay_t;


/*---------------------software interfaces declarations-----------------*/

STD_ReturnStatus relay_initialize(const relay_t *_relay);
STD_ReturnStatus relay_turn_on(const relay_t *_relay);
STD_ReturnStatus relay_turn_off(const relay_t *_relay);




#endif /* ECU_LAYER_RELAY_ECU_RELAY_H_ */
