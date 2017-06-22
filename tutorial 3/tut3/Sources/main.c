#include "derivative.h"
#include "clock.h"
#include <stdio.h>

void initialiseADC (void){
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		
		PORTC_PCR0 = PORT_PCR_MUX(0);
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
		ADC0_SC2 = ADC_SC2_REFSEL(0);
		ADC0_SC3 = 0;
		ADC0_CFG1 = ADC_CFG1_ADIV(2)|ADC_CFG1_MODE(2)|ADC_CFG1_ADICLK(0);
		ADC0_CFG2 = ADC_CFG2_MUXSEL_MASK;
}

int doADCConversion(void){
	ADC0_SC1A = ADC_SC1_ADCH(14);
	while((ADC0_SC1A&ADC_SC1_COCO_MASK)==0){
		
	}
	return ADC0_RA;
}

int main(void){
	clock_initialise();
	initialiseADC();
	for(;;){
		int result = doADCConversion();
		printf("ADC Channel 14 = %d\n", result);
	}
	return 0;
}
