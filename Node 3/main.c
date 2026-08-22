/* main_nodeB_RX.c */
#include<LPC21XX.H>
#include "header.h"
#include "lcd.h"
#include "delay.h"
#define rled 1<<2
#define yled 1<<3
#define gled 1<<4
#define wled 1<<5
main(){	
	int d;
	float f;
	CAN2_MSG m1;
	IODIR0 |=rled|yled|gled|wled;
	IOSET0=rled|yled|gled|wled;
	LCD_INIT();
	LCD_TITLE();
	can2_init();
	uart0_init(115200);
	uart0_tx_string("nodeB TESTING CAN\r\n");
	while(1){		
		can2_rx(&m1);
		LCD_COMMAND(0X80);
		LCD_STR("Distance:");
		LCD_COMMAND(0XC0);
		LCD_STR("Status:");
		if(m1.id==0x102){
			uart0_tx_hex(m1.id);
			d=m1.byteA;    
			uart0_tx_string("Distance:");
			LCD_COMMAND(0X89);
			LCD_STR("      ");
			LCD_COMMAND(0X89);
			LCD_INTEGER(d);
			uart0_tx_integer(d);
			uart0_tx_string("\r\n");
			uart0_tx_string("Status:");
			LCD_COMMAND(0XC7);
			if(d>25){
			    LCD_STR("       ");
				LCD_COMMAND(0XC7);
				LCD_STR("SAFE");
				uart0_tx_string("SAFE\r\n");
				IOCLR0=gled;
				IOSET0=rled|yled|wled;
			}
			else if(d>15 && d<=25){
			    LCD_STR("       ");
				LCD_COMMAND(0XC7);
				LCD_STR("WARNING");
				uart0_tx_string("WARNING\r\n");
				IOCLR0=yled;
				IOSET0=rled|gled|wled;
			}
			else if(d<=15){
			    LCD_STR("       ");
				LCD_COMMAND(0XC7);
				LCD_STR("DANGER");
				uart0_tx_string("Danger\r\n");
				IOCLR0=rled|wled;
				IOSET0=yled|gled;
			}
		}	
		LCD_COMMAND(0X94);
		LCD_STR("TEMP:");	
		if(m1.id==0x104){
		uart0_tx_hex(m1.id);
			d=m1.byteA;
			f=(((d*3.3)/1023)*100);	
			uart0_tx_string("TEMP:");
			uart0_tx_float(f);
			uart0_tx_string("\r\n");
			LCD_COMMAND(0X99);
			LCD_STR("       ");	
			LCD_COMMAND(0X99);		
			LCD_FLOAT(f);
		}

		LCD_COMMAND(0XD4);
		LCD_STR("GAS:");
		if((m1.id==0x105)&&(m1.byteA==1)){
			IOCLR0=wled;
			IOSET0=rled|yled|gled;
			uart0_tx_string("GAS:Y\r\n");
			LCD_COMMAND(0XD8);
			LCD_DATA('Y');
		}
		else{
		    IOSET0=wled;
			uart0_tx_string("GAS:N\r\n");
			LCD_COMMAND(0XD8);
			LCD_DATA('N');
		}

		LCD_COMMAND(0XDA);
		LCD_STR("FIRE:");
		if((m1.id==0x106)&&(m1.byteA==1))
		{
			IOCLR0=wled;
			IOSET0=rled|yled|gled;
			uart0_tx_string("FIRE:Y\r\n");
			LCD_COMMAND(0XDF);
			LCD_DATA('Y');
		}
		else{
		    IOSET0=wled;
			uart0_tx_string("FIRE:N\r\n");
			LCD_COMMAND(0XDF);
			LCD_DATA('N');
		}
	}
}
void LCD_TITLE()
{
	LCD_COMMAND(0X80);
	LCD_STR("CAN BASED SMART SHIP MONITORING AND COLLISION WARNING SYSTEM");
	delay_s(3);
	LCD_COMMAND(0X01);
}
