/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    DC_Motor          **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DC_interface.h"
#include "DC_private.h"
#include "DC_config.h"


void DC_u8RCW(DC_t *Copy_u8DC)
{
	DIO_u8SetPinValue(Copy_u8DC->Port,Copy_u8DC->Pin2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_u8DC->Port,Copy_u8DC->Pin1,DIO_u8PIN_HIGH);
}

void DC_u8RCCW(DC_t *Copy_u8DC)
{
	DIO_u8SetPinValue(Copy_u8DC->Port,Copy_u8DC->Pin1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_u8DC->Port,Copy_u8DC->Pin2,DIO_u8PIN_HIGH);

}
