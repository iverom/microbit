#include "uart.h"


void uart_init () {
    //TGT_RXD og TGT_TXD har pin 24 og 25
	GPIO->PIN_CNF[24] = 1; // hvorfor
	GPIO->PIN_CNF[25] = 0; 

	//Disse må brukes av uart-modellen
	UART->PSELTXD = 24; 
	UART->PSELRXD = 25; 
	UART->PSELRTS = 0xFFFFFFFF; //Disabled
	UART->PSELCTS = 0xFFFFFFFF; //Disabled
	UART->BAUDRATE = 0x00275000; //Fra datablad
	UART->ENABLE = 4; 
    UART->STARTRX = 1;  
}

void uart_send(char letter) {
    UART->STARTTX = 1;
    UART->TXDRDY = 0; 
    UART->TXD = letter;
    while(!UART->TXDRDY);
    UART->STOPTX = 1;
}

char uart_read() {
    if (!UART->RXDRDY){
		return '\0';
    }
	char rx;
    UART->RXDRDY = 0;
	rx = UART->RXD; 
    return rx; 
}