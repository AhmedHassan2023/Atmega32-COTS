/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: HAL	              	**********************/
/**************************     SWC		: BLUETOOTH            	**********************/
/**************************     Version	: 1.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

#include "BLUETOOTH_interface.h"
#include "BLUETOOTH_private.h"
#include "BLUETOOTH_config.h"

void BLUETOOTH_voidInit(void)
{
	/* USART Initialize*/
	USART_voidInit();
	
}

void BLUETOOTH_voidSendData(u8 Copy_u8Data)
{
	/* Send Data*/
	USART_voidSendData(Copy_u8Data);
}

u8 BLUETOOTH_u8ReceiveData(void)
{
	u8 Local_u8DataReceived = 0;

	/* Recieve Data */
	Local_u8DataReceived = USART_u8Receive();
	
	return Local_u8DataReceived;
}

void BLUETOOTH_voidSendString(const char* Copy_pcString)
{
	/* Send String Data */
	USART_voidSendString(Copy_pcString);
	
}

void BLUETOOTH_voidSendNumber(u32 Copy_u32Number)
{
	u32 Local_u32Reversed = 1;

	if(Local_u32Reversed == 0)
	{
		BLUETOOTH_voidSendData('0');
	}

	while(Copy_u32Number != 0)
	{
		Local_u32Reversed = ((Local_u32Reversed * 10) + (Copy_u32Number % 10));
		Copy_u32Number /= 10;
	}

	while(Local_u32Reversed != 1)
	{
		BLUETOOTH_voidSendData((Local_u32Reversed % 10) + 48);
		Local_u32Reversed /= 10;
	}
	
}
