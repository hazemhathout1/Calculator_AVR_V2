/*
 * ECU_DC_Motor.h
 *
 *  Created on: Sep 4, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_DC_MOTOR_ECU_DC_MOTOR_H_
#define ECU_LAYER_DC_MOTOR_ECU_DC_MOTOR_H_


/*---------------------------INCLUDES------------------------*/
#include "../../MCAL_Layer/01-GPIO/MCAL_GPIO.h"
/*------------------------MACRO Declarations----------------*/
#define DC_MOTOR_ON_STATUS   0x01U
#define DC_MOTOR_OFF_STATUS  0x00U

#define DC_MOTOR_PIN1		 0x00U
#define DC_MOTOR_PIN2		 0x01U

/*------------------------MACRO functions Declarations------------------*/


/*-------------------------Data Types Declarations---------------------------*/
typedef struct{
	Pin_Config_t dc_motor_pin[2];
}dc_motor_t;

/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus dc_motor_initialize(const dc_motor_t *_dc_motor);
STD_ReturnStatus dc_motor_move_right(const dc_motor_t *_dc_motor);
STD_ReturnStatus dc_motor_move_left(const dc_motor_t *_dc_motor);
STD_ReturnStatus dc_motor_stop(const dc_motor_t *_dc_motor);

#endif /* ECU_LAYER_DC_MOTOR_ECU_DC_MOTOR_H_ */
