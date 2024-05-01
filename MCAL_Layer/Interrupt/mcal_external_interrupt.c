/*
 * mcal_external_interrupt.c
 *
 *  Created on: Sep 18, 2023
 *      Author: hazem
 */
#include "mcal_external_interrupt.h"

static void(*INT0_InterruptHandler)(void)=NULL;
static void(*INT1_InterruptHandler)(void)=NULL;
static void(*INT2_InterruptHandler)(void)=NULL;

static STD_ReturnStatus interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static STD_ReturnStatus interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static STD_ReturnStatus interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static STD_ReturnStatus interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static STD_ReturnStatus interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);
/***
 *
 * @param INT0_InterruptHandler
 * Function betakhid pointer to function for call back
 */
static STD_ReturnStatus INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnStatus INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnStatus INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnStatus interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


/***
 *
 * @param int_obj
 * @return
 */
STD_ReturnStatus interrupt_INTx_init(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/*	Disable the External Interrupt*/
		ret = interrupt_INTx_Disable(int_obj);
		/*	Clear Interrupt Flag : External interrupt did not occur*/
		ret = interrupt_INTx_Clear_Flag(int_obj);
		/*	configure External interrupt edge*/
		ret = interrupt_INTx_Edge_Init(int_obj);
		/*	configure External interrupt I/O pin*/
		ret = interrupt_INTx_Pin_Init(int_obj);
		/*	configure Default Interrupt Call Back*/
		ret = interrupt_INTx_SetInterruptHandler(int_obj);
		/*	Enable the External Interrupt*/
		ret = interrupt_INTx_Enable(int_obj);
	}
	return ret;
}


void INT0_ISR(void)
{
	/* Clear flag*/
	EXT_INT0_InterruptFlagClear();
	/* Code */

	/*	call back */
	if(INT0_InterruptHandler)
	{
		INT0_InterruptHandler();
	}
}


void INT1_ISR(void)
{
	/* Clear flag*/
	EXT_INT1_InterruptFlagClear();
	/* Code */

	/*	call back */
	if(INT1_InterruptHandler)
	{
		INT1_InterruptHandler();
	}
}


void INT2_ISR(void)
{
	/* Clear flag*/
	EXT_INT2_InterruptFlagClear();
	/* Code */

	/*	call back */
	if(INT2_InterruptHandler)
	{
		INT2_InterruptHandler();
	}
}


/***
 *
 * @param int_obj
 * @return
 */
STD_ReturnStatus interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = interrupt_INTx_Disable(int_obj);
	}
	return ret;
}


static STD_ReturnStatus interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(int_obj->source)
		{
		case INTERRUPT_EXTERNAL_INT0:
			INTERRUPT_GlobalInterruptEnable();
			EXT_INT0_InterruptEnable();
			ret = E_OK;
			break;
		case INTERRUPT_EXTERNAL_INT1:
			INTERRUPT_GlobalInterruptEnable();
			EXT_INT1_InterruptEnable();
			ret = E_OK;
			break;
		case INTERRUPT_EXTERNAL_INT2:
			INTERRUPT_GlobalInterruptEnable();
			EXT_INT2_InterruptEnable();
			ret = E_OK;
			break;
		default:ret=E_NOT_OK;
		}

	}
	return ret;
}


static STD_ReturnStatus interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(int_obj->source)
		{
		case INTERRUPT_EXTERNAL_INT0:
			EXT_INT0_InterruptDisable();
			ret = E_OK;
			break;
		case INTERRUPT_EXTERNAL_INT1:
			EXT_INT1_InterruptDisable();
			ret = E_OK;
			break;
		case INTERRUPT_EXTERNAL_INT2:
			EXT_INT2_InterruptDisable();
			ret = E_OK;
			break;
		default:ret=E_NOT_OK;
		}

	}
	return ret;
}


