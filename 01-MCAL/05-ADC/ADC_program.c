/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    ADC               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_register.h"

/*Asynchronous global Variables*/
static u8* ADC_pu8Reading=NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)=NULL;

u8 ADC_u8BusyState = IDLE;

void ADC_voidInit(void)
{
#if(ADC_VREF==AREF)
	{
		/*AREF as reference voltage*/
		CLR_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);
	}

#elif(ADC_VREF==AVCC)
	{
		/*AVCC as reference voltage*/
		SET_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);
	}
#elif(ADC_VREF==INTERNAL)
	{
		/*Internal 2.56v as reference voltage */
		SET_BIT(ADMUX,ADMUX_REFS0);
		SET_BIT(ADMUX,ADMUX_REFS1);
	}
#else
#error "Wrong Reference Voltage Configuration"
#endif


#if(ADC_RESOLUTION==ADC_8_BITS_RESOLUTION)
	{
		/*Activate Left Adjust result*/
		SET_BIT(ADMUX,ADMUX_ADLAR);
	}
#elif(ADC_RESOLUTION==ADC_10_BITS_RESOLUTION)
	{
		/*Activate Right Adjust result*/
		CLR_BIT(ADMUX,ADMUX_ADLAR);
	}
#else
#error "Wrong Resolution Configuration"
#endif


	/*Set Prescaler division factor*/
	ADCSRA &=PRESCALAR_MASK;
	ADCSRA |=ADC_PRESCALAR;

	/*Enable peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u8* Copy_pu8Reading)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;

	if(ADC_u8BusyState == IDLE)
	{
		/*ADC is now BUSY*/
		ADC_u8BusyState =BUSY;

		/*Clear the MUX bits in ADMUX register*/
		ADMUX &=ADMUX_Mask;

		/*Set the required Channel into the MUX bits*/
		ADMUX|=Copy_u8Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Polling (busy waiting) until the conversion complete flag is set or Counter reaching timeout value*/
		while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0) && (Local_u32Counter != ADC_u32TIMEOUT));
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==ADC_u32TIMEOUT)
		{
			/*Loop is broken because the timeout is reached*/
			Local_u8ErrorState=NOK;
		}
		else
		{
			/*Loop is broken because flag is raised*/

			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*Return the reading if : 1- 8 bits resolution return ADCH --> Left Adjust
			 * 						  2- 10 bits resolution return ADC --> ADCL+ADCH */
#if(ADC_RESOLUTION == ADC_8_BITS_RESOLUTION)
			{
				*Copy_pu8Reading=ADCH;
			}
#elif(ADC_RESOLUTION == ADC_10_BITS_RESOLUTION)
			{
				*Copy_pu8Rading=ADC;
			}
#endif
			/*ADC is finished, return it to IDLE*/
			ADC_u8BusyState=IDLE;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, u8* Copy_pu8Reading, void(*Copy_pvNotificationFunv)(void))
{
	u8 Local_u8ErrorState=OK;

	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_pu8Reading == NULL || Copy_pvNotificationFunv == NULL)
		{
			Local_u8ErrorState=NULL_POINTER;
		}
		else
		{
			/*Make ADC busy in order not to work until being IDLE*/
			ADC_u8BusyState = BUSY;

			/*Initialize the reading variable globally*/
			ADC_pu8Reading=Copy_pu8Reading;

			/*Initialize the callback notification function globally*/
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunv;

			/*Clear the MUX bits in ADMUX register*/
			ADMUX &=ADMUX_Mask;

			/*Set the required Channel into the MUX bits*/
			ADMUX|=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC Interrupt Enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;

}

void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{
	/*Read ADC result*/
#if(ADC_RESOLUTION == ADC_8_BITS_RESOLUTION)
	{
		*ADC_pu8Reading = ADCH;
	}
#elif(ADC_RESOLUTION == ADC_10_BITS_RESOLUTION)
	{
		*ADC_pu8Reading = ADC;
	}
#endif


	/*make ADC state be IDLE because it finished*/
	ADC_u8BusyState = IDLE;

	/*Invoke the callback notification function*/
	ADC_pvCallBackNotificationFunc();

	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}

