#include <stdint.h>
#include "uart.h"
#include "gpio.h"



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
	uart_init();

	while(1){
		
		char rx = uart_read();
		uart_send(rx); 
		// if B button pressed 
		if(!(GPIO->IN & (1<<26))){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1<<i); 
			}
			uart_send('B');
		}

		//if A button pressed
		else if(!(GPIO->IN & (1<<17))){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1<<i); 
			}
			uart_send('A');
		}								
		//Fra oppg1		
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}