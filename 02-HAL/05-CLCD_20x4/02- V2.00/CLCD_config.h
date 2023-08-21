/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 21 Aug 2023				 ***********************/
/* Layer   	: HAL           		   	 ***********************/
/* SWC      : CLCD           			 ***********************/
/* Version 	: 2.00             			 ***********************/
/***************************************************************/
/*Preprocessor file guard*/
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* Data Length Mode Options :	1- FOUR_BITS_MODE
 * 								2- EIGHT_BITS_MODE	 */
#define CLCD_DATA_LENGTH_MODE 		FOUR_BITS_MODE

/* Data Port */
#define CLCD_DATA_PORT					DIO_u8PORTC

/* Eight Data Bits */
#define CLCD_D0_PIN		DIO_u8PIN0
#define CLCD_D1_PIN		DIO_u8PIN1
#define CLCD_D2_PIN		DIO_u8PIN2
#define CLCD_D3_PIN		DIO_u8PIN3
#define CLCD_D4_PIN		DIO_u8PIN4
#define CLCD_D5_PIN		DIO_u8PIN5
#define CLCD_D6_PIN		DIO_u8PIN6
#define CLCD_D7_PIN		DIO_u8PIN7


/* Control Port & Pins */
#define CLCD_CTRL_PORT			DIO_u8PORTA
#define CLCD_RS_PIN				DIO_u8PIN7
#define CLCD_RW_PIN				DIO_u8PIN6
#define CLCD_E_PIN				DIO_u8PIN5

/* Cursor Configuartion */
#define CURSOR_DISPLAY		CURSOR_DISPLAY_OFF
#define CURSOR_BLINK		CURSOR_BLINK_OFF



#endif
