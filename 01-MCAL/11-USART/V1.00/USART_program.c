#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"

void USART_voidInit(void)
{
//	u8 Local_u8UCSRCValue=0;
//	SET_BIT(Local_u8UCSRCValue,7);
//	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
//	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
//
//	UCSRC=Local_u8UCSRCValue;

	/*1 Stop bit*/
	/*No parity*/
	/*Data bit*/
	/*Asynchronous*/
	   UCSRC =0b10000110;

	CLR_BIT(UCSRB,UCSRB_UCSZ2);

	/*9600bps Baud rate*/
	UBRRL=51;


	/*Enablling*/
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);

}

void USART_voidSendData(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);		/*Wait untill transmit buffer is empty*/
	UDR=Copy_u8Data;
}

u8 USART_u8Receive(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}
