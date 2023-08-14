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

#define TCCR1A			*((volatile u8*)0x4F)		/*Timer/Counter1 Control Register A*/		
#define TCCR1A_COM1A1	7							/*Compare Output Mode for Channel A bit 1*/
#define TCCR1A_COM1A0	6							/*Compare Output Mode for Channel A bit 0*/
#define TCCR1A_COM1B1	5							/*Compare Output Mode for Channel B bit 1*/
#define TCCR1A_COM1B0	4							/*Compare Output Mode for Channel B bit 0*/
#define TCCR1A_WGM11	1							/*Waveform Generation Mode bit1*/
#define TCCR1A_WGM10	0							/*Waveform Generation Mode bit0*/


#define TCCR1B 			*((volatile u8*)0x4E)		/*Timer/Counter1 Control Register B*/
#define TCCR1B_ICNC1	7							/*Input Capture Noise Canceler*/
#define TCCR1B_ICES1	6							/*Input Capture Edge Select*/
#define TCCR1B_WGM13	4							/*Waveform Generation Mode bit 3*/
#define TCCR1B_WGM12	3							/*Waveform Generation Mode bit 2*/
#define TCCR1B_CS12		2							/*Prescaler bit2*/
#define TCCR1B_CS11		1							/*Prescaler bit1*/
#define TCCR1B_CS10		0							/*Prescaler bit0*/

#define TCNT1 			*((volatile u16*)0x4C)		/*TIMER/Counter1 Register*/

#define ICR1			*((volatile u16*)0x46)		/*Input capture register 1*/

#define OCR1A			*((volatile u16*)0x4A)		/*Output compare register 1 A*/
#define OCR1B			*((volatile u16*)0x48)		/*Output Compare register 1 B*/

#define TIMSK			*((volatile u8*)0x59)		/*Timer Interrupt mask*/
#define TIMSK_TICIE1	5							/*Timer/Counter1 Input Capture Interrupt Enable*/
#define TIMSK_OCIE1A	4							/*Timer/Counter1 Output Compare A Match Interrupt Enable*/
#define TIMSK_OCIE1B	3							/*Timer/Cunter1 Output Compare B Match Interrupt Enable*/
#define TIMSK_TOIE1		2							/*Timer/Counter1 Overflow Interrupt Enable*/

#endif
