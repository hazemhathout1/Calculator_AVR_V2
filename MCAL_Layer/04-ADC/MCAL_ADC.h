/*
 * MCAL_ADC.h
 *
 *  Created on: Sep 21, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_04_ADC_MCAL_ADC_H_
#define MCAL_LAYER_04_ADC_MCAL_ADC_H_
/*---------------------------INCLUDES------------------------*/
#include "../01-GPIO/MCAL_GPIO.h"
#include "MCAL_ADC_cfg.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/*------------------------MACRO Declarations----------------*/
#define ADC_RIGHT_ADJUST 	0x00u
#define ADC_LEFT_ADJUST 	0x01u

#define ADC_VOLTAGE_REFERENCE_ENABLED	0X01U
#define ADC_VOLTAGE_REFERENCE_DISABLED	0X00U

#define ADC_CONVERSION_COMPLETED 1
#define ADC_CONVERSION_NOT_COMPLETED 0

/*------------------------MACRO functions Declarations------------------*/
/*ADC_CONVERSION_STATUS:Check if the conversion is done or not*/
#define ADC_CONVERSION_STATUS()		(READ_BIT(ADCSRA,ADSC))
#define ADC_CONVERTER_ENABLE()		(SET_BIT(ADCSRA,ADEN))
#define ADC_CONVERTER_DISABLE()		(CLR_BIT(ADCSRA,ADEN))
#define ADC_DISABLE_VOLTAGE_REFERENCE()		do{SET_BIT(ADMUX,REFS0);\
											   CLR_BIT(ADMUX,REFS1);\
												} while (0)
#define ADC_RESULT_RIGHT_ADJUST()	(CLR_BIT(ADMUX,ADLAR))
#define ADC_RESULT_LEFT_ADJUST()	(SET_BIT(ADMUX,ADLAR))

#define ADC_SETPRESCALAR(Prescalar)	(ADCSRA|=Prescalar)
#define ADC_SETCHANNEL(channel)		do{(ADMUX&=0xE0);\
										(ADMUX|=channel);\
										}while(0)

#define ADC_START_CONVERSION()		(SET_BIT(ADCSRA,ADSC))





/*-------------------------Data Types Declarations---------------------------*/
typedef enum{
	ADC_CHANNEL_AN0=0,
	ADC_CHANNEL_AN1,
	ADC_CHANNEL_AN2,
	ADC_CHANNEL_AN3,
	ADC_CHANNEL_AN4,
	ADC_CHANNEL_AN5,
	ADC_CHANNEL_AN6,
	ADC_CHANNEL_AN7
}adc_channel_select_t;

typedef enum{
	ADC_CONVERSION_CLOCK_FOSC_DIV_2=0,
	ADC_CONVERSION_CLOCK_FOSC_DIV1_2=1,
	ADC_CONVERSION_CLOCK_FOSC_DIV_4,
	ADC_CONVERSION_CLOCK_FOSC_DIV_8,
	ADC_CONVERSION_CLOCK_FOSC_DIV_16,
	ADC_CONVERSION_CLOCK_FOSC_DIV_32,
	ADC_CONVERSION_CLOCK_FOSC_DIV_64,
	ADC_CONVERSION_CLOCK_FOSC_DIV_128,
}adc_conversion_clock_t;


typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void(*ADC_InterruptHandler)(void);
#endif
	adc_conversion_clock_t conversion_clock;
	adc_channel_select_t adc_channel;
	uint8 voltage_reference : 1;
	uint8 result_format : 1;//0 or 1
}adc_conf_t;

typedef uint16 adc_result_t;

/*-----------------------------SoftwaSre Interfaces Declarations-----------------------*/
STD_ReturnStatus ADC_Init(const adc_conf_t*_adc);
STD_ReturnStatus ADC_DeInit(const adc_conf_t*_adc);
STD_ReturnStatus ADC_SelectChannel(const adc_conf_t*_adc,adc_channel_select_t channel);
STD_ReturnStatus ADC_StartConversion(const adc_conf_t*_adc);
STD_ReturnStatus ADC_IsConversionDone(const adc_conf_t*_adc,uint8 *conversion_status);
STD_ReturnStatus ADC_GetConversionResult(const adc_conf_t*_adc,adc_result_t *conversion_result);
STD_ReturnStatus ADC_GetConversion_Blocking(const adc_conf_t*_adc,adc_channel_select_t channel,adc_result_t *conversion_result);
STD_ReturnStatus ADC_StartConversion_Interrupt(const adc_conf_t*_adc,adc_channel_select_t channel);
#endif /* MCAL_LAYER_04_ADC_MCAL_ADC_H_ */
