/*
 * massagingMotorFunction.h
 *
 * Created: 4/26/2022 12:00:56 PM
 *  Author: Isuru
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char counting=1;



void massagingMotorFunction(unsigned char y)
{
    DDRB|=0x03;

	GICR|=(1<<INT0);				//Enable the external interrupt source in general interrupt control register
	MCUCR|=(1<<ISC01);				//interrupt fire on falling edge in INT0

	
	/*Generating interrupt for activating or deactivating
	the massaging motor*/
	
	sei();							//enable global interrupts

		if(counting%2==0){			//If counting value is even massaging motor will activate.
			PORTB|=0x01;
			_delay_ms(10);
			if(y==8){				//Speed of the motor is increasing 
				PORTB|=1<<PB1;
				_delay_ms(10);
			}
			else{
				PORTB&=~(1<<PB1);
				_delay_ms(10);
			}
		}	
		else{						//If counting value is even massaging motor will deactivate.
			PORTB&=~(0x03);
		}
		_delay_ms(1);
    
	
}

void terminatingMotorFunction(unsigned char y){
	DDRB|=0x03;

	GICR=(1<<INT0);
	MCUCR=(1<<ISC01);
	
	/*Generating interrupt for activating or deactivating
	the massaging motor*/
	
	sei();
	//Set PB0 and PB1 to zero
	PORTB&=~(0x03);
	
}

/*Interrupt Function*/
ISR(INT0_vect){

	counting++;	
	_delay_ms(1);
}

