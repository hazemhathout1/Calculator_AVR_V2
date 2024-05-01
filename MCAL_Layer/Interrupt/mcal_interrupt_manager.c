/*
 * mcal_interrupt_manager.c
 *
 *  Created on: Sep 18, 2023
 *      Author: hazem
 */
#include "../Interrupt/mcal_interrupt_manager.h"



ISR(INT0_vect)
{
	INT0_ISR();
}


ISR(INT1_vect)
{
	INT1_ISR();
}

ISR(INT2_vect)
{
	INT2_ISR();
}

ISR(ADC_vect)
{
	ADC_ISR();
}
ISR(TIMER0_COMP_vect)
{
	Timer0_Normal_ISR();
}
