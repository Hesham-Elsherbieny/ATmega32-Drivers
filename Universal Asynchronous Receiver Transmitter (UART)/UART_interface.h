#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_voidInit             (void);
u8   UART_u8TransmitByteSynch    (u8 Copy_u8Data);
u8   UART_u8TransmitByteAsynch   (u8 Copy_u8Data , void(*Copy_pfunc)(void));

u8   UART_u8RecieveByteSynch     (u8 * Copy_pu8Data);
u8   UART_u8RecieveByteAsynch    (u8 * Copy_pu8Data, void(*Copy_pfunc)(void));

u8   UART_u8RecieveByteAsynch2    (void(*Copy_pfunc)(u8));


#endif /* UART_INTERFACE_H_ */
