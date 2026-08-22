#include <lpc21xx.h>
#include"header.h"
#include"servo.h"
#include "delay.h"

// --- PIN DEFINITIONS ---------------------------------------
#define TRIG          (1<<3)    // P0.3
#define ECHO          (1<<4)    // P0.4

// --- GLOBAL VARIABLE DECLARATIONS -------------------------
unsigned int d;
unsigned int dist;
unsigned int timeout;


// --- FUNCTION DECLARATIONS ---------------------------------
void distance_init(void);
unsigned int distance(void);

// --- MAIN --------------------------------------------------
int main(void){
	CAN2_MSG m1;
	int i;
	unsigned int angle[]={1000,1500,2000};
	can2_init();
	distance_init();
	VPBDIV=1;
	servo_init();	
	m1.id=0x102;
	m1.rtr=0;
	m1.dlc=4;
	uart0_init(115200);
	uart0_tx_string("node testing Can");
	uart0_tx_string("\r\n");
	while(1){
		d = distance();
		for(i=0;i<3;i++)
		{
			PWMMR3=angle[i];
			PWMLER=0X08;
			delay_ms(500);
			if(d != 1000){
				uart0_tx_string("Distance:");
				m1.byteA=d;
				uart0_tx_integer(d);
				uart0_tx_string("\r\n");
				m1.byteB=0;
				can2_tx(m1);
			}
			else{
				uart0_tx_string("DIST : -\r\n");
				m1.byteA=1000;
				m1.byteB=0;
				can2_tx(m1);
			}
		}
	}

}
// --- HC-SR04 FUNCTIONS -------------------------------------
void distance_init(void){
	IODIR0 |=  TRIG;
	IODIR0 &= ~ECHO;
	IOCLR0  =  TRIG;
}

unsigned int distance(void){
	timeout = 0;

	IOCLR0 = TRIG;
	delay_us(5);
	IOSET0 = TRIG;
	delay_us(15);
	IOCLR0 = TRIG;

	timeout = 0;
	while(!(IOPIN0 & ECHO)){
		timeout++;
		if(timeout > 50000) 
			return 1000;
	}

	T1PR  = 60 - 1;
	T1TCR = 0x03;
	T1TCR = 0x01;

	timeout = 0;
	while(IOPIN0 & ECHO){
		timeout++;
		if(timeout > 50000){
			T1TCR = 0x00;
			return 1000;
		}
	}

	T1TCR = 0x00;

	dist = T1TC / 58;
	if(dist < 2 || dist > 400) return 1000;
	return dist;
}
