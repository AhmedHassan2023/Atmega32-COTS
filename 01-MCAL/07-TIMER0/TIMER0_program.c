/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER0            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_register.h"
#include "Timer0_private.h"
#include "TIMER0_config.h"


static void(*TIMER0_pvCallBackFunc[2])(void)={NULL};

void TIMER0_voidInit(u8 Copy_u8Mode, u8 Copy_u8Prescaler)
{
	/*Select Waveform generation mode*/
	switch(Copy_u8Mode)
	{
	case TIMER0_NORMAL_MODE: CLR_BIT(TCCR0,TCCR0_WGM00); CLR_BIT(TCCR0,TCCR0_WGM01); break;
	case TIMER0_PHASE_CORRECT_PWM :SET_BIT(TCCR0,TCCR0_WGM00); CLR_BIT(TCCR0,TCCR0_WGM01); break;
	case TIMER0_CTC: CLR_BIT(TCCR0,TCCR0_WGM00); SET_BIT(TCCR0,TCCR0_WGM01); break;
	case TIMER0_FAST_PWM: SET_BIT(TCCR0,TCCR0_WGM00); SET_BIT(TCCR0,TCCR0_WGM01); break;
	default: break;
	}


	/*Set Prescaler division factor*/
	TCCR0 &=PRESCALER_MASK;
	TCCR0 |=Copy_u8Prescaler;

}

void TIMER0_voidSetCompMatchOutputMode(u8 Copy_u8CompOutputMode)
{
	/*Select Compare match Output mode*/
	switch(Copy_u8CompOutputMode)
	{
	case NORMAL_OPERATION_MODE : CLR_BIT(TCCR0,TCCR0_COM00); CLR_BIT(TCCR0,TCCR0_COM01); break;
	case NON_INVERTED_MODE: CLR_BIT(TCCR0,TCCR0_COM00); SET_BIT(TCCR0,TCCR0_COM01); break;
	case INVERTED_MODE : SET_BIT(TCCR0,TCCR0_COM00); SET_BIT(TCCR0,TCCR0_COM01); break;
	default : break;
	}

}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void TIMER0_voidSetTimerValue(u8 Copy_u8Value)
{
	TCNT0 = Copy_u8Value;
}

u8 TIMER0_u8ReadTimerValue(void)
{
	return TCNT0;
}

void TIMER0_voidCompMatchInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_OCIE1);
}

void TIMER0_voidCompMatchInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_OCIE1);
}

void TIMER0_voidOVFInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE0);
}

void TIMER0_voidOVFInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE0);
}

void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle <= 100)
	{
		u8 Local_u8TimeOn = ((u16)Copy_u8DutyCycle * (TIMER0_MAX_COUNT))/100 ;

		if(Local_u8TimeOn >1)
		{
			OCR0 = TIMER0_MAX_COUNT-Local_u8TimeOn;
		}
		else
		{
			OCR0 = 0;
		}
	}
	else
	{
		/*return Error*/
	}
}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorStatus=OK;

	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER0_pvCallBackFunc[Copy_u8IntNumber]= Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;

}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc[TIMER0_COMP] != NULL)
	{
		TIMER0_pvCallBackFunc[TIMER0_COMP]();
	}
	else
	{
		/*Do nothing*/
	}
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(TIMER0_pvCallBackFunc[TIMER0_OVF] != NULL)
	{
		TIMER0_pvCallBackFunc[TIMER0_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}
