/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER2            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR2			*((volatile u8*)0x45)		/*Timer2 control register*/
#define TCCR2_WGM20		6							/*Waveform Generation Mode bit0*/
#define TCCR2_COM21		5							/*Compare match Output Mode bit 1*/
#define TCCR2_COM20		4							/*Compare match output Mode bit 0*/
#define TCCR2_WGM21		3							/*Waveform Generation Mode bit1*/
#define TCCR2_CS22		2							/*Prescaler bit2*/
#define TCCR2_CS21		1							/*Prescaler bit1*/
#define TCCR2_CS20		0							/*Prescaler bit0*/

#define TCNT2			*((volatile u8*)0x44)		/*Timer/Counter Register 2*/

#define OCR2			*((volatile u8*)0x43)		/*Output compare register 2*/

#define TIMSK			*((volatile u8*)0x59)		/*Timer mask*/
#define TIMSK_OCIE2		7							/*Output compare 2 interrupt enable bit 1*/
#define TIMSK_TOIE2		6							/*Timer/Counter 2 Overflow Interrupt Enable bit 0*/

#endif
