#include "UART.h"
#include "AS2.h"

/* Cambiar
void UART_Write_Numero_Int(unsigned int velocidad)
{
	while(AS2_SendChar((char)(48+(velocidad/10000)))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%10000)/1000))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%1000)/100))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%100)/10))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+(velocidad%10)))!= ERR_OK) {};
}

Cambiar por:
*/

void UART_Write_Numero_Int(unsigned int velocidad)
{
	while(AS3_SendChar((char)(48+(velocidad%1000)/100))!= ERR_OK) {};
	while(AS3_SendChar((char)(48+(velocidad%100)/10))!= ERR_OK) {};
	while(AS3_SendChar((char)(48+(velocidad%10)))!= ERR_OK) {};
}

void enviarVelocidad(int x){
	// Enviamos una X de prueba
	//while(AS2_SendChar('Z') != ERR_OK) {};

//	int j = 49; // Hay que mandar en ASCII
	//int j = 132; // para mandar 132

	//char var = "049051053";  // 135 velocidad

	/*char var = (char)((j%1000)/100)+48;
	var += (char)((j%100)/10)+48;
	var += (char)(j%10)+48;*/

	if(x == ERR_OK){
		while(AS2_SendChar('n') != ERR_OK) {};

	}
	else{
		while(AS2_SendChar(x) != ERR_OK) {};
		while(AS2_SendChar('j') != ERR_OK) {};
		//while(AS2_SendChar(var) != ERR_OK) {};
		//while(AS2_SendChar(x) != ERR_OK) {};
		/*while(AS2_SendChar((char)((x%10000)/1000))!= ERR_OK) {};
		while(AS2_SendChar((char)((x%1000)/100))!= ERR_OK) {};
		while(AS2_SendChar((char)((x%100)/10))!= ERR_OK) {};
		while(AS2_SendChar((char)((x%10)))!= ERR_OK) {};*/

	}

	// Enviamos digito a digito el numero
	/*while(AS2_SendChar((char)(48+((int)abs(x)%1000)/100))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+((int)abs(x)%100)/10))!= ERR_OK) {};
	while(AS2_SendChar((char)(48+((int)abs(x)%10)))!= ERR_OK) {};*/
}
