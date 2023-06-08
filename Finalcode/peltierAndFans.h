/*
 * peltierAndFan.h
 *
 * Created: 5/10/2022 1:14:07 PM
 *  Author: Vibuda
 */ 



#define F_CPU 16000000UL
#include <util/delay.h>


//cool the system
void cooling(){
	
	PORTB|=0x10;
	PORTA&=~(0x20);
}

//heat the system
void heating(){

	PORTA|=0x20;
	PORTB&=~(0x10);
}
//off the cooling unit
void offFunction(){
	
	PORTB&=~(0x10);
	PORTA&=~(0x20);
}
//activate the fans
void activateFans(){
	PORTC|=0x40;
}
//deactivate the fans
void deactivateFans(){
	PORTC&=~(0x40);
}
