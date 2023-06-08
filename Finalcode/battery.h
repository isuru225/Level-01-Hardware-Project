/*
 * battery.h
 *
 * Created: 5/12/2022 9:05:02 PM
 *  Author: Pramoda
 */ 




#define F_CPU 16000000UL
#include <util/delay.h>
char battery[10];

void calculateAndDisplay(unsigned char value)
{
	float gotVoltage,realVoltage,percentage;
	gotVoltage=value/100.0;
	realVoltage=gotVoltage*8.0;
	percentage=((realVoltage-12.0)/2.8*100);
	sprintf(battery,"%d", (int)percentage);		//convert integer value to ASCII string
	lcd_msg(battery);							//send string data to display through lcd
	_delay_ms(2);
	memset(battery,0,10);
	
		
}

char getVoltage(){
	
	ADCSRA=0x87;					// make ADC enable and ck/128
	ADMUX=0xE4;						// 2.56v Vref and ADC4 single ended data will be left justified
		

	ADCSRA |=(1<<ADSC);				//start the ADC conversion
	while((ADCSRA&(1<<ADIF))==0);	//check the ADC conversion is finished
	data=ADCH;						//read the data from ADCH register
		
	calculateAndDisplay(data);
		
	_delay_ms(1);
	
	return 0;
		
	}



