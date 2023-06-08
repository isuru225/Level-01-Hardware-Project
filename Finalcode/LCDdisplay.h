/*
 * LCDdisplay.h
 *
 * Created: 7/5/2022 4:31:08 pm
 *  Author: Rashini
 */ 

//header file for LCD

#include <avr/io.h>


void lcd_init();			//----LCD Initializing Function
void toggle();				//----Latching function of LCD
void lcd_cmd_hf(char v1);   //----Function to send half byte command to LCD
void lcd_cmd(char v2);		//----Function to send Command to LCD
void lcd_dwr(char v3);		//----Function to send data to LCD
void lcd_msg(char *c);		//----Function to Send String to LCD
void delay(int ms);			//----Delay function


void toggle()
{
	TWDR |= 0x02;					
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));	
	delay(1);
	TWDR &= ~0x02;					
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

void lcd_cmd_hf(char v1)
{
	TWDR &=~0x01;					//Selecting register as Command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;					//clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (v1 & 0xF0);			//Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcd_cmd(char v2)
{
	TWDR&=~0x01;					//Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;                   //clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (v2 & 0xF0);			//Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;                    //clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((v2 & 0x0F)<<4);		//Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcd_dwr(char v3)
{
	TWDR|=0x01;						//Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;				    //clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (v3 & 0xF0);			//Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;					//clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((v3 & 0x0F)<<4);		//Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcd_init()
{
	lcd_cmd_hf(0x30);       //Sequence for initializing LCD
	lcd_cmd_hf(0x30);       
	lcd_cmd_hf(0x20);       
	lcd_cmd(0x28);          //Selecting 16 x 2 LCD in 4Bit mode
	lcd_cmd(0x0C);          //Display ON Cursor OFF
	lcd_cmd(0x01);          //Clear display
	lcd_cmd(0x06);          //Cursor Auto Increment
	lcd_cmd(0x80);          //1st line 1st location of LCD
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<=ms;i++)
	for(j=0;j<=120;j++);
}

void lcd_msg(char *c)
{
	while(*c != 0)      //Wait till all String are passed to LCD
	lcd_dwr(*c++);		//Send the String to LCD
}




