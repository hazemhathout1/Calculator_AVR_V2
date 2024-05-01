/*
 * mcal_timr0.h
 *
 *  Created on: Oct 8, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_TIMER_0_MCAL_TIMR0_H_
#define MCAL_LAYER_TIMER_0_MCAL_TIMR0_H_
/*---------------------------INCLUDES------------------------*/
#include "../01-GPIO/MCAL_GPIO.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/*------------------------MACRO Declarations----------------*/


/*------------------------MACRO functions Declarations------------------*/
#define Timer0_Normal_Mode_Enable()			do{CLR_BIT(TCCR0,WGM00);\
											   CLR_BIT(TCCR0,WGM01);\
												}while(0)
#define Timer0_CTC_Mode_Enable()			do{CLR_BIT(TCCR0,WGM00);\
											   SET_BIT(TCCR0,WGM01);\
												}while(0)
#define Timer0_Fast_PWM_Mode_Enable()		do{SET_BIT(TCCR0,WGM00);\
											   CLR_BIT(TCCR0,WGM01);\
												}while(0)
#define Timer0_PhaseCorrect_PWM_Mode_Enable() do{SET_BIT(TCCR0,WGM00);\
											   SET_BIT(TCCR0,WGM01);\
												}while(0)



#define Timer0_no_clock_source()			  do{CLR_BIT(TCCR0,CS00);\
												 CLR_BIT(TCCR0,CS01);\
												 CLR_BIT(TCCR0,CS02);\
												}while(0)
#define Timer0_no_prescaling()  			  do{SET_BIT(TCCR0,CS00);\
												 CLR_BIT(TCCR0,CS01);\
												 CLR_BIT(TCCR0,CS02);\
												}while(0)
#define Timer0_Prescaling_8()   			  do{CLR_BIT(TCCR0,CS00);\
												 SET_BIT(TCCR0,CS01);\
												 CLR_BIT(TCCR0,CS02);\
												}while(0)
#define Timer0_Prescaling_64()  			  do{SET_BIT(TCCR0,CS00);\
												 SET_BIT(TCCR0,CS01);\
												 CLR_BIT(TCCR0,CS02);\
												}while(0)
#define Timer0_Prescaling_256()				  do{CLR_BIT(TCCR0,CS00);\
												 CLR_BIT(TCCR0,CS01);\
												 SET_BIT(TCCR0,CS02);\
												}while(0)
#define Timer0_Prescaling_1024()			  do{SET_BIT(TCCR0,CS00);\
												 CLR_BIT(TCCR0,CS01);\
												 SET_BIT(TCCR0,CS02);\
												}while(0)



#define Timer0_Normal_Interrupt_Enable()	  do{CLR_BIT(TIMSK,OCIE0);\
												 SET_BIT(TIMSK,TOIE0);\
												}while(0)
#define Timer0_CTC_Interrupt_Enable()	  	  do{SET_BIT(TIMSK,OCIE0);\
												 CLR_BIT(TIMSK,TOIE0);\
												}while(0)



#define Timer0_Clear_Normal_interrupt_Flag()	SET_BIT(TIFR,TOV0);
#define Timer0_Clear_Overflow_interrupt_Flag()	SET_BIT(TIFR,OCF0);



#define CTC_Normal_Mode_Operation()				do{CLR_BIT(TCCR0,COM00);\
												   CLR_BIT(TCCR0,COM01);\
												}while(0)
#define CTC_Toggle_on_Compare()					do{SET_BIT(TCCR0,COM00);\
												   CLR_BIT(TCCR0,COM01);\
												}while(0)
#define CTC_Clear_on_Compare()					do{CLR_BIT(TCCR0,COM00);\
												   SET_BIT(TCCR0,COM01);\
												}while(0)
#define CTC_Set_on_Compare()					do{SET_BIT(TCCR0,COM00);\
												   SET_BIT(TCCR0,COM01);\
												}while(0)


/*-------------------------Data Types Declarations---------------------------*/
typedef enum{
	Normal_mode=0,
	PWM_PhaseCorrect,
	CTC,
	Fast_PWM
}Timer_Mode_t;

typedef enum{
	Normal_port_compare_off=0,
	Toggle_on_Compare,
	Clear_on_compare,
	Set_on_compare
}CTC_Mode_t;

typedef enum{
	Normal_port_compare_off_FPWM=0,
	Reserved_FPWM,
	Clear_on_compare_set_OCO_on_top_FPWM,
	Set_on_compare_Clear_OC0_on_top_FPWM
}FastPwm_Modes;

typedef enum{
	Normal_port_compare_off_CPWM=0,
	Reserved_CPWM,
	Clear_on_compare_set_OCO_on_top_CPWM,
	Set_on_compare_Clear_OC0_on_top
}PhaseCorrectPwm_Modes_t;


typedef enum{
	No_Clock_source=0,
	No_Prescaling=1,
	CONVERSION_CLOCK_FOSC_DIV_8,
	CONVERSION_CLOCK_FOSC_DIV_64,
	CONVERSION_CLOCK_FOSC_DIV_256,
	CONVERSION_CLOCK_FOSC_DIV_1024,
}Timer_conversion_clock_t;

typedef struct{
	void(*TIMER0_InterruptHandler)(void);
	Timer_Mode_t Timer_mode;
	CTC_Mode_t NormalCTCMode;
	Timer_conversion_clock_t Clock_conversion;
}Timer0_t;






/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus Timer0_Init(const Timer0_t* _Tmr0);
STD_ReturnStatus Timer0_SetMode(const Timer0_t* _Tmr0,Timer_Mode_t Mode);
STD_ReturnStatus Timer0_Set_CTC_Mode(const Timer0_t* _Tmr0,CTC_Mode_t CTC_Mode);
STD_ReturnStatus Timer0_Set_FastPWM_Mode(const Timer0_t* _Tmr0,FastPwm_Modes FPWM_Mode);
STD_ReturnStatus Timer0_Set_PhaseCorrectPWM_Mode(const Timer0_t* _Tmr0,PhaseCorrectPwm_Modes_t CPWM_Mode);
STD_ReturnStatus Timer0_Write_Value(const Timer0_t* _Tmr0,uint8 value);

#endif /* MCAL_LAYER_TIMER_0_MCAL_TIMR0_H_ */
