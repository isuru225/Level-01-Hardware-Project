/*
 * UltrasonicSensor.h
 *
 * Created: 5/8/2022 5:33:14 PM
 *  Author: Prasadi
 */ 




#include <util/delay.h>         // to use delay function we need to include this library



#define US_PORT PORTA           // we have connected the Ultrasonic sensor on port A. to use the ultrasonic we need two pins of the ultrasonic to be connected on port A
#define	US_PIN	PINA            // we need to initialize the pin resistor when we want to take input.
#define US_DDR 	DDRA            // we need data-direction-resistor (DDR) to set the direction of data flow. input or output. we will define it later, now we're just naming it.

#define US_TRIG_POS	PA0         // the trigger pin of ultrasonic sound sensor is connected to port A pin 0
#define US_ECHO_POS	PA1         // the echo pin of the ultrasonic sound sensor is connected to port A pin 1



#define US_ERROR		-1      // we're defining two more variables two know if the ultrasonic sensor is working or not
#define	US_NO_OBSTACLE	-2

int distance, previous_distance;




void HCSR04Init();
void HCSR04Trigger();

//void lcd_command( unsigned char );

void HCSR04Init()
{
	
	// we're setting the trigger pin as output as it will generate ultrasonic sound wave
	US_DDR|=(1<<US_TRIG_POS);
}

void HCSR04Trigger()
{   // this function will generate ultrasonic sound wave for 10 microseconds
	//Send a 10uS pulse on trigger line
	
	US_PORT|=(1<<US_TRIG_POS);	//high
	
	_delay_us(10);				//wait 10uS
	
	US_PORT&=~(1<<US_TRIG_POS);	//low
}

uint16_t GetPulseWidth()
{
	// this function will be used to measure the pulse duration. When the ultra sound echo back after hitting an object
	// the microcontroller will read the pulse using the echo pin of the ultrasonic sensor connected to it.
	
	uint32_t j,result;

	// Section - 1: the following lines of code before the section - 2 is checking if the ultrasonic is working or not
	// it check the echo pin for a certain amount of time. If there is no signal it means the sensor is not working or not connect properly
	for(j=0;j<300000;j++)
	{
		if(!(US_PIN & (1<<US_ECHO_POS)))
		continue;			//Line is still low, so wait
		else
		break;				//High edge detected, so break.
	}

	if(j==300000)
	return US_ERROR;		//Indicates time out
	
	//High Edge Found
	
	// Section -2 : This section is all about preparing the timer for counting the time of the pulse. Timers in microcontrllers is used for timimg operation
	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);						// This line sets the resolution of the timer. Maximum of how much value it should count.
	TCNT1=0x00;								// This line start the counter to start counting time

	// Section -3 : This section checks weather the there is any object or not
	for(j=0;j<300000;j++)                // the 300000 value is used randomly to denote a very small amount of time, almost 20 miliseconds
	{
		if(US_PIN & (1<<US_ECHO_POS))
		{
			if(TCNT1 > 300000) break; else continue;   // if the TCNT1 value gets higher than 60000 it means there is not object in the range of the sensor
		}
		else
		break;
	}

	if(j==300000)
	return US_NO_OBSTACLE;	//Indicates time out

	//Falling edge found

	result=TCNT1;          // microcontroller stores the the value of the counted pulse time in the TCNT1 register. So, we're returning this value to the
	// main function for utilizing it later

	//Stop Timer
	TCCR1B=0x00;

	if(result > 300000)
	return US_NO_OBSTACLE;	//No obstacle
	else
	return (result>>1);
}



