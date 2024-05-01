/*
 * ECU_LAYER_INIT.h
 *
 *  Created on: Sep 6, 2023
 *      Author: hazem
 */

#ifndef ECU_LAYER_ECU_LAYER_INIT_H_
#define ECU_LAYER_ECU_LAYER_INIT_H_

#include "LED/ECU_LED.h"
#include "PUSH_BUTTON/ECU_PB.h"
#include "RELAY/ECU_RELAY.h"
#include "DC_Motor/ECU_DC_Motor.h"
#include "ECU_SEVEN_SEG/ECU_SEVEN_SEG.h"
#include "KEYPAD/ECU_KEYPAD.h"
#include "LCD/ECU_CHR_LCD.h"
#include <util/delay.h>

void welcome_message();
void ecu_layer_initialize();

#endif /* ECU_LAYER_ECU_LAYER_INIT_H_ */
