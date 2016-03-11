/* ###################################################################
**     Filename    : main.c
**     Project     : ControlMotor
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-20, 11:59, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
//---------------------------ENCODER--------------------------------//
float encoder;  //ponerla como externa
float encoderAnt; // con el valor del encoder de la anterior posicion del encoder
float distEncoder; //distancia recorrida del encoder
//---------------------------ENCODER--------------------------------//
extern int t; // ver events.c
extern bool llamada;


//extern AS2_TComData velReferencia; //velocidad deseada
//extern AS2_TComData k; // K=cte , constante
//extern AS2_TComData X;

AS2_TComData velReferencia; //velocidad deseada
//AS2_TComData k=0.01; // K=cte , constante
AS2_TComData X;


struct {
byte Comando;
byte Valor;
} datos;

static float obtenerEncoder(){

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
static void configuracionMotor(){
	int i;
	char message[] = "Introduce una velocidad de 0 (full reverse)  128 (stop)   255 (full forward):";
	// Imprime 1er mensaje para introducir la "velReferencia" o velocidad deseada
	    velReferencia = '0';							//Lo inicializa a NULL
	    for(i = 0; i < sizeof(message); i++) {
	  	while(AS2_SendChar((byte)message[i]) != ERR_OK) {}


			//COMANDOS PARA LA CONFIGURACION DEL MOTOR
			while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
			while(AS1_SendChar(0x36)!=ERR_OK){}; //COMANDO REGULADOR "disable regulator"

			while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
			while(AS1_SendChar(0x34)!=ERR_OK){}; //COMANDO MODO "set mode"
			while(AS1_SendChar(0x00)!=ERR_OK){}; //MANDAR MODO "0 (full reverse)  128 (stop)   255 (full forward)"
			//while(AS1_SendChar(0x01)!=ERR_OK){}; //MANDAR MODO "-128(full reverse)0(stop) 127 (full forward)."

			while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
			while(AS1_SendChar(0x31)!=ERR_OK){}; //COMANDO VELOCIDAD "set speed1"
			while(AS1_SendChar(128) != ERR_OK) {}; // lo ponemos a 128 stop, ya que cogemos el MODO0
			//while(AS1_SendChar(0) != ERR_OK) {}; // lo ponemos a 0 stop, ya que cogemos el modo1

	    }
}
static void imprimirVariables(int error, int velEncoder, int velCalculada){

	char msg_velEncoder[] = "Velocidad Encoder:";
	char msg_error[] = "Error:";
	char msg_velCalculada[] = "Velocidad calculada";
	char msg_velReferencia[] = "Velocidad deseada";
	char msg_k [] = "Constante K:";
	char messagek[] = "Introduce una cte K:";
	int a,b,c,d,f;
	 //IMPRIMIR LAS VARIABLES velEncoder, velReferencia, error, velCalculada
	  			 	 //imprime velocidadEncoder
	  			 for(a = 0; a < sizeof(msg_velEncoder); a++) {
	  				while(AS2_SendChar((byte)msg_velEncoder[a]) != ERR_OK) {}
	  			  }

	  			 UART_Write_Numero_Int(velEncoder); //escribe el valor de velocidadEncoder
	  			 while(AS2_SendChar(10)!=ERR_OK){};//tabulacion vertical
	  			 while(AS2_SendChar(13)!=ERR_OK){};//retorno de carro


	  			 // Imprime error
	  			 for(b = 0; b < sizeof(msg_error); b++) {
	  				while(AS2_SendChar((byte)msg_error[b]) != ERR_OK) {}
	  				}

	  			 UART_Write_Numero_Int(error) ;
	  			 while(AS2_SendChar(10)!=ERR_OK){};
	  			 while(AS2_SendChar(13)!=ERR_OK){};

	  				//Imprime velCalculada
	  			  for(c = 0; c < sizeof(msg_velCalculada); c++) {
	  				while(AS2_SendChar((byte)msg_velCalculada[c]) != ERR_OK) {}
	  			  }

	  			  UART_Write_Numero_Int(velCalculada) ;
	  			  while(AS2_SendChar(10)!=ERR_OK){};
	  			  while(AS2_SendChar(13)!=ERR_OK){};


	  				//Imprime la velReferencia --> velocidad deseada
	  			  for(d = 0; d < sizeof(msg_velReferencia); d++) {
	  				while(AS2_SendChar((byte)msg_velReferencia[d]) != ERR_OK) {}
	  			  }

	  				UART_Write_Numero_Int(velReferencia) ;
	  				while(AS2_SendChar(10)!=ERR_OK){};
	  				while(AS2_SendChar(13)!=ERR_OK){};

	  			/*	Imprime la k --> cte deseada
	  			  for(f = 0; f < sizeof(msg_ctek); d++) {
	  				while(AS2_SendChar((byte)msg_ctek[f]) != ERR_OK) {}
	  			  }

	  				UART_Write_Numero_Int(k) ;
	  				while(AS2_SendChar(10)!=ERR_OK){};
	  				while(AS2_SendChar(13)!=ERR_OK){};*/
}
static void comprobarDatos(int *k){

	// Comprobamos si es una V de velReferencia.
					if(datos.Comando == 118) {  velReferencia = datos.Valor;
							//Comprobamos la constante k
					}if(datos.Comando == 107){
						*k = datos.Valor;
					}

}
static calcularDatosEncoder(int *velCalculada, int *velCalculadaAnt, int *velEncoder, int *error, int k){
     	//CALCULAMOS DATOS DEL ENCODER: distancia recorrida y velocidad
  		encoderAnt = encoder; // Guardamos los valores para el siguiente calculo
  		encoder= obtenerEncoder(); // Obtenemos los valores de los encoders --- llamarla cada 0,1seg

  			//distancia recorrida
  		distEncoder = (encoder - encoderAnt); // Obtenemos la distancia recorrida por el enconder
  			//velocidad rps
  		//velocidadEncoder = (distEncoder1) * 10 / 360; //cada 0.1 seg
  			//velocidad rpm --> *60
  		*velEncoder = (distEncoder) * 10/ 360*60; //cada 0.1seg

  		//CALCULAMOS EL ERROR
  		*error= velReferencia - *velEncoder;
  		//velCalculada = velCalculadaAnt + error; //(P=Proporcional y PI = P+Integral)
  		//velCalculada = velCalculadaAnt + 0.01*error;    //MODIFICAR ESTA PARA LA DEL PI 0.01 es la "k"
  		*velCalculada = *velCalculadaAnt + (float)k/100*(*error);


				//la MAX velocidad que puede alcanzar velCalculada es 255
			if(*velCalculada>255) *velCalculada=255;
			if(*velCalculada<0) *velCalculada=0;
			else *velCalculada = *velCalculada;

			*velCalculadaAnt=*velCalculada;  //Igualamos la varCalculada a velCalculadaAnt
  	}

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	int k;
	int t;
