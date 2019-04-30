/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "def.h"
#include "uart.h"
//#include "playerMovement.h"


extern const int NCOL;
extern int tablero[];
extern int turno;
extern int comprobarFinDelJuego();

/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;
int key;

/*--- Funciones externas ---*/
void D8Led_symbol(int value);
extern void drawO(int posicion);
extern void drawX(int posicion);

/*--- Declaracion de funciones ---*/
void keyboard_init();
int key_read();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));


/*--- Codigo de las funciones ---*/
void keyboard_init()
{
	/* Configurar el puerto G (si no lo estuviese ya) */	
	// Establece la funcion de los pines (EINT0-7)
	rPCONG |= 0xC;
	//rPCONG |= (1<<2 | 1<<3);

	// Habilita el "pull up" del puerto
	rPUPG = 0x0;

	/*
		AÑADIMOS LAS INTERRUPCIONES
	*/

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = 0x22222222;

	/* Establece la rutina de servicio para EINT1 */
	pISR_EINT1 = (unsigned) KeyboardInt; // Funcion de arriba indicada para interrupciones

	/* Configurar controlador de interrupciones */
	// Borra INTPND escribiendo 1s en I_ISPC
	//rEXTINTPND = 0xf;
	rI_ISPC = 0x3ffffff;
	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;
	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;

	/* Habilitar linea EINT1 */
	rINTMSK = rINTMSK & ~(BIT_EINT1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Eint1 y el bit global

	/* Por precaucion, se vuelven a borrar los bits de INTPND correspondientes*/
	rI_ISPC = 0x3ffffff;
}


void KeyboardInt(void)
{

	int aux[9];
	int i;
	for (i = 0; i < 9; i++){
		aux[i] = tablero[i];
	}
	/* Esperar trp mediante la funcion DelayMs()*/
	DelayMs(100);
	/* Identificar la tecla */
	key = 15;
	while (key > NCOL*NCOL || tablero[key] != 0 ){ // es como que deshabilitamos el resto de teclas...
		key = key_read();
		int aux2 = tablero[key];
		DelayMs(1);
	}

	/* Si la tecla se ha identificado, visualizarla en el 8SEG*/
	if(key > -1 && tablero[key] == 0)
	{
		D8Led_symbol(key);
		//lcd_puts_x2(40,20,0xffffff,"X");
		tablero[key] = (turno % 2) +1;
		for (i = 0; i < 9; i++){
			aux[i] = tablero[i];
		}
		Uart1_SendByte(key);
		int h = turno;
		if (turno % 2 == 0){
			drawO(key);
		}
		else {
			drawX(key);
		}
		h = turno;
		int fin = comprobarFinDelJuego();

		if(fin != 0){
			drawFin(fin);
			Uart1_SendByte('f');
		}


		DelayMs(1);
	}
	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while ((rPDATG & 0x00000002) == 0 ){ // Que está pulsada la tecla
		//NOTHING
	}
	/* Esperar trd mediante la funcion Delay() */
	DelayMs(100);

	/* Borrar interrupción de teclado */
	rI_ISPC = BIT_EINT1; // ????

	turno = turno + 1;
}

/*---- OJO HARDCODEADO PARA QUE SEA UNA MATRIZ DE 3X3 ---*/
int key_read()
{
	int value= -1;
	char temp;
	// Identificar la tecla mediante ''scanning''
	// Si la identificación falla la función debe devolver -1
	temp = *(keyboard_base + 0xfd) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 0; break;
		case 0xB:  value = 1; break;
		case 0xD:  value = 2; break;
		case 0xE:  value = 15; break;
	}

	temp = *(keyboard_base + 0xfb) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 3; break;
		case 0xB:  value = 4; break;
		case 0xD:  value = 5; break;
		case 0xE:  value = 15; break;
	}

	temp = *(keyboard_base + 0xf7) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 6; break;
		case 0xB:  value = 7; break;
		case 0xD:  value = 8; break;
		case 0xE:  value = 15; break;
	}

	temp = *(keyboard_base + 0xef) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 15; break;
		case 0xB:  value = 15; break;
		case 0xD:  value = 15; break;
		case 0xE:  value = 15; break;
	}

	return value;

}
