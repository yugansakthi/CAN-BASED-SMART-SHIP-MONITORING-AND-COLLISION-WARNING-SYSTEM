/*header.h*/
#ifndef __HEADER_H_
#define __HEADER_H_

typedef  unsigned int u32;
typedef  signed int s32;
typedef  unsigned char u8;
typedef  signed char s8;
typedef  unsigned short int u16;
typedef   signed short int s16;

//Structure
typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;

//Function declarations
void can2_rx(CAN2_MSG *m1);
void can2_init(void);
void uart0_init(u32 baud);
void uart0_tx(u8 ch);
u8 uart0_rx(void);
void uart0_string(s8 *s);
void uart0_tx_integer(s32 n);
void uart0_tx_float(float num);
void uart0_tx_hex(int num);
void uart0_tx_string(char *ptr);
#endif

