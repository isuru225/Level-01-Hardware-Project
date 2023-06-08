/*
 * FootMassaging.h
 *
 * Created: 5/11/2022 11:56:35 AM
 *  Author: Pramoda
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char i=64;

void footMassager(unsigned char m){
	OCR0=i;					// for 25% duty cycle in non inverted phase correct PWM
	TCCR0=0X61;				// Phase correct PWM, Non inverted 31.372 kHz,16Mhz crystal,so N=1
	MCUCR |= (1<<ISC11);    //interrupt fire on falling edge in INT1
	GICR  |= (1<<INT1);     //Enable the external interrupt source in general interrupt control register
	sei();					//enable global interrupts
	
{	
	if(PINC==(PINC|0x80)){
		PORTB|=0x20;
		}
	OCR0=i;
}
}
void eliminateFootMassager(){
		PORTB&=~(0x20);
		OCR0=0;
}
void footElevator(unsigned char m){
	//Rotate elevating motor to clockwise direction
	{	
	if(m==5){
		PORTB|=0x80;
		}else{
		PORTB&=~(0x80);
	}
}

//Rotate elevating motor to counter-clockwise direction
	{
	if(m==2){
			PORTB|=0x40;
		}else{
			PORTB&=~(0x40);
		}
	}
		
}

ISR(INT1_vect){
	if(i<=240){
		i=i+60;
	}else{
		i=64;
	}
		
	_delay_us(10);
}

