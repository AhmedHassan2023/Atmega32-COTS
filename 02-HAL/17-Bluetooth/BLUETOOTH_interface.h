/*************************************************************************************/
/*************************************************************************************/
/**************************     Author	: Ahmed Hassan      	**********************/
/**************************     Layer	: HAL	              	**********************/
/**************************     SWC		: BLUETOOTH            	**********************/
/**************************     Version	: 1.00              	**********************/
/*************************************************************************************/
/*************************************************************************************/

#ifndef BLUETOOTH_INTERFACE_H_
#define BLUETOOTH_INTERFACE_H_

void BLUETOOTH_voidInit(void);

void BLUETOOTH_voidSendData(u8 Copy_u8Data);

u8 BLUETOOTH_u8ReceiveData(void);

void BLUETOOTH_voidSendString(const char* Copy_pcString);

void BLUETOOTH_voidSendNumber(u32 Copy_u32Number);


#endif	/* BLUETOOTH_INTERFACE_H_ */
