/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 21 Aug 2023				 ***********************/
/* Layer   	: HAL           		   	 ***********************/
/* SWC      : CLCD           			 ***********************/
/* Version 	: 2.00             			 ***********************/
/***************************************************************/
#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

/* Initialization Mode Configuaration */
#define FOUR_BITS_MODE		0
#define EIGHT_BITS_MODE		1

/* Cursor Display Configuration */
#define CURSOR_DISPLAY_ON		1
#define CURSOR_DISPLAY_OFF		2
#define CURSOR_BLINK_ON			3
#define CURSOR_BLINK_OFF		4


static void CLCD_voidSetDataPort(u8 Copy_u8Data);

static void CLCD_voidSetHalfDataPort(u8 Copy_u8Data);

static void CLCD_voidSendEnablePulse(void);




#endif	/* CLCD_PRIVATE_H_ */
