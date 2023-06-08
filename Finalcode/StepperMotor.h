/*
 * steppermotor.h
 *
 * Created: 7/5/2022 4:36:46 pm
 *  Author: Rashini
 */ 

//Header file for stepper motor


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// to move lumbersupport forward by 45 degree (45*8)=360 degree
int lumbersupportForward1(void)
{	
	PORTC|=0x24;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportForward2(void)
{
	
	PORTC&=~(0x04);
	_delay_ms(10);
	
	return 0;
	
}
int lumbersupportForward3(void)
{		
	
	PORTC|=0x28;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportForward4(void)
{		
	
	PORTC&=~(0x20);
	_delay_ms(10);
	
	return 0;	
}
int lumbersupportForward5(void)
{	
	
	PORTC |=0x18;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportForward6(void)
{		
	
	PORTC &=~(0x08);
	_delay_ms(10);
	
	return 0;	
}
int lumbersupportForward7(void)
{		
	
	PORTC |= 0x14;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportForward8(void)
{		
	
	PORTC &=~(0x10);
	_delay_ms(10);
	
	return 0;	
}

// to move lumbersupport backward by 45 degree (45*8)=360 degree
int lumbersupportBackward1(void)
{		
	
	PORTC |= 0x14;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportBackward2(void)
{	
	
	PORTC &= ~(0x04);
	_delay_ms(10);
	
	return 0;
}
int lumbersupportBackward3(void)
{		
	
	PORTC |= 0x18;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportBackward4(void)
{	
	
	PORTC &=~(0x10);
	_delay_ms(10);
	
	return 0;
}
int lumbersupportBackward5(void)
{		
	
	PORTC |= 0x28;
	_delay_ms(10);
	
	return 0;
}
int lumbersupportBackward6(void)
{		
	
	PORTC &=~(0x08);
	_delay_ms(10);
	
	return 0;

}
int lumbersupportBackward7(void)
{		
	
	PORTC |= 0x24;
	_delay_ms(10);
	
	return 0;

}
int lumbersupportBackward8(void)
{		
	
	PORTC &=~(0x20);
	_delay_ms(10);
	
	return 0;

}