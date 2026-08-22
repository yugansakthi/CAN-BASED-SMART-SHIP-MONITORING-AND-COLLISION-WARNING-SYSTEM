#include <LPC21XX.H>
void servo_init(void)
{
	VPBDIV=1;//set PCLK=CCLK
	PINSEL0|=0x08;//P0.1 → PWM3
	PWMTCR=0x02;//Reset PWM counter
	PWMPR=59;//60 MHz PCLK → 1 µs/count
	PWMMR0=20000;//20 ms period
	PWMMR3=1000;//1 ms pulse
	PWMPCR=0x0800;//PWMENA3 → Enable PWM3
	PWMMCR=0x02;//Reset counter on MR0
	PWMLER=0x09;//Latch MR0 and MR3
	PWMTCR=0x09;//Enable counter+PWM     
}
