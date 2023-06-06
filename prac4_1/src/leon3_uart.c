//! LEON3 UART A Transmit FIFO is FULL
#define LEON3_UART_TFF (0x200)

#define leon3_UART_TF_IS_FULL() (pLEON3_UART_REGS->Status & LEON3_UART_TFF)

#include "leon3_uart.h"

#include "leon3_bprint.h"

//Estructura de datos que permite acceder a los registros de la UART de LEON3
struct UART_regs
{
	/** \brief UART Data Register */
	volatile uint32_t Data;			/* 0x80000100 */
	/** \brief UART Status Register */
	volatile uint32_t Status;		/* 0x80000104 */
	/** \brief UART Control Register */
	volatile uint32_t Control;		/* 0x80000108 */
	/** \brief UART Scaler Register */
	volatile uint32_t Scaler;		/* 0x8000010C */

};

struct UART_regs * pLEON3_UART_REGS = (struct UART_regs *) 0x80000100;

int8_t leon3_putchar(char c)
{
	uint32_t write_timeout=0;
	while(leon3_UART_TF_IS_FULL() && (write_timeout < 0xAAAAA))
	{
		write_timeout++;
	} //Espera mientras la cola de transmisión esté llena
	if(write_timeout < 0xAAAAA){
		pLEON3_UART_REGS -> Data = c;
	}
	return (write_timeout == 0xAAAAA);
}


// Este metodo retorna el valor del registro Data de la UART, en formato uint8_t.
char leon3_getchar(){

	uint8_t i = (uint8_t) pLEON3_UART_REGS -> Data;	//Sacamos el valor del registro Data

	return i;
}


/**Este metodo retorna 1 si el campo Transmit_Fifo_EMPTY del registro Status de la UART
 * vale 1, y en caso contrario retorna 0.
 */
uint8_t leon3_UART_TF_IS_EMPTY(){
    uint32_t status_value = pLEON3_UART_REGS->Status;

    uint32_t bit = (1 << 2);

    if ((bit & status_value) == 0){
    	return 0;
    }else{
    	return 1;
    }
}


/** Este metodo pone a 1 el campo de Receiver_enable del registro de control de la UART,
 * sin modificar el resto de campos, habilitando la recepción de datos a través de la UART.
 */
void leon3_UART_RX_ENABLE(){
	uint32_t bit = (1 << 0);

	if ((pLEON3_UART_REGS -> Control & bit) == 0){
		pLEON3_UART_REGS -> Control = ((pLEON3_UART_REGS -> Control) | bit);
	}
}


/**Este metodo pone a 1 el campo de Receiver_interrupt_enable del registro de control de la
 * UART sin modificar el resto de campos, habilitando las interrupciones tras la recepcion
 * de datos.
 */
void leon3_UART_RX_IRQ_ENABLE(){
	uint32_t bit = (1 << 2);

	if ((pLEON3_UART_REGS -> Control & bit) == 0){
		pLEON3_UART_REGS -> Control = ((pLEON3_UART_REGS -> Control) | bit);
	}
}


/**Este metodo recibe como parametro el valor que se quiere fijar en el campo loop-back del
 * registro de control de la UART. Si es 1, se activa el modo loop-back, y con 0 se
 * deshabilita
 */
void leon3_UART_ConfigRXTXLoop(uint8_t set_rxtxloop){
	uint32_t bit = (1 << 7);
	uint32_t loop_back = pLEON3_UART_REGS -> Control;

	if (set_rxtxloop == 0){
		pLEON3_UART_REGS -> Control = (pLEON3_UART_REGS -> Control & ~bit);
	}else if (set_rxtxloop == 1){
		pLEON3_UART_REGS -> Control = (pLEON3_UART_REGS -> Control | bit);
	}else {
		leon3_putchar("Error, introduce el valor 0 o el valor 1");
	}
}



