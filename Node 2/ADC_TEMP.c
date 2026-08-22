 #include<LPC21XX.H>
 void temp_init(void)
{
    PINSEL1|=0x04000000;//Configure the temperature sensor pin as ADC input
    ADCR=0x04;//Select ADC channel 2
    ADCR|=(3<<8);//Set ADC clock divider
    ADCR|=0x00010000;//Enable ADC conversion
    ADCR|=0x00200000;//Power up the ADC
}

