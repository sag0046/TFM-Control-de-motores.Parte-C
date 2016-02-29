#include "UART.h"
#include "AS2.h"


void UART_Write_Numero_Int(unsigned int velocidad)
{
	while(AS2_SendChar((char)(48+(velocidad/10000)))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%10000)/1000))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%1000)/100))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%100)/10))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%10)))!= ERR_OK) {};
}

