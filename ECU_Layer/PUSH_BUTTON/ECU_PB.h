/*
 * ECU_PB.h
 *
 *  Created on: Aug 23, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_PUSH_BUTTON_ECU_PB_H_
#define ECU_LAYER_PUSH_BUTTON_ECU_PB_H_
/*Section : includes */
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
#include "ECU_PB_cfg.h"


/*Section : Data types Declarations */

typedef enum{
	BUTTON_PRESSED=0,
	BUTTON_RELEASED
}button_status_t;

typedef enum{
	BUTTON_ACTIVE_HIGH,
	BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
	Pin_Config_t button_pin;
	button_status_t button_status;
	button_active_t button_connection;
}button_t;

/*Section : Software Declarations */
STD_ReturnStatus button_initialize(const button_t *btn);
STD_ReturnStatus button_read_state(const button_t *btn,button_status_t *btn_state);

#endif /* ECU_LAYER_PUSH_BUTTON_ECU_PB_H_ */
