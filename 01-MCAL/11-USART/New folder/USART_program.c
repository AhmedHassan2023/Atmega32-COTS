/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: MCAL              	**********************/
/**************************     SWC		: USART             	**********************/
/**************************     Version	: 2.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"

void USART_voidInit(void)
{
	u8 Local_u8UCSRCValue=0;

	/* Set Baud Rate Value */
	UBRRL=BAUD_RATE_VALUE;

	/* USART Mode */
#if USART_MODE == ASYNCHRONOUS
	/* Asynchronous Mode*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

#elif USART_MODE == SYNCHRONOUS
	/* Synchronous Mode*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

#else
#error ("Wrong USART Mode Select Option")
#endif

	/* USART Parity Mode */
#if PARITY_MODE == DISABLED
	/* Disabled Parity Mode */
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#elif PARITY_MODE == EVEN_PARITY
	/* Even Parity Mode */
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#elif PARITY_MODE == ODD_PARITY
	/* Odd Parity Mode */
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);

#else
#error ("Wrong Parity Mode Select Option")
#endif

	/* Stop Bit Selection */
#if STOP_BIT == ONE_BIT
	/* 1-Bit Stop */
	CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);
#elif STOP_BIT == TWO_BIT
	/* 2-Bit Stop */
	SET_BIT(Local_u8UCSRCValue,UCSRC_USBS);
#else
#error ("Wrong Stop Bit Option")
#endif

	/* Data Size Selection */
#if DATA_SIZE == FIVE_BIT
	/* Data Size 5-bit*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRCValue,UCSRB_UCSZ2);

#elif DATA_SIZE == SIX_BIT
	/* Data Size 6-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRCValue,UCSRB_UCSZ2);

#elif DATA_SIZE == SEVEN_BIT
	/* Data Size 7-bit*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRCValue,UCSRB_UCSZ2);

#elif DATA_SIZE == EIGHT_BIT
	/* Data Size 8-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRCValue,UCSRB_UCSZ2);

#elif DATA_SIZE == NINE_BIT
	/* Data Size 9-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRB_UCSZ2);

#else
#error ("Wrong Data Size Option")
#endif

	/* Assing Value dirct in UCSRC register */
	UCSRC = Local_u8UCSRCValue;

	/*Enablling*/
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);

}

void USART_voidSendData(u8 Copy_u8Data)
{
	/*Wait untill transmit buffer is empty*/
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);

	/* Put Data in Data Register */
	UDR=Copy_u8Data;
}

u8 USART_u8Receive(void)
{
	/* Wait untill Receive Complete*/
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);

	return UDR;
}

void USART_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;

	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		USART_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

