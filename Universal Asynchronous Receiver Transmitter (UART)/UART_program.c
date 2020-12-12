#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"




static const u8 UART_u8BaudRateValue[3][3]={
		         //4800        9600      115200
		/*8MHZ */ {0x67    ,    0x33   ,   0x03},
		/*12MHZ*/ {154     ,     77    ,      6},
		/*16MHZ*/ {0xcf    ,    0x67   ,   0x08}
};
/* Global Variable  */
static u8   UART_u8TransmitByte ;
static u8 * UART_pu8RecieveByte = NULL;

/* Global pointer To function to the End of transmit */
static void(*EndOfTransmitCB)(void) = NULL;

/* Global Pointer TO Function to The Receive Interrupt */
static void(*EndOfReceive2)(u8)    = NULL;

/* Global Pointer TO Function to The Receive Interrupt */
static void(*EndOfReceive)(void)    = NULL;

void UART_voidInit             (void)
{
	/* Enable Tx And Rx  */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

	UCSRC = ((1<<7) | (UART_u8_PARITY_BIT << UCSRC_UPM0) | (UART_u8_STOP_BITS << UCSRC_USBS) | (3<<UCSRC_UCSZ0));

	UBRRL = UART_u8BaudRateValue[UART_u8_SYS_FREQ][UART_u8_BAUD_RATE];
	//	UBRRL = 51;
	//	UCSRA = 0x00;
	//	UCSRB = 0b00011000;
	//	UCSRC = 0b10000110;
}
u8   UART_u8TransmitByteSynch    (u8 Copy_u8Data)
{
	u8  Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	u32 Local_u32TimeOutCounter = 0;

	UDR_T = Copy_u8Data;

	while((GET_BIT(UCSRA,UCSRA_UDRE) == 0) && (Local_u32TimeOutCounter < UART_u32_TIME_OUT))
	{
		Local_u32TimeOutCounter++;
	}

	if(Local_u32TimeOutCounter >= UART_u32_TIME_OUT)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}
	return Local_u8ReturnState;
}
u8   UART_u8TransmitByteAsynch   (u8 Copy_u8Data , void(*Copy_pfunc)(void))
{
	u8 Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	/* Check That The Pointer Is Initialized */
	if(Copy_pfunc == NULL)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NULL_POINTER;
	}
	else
	{
		/* Enable Interupt UDR Register is empty */
		//        SET_BIT(UCSRB,UCSRB_UDRIE);

		UDR_T = Copy_u8Data;


		SET_BIT(UCSRB,UCSRB_TXCIE);

		//        UART_u8TransmitByte = Copy_u8Data;


		//Init The Global Pointer To function
		EndOfTransmitCB = Copy_pfunc;
	}
	return Local_u8ReturnState;
}

u8   UART_u8RecieveByteSynch     (u8 * Copy_pu8Data)
{
	u8  Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	u32 Local_u32TimeOutCounter = 0;

	while((GET_BIT(UCSRA,UCSRA_RXC) == 0) && (Local_u32TimeOutCounter < UART_u32_TIME_OUT))
	{
		Local_u32TimeOutCounter++;
	}

	if(Local_u32TimeOutCounter >= UART_u32_TIME_OUT)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NOK;
	}
	else
	{
		*Copy_pu8Data = UDR_R;
	}
	return Local_u8ReturnState;

}
u8   UART_u8RecieveByteAsynch2    (void(*Copy_pfunc)(u8))
{
	u8 Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	if(Copy_pfunc == NULL)
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NULL_POINTER;
	}
	else
	{
		//Check if the Data Is Received or not
		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
		{
			Copy_pfunc(UDR_R);
		}
		else//The Data Is Not Received
		{
			//Enable Receive Interrupt
			SET_BIT(UCSRB,UCSRB_RXCIE);

			//Save The Pointer to the Function in the Global Pointer to function
			EndOfReceive = Copy_pfunc;
		}
	}

	return Local_u8ReturnState;
}

u8   UART_u8RecieveByteAsynch    (u8 * Copy_pu8Data, void(*Copy_pfunc)(void))
{
	u8 Local_u8ReturnState = STD_TYPES_u8_ERROR_OK;
	if((Copy_pu8Data == NULL) || (Copy_pfunc == NULL))
	{
		Local_u8ReturnState = STD_TYPES_u8_ERROR_NULL_POINTER;
	}
	else
	{
		//check if the Data Is Received or not
		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
		{
			*Copy_pu8Data = UDR_R;
			//Call Notification Function
			Copy_pfunc();
		}
		else
		{
			//Enable Receive Interrupt
			SET_BIT(UCSRB,UCSRB_RXCIE);

			//Init The Global pointer to take the received byte
			UART_pu8RecieveByte = Copy_pu8Data;

			//Init The Global pointer to function
			EndOfReceive = Copy_pfunc;
		}
	}
	return Local_u8ReturnState;
}


#define ISR(NO)                           void __vector_##NO(void) __attribute__((signal));   \
		void __vector_##NO(void)

/* Code of ISR function For UDR is Empty */
/*void __vector_14(void)    __attribute__((signal));
void __vector_14(void)
{
	//Disable Interrupt
	CLR_BIT(UCSRB,UCSRB_UDRIE);
	//Call Notification func
	EndOfTransmitCB();
}*/

//Interrupt for RXC
ISR(13)
{
	//	/* Disable Interupt of Rec */
	//	CLR_BIT(UCSRB,UCSRB_RXCIE);
	//
	//	/* Call notification function */
	//	EndOfReceive(UDR_R);
  
	/* Disable Interupt of Rec */
	CLR_BIT(UCSRB,UCSRB_RXCIE);

	*UART_pu8RecieveByte = UDR_R;

	//Call Pointer function
	EndOfReceive();

}

//Interrupt For UDRE
ISR(14)
{
	//	 UDR_T = UART_u8TransmitByte;
	//Disable Interrupt
	CLR_BIT(UCSRB,UCSRB_UDRIE);
	//	UDR_T = UART_u8TransmitByte;
	EndOfTransmitCB();

}

ISR(15)
{
	CLR_BIT(UCSRB,UCSRB_TXCIE);


	EndOfTransmitCB();
}


