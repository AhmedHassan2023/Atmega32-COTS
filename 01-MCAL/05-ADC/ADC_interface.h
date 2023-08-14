/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    ADC               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define AREF		1
#define AVCC		2
#define INTERNAL	3

#define ADC_8_BITS_RESOLUTION	1
#define ADC_10_BITS_RESOLUTION	2

#define DIVIDE_BY_2		0
#define DIVIDE_BY_4		2
#define DIVIDE_BY_8		3
#define DIVIDE_BY_16	4
#define DIVIDE_BY_32	5
#define DIVIDE_BY_64	6
#define DIVIDE_BY_128	7

#define PRESCALAR_MASK		0b11111000
#define ADMUX_Mask			0b11100000


void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u8* Copy_pu8Reading);

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, u8* Copy_pu8Reading, void(*Copy_pvNotificationFunv)(void));



#endif
