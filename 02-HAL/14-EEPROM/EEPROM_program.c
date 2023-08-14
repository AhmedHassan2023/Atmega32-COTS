/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    EEPROM            **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/
#include "STD_TYPES.h"

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u8 Copy_u8DataByte,u16 Copy_u16Address)
{
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(1010|A2_2<<2|Copy_u16Address>>8);
	TWI_MasterWriteDataByte((u8)Copy_u16Address);
	TWI_MasterWriteDataByte(Copy_u8DataByte);
	TWI_voidSendStopCondition();

}

void EEPROM_voiReadDataByte(u16 Copy_u16Address,u8 *Copy_pu8Data)
{
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(1010|A2_2<<2|Copy_u16Address>>8);
	TWI_MasterWriteDataByte((u8)Copy_u16Address);
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithRead(1010|A2_2<<2|Copy_u16Address>>8);
	TWI_MasterReadDataByte(Copy_pu8Data);
	TWI_voidSendStopCondition();
}
