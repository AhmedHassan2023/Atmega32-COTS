/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER0            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0			*((volatile u8*)0x53)		/*Timer0 control register*/
#define TCCR0_WGM00		6							/*Waveform Generation Mode bit0*/
#define TCCR0_COM01		5							/*Compare match Output Mode bit 1*/
#define TCCR0_COM00		4							/*Compare match output Mode bit 0*/
#define TCCR0_WGM01		3							/*Waveform Generation Mode bit1*/
#define TCCR0_CS02		2							/*Prescaler bit2*/
#define TCCR0_CS01		1							/*Prescaler bit1*/
#define TCCR0_CS00		0							/*Prescaler bit0*/

#define TCNT0			*((volatile u8*)0x52)		/*Timer/Counter Register 0*/

#define OCR0			*((volatile u8*)0x5C)		/*Output compare register 0*/

#define TIMSK			*((volatile u8*)0x59)		/*Timer mask*/
#define TIMSK_OCIE1		1							/*Output compare 0 interrupt enable bit 1*/
#define TIMSK_TOIE0		0							/*Timer/Counter0 Overflow Interrupt Enable bit 0*/

#endif