// k = 1;
/*VARIABLES USADAS*/

    LDD_TDeviceData *Rojo_Ptr, *Verde_Ptr, *Azul_Ptr;
    int y,e; //Contadores bucles FOR para imprimira por pantalla
    int velCalculada=0; // velocidad calcualda
    int velCalculadaAnt=0; //velocidad calculada anterior
    int velEncoder = 0; //velocidad real
    int error = 0; //variable que recoge el error
    byte err; /*????*/

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

    /*CODIGO*/
  	  configuracionMotor();

  	  for(;;) {
  		// Comprobamos si es una V de velReferencia.
  							/*if(datos.Comando == 118) {  velReferencia = datos.Valor;
  									//Comprobamos la constante k
  							}if(datos.Valor == 107){
  								k = datos.Valor;
  							}*/
  		 comprobarDatos(&k);
		//AS2_RecvChar(&velReferencia); //Introducimos la velReferencia por puerto serie
      	if (llamada){

         		llamada = FALSE;


      		calcularDatosEncoder(&velCalculada, &velCalculadaAnt, &velEncoder, &error, k);

  			 //IMPRIMIR LAS VARIABLES velEncoder, velReferencia, error, velCalculada
  			 imprimirVariables(error, velCalculada, velEncoder);

  		//ENVIO AL MOTOR de la velCalculada ----> se añadiria antes de empezar las impresiones x pantalla
  		while(AS1_SendChar(0x00)!=ERR_OK){}; //SINCRONIZAR
  		while(AS1_SendChar(0x32)!=ERR_OK){}; //COMANDO VELOCIDAD set speed2 ¿xq al 2 y no al 0x31 como arriba?
  		while(AS1_SendChar(velCalculada) != ERR_OK) {};


  		LED_ROJO_SetVal(Rojo_Ptr);
  		LED_VERDE_SetVal(Verde_Ptr);
  		LED_AZUL_NegVal(Azul_Ptr);

      	}
      }
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
