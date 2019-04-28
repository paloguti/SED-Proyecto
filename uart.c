/*********************************************************************************************
* Fichero:	uart.c
* Autor:	
* Descrip:	funciones de UART
* Version: <P6-ARM-simple>	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "uart.h"
#include "visualizacion.h"
#include <stdarg.h>
#include <stdio.h>

void DelayMs(int time);

//void Uart0Rx_ISR(void) __attribute__ ((interrupt ("IRQ")));
//void Uart1Rx_ISR(void) __attribute__ ((interrupt ("IRQ")));

//extern int friendSeed;

int state = 0;
int fpPosX;
int fpPosY;

int fbPosX;
int fbPosY;

int fbBoomPosX;
int fbBoomPosY;

extern int fpSprite;

extern int foldPlayerPosX;
extern int foldPlayerPosY;
extern int fplayerPosX;
extern int fplayerPosY;

extern int fbombPosX;
extern int fbombPosY;

/*--- implementación de las funciones ---*/
void Uart_Init(int baud)
{
    /* UART0 */
    /*rULCON0=0x3;	// Modo normal, no paridad, 1b stop, 8b char
    rUCON0=0x85;	// tx=Pulse, rx=Pulse, rx-timeout ON, rx-error OFF, normal, int/polling
    rUBRDIV0=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
    rUFCON0=0x1;	// Activar FIFO, Rx FIFO Trigger Level = 4-bytes
    rUMCON0=0x0;	// Desactivar control de flujo
    */
	rULCON0=0x3;	// Modo normal, no paridad, 1b stop, 8b char
	rUCON0=0x205; 	// tx=nivel, rx = flanco, no rx-timeout ni rx-error, normal, int/polling
	rUBRDIV0=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
	rUFCON0=0x0;     // Desactivar FIFO
	rUMCON0=0x0;	 // Desactivar control de flujo

    /* UART1 */
    /*rULCON1=0x3;     // Modo normal, no paridad, 1b stop, 8b char
    rUCON1=0x85;    // tx=nivel, rx=flanco, no rx-timeout ni rx-error, normal, int/polling
    rUBRDIV1=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
    rUFCON1=0x1;	// Desactivar FIFO
    rUMCON1=0x0;	// Desactivar control de flujo
	*/
	rULCON1=0x3;     // Modo normal, no paridad, 1b stop, 8b char
	rUCON1=0x205;    // tx=nivel, rx=flanco, no rx-timeout ni rx-error, normal, int/polling
	rUBRDIV1=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
	rUFCON1=0x0;	// Desactivar FIFO
	rUMCON1=0x0;	// Desactivar control de flujo
    //Uart_Config();
}
/*
void Uart_Config(void)
{
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = ~0x0;
	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = ~0x0;
	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;
	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON &= ~(0x1<<1 | 0x1<<2);
	rINTCON |= 0x1<<0;
	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK &= ~((1<<7) | (1<<6) | (1<<26)); // Habiltar las lineas 21(Eint4567) y 26(bit global)
	// Establecer la rutina de servicio para Eint4567
	pISR_URXD0 = (unsigned) Uart0Rx_ISR;
	pISR_URXD1 = (unsigned) Uart1Rx_ISR;
/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	//rPCONG |= (1<<12 | 1<<13 | 1<<14 | 1<<15);
	//Habilita las resistencias de pull-up
	//rPUPG = 0;
	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	/*rEXTINT &= ~(1<<30 | 1<<26);
	rEXTINT |= 1<<29 | 1<<25;*/
/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	//RdURXH0();
	/*rUFCON0 |= 0x6;
	rUFCON0 |= 0x6;
	rI_ISPC = ~0x0;
}*/


// TODO Documentar estados
// 0 Esperando commandos.
// 1 Friend player posX.
// 2 Friend player posY.
// 3 Friend bomb posY.
// 4 Friend bombBoom posY.
// 5 Semilla.
/*
void Uart0Rx_ISR(void){

	char str[1];
	char *pt_str = str;

	while((rUFSTAT0 & 0xF) != 0){
		*pt_str = Uart0_Getch();
		DelayMs(100);
		Uart0_SendByte(*pt_str);
	}

	// borra el bit pendiente en INTPND
	rI_ISPC = 1<<7;

}
*/
/*
void Uart1Rx_ISR(void){
	char str[1];
	char *pt_str = str;

	while((rUFSTAT1 & 0xF) != 0){
		*pt_str = Uart1_Getch();

		if ((*pt_str & 0x80) != 0){
			state = 0;
		}

		if ((state == 0) && ((*pt_str & 0x80) != 0)){
			if((*pt_str & 0x60) == 0x00){
				fpPosX = 0;
				fpPosX |= (*pt_str & 0x18)<<4;
				fpPosY = 0;
				fpPosY |= (*pt_str & 0x04)<<5;
				fpSprite = (*pt_str & 0x03);
				state = 1;
				continue;
			}

			if((*pt_str & 0x60) == 0x20){
				fbPosX = 0;
				fbPosX |= (*pt_str & 0x1F);
				fbPosY = 0;
				state = 3;
				continue;
			}

			if((*pt_str & 0x60) == 0x40){
				if((*pt_str & 0x1F) == 0x00){
					state = 5;
					continue;
				}

				if((*pt_str & 0x1F) == 0x01){
					_gameOver();
					continue;
				}

				if((*pt_str & 0x1F) == 0x02){
					_gameWin();
					continue;
				}

			}

			if((*pt_str & 0x60) == 0x60){
				fbBoomPosX = 0;
				fbBoomPosX |= (*pt_str & 0x1F);
				fbBoomPosY = 0;
				state = 4;
				continue;
			}
		}

		if (state == 1){
			fpPosX |= *pt_str;
			state = 2;
			continue;
		}

		if (state == 2){
			fpPosY |= *pt_str;
			state = 0;

			foldPlayerPosX = fplayerPosX;
			foldPlayerPosY = fplayerPosY;
			fplayerPosX = fpPosX;
			fplayerPosY = fpPosY;
			continue;
		}

		if (state == 3){
			fbPosY |= *pt_str;
			state = 0;

			fbombPosX = fbPosX<<4;
			fbombPosY = fbPosY<<4; //Multiplicar por 16.
			continue;
		}

		if (state == 4){
			fbBoomPosY |= *pt_str;
			state = 0;

			boomBomb(1);

			fbombPosX = -1;
			fbombPosY = -1;
			continue;
		}

		if(state == 5){
			friendSeed = *pt_str;
			state = 0;
			continue;
		}
	}

	// borra el bit pendiente en INTPND
	rI_ISPC = 1<<6;
}
*/

