/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  HAL               **********************/
/**************************     SWC:    CLCD              **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*SET RS pin to low for Command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*SET RW pin low for Write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Command to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*Send Enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(5);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);



}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS pin to HIGH for Data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Set RW pin low for Write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Send Data to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*Send Enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(5);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);


}

void CLCD_voidInit(void)
{
	/*Wait for more than 15 ms*/
	_delay_ms(50);

	CLCD_voidSendCommand(0b00110000);

	CLCD_voidSendCommand(0b00110000);

	CLCD_voidSendCommand(0b00110000);

	/*Function Send command : 2 Lines, 5*8 Font size*/
	CLCD_voidSendCommand(0b00111000);

	/*Display on off control: display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(0b00001000);

	/*Clear display -> 0b00000001 == 1*/
	CLCD_voidSendCommand(0b00000001);

	/*Entry mode set -> 0b00000110*/
	CLCD_voidSendCommand(0b00000110);

	/*Display on off control: set bit 3, display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(0b00001100);


}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter]!= '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}

}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if (Copy_u8XPos==0)
	{
		/*Location is at first line*/
		Local_u8Address=Copy_u8YPos;
	}
	else if(Copy_u8XPos==1)
	{
		/*Location is at second line*/
		Local_u8Address=Copy_u8YPos+0x40;
	}
	else if (Copy_u8XPos==2)
	{
		/*Location is at third line*/
		Local_u8Address=Copy_u8YPos+0x14;
	}
	else if (Copy_u8XPos==3)
	{
		/*Location is at forth line*/
		Local_u8Address=Copy_u8YPos+0x54;
	}

	/*set bit number 7 for Set DDRAM Address command then send the command*/
	CLCD_voidSendCommand(Local_u8Address+128);

}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress=0, Local_u8Iterator;

	/*Calculate CGRAM Address whose each block is 8 bytes*/
	Local_u8CGRAMAddress= Copy_u8PatternNumber*8;

	/*Send CGRAM Address command to LCD, with setting bit 6, clearing bit 7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*Write the Pattern into CGRAM */
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);

	}
	/*go back to DDRAM to display the pattern*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Display the Pattern written in CGRAM */
	CLCD_voidSendData(Copy_u8PatternNumber);

}
