/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    TIMER1            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER1_INTRFACE_H_
#define TIMER1_INTERFACE_H_

/*Waveform Generation Mode :
 * 								1-TIMER1_NORMAL_MODE
 * 								2-TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE
 * 								3-TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE
 * 								4-TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE
 * 								5-TIMER1_CTC_OCR1A_MODE
 * 								6-TIMER1_FAST_PWM_8_BIT_MODE
 * 								7-TIMER1_FAST_PWM_8_BIT_MODE
 * 								8-TIMER1_FAST_PWM_10_BIT_MODE
 * 								9-TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE
 * 								10-TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_NODE
 * 								11-TIMER1_PHASE_CORRECT_PWM_ICR1_MODE
 * 								12-TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE
 * 								13-TIMER1_FAST_PWM_ICR1_MODE
 * 								14-TIMER1_FAST_PWM_OCR1A_MODE
 * 																					*/
#define TIMER1_NORMAL_MODE							0
#define TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE			1
#define TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE			2
#define TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE		3
#define TIMER1_CTC_OCR1A_MODE						4
#define TIMER1_FAST_PWM_8_BIT_MODE					5
#define TIMER1_FAST_PWM_9_BIT_MODE					6
#define TIMER1_FAST_PWM_10_BIT_MODE					7
#define TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE		8
#define TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_NODE	9
#define TIMER1_PHASE_CORRECT_PWM_ICR1_MODE			10
#define TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE			11
#define TIMER1_CTC_ICR1_MODE						12
#define TIMER1_FAST_PWM_ICR1_MODE					14
#define TIMER1_FAST_PWM_OCR1A_MODE					15

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

#define PRESCALER_MASK				0b11111000

/*Output Compare Modes*/
#define NORMAL_OPERATION_MODE		0
#define NON_INVERTED_MODE			1
#define INVERTED_MODE 				2

/*Compare Output Mode Channels*/
#define TIMER1_OCR1A				0
#define TIMER1_OCR1B				1

/*ICU Edge Select*/
#define ICU_RISING_EDGE		1
#define ICU_FALLING_EDGE	0

/*Interrupt Source*/
#define TIMER1_ICU			0
#define TIMER1_COMPA		1
#define TIMER1_COMPB		2
#define TIMER1_OVF			3


void  TIMER1_voidInit(u8 Copy_u8Mode,u8 Copy_u8Prescaler);

void TIMER1_voidSetCompareOutputMode(u8 Copy_u8CompOutputMode, u8 Copy_u8Channel);

void TIMER1_voidSetChannelACompMatchValue(u16 Copy_u16Value);

void TIMER1_voidSetChannelBCompMatchValue(u16 Copy_u16Value);

void TIMER1_voidSetTimerValue(u16 Copy_u16Value);

u16 TIMER1_u16ReadTimerValue(void);

void PWM1_voidInit(void);

void ICU_voidInit(void);

u8 ICU_u8SetTriggerEdge(u8 Copy_u8Edge);

void ICU_voidEnableInterrupt(void);

void ICU_voidDisableInterrupt(void);

u16 ICU_u16ReadInputCaptureRegister(void);

void ICU_voidSetInputCaptureRegister(u16 Copy_u16Value);

void TIMER1_voidOVFInterrruptEnable(void);

void TIMER1_voidOVFInterrruptDisable(void);

u8 TIMER1_u8SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber);






#endif
