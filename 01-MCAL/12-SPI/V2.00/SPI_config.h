/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    SPI               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* Master/Slave mode Option:
 * 								 1- SPI_MASTER
 * 								 2- SPI_SLAVE */
#define SPI_MODE_SELECT			SPI_MASTER

/* SPI Clock Rate Select Options :
 * 								   1- SPI_CLK_OVER_4
 * 								   2- SPI_CLK_OVER_16
 * 								   3- SPI_CLK_OVER_64
 * 								   4- SPI_CLK_OVER_128
 * 								   5- SPI_CLK_OVER_2
 * 								   6- SPI_CLK_OVER_8
 * 								   7- SPI_CLK_OVER_32
 * 								   8- SPI_DCLK_OVER_64	  */
#define SPI_CLK_RATE		SPI_CLK_OVER_16

/* SPI Data Order Options :
 * 						    1- SPI_MSB
 * 						    2- SPI_LSB*/
#define SPI_DATA_ORDER		SPI_LSB

/* SPI Clock Polarity Options :
 * 								1- SPI_FALLING_EDGE
 * 								2- SPI_RISING_EDGE		*/
#define SPI_CLK_POL		SPI_RISING_EDGE

/* SPI Clock Ohase Options :
 * 							 1- SPI_SAMPLE
 * 							 2- SPI_SETUP */
#define SPI_CLK_PHASE		SPI_SAMPLE

#define SPI_u32_TIMEOUT		50000



#endif /*SPI_CONFIG_H_*/
