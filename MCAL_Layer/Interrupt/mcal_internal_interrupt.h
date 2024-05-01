/*
 * mcal_internal_interrupt.h
 *
 *  Created on: Sep 18, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_INTERRUPT_MCAL_INTERNAL_INTERRUPT_H_
#define MCAL_LAYER_INTERRUPT_MCAL_INTERNAL_INTERRUPT_H_

/*---------------------------INCLUDES------------------------*/
#include "mcal_interrupt_config.h"
/*------------------------MACRO Declarations----------------*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/*macro Function to disable ADC Interrupt*/
#define ADC_InterruptDisable()		(CLR_BIT(ADCSRA,ADIE))
/*macro Function to enable ADC Interrupt*/
#define ADC_InterruptEnable()		(SET_BIT(ADCSRA,ADIE))
/*macro Function to clear ADC flag*/
#define ADC_InterruptFlagClear()	(SET_BIT(ADCSRA,ADIF))
#endif
/*------------------------MACRO functions Declarations------------------*/


/*-------------------------Data Types Declarations---------------------------*/


/*-----------------------------Software Interfaces Declarations-----------------------*/

#endif /* MCAL_LAYER_INTERRUPT_MCAL_INTERNAL_INTERRUPT_H_ */
