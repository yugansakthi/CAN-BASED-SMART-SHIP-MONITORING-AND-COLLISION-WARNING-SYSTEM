/* UART Driver */
#include<LPC21xx.H>
#include"header.h"
/* Initialize UART0 with the given baud rate */
void uart0_init(unsigned int baud)
{
	PINSEL0|=0x5;// Configure P0.0 as TXD0 and P0.1 as RXD0
	U0LCR = 0x83;// Enable DLAB and set UART to 8N1 format
	switch(baud)
	{
		case 115200:
			U0DLL=32;//Set divisor for 115200 baud (PCLK = 60 MHz)
			break;
		case 921600:
			U0DLL=4;//Set divisor for 921600 baud
			break;
		default:
			U0DLL=32;//Default baud rate setting
	}
	U0LCR=0x03;// Disable DLAB and set UART to 8N1 format
}
/* Transmit a single character through UART0 */
void uart0_tx(unsigned char data)
{
	U0THR=data;//Load data into UART0 Transmit Holding Register
	while((U0LSR&(1<<5))==0);//Wait until THR is empty
}
/* Receive a single character through UART0 */
unsigned char uart0_rx(void)
{
	while((U0LSR&0x01)==0);//Wait until data is received
	return U0RBR;//Return received character
}
/* Transmit a string through UART0 */
void uart0_tx_string(char *ptr)
{
	while(*ptr!=0)//Continue until null character is reached
	{
		U0THR=*ptr;//Send current character
		while((U0LSR&(1<<5))==0);//Wait until transmission is complete
		ptr++;//Move to the next character
	}
}
#include <stdio.h>
/* Transmit an integer value through UART0 */
void uart0_tx_integer(int num)
{
	char buf[10];
	sprintf(buf, "%d", num);//Convert integer to decimal string
	uart0_tx_string(buf);//Transmit the converted string
}

/* Transmit an integer value in hexadecimal format through UART0 */
void uart0_tx_hex(int num)
{
	char buf[10];
	sprintf(buf, "%X", num);//Convert integer to hexadecimal string
	uart0_tx_string(buf);//Transmit the converted string
}

