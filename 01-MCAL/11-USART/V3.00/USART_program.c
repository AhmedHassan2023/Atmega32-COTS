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

static void (*USART_pvRXCCallBackFunc) (void)   = NULL;
static void (*USART_pvTXCCallBackFunc) (void) = NULL;
static void (*USART_pvUDRECallBackFunc)(void) = NULL;

static u8 *USART_u8ReceiveData = NULL ;

u8 USART_u8BusyState = USART_IDLE;

void USART_voidInit(void)
{
	u8 Local_u8UCSRCValue=0;

	CLR_BIT(UCSRA,UCSRA_U2X);

	/* Set Bit 7 to one to write on UCSRC register*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

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
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif DATA_SIZE == SIX_BIT
	/* Data Size 6-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif DATA_SIZE == SEVEN_BIT
	/* Data Size 7-bit*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif DATA_SIZE == EIGHT_BIT
	/* Data Size 8-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif DATA_SIZE == NINE_BIT
	/* Data Size 9-bit*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(UCSRB,UCSRB_UCSZ2);

#else
#error ("Wrong Data Size Option")
#endif

	/* Assing Value dirct in UCSRC register */
	UCSRC = Local_u8UCSRCValue;


	/* Set Baud Rate Value */
	UBRRL=BAUD_RATE_VALUE;
	UBRRH=0;	//(BAUD_RATE_VALUE>>8);

	/*Enablling*/
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);

}

u8 USART_u8SendDataSynch(u8 Copy_u8Data)
{
	u8 Local_u8ErrorStatus = OK ;

	u32 Local_u32TimeOut   = 0  ;

	/* Put Data in Data Register */
	UDR=Copy_u8Data;

	/*Wait untill transmit buffer is empty*/
	while((GET_BIT(UCSRA,UCSRA_TXC)==0) && (Local_u32TimeOut < USART_TIME_OUT))
	{
		Local_u32TimeOut ++;
	}

	if(Local_u32TimeOut == USART_TIME_OUT)
	{
		Local_u8ErrorStatus = NOK ;
	}
	else
	{
		/* Clear Flag */
		SET_BIT(UCSRA,UCSRA_TXC);
	}

	return Local_u8ErrorStatus;

}

u8 USART_u8ReceiveDataSynch(void)
{
	u32 Local_u32TimeOut 	= 0 ;
	u8 Local_u8Data    		= 0 ;

	/* Wait untill Receive Complete*/
	while((GET_BIT(UCSRA,UCSRA_RXC)==0) && (Local_u32TimeOut < USART_TIME_OUT))
	{
		Local_u32TimeOut++;
	}

	if(Local_u32TimeOut == USART_TIME_OUT)
	{
		Local_u8Data = 255;
	}
	else
	{
		Local_u8Data = UDR ;
	}

	return Local_u8Data;
}

void USART_voidSendStringSynch(char* Copy_pcString)
{
	u8 Local_u8Counter=0;

	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		/* Send Data Byte by Byte , Array Of Characters*/
		USART_u8SendDataSynch(Copy_pcString[Local_u8Counter]);

		/* Increment The Iterator*/
		Local_u8Counter++;
	}
}


u8 USART_u8SendDataASynch(u8 Copy_u8Data,void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pvNotificationFunc == NULL)
	{
		Local_u8ErrorStatus = NULL_POINTER ;
	}
	else
	{
		/* Make USART Busy*/
		USART_u8BusyState = USART_BUSY;

		/* Enable USART  Interrupt */
		SET_BIT(UCSRB,UCSRB_TXCIE);

		/* Put Data in Data Register */
		UDR = Copy_u8Data;

		/* Initialize The CallBack Notification Function Globally */
		USART_pvTXCCallBackFunc = Copy_pvNotificationFunc;

	}

	return Local_u8ErrorStatus;
}

u8 USART_u8ReceiveDataASynch(u8 *Copy_pu8Data,void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErroeStatus = OK;

	if((Copy_pu8Data == NULL ) || (Copy_pvNotificationFunc == NULL))
	{
		Local_u8ErroeStatus = NULL_POINTER ;
	}
	else
	{
		/* Check if Data is Received or not */
		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
		{
			*Copy_pu8Data = UDR ;
			Copy_pvNotificationFunc();
		}
		else
		{
			/* Enable Receive Interrupt */
			SET_BIT(UCSRB,UCSRB_RXCIE);

			/* Initialize Receiving Data Variable Globally  */
			USART_u8ReceiveData = Copy_pu8Data ;

			/* Initialize thr CallBack Function Globally */
			USART_pvRXCCallBackFunc = Copy_pvNotificationFunc ;
		}
	}

	return Local_u8ErroeStatus ;
}

//u8 USART_u8ReceiveDataASynch2(void (*Copy_pvNotificationFunc)(u8))
//{
//	u8 Local_u8ErrorStatus = OK ;
//
//	if(Copy_pvNotificationFunc == NULL)
//	{
//		Local_u8ErrorStatus = NULL_POINTER ;
//	}
//	else
//	{
//		/* Check if Data is Received or not */
//		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
//		{
//			Copy_pvNotificationFunc(UDR);
//		}
//		else
//		{
//			/* Enable Receive Interrupt */
//			SET_BIT(UCSRB,UCSRB_RXCIE);
//
//			/* Initialize thr CallBack Function Globally */
//			USART_pvRXCCallBackFunc = Copy_pvNotificationFunc ;
//
//		}
//	}
//
//	return Local_u8ErrorStatus ;
//
//}

void __vector_13 (void)		__attribute__((signal));
void __vector_13 (void)
{
	/* Reading The Received Data */
	*USART_u8ReceiveData = UDR ;

	/* Invoke Receive Complete CallBack Function */
	USART_pvRXCCallBackFunc();

	/* Clear Interrupt Flag */
	CLR_BIT(UCSRB,UCSRB_RXCIE);

}

void __vector_14 (void)		__attribute__((signal));
void __vector_14 (void)
{
	/* Invoke Data Register Empty CallBack Function */
	USART_pvUDRECallBackFunc();

	/* Clear Interrupt */
	CLR_BIT(UCSRB,UCSRB_UDRIE);
}

void __vector_15 (void)		__attribute__((signal));
void __vector_15 (void)
{
	/*Make USART State IDLE*/
	USART_u8BusyState = USART_IDLE;

	/* Invoke Transmition Complete CallBack Function */
	USART_pvTXCCallBackFunc();

	/* Disable USART Interrupt */
	CLR_BIT(UCSRB,UCSRB_TXCIE);

}

