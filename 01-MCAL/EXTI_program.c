/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    EXTI              **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_register.h"
#include "EXTI_config.h"

void EXTI_voidInt0Init(void)
{
	/*Sense control for INT0: ISC01  ISC00
	 	 	 	 	 	 	   0      0   --> LOW Level
	 	 	 	 	 	 	   0      1   --> Any logical Change
	 	 	 	 	 	 	   1      0   --> The falling edge
	 	 	 	 	 	 	   1      1   --> The rising edge*/

	/*Set sense control for INT0 to falling edge */
	SET_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);

	/*Peripheral interrupt enable for INT0*/
	SET_BIT(GICR,GICR_INT0);
}

void EXTI_voidInt1Init(void)
{
	/*Sense control for INT1: ISC11  ISC10
		 	 	 	 	 	   0      0   --> LOW Level
		 	 	 	 	 	   0      1   --> Any logical Change
		 	 	 	 	 	   1      0   --> The falling edge
		 	 	 	 	 	   1      1   --> The rising edge*/

	/*Set Sense control for INT1 to falling edge */
	SET_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);

	/*Peripheral interrupt enable for INT0*/
	SET_BIT(GICR,GICR_INT1);

}

void EXTI_voidInt2Init(void)
{
	/*Sense control for INT2:
	 	 	 	 	 	 	 0 --> falling edge
	 	 	 	 	 	 	 1 --> rising edge */

	/*Set Sense control for INT2 to */
	SET_BIT(MCUCSR,MCUCSR_INT2);

	/*Peripheral interrupt enable for INT0*/
	SET_BIT(GICR,GICR_INT2);
}



