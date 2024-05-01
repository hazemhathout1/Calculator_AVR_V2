/*
 * MCAL_ADC.c
 *
 *  Created on: Sep 21, 2023
 *      Author: hazem
 */

#include "MCAL_ADC.h"


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*ADC_InterruptHandler)(void)=NULL;
#endif




static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t*_adc);

STD_ReturnStatus ADC_Init(const adc_conf_t*_adc)
{
	STD_ReturnStatus ret = E_NOT_OK;
	uint8 l_channel;
	if(NULL==_adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable the ADC */
		ADC_CONVERTER_DISABLE();
		/* Configure the conversion clock */
		ADC_SETPRESCALAR(_adc->conversion_clock);
		/* Configure the default channel*/
		l_channel=_adc->adc_channel;
		ADC_SETCHANNEL(l_channel);
		adc_input_channel_port_configure(_adc->adc_channel);
		/* Configure the interrupt */
		#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GlobalInterruptEnable();
		ADC_InterruptEnable();
		ADC_InterruptHandler = _adc->ADC_InterruptHandler;
		#endif
		/* Configure the result format*/
		select_result_format(_adc);
		/* Configure the voltage reference*/
		ADC_DISABLE_VOLTAGE_REFERENCE();//make Vref the internal VDD-->5v
		/* Enable the ADC*/
		ADC_CONVERTER_ENABLE();
	}
	return ret;
}

STD_ReturnStatus ADC_DeInit(const adc_conf_t*_adc)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==_adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable the ADC */
		ADC_CONVERTER_DISABLE();
		//Disable interrupt
		#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		ADC_InterruptDisable();
		#endif
	}
	return ret;
}
STD_ReturnStatus ADC_SelectChannel(const adc_conf_t*_adc,adc_channel_select_t channel)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==_adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Configure the default channel*/
		ADC_SETCHANNEL(channel);
		adc_input_channel_port_configure(channel);
	}
	return ret;
}
STD_ReturnStatus ADC_StartConversion(const adc_conf_t*_adc)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==_adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ADC_START_CONVERSION();
	}
	return ret;
}

/***
 *
 * @param _adc
 * @param conversion_status
 * @return true if conversion complete
 * 		   false if conversion is not complete
 */
STD_ReturnStatus ADC_IsConversionDone(const adc_conf_t*_adc,uint8 *conversion_status)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if((NULL==_adc)&&(NULL==conversion_status))
	{
		ret = E_NOT_OK;
	}
	else
	{
		//if ADC_CONVERSION_STATUS() get value of 1 then the conversion is ongoing else the conversion is done
		*conversion_status=(uint8)(!ADC_CONVERSION_STATUS());//
	}
	return ret;
}

/***
 *
 * @param _adc
 * @param conversion_result
 * @return
 */
STD_ReturnStatus ADC_GetConversionResult(const adc_conf_t*_adc,adc_result_t *conversion_result)
{
	STD_ReturnStatus ret = E_NOT_OK;
	uint16 low;
	if((NULL==_adc)&&(NULL==conversion_result))
	{
		ret = E_NOT_OK;
	}
	else
	{
		if(_adc->result_format==ADC_RIGHT_ADJUST)
		{
			low=(uint16)ADCL;
//			*conversion_result=(adc_result_t)(ADCH<<8)+ADCL;
			*conversion_result=(uint16)ADCH*256;
			*conversion_result+=low;
		}
		else if(_adc->result_format==ADC_LEFT_ADJUST)
		{
			*conversion_result=(adc_result_t)(((ADCH<<8)+ADCL)>>6);
		}
	}
	return ret;
}
STD_ReturnStatus ADC_GetConversion_Blocking(const adc_conf_t*_adc,adc_channel_select_t channel,adc_result_t *conversion_result)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if((NULL==_adc)&&(NULL==conversion_result))
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Select channel */
		ret = ADC_SelectChannel(_adc,channel);
		/* Start adc conversion */
		ret = ADC_StartConversion(_adc);
		/* check conversion*/
		while(ADSC==1);
		ret = ADC_GetConversionResult(_adc,conversion_result);
	}
	return ret;
}



static inline void adc_input_channel_port_configure(adc_channel_select_t channel)
{
	switch(channel)
	{
	case ADC_CHANNEL_AN0:	CLR_BIT(DDRA,PIN0);break;
	case ADC_CHANNEL_AN1:	CLR_BIT(DDRA,PIN1);break;
	case ADC_CHANNEL_AN2:	CLR_BIT(DDRA,PIN2);break;
	case ADC_CHANNEL_AN3:	CLR_BIT(DDRA,PIN3);break;
	case ADC_CHANNEL_AN4:	CLR_BIT(DDRA,PIN4);break;
	case ADC_CHANNEL_AN5:	CLR_BIT(DDRA,PIN5);break;
	case ADC_CHANNEL_AN6:	CLR_BIT(DDRA,PIN6);break;
	case ADC_CHANNEL_AN7:	CLR_BIT(DDRA,PIN7);break;
	}
}


static inline void select_result_format(const adc_conf_t*_adc)
{
	if(_adc->result_format==ADC_RIGHT_ADJUST)
	{
		ADC_RESULT_RIGHT_ADJUST();
	}
	else if(_adc->result_format==ADC_LEFT_ADJUST)
	{
		ADC_RESULT_LEFT_ADJUST();
	}
}

STD_ReturnStatus ADC_StartConversion_Interrupt(const adc_conf_t*_adc,adc_channel_select_t channel)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==_adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Select channel */
		ret = ADC_SelectChannel(_adc,channel);
		/* Start adc conversion */
		ret = ADC_StartConversion(_adc);
	}
	return ret;
}

void ADC_ISR()
{
	/* clear flag*/
	ADC_InterruptFlagClear();
	if(ADC_InterruptHandler)
	{
		ADC_InterruptHandler();
	}
}
