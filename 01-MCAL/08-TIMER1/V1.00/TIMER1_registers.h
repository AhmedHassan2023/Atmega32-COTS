/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER1            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER1_REGISTER_H_
#define TIMER1_REGISTER_H_

#define TCCR1A			*((volatile u8*)0x4F)
#define TCCR1A_COM1A1	7
#define TCCR1A_COM1A0	6
#define TCCR1A_WGM11	1		/*Waveform Generation Mode bit1*/
#define TCCR1A_WGM10	0		/*Waveform Generation Mode bit0*/


#define TCCR1B 			*((volatile u8*)0x4E)	
#define TCCR1B_CS12		2		/*Prescaler bit2*/
#define TCCR1B_CS11		1		/*Prescaler bit1*/
#define TCCR1B_CS10		0		/*Prescaler bit0*/

#define ICR1	*((volatile u16*)0x46)		/*Input capture register 1*/

#define OCR1A	*((volatile u16*)0x4A)		/*Output compare register 1*/



#endif