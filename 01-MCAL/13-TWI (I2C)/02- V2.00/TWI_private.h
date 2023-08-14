/***************************************************************/
/* Author  	: Ahmed Hassan     			 ***********************/
/* Date		: 13 Aug 2023				 ***********************/
/* Layer   	: MCAL           		   	 ***********************/
/* SWC      : TWI           		   	 ***********************/
/* Version 	: 2.00             			 ***********************/
/***************************************************************/

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWBR	*((volatile u8*)0x20)		/* TWI Bit Rate Register */

#define TWCR	*((volatile u8*)0x56)		/* TWI Control Register */
#define TWCR_TWIE		0					/* TWI Interrupt Enable */
#define TWCR_TWEN		2					/* TWI Enable Bit */
#define TWCR_TWWC		3					/* TWI Write Collision Flag*/
#define TWCR_TWSTO		4					/* TWI STOP Condition Bit */
#define TWCR_TWSTA		5					/* TWI START Condition Bit */
#define TWCR_TWEA		6					/* TWI Enable Acknowledge Bit */
#define TWCR_TWTWINT	7					/*  TWI Interrupt Flag */
#define TWCR_

#define TWSR	*((volatile u8*)0x21)	
#define TWSR_TWPS1	1							/* TWI Prescaler Bit 1 */
#define TWSR_TWPS0	0							/* TWI Prescaler Bit 0 */	

#define TWAR	*((volatile u8*)0x22)			/* TWI (Slave) Address Register */
#define TWAR_TWGCE	0							/* TWI General Call Recognition Enable Bit */


#define TWDR	*((volatile u8*)0x23)			/* TWI Data Register */





#endif	/* TWI_PRIVATE_H_ */