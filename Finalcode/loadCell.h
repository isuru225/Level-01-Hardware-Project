/*
 * loadCell.h
 *
 * Created: 5/17/2022 10:49:16 PM
 *  Author: Isuru
 */ 



#define calibrationFactor 0.00002773232
#define clock PORTA7
#define Reading_Data PINA6
int loadCondition;
char digitAmount;
char valueString[24];
char calculation();
//double callibrationFactor=1/36059;
char numbers[5];

void loadCellFunction(){
	
	PORTA|=(1<<Reading_Data);		//We need to set PD3 high before data retrieval
	char d;							//Reading
	
	for(int i=0;i<24;i++){
									
		PORTA |= (1<<clock);		//Sending the clock pulse to PD_SCK to retrieve data
		_delay_us(2);
		PORTA &= ~(1<<clock);

		
		if(!(~PINA & (1<<Reading_Data))){
			d='1';
			}else{
			d='0';
		}
		valueString[i]=d;			//i=0  MSD bit will be stored in the first location of the array
		_delay_us(2);
		
	}
	PORTA |= (1<<clock);			//25th pulse(if number of PD_SCK pulses are 25.Then the input channel is 'A' and the gain is 128)
	_delay_us(2);					//DOUT pin back to high.When DOUT is high output data is not ready for retrieval
	PORTA &= ~(1<<clock);
	digitAmount=calculation();		
	
	
}

char calculation(){					
	int32_t summation=0;								//Set initial value to 0
	for(int j=23;j>=0;j--){								//Proceed to evaluate values from 24th location of the  array.
		
		if(valueString[j]=='0'){						//If the retrieved bit is 0,consider it as 1.Because the output of 24 bits of data is in 2's complement format.
			summation=summation + pow(2,(23-j))*1;		//Binary to decimal conversion 
		}
		
	}
	
	double decimalOutput=summation+1.0;                //Add 1 to summation after taking the complement 
	double finalValue=calibrationFactor*decimalOutput; //calibration factor(0.00002773232),This value should be calculated.
	loadCondition=round(finalValue);				   //round decimal values to integers
	int roundFinalValue=round(finalValue);
	
	int count=0;
	if(roundFinalValue==465){
		
		numbers[count]='0';
		_delay_ms(2);
		numbers[count+1]='0';
		
		}else{
		
		while(roundFinalValue>0){						//Store values in "numbers" array.
			
			int remainder=roundFinalValue%10;			//Split 'roundFinalValue' into characters for displaying on LCD.
			numbers[count]=remainder+'0';
			roundFinalValue=roundFinalValue/10;
			count++;
			_delay_ms(1);
			
		}
	}
	return count;
	
}
