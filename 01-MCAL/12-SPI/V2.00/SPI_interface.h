/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    SPI               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define SPI_MASTER		1
#define SPI_SLAVE		2

#define SPI_CLK_OVER_4		1
#define SPI_CLK_OVER_16		2
#define SPI_CLK_OVER_64		3
#define SPI_CLK_OVER_128	4
#define SPI_CLK_OVER_2		5
#define SPI_CLK_OVER_8		6
#define SPI_CLK_OVER_32		7
#define SPI_DCLK_OVER_64	8

#define SPI_MSB		1
#define SPI_LSB		2

#define SPI_FALLING_EDGE	1
#define SPI_RISING_EDGE		2

#define SPI_SAMPLE			1
#define SPI_SETUP			2


void SPI_voidInit(void);

u8 SPI_u8TransceiveSynch(,u8 *Copy_pu8ReceivedData,u8 Copy_u8SendData);

u8 SPI_u8TransceiveSynch(u8 *Copy_pu8ReceivedData,u8 Copy_u8SendData,void(*Copy_pvNotificationFunc)(void));

#endif /*SPI_INTERFACE_H_*/
