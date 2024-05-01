/*
 * mcal_timr0.c
 *
 *  Created on: Oct 8, 2023
 *      Author: hazem
 */

#include "mcal_timr0.h"


static void(*TIMER0_InterruptHandler)(void)=NULL;

static inline void SetMode(Timer_Mode_t Mode);
static inline void Set_Frequency(Timer_conversion_clock_t Clock);
static inline void StructInitilaizer(const Timer0_t* _Tmr0);

STD_ReturnStatus Timer0_Init(const Timer0_t* _Tmr0)
{
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INTERRUPT_GlobalInterruptEnable();
		StructInitilaizer(_Tmr0);
		Set_Frequency(_Tmr0->Clock_conversion);
		TIMER0_InterruptHandler=_Tmr0->TIMER0_InterruptHandler;
		SetMode(_Tmr0->Timer_mode);
	}
	return ret;
}


STD_ReturnStatus Timer0_SetMode(const Timer0_t* _Tmr0,Timer_Mode_t Mode){
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(Mode)
			{
			case Normal_mode: 		Timer0_Normal_Mode_Enable(); break;
			case PWM_PhaseCorrect:  Timer0_PhaseCorrect_PWM_Mode_Enable(); break;
			case CTC: 				Timer0_CTC_Mode_Enable(); break;
			case Fast_PWM:			Timer0_CTC_Mode_Enable(); break;
			}
	}
	return ret;
}


STD_ReturnStatus Timer0_Set_CTC_Mode(const Timer0_t* _Tmr0,CTC_Mode_t CTC_Mode){
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{

	}
	return ret;
}


STD_ReturnStatus Timer0_Set_FastPWM_Mode(const Timer0_t* _Tmr0,FastPwm_Modes FPWM_Mode){
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{

	}
	return ret;
}


STD_ReturnStatus Timer0_Set_PhaseCorrectPWM_Mode(const Timer0_t* _Tmr0,PhaseCorrectPwm_Modes_t CPWM_Mode){
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{

	}
	return ret;
}


STD_ReturnStatus Timer0_Write_Value(const Timer0_t* _Tmr0,uint8 value){
	STD_ReturnStatus ret = E_OK;
	if(_Tmr0==NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{

	}
	return ret;
}

static inline void SetMode(Timer_Mode_t Mode)
{
	switch(Mode)
	{
	case Normal_mode:
		Timer0_Normal_Mode_Enable();
		Timer0_Normal_Interrupt_Enable();
		break;
	case PWM_PhaseCorrect:
		Timer0_PhaseCorrect_PWM_Mode_Enable();
		Timer0_CTC_Interrupt_Enable();
		break;
	case CTC:
		Timer0_CTC_Mode_Enable();
		Timer0_CTC_Interrupt_Enable();
		break;
	case Fast_PWM:
		Timer0_CTC_Mode_Enable();
		Timer0_CTC_Interrupt_Enable();
		break;
	}
}


static inline void Set_Frequency(Timer_conversion_clock_t Clock)
{
	switch(Clock)
	{
	case No_Clock_source:
		Timer0_no_clock_source();
		break;
	case No_Prescaling:
		Timer0_no_prescaling();
		break;
	case CONVERSION_CLOCK_FOSC_DIV_8:
		Timer0_Prescaling_8();
		break;
	case CONVERSION_CLOCK_FOSC_DIV_64:
		Timer0_Prescaling_64();
		break;
	case CONVERSION_CLOCK_FOSC_DIV_256:
		Timer0_Prescaling_256();
		break;
	case CONVERSION_CLOCK_FOSC_DIV_1024:
		Timer0_Prescaling_1024();
		break;
	}
}

void Timer0_Normal_ISR()
{
	/* clear flag*/
	Timer0_Clear_Normal_interrupt_Flag();
	if(TIMER0_InterruptHandler)
	{
		TIMER0_InterruptHandler();
	}
}
static inline void StructInitilaizer(const Timer0_t* _Tmr0)
{
	CTC_Normal_Mode_Operation();
}
