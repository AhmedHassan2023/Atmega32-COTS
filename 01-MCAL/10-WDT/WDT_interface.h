/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    WDT               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#define WDT_DISABLE_MASK		0b00011000
#define TURN_OFF				0

#define WDT_PRESCALER_MASK		0b11111000

/*Watchdog Timer Prescaler*/
#define WDT_PRESCALER_16K		0
#define WDT_PRESCALER_32K		1
#define WDT_PRESCALER_64K		2
#define WDT_PRESCALER_128K		3
#define WDT_PRESCALER_256K		4
#define WDT_PRESCALER_512K		5
#define WDT_PRESCALER_1024K		6
#define WDT_PRESCALER_2048K		7

void WDT_voidEnable(void);

void WDT_voidDisable(void);

void WDT_voidSleep(u8 Copy_u8SleepTime);

#endif
