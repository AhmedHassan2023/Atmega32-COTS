/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL              **********************/
/**************************     SWC:    SSD               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"
#include <util/delay.h>



void SSD_voidSetNumber(SSD_t* Copy_u8SSD,u8 Copy_u8Number)
{
	u8 Local_u8SSDValue[10]=SSD_ARR_VAL;

	DIO_u8SetPortDirection(Copy_u8SSD->Port,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(Copy_u8SSD->Enable_Port,Copy_u8SSD->Enable_Pin,DIO_u8PIN_OUTPUT);
	if(Copy_u8SSD->Com_Type == SSD_u8ComCathode)
	{
		DIO_u8SetPinValue(Copy_u8SSD->Enable_Port,Copy_u8SSD->Enable_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPortValue(Copy_u8SSD->Port,Local_u8SSDValue[Copy_u8Number]);
	}
	else if(Copy_u8SSD->Com_Type == SSD_u8ComAnode)
	{
		DIO_u8SetPinValue(Copy_u8SSD->Enable_Port,Copy_u8SSD->Enable_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPortValue(Copy_u8SSD->Port,Local_u8SSDValue[Copy_u8Number]);
	}

}

void SSD_voidMultiplex(SSD_t* Copy_u8SSD1,SSD_t* Copy_u8SSD2,u8 Copy_u8Number1,u8 Copy_u8Number2)
{

	SSD_voidSetNumber(Copy_u8SSD1,Copy_u8Number1);
	DIO_u8SetPinValue(Copy_u8SSD2->Enable_Port,Copy_u8SSD2->Enable_Pin,DIO_u8PIN_HIGH);
	_delay_ms(10);
	SSD_voidSetNumber(Copy_u8SSD2,Copy_u8Number2);
	DIO_u8SetPinValue(Copy_u8SSD1->Enable_Port,Copy_u8SSD1->Enable_Pin,DIO_u8PIN_HIGH);
	_delay_ms(10);
}

