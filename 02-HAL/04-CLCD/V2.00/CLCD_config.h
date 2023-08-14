/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    CLCD              **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

/*Preprocessor file guard*/
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_DATA_PORT			DIO_u8PORTA
#define CLCD_D0					0
#define CLCD_D1					1
#define CLCD_D2					2
#define CLCD_D3					3
#define CLCD_D4					4
#define CLCD_D5					5
#define CLCD_D6					6
#define CLCD_D7					7

#define CLCD_CTRL_PORT			DIO_u8PORTC
#define CLCD_RS_PIN				DIO_u8PIN0
#define CLCD_RW_PIN				DIO_u8PIN1
#define CLCD_E_PIN				DIO_u8PIN2

/* CLCD MODES : 1- CLCD_8_BIT_MODE
 * 				2- CLCD_4_BIT_MODE*/
#define CLCD_MODE	CLCD_8_BIT_MODE


#endif
