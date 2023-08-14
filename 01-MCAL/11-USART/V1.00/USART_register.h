/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    USART             **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR		*((volatile u8*)0x2C)

#define UCSRA		*((volatile u8*)0x2B)
#define UCSRA_RXC	7
#define UCSRA_TXC	6
#define UCSRA_UDRE	5

#define UCSRB			*((volatile u8*)0x2A)
#define UCSRB_RXEN		4
#define UCSRB_TXEN		3
#define UCSRB_UCSZ2		2

#define UCSRC			*((volatile u8*)0x40)
#define UCSRA_URSEL		7		//Register select
#define UCSRC_UMSEL		6		//Mode Select
#define UCSRC_UPM1		5 		//Parity bit1
#define UCSRC_UPM0		4		//Parity bit0
#define UCSRC_UCSZ1		2
#define UCSRC_UCSZ0		1

#define UBRRL		*((volatile u8*)0x29)

#define UBRRH		*((volatile u8*)0x40)


#endif
