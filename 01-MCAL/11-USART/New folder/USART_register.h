/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: MCAL              	**********************/
/**************************     SWC		: USART             	**********************/
/**************************     Version	: 2.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR				*((volatile u8*)0x2C)		/* USART Data Register */

#define UCSRA			*((volatile u8*)0x2B)		/* USART Control and Status Register A */
#define UCSRA_RXC		7							/* USART Receive Complete bit */
#define UCSRA_TXC		6							/* USART Transmit Complete bit */
#define UCSRA_UDRE		5							/* USART Data Register Empty bit */

#define UCSRB			*((volatile u8*)0x2A)		/* USART Control and Status Register B */
#define UCSRB_RXEN		4							/* Receiver Enable bit */
#define UCSRB_TXEN		3							/* Transmitter Enable bit */
#define UCSRB_UCSZ2		2							/* Data size bit2 */

#define UCSRC			*((volatile u8*)0x40)		/* USART Control and Status Register C */
#define UCSRA_URSEL		7							/* Register select */
#define UCSRC_UMSEL		6							/* Mode Select */
#define UCSRC_UPM1		5 							/* Parity bit1 */
#define UCSRC_UPM0		4							/* Parity bit0 */
#define UCSRC_USBS		3							/* Stop Bit */
#define UCSRC_UCSZ1		2							/* Data size bit1 */
#define UCSRC_UCSZ0		1							/* Data size bit0 */

#define UBRRL		*((volatile u8*)0x29)			/* Baud rate Register Low */

#define UBRRH		*((volatile u8*)0x40)			/* Baud rate Register High */


#endif
