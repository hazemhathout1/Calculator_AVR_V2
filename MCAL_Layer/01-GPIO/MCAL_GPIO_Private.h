/*
 * MCAL_GPIO_Private.h
 *
 *  Created on: Aug 21, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_01_GPIO_MCAL_GPIO_PRIVATE_H_
#define MCAL_LAYER_01_GPIO_MCAL_GPIO_PRIVATE_H_
#include "MCAL_STD_TYPES.h"

#define PORTA *((volatile uint8*)0x3B)
#define PORTB *((volatile uint8*)0x38)
#define PORTC *((volatile uint8*)0x35)
#define PORTD *((volatile uint8*)0x32)

#define PINA *((volatile uint8*)0x39)
#define PINB *((volatile uint8*)0x36)
#define PINC *((volatile uint8*)0x33)
#define PIND *((volatile uint8*)0x30)

#define DDRA *((volatile uint8*)0x3A)
#define DDRB *((volatile uint8*)0x37)
#define DDRC *((volatile uint8*)0x34)
#define DDRD *((volatile uint8*)0x31)
//-----------------------------------------------
#define SREG *((volatile uint8*)0x5F)
#define SREG_I 7

#define MCUCR *((volatile uint8*)0x55)
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3
#define MCUCR_SM0 	4
#define MCUCR_SM1 	5
#define MCUCR_SM2 	6
#define MCUCR_SE    7

#define GICR *((volatile uint8*)0x5B)
#define GICR_INT0 6
#define GICR_INT1 7
#define GICR_INT2 5

#define GIFR *((volatile uint8*)0x5A)
#define GIFR_INTF1 7
#define GIFR_INTF0 6
#define GIFR_INTF2 5

#define MCUCSR *((volatile uint8*)0x54)
#define MCUSR_ISC2 6

//----------------------------------------------------
/* EEPROM Data Register */
#define EEDR	_SFR_IO8(0x1D)

/* EEPROM Address Register */
#define EEAR	_SFR_IO16(0x1E)
#define EEARL	_SFR_IO8(0x1E)
#define EEARH	_SFR_IO8(0x1F)

//------------------ADC Registers------------------------
#define ADMUX *((volatile u8*)0x27)
#define REFS0 6
#define REFS1 7
#define ADLAR 5

#define ADCSRA *((volatile u8*)0x26)
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

#define ADCL *((volatile u16*)0x24)
#define ADCH *((volatile u16*)0x25)

//------------------Timer Registers------------------------
//Timer 0
#define TCCR0 *((volatile u8*)0x53)
#define WGM00 6
#define WGM01 3
#define COM01 5
#define COM00 4
#define CS02 2
#define CS01 1
#define CS00 0

#define TCNT0 *((volatile u8*)0x52)

#define OCR0 *((volatile u8*)0x5C)


#define TIMSK *((volatile u8*)0x59)
#define TICIE1 5
#define OCIE0 1
#define TOIE0 0

#define TIFR *((volatile u8*)0x58)
#define OCF0 1
#define TOV0 0

/*Timer1 Servo*/

#define TCCR1A *((volatile u8*)0x4F)
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A 3
#define FOC1B 2
#define WGM11 1
#define WGM10 0


#define TCCR1B *((volatile u8*)0x4E)
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#define TCNT1L *((volatile u16*)0x4C)
#define OCR1AL *((volatile u16*)0x4A)
#define ICR1L *((volatile u16*)0x46)

//------------------SPI Registers------------------------
#define SPCR *((volatile u8*)0x2D)
#define SPIE 7
#define SPE  6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0
/*-----------------------------------*/
#define SPSR *((volatile u8*)0x2E)
#define SPIF 7
#define WCOL 6
#define SPI2X 0
#define SPDR *((volatile u8*)0x2F)






#endif /* MCAL_LAYER_01_GPIO_MCAL_GPIO_PRIVATE_H_ */
