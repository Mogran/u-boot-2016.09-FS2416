/*
 * @filename    : spl_fs2416_uart.c
 * @author      : <lumingliang.github@gmail.com>
 * @description : This file is used to init fs2416 uart  
 *
 * */

#define ULCON0 			(*(volatile unsigned char*) 0x50000000)
#define UCON0 			(*(volatile unsigned int*)  0x50000004)
#define UFCON0 			(*(volatile unsigned char*) 0x50000008)
#define UMCON0 			(*(volatile unsigned char*) 0x5000000C)
#define UTRSTAT0		(*(volatile unsigned char*) 0x50000010)
#define UTXH0 			(*(volatile unsigned char*) 0x50000020)
#define UBRDIV0 		(*(volatile unsigned short*)0x50000028)
#define UDIVSLOT0 		(*(volatile unsigned short*)0x5000002C)
#define GPHCON 			(*(volatile unsigned int*)0x56000070)
#define GPHDAT 			(*(volatile unsigned int*)0x56000074)
#define GPHUDP 			(*(volatile unsigned int*)0x56000078)


#define wait4txdone()  		while(!(UTRSTAT0& 0x2))
#define UART0_TX_ENABLE()   do{UCON0 |= (1 << 2);}while(0)
#define UART0_TX_DISABLE()  do{UCON0 &= ~(3 << 2);}while(0)

void uart_init(void)
{
	/* uart0 */
	GPHCON &= ~((3 << 2) | (3 << 0));
	GPHCON |= (2 << 2) |(2 << 0); 

	/* uart3 */
	GPHCON &= ~((3 << 14) | (3 << 12));
	GPHCON |= (2 << 14) |(2 << 12); 

	/* enable uart0's pull up*/
	GPHUDP &= ~((3 << 2) | (3 << 0));
	GPHUDP |= (2 << 2) |(2 << 0); 

	/* enable uart3's pull up*/
	GPHUDP &= ~((3 << 14) | (3 << 12));
	GPHUDP |= (2 << 14) |(2 << 12); 

	ULCON0 = 0x3;
	UCON0  = 0x5;
	UMCON0 = 0x0;
	UFCON0 = 0x0;
	UBRDIV0 = 34;
	UDIVSLOT0 = 0xDFDD;

	return;
}

void uart_tx_byte(unsigned char data)
{
	while(!(UTRSTAT0&0x2));
	UTXH0 = data;
}

void uart_tx_multiple_bytes(unsigned char *buf, int size)
{
	volatile int ssize = 0;

	for(ssize = 0; ssize < size; ssize++){
		uart_tx_byte(buf[ssize]);
	}
}

