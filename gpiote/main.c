#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){

    // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    GPIOTE->IN[0] = 1; // setter første in-pin til enable
    GPIOTE->CONFIG[0] = 0x11101; // setter in[0] sin mode til å være på rising edge, og pinselect til å være A-knapp og 
    // egentlig: 000 00 01 000 xxxxx 000000 01,
    // der xxxxx er pinnummeret til A-pinnen. Burde være 17: 10001 :::: => 000 00 01 000 10001 000000 01
    
    // kanskje for enable?
    //GPIOTE->OUT[0] = 1;

    // sette alle in-pins til enable
    GPIOTE->IN[1] = 1; 
    GPIOTE->IN[2] = 1; 
    GPIOTE->IN[3] = 1; 

    // konfigurerer pin 1, 2 og 3
    // (mode: toggle: pin: 13, initial:0) 0 00 11 0000 1101 000000 11 ::: (initial:1) 1 00 11 0000 1101 000000 11
    GPIOTE->CONFIG[1] = 0x130D03; // mode: toggle: pin: 13, initial:1
    GPIOTE->CONFIG[2] = 0x130E03; // mode: toggle: pin: 14, initial:1
    GPIOTE->CONFIG[3] = 0x130F03; // mode: toggle: pin: 15, initial:1

    // PPI setup
    // enables the three first channels
    PPI->CHEN = 0x7; // 111

    // 
    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

    PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);
    
    PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);


    

   while(1){

    }

}