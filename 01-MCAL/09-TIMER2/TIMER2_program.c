/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER2            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER2_interface.h"
#include "TIMER2_register.h"
#include "Timer2_private.h"
#include "TIMER2_config.h"


static void(*TIMER2_pvCallBackFunc[2])(void)={NULL};

void TIMER2_voidInit(u8 Copy_u8Mode, u8 Copy_u8Prescaler)
{
	/*Select Waveform generation mode*/
	switch(Copy_u8Mode)
	{
	case TIMER2_NORMAL_MODE: CLR_BIT(TCCR2,TCCR2_WGM20); CLR_BIT(TCCR2,TCCR2_WGM21); break;
	case TIMER2_PHASE_CORRECT_PWM :SET_BIT(TCCR2,TCCR2_WGM20); CLR_BIT(TCCR2,TCCR2_WGM21); break;
	case TIMER2_CTC: CLR_BIT(TCCR2,TCCR2_WGM20); SET_BIT(TCCR2,TCCR2_WGM21); break;
	case TIMER2_FAST_PWM: SET_BIT(TCCR2,TCCR2_WGM20); SET_BIT(TCCR2,TCCR2_WGM21); break;
	default: break;
	}


	/*Set Prescaler division factor*/
	TCCR2 &=PRESCALER_MASK;
	TCCR2 |=Copy_u8Prescaler;

}

void TIMER2_voidSetCompMatchOutputMode(u8 Copy_u8CompOutputMode)
{
	/*Select Compare match Output mode*/
	switch(Copy_u8CompOutputMode)
	{
	case NORMAL_OPERATION_MODE : CLR_BIT(TCCR2,TCCR2_COM20); CLR_BIT(TCCR2,TCCR2_COM21); break;
	case NON_INVERTED_MODE: CLR_BIT(TCCR2,TCCR2_COM20); SET_BIT(TCCR2,TCCR2_COM21); break;
	case INVERTED_MODE : SET_BIT(TCCR2,TCCR2_COM20); SET_BIT(TCCR2,TCCR2_COM21); break;
	default : break;
	}

}

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR2 = Copy_u8Value;
}

void TIMER2_voidSetTimerValue(u8 Copy_u8Value)
{
	TCNT2 = Copy_u8Value;
}

u8 TIMER2_u8ReadTimerValue(void)
{
	return TCNT2;
}

void TIMER2_voidCompMatchInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_OCIE2);
}

void TIMER2_voidCompMatchInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_OCIE2);
}

void TIMER2_voidOVFInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE2);
}

void TIMER2_voidOVFInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE2);
}

void TIMER2_voidSetDutyCycle(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle <= 100)
	{
		u8 Local_u8TimeOn = ((u16)Copy_u8DutyCycle * (TIMER2_MAX_COUNT))/100 ;

		if(Local_u8TimeOn >1)
		{
			OCR2 = TIMER2_MAX_COUNT-Local_u8TimeOn;
		}
		else
		{
			OCR2 = 0;
		}
	}
	else
	{
		/*return Error*/
	}
}

u8 TIMER2_u8SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorStatus=OK;

	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER2_pvCallBackFunc[Copy_u8IntNumber]= Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;

}

void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if(TIMER2_pvCallBackFunc[TIMER2_COMP] != NULL)
	{
		TIMER2_pvCallBackFunc[TIMER2_COMP]();
	}
	else
	{
		/*Do nothing*/
	}
}

void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if(TIMER2_pvCallBackFunc[TIMER2_OVF] != NULL)
	{
		TIMER2_pvCallBackFunc[TIMER2_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}
