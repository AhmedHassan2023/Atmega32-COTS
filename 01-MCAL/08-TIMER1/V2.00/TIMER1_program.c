/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER1            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER1_interface.h"
#include "TIMER1_registers.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"


static void(*TIMER1_pvCallBackFunc[4])(void)={NULL};

void  TIMER1_voidInit(u8 Copy_u8Mode,u8 Copy_u8Prescaler)
{
	switch(Copy_u8Mode)
	{
	case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_CTC_OCR1A_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_FAST_PWM_8_BIT_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_FAST_PWM_9_BIT_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_FAST_PWM_10_BIT_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_NODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PHASE_CORRECT_PWM_ICR1_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_CTC_ICR1_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_FAST_PWM_ICR1_MODE:
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	case TIMER1_FAST_PWM_OCR1A_MODE:
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		break;
	default:	 break;
	}

	/*Set Prescaler division factor*/
	TCCR1B &=PRESCALER_MASK;
	TCCR1B |=Copy_u8Prescaler;
}

/* Discription : TIMER0 Output Compare Match Initialization Function
 * 				to Select Output Compare Mode
 * Input : 1-Copy_u8CompOutPutMode , Options are : 1- NORMAL_OPERATION_MODE		--> Normal Port Operation, OC1A/OC1B is disconnected.
 * 											       2- NON_INVERTED_MODE :
 * 														a- Fast PWM : - Clear OC1A/OC1B on Copm match, Set OC1A/OC1B on TOP.
 * 														b- Phase correct PWM : - Clear OC1A/OC1B on compare match when up-counting,
 * 														 						  Set OC1A/OC1B on compare match when downcounting.
 * 												   3- INVERTED_MODE :
 * 														a- Fast PWM : - Set OC1A/OC1B on Copm match, Clear OC1A/OC1B on TOP.
 * 														b- Phase correct PWM : - Set OC1A/OC1B on compare match when up-counting,
 * 														 						  Clear OC1A/OC1B on compare match when downcounting.
 * 		  2- Copy_u8Channel : a- Compare Output Mode for Channel A COM1A1:0
 * 		  					  b- Compare Output Mode for Channel B COM1B1:0
 * Output: void
 * 	*/
void TIMER1_voidSetCompareOutputMode(u8 Copy_u8CompOutputMode, u8 Copy_u8Channel)
{
	switch(Copy_u8CompOutputMode)
	{
	case NORMAL_OPERATION_MODE:
		switch(Copy_u8Channel)
		{
		case TIMER1_OCR1A:
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
			break;
		case TIMER1_OCR1B:
			CLR_BIT(TCCR1A,TCCR1A_COM1B0);
			CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			break;
		default: break;
		}
		break;

		case NON_INVERTED_MODE:
			switch(Copy_u8Channel)
			{
			case TIMER1_OCR1A:
				CLR_BIT(TCCR1A,TCCR1A_COM1A0);
				SET_BIT(TCCR1A,TCCR1A_COM1A1);
				break;
			case TIMER1_OCR1B:
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				break;
			default : break;
			}
			break;

			case INVERTED_MODE:
				switch(Copy_u8Channel)
				{
				case TIMER1_OCR1A:
					SET_BIT(TCCR1A,TCCR1A_COM1A0);
					SET_BIT(TCCR1A,TCCR1A_COM1A1);
					break;
				case TIMER1_OCR1B:
					SET_BIT(TCCR1A,TCCR1A_COM1B0);
					SET_BIT(TCCR1A,TCCR1A_COM1B1);
					break;
				default : break;
				}
				break;

				default : break;
	}
}


void TIMER1_voidSetChannelACompMatchValue(u16 Copy_u16Value)
{
	OCR1A=Copy_u16Value;
}

void TIMER1_voidSetChannelBCompMatchValue(u16 Copy_u16Value)
{
	OCR1B=Copy_u16Value;
}

void TIMER1_voidSetTimerValue(u16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}

u16 TIMER1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void PWM1_voidInit(void)
{
	TIMER1_voidInit(TIMER1_FAST_PWM_ICR1_MODE,DIVIDE_BY_8);
	TIMER1_voidSetCompareOutputMode(NON_INVERTED_MODE,TIMER1_OCR1A);
}

void PWM1_voidDutyCycle(u16 Copy_u16Duty)
{
	if (Copy_u16Duty <= 100)
	{
		u16 Local_u16TimeOn = ((u32)Copy_u16Duty * (ICR1 +1)) /100;
		if(Local_u16TimeOn > 1)
		{
			OCR1A = Local_u16TimeOn-1;
		}
		else
		{
			OCR1A = 0;
		}
	}
	else
	{
		/*Return error*/
	}
}

void ICU_voidInit(void)
{
	/*set trigger source to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_u8SetTriggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_u8Edge==ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Edge==ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorStatus=NOK;
	}

	return Local_u8ErrorStatus;
}

void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadInputCaptureRegister(void)
{
	return ICR1;
}

void ICU_voidSetInputCaptureRegister(u16 Copy_u16Value)
{
	ICR1=Copy_u16Value;
}

void TIMER1_voidOVFInterrruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE1);
}

void TIMER1_voidOVFInterrruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE1);
}

u8 TIMER1_u8SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorStatus=OK;

	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER1_pvCallBackFunc[Copy_u8IntNumber]= Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}


void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(TIMER1_pvCallBackFunc[TIMER1_ICU] != NULL)
	{
		TIMER1_pvCallBackFunc[TIMER1_ICU]();
	}
	else
	{
		/*Do nothing*/
	}
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if(TIMER1_pvCallBackFunc[TIMER1_COMPA] != NULL)
	{
		TIMER1_pvCallBackFunc[TIMER1_COMPA]();
	}
	else
	{
		/*Do nothing*/
	}
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if(TIMER1_pvCallBackFunc[TIMER1_COMPB] != NULL)
	{
		TIMER1_pvCallBackFunc[TIMER1_COMPB]();
	}
	else
	{
		/*Do nothing*/
	}
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(TIMER1_pvCallBackFunc[TIMER1_OVF] != NULL)
	{
		TIMER1_pvCallBackFunc[TIMER1_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}


