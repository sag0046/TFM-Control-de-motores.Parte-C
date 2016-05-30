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

/**
 * @brief Programa principal. Inicio del programa.
 * @file Controlador/main.c
 * @author Sandra Ajates González
 * @date Junio/2016
 * @version 1.0
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
#include "AS3.h"
#include "ASerialLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Controlador/algoritmo.h"
#include "Modelo/comunicacion.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
//---------------------------ENCODER--------------------------------//
float encoder;      // valor encoder
float encoderAnt;   // valor del encoder en la anterior posicion
float distEncoder;  //distancia recorrida del encoder
int velEncoder;     //velocidad del encoder
//---------------------------ENCODER--------------------------------//
extern int ti; // tiempo de interrupcion events.c
extern bool llamada;

/**
 * Tarea principal. Se ejecuta continuamente recogiendo los datos recibidos
 * por bluetooth para despues actuar segun el mensaje recibido.
 *
 */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
    LDD_TDeviceData *Rojo_Ptr, *Verde_Ptr, *Azul_Ptr;
    int y,e; //Contadores bucles FOR para imprimir por pantalla
    int velCalculada=0; // velocidad calculada
    int velCalculadaAnt=0; //velocidad calculada anterior
    int velEncoder = 0; //velocidad real
    int error = 0; //variable que recoge el error
    int errorK = 0;
    byte err;

    int cont=0; // Contador

	int velocidad=0;
	int constK=0;
	int constT=0;
	char algoritmo;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	// Reseteamos los encoders.
  	resetearEncoders();

    // Configuración del motor.
  	configuracionMotor();

  	for(;;) {
	  AS2_TComData datoRecibido; // Dato recibido por el puerto serie del modulo bluetooth.
	  if(AS2_RecvChar(&datoRecibido) == ERR_OK){
	    // Comprobamos si es una P, lo que significa que es el algorimo rdProporcional
	    if(datoRecibido == 80){
		  // Vamos obteniendo el resto del mensaje y localizando la velocidad, son siempre 3 caracteres.
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad=(datoRecibido-48)*100;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad+=(datoRecibido-48)*10;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad+=(datoRecibido-48);
		  UART_Write_Numero_Int(velocidad); //muestra por consola el valor de la Velocidad

		  // Vamos obteniendo el resto del mensaje y localizando la constanteK, son siempre 3 caracteres.
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK=(datoRecibido-48)*100;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK+=(datoRecibido-48)*10;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK+=(datoRecibido-48);
		  UART_Write_Numero_Int(constK);//muestra por consola el valor de la K

		  // Al ser el algoritmo rdProporcional, no hay valor para constT.
		  constT=0;
		  algoritmo='P';

	    // Comprobamos si es una I, lo que significa que es el algorimo rdIntegral
	    }else if (datoRecibido == 73){
		  // Vamos obteniendo el resto del mensaje y localizando la velocidad, son siempre 3 caracteres.
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad=(datoRecibido-48)*100;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad+=(datoRecibido-48)*10;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  velocidad+=(datoRecibido-48);
		  UART_Write_Numero_Int(velocidad);//muestra por consola el valor de la Velocidad

		  // Vamos obteniendo el resto del mensaje y localizando la constanteK, son siempre 3 caracteres.
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK=(datoRecibido-48)*100;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK+=(datoRecibido-48)*10;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constK+=(datoRecibido-48);
		  UART_Write_Numero_Int(constK);//muestra por consola el valor de la K

		  // Al ser el algoritmo rdIntegral, si hay valor para constt, son siempre 3 caracteres.
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constT=(datoRecibido-48)*100;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constT+=(datoRecibido-48)*10;
		  while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
		  constT+=(datoRecibido-48);
		  UART_Write_Numero_Int(constT);//muestra por consola el valor del Tiempo

		  // Al ser el algoritmo rdIntegral, variable 'I'.
		  algoritmo='I';

		}else if (datoRecibido == 83){// una S
		  // Botón pulsado STOP, parada del motor.
			algoritmo='S';
		}
	  }

	LED_ROJO_SetVal(Rojo_Ptr);
	LED_VERDE_SetVal(Verde_Ptr);
	LED_AZUL_NegVal(Azul_Ptr);

	//En función de la orden indicada..
	if (algoritmo == 'P' || algoritmo == 'I'){
		UART_Write_Numero_Int(51);
		calcularDatosEncoder(algoritmo, &velCalculada, &velCalculadaAnt, &velEncoder, &error, &errorK, constK, constT, &velocidad);
	} else if (algoritmo == 'S'){
		UART_Write_Numero_Int(52);
		stopMotor();
	}
  }

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
