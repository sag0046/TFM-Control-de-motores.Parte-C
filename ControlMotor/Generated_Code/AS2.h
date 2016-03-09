/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AS2.h
**     Project     : ControlMotor
**     Processor   : MK64FN1M0VLQ12
**     Component   : AsynchroSerial
**     Version     : Component 02.611, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-03-09, 18:32, # CodeGen: 13
**     Abstract    :
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
**     Settings    :
**         Serial channel              : UART0
**
**         Protocol
**             Width                   : 8 bits
**             Stop bits               : 1
**             Parity                  : none
**             Breaks                  : Disabled
**             Input buffer size       : 2
**             Output buffer size      : 0
**
**         Registers
**             Input buffer            : UART0_D   [0x4006A007]
**             Output buffer           : UART0_D   [0x4006A007]
**             Control register        : UART0_C1  [0x4006A002]
**
**         Input interrupt
**             Vector name             : INT_UART0_RX_TX
**             Priority                : 112
**
**         Output interrupt
**             Vector name             : INT_UART0_RX_TX
**             Priority                : 112
**
**         Used pins:
**         ----------------------------------------------------------
**           Function | On package           |    Name
**         ----------------------------------------------------------
**            Input   |     95               |  PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN
**            Output  |     96               |  PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b
**         ----------------------------------------------------------
**
**
**
**     Contents    :
**         RecvChar        - byte AS2_RecvChar(AS2_TComData *Chr);
**         SendChar        - byte AS2_SendChar(AS2_TComData Chr);
**         RecvBlock       - byte AS2_RecvBlock(AS2_TComData *Ptr, word Size, word *Rcv);
**         ClearRxBuf      - byte AS2_ClearRxBuf(void);
**         GetCharsInRxBuf - word AS2_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word AS2_GetCharsInTxBuf(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file AS2.h
** @version 01.01
** @brief
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
*/         
/*!
**  @addtogroup AS2_module AS2 module documentation
**  @{
*/         

#ifndef __AS2
#define __AS2

/* MODULE AS2. */

/* Include inherited components */
#include "ASerialLdd2.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 



#ifndef __BWUserType_AS2_TError
#define __BWUserType_AS2_TError
  typedef union {
  byte err;
  struct {
    bool OverRun  : 1;                 /* Overrun error flag */
    bool Framing  : 1;                 /* Framing error flag */
    bool Parity   : 1;                 /* Parity error flag */
    bool RxBufOvf : 1;                 /* Rx buffer full error flag */
    bool Noise    : 1;                 /* Noise error flag */
    bool Break    : 1;                 /* Break detect */
    bool LINSync  : 1;                 /* LIN synchronization error */
    bool BitError  : 1;                /* Bit error flag - mismatch to the expected value happened. */
  } errName;
} AS2_TError;                          /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
#endif

#ifndef __BWUserType_AS2_TComData
#define __BWUserType_AS2_TComData
  typedef byte AS2_TComData;           /* User type for communication. Size of this type depends on the communication data witdh */
#endif

#define AS2_INP_BUF_SIZE  0x02U        /* Length of the RX buffer */

/*
** ===================================================================
**     Method      :  AS2_RecvChar (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). This method is enabled only if the receiver property
**         is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence the
**         information about an exception in interrupt mode is returned
**         only if there is a valid character ready to be read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service> property
**                           is disabled and the <Break signal> property
**                           is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/
byte AS2_RecvChar(AS2_TComData *Chr);

/*
** ===================================================================
**     Method      :  AS2_SendChar (component AsynchroSerial)
**     Description :
**         Sends one character to the channel. If the component is
**         temporarily disabled (Disable method) SendChar method only
**         stores data into an output buffer. In case of a zero output
**         buffer size, only one character can be stored. Enabling the
**         component (Enable method) starts the transmission of the
**         stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte AS2_SendChar(AS2_TComData Chr);

/*
** ===================================================================
**     Method      :  AS2_RecvBlock (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns the block of
**         the data and its length (and incidental error), otherwise it
**         returns an error code (it does not wait for data).
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**         If less than requested number of characters is received only
**         the available data is copied from the receive buffer to the
**         user specified destination. The value ERR_EXEMPTY is
**         returned and the value of variable pointed by the Rcv
**         parameter is set to the number of received characters.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of received data
**         Size            - Size of the block
**       * Rcv             - Pointer to real number of the received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data has been returned.
**                           ERR_COMMON - common error occurred (the
**                           GetError method can be used for error
**                           specification)
** ===================================================================
*/
byte AS2_RecvBlock(AS2_TComData *Ptr,word Size,word *Rcv);

/*
** ===================================================================
**     Method      :  AS2_ClearRxBuf (component AsynchroSerial)
**     Description :
**         Clears the receive buffer.
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AS2_ClearRxBuf(void);

/*
** ===================================================================
**     Method      :  AS2_GetCharsInRxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the input buffer. This
**         method is available only if the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the input
**                           buffer.
** ===================================================================
*/
word AS2_GetCharsInRxBuf(void);

/*
** ===================================================================
**     Method      :  AS2_GetCharsInTxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the output buffer. This
**         method is available only if the transmitter property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the output
**                           buffer.
** ===================================================================
*/
word AS2_GetCharsInTxBuf(void);

/*
** ===================================================================
**     Method      :  AS2_Init (component AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AS2_Init(void);

/*
** ===================================================================
**     Method      :  AS2_ASerialLdd2_OnBlockReceived (component AsynchroSerial)
**
**     Description :
**         This event is called when the requested number of data is 
**         moved to the input buffer.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd2_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  AS2_ASerialLdd2_OnBlockSent (component AsynchroSerial)
**
**     Description :
**         This event is called after the last character from the output 
**         buffer is moved to the transmitter.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd2_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  AS2_ASerialLdd2_OnError (component AsynchroSerial)
**
**     Description :
**         This event is called when a channel error (not the error 
**         returned by a given method) occurs.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd2_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  AS2_ASerialLdd2_OnBreak (component AsynchroSerial)
**
**     Description :
**         This event is called when a break occurs on the input channel.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ASerialLdd2_OnBreak(LDD_TUserData *UserDataPtr);


/* END AS2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif /* ifndef __AS2 */
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
