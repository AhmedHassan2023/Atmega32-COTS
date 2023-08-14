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

void ULTRASONIC_voidInit_SW(void);

void ULTRASONIC_voidStart_SW(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin);

u8 ULTRASONIC_u8GetDistance_SW(u8 Copy_u8TriggerPort,u8 Copy_u8TriggerPin);

#endif
