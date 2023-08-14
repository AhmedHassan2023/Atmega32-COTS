/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    ULTRASONIC        **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#define OVERFLOW_TICKS		65535

void ULTRASONIC_voidInit(void);

void ULTRASONIC_voidStart(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin);

u8 ULTRASONIC_u8GetDistance(u8 Copy_u8TriggerPort,u8 Copy_u8TriggerPin);

u8 ULTRASONIC_u8GetDistanceNoBlocking(u8 *Copy_pu8Distance);



#endif
