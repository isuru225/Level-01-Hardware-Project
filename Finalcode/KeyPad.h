/*
 * KeyPad.h
 *
 * Created: 5/8/2022 10:36:47 AM
 *  Author: Prasadi
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


char Keypad()
{
	
	PORTD=0b11101111;         // make first row 0
	if((PIND &(1<<PIND0))==0)
	{
		_delay_ms(1);
		return 7;
	}

	else if((PIND&(1<<PIND1))==0)
	{
		_delay_ms(1);
		return 8;
	}
	else if((PIND&(1<<PIND2))==0)
	{
		_delay_ms(1);
		return 9;
	}
	else if ((PIND&(1<<PIND3))==0)
	{
		_delay_ms(1);
		return 13;//'division'
	}

	PORTD=0b11011111;   // make second row 0
	if((PIND &(1<<PIND0))==0)
	{
		_delay_ms(1);
		return 4;
	}
	else if((PIND&(1<<PIND1))==0)
	{
		_delay_ms(1);
		return 5;
	}
	else if((PIND&(1<<PIND2))==0)
	{
		_delay_ms(1);
		return 6;
	}
	else if((PIND&(1<<PIND3))==0)
	{
		_delay_ms(1);
		return 14;//'*'
	}

	
	PORTD=0b10111111;   // make third row 0
	if((PIND &(1<<PIND0))==0)
	{
		_delay_ms(1);
		return 1;
	}
	else if((PIND&(1<<PIND1))==0)
	{
		_delay_ms(1);
		return 2;
	}
	else if((PIND&(1<<PIND2))==0)
	{
		_delay_ms(1);
		return 3;
	}
	else if((PIND&(1<<PIND3))==0)
	{
		_delay_ms(1);
		return 15;//'-'
	}
	
	
	PORTD=0b01111111;   // make fourth row 0
	if((PIND &(1<<PIND0))==0)
	{
		_delay_ms(1);
		return 10;
	}
	else if((PIND&(1<<PIND1))==0)
	{
		_delay_ms(1);
		return 11;
	}
	else if((PIND&(1<<PIND2))==0)
	{
		_delay_ms(1);
		return 12;
	}
	else if((PIND&(1<<PIND3))==0)
	{
		_delay_ms(1);
		return 16;//'+'
	}
	
	return 0;
}

