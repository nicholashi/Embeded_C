/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */

#define PIN1_MASK (1<<1)
#define PIN2_MASK (1<<2)
#define PIN3_MASK (1<<3)
#define PIN_MASK PIN1_MASK|PIN2_MASK|PIN3_MASK

void initialiseCharlieplexing(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	PORTD_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	PORTD_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	PORTD_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
}

void setLED(int ledNum){
	int PDOR_Array[6] = {	(GPIOD_PDOR|PIN_MASK)&~PIN3_MASK, 
							(GPIOD_PDOR|PIN_MASK)&~PIN1_MASK, 
							(GPIOD_PDOR|PIN_MASK)&~PIN2_MASK, 
							(GPIOD_PDOR|PIN_MASK)&~PIN1_MASK,
							(GPIOD_PDOR|PIN_MASK)&~PIN3_MASK,
							(GPIOD_PDOR|PIN_MASK)&~PIN2_MASK
	};
	
	int PDDR_Array[6] = {	(GPIOD_PDDR|PIN_MASK)&~PIN2_MASK,
							(GPIOD_PDDR|PIN_MASK)&~PIN2_MASK,
							(GPIOD_PDDR|PIN_MASK)&~PIN3_MASK,
							(GPIOD_PDDR|PIN_MASK)&~PIN3_MASK,
							(GPIOD_PDDR|PIN_MASK)&~PIN1_MASK,
							(GPIOD_PDDR|PIN_MASK)&~PIN1_MASK
	};
	
	GPIOD_PDOR = PDOR_Array[(ledNum - 1)];
	GPIOD_PDDR = PDDR_Array[(ledNum - 1)];
	                        
}

void delay(){
	int i;
	for(i=0; i<1000000; i++){
		asm("nop");
	}
}
int main(void)
{
	int x;
	for(;;){
		initialiseCharlieplexing();
		for(x=1; x<7; x++){
			setLED(x);
			delay();
		}
	}
	return 0;
}


