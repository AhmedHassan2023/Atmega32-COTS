/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    ADC               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ADC_CONIF_H_
#define ADC_CONIF_H_

/*Options:
			1- AREF			-> AREF, Internal Vref turned off
			2- AVCC			-> AVCC with external capacitor at AREF pin
			3- INTENAL		-> Internal 2.56V Voltage Reference with external capacitor at AREF pin

							 */
#define ADC_VREF	AVCC

/*Options:
			1- ADC_8_BITS_RESOLUTION
			2- ADC_10_BITS_RESOLUTION
							 */
#define ADC_RESOLUTION	ADC_8_BITS_RESOLUTION


/*These bits determine the division factor between the XTAL frequency and the input clock to the ADC.
  Options:
				1- DIVIDE_BY_2
				2- DIVIDE_BY_4
				3- DIVIDE_BY_8
				4- DIVIDE_BY_16
				5- DIVIDE_BY_32
				6- DIVIDE_BY_64
				7- DIVIDE_BY_128
			*/


#define ADC_PRESCALAR	DIVIDE_BY_128

#define ADC_u32TIMEOUT		50000


#endif
