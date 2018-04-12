#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	int sleep = 0;

	while(1){

		// if B button pressed 
		if(!(GPIO->IN & (1<<26))){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1<<i); 
			}
		}

		//if A button pressed
		else if(!(GPIO->IN & (1<<17))){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1<<i); 
			}
		}								
		sleep = 10000;

		while(--sleep);

	}
	
	return 0;
}


//Knapp A koblet til pin 17 og knapp B koblet til pin 26
//De vil være lave ved trykk
//0x50000000 er base for GPIO 
//Verdien til PIN_CNF[0] = 0x700 minus verdien til DIRCLR = 0x520 og dele på 4 for å 
//finne verdien til reserved_size = 120 
