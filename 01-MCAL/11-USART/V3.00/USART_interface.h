/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: MCAL              	**********************/
/**************************     SWC		: USART             	**********************/
/**************************     Version	: 2.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);

u8 USART_u8SendDataSynch(u8 Copy_u8Data);

u8 USART_u8ReceiveDataSynch(void);

void USART_voidSendStringSynch(char* Copy_pcString);

u8 USART_u8SendDataASynch(u8 Copy_u8Data,void (*Copy_pvNotificationFunc)(void));

u8 USART_u8ReceiveDataASynch(u8 *Copy_pu8Data,void (*Copy_pvNotificationFunc)(void));

u8 USART_u8ReceiveDataASynch2(void (*Copy_pvNotificationFunc)(u8));

#endif	/* USART_INTERFACE_H_ */
