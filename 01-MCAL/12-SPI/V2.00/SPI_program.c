/*******************************************************************************/
/*******************************************************************************/
/**************************     Author: Ahmed Hassan      **********************/
/**************************     Layer:  MCAL              **********************/
/**************************     SWC:    SPI               **********************/
/**************************     Version:1.00              **********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_register.h"
#include "SPI_config.h"
#include "SPI_private.h"

static void (*SPI_pvCallBackNotificationFunc)(void)=NULL;

static u8* SPI_pu8ReceivedData=NULL;

u8 SPI_u8BusyState = IDLE;


/* Discription : Function to Initialize SPI
 * Input : void
 * Output : void		*/
void SPI_voidInit(void)
{
	/*Select Master/Slave mode*/
#if SPI_MODE_SELECT == SPI_MASTER
	{
		/*Master Initialization*/
		SET_BIT(SPCR,SPCR_MSTR);
	}

	/* Selecting Clock Rate*/
#if SPI_CLK_RATE == SPI_CLK_OVER_4
	{
		/*Clock Prescaler: Divide by 4*/
		CLR_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_16
	{
		/*Clock Prescaler: Divide by 16*/
		SET_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_64
	{
		/*Clock Prescaler: Divide by 64*/
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_128
	{
		/*Clock Prescaler: Divide by 128*/
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_2
	{
		/*Clock Prescaler: Divide by 2*/
		CLR_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_8
	{
		/*Clock Prescaler: Divide by 8*/
		SET_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_CLK_OVER_32
	{
		/*Clock Prescaler: Divide by 32*/
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
	}
#elif SPI_CLK_RATE == SPI_DCLK_OVER_64
	{
		/*Clock Prescaler: Divide by 64*/
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
	}

#else
#error "Wrong SPI CLOCK Rate Configuration"
#endif

#elif SPI_MODE_SELECT == SPI_SLAVE
	{
		/*Slave Initialization*/
		CLR_BIT(SPCR,SPCR_MSTR);
	}
#else
#error	"Wrong SPI Master/Slave Mode Configuration"
#endif

	/*Select Data Order*/
#if SPI_DATA_ORDER == SPI_MSB
	{
		CLR_BIT(SPCR,SPCR_DORD);
	}
#elif SPI_DATA_ORDER == SPI_LSB
	{
		SET_BIT(SPCR,SPCR_DORD);
	}
#endif

	/*Selecting Clock Polarity*/
#if SPI_CLK_POL == SPI_FALLING_EDGE
	{
		CLR_BIT(SPCR,SRCR_CPOL);
	}
#elif SPI_CLK_POL == SPI_RISING_EDGE
	{
		SET_BIT(SPCR,SPCR_CPOL);
	}
#endif

	/*Selecting Clock Phase*/
#if SPI_CLK_PHASE == SPI_SAMPLE
	{
		CLR_BIT(SPCR,SPCR_CPHA);
	}
#else SPI_CLK_PHASE == SPI_SETUP
	{
		SET_BIT(SPCR,SPCR_CPHA);
	}
#endif

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}


/*Discription : Function to send and receive dada Synchronously
 * Input : 1- Copy_pu8ReceivedData : pointer to hold the received data
 * 		   2- Copy_u8SendData : to send the data
 * Output : Local_u8ErrorStatus		*/
u8 SPI_u8TransceiveSynch(u8 *Copy_pu8ReceivedData,u8 Copy_u8SendData)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pu8ReceivedData == NULL)
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	else
	{
		/*Writing in The Data register ---> sending*/
		SPDR = Copy_u8SendData;

		/*Wait until transmission complete*/
		while((GET_BIT(SPSR,SPSR_SPIF)==0) && (Local_u32Counter != SPI_u32_TIMEOUT))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==SPI_u32_TIMEOUT)
		{
			/*Loop is broken because the timeout is reached*/
			Local_u8ErrorStatus=NOK;
		}
		else
		{
			*Copy_pu8ReceivedData = SPDR;
		}
	}

	return Local_u8ErrorStatus;
}


/*Discription : Function to send and receive dada ASynchronously
 * Input : 1- Copy_pu8ReceivedData : pointer to hold the received data
 * 		   2- Copy_u8SendData : to send the data
 * Output : Local_u8ErrorStatus		*/
u8 SPI_u8TransceiveASynch(u8 *Copy_pu8ReceivedData,u8 Copy_u8SendData,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;
	if(Copy_pu8ReceivedData == NULL || Copy_pvNotificationFunc == NULL)
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	else
	{
		if(SPI_u8BusyState == IDLE)
		{
			/*Make SPI Busy*/
			SPI_u8BusyState = BUSY;

			/*Initialize the receving data variable globally*/
			SPI_pu8ReceivedData = Copy_pu8ReceivedData;

			/*Initialize the callback notification function globally*/
			SPI_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Send the data*/
			SPDR = Copy_u8SendData;

			/* Enable SPI Interrupt*/
			SET_BIT(SPCR,SPCR_SPIE);
		}
	}

	return Local_u8ErrorStatus;
}

void __vector_12 (void)	 __attribute__((signal));
void __vector_12 (void)
{
	/*Reading the received Data byte*/
	SPI_pu8ReceivedData = SPDR;

	/*Make SPI State IDLE*/
	SPI_u8BusyState = IDLE;

	/*Invoke SPI Notification Function*/
	SPI_pvCallBackNotificationFunc();

	/*Disable SPI Interrupt*/
	CLR_BIT(SPCR,SPCR_SPIE);
}
