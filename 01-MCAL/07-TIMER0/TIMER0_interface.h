/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER0            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


/*Waveform Generation Mode :
								1- TIMER0_NORMAL_MODE
								2- TIMER0_PHASE_CORRECT_PWM
								3- TIMER0_CTC
								4- TIMER0_FAST_PWM
 */

#define TIMER0_NORMAL_MODE				0
#define TIMER0_PHASE_CORRECT_PWM		1
#define TIMER0_CTC						2
#define TIMER0_FAST_PWM					3

/*Prescaler : 1- NO_CLK_SOURCE 
			  2- NO_PRESCALING
			  3- DIVIDE_BY_8
			  4- DIVIDE_BY_64
			  5- DIVIDE_BY_256
			  6- DIVIDE_BY_1024
			  7- EXTERNAL_FALLING_EDGE
			  8- EXTERNAL_RISING_EDGE
 */

#define NO_CLK_SOURCE				0
#define NO_PRESCALING				1
#define DIVIDE_BY_8					2
#define DIVIDE_BY_64				3
#define DIVIDE_BY_256				4
#define DIVIDE_BY_1024				5
#define EXTERNAL_FALLING_EDGE		6
#define EXTERNAL_RISING_EDGE		7

/*Prescaler Mask */
#define PRESCALER_MASK				0b11111000

/*Max counts that could Reach*/
#define TIMER0_MAX_COUNT			255

/*Compare Match Output Mode:
 * 								1- NORMAL_OPERATION_MODE		--> Normal Port Operation, OC0 is disconnected.
 * 								2- NON_INVERTED_MODE :
 * 														a- Fast PWM : - Clear OC0 on Copm match, Set OC0 on TOP.
 * 														b- Phase correct PWM : - Clear OC0 on compare match when up-counting,
 * 														 						  Set OC0 on compare match when downcounting.
 * 								3- INVERTED_MODE :
 * 														a- Fast PWM : - Set OC0 on Copm match, Clear OC0 on TOP.
 * 														b- Phase correct PWM : - Set OC0 on compare match when up-counting,
 * 														 						  Clear OC0 on compare match when downcounting.
 * 													*/

#define NORMAL_OPERATION_MODE		0
#define NON_INVERTED_MODE			1
#define INVERTED_MODE 				2

/*Interrubt Source*/
#define TIMER0_OVF					0
#define TIMER0_COMP					1

/* Discription: TIMER0 Initialization Function to select Timer Mode and Prescaler.
 * Input : 1- Copy_u8Mode, Options are : 1- TIMER0_NORMAL_MODE
 * 										 2- TIMER0_PHASE_CORRECT_PWM
 * 										 3- TIMER0_CTC
 * 										 4- TIMER0_FAST_PWM
 * 		   2- Copy_u8Prescaler, Options are : 1- NO_CLK_SOURCE
			  	  	  	  	  	  	  	  	  2- NO_PRESCALING
			  	  	  	  	  	  	  	  	  3- DIVIDE_BY_8
			  	  	  	  	  	  	  	  	  4- DIVIDE_BY_64
			  	  	  	  	  	  	  	  	  5- DIVIDE_BY_256
			  	  	  	  	  	  	  	  	  6- DIVIDE_BY_1024
			  	  	  	  	  	  	  	  	  7- EXTERNAL_FALLING_EDGE
			  	  	  	  	  	  	  	  	  8- EXTERNAL_RISING_EDGE
   Output: void
   				*/

void TIMER0_voidInit(u8 Copy_u8Mode, u8 Copy_u8Prescaler);

/* Discription : TIMER0 Output Compare Match Initialization Function
 * 				to Select Output Compare Mode
 * Input : Copy_u8CompOutPutMode , Options are : 1- NORMAL_OPERATION_MODE		--> Normal Port Operation, OC0 is disconnected.
 * 											     2- NON_INVERTED_MODE :
 * 														a- Fast PWM : - Clear OC0 on Copm match, Set OC0 on TOP.
 * 														b- Phase correct PWM : - Clear OC0 on compare match when up-counting,
 * 														 						  Set OC0 on compare match when downcounting.
 * 												 3- INVERTED_MODE :
 * 														a- Fast PWM : - Set OC0 on Copm match, Clear OC0 on TOP.
 * 														b- Phase correct PWM : - Set OC0 on compare match when up-counting,
 * 														 						  Clear OC0 on compare match when downcounting.
 * Output: void
 * 	*/
void TIMER0_voidSetCompMatchOutputMode(u8 Copy_u8CompOutputMode);

/* Discription : TIMER0 Set Output Compare Register OCR0 Value Function.
 * Input  : Copy_u8Value : Compare Match Value ( 0 ---> 255) at Which the Compare Match event will happen
 * Output : void
 *  */
void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);

/*Discription : TIMER0 Set Timer/Counter Register TCNT0 Value Function
 * Input  : Copy_u8Value : Timer/Counter value (0--->255)
 * Output : void
 * */
void TIMER0_voidSetTimerValue(u8 Copy_u8Value);

/*Discription : TIMER0 Get (Read) Timer/Counter Register TCNT0 Value Function
 * Input  : void
 * Output : void
 * */
u8 TIMER0_u8ReadTimerValue(void);

/* Discription : TIMER0 Compare Match Interrupt Enable Function.
 * Input  : void
 * Output : void*/
void TIMER0_voidCompMatchInterruptEnable(void);

/* Discription : TIMER0 Compare Match Interrupt Disable Function.
 * Input  : void
 * Output : void*/
void TIMER0_voidCompMatchInterruptDisable(void);

/* Discription : TIMER0 Overflow Interrupt Enable Function.
 * Input  : void
 * Output : void*/
void TIMER0_voidOVFInterruptEnable(void);

/* Discription : TIMER0 Overflow Interrupt Disable Function.
 * Input  : void
 * Output : void*/
void TIMER0_voidOVFInterruptDisable(void);

void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle);

/* Discription : Function used to Communicate with the ISR function
 * 				 in APP Layer (The CallBack Function TIMER0)
 * Inputs: 1- Pointer to Function Array that Points to the first line in ISR Function
 * 		   2- Copy_u8IntNumber : ID of Interrupt Source   Options are :
 * 		   																1- TIMER0_OVF    -----> first element in the array function  that points to Overflow Interrupt ISR.
 * 			  															2- TIMER0_COMP   -----> second element in the array function that points to Compare Match Interrupt ISR.
 *
 * Output : Local_u8StateError.	   */
u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber);


#endif
