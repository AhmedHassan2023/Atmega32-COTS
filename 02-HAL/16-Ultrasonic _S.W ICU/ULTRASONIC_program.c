#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "EXTI_interface.h"

#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"
#include "ULTRASONIC_private.h"

#include <util/delay.h>

void OVF(void);
void ICU_SW(void);

static u16 Global_u16Time1,Global_u16Time2;
static u16 Global_u16Counter=0;
static u8 Global_u8Flag=3;

void ULTRASONIC_voidInit_SW(void)
{
	/*Initialize timer 1 in normal mode ,set prescaler divide by 8 ----> ticktime= 1us , Set Timer1 Value = 0 at beginning*/

	TIMER1_voidInit(TIMER1_NORMAL_MODE,DIVIDE_BY_8);
	TIMER1_u8SetCallBack(&OVF,TIMER1_OVF);
	TIMER1_voidSetTimerValue(0);

	/*Initialize INT0 rising Edge and enable it  */
	EXTI_u8Int0SetCallBack(&ICU_SW);
	EXTI_voidInt0Init();

}

void ULTRASONIC_voidStart_SW(u8 Copy_u8TriggerPort, u8 Copy_u8TriggerPin)
{
	if(Global_u8Flag==0)
	{
		/*Send a Pulse to trigger pin for 10us*/
		DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_LOW);

		/*Enable INT0 Interrupt*/
		EXTI_voidInt0Init();

		/*Enable Timer1 Overflow Interrupt*/
		TIMER1_voidOVFInterrruptEnable();

	}
}

u8 ULTRASONIC_u8GetDistance_SW(u8 Copy_u8TriggerPort,u8 Copy_u8TriggerPin)
{
	u8 Local_u8Distace;
	u16 Local_u16Time=0;

	Global_u16Counter=0;
	Global_u8Flag=0;


	/*Send a Pulse to trigger pin for 10us*/
	DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(Copy_u8TriggerPort,Copy_u8TriggerPin,DIO_u8PIN_LOW);

	/*Set trigger source to rising edge, enable INT0 Interrupt*/
	EXTI_voidInt0Init();

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

	Local_u16Time = ((Global_u16Time2-Global_u16Time1) + ((u16)Global_u16Counter * OVERFLOW_TICKS));
	Local_u8Distace = Local_u16Time /58;

	EXTI_u8IntDisable(INT0);

	return Local_u8Distace;
}



void ICU_SW(void)
{
	if(Global_u8Flag==0)
	{
		Global_u16Counter =0;
		/*Second rising edge*/
		Global_u16Time1=TIMER1_u16ReadTimerValue();
		/*Change trigger to falling edge*/
		EXTI_u8Int0SetSenseControl(FALLING_EDGE);
		Global_u8Flag=1;
	}
	else if(Global_u8Flag==1)
	{
		/*Timer reading now is period ticks + on ticks*/
		Global_u16Time2=TIMER1_u16ReadTimerValue();

		Global_u8Flag=2;
		/*Disable IN0 interrupt*/
		EXTI_u8Int0SetSenseControl(RISING_EDGE);

		EXTI_u8IntDisable(INT0);
		TIMER1_voidOVFInterrruptDisable();

	}
}

void OVF(void)
{
	Global_u16Counter++;
}
