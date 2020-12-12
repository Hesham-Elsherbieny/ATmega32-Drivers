#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* UCSRA BITS */
#define UCSRA_RXC                                     7
#define UCSRA_TXC                                     6
#define UCSRA_UDRE                                    5
#define UCSRA_FE                                      4
#define UCSRA_DOR                                     3
#define UCSRA_PE                                      2
#define UCSRA_U2X                                     1
#define UCSRA_MPCM                                    0

/* UCSRB BITS */
#define UCSRB_RXCIE                                   7
#define UCSRB_TXCIE                                   6
#define UCSRB_UDRIE                                   5
#define UCSRB_RXEN                                    4
#define UCSRB_TXEN                                    3
#define UCSRB_UCSZ2                                   2
#define UCSRB_RXB9                                    1
#define UCSRB_TXb9                                    0


/* UCSRC BITS */
#define UCSRC_URSEL                                   7
#define UCSRC_UMSEL                                   6
#define UCSRC_UPM1                                    5
#define UCSRC_UPM0                                    4
#define UCSRC_USBS                                    3
#define UCSRC_UCSZ1                                   2
#define UCSRC_UCSZ0                                   1
#define UCSRC_UCPOL                                   0


/* Private Macros */
#define UART_u8_PARITY_DISABLED                       0
#define UART_u8_PARITY_ENABLED_EVEN_PARITY            2
#define UART_u8_PARITY_ENABLED_ODD_PARITY             3

#define UART_u8_BAUD_RATE_4800                        0
#define UART_u8_BAUD_RATE_9600                        1
#define UART_u8_BAUD_RATE_115200                      2



#define UART_u8_STOP_1_BITS                           0
#define UART_u8_STOP_2_BITS                           1


#define UART_u8_SYS_FREQ_8M                           0
#define UART_u8_SYS_FREQ_12M                          1
#define UART_u8_SYS_FREQ_16M                          2






#endif /* UART_PRIVATE_H_ */