inline void Uart0_TxEmpty(void){
    while (!(rUTRSTAT0 & 0x4));} 	     // esperar a que el shifter de TX se vacie

inline void Uart1_TxEmpty(void){
    while (!(rUTRSTAT1 & 0x4));} 	     // esperar a que el shifter de TX se vacie

char Uart0_Getch(void){
    while (!(rUTRSTAT0 & 0x1));        // esperar a que el buffer contenga datos
	return RdURXH0();}		   		   // devolver el caracter

char Uart1_Getch(void){
    while (!(rUTRSTAT1 & 0x1));        // esperar a que el buffer contenga datos
	return RdURXH1();}		   		   // devolver el caracter

void Uart0_SendByte(int data){
    if(data == '\n'){
	   while ((rUFSTAT0 & 0xF0) == 15);		// esperar a que la FIFO no este llena
	   WrUTXH0('\r');}						// escribir retorno de carro (utilizar macro)
    while ((rUFSTAT0 & 0xF0) == 15);		// esperar a que la FIFO no este llena
	WrUTXH0(data);}			       // escribir data (utilizar macro)

void Uart1_SendByte(int data){
    char localBuf[2] = {'\0','\0'};

    if(data == '\n')
	{
	   while (!(rUTRSTAT1 & 0x2));     // esperar a que THR se vacie
	   WrUTXH1('\r');			       // escribir retorno de carro (utilizar macro)
	}
	while (!(rUTRSTAT1 & 0x2)); 	   // esperar a que THR se vacie
	WrUTXH1(data);				       // escribir data (utilizar macro)
}


void Uart0_SendString(char *pt){
    while (*pt)						    // mandar byte a byte hasta completar string
	Uart0_SendByte(*pt++);}

void Uart1_SendString(char *pt){
    while (*pt)						    // mandar byte a byte hasta completar string
	Uart1_SendByte(*pt++);}

void Uart0_Printf(char *fmt,...){
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart0_SendString(string);
    va_end(ap);
}

void Uart1_Printf(char *fmt,...){
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart1_SendString(string);
    va_end(ap);}

/*
void enviarPosPlayer(int posX, int posY, int pSprite){
	int toSendByte = 0x80;
	toSendByte |= (posX & 0x180)>>4;
	toSendByte |= (posY & 0x80)>>5;
	toSendByte |= (pSprite & 0x2);
	Uart1_SendByte(toSendByte);

	toSendByte = 0x00;
	toSendByte |= (posX & 0x7F);
	Uart1_SendByte(toSendByte);

	toSendByte = 0x00;
	toSendByte |= (posY & 0x7F);
	Uart1_SendByte(toSendByte);
}

void enviarPosBomb(int posX, int posY){
	int toSendByte = 0x80;
	toSendByte |= 0x20;
	toSendByte |= posX>>4; // Dividir entre 16.
	Uart1_SendByte(toSendByte);

	toSendByte = 0x00;
	toSendByte |= posY>>4;
	Uart1_SendByte(toSendByte);
}*/
/*
void enviarPosBombBoom(int posX, int posY){
	int toSendByte = 0x80;
	toSendByte |= 0x60;
	toSendByte |= posX>>4; // Dividir entre 16.
	Uart1_SendByte(toSendByte);

	toSendByte = 0x00;
	toSendByte |= posY>>4;
	Uart1_SendByte(toSendByte);
}
*/
/*
void enviarSeed(int seed){
	int toSendByte = 0x80;
	toSendByte |= 0x40;
	Uart1_SendByte(toSendByte);

	toSendByte = seed & 0x7F;
	Uart1_SendByte(toSendByte);
}
*/

void enviarGameWin(){
	int toSendByte = 0x80;
	toSendByte |= 0x40;
	toSendByte |= 0x01;
	Uart1_SendByte(toSendByte);
}

void enviarGameLose(){
	int toSendByte = 0x80;
	toSendByte |= 0x40;
	toSendByte |= 0x02;
	Uart1_SendByte(toSendByte);
}

