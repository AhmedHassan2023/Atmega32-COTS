/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: MCAL              	**********************/
/**************************     SWC		: USART             	**********************/
/**************************     Version	: 2.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/* Baud rate = 9600 bps*/
#define BAUD_RATE_VALUE		51

/* USART Mode Select Options :	1- ASYNCHRONOUS
 * 								2- SYNCHRONOUS				*/
#define USART_MODE		ASYNCHRONOUS

/* USART Parity Mode Select Options :	1- DISABLED
 * 										2- EVEN_PARITY
 * 										3- ODD_PARITY		*/
#define PARITY_MODE		DISABLED

/* Stop Bit Options : 	1- ONE_BIT
 * 						2- TWO_BIT			 */
#define STOP_BIT		ONE_BIT

/* Data Size Options :		1- FIVE_BIT
 * 							2- SIX_BIT
 * 							3- SEVEN_BIT
 * 							4- EIGHT_BIT
 * 							5- NINE_BIT		*/
#define DATA_SIZE		EIGHT_BIT

#define USART_TIME_OUT		5000

#endif	/* USART_CONFIG_H_ */
