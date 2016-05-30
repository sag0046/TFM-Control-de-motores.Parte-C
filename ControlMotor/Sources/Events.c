/* ###################################################################
**     Filename    : Events.c
**     Project     : ControlMotor
**     Processor   : MK64FN1M0VLQ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-20, 11:59, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         Clase encargada de los eventos del programa.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */


void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}


/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
*/
/*!
**     @brief
**         Cuando se produce una interrupción del temporizador
**         se llama a este evento.
**
*/
/* ===================================================================*/

int ti=0;
bool llamada;

void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
	ti++;
	llamada=TRUE;
}


/*
** ===================================================================
**     Event       :  AS2_OnFullRxBuf (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*extern struct {
byte Comando;
byte Valor;
} datos;*/
/*void AS2_OnFullRxBuf(void)
{
	/* Write your code here ... */
	//word Received;

	//AS2_TComData datoRecibido; // Dato recibido por el puerto serie perteneciente al modulo bluetooth.

	//AS2_RecvBlock((byte*)&datos, sizeof(datos), &Received);

	//AS2_RecvBlock(datoRecibido, sizeof(datoRecibido), &Received);



	/*char valor; // Valor recibido por el modulo bluetooth.

	int velo;
	int k;
	int t;

	//while(AS2_RecvChar(&datoRecibido) != ERR_OK){};



	if(AS2_RecvChar(&datoRecibido) == ERR_OK){
		//enviarVelocidad('y');
	//enviarVelocidad(1);
	// Comprobamos si es una X, lo que significa que es un movimiento a un punto concreto
	if(datoRecibido == 80){
	// Vamos obteniendo el resto del mensaje y construyendo el número
		//enviarVelocidad('k');

	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	if(datoRecibido == '0'){
		enviarVelocidad('a');
	}else{
		enviarVelocidad('b');
	}
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	if(datoRecibido == '1'){
			enviarVelocidad('c');
		}else{
			enviarVelocidad('d');
		}

	velo = (datoRecibido)*100;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	velo += (datoRecibido)*10;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	velo += (datoRecibido);
	enviarVelocidad(velo);


	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	k = (datoRecibido)*100;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	k += (datoRecibido)*10;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	k += (datoRecibido);
	enviarVelocidad(k);

	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	t = (datoRecibido)*100;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	t += (datoRecibido)*10;
	while(AS2_RecvChar(&datoRecibido) != ERR_OK){};
	t += (datoRecibido);
	enviarVelocidad(t);


	}
	else if(datoRecibido == "P"){
	while(AS2_SendChar('y') != ERR_OK) {};
	} else {
	while(AS2_SendChar('z') != ERR_OK) {};
	}
	}
	else{
		//enviarVelocidad('y');
	}

	//valor = datoRecibido;

	//enviarVelocidad(valor);
	//enviarVelocidad((int)datos.Valor);
	//enviarVelocidad((int)datos.Valor);
}*/

/*
** ===================================================================
**     Event       :  AS2_OnError (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnRxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnTxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnFullRxBuf (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
