/*
 * afterFirstSemExamination.c
 *
 * Created: 1/20/2022 4:02:22 PM
 * Author : Isuru
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "KeyPad.h"
#include "LCDdisplay.h"
#include "massagingMotor.h"
#include "UltrasonicSensor.h"
#include "I2C.h"
#include "TemperatureSensor.h"
#include "peltierAndFans.h"
#include "FootMassaging.h"
#include "StepperMotor.h"
#include "battery.h"
#include "loadCell.h"
#include <util/delay.h>


unsigned char x,p,count;
unsigned char temperature,temperature2;	
unsigned char enable=0;					//Using enables for controlling cooling & heating system
unsigned char y=0;						//Stepper Motor counting
unsigned char buzzerCount=0;			//buzzer counting
unsigned char islcdON=0;				//Check the status of LCD
int main(void)
{
    /* Replace with your application code */
	
	
	DDRA|=(1<<clock);
	DDRA&=~(0x10); //making input pin to get the voltage
	DDRB|=0x04;
	DDRD=0xF0;
	DDRC|=0x03;
	//making output pin for peltier device
	DDRA|=0x20;
	DDRB|=0x10; 
	DDRC|=0x40;		//making output pin for fans
	DDRC&=~(0x80);	//take input signal for foot massaging motor
	DDRB|=0xF8;		//making PB3,PB4,PB5,PB6,PB7 pin as output pin
	DDRC|=0x3C;		// Make PORTC relevant pins as output
	
	
	//I2c & LCD display
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
    while (1) 
    {
		
					
					/************Coding Section Key Pad*************/
		
			PORTD =0x0F;   //Make all columns 1 and all rows 0.

			x=Keypad();
			_delay_ms(10);
			if(x==7||x==4||x==1){
				p=x;
			}
			
					/*************Coding Section UltraSonic**************/ 
			uint16_t r;
		
	
			//Set io port direction of sensor
			HCSR04Init();
			
			
			//Send a trigger pulse
			HCSR04Trigger();                // calling the ultrasonic sound wave generator function

			//Measure the width of pulse
			r=GetPulseWidth();              // getting the duration of the ultrasound took to echo back after hitting the object

			//Handle Errors
			if(r!=US_ERROR)                 // if micro controller doesn't get any pulse then it will set the US_ERROR variable to -1
			
			{
				
				distance=(r*0.034/2.0);			// This will give the distance in centimeters
												//	The speed of sound waves is 343 m/s
	
				
				if(distance<15 || buzzerCount<=6)
				{
					
					
					
					loadCellFunction();			//Activating Load cell
				
					if(loadCondition<=15){		/*If the load which is generated is less than or equal to 15kg,
													then the massaging motor will be activated.*/
			
						massagingMotorFunction(x);//calling massagingMotorFunction(Start the motor)
					}else{
			
						terminatingMotorFunction(x);//calling terminatingMotorFunction(Stop the motor)
					}
					
					
					
							/*************Coding Section for temperature sensor************/
							
						if(islcdON==0){	
							lcd_cmd(0x0F);	
							count=0;
						}
							islcdON=1;
							if(count==0){
								lcd_cmd(0x80);
								lcd_msg("Battery:");
								getVoltage();
								lcd_msg("%");
								lcd_cmd(0xC0);
								lcd_msg("Temp:");
								count++;							
							}
							
							//check the values of two temperature sensors
							temperature=getTemperature(enable);
							temperature2=getTemperature2();
							
							
							if(temperature<=70 && temperature2<=70){	//Protect the peltier device from being damage
								if(p==7 || p==4){
									activateFans();
								}
								
								if(p==1){
									deactivateFans();
								}
								
								//make hot the system when "H" button is pressed
								if((p==7 && enable==2) || (p==7 && enable==3) ||(p==7 && enable==4) ||(p==7 && enable==5)||(p==7 && enable==1)){
									if(temperature<=28){
										offFunction();
										lcd_cmd(0xCA);
										_delay_ms(10);
										lcd_msg("..Wait");
										}else{
										heating();
										enable=1;
										lcd_cmd(0xCA);
										lcd_msg("      ");
									}
								}
								else if(p==7 && enable==0){
									enable=1;
								}
								
								//cool the system when "C" button is pressed
								if((p==4 && enable==1) || (p==4 && enable==3) ||(p==4 && enable==4) ||(p==4 && enable==5)||(p==4 && enable==2)){
									if(temperature>=28){
										offFunction();
										lcd_cmd(0xCA);
										lcd_msg("..Wait");
										}else{
										cooling();
										enable=2;
										lcd_cmd(0xCA);
										lcd_msg("      ");
									}

								}
								else if(p==4 && enable==0){
									cooling();
									enable=2;
								}
								
								//off the peltier device when "OFF" button is pressed
								if(p==1){
									offFunction();
									enable=3;
									lcd_cmd(0xC5);
									lcd_msg("           ");
								}
								
								}else if(temperature>70 || temperature2>70){
								activateFans();
								_delay_ms(10);
								offFunction();
								_delay_ms(10);
								enable=4;
							}
							
						//Automated footrest and massaging motor
				
						if(PINC==(PINC|0x80)){
							footMassager(x);
							}else {
							eliminateFootMassager();
							}
				
							footElevator(x);		//Move foot elevator
							
							
							//Stepper motor function for lumber supporter//
							
							 if(x==10)				//if 0 button is pressed
							 {
								 y++;
								 if(y==1)
								 {
									 lumbersupportForward1();
								 }
								 if(y==2)
								 {
									 lumbersupportForward2();
								 }
								 if(y==3)
								 {
									 lumbersupportForward3();
								 }
								 if(y==4)
								 {
									 lumbersupportForward4();
								 }
								 if(y==5)
								 {
									 lumbersupportForward5();
								 }
								 if(y==6)
								 {
									 lumbersupportForward6();
								 }
								 if(y==7)
								 {
									 lumbersupportForward7();
								 }
								 if(y==8)
								 {
									 lumbersupportForward8();
									 
								 }
								 
							 }
							 
							 
							 if(x==11)				//if = button is pressed
							 {
								 
								 if(y==8)
								 {
									 lumbersupportBackward1();
								 }
								 if(y==7)
								 {
									 lumbersupportBackward2();
								 }
								 if(y==6)
								 {
									 lumbersupportBackward3();
								 }
								 if(y==5)
								 {
									 lumbersupportBackward4();
								 }
								 if(y==4)
								 {
									 lumbersupportBackward5();
								 }
								 if(y==3)
								 {
									 lumbersupportBackward6();
								 }
								 if(y==2)
								 {
									 lumbersupportBackward7();
								 }
								 if(y==1)
								 {
									 lumbersupportBackward8();
								 }
								 y--;
								 
							 }
							 
					if(buzzerCount<=7 && distance<15){
						buzzerCount=0;					//Reset the buzzer count
					}
				}
				
				
				if(distance>=15)
				{										
			
			
					if(buzzerCount<=5){
							PORTB|=0x04;				//Turn on the buzzer (Six beep sounds are generated)
							_delay_ms(5);
							PORTB&=~(0x04);				//Turn off the buzzer
							_delay_ms(100);
							buzzerCount++;				//Increase buzzer count by 1
					}else if(buzzerCount>5 && buzzerCount<=6){
						PORTB|=0x04;					//Turn on the buzzer (Continuous beep sound is generated)
						_delay_ms(100);
						buzzerCount++;					//Increase buzzer count by 1
					}else{
						PORTB&=~(0x04);					//Turn off the buzzer
						
						deactivateFans();				//Turn off fans
						
						offFunction();					//Turn off peltier device
						enable=5;
						lcd_cmd(0x08);					//Turn off LCD display
						islcdON=0;
						
						terminatingMotorFunction(x);	//calling terminatingMotorFunction(Stop the motor)
						
						eliminateFootMassager();		//Turn off foot massaging motor
						//buzzerCount=7;
					}
							
					
					
						
						
					
				}
				 
			}
				
		 

		
    }
	
	return 0;
}