static STD_ReturnStatus interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(int_obj->source)
				{
				case INTERRUPT_EXTERNAL_INT0:
					if(int_obj->edge==INTERRUPT_FALLING_EDGE){EXT_INT0_FallingEdgeSet(); }
					else if(int_obj->edge==INTERRUPT_RISING_EDGE){EXT_INT0_RisingEdgeSet();}
					ret = E_OK;
					break;
				case INTERRUPT_EXTERNAL_INT1:
					if(int_obj->edge==INTERRUPT_FALLING_EDGE){EXT_INT1_FallingEdgeSet(); }
					else if(int_obj->edge==INTERRUPT_RISING_EDGE){EXT_INT1_RisingEdgeSet();}
					ret = E_OK;
					break;
				case INTERRUPT_EXTERNAL_INT2:
					if(int_obj->edge==INTERRUPT_FALLING_EDGE){EXT_INT2_FallingEdgeSet(); }
					else if(int_obj->edge==INTERRUPT_RISING_EDGE){EXT_INT2_RisingEdgeSet();}
					ret = E_OK;
					break;
				default:ret=E_NOT_OK;
				}
	}
	return ret;
}

static STD_ReturnStatus interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
	}
	return ret;
}



static STD_ReturnStatus interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(int_obj->source)
				{
				case INTERRUPT_EXTERNAL_INT0:
					EXT_INT0_InterruptFlagClear();
					ret = E_OK;
					break;
				case INTERRUPT_EXTERNAL_INT1:
					EXT_INT1_InterruptFlagClear();
					ret = E_OK;
					break;
				case INTERRUPT_EXTERNAL_INT2:
					EXT_INT2_InterruptFlagClear();
					ret = E_OK;
					break;
				default:ret=E_NOT_OK;
				}
	}
	return ret;
}





static STD_ReturnStatus INT0_SetInterruptHandler(void(*InterruptHandler)(void))
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT0_InterruptHandler = InterruptHandler;//hena hakhaly el address bta3 el func in app yeb2a shaylo el INT0_InterruptHandler
		//keda 3amalat callback be hes en function fel application layer a2dar astakhdemha dlw2ty fel MCAL layer
		ret = E_OK;
	}
	return ret;
}
static STD_ReturnStatus INT1_SetInterruptHandler(void(*InterruptHandler)(void))
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT1_InterruptHandler = InterruptHandler;//hena hakhaly el address bta3 el func in app yeb2a shaylo el INT0_InterruptHandler
		//keda 3amalat callback be hes en function fel application layer a2dar astakhdemha dlw2ty fel MCAL layer
		ret = E_OK;
	}
	return ret;
}
static STD_ReturnStatus INT2_SetInterruptHandler(void(*InterruptHandler)(void))
{
	STD_ReturnStatus ret = E_NOT_OK;
	if(NULL==InterruptHandler)
	{
		ret = E_NOT_OK;
	}
	else
	{
		INT2_InterruptHandler = InterruptHandler;//hena hakhaly el address bta3 el func in app yeb2a shaylo el INT0_InterruptHandler
		//keda 3amalat callback be hes en function fel application layer a2dar astakhdemha dlw2ty fel MCAL layer
		ret = E_OK;
	}
	return ret;
}
static STD_ReturnStatus interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
	STD_ReturnStatus ret = E_NOT_OK;
		if(NULL==int_obj)
		{
			ret = E_NOT_OK;
		}
		else
		{
			switch(int_obj->source)
			{
			case INTERRUPT_EXTERNAL_INT0:
				ret = INT0_SetInterruptHandler(int_obj->EXT_INTERRUPTHANDLER);//hena ana ba3at el address bta3 el function bta3 el application
				break;
			case INTERRUPT_EXTERNAL_INT1:
				ret = INT1_SetInterruptHandler(int_obj->EXT_INTERRUPTHANDLER);
				break;
			case INTERRUPT_EXTERNAL_INT2:
				ret = INT2_SetInterruptHandler(int_obj->EXT_INTERRUPTHANDLER);
				break;
			default:ret=E_NOT_OK;
			}

		}
		return ret;
}
