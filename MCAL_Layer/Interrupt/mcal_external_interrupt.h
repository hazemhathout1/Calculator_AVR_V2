/*
 * mcal_external_interrupt.h
 *
 *  Created on: Sep 18, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_INTERRUPT_MCAL_EXTERNAL_INTERRUPT_H_
#define MCAL_LAYER_INTERRUPT_MCAL_EXTERNAL_INTERRUPT_H_

/*---------------------------INCLUDES------------------------*/
#include "mcal_interrupt_config.h"
/*------------------------MACRO Declarations----------------*/

/*------------------------MACRO functions Declarations------------------*/
#if EXTERNAL_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*			External Interrupt 0		*/

/*macro Function to disable interrupt*/
#define EXT_INT0_InterruptDisable()		(CLR_BIT(GICR,GICR_INT0))
/*macro Function to enable interrupt*/
#define EXT_INT0_InterruptEnable()		(SET_BIT(GICR,GICR_INT0))
/*macro Function to clear interrupt flag*/
#define EXT_INT0_InterruptFlagClear()	(SET_BIT(GIFR,GIFR_INTF0))
/*macro Function to set Rising edge*/
#define EXT_INT0_RisingEdgeSet()   \
    do {                           \
        SET_BIT(MCUCR, MCUCR_ISC00);\
        SET_BIT(MCUCR, MCUCR_ISC01);\
    } while (0)
/*macro Function to set falling edge*/
#define EXT_INT0_FallingEdgeSet()		(SET_BIT(MCUCR,MCUCR_ISC01))

/*			External Interrupt 1		*/

/*macro Function to disable interrupt*/
#define EXT_INT1_InterruptDisable()		(CLR_BIT(GICR,GICR_INT1))
/*macro Function to enable interrupt*/
#define EXT_INT1_InterruptEnable()		(SET_BIT(GICR,GICR_INT1))
/*macro Function to clear interrupt flag*/
#define EXT_INT1_InterruptFlagClear()	(SET_BIT(GIFR,GIFR_INTF1))
/*macro Function to set Rising edge*/
#define EXT_INT1_RisingEdgeSet()   \
    do {                           \
        SET_BIT(MCUCR, MCUCR_ISC10);\
        SET_BIT(MCUCR, MCUCR_ISC11);\
    } while (0)
/*macro Function to set falling edge*/
#define EXT_INT1_FallingEdgeSet()		(SET_BIT(MCUCR,MCUCR_ISC11))


/*			External Interrupt 2		*/

/*macro Function to disable interrupt*/
#define EXT_INT2_InterruptDisable()		(CLR_BIT(GICR,GICR_INT2))
/*macro Function to enable interrupt*/
#define EXT_INT2_InterruptEnable()		(SET_BIT(GICR,GICR_INT2))
/*macro Function to clear interrupt flag*/
#define EXT_INT2_InterruptFlagClear()	(SET_BIT(GIFR,GIFR_INTF2))
/*macro Function to set Rising edge*/
#define EXT_INT2_FallingEdgeSet()		(CLR_BIT(MCUCSR,MCUSR_ISC2))
/*macro Function to set falling edge*/
#define EXT_INT2_RisingEdgeSet()		(SET_BIT(MCUCSR,MCUSR_ISC2))
#endif



/*-------------------------Data Types Declarations---------------------------*/
typedef enum{
	INTERRUPT_FALLING_EDGE=0,
	INTERRUPT_RISING_EDGE

}interrupt_INTx_edge;

typedef enum{
	INTERRUPT_EXTERNAL_INT0=0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef struct{
	void (*EXT_INTERRUPTHANDLER)(void);//call back function
	Pin_Config_t mcu_pin;
	interrupt_INTx_edge edge;
	interrupt_INTx_src source;
}interrupt_INTx_t;

/*-----------------------------Software Interfaces Declarations-----------------------*/
STD_ReturnStatus interrupt_INTx_init(const interrupt_INTx_t *int_obj);
STD_ReturnStatus interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj);

#endif /* MCAL_LAYER_INTERRUPT_MCAL_EXTERNAL_INTERRUPT_H_ */
