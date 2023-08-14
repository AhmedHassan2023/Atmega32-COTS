/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    EXTI              **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#define INT0			1
#define INT1			2
#define INT2			3


void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);


/*   Description: A Function to set the Required sense control using the Postbuild Configuration
 *   Input : Copy_u8Sense , Options are : 1- LOW_LEVEL
 *   									  2- ON_CHANGE
 *   									  3- FALLING_EDGE
 *   									  4- RISING_EDGE
 *   Output: Error Status with type u8
 *   */
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense);

u8 EXTI_u8Int1SetSenseControl(u8 Copy_u8Sense);

u8 EXTI_u8Int2SetSenseControl(u8 Copy_u8Sense);

/*   Description: A Function to set the Required Peripheral  Interrupt using the Postbuild Configuration
 *   Input : Copy_u8Int , Options are :   1- INT0
 *   									  2- INT1
 *   									  3- INT2
 *   Output: Error Status with type u8
 *   */
u8 EXTI_u8IntEnable(u8 Copy_Int);

u8 EXTI_u8IntDisable(u8 Copy_Int);

/*   Description: A Function to take ISR address using callback it will take the address of ISR function in APP layer
 * 	 and call it from MCAL layer ---> CallBack
 *   Input : Pointer to function  Copy_pvInt0Func
 *   Output: Error Status with type u8
 *   */
u8 EXTI_u8Int0SetCallBack(void(*Copy_pvInt0Func)(void));

u8 EXTI_u8Int1SetCallBack(void(*Copy_pvInt1Func)(void));

u8 EXTI_u8Int2SetCallBack(void(*Copy_pvInt2Func)(void));




#endif
