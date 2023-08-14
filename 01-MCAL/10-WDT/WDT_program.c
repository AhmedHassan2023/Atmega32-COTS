#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_interface.h"
#include "WDT_register.h"
#include "WDT_config.h"
#include "WDT_private.h"

void WDT_voidEnable(void)
{
	/*Enable Watchdog Timer*/
	SET_BIT(WDTCR,WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	/*Disable Watchdog Timer*/

	WDTCR |= WDT_DISABLE_MASK;

	WDTCR =TURN_OFF;

}

void WDT_voidSleep(u8 Copy_u8SleepTime)
{
	WDTCR &=WDT_PRESCALER_MASK;
	WDTCR |=Copy_u8SleepTime;
}
