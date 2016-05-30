/**
 * @brief Clase que se encarga de la implementacion del algoritmo PID.
 * @file Controlador/algoritmo.c
 * @author Sandra Ajates Gonzalez
 * @date Junio/2016
 * @version 1.0
 */

#include "AS1.h"
#include "AS2.h"
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "AS2.h"
#include "ASerialLdd2.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "LED_ROJO.h"
#include "LED_AZUL.h"
#include "LED_VERDE.h"
#include "AS3.h"
#include "ASerialLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "Controlador/algoritmo.h"
#include "Modelo/comunicacion.h"
#include "stdlib.h"

float encoder;      // valor encoder
float encoderAnt;   // valor del encoder en la anterior posicion
float distEncoder;  //distancia recorrida del encoder
int velEncoder;     //velocidad del encoder
extern bool llamada;

/**
 * @brief Calculo encoder.
 *
 * Calcula la velocidad a enviar al encoder en función del algoritmo seleccionado.
 * @param algoritmo Tomará valor - I: Integral, P: Proporcional, S: Stop.
 * @param velCalculada Valor a enviar al motor, tomará valores entre 0 y 255.
 * @param velCalculadaAnt Valor previo para el cálculo del ajuste.
 * @param velEncoder Valor recibido del motor.
 * @param error Diferencia entre la velocidad del encoder y la deseada.
 * @param errorK Acumulado de los errores para el recálculo del algoritmo Integral.
 * @param constK Valor recibido por el módulo Bluetooth insertada por el usuario.
 * @param constT Valor recibido por el módulo Bluetooth insertada por el usuario.
 * @param velocidad recibido por el módulo Bluetooth insertada por el usuario.
 */
void calcularDatosEncoder(char algoritmo, int *velCalculada, int *velCalculadaAnt, int *velEncoder, int *error, int *errorK, int constK, int constT, int *velocidad){
	int llamadaMotor;
	// Calculamos la velocidad en función del algoritmo recibido.
	if (llamada){
		llamada = FALSE;

		//CALCULAMOS DATOS DEL ENCODER: distancia recorrida y velocidad
		encoderAnt = encoder; // Guardamos los valores para el siguiente calculo
		encoder = obtenerEncoder(); // Obtenemos los valores de los encoders --- llamarla cada 0,1seg

		//distancia recorrida
		distEncoder = (encoder - encoderAnt); // Obtenemos la distancia recorrida por el enconder
			//velocidad rps
		//velocidadEncoder = (distEncoder1) * 10 / 360; //cada 0.1 seg
			//velocidad rpm --> *60

		//velocidad del encoder
		*velEncoder = (((distEncoder) * 10)/ 360)*60; //cada 0.1seg

		//Imprime de la velocidad del encoder para comparar con la gráfica.
		//UART_Write_Numero_Int(*velEncoder);

		//Envia velocidad por Bluetooth
		enviarVelocidad(*velEncoder);

		//Cálculo del error
		*error = *velocidad - *velEncoder;

		//Cálculo de la velocidad a enviar en función del algoritmo
		if (algoritmo == 'P'){
			*velCalculada = *velCalculadaAnt + ((float)constK/100)*(*error);
		} else if (algoritmo == 'I'){
			//Acumula todos los errores para el cáculo integral
			*errorK += *error;
			*velCalculada = *velCalculadaAnt + ((float)constK/100)*(*error) + ((float)constK/constT)*(*errorK)*0.1;
		}

		//la MAX velocidad que puede alcanzar velCalculada es 255
		if(*velCalculada>255) *velCalculada=255;
		if(*velCalculada<0) *velCalculada=0;
		else *velCalculada = *velCalculada;

		//Igualamos la varCalculada a velCalculadaAnt para el próximo recálculo
		*velCalculadaAnt=*velCalculada;

		//Eenvío al motor de la velCalculada
		while(AS1_SendChar(0x00)!=ERR_OK){}; //Sincroniza con el motor elegido
		while(AS1_SendChar(0x32)!=ERR_OK){}; //COMANDO VELOCIDAD set speed2 ya que el 0x31 es el parado
		while(AS1_SendChar(*velCalculada) != ERR_OK) {};
	}
}
