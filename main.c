/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "visualizacion.h"
#include "playerMovement.h"

extern void keyboard_init();

int empezar; // Si el maletín ha pulsado el botón
int empezarOtro;

int turno;

const int NCOL = 3;

char str[1];
int tablero[9]; // 0 vacío, 1 el primer jugador, 2 el segundo jugador


/*--- declaracion de funciones ---*/
int Main(void);

int Main(void){

	int i;
	//Inicializamos el tablero:
	for ( i = 0; i < NCOL*NCOL; i++){
		tablero[i] = 0;
	}

	empezar = 0;
	turno = 1;
	empezarOtro = 0;

	sys_init(); // inicializacion de la placa, interrupciones, puertos
	//friedSeed = -1;
	Uart_Init(115200); // inicializacion de la Uart
	keyboard_init();
	Eint4567_init();

	init_visualizacion();
	init_welcome3R();

	int emp = 0;
	int empO = 0;

	char *pt_str = str;

	/*while(empezar == 0 || empezarOtro == 0){
		emp = empezar;
		*pt_str = Uart1_Getch();
		if(*pt_str == 'a'){
			empezarOtro =1;
			empO=1;
		}
		pt_str = str;
	}
*/
	lcd_clear();
	drawTab();

	while(1){
		*pt_str = Uart1_Getch(); // leer caracter
		if (*pt_str >= 0 && *pt_str < NCOL*NCOL){
			D8Led_symbol(*pt_str);
			tablero[*pt_str] = (turno % 2) +1;
			if (turno % 2 == 0){
				drawX(*pt_str);
			}
			else {
				drawO(*pt_str);
			}
			int fin = comprobarFinDelJuego();

			if(fin != 0){
				drawFin(fin);
			}
			turno++;

		}
		pt_str = str;
	}
	return 0;
}
