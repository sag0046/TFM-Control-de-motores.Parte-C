/**
 * Clase que controla la comunicacion tanto con los motores como con el modulo bluetooth.
 * @file Modelo/comunicacion.c
 * @author XXXXX
 * @date XX/05/2016
 * @version 1.0
 */

#include "AS1.h"
#include "AS2.h"
#include "Modelo/comunicacion.h"
#include "stdlib.h"

/**
 * @brief Imprime encoder.
 *
 * Imprime en pantalla el valor recibido del encoder.
 * @param velocidad Valor recibido del motor.
 */
void UART_Write_Numero_Int(unsigned int velocidad){
	while(AS3_SendChar((char)(48+(velocidad%1000)/100))!= ERR_OK) {};
	while(AS3_SendChar((char)(48+(velocidad%100)/10))!= ERR_OK) {};
	while(AS3_SendChar((char)(48+(velocidad%10)))!= ERR_OK) {};
	while(AS3_SendChar((char)(48+(velocidad)))!= ERR_OK) {};
}

/**
 * @brief Envío velocidad Bluetooth.
 *
 * Envío de la velocidad por el puerto de Bluetooth.
 * @param velocidad Valor recibido del motor.
 */
void enviarVelocidad(int velocidadEnvio){
	if(velocidadEnvio == ERR_OK){
		//while(AS2_SendChar('n') != ERR_OK) {};
	}
	else{
		// Enviamos digito a digito la velocidad.
		while(AS2_SendChar((char)(48+(velocidadEnvio%1000)/100))!= ERR_OK) {};
		while(AS2_SendChar((char)(48+(velocidadEnvio%100)/10))!= ERR_OK) {};
		while(AS2_SendChar((char)(48+(velocidadEnvio%10)))!= ERR_OK) {};

	}
}

/**
 * @brief Obtener encoder.
 *
 * Obtiene la velocidad del encoder.
 */
float obtenerEncoder(){
	// Contador
	int i;
	// Variable del resultado
	float result;
	// Variable del dato a recibir
	AS1_TComData dato;
	// Mandamos los bytes del mensaje
	while(AS1_SendChar(0x00) != ERR_OK) {};
	while(AS1_SendChar(0x24) != ERR_OK) {};//get encoder2

	// Bucle para recibir los 4 bytes de la respuesta
	for(i = 0; i < 4; i++){
		// Recibimos el dato
		while(AS1_RecvChar(&dato) != ERR_OK) {};
		// Segun el nº de dato tiene un valor u otro.
		switch (i){
			case 0:
				result = dato << 24;
				break;
			case 1:
				result += dato << 16;
				break;
			case 2:
				result += dato << 8;
				break;
			case 3:
				result += dato;
		}
	}
	// Devolvemos el resultado
	return result;
}

/**
 * @brief Configura Motor.
 *
 * Configuración del motor para el envío y recibir datos.
 */
void configuracionMotor(){
	//Comandos para la configuración del motor.
	while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
	while(AS1_SendChar(0x36)!=ERR_OK){}; //COMANDO REGULADOR "disable regulator"

	while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
	while(AS1_SendChar(0x34)!=ERR_OK){}; //COMANDO MODO "set mode"
	while(AS1_SendChar(0x00)!=ERR_OK){}; //MANDAR MODO "0 (full reverse) - 128 (stop) - 255 (full forward)"

	while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
	while(AS1_SendChar(0x31)!=ERR_OK){}; //COMANDO VELOCIDAD "set speed1" Inhabilitamos el motor1 por ejemplo enviando 128
	while(AS1_SendChar(128) != ERR_OK) {}; // lo ponemos a 128 stop, ya que cogemos el MODO 0
}

/**
 * @brief Resetea los encoder.
 *
 * Manda a la controladora la orden de poner a 0 el encoder.
 */
void resetearEncoders(){
	// Mandamos los bytes del mensaje
	while(AS1_SendChar(0x00) != ERR_OK) {};
	while(AS1_SendChar(0x35) != ERR_OK) {};
}

/**
 * @brief Parada encoder.
 *
 * Manda a la controladora la orden parar el encoder.
 */
void stopMotor(){
	enviarVelocidad('S');
	// Mandamos los bytes del mensaje
	resetearEncoders();
	while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
	while(AS1_SendChar(0x32)!=ERR_OK){}; //COMANDO VELOCIDAD "set speed1" Inhabilitamos el motor1 por ejemplo enviando 128
	while(AS1_SendChar(128) != ERR_OK) {}; // lo ponemos a 128 stop, ya que cogemos el MODO0
}
