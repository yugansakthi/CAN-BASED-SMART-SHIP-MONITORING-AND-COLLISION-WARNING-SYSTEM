#include <LPC21XX.H>
// Delay in microseconds
void delay_us(unsigned int n)
{
	T0PR=60-1;//Set prescaler for 1 microsecond
	T0TCR=0x01;//Start Timer 0
	while(T0TC<n);//Wait until required microseconds are elapsed
	T0TCR=0x03;//Reset Timer 0
	T0TCR=0x00;//Stop Timer 0
}
// Delay in seconds
void delay_s(unsigned int s)
{
	T0PR=60000000-1;//Set prescaler for 1 second
	T0TCR=0x01;//Start Timer 0
	while(T0TC<s);//Wait until required seconds are elapsed
	T0TCR=0x03;//Reset Timer 0
	T0TCR=0x00;//Stop Timer 0
}

// Delay in milliseconds
void delay_ms(unsigned int ms)
{
	T0PR=60000-1;//Set prescaler for 1 millisecond
	T0TCR=0x01;//Start Timer 0
	while(T0TC<ms);// Wait until required milliseconds are elapsed
	T0TCR=0x03;// Reset Timer 0
	T0TCR=0x00;// Stop Timer 0
}

