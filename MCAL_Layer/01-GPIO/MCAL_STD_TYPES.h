/*
 * MCAL_STD_TYPES.h
 *
 *  Created on: Aug 21, 2023
 *      Author: hazem
 */

#ifndef MCAL_LAYER_01_GPIO_MCAL_STD_TYPES_H_
#define MCAL_LAYER_01_GPIO_MCAL_STD_TYPES_H_



/* Section : Includes */
#include "string.h"


/* Section : Macro Function Declarations */



/* Section : Data Types Declarations */
typedef int sint32;
typedef long long int sint64;
typedef unsigned long long int uint64;
typedef unsigned int uint32;
typedef short int sint16;
typedef unsigned short int uint16;
typedef char sint8;
typedef unsigned char uint8;
typedef float float32;
typedef double float64;
typedef long double float128;

typedef uint8 STD_ReturnStatus;//Return type of any function from now on, it may return E_Ok,E_NOT_OK
//uint 8 Func()==Std_ReturnType Func()



/* Section : Macro Declarations*/
#define STD_HIGH       		0x01
#define STD_LOW        		0x00

#define STD_ON         		0x01
#define STD_OFF        		0x00

#define STD_ACTIVE     		0x01
#define STD_IDLE       		0x00

#define E_OK		(STD_ReturnStatus)0x01
#define E_NOT_OK	(STD_ReturnStatus)0x00

#define PORT_OUTPUT    		0xFF
#define PORT_INPUT     		0x00

#define ZERO_INIT			0
#define NULL ((void *)0)


/* Section : User type Declarations */



#endif /* MCAL_LAYER_01_GPIO_MCAL_STD_TYPES_H_ */
