/*
 * TemperatureSensor.h
 *
 * Created: 5/10/2022 12:38:23 PM
 *  Author: Vibuda
 */ 


//LM35 Interfacing with ATmega32

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
unsigned char data;

#define degree 0xdf
char temp1[10];

// display the values of 1st LM 35 sensor
void display1(unsigned char value)
{
		
		sprintf(temp1,"%d%cC  ", (int)value, degree);	//convert integer value to ASCII string
		lcd_cmd(0xC5);
		lcd_msg(temp1);									//send string data to display through lcd
		
		_delay_ms(2);
		memset(temp1,0,10);
		
	
	
}	

//get the temperature of 1st LM 35 sensor
		

	char getTemperature(unsigned char enable){
		DDRA&=~(0x04);						//Make PINA2 zero for input purpose
		ADCSRA=0x87;						// make ADC enable and ck/128
		ADMUX=0xE2;							// 2.56v Vref and ADC2 single ended data will be left justified
		

		ADCSRA |=(1<<ADSC);					//start the ADC conversion
		while((ADCSRA&(1<<ADIF))==0);		//check the ADC conversion is finished
		data=ADCH;							//read the data from ADCH register
		if((enable==1 || enable==2)){
			display1(data);					//pass the temperature value to display in LCD
		}	
		
		_delay_ms(1);
		return data;
	
	}
//get the temperature of 2nd LM 35 sensor
	char getTemperature2(){
		DDRA&=~(0x08);						//Make PINA3 zero for input purpose
		ADCSRA=0x87;						// make ADC enable and ck/128
		ADMUX=0xE3;							// 2.56v Vref and ADC3 single ended data will be left justified
		

		ADCSRA |=(1<<ADSC);					//start the ADC conversion
		while((ADCSRA&(1<<ADIF))==0);		//check the ADC conversion is finished
		data=ADCH;							//read the data from ADCH register
		
		_delay_ms(1);
		return data;
		
	}	
	
	




