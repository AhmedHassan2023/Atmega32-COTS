/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    LED               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"


void LED_voidTurnON(LED_t* Copy_u8LED)
{
	DIO_u8SetPortDirection(Copy_u8LED->Port,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_OUTPUT);

	if(Copy_u8LED->Connection_Type== SRC)
	{
		DIO_u8SetPinValue(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_HIGH);
	}

	if(Copy_u8LED->Connection_Type== SINK)
	{
		DIO_u8SetPinValue(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_LOW);
	}
}

void LED_voidTurnOFF(LED_t* Copy_u8LED)
{
	DIO_u8SetPortDirection(Copy_u8LED->Port,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_OUTPUT);

	if(Copy_u8LED->Connection_Type== SRC)
	{
		DIO_u8SetPinValue(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_LOW);
	}

	if(Copy_u8LED->Connection_Type== SINK)
	{
		DIO_u8SetPinValue(Copy_u8LED->Port,Copy_u8LED->Pin,DIO_u8PIN_HIGH);
	}

}

