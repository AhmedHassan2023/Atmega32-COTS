/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    BUZZER            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER0_interface.h"

#include "BUZZER_interface.h"
#include "BUZZER_private.h"
#include "BUZZER_config.h"

void BUZZER_voidInit(void)
{
	TIMER0_voidInit(TIMER0_FAST_PWM,DIVIDE_BY_8);
	TIMER0_voidSetCompMatchOutputMode(NON_INVERTED_MODE);
}

void BUZZER_voidSetSoundMode(u8 Copy_u8State)
{
	switch(Copy_u8State)
	{
	case BUZZER_ON: TIMER0_voidSetDutyCycle(BUZZER_MAX_SOUND); break;
	case BUZZER_OFF: TIMER0_voidSetDutyCycle(BUZZER_SOUND_OFF); break;
	default: break;
	}

}

void BUZZER_voidSetSoundValue(u8 Copy_u8SoundValue)
{
	/*Set sound value from 0 ---> 100 */
	TIMER0_voidSetDutyCycle(Copy_u8SoundValue);
}
