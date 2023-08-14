#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"
#include "ULTRASONIC_private.h"

#include <util/delay.h>


static u16 Global_u16Time1,Global_u16Time2;
static u16 Global_u16Counter=0;
static u8 Global_u8Flag=3;


void ULTRASONIC_voidInit(void)
{
	/*Initialize timer 1 in normal mode ,set prescaler divide by 8 ----> ticktime= 1us */
	TIMER1_voidInit(TIMER1_NORMAL_MODE,DIVIDE_BY_8);
	TIMER1_u8SetCallBack(&ICU,TIMER1_ICU);
	TIMER1_u8SetCallBack(&OVF,TIMER1_OVF);


}

void ULTRASONIC_voidStart(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin)
{
	if(Global_u8Flag==0)
	{
		/*Send a Pulse to trigger pin for 10us*/
		DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_LOW);

		/*Set trigger source to rising edge, enable Input capture Interrupt*/
		ICU_voidInit();

		/*Enable Timer1 Overflow Interrupt*/
		TIMER1_voidOVFInterrruptEnable();

	}
}

u8 ULTRASONIC_u8GetDistance(u8 Copy_u8TriggerPort,u8 Copy_u8TriggerPin)
{
	u8 Local_u8Distace;
	u16 Local_u16Time=0;

	Global_u16Counter=0;
	Global_u8Flag=0;

	/*Send a Pulse to trigger pin for 10us*/
	DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_LOW);

	/*Set trigger source to rising edge, enable Input capture Interrupt*/
	ICU_voidInit();

	/*Polling until flag = 2 --> finishes*/
	while(Global_u8Flag<2);

	/*Distance in cm = (sound velocity * Timer )/2
	 * 	Time = ON Time + no of overflows counts* OverflowTicks (65535)
	 * 	ON Time = Time1 - Time2
	 * 	Time1 --> at the rising edge
	 * 	Time2 --> at the falling edge
	 * 	Sound velocity = 340 m/s
	 * 	Tick Time = Prescaler/Seytem Frequency = 1us
	 * so,
	 *		Distance = Time/58 */
	Local_u16Time = ((Global_u16Time2-Global_u16Time1) + ((u32)Global_u16Counter * OVERFLOW_TICKS));
	Local_u8Distace = Local_u16Time / 58;

	/*Disable input capture interrupt*/
	ICU_voidDisableInterrupt();

	return Local_u8Distace;
}

u8 ULTRASONIC_u8GetDistanceNoBlocking(u8 *Copy_pu8Distance)
{
	u8 Local_u8Distace;
	u16 Local_u16Time=0;

	if(Global_u8Flag == 2)
	{
		Local_u16Time = ((Global_u16Time2-Global_u16Time1) + ((u32)Global_u16Counter * OVERFLOW_TICKS));
		Local_u8Distace = Local_u16Time / 58;

		*Copy_pu8Distance = Local_u8Distace;

		TIMER1_voidOVFInterrruptEnable();

		Global_u8Flag=0;

		return 1;
	}

	return 0;
}

void ICU(void)
{
	if(Global_u8Flag==0)
	{
		Global_u16Counter=0;

		Global_u16Time1=ICU_u16ReadInputCaptureRegister();
		Global_u8Flag=1;
		ICU_u8SetTriggerEdge(ICU_FALLING_EDGE);
	}
	else if(Global_u8Flag==1)
	{
		Global_u16Time2=ICU_u16ReadInputCaptureRegister();
		Global_u8Flag=2;

		ICU_u8SetTriggerEdge(ICU_RISING_EDGE);

		ICU_voidDisableInterrupt();
		TIMER1_voidOVFInterrruptDisable();
	}
}

void OVF(void)
{
	Global_u16Counter++;
}
