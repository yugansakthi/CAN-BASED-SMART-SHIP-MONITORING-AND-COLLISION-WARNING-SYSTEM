#include<LPC21XX.H>
#include"header.h"
#include"ADC_TEMP.h"
#include"delay.h"
#define GAS 9
#define FLAME 10
 unsigned int d;
int main()
{
    CAN2_MSG m1,m2,m3;
    can2_init();
    temp_init();
    m1.id=0x104;
    m1.rtr=0;
    m1.dlc=4;
    m2.id=0x105;
    m2.rtr=0;
    m2.dlc=4;
    m3.id=0x106;
    m3.rtr=0;
    m3.dlc=4;
    uart0_init(115200);
    uart0_tx_string("node testing Can");
    uart0_tx_string("\r\n");
while(1)
{
 while(((ADDR>>31)&1)==0);
 d=ADDR;
 d=d>>6;
 d=d&0x3ff; 
 m1.byteA=d;
 m1.byteB=0;
 uart0_tx_string("Temperature:");
 uart0_tx_integer(d);
 can2_tx(m1);
 delay_ms(250);
 if(((IOPIN0>>GAS)&1)==0){
    m2.byteA=1;
    m2.byteB=0;
    uart0_tx_string("GAS:Y\r\n");
    can2_tx(m2);
 }
 if(((IOPIN0>>FLAME)&1)==0){
    m3.byteA=1;
    m3.byteB=0;
    uart0_tx_string("FIRE:Y\r\n");
    can2_tx(m3);
 }
}
}



