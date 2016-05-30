/*!
** @file Modelo/comunicacion.h
** @version 01.00
** @brief
**         Contiene las declaraciones de las funciones relacionadas con la comunicacion.
**
*/
void UART_Write_Numero_Int(unsigned int velocidad);
void enviarVelocidad(int velocidadEnvio);
float obtenerEncoder();
void configuracionMotor();
void resetearEncoders();
void stopMotor();
