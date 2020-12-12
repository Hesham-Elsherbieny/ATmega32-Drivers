#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/* Config for Parity Bit */
/* Options 1- UART_u8_PARITY_DISABLED
 * 		   2- UART_u8_PARITY_ENABLED_EVEN_PARITY
 * 		   3- UART_u8_PARITY_ENABLED_ODD_PARITY*/


#define UART_u8_PARITY_BIT              UART_u8_PARITY_DISABLED

/* Config For Baud Rate */
/* Options 1- UART_u8_BAUD_RATE_4800
 *         2- UART_u8_BAUD_RATE_9600
 *         3- UART_u8_BAUD_RATE_115200 */
#define UART_u8_BAUD_RATE               UART_u8_BAUD_RATE_9600

/* Config For Stop Bits
 * options 1- UART_u8_STOP_1_BITS
 *         2- UART_u8_STOP_2_BITS */
#define UART_u8_STOP_BITS               UART_u8_STOP_1_BITS

/* Config For Clk System Freq */
/* Options 1- UART_u8_SYS_FREQ_8M
 *         2- UART_u8_SYS_FREQ_12M
 *         3- UART_u8_SYS_FREQ_16M */
#define UART_u8_SYS_FREQ                UART_u8_SYS_FREQ_16M

/* Config Time out */
#define UART_u32_TIME_OUT               40000UL


#endif /* UART_CONFIG_H_ */
