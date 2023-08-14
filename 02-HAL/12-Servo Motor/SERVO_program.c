/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    SERVO             **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "SERVO_interface.h"
#include "SERVO_config.h"
#include "SERVO_private.h"


void SERVO_voidInit(void)
{
	TIMER1_voidInit(TIMER1_FAST_PWM_ICR1_MODE,DIVIDE_BY_8);
	TIMER1_voidSetCompareOutputMode(NON_INVERTED_MODE,TIMER1_OCR1A);

	/*20000 us to get freq 50Hz, Periodtime = 20ms */
	ICU_voidSetInputCaptureRegister(TOP_VALUE);

	/*Angle Zero at 1000us, Ontime : 1ms------->2ms
	 * 							     1000us------->2000us
	 * Practically Servo works in Rang : 750us ------> 2500us
	 * 									 0 degree ----->180 degree*/
	TIMER1_voidSetChannelACompMatchValue(MIN_VALUE);
	
}

void SERVO_voidSetAngle(u8 Copy_u8Angle)
{
	u16 Local_u16Result = (((u32)Copy_u8Angle * (MAX_VALUE-MIN_VALUE))/ANGLE_180)+ MIN_VALUE ;
	TIMER1_voidSetChannelACompMatchValue(Local_u16Result);
}
