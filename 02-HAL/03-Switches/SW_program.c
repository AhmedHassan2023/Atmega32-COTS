/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    SW                **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"


u8 SW_u8GetState(SW_t* Copy_u8SW)
{
	u8 Local_u8SWValue=0;

	DIO_u8SetPinDirection(Copy_u8SW->Port,Copy_u8SW->Pin,DIO_u8PIN_INPUT);

	if(Copy_u8SW->Pull_Type==PULL_UP)
	{
		DIO_u8SetPinValue(Copy_u8SW->Port,Copy_u8SW->Pin,DIO_u8PIN_HIGH);

		DIO_u8GetPinValue(Copy_u8SW->Port,Copy_u8SW->Pin,&Local_u8SWValue);

		switch(Local_u8SWValue)
		{
		case 0  :  return PRESSED; break;
		case 1  :  return NOT_PRESSED;break;
		}
	}
	else if(Copy_u8SW->Pull_Type==PULL_DOWN)
		{
			DIO_u8GetPinValue(Copy_u8SW->Port,Copy_u8SW->Pin,&Local_u8SWValue);

			switch(Local_u8SWValue)
			{
			case 0  :  return NOT_PRESSED; break;
			case 1  :  return PRESSED;break;
			}
		}
}
